#include "GameEngineFolderImage.h"
#include "GameEngineImageManager.h"
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEngineBase/GameEngineFile.h>

// �̹��� ���̺귯���� �ʿ�
#pragma comment(lib,"msimg32.lib")

GameEngineFolderImage::GameEngineFolderImage()
{
}

GameEngineFolderImage::~GameEngineFolderImage()
{
	for (size_t i = 0; i < Images_.size(); ++i)
	{
		delete Images_[i];
		Images_[i] = nullptr;
	}
}

bool GameEngineFolderImage::Load(const std::string& _Path)
{
	GameEngineDirectory ResourcesDir = GameEngineDirectory(_Path);

	std::vector<GameEngineFile> AllImageFileList = ResourcesDir.GetAllFile("bmp");
	Images_.reserve(AllImageFileList.size());
	for (size_t i = 0; i < AllImageFileList.size(); ++i)
	{
		GameEngineImage* Image = new GameEngineImage();

		if (false == Image->Load(AllImageFileList[i].GetFullPath()))
		{
			MsgBoxAssert("���� �̹��� �ε� �� ������ �̹����� �����մϴ�.");
		}
		Images_.push_back(Image);
	}
	return true;
}
