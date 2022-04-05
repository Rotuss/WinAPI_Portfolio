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

// ���� ���� ��� �Լ�
void GameEnginePath::SetCurrentPath()
{
	Path_ = std::filesystem::current_path();
}

// ��ȿ�� ������� Ȯ���ϴ� �Լ�
bool GameEnginePath::IsExists()
{
	return std::filesystem::exists(Path_);
}

// Ȯ���� �˾Ƴ��� �Լ�
std::string GameEnginePath::GetExtension()
{
	return Path_.extension().string();
}

// ���ϸ� ������ �Լ�
std::string GameEnginePath::GetFileName()
{
	return Path_.filename().string();
}

// ��� ��� ��ȯ �Լ�
std::string GameEnginePath::GetFullPath()
{
	return Path_.string();
}
