#include "GameEngine.h"
#include "GameEngineLevel.h"
#include "GameEngineImageManager.h"
#include <GameEngineBase/GameEngineWindow.h>

// 초기화
std::map<std::string, GameEngineLevel*> GameEngine::AllLevel_;
GameEngineLevel* GameEngine::CurrentLevel_ = nullptr;
GameEngineLevel* GameEngine::NextLevel_ = nullptr;
GameEngine* GameEngine::UserContents_ = nullptr;
GameEngineImage* GameEngine::BackBufferImage_ = nullptr;

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
	// CurrentLevel이 아닌 NextLevel인 이유? => CurrentLevel로 할 경우, Title로 들어가서 Play로 나오기 때문
	NextLevel_ = FindIter->second;
}

void GameEngine::EngineInit()
{
	// 여기서 윈도우의 크기가 결정되는 것이므로
	UserContents_->GameInit();
	// 백버퍼를 만듦
	BackBufferImage_ = GameEngineImageManager::GetInst()->Create("BackBuffer", GameEngineWindow::GetScale());
}

void GameEngine::EngineLoop()
{
	// 엔진수준에서 매 프레임마다 체크
	UserContents_->GameLoop();

	// 시점함수 : Level이 바뀌는 순간
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
	}

	if (nullptr == CurrentLevel_)
	{
		MsgBoxAssert("Level is nullptr => GameEngine Loop Error");
	}
	// (시간제한이 있는 게임이라면)레벨수준에서 매 프레임마다 시간을 체크하는 일
	CurrentLevel_->Update();
	CurrentLevel_->ActorUpdate();
	CurrentLevel_->ActorRender();
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
}
