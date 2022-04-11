#pragma once
#include "GameEnginePath.h"

// Ό³Έν : 
class GameEngineFile;
class GameEngineDirectory : public GameEnginePath
{
public:
	// constrcuter destructer
	GameEngineDirectory();
	GameEngineDirectory(const std::string& _Path);
	~GameEngineDirectory();

	// delete Function
	GameEngineDirectory(const GameEngineDirectory& _Other) = delete;
	GameEngineDirectory(GameEngineDirectory&& _Other) noexcept = delete;
	GameEngineDirectory& operator=(const GameEngineDirectory& _Other) = delete;
	GameEngineDirectory& operator=(GameEngineDirectory&& _Other) noexcept = delete;

	void MoveParent();
	void MoveParent(const std::string& _Name);
	void Move(const std::string& _Name);
	bool IsRoot();

	std::vector<GameEngineFile> GetAllFile(const std::string& _Extension = "");

protected:

private:
};

