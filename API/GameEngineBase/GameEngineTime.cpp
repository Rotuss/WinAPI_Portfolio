#include "GameEngineTime.h"
#include <Windows.h>

GameEngineTime* GameEngineTime::Inst_ = new GameEngineTime();

GameEngineTime::GameEngineTime()
{
}

GameEngineTime::~GameEngineTime()
{
}

void GameEngineTime::Reset()
{
	// 현재까지 센 수
	QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&PrevCount_));
	QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&CurrentCount_));
	QueryPerformanceFrequency(reinterpret_cast<LARGE_INTEGER*>(&SecondCount_));

	Update();
}

void GameEngineTime::Update()
{
	QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&CurrentCount_));

	RealDeltaTime_ = static_cast<double>((CurrentCount_ - PrevCount_) / SecondCount_);
	PrevCount_ = CurrentCount_;

	DeltaTime_ = static_cast<float>(RealDeltaTime_);
}
