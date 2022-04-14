#pragma once
#include <map>

// ���� : 
class GameEngineTime
{
public:
	static GameEngineTime* GetInst()
	{
		return Inst_;
	}

	// �������� ����� �ϴ��� �ǵ��� �������� ����� �ͱ� ������ �����ͷ� ����
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

	static inline float GetDeltaTime(int _Key)
	{
		return Inst_->DeltaTime_ * Inst_->GetTimeScale(_Key);
	}

	float GetTimeScale(int _Key)
	{
		return TimeScale_[_Key];
	}
	
	void SetTimeScale(int _Key, float _TimeScale)
	{
		if (TimeScale_.end() == TimeScale_.find(_Key))
		{
			_TimeScale = 1.0f;
		}
		TimeScale_[_Key] = _TimeScale;
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
	std::map<int, float> TimeScale_;

	static GameEngineTime* Inst_;
};

