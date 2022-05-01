#include "Candy.h"
#include <GameEngineBase/GameEngineTime.h>

Candy::Candy()
	:Time_(10.0f)
{
}

Candy::~Candy()
{
}

void Candy::Start()
{
	CandyCollision_ = CreateCollision("CandyHitBox", {});

	Actor_ = CreateRenderer("Candy.bmp");
	Actor_->SetPivot({ 0,10 });
}

void Candy::Update()
{
	Time_ -= GameEngineTime::GetDeltaTime();

	if (Time_ <= 0)
	{
		Death();
	}

	if (true == CandyCollision_->CollisionCheck("PlayerHitBox", CollisionType::RECT, CollisionType::RECT))
	{
		// ½ºÄÚ¾îUI +100
		Death();
	}
}

void Candy::Render()
{
}
