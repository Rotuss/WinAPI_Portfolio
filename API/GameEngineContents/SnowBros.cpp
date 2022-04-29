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
		GameEngineInput::GetInst()->CreateKey("LevelChange", VK_RETURN);
		GameEngineInput::GetInst()->CreateKey("Left", VK_LEFT);
		GameEngineInput::GetInst()->CreateKey("Right", VK_RIGHT);
		GameEngineInput::GetInst()->CreateKey("Debug", '0');
	}

	// UI
	{
		GameEngineImage*
		Image = GameEngineImageManager::GetInst()->Find("Number.bmp");
		Image->Cut({ 32, 32 });
	}
	
	// Nick
	{
		GameEngineImage* 
		Image = GameEngineImageManager::GetInst()->Find("Title.bmp");
		Image->CutCount(3, 1);
		
		Image = GameEngineImageManager::GetInst()->Find("BossStageEnter.bmp");
		Image->CutCount(3, 1);
		
		Image = GameEngineImageManager::GetInst()->Find("Appear.bmp");
		Image->CutCount(4, 1);
		
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

		Image = GameEngineImageManager::GetInst()->Find("Nick_Down_Right.bmp");
		Image->Cut({ 64, 116 });
		Image = GameEngineImageManager::GetInst()->Find("Nick_Down_Left.bmp");
		Image->Cut({ 64, 116 });
		
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

		Image = GameEngineImageManager::GetInst()->Find("Nick_Death.bmp");
		Image->CutCount(3, 1);
	}

	// RedDemon
	{
		GameEngineImage*
		Image = GameEngineImageManager::GetInst()->Find("RedDemon_Idle_Right.bmp");
		Image->Cut({ 96, 96 });
		Image = GameEngineImageManager::GetInst()->Find("RedDemon_Idle_Left.bmp");
		Image->Cut({ 96, 96 });

		Image = GameEngineImageManager::GetInst()->Find("RedDemon_Move_Right.bmp");
		Image->CutCount(2, 1);
		Image = GameEngineImageManager::GetInst()->Find("RedDemon_Move_Left.bmp");
		Image->CutCount(2, 1);

		Image = GameEngineImageManager::GetInst()->Find("RedDemon_Jump_Right.bmp");
		Image->CutCount(2, 1);
		Image = GameEngineImageManager::GetInst()->Find("RedDemon_Jump_Left.bmp");
		Image->CutCount(2, 1);

		Image = GameEngineImageManager::GetInst()->Find("RedDemon_Down_Right.bmp");
		Image->Cut({ 96, 124 });
		Image = GameEngineImageManager::GetInst()->Find("RedDemon_Down_Left.bmp");
		Image->Cut({ 96, 124 });

		Image = GameEngineImageManager::GetInst()->Find("RedDemon_Rolling.bmp");
		Image->CutCount(4, 1);

		Image = GameEngineImageManager::GetInst()->Find("RedDemon_ShakingSnow.bmp");
		Image->CutCount(2, 1);

		Image = GameEngineImageManager::GetInst()->Find("RedDemon_Defeated.bmp");
		Image->CutCount(4, 1);

		Image = GameEngineImageManager::GetInst()->Find("RedDemon_Death.bmp");
		Image->Cut({ 96, 64 });
	}

	// Frog
	{
		GameEngineImage*
		Image = GameEngineImageManager::GetInst()->Find("Frog_Idle_Right.bmp");
		Image->Cut({ 96, 104 });
		Image = GameEngineImageManager::GetInst()->Find("Frog_Idle_Left.bmp");
		Image->Cut({ 96, 104 });

		Image = GameEngineImageManager::GetInst()->Find("Frog_Move_Right.bmp");
		Image->CutCount(2, 1);
		Image = GameEngineImageManager::GetInst()->Find("Frog_Move_Left.bmp");
		Image->CutCount(2, 1);

		Image = GameEngineImageManager::GetInst()->Find("Frog_Jump_Right.bmp");
		Image->Cut({ 64, 120 });
		Image = GameEngineImageManager::GetInst()->Find("Frog_Jump_Left.bmp");
		Image->Cut({ 64, 120 });

		Image = GameEngineImageManager::GetInst()->Find("Frog_ThrowingFire_Right.bmp");
		Image->Cut({ 64, 112 });
		Image = GameEngineImageManager::GetInst()->Find("Frog_ThrowingFire_Left.bmp");
		Image->Cut({ 64, 112 });

		Image = GameEngineImageManager::GetInst()->Find("FrogFire_Right.bmp");
		Image->Cut({ 96, 64});
		Image = GameEngineImageManager::GetInst()->Find("FrogFire_Left.bmp");
		Image->Cut({ 96, 64 });
		Image = GameEngineImageManager::GetInst()->Find("FrogFire_Boom.bmp");
		Image->Cut({ 64, 64 });
		
		Image = GameEngineImageManager::GetInst()->Find("Frog_ShakingSnow.bmp");
		Image->CutCount(2, 1);

		Image = GameEngineImageManager::GetInst()->Find("Frog_Defeated.bmp");
		Image->CutCount(4, 1);

		Image = GameEngineImageManager::GetInst()->Find("Frog_Death.bmp");
		Image->Cut({ 96, 64 });
	}

	// YellowTroll
	{
		GameEngineImage*
		Image = GameEngineImageManager::GetInst()->Find("YellowTroll_Idle_Right.bmp");
		Image->Cut({ 96, 108 });
		Image = GameEngineImageManager::GetInst()->Find("YellowTroll_Idle_Left.bmp");
		Image->Cut({ 96, 108 });

		Image = GameEngineImageManager::GetInst()->Find("YellowTroll_Move_Right.bmp");
		Image->CutCount(2, 1);
		Image = GameEngineImageManager::GetInst()->Find("YellowTroll_Move_Left.bmp");
		Image->CutCount(2, 1);

		Image = GameEngineImageManager::GetInst()->Find("YellowTroll_Jump_Right.bmp");
		Image->CutCount(2, 1);
		Image = GameEngineImageManager::GetInst()->Find("YellowTroll_Jump_Left.bmp");
		Image->CutCount(2, 1);

		Image = GameEngineImageManager::GetInst()->Find("YellowTroll_Down_Right.bmp");
		Image->Cut({ 96, 128 });
		Image = GameEngineImageManager::GetInst()->Find("YellowTroll_Down_Left.bmp");
		Image->Cut({ 96, 128 });

		Image = GameEngineImageManager::GetInst()->Find("YellowTroll_ShakingSnow.bmp");
		Image->CutCount(2, 1);

		Image = GameEngineImageManager::GetInst()->Find("YellowTroll_Defeated.bmp");
		Image->CutCount(4, 1);

		Image = GameEngineImageManager::GetInst()->Find("YellowTroll_Death.bmp");
		Image->Cut({ 96, 64 });
	}

	// Snow
	{
		GameEngineImage*
		Image = GameEngineImageManager::GetInst()->Find("Snow1.bmp");
		Image->Cut({ 84, 64 });
		Image = GameEngineImageManager::GetInst()->Find("Snow2.bmp");
		Image->Cut({ 84, 64 });
		Image = GameEngineImageManager::GetInst()->Find("Snow3.bmp");
		Image->Cut({ 88, 92 });
		Image = GameEngineImageManager::GetInst()->Find("SnowballRolling.bmp");
		Image->CutCount(4, 1);
		Image = GameEngineImageManager::GetInst()->Find("SnowBallEffect.bmp");
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
