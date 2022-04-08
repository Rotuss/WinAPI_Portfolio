#include "SnowBros.h"
#include "TitleLevel.h"
#include "Floor1.h"
#include "Floor2.h"
#include "Floor3.h"
#include "BossFloor.h"
#include "EndingLevel.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEngineBase/GameEngineFile.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngine/GameEngineImageManager.h>

SnowBros::SnowBros()
{}

SnowBros::~SnowBros()
{}

void SnowBros::GameInit()
{
	// 원본사이즈 * 4
	GameEngineWindow::GetInst().SetWindowScaleAndPosition({ 100, 30 }, { 1024, 964 });
	
	// 현재 디렉터리
	GameEngineDirectory ResourcesDir;
	ResourcesDir.MoveParent("API");
	ResourcesDir.Move("Resources");
	ResourcesDir.Move("Image");

	// 폴더 안에 모든 이미지 파일을 찾음
	std::vector<GameEngineFile> AllImageFileList = ResourcesDir.GetAllFile("bmp");

	for (size_t i = 0; i < AllImageFileList.size(); i++)
	{
		GameEngineImageManager::GetInst()->Load(AllImageFileList[i].GetFullPath());
	}

	if (false == GameEngineInput::GetInst()->IsKey("LevelChange"))
	{
		GameEngineInput::GetInst()->CreateKey("LevelChange", 'P');
	}

	GameEngineImage* Image = GameEngineImageManager::GetInst()->Find("Nick_Right_Walk.bmp");
	Image->CutCount(4, 1);
	
	// 각 레벨 생성
	CreateLevel<TitleLevel>("Title");
	CreateLevel<Floor1>("Floor1");
	CreateLevel<Floor2>("Floor2");
	CreateLevel<Floor3>("Floor3");
	CreateLevel<BossFloor>("BossFloor");
	CreateLevel<EndingLevel>("Ending");
	ChangeLevel("Floor1");
}

void SnowBros::GameLoop()
{
}

void SnowBros::GameEnd()
{
}
