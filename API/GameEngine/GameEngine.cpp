#include "GameEngine.h"
#include "GameEngineLevel.h"
#include "GameEngineImageManager.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineTime.h>

// �ʱ�ȭ
std::map<std::string, GameEngineLevel*> GameEngine::AllLevel_;
GameEngineLevel* GameEngine::CurrentLevel_ = nullptr;
GameEngineLevel* GameEngine::NextLevel_ = nullptr;
GameEngine* GameEngine::UserContents_ = nullptr;
GameEngineImage* GameEngine::BackBufferImage_ = nullptr;
GameEngineImage* GameEngine::WindowMainImage_ = nullptr;

HDC GameEngine::BackBufferDC()
{
	return BackBufferImage_->ImageDC();
}

GameEngine::GameEngine()
{}

GameEngine::~GameEngine()
{}

void GameEngine::GameInit()
{
}

void GameEngine::GameLoop()
{
}

void GameEngine::GameEnd()
{
}

void GameEngine::WindowCreate()
{
	GameEngineWindow::GetInst().CreateGameWindow(nullptr, "GameWindow");
	GameEngineWindow::GetInst().ShowGameWindow();
	GameEngineWindow::GetInst().MessageLoop(EngineInit, EngineLoop);
}

void GameEngine::ChangeLevel(const std::string& _Name)
{
	std::map<std::string, GameEngineLevel*>::iterator FindIter = AllLevel_.find(_Name);

	if (AllLevel_.end() == FindIter)
	{
		MsgBoxAssert("Level Find Error");
		return;
	}
	// CurrentLevel�� �ƴ� NextLevel�� ����? => CurrentLevel�� �� ���, Title�� ���� Play�� ������ ����
	NextLevel_ = FindIter->second;
}

void GameEngine::EngineInit()
{
	// ���⼭ �������� ũ�Ⱑ �����Ǵ� ���̹Ƿ�
	UserContents_->GameInit();
	// ����۸� ����. ������۸�? => �ϳ��� �̹����� �ټ��� ��������� ������ �� ������׵��� ���� �ٲ�� ����� ���̴� ���� �̹��� 1���� ����ȴٴ� ������ ���̷��� ��
	//								(������ �̹��� �ϳ� �����Ͽ� �װ��� �׸� ���� ���縦 1���� �ϴ� ��)
	WindowMainImage_ = GameEngineImageManager::GetInst()->Create("WindowMain", GameEngineWindow::GetHDC());
	BackBufferImage_ = GameEngineImageManager::GetInst()->Create("BackBuffer", GameEngineWindow::GetScale());
}

void GameEngine::EngineLoop()
{
	GameEngineTime::GetInst()->Update();
	// �������ؿ��� �� �����Ӹ��� üũ
	UserContents_->GameLoop();

	// �����Լ� : Level�� �ٲ�� ����
	if (nullptr != NextLevel_)
	{
		if (nullptr != CurrentLevel_)
		{
			CurrentLevel_->LevelChangeEnd();
		}
		
		CurrentLevel_ = NextLevel_;
		
		if (nullptr != CurrentLevel_)
		{
			CurrentLevel_->LevelChangeStart();
		}

		NextLevel_ = nullptr;
		GameEngineTime::GetInst()->Reset();

		Rectangle(WindowMainImage_->ImageDC(), 0, 0, WindowMainImage_->GetScale().ix(), WindowMainImage_->GetScale().iy());
		Rectangle(BackBufferImage_->ImageDC(), 0, 0, BackBufferImage_->GetScale().ix(), BackBufferImage_->GetScale().iy());
	}

	if (nullptr == CurrentLevel_)
	{
		MsgBoxAssert("Level is nullptr => GameEngine Loop Error");
	}
	GameEngineInput::GetInst()->Update(GameEngineTime::GetInst()->GetDeltaTime());
	// (�ð������� �ִ� �����̶��)�������ؿ��� �� �����Ӹ��� �ð��� üũ�ϴ� ��
	CurrentLevel_->Update();
	CurrentLevel_->ActorUpdate();
	CurrentLevel_->ActorRender();
	CurrentLevel_->CollisionDebugRender();
	//WindowMainImage_->BitCopy(BackBufferImage_, { 0, 0 }, { 0, 0 }, WindowMainImage_->GetScale());
	WindowMainImage_->BitCopy(BackBufferImage_);
	CurrentLevel_->ActorRelease();
}

void GameEngine::EngineEnd()
{
	UserContents_->GameEnd();

	std::map<std::string, GameEngineLevel*>::iterator StartIter = AllLevel_.begin();
	std::map<std::string, GameEngineLevel*>::iterator EndIter = AllLevel_.end();

	for (; StartIter != EndIter; ++StartIter)
	{
		if (nullptr == StartIter->second)
		{
			continue;
		}
		delete StartIter->second;
	}
	GameEngineImageManager::Destroy();
	GameEngineWindow::Destroy();
	GameEngineInput::Destroy();
	GameEngineTime::Destroy();
}
