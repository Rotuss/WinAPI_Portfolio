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
#include <GameEngineBase/GameEngineSound.h>
#include <GameEngine/GameEngineImageManager.h>

SnowBros::SnowBros()
{}

SnowBros::~SnowBros()
{}

void SnowBros::GameInit()
{
	// ���������� * 4
	GameEngineWindow::GetInst().SetWindowScaleAndPosition({ 100, 30 }, { 1024, 964 });
	
	{
		// ���� ���͸�
		GameEngineDirectory ResourcesDir;
		ResourcesDir.MoveParent("API");
		ResourcesDir.Move("Resources");
		ResourcesDir.Move("Image");

		// ���� �ȿ� ��� �̹��� ������ ã��
		std::vector<GameEngineFile> AllImageFileList = ResourcesDir.GetAllFile("bmp");

		for (size_t i = 0; i < AllImageFileList.size(); ++i)
		{
			GameEngineImageManager::GetInst()->Load(AllImageFileList[i].GetFullPath());
		}
	}
	{
		// ���� ���͸�
		GameEngineDirectory ResourcesDir;
		ResourcesDir.MoveParent("API");
		ResourcesDir.Move("Resources");
		ResourcesDir.Move("Sound");

		// ���� �ȿ� ��� ���� ������ ã��
		std::vector<GameEngineFile> AllSoundFileList = ResourcesDir.GetAllFile();

		for (size_t i = 0; i < AllSoundFileList.size(); ++i)
		{
			GameEngineSound::LoadRes(AllSoundFileList[i].GetFullPath());
		}
	}
	// ���� �̹����� �̿��� ���
	{
		GameEngineDirectory ResourcesDir;
		ResourcesDir.MoveParent("API");
		ResourcesDir.Move("Resources");
		ResourcesDir.Move("Image");
		//ResourcesDir.Move("���ϴ� �����̹�����");

		GameEngineImageManager::GetInst()->FolderImageLoad(ResourcesDir.GetFullPath());
	}
	if (false == GameEngineInput::GetInst()->IsKey("LevelChange"))
	{
		GameEngineInput::GetInst()->CreateKey("LevelChange", 'P');
	}

	{
		GameEngineImage* Image = GameEngineImageManager::GetInst()->Find("Nick_Walk_Right.bmp");
		Image->CutCount(4, 1);
		Image = GameEngineImageManager::GetInst()->Find("Nick_Walk_Left.bmp");
		Image->CutCount(4, 1);
	}

	// �� ���� ����
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
