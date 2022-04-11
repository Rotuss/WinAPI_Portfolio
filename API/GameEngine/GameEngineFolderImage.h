#pragma once
#include <GameEngineBase/GameEngineMath.h>
#include <GameEngineBase/GameEngineNameObject.h>
#include <Windows.h>
#include <vector>
#include "GameEngineImage.h"

// Ό³Έν : 
class GameEngineFolderImage : public GameEngineNameObject
{
public:
	// constrcuter destructer
	GameEngineFolderImage();
	~GameEngineFolderImage();

	// delete Function
	GameEngineFolderImage(const GameEngineFolderImage& _Other) = delete;
	GameEngineFolderImage(GameEngineFolderImage&& _Other) noexcept = delete;
	GameEngineFolderImage& operator=(const GameEngineFolderImage& _Other) = delete;
	GameEngineFolderImage& operator=(GameEngineFolderImage&& _Other) noexcept = delete;

	bool Load(const std::string& _Path);

protected:

private:
	std::vector<GameEngineImage*> Images_;
};

