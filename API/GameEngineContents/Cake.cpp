#include "Cake.h"
#include "Score.h"
#include "ScoreMoveUp.h"
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
		GameEngineSound::SoundPlayOneShot("Item_Effect(10).mp3", 0);
		ScoreMoveUp* ScoreImage_ = GetLevel()->CreateActor<ScoreMoveUp>(5);
		ScoreImage_->SetPosition(GetPosition());
		ScoreImage_->Type_ = 2000;
		// ½ºÄÚ¾îUI +2000
		Score::ScoreUI_ += 2000;
		Death();
	}
}

void Cake::Render()
{
}
