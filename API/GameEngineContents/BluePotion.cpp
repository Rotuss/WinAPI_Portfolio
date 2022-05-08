#include "BluePotion.h"
#include "Score.h"
#include "ScoreMoveUp.h"
#include <GameEngineBase/GameEngineTime.h>

bool BluePotion::BPCheck_ = false;
BluePotion::BluePotion()
	:Time_(10.0f)
{
}

BluePotion::~BluePotion()
{
}

void BluePotion::Start()
{
	BluePotionCollision_ = CreateCollision("BluePotionHitBox", { });

	Actor_ = CreateRenderer();
	Actor_->CreateAnimation("BluePotion.bmp", "BluePotion", 0, 3, 0.2f, true);
	Actor_->ChangeAnimation("BluePotion");
	Actor_->SetPivot({ 0,20 });
}

void BluePotion::Update()
{
	Time_ -= GameEngineTime::GetDeltaTime();

	if (Time_ <= 0)
	{
		Death();
	}

	if (true == BluePotionCollision_->CollisionCheck("PlayerHitBox", CollisionType::RECT, CollisionType::RECT))
	{
		GameEngineSound::SoundPlayOneShot("Item_Effect(10).mp3", 0);
		if (true == BPCheck_)
		{
			ScoreMoveUp* ScoreImage_ = GetLevel()->CreateActor<ScoreMoveUp>(5);
			ScoreImage_->SetPosition(GetPosition());
			ScoreImage_->Type_ = 1000;
			Score::ScoreUI_ += 1000;
		}
		
		BPCheck_ = true;
		Death();
	}
}

void BluePotion::Render()
{
}
