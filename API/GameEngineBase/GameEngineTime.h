#pragma once

// Ό³Έν : 
class GameEngineTime
{
public:
	static GameEngineTime* GetInst()
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

	void Reset();
	void Update();

	inline float DeltaTime()
	{
		return DeltaTime_;
	}

protected:

private:
	// constrcuter destructer
	GameEngineTime();
	~GameEngineTime();

	// delete Function
	GameEngineTime(const GameEngineTime& _Other) = delete;
	GameEngineTime(GameEngineTime&& _Other) noexcept = delete;
	GameEngineTime& operator=(const GameEngineTime& _Other) = delete;
	GameEngineTime& operator=(GameEngineTime&& _Other) noexcept = delete;

	__int64 SecondCount_;
	__int64 CurrentCount_;
	__int64 PrevCount_;
	float DeltaTime_;
	double RealDeltaTime_;

	static GameEngineTime* Inst_;
};

