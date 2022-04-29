#pragma once
#include "GameEngineFile.h"

// Ό³Έν : 
class GameEngineReadFile : private GameEngineFile
{
public:
	// constrcuter destructer
	GameEngineReadFile();
	GameEngineReadFile(const std::string& _Path);
	GameEngineReadFile(std::filesystem::path _Path);
	~GameEngineReadFile();

	// delete Function
	GameEngineReadFile(const GameEngineReadFile& _Other);
	//GameEngineFile(GameEngineFile&& _Other) noexcept = delete;
	GameEngineReadFile& operator=(const GameEngineReadFile& _Other) = delete;
	GameEngineReadFile& operator=(GameEngineReadFile&& _Other) noexcept = delete;

protected:

private:
};

