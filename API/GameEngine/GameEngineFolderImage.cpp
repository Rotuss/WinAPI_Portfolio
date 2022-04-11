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
}

bool GameEngineFolderImage::Load(const std::string& _Path)
{
	GameEngineDirectory ResourcesDir = GameEngineDirectory(_Path);

	std::vector<GameEngineFile> AllImageFileList = ResourcesDir.GetAllFile("bmp");
	for (size_t i = 0; i < AllImageFileList.size(); ++i)
	{
		GameEngineImage* Image = new GameEngineImage();

		//Image->Load();
		//Imgaes_.push_back();
	}
	return false;
}
