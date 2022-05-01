#include "Cake.h"
#include <GameEngineBase/GameEngineTime.h>

Cake::Cake()
	:Time_(10.0f)
{
}

Cake::~Cake()
{
}

void Cake::Start()
{
	CakeCollision_ = CreateCollision("CakeHitBox", {});

	Actor_ = CreateRenderer("Cake.bmp");
	Actor_->SetPivot({ 0,20 });
}

void Cake::Update()
{
	Time_ -= GameEngineTime::GetDeltaTime();

	if (Time_ <= 0)
	{
		Death();
	}

	if (true == CakeCollision_->CollisionCheck("PlayerHitBox", CollisionType::RECT, CollisionType::RECT))
	{
		// ���ھ�UI +2000
		Death();
	}
}

void Cake::Render()
{
}
