#include "StickIceCream.h"
#include "Score.h"
#include "ScoreMoveUp.h"
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
		GameEngineSound::SoundPlayOneShot("Item_Effect(10).mp3", 0);
		ScoreMoveUp* ScoreImage_ = GetLevel()->CreateActor<ScoreMoveUp>(5);
		ScoreImage_->SetPosition(GetPosition());
		ScoreImage_->Type_ = 800;
		// ½ºÄÚ¾îUI +800
		Score::ScoreUI_ += 800;
		Death();
	}
}

void StickIceCream::Render()
{
}
