#pragma once
#include <Windows.h>
#include <map>
#include <string>

// 설명 : 
class GameEngineInput
{
	friend class GameEngineWindow;
public:
	void Update(float _DeltaTime = 0.0f);
	// ex) 'PlayerJump', 'A'
	void CreateKey(const std::string& _Name, int _Key);

	float GetTime(const std::string& _Name);
	
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
	inline int GetMouseWheel()
	{
		return CurWheelValue_;
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

		// 최초로 키를 눌렀을 경우
		bool Down_;
		// 지속적으로 누르고 있는 경우
		bool Press_;
		// 누르다가 처음으로 뗐을 경우
		bool Up_;
		// 누르지 않고 있는 경우
		bool Free_;

		// ??키가 눌렸다면..
		int Key_;

		float Time_;

		bool KeyCheck()
		{
			// return값이 0이 아니라면 Key_키가 눌렸다는 것
			return 0 != GetAsyncKeyState(Key_);
		}

		void Update(float _DeltaTime);
		void Reset()
		{
			Down_ = false;
			Press_ = false;
			Up_ = false;
			Free_ = true;

		}
	};

	std::map<std::string, GameEngineKey> AllInputKey_;
	int WheelValue_;
	int CurWheelValue_;
};

