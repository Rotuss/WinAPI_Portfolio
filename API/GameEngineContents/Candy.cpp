#include "Candy.h"
#include "Score.h"
#include "ScoreMoveUp.h"
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
		GameEngineSound::SoundPlayOneShot("Item_Effect(10).mp3", 0);
		ScoreMoveUp* ScoreImage_ = GetLevel()->CreateActor<ScoreMoveUp>(5);
		ScoreImage_->SetPosition(GetPosition());
		ScoreImage_->Type_ = 100;
		// ½ºÄÚ¾îUI +100
		Score::ScoreUI_ += 100;
		Death();
	}
}

void Candy::Render()
{
}
