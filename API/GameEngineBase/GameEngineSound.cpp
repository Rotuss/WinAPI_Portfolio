#include "GameEngineSound.h"
#include "GameEngineDebug.h"
#include "GameEnginePath.h"
#include "GameEngineString.h"

// bin -> 속성 -> 일반 -> 항목 형식(파일 복사)
// ㄴ +) Git -> 소스 제어에 무시된 파일 추가
// inc -> 속성 -> 일반 -> 항목 형식(빌드에 참여 안 함)
#pragma comment(lib,"fmod_vc.lib")

FMOD::System* SoundSystem_ = nullptr;
class SoundSystemCreater
{
public:
    SoundSystemCreater()
    {
        FMOD::System_Create(&SoundSystem_);

        if (nullptr == SoundSystem_)
        {
            MsgBoxAssert("사운드 시스템 생성에 실패했습니다.");
            return;
        }
        if (FMOD_OK != SoundSystem_->init(32, FMOD_DEFAULT, nullptr))
        {
            MsgBoxAssert("사운드 시스템 섧정이 실패했습니다.");
            return;
        }
    }
};

SoundSystemCreater CreateInst = SoundSystemCreater();

GameEngineSound::GameEngineSound()
{
   // FMOD::System_Create();
}

GameEngineSound::~GameEngineSound()
{
}

bool GameEngineSound::Load(const std::string& _Path)
{
    // FMOD_LOOP_NORMAL : 반복 재생, FMOD_DEFAULT : 기본 재생
    if (FMOD_OK != SoundSystem_->createSound(_Path.c_str(), FMOD_LOOP_NORMAL, nullptr, &Sound))
    {
        MsgBoxAssertString(_Path + "사운드 로드에 실패했습니다.");
        return false;
    }
    return true;
}

//====================ManagementSound=======================
GameEngineSoundPlayer GameEngineSound::SoundPlayControl(const std::string& _Name)
{
    std::string UpperName = GameEngineString::ToUpperReturn(_Name);
    GameEngineSound* FindSound = FindRes(UpperName);
    if (nullptr == FindSound)
    {
        MsgBoxAssert("존재하지 않는 사운드를 재생하려 했습니다.");
        return GameEngineSoundPlayer();
    }
    FMOD::Channel* PlayControl = nullptr;
    SoundSystem_->playSound(FindSound->Sound, nullptr, false, &PlayControl);
    return GameEngineSoundPlayer(FindSound, PlayControl);
}

void GameEngineSound::SoundPlayOneShot(const std::string& _Name, int _LoopCount)
{
    std::string UpperName = GameEngineString::ToUpperReturn(_Name);
    GameEngineSound* FindSound = FindRes(UpperName);
    if (nullptr == FindSound)
    {
        MsgBoxAssert("존재하지 않는 사운드를 재생하려 했습니다.");
        return;
    }
    FMOD::Channel* PlayControl = nullptr;
    SoundSystem_->playSound(FindSound->Sound, nullptr, false, &PlayControl);
    PlayControl->setLoopCount(_LoopCount);
}

void GameEngineSound::Update()
{
    if (nullptr == SoundSystem_)
    {
        return;
    }
    SoundSystem_->update();
}
//=======================Management=========================
std::map<std::string, GameEngineSound*> GameEngineSound::AllRes_;

GameEngineSound* GameEngineSound::FindRes(const std::string& _Name)
{
    std::string UpperName = GameEngineString::ToUpperReturn(_Name);
    std::map<std::string, GameEngineSound*>::iterator FindIter = AllRes_.find(UpperName);
    if (FindIter == AllRes_.end())
    {
        return nullptr;
    }
    return FindIter->second;
}

GameEngineSound* GameEngineSound::LoadRes(const std::string& _Path)
{
    GameEnginePath NewPath = GameEnginePath(_Path);
    return LoadRes(_Path,NewPath.GetFileName());
}

GameEngineSound* GameEngineSound::LoadRes(const std::string& _Path, const std::string& _Name)
{
    std::string UpperName = GameEngineString::ToUpperReturn(_Name);
    GameEngineSound* NewRes = new GameEngineSound();
    if (false == NewRes->Load(_Path))
    {
        delete NewRes;
        NewRes = nullptr;
        return nullptr;
    }
    AllRes_.insert(std::make_pair(UpperName, NewRes));
    return nullptr;
}

void GameEngineSound::AllResourcesDestroy()
{
    for (std::pair<std::string, GameEngineSound*> Res : AllRes_)
    {
        delete Res.second;
        Res.second = nullptr;
    }
    AllRes_.clear();

    if (nullptr != SoundSystem_)
    {
        SoundSystem_->release();
        SoundSystem_ = nullptr;
    }
}

// 사운드 플레이어
GameEngineSoundPlayer::GameEngineSoundPlayer()
    : Sound_(nullptr)
    , ControlHandle_(nullptr)
{}

GameEngineSoundPlayer::GameEngineSoundPlayer(GameEngineSound* _Sound, FMOD::Channel* _ControlHandle)
    : Sound_(_Sound)
    , ControlHandle_(_ControlHandle)
{}

GameEngineSoundPlayer::~GameEngineSoundPlayer()
{}

void GameEngineSoundPlayer::Stop()
{
    if (nullptr == ControlHandle_)
    {
        MsgBoxAssert("사운드 컨트롤 채널에 치명적인 문제가 있습니다.");
        return;
    }
    ControlHandle_->stop();
}

void GameEngineSoundPlayer::PlaySpeed(float _Speed)
{
    if (nullptr == ControlHandle_)
    {
        MsgBoxAssert("사운드 컨트롤 채널에 치명적인 문제가 있습니다.");
        return;
    }
    ControlHandle_->setPitch(_Speed);
}

void GameEngineSoundPlayer::Volume(float _Value)
{
    ControlHandle_->setVolume(_Value);
}

GameEngineSoundPlayer::GameEngineSoundPlayer(const GameEngineSoundPlayer& _Other)
    : Sound_(_Other.Sound_)
    , ControlHandle_(_Other.ControlHandle_)
{}
