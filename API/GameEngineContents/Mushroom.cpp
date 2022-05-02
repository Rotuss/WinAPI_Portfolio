#include "Mushroom.h"
#include "Score.h"
#include "ScoreMoveUp.h"
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
		GameEngineSound::SoundPlayOneShot("Item_Effect(10).mp3", 0);
		ScoreMoveUp* ScoreImage_ = GetLevel()->CreateActor<ScoreMoveUp>(5);
		ScoreImage_->SetPosition(GetPosition());
		ScoreImage_->Type_ = 600;
		// ½ºÄÚ¾îUI +600
		Score::ScoreUI_ += 600;
		Death();
	}
}

void Mushroom::Render()
{
}
