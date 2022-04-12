#include "GameEngineFolderImage.h"
#include "GameEngineImageManager.h"
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEngineBase/GameEngineFile.h>

// 이미지 라이브러리가 필요
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
			MsgBoxAssert("폴더 이미지 로드 중 실패한 이미지가 존재합니다.");
		}
		Images_.push_back(Image);
	}
	return true;
}
