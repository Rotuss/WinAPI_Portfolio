#include "StickIceCream.h"
#include <GameEngineBase/GameEngineTime.h>

StickIceCream::StickIceCream()
	:Time_(10.0f)
{
}

StickIceCream::~StickIceCream()
{
}

void StickIceCream::Start()
{
	StickIceCreamCollision_ = CreateCollision("StickIceCreamHitBox", {});

	Actor_ = CreateRenderer("StickIceCream.bmp");
	Actor_->SetPivot({ 0,18 });
}

void StickIceCream::Update()
{
	Time_ -= GameEngineTime::GetDeltaTime();

	if (Time_ <= 0)
	{
		Death();
	}

	if (true == StickIceCreamCollision_->CollisionCheck("PlayerHitBox", CollisionType::RECT, CollisionType::RECT))
	{
		// ½ºÄÚ¾îUI +800
		Death();
	}
}

void StickIceCream::Render()
{
}
