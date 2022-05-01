#include "Sandwich.h"
#include <GameEngineBase/GameEngineTime.h>

Sandwich::Sandwich()
	:Time_(10.0f)
{
}

Sandwich::~Sandwich()
{
}

void Sandwich::Start()
{
	SandwichCollision_ = CreateCollision("SandwichHitBox", {});

	Actor_ = CreateRenderer("Sandwich.bmp");
	Actor_->SetPivot({ 0,20 });
}

void Sandwich::Update()
{
	Time_ -= GameEngineTime::GetDeltaTime();

	if (Time_ <= 0)
	{
		Death();
	}

	if (true == SandwichCollision_->CollisionCheck("PlayerHitBox", CollisionType::RECT, CollisionType::RECT))
	{
		// ���ھ�UI +1000
		Death();
	}
}

void Sandwich::Render()
{
}
