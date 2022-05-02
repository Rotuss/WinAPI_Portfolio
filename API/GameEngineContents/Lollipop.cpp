#include "Lollipop.h"
#include "Score.h"
#include "ScoreMoveUp.h"
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
		GameEngineSound::SoundPlayOneShot("Item_Effect(10).mp3", 0);
		ScoreMoveUp* ScoreImage_ = GetLevel()->CreateActor<ScoreMoveUp>(5);
		ScoreImage_->SetPosition(GetPosition());
		ScoreImage_->Type_ = 200;
		// ½ºÄÚ¾îUI +200
		Score::ScoreUI_ += 200;
		Death();
	}
}

void Lollipop::Render()
{
}
