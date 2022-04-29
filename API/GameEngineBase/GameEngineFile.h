#pragma once
#include "GameEnginePath.h"

enum class OpenMode
{
	Read,
	Write,
};
// Ό³Έν : 
class GameEngineFile : public GameEnginePath
{
public:
	// constrcuter destructer
	GameEngineFile();
	GameEngineFile(const char* _Path);
	GameEngineFile(std::filesystem::path _Path);
	~GameEngineFile();

	// delete Function
	GameEngineFile(const GameEngineFile& _Other);
	//GameEngineFile(GameEngineFile&& _Other) noexcept = delete;
	//GameEngineFile& operator=(const GameEngineFile& _Other) = delete;
	//GameEngineFile& operator=(GameEngineFile&& _Other) noexcept = delete;

	void Open(OpenMode _Mode);
	void ReadOpen()
	{
		Open(OpenMode::Read);
	}
	void WriteOpen()
	{
		Open(OpenMode::Write);
	}

	void Close();

	void Create()
	{
		Open(OpenMode::Write);
		Close();
	}

protected:

private:
	FILE* FilePtr;
};

