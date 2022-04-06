#include "SnowBullet.h"
#include <GameEngineBase/GameEngineTime.h>

SnowBullet::SnowBullet()
{
}

SnowBullet::~SnowBullet()
{
}

void SnowBullet::Start()
{
	CreateRenderer("Snow_Bullet.bmp");
	//Time = 2.0f;
	Death(2.0f);
}

void SnowBullet::Update()
{
	/*
	Time -= GameEngineTime::GetDeltaTime();
	if (0.0f >= Time)
	{
		Death();
		return;
	}
	SetMove(float4::RIGHT * GameEngineTime::GetDeltaTime() * 200.0f);
	*/
}
