#include "Lollipop.h"
#include "Score.h"
#include <GameEngineBase/GameEngineTime.h>

Lollipop::Lollipop()
	:Time_(10.0f)
{
}

Lollipop::~Lollipop()
{
}

void Lollipop::Start()
{
	LollipopCollision_ = CreateCollision("LollipopHitBox", {});

	Actor_ = CreateRenderer("Lollopop.bmp");
	Actor_->SetPivot({ 0,15 });
}

void Lollipop::Update()
{
	Time_ -= GameEngineTime::GetDeltaTime();

	if (Time_ <= 0)
	{
		Death();
	}

	if (true == LollipopCollision_->CollisionCheck("PlayerHitBox", CollisionType::RECT, CollisionType::RECT))
	{
		// ½ºÄÚ¾îUI +200
		Score::ScoreUI_ += 200;
		Death();
	}
}

void Lollipop::Render()
{
}
