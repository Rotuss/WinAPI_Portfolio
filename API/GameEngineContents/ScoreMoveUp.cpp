#include "ScoreMoveUp.h"
#include <GameEngineBase/GameEngineTime.h>

ScoreMoveUp::ScoreMoveUp()
	:Time_(0.5f)
{
}

ScoreMoveUp::~ScoreMoveUp()
{
}

void ScoreMoveUp::Start()
{
}

void ScoreMoveUp::Update()
{
	SetMove(float4::UP * GameEngineTime::GetDeltaTime() * 300.0f);

	if (100 == Type_)
	{
		CreateRenderer("Score100.bmp");
	}
	if (200 == Type_)
	{
		CreateRenderer("Score200.bmp");
	}
	if (600 == Type_)
	{
		CreateRenderer("Score600.bmp");
	}
	if (800 == Type_)
	{
		CreateRenderer("Score800.bmp");
	}
	if (1000 == Type_)
	{
		CreateRenderer("Score1000.bmp");
	}
	if (2000 == Type_)
	{
		CreateRenderer("Score2000.bmp");
	}

	Time_ -= GameEngineTime::GetDeltaTime();
	if (Time_ <= 0)
	{
		Death();
	}
}

void ScoreMoveUp::Render()
{
}
