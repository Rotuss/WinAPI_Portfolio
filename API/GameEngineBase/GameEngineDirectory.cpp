#include "GameEngineDirectory.h"
#include "GameEngineDebug.h"
#include "GameEngineFile.h"
#include "GameEngineString.h"

GameEngineDirectory::GameEngineDirectory()
{
	SetCurrentPath();
}

GameEngineDirectory::GameEngineDirectory(const char* _Path)
{
	Path_ = _Path;
	if (false == IsExists())
	{
		MsgBoxAssert("존재하지 않는 폴더로 디렉터리를 초기화하려고 했습니다.");
	}
}

GameEngineDirectory::GameEngineDirectory(std::filesystem::path _Path)
{
	Path_ = _Path;
	if (false == IsExists())
	{
		MsgBoxAssert("존재하지 않는 폴더로 디렉터리를 초기화하려고 했습니다.");
	}
}

GameEngineDirectory::GameEngineDirectory(const GameEngineDirectory& _Other)
{
	Path_ = _Other.Path_;
	if (false == IsExists())
	{
		MsgBoxAssert("존재하지 않는 폴더로 디렉토리를 초기화하려고 했습니다.");
	}
}

GameEngineDirectory::~GameEngineDirectory()
{
}

void GameEngineDirectory::MoveParent()
{
	Path_ = Path_.parent_path();
}

void GameEngineDirectory::MoveParent(const std::string& _Name)
{
	while (false == IsRoot())
	{
		Path_ = Path_.parent_path();

		if (GetFileName() == _Name)
		{
			break;
		}
	}
}

void GameEngineDirectory::Move(const std::string& _Name)
{
	std::filesystem::path CheckPath = Path_;
	CheckPath.append(_Name);

	if (false == std::filesystem::exists(CheckPath))
	{
		MsgBoxAssertString(_Name + "경로가 존재하지 않습니다.");
		return;
	}
	Path_ = CheckPath;
}

bool GameEngineDirectory::IsRoot()
{
	return Path_ == Path_.root_directory();
}

std::vector<GameEngineFile> GameEngineDirectory::GetAllFile(const std::string& _Extension)
{
	std::filesystem::directory_iterator DirIter(Path_);
	std::string Extension = _Extension;
	
	if (Extension != "")
	{
		GameEngineString::ToUpper(Extension);

		if (std::string::npos == Extension.find("."))
		{
			Extension = "." + Extension;
		}
	}

	std::vector<GameEngineFile> Return;

	for (const std::filesystem::directory_entry& Entry : DirIter)
	{
		if (true == Entry.is_directory())
		{
			continue;
		}
		
		if (Extension != "")
		{
			GameEnginePath NewPath = Entry.path();

			std::string OtherExtension = NewPath.GetExtension();
			GameEngineString::ToUpper(OtherExtension);

			if (OtherExtension != Extension)
			{
				continue;
			}
		}
		Return.push_back(GameEngineFile(Entry.path()));
	}
	return Return;
}

std::vector<GameEngineDirectory> GameEngineDirectory::GetAllDirectory()
{
	std::filesystem::directory_iterator DirIter(Path_);
	std::vector<GameEngineDirectory> Return;
	
	// 디렉터리까지 다 나오니까 File
	for (const std::filesystem::directory_entry& Entry : DirIter)
	{
		if (true == Entry.is_directory())
		{
			// 이 때 재귀
			Return.push_back(GameEngineDirectory(Entry.path()));
			continue;
		}
	}
	return Return;
}
