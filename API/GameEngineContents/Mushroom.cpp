#include "Mushroom.h"
#include <GameEngineBase/GameEngineTime.h>

Mushroom::Mushroom()
	:Time_(10.0f)
{
}

Mushroom::~Mushroom()
{
}

void Mushroom::Start()
{
	MushroomCollision_ = CreateCollision("MushroomHitBox", {});

	Actor_ = CreateRenderer("Mushroom.bmp");
	Actor_->SetPivot({ 0,18 });
}

void Mushroom::Update()
{
	Time_ -= GameEngineTime::GetDeltaTime();

	if (Time_ <= 0)
	{
		Death();
	}

	if (true == MushroomCollision_->CollisionCheck("PlayerHitBox", CollisionType::RECT, CollisionType::RECT))
	{
		// ½ºÄÚ¾îUI +600
		Death();
	}
}

void Mushroom::Render()
{
}
