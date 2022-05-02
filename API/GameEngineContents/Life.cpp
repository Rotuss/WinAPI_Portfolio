#include "Life.h"

int Life::LifeUI_ = 2;
Life::Life()
{
}

Life::~Life()
{
}

void Life::Start()
{
	Actor = CreateRenderer("LifeLogo.bmp");
	Actor->SetPivot(float4{ 330,20 });

	Count = CreateRenderer("Number.bmp");
	Count->SetPivot(float4{ 328,50 });
	Count->SetIndex(2);
	
	Count->CreateAnimation("Number.bmp", "0", 0, 0, 0.0f, false);
	Count->CreateAnimation("Number.bmp", "1", 1, 1, 0.0f, false);
	Count->CreateAnimation("Number.bmp", "2", 2, 2, 0.0f, false);
}

void Life::Update()
{
	if (2 == LifeUI_)
	{
		Count->ChangeAnimation("2");
	}
	if (1 == LifeUI_)
	{
		Count->ChangeAnimation("1");
	}
	if (0 == LifeUI_)
	{
		Count->ChangeAnimation("0");
	}
}

void Life::Render()
{
}
