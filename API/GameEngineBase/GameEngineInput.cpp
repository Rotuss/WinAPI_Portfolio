#include "GameEngineInput.h"
#include "GameEngineDebug.h"

GameEngineInput* GameEngineInput::Inst_ = new GameEngineInput();

GameEngineInput::GameEngineInput()
{
}

GameEngineInput::~GameEngineInput()
{
}

void GameEngineInput::Update()
{
	std::map<std::string, GameEngineKey>::iterator KeyUpdateStart = AllInputKey_.begin();
	std::map<std::string, GameEngineKey>::iterator KeyUpdateEnd= AllInputKey_.end();

	for (; KeyUpdateStart != KeyUpdateEnd; ++KeyUpdateStart)
	{
		GameEngineKey& CurrentKey = KeyUpdateStart->second;
		
		CurrentKey.Update();
	}
}

void GameEngineInput::CreateKey(std::string _Name, int _Key)
{
	// _Name가 존재하는 경우
	if (AllInputKey_.end() != AllInputKey_.find(_Name))
	{
		MsgBoxAssert("이미 존재하는 이름의 키를 재생성하려 했습니다.");
		return;
	}
	
	if ('a' <= _Key && 'z' >= _Key)
	{
		_Key = std::toupper(_Key);
	}

	AllInputKey_.insert(std::make_pair(_Name, GameEngineKey()));
	AllInputKey_[_Name].Key_ = _Key;
	AllInputKey_[_Name].Reset();
}

bool GameEngineInput::IsDown(std::string _Name)
{
	if (AllInputKey_.end() == AllInputKey_.find(_Name))
	{
		MsgBoxAssert("존재하지 않는 키 입니다.");
		return false;
	}
	return AllInputKey_[_Name].Down_;
}

bool GameEngineInput::IsPress(std::string _Name)
{
	if (AllInputKey_.end() == AllInputKey_.find(_Name))
	{
		MsgBoxAssert("존재하지 않는 키 입니다.");
		return false;
	}
	return AllInputKey_[_Name].Press_;
}

bool GameEngineInput::IsUp(std::string _Name)
{
	if (AllInputKey_.end() == AllInputKey_.find(_Name))
	{
		MsgBoxAssert("존재하지 않는 키 입니다.");
		return false;
	}
	return AllInputKey_[_Name].Up_;
}

bool GameEngineInput::IsFree(std::string _Name)
{
	if (AllInputKey_.end() == AllInputKey_.find(_Name))
	{
		MsgBoxAssert("존재하지 않는 키 입니다.");
		return false;
	}
	return AllInputKey_[_Name].Free_;
}

bool GameEngineInput::IsKey(std::string _Name)
{
	if (AllInputKey_.end() != AllInputKey_.find(_Name))
	{
		return true;
	}
	return false;
}

//==========================================================
void GameEngineInput::GameEngineKey::Update()
{
	// 눌렀다
	if (true == KeyCheck())
	{
		// 방금, 처음
		if (true == Free_)
		{
			Down_ = true;
			Press_ = true;
			Up_ = false;
			Free_ = false;
		}
		// 계속
		else if (true == Press_)
		{
			Down_ = false;
			Press_ = true;
			Up_ = false;
			Free_ = false;
		}
	}
	// 안 눌렀다
	else
	{
		// 방금, 처음
		if (true == Press_)
		{
			Down_ = false;
			Press_ = false;
			Up_ = true;
			Free_ = false;
		}
		// 계속
		else if (true == Up_)
		{
			Down_ = false;
			Press_ = false;
			Up_ = false;
			Free_ = true;
		}
	}
}
//==========================================================