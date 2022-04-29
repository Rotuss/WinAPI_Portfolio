#include "GameEngineFile.h"
#include "GameEngineDebug.h"

GameEngineFile::GameEngineFile()
	:FilePtr(nullptr)
{
}

GameEngineFile::GameEngineFile(const char* _Path)
	: FilePtr(nullptr)
{
	Path_ = _Path;
}

GameEngineFile::GameEngineFile(std::filesystem::path _Path)
	:FilePtr(nullptr)
{
	Path_ = _Path;
}

GameEngineFile::~GameEngineFile()
{
	GameEngineFile::Close();
}

GameEngineFile::GameEngineFile(const GameEngineFile& _Other)
	:FilePtr(nullptr)
{
	Path_ = _Other.Path_;
}

void GameEngineFile::Open(OpenMode _Mode)
{
	// b : 바이너리(바이트 덩어리)
	// t : 텍스트냐
	// 즉 어떤 모드냐에 따라 파일이 저장되었을 때 최종적 형식이 달라짐
	std::string OpenMode = "";
	switch (_Mode)
	{
	case OpenMode::Read:
		OpenMode = "rb";
		break;
	case OpenMode::Write:
		OpenMode = "wb";
		break;
	default:
		break;
	}

	fopen_s(&FilePtr, Path_.string().c_str(), OpenMode.c_str());

	if (nullptr == FilePtr)
	{
		MsgBoxAssert("파일이 정상적으로 열리지 않았습니다.");
	}
}

void GameEngineFile::Close()
{
	if (nullptr != FilePtr)
	{
		fclose(FilePtr);
		FilePtr = nullptr;
	}
}