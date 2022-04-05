#include "GameEnginePath.h"

GameEnginePath::GameEnginePath()
{
}

GameEnginePath::GameEnginePath(const std::filesystem::path& _Path)
	:Path_(_Path)
{
}

GameEnginePath::~GameEnginePath()
{
}

// 현재 폴더 경로 함수
void GameEnginePath::SetCurrentPath()
{
	Path_ = std::filesystem::current_path();
}

// 유효한 경로인지 확인하는 함수
bool GameEnginePath::IsExists()
{
	return std::filesystem::exists(Path_);
}

// 확장자 알아내는 함수
std::string GameEnginePath::GetExtension()
{
	return Path_.extension().string();
}

// 파일명만 얻어오는 함수
std::string GameEnginePath::GetFileName()
{
	return Path_.filename().string();
}

// 모든 경로 반환 함수
std::string GameEnginePath::GetFullPath()
{
	return Path_.string();
}
