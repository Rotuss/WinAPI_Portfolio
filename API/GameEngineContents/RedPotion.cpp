#include "RedPotion.h"
#include "Score.h"
#include "ScoreMoveUp.h"
#include <GameEngineBase/GameEngineTime.h>

bool RedPotion::RPCheck_ = false;
RedPotion::RedPotion()
	:Time_(10.0f)
{
}

RedPotion::~RedPotion()
{
}

void RedPotion::Start()
{
	RedPotionCollision_ = CreateCollision("RedPotionHitBox", { });

	Actor_ = CreateRenderer();
	Actor_->CreateAnimation("RedPotion.bmp", "RedPotion", 0, 3, 0.2f, true);
	Actor_->ChangeAnimation("RedPotion");
	Actor_->SetPivot({ 0,20 });
}

void RedPotion::Update()
{
	Time_ -= GameEngineTime::GetDeltaTime();

	if (Time_ <= 0)
	{
		Death();
	}

	if (true == RedPotionCollision_->CollisionCheck("PlayerHitBox", CollisionType::RECT, CollisionType::RECT))
	{
		GameEngineSound::SoundPlayOneShot("Item_Effect(10).mp3", 0);
		if (true == RPCheck_)
		{
			ScoreMoveUp* ScoreImage_ = GetLevel()->CreateActor<ScoreMoveUp>(5);
			ScoreImage_->SetPosition(GetPosition());
			ScoreImage_->Type_ = 1000;
			Score::ScoreUI_ += 1000;
		}
		
		RPCheck_ = true;
		Death();
	}
}

void RedPotion::Render()
{
}
