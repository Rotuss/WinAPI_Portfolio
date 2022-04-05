#pragma once
#include "GameEnginePath.h"

// ���� : 
class GameEngineFile : public GameEnginePath
{
public:
	// constrcuter destructer
	GameEngineFile();
	GameEngineFile(std::filesystem::path _Path);
	GameEngineFile(const std::string& _Path);
	~GameEngineFile();

	// delete Function
	GameEngineFile(const GameEngineFile& _Other);
	//GameEngineFile(GameEngineFile&& _Other) noexcept = delete;
	GameEngineFile& operator=(const GameEngineFile& _Other) = delete;
	GameEngineFile& operator=(GameEngineFile&& _Other) noexcept = delete;

protected:

private:
};

