#pragma once
#include <Windows.h>
#include <map>
#include <string>

// ���� : 
class GameEngineInput
{
public:
	void Update();
	// ex) 'PlayerJump', 'A'
	void CreateKey(const std::string& _Name, int _Key);

	bool IsDown(const std::string& _Name);
	bool IsPress(const std::string& _Name);
	bool IsUp(const std::string& _Name);
	bool IsFree(const std::string& _Name);
	bool IsKey(const std::string& _Name);
	
	static GameEngineInput* GetInst()
	{
		return Inst_;
	}
	static void Destroy()
	{
		if (nullptr != Inst_)
		{
			delete Inst_;
			Inst_ = nullptr;
		}
	}

protected:

private:
	// constrcuter destructer
	GameEngineInput();
	~GameEngineInput();

	// delete Function
	GameEngineInput(const GameEngineInput& _Other) = delete;
	GameEngineInput(GameEngineInput&& _Other) noexcept = delete;
	GameEngineInput& operator=(const GameEngineInput& _Other) = delete;
	GameEngineInput& operator=(GameEngineInput&& _Other) noexcept = delete;

	static GameEngineInput* Inst_;

	class GameEngineKey
	{
		friend GameEngineInput;

		// ���ʷ� Ű�� ������ ���
		bool Down_;
		// ���������� ������ �ִ� ���
		bool Press_;
		// �����ٰ� ó������ ���� ���
		bool Up_;
		// ������ �ʰ� �ִ� ���
		bool Free_;

		// ??Ű�� ���ȴٸ�..
		int Key_;

		bool KeyCheck()
		{
			// return���� 0�� �ƴ϶�� Key_Ű�� ���ȴٴ� ��
			return 0 != GetAsyncKeyState(Key_);
		}

		void Update();
		void Reset()
		{
			Down_ = false;
			Press_ = false;
			Up_ = false;
			Free_ = true;

		}
	};

	std::map<std::string, GameEngineKey> AllInputKey_;
};

