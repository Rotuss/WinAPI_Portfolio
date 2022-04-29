#include "Life.h"

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
}

void Life::Render()
{
}
