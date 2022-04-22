#include "SnowBros.h"
#include "TitleMainLevel.h"
#include "TitleSelectLevel.h"
#include "Floor1.h"
#include "Floor2.h"
#include "Floor3.h"
#include "BossFloor.h"
#include "EndingLevel.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEngineBase/GameEngineFile.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineSound.h>
#include <GameEngine/GameEngineImageManager.h>

SnowBros::SnowBros()
{}

SnowBros::~SnowBros()
{}

void SnowBros::GameInit()
{
	// 원본사이즈 * 4
	GameEngineWindow::GetInst().SetWindowScaleAndPosition({ 100, 30 }, { 1024, 896 });
	
	{
		// 현재 디렉터리
		GameEngineDirectory ResourcesDir;
		ResourcesDir.MoveParent("API");
		ResourcesDir.Move("Resources");
		ResourcesDir.Move("Image");

		// 폴더 안에 모든 이미지 파일을 찾음
		std::vector<GameEngineFile> AllImageFileList = ResourcesDir.GetAllFile("bmp");

		for (size_t i = 0; i < AllImageFileList.size(); ++i)
		{
			GameEngineImageManager::GetInst()->Load(AllImageFileList[i].GetFullPath());
		}
	}
	{
		// 현재 디렉터리
		GameEngineDirectory ResourcesDir;
		ResourcesDir.MoveParent("API");
		ResourcesDir.Move("Resources");
		ResourcesDir.Move("Sound");

		// 폴더 안에 모든 사운드 파일을 찾음
		std::vector<GameEngineFile> AllSoundFileList = ResourcesDir.GetAllFile();

		for (size_t i = 0; i < AllSoundFileList.size(); ++i)
		{
			GameEngineSound::LoadRes(AllSoundFileList[i].GetFullPath());
		}
	}
	// 폴더 이미지로 이용할 경우
	{
		GameEngineDirectory ResourcesDir;
		ResourcesDir.MoveParent("API");
		ResourcesDir.Move("Resources");
		ResourcesDir.Move("Image");
		//ResourcesDir.Move("원하는 폴더이미지명");

		GameEngineImageManager::GetInst()->FolderImageLoad(ResourcesDir.GetFullPath());
	}
	if (false == GameEngineInput::GetInst()->IsKey("LevelChange"))
	{
		GameEngineInput::GetInst()->CreateKey("LevelChange", 'P');
		GameEngineInput::GetInst()->CreateKey("TitleSelect", VK_RETURN);
		GameEngineInput::GetInst()->CreateKey("Floor1", VK_RETURN);
		GameEngineInput::GetInst()->CreateKey("Left", VK_LEFT);
		GameEngineInput::GetInst()->CreateKey("Right", VK_RIGHT);
	}

	{
		GameEngineImage* 
		Image = GameEngineImageManager::GetInst()->Find("Nick_Idle_Right.bmp");
		Image->Cut({ 68, 100 });
		Image = GameEngineImageManager::GetInst()->Find("Nick_Idle_Left.bmp");
		Image->Cut({ 68, 100 });
		
		Image = GameEngineImageManager::GetInst()->Find("Nick_Move_Right.bmp");
		Image->CutCount(3, 1);
		Image = GameEngineImageManager::GetInst()->Find("Nick_Move_Left.bmp");
		Image->CutCount(3, 1);
		
		Image = GameEngineImageManager::GetInst()->Find("Nick_Jump_Right.bmp");
		Image->CutCount(5, 1);
		Image = GameEngineImageManager::GetInst()->Find("Nick_Jump_Left.bmp");
		Image->CutCount(5, 1);

		Image = GameEngineImageManager::GetInst()->Find("Nick_Shooting_Right.bmp");
		Image->CutCount(2, 1);
		Image = GameEngineImageManager::GetInst()->Find("Nick_Shooting_Left.bmp");
		Image->CutCount(2, 1);
		
		Image = GameEngineImageManager::GetInst()->Find("Nick_Push_Right.bmp");
		Image->CutCount(3, 1);
		Image = GameEngineImageManager::GetInst()->Find("Nick_Push_Left.bmp");
		Image->CutCount(3, 1);

		Image = GameEngineImageManager::GetInst()->Find("SnowBullet_Right.bmp");
		Image->CutCount(2, 1);
		Image = GameEngineImageManager::GetInst()->Find("SnowBullet_Left.bmp");
		Image->CutCount(2, 1);
		
		Image = GameEngineImageManager::GetInst()->Find("Push_Start.bmp");
		Image->CutCount(2, 1);
	}

	// 각 레벨 생성
	CreateLevel<TitleMainLevel>("TitleMain");
	CreateLevel<TitleSelectLevel>("TitleSelect");
	CreateLevel<Floor1>("Floor1");
	CreateLevel<Floor2>("Floor2");
	CreateLevel<Floor3>("Floor3");
	CreateLevel<BossFloor>("BossFloor");
	CreateLevel<EndingLevel>("Ending");
	ChangeLevel("TitleMain");
}

void SnowBros::GameLoop()
{
}

void SnowBros::GameEnd()
{
}
