#pragma once

// 설명 : 
class GameEngineTime
{
public:
	static GameEngineTime* GetInst()
	{
		return Inst_;
	}

	// 마지막에 지운다 하더라도 의도한 순서에서 지우고 싶기 때문에 포인터로 삭제
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

	static inline float GetDeltaTime()
	{
		return Inst_->DeltaTime_;
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

