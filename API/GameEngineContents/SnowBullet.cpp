#include "SnowBullet.h"
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineImageManager.h>

SnowBullet::SnowBullet()
	: YDir_(float4::DOWN * 200.0f)
{
}

SnowBullet::~SnowBullet()
{
}

void SnowBullet::Start()
{
	//CreateRenderer("Snow_Bullet.bmp");
	GameEngineRenderer* Render = CreateRenderer();
	Render->CreateAnimation("SnowBullet_Left.bmp", "SnowBullet", 0, 1, 0.12f, true);
	Render->ChangeAnimation("SnowBullet");
	//Time = 2.0f;
	Death(0.25f);

	XSpeed_ = 800.0f;
	YSpeed_ = 100.0f;
	DownSpeed_ = 900.0f;
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
	float4 ResultDir = float4::ZERO;
	// ¸ðµç ÈûÀº ¹»ÇØµµ float4
	ResultDir += SnowBulletDir_ * GameEngineTime::GetDeltaTime() * XSpeed_;
	
	ResultDir += YDir_ * GameEngineTime::GetDeltaTime();
	SetMove(ResultDir);
	//YDir_ *= float4::DOWN * GameEngineTime::GetDeltaTime() * DownSpeed_;
	GameEngineImage* ColImage_ = GameEngineImageManager::GetInst()->Find("Colfloor01.bmp");

	//float4 CheckPos = GetPosition();
	int Color = ColImage_->GetImagePixel(GetPosition());

	if (RGB(0, 0, 0) == Color)
	{
		YDir_ = float4::UP * YSpeed_;
	}
}
