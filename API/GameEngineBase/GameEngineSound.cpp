#include "GameEngineSound.h"
#include "GameEngineDebug.h"
#include "GameEnginePath.h"
#include "GameEngineString.h"

// bin -> �Ӽ� -> �Ϲ� -> �׸� ����(���� ����)
// �� +) Git -> �ҽ� ��� ���õ� ���� �߰�
// inc -> �Ӽ� -> �Ϲ� -> �׸� ����(���忡 ���� �� ��)
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
            MsgBoxAssert("���� �ý��� ������ �����߽��ϴ�.");
            return;
        }
        if (FMOD_OK != SoundSystem_->init(32, FMOD_DEFAULT, nullptr))
        {
            MsgBoxAssert("���� �ý��� ������ �����߽��ϴ�.");
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
    // FMOD_LOOP_NORMAL : �ݺ� ���, FMOD_DEFAULT : �⺻ ���
    if (FMOD_OK != SoundSystem_->createSound(_Path.c_str(), FMOD_LOOP_NORMAL, nullptr, &Sound))
    {
        MsgBoxAssertString(_Path + "���� �ε忡 �����߽��ϴ�.");
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
        MsgBoxAssert("�������� �ʴ� ���带 ����Ϸ� �߽��ϴ�.");
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
        MsgBoxAssert("�������� �ʴ� ���带 ����Ϸ� �߽��ϴ�.");
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

// ���� �÷��̾�
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
        MsgBoxAssert("���� ��Ʈ�� ä�ο� ġ������ ������ �ֽ��ϴ�.");
        return;
    }
    ControlHandle_->stop();
}

void GameEngineSoundPlayer::PlaySpeed(float _Speed)
{
    if (nullptr == ControlHandle_)
    {
        MsgBoxAssert("���� ��Ʈ�� ä�ο� ġ������ ������ �ֽ��ϴ�.");
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
