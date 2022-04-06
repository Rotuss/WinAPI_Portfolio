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
	// _Name�� �����ϴ� ���
	if (AllInputKey_.end() != AllInputKey_.find(_Name))
	{
		MsgBoxAssert("�̹� �����ϴ� �̸��� Ű�� ������Ϸ� �߽��ϴ�.");
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
		MsgBoxAssert("�������� �ʴ� Ű �Դϴ�.");
		return false;
	}
	return AllInputKey_[_Name].Down_;
}

bool GameEngineInput::IsPress(std::string _Name)
{
	if (AllInputKey_.end() == AllInputKey_.find(_Name))
	{
		MsgBoxAssert("�������� �ʴ� Ű �Դϴ�.");
		return false;
	}
	return AllInputKey_[_Name].Press_;
}

bool GameEngineInput::IsUp(std::string _Name)
{
	if (AllInputKey_.end() == AllInputKey_.find(_Name))
	{
		MsgBoxAssert("�������� �ʴ� Ű �Դϴ�.");
		return false;
	}
	return AllInputKey_[_Name].Up_;
}

bool GameEngineInput::IsFree(std::string _Name)
{
	if (AllInputKey_.end() == AllInputKey_.find(_Name))
	{
		MsgBoxAssert("�������� �ʴ� Ű �Դϴ�.");
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
	// ������
	if (true == KeyCheck())
	{
		// ���, ó��
		if (true == Free_)
		{
			Down_ = true;
			Press_ = true;
			Up_ = false;
			Free_ = false;
		}
		// ���
		else if (true == Press_)
		{
			Down_ = false;
			Press_ = true;
			Up_ = false;
			Free_ = false;
		}
	}
	// �� ������
	else
	{
		// ���, ó��
		if (true == Press_)
		{
			Down_ = false;
			Press_ = false;
			Up_ = true;
			Free_ = false;
		}
		// ���
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