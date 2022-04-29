#include "Score.h"

Score::Score()
{
}

Score::~Score()
{
}

void Score::Start()
{
	Actor_1P = CreateRenderer("1PLogo.bmp");
	Actor_1P->SetPivot(float4{ 100,20 });

	Number0 = CreateRenderer("Number.bmp");
	Number0->SetPivot(float4{ 272,50 });
	Number0->SetIndex(0);

	Number0->CreateAnimation("Number.bmp", "0", 0, 0, 0.0f, false);
	Number0->CreateAnimation("Number.bmp", "1", 1, 1, 0.0f, false);
	Number0->CreateAnimation("Number.bmp", "2", 2, 2, 0.0f, false);
	Number0->CreateAnimation("Number.bmp", "3", 3, 3, 0.0f, false);
	Number0->CreateAnimation("Number.bmp", "4", 4, 4, 0.0f, false);
	Number0->CreateAnimation("Number.bmp", "5", 5, 5, 0.0f, false);
	Number0->CreateAnimation("Number.bmp", "6", 6, 6, 0.0f, false);
	Number0->CreateAnimation("Number.bmp", "7", 7, 7, 0.0f, false);
	Number0->CreateAnimation("Number.bmp", "8", 8, 8, 0.0f, false);
	Number0->CreateAnimation("Number.bmp", "9", 9, 9, 0.0f, false);

	Number1 = CreateRenderer("Number.bmp");
	Number1->SetPivot(float4{ 240,50 });
	Number1->SetIndex(0);

	Number1->CreateAnimation("Number.bmp", "0", 0, 0, 0.0f, false);
	Number1->CreateAnimation("Number.bmp", "1", 1, 1, 0.0f, false);
	Number1->CreateAnimation("Number.bmp", "2", 2, 2, 0.0f, false);
	Number1->CreateAnimation("Number.bmp", "3", 3, 3, 0.0f, false);
	Number1->CreateAnimation("Number.bmp", "4", 4, 4, 0.0f, false);
	Number1->CreateAnimation("Number.bmp", "5", 5, 5, 0.0f, false);
	Number1->CreateAnimation("Number.bmp", "6", 6, 6, 0.0f, false);
	Number1->CreateAnimation("Number.bmp", "7", 7, 7, 0.0f, false);
	Number1->CreateAnimation("Number.bmp", "8", 8, 8, 0.0f, false);
	Number1->CreateAnimation("Number.bmp", "9", 9, 9, 0.0f, false);

	Number2 = CreateRenderer("Number.bmp");
	Number2->SetPivot(float4{ 208,50 });
	Number2->SetIndex(0);

	Number2->CreateAnimation("Number.bmp", "0", 0, 0, 0.0f, false);
	Number2->CreateAnimation("Number.bmp", "1", 1, 1, 0.0f, false);
	Number2->CreateAnimation("Number.bmp", "2", 2, 2, 0.0f, false);
	Number2->CreateAnimation("Number.bmp", "3", 3, 3, 0.0f, false);
	Number2->CreateAnimation("Number.bmp", "4", 4, 4, 0.0f, false);
	Number2->CreateAnimation("Number.bmp", "5", 5, 5, 0.0f, false);
	Number2->CreateAnimation("Number.bmp", "6", 6, 6, 0.0f, false);
	Number2->CreateAnimation("Number.bmp", "7", 7, 7, 0.0f, false);
	Number2->CreateAnimation("Number.bmp", "8", 8, 8, 0.0f, false);
	Number2->CreateAnimation("Number.bmp", "9", 9, 9, 0.0f, false);

	Number3 = CreateRenderer("Number.bmp");
	Number3->SetPivot(float4{ 176,50 });
	Number3->SetIndex(0);

	Number3->CreateAnimation("Number.bmp", "0", 0, 0, 0.0f, false);
	Number3->CreateAnimation("Number.bmp", "1", 1, 1, 0.0f, false);
	Number3->CreateAnimation("Number.bmp", "2", 2, 2, 0.0f, false);
	Number3->CreateAnimation("Number.bmp", "3", 3, 3, 0.0f, false);
	Number3->CreateAnimation("Number.bmp", "4", 4, 4, 0.0f, false);
	Number3->CreateAnimation("Number.bmp", "5", 5, 5, 0.0f, false);
	Number3->CreateAnimation("Number.bmp", "6", 6, 6, 0.0f, false);
	Number3->CreateAnimation("Number.bmp", "7", 7, 7, 0.0f, false);
	Number3->CreateAnimation("Number.bmp", "8", 8, 8, 0.0f, false);
	Number3->CreateAnimation("Number.bmp", "9", 9, 9, 0.0f, false);

	Number4 = CreateRenderer("Number.bmp");
	Number4->SetPivot(float4{ 144,50 });
	Number4->SetIndex(0);

	Number4->CreateAnimation("Number.bmp", "0", 0, 0, 0.0f, false);
	Number4->CreateAnimation("Number.bmp", "1", 1, 1, 0.0f, false);
	Number4->CreateAnimation("Number.bmp", "2", 2, 2, 0.0f, false);
	Number4->CreateAnimation("Number.bmp", "3", 3, 3, 0.0f, false);
	Number4->CreateAnimation("Number.bmp", "4", 4, 4, 0.0f, false);
	Number4->CreateAnimation("Number.bmp", "5", 5, 5, 0.0f, false);
	Number4->CreateAnimation("Number.bmp", "6", 6, 6, 0.0f, false);
	Number4->CreateAnimation("Number.bmp", "7", 7, 7, 0.0f, false);
	Number4->CreateAnimation("Number.bmp", "8", 8, 8, 0.0f, false);
	Number4->CreateAnimation("Number.bmp", "9", 9, 9, 0.0f, false);

	Number5 = CreateRenderer("Number.bmp");
	Number5->SetPivot(float4{ 112,50 });
	Number5->SetIndex(0);

	Number5->CreateAnimation("Number.bmp", "0", 0, 0, 0.0f, false);
	Number5->CreateAnimation("Number.bmp", "1", 1, 1, 0.0f, false);
	Number5->CreateAnimation("Number.bmp", "2", 2, 2, 0.0f, false);
	Number5->CreateAnimation("Number.bmp", "3", 3, 3, 0.0f, false);
	Number5->CreateAnimation("Number.bmp", "4", 4, 4, 0.0f, false);
	Number5->CreateAnimation("Number.bmp", "5", 5, 5, 0.0f, false);
	Number5->CreateAnimation("Number.bmp", "6", 6, 6, 0.0f, false);
	Number5->CreateAnimation("Number.bmp", "7", 7, 7, 0.0f, false);
	Number5->CreateAnimation("Number.bmp", "8", 8, 8, 0.0f, false);
	Number5->CreateAnimation("Number.bmp", "9", 9, 9, 0.0f, false);

	Number6 = CreateRenderer("Number.bmp");
	Number6->SetPivot(float4{ 80,50 });
	Number6->SetIndex(0);

	Number6->CreateAnimation("Number.bmp", "0", 0, 0, 0.0f, false);
	Number6->CreateAnimation("Number.bmp", "1", 1, 1, 0.0f, false);
	Number6->CreateAnimation("Number.bmp", "2", 2, 2, 0.0f, false);
	Number6->CreateAnimation("Number.bmp", "3", 3, 3, 0.0f, false);
	Number6->CreateAnimation("Number.bmp", "4", 4, 4, 0.0f, false);
	Number6->CreateAnimation("Number.bmp", "5", 5, 5, 0.0f, false);
	Number6->CreateAnimation("Number.bmp", "6", 6, 6, 0.0f, false);
	Number6->CreateAnimation("Number.bmp", "7", 7, 7, 0.0f, false);
	Number6->CreateAnimation("Number.bmp", "8", 8, 8, 0.0f, false);
	Number6->CreateAnimation("Number.bmp", "9", 9, 9, 0.0f, false);
	
	//==========================================================

	Actor_HI = CreateRenderer("HILogo.bmp");
	Actor_HI->SetPivot(float4{ 420,20 });

	HNumber0 = CreateRenderer("Number.bmp");
	HNumber0->SetPivot(float4{ 592,50 });
	HNumber0->SetIndex(0);

	HNumber0->CreateAnimation("Number.bmp", "0", 0, 0, 0.0f, false);
	HNumber0->CreateAnimation("Number.bmp", "1", 1, 1, 0.0f, false);
	HNumber0->CreateAnimation("Number.bmp", "2", 2, 2, 0.0f, false);
	HNumber0->CreateAnimation("Number.bmp", "3", 3, 3, 0.0f, false);
	HNumber0->CreateAnimation("Number.bmp", "4", 4, 4, 0.0f, false);
	HNumber0->CreateAnimation("Number.bmp", "5", 5, 5, 0.0f, false);
	HNumber0->CreateAnimation("Number.bmp", "6", 6, 6, 0.0f, false);
	HNumber0->CreateAnimation("Number.bmp", "7", 7, 7, 0.0f, false);
	HNumber0->CreateAnimation("Number.bmp", "8", 8, 8, 0.0f, false);
	HNumber0->CreateAnimation("Number.bmp", "9", 9, 9, 0.0f, false);

	HNumber1 = CreateRenderer("Number.bmp");
	HNumber1->SetPivot(float4{ 560,50 });
	HNumber1->SetIndex(0);

	HNumber1->CreateAnimation("Number.bmp", "0", 0, 0, 0.0f, false);
	HNumber1->CreateAnimation("Number.bmp", "1", 1, 1, 0.0f, false);
	HNumber1->CreateAnimation("Number.bmp", "2", 2, 2, 0.0f, false);
	HNumber1->CreateAnimation("Number.bmp", "3", 3, 3, 0.0f, false);
	HNumber1->CreateAnimation("Number.bmp", "4", 4, 4, 0.0f, false);
	HNumber1->CreateAnimation("Number.bmp", "5", 5, 5, 0.0f, false);
	HNumber1->CreateAnimation("Number.bmp", "6", 6, 6, 0.0f, false);
	HNumber1->CreateAnimation("Number.bmp", "7", 7, 7, 0.0f, false);
	HNumber1->CreateAnimation("Number.bmp", "8", 8, 8, 0.0f, false);
	HNumber1->CreateAnimation("Number.bmp", "9", 9, 9, 0.0f, false);

	HNumber2 = CreateRenderer("Number.bmp");
	HNumber2->SetPivot(float4{ 528,50 });
	HNumber2->SetIndex(0);

	HNumber2->CreateAnimation("Number.bmp", "0", 0, 0, 0.0f, false);
	HNumber2->CreateAnimation("Number.bmp", "1", 1, 1, 0.0f, false);
	HNumber2->CreateAnimation("Number.bmp", "2", 2, 2, 0.0f, false);
	HNumber2->CreateAnimation("Number.bmp", "3", 3, 3, 0.0f, false);
	HNumber2->CreateAnimation("Number.bmp", "4", 4, 4, 0.0f, false);
	HNumber2->CreateAnimation("Number.bmp", "5", 5, 5, 0.0f, false);
	HNumber2->CreateAnimation("Number.bmp", "6", 6, 6, 0.0f, false);
	HNumber2->CreateAnimation("Number.bmp", "7", 7, 7, 0.0f, false);
	HNumber2->CreateAnimation("Number.bmp", "8", 8, 8, 0.0f, false);
	HNumber2->CreateAnimation("Number.bmp", "9", 9, 9, 0.0f, false);

	HNumber3 = CreateRenderer("Number.bmp");
	HNumber3->SetPivot(float4{ 496,50 });
	HNumber3->SetIndex(0);
	
	HNumber3->CreateAnimation("Number.bmp", "0", 0, 0, 0.0f, false);
	HNumber3->CreateAnimation("Number.bmp", "1", 1, 1, 0.0f, false);
	HNumber3->CreateAnimation("Number.bmp", "2", 2, 2, 0.0f, false);
	HNumber3->CreateAnimation("Number.bmp", "3", 3, 3, 0.0f, false);
	HNumber3->CreateAnimation("Number.bmp", "4", 4, 4, 0.0f, false);
	HNumber3->CreateAnimation("Number.bmp", "5", 5, 5, 0.0f, false);
	HNumber3->CreateAnimation("Number.bmp", "6", 6, 6, 0.0f, false);
	HNumber3->CreateAnimation("Number.bmp", "7", 7, 7, 0.0f, false);
	HNumber3->CreateAnimation("Number.bmp", "8", 8, 8, 0.0f, false);
	HNumber3->CreateAnimation("Number.bmp", "9", 9, 9, 0.0f, false);
	
	HNumber4 = CreateRenderer("Number.bmp");
	HNumber4->SetPivot(float4{ 464,50 });
	HNumber4->SetIndex(0);
	
	HNumber4->CreateAnimation("Number.bmp", "0", 0, 0, 0.0f, false);
	HNumber4->CreateAnimation("Number.bmp", "1", 1, 1, 0.0f, false);
	HNumber4->CreateAnimation("Number.bmp", "2", 2, 2, 0.0f, false);
	HNumber4->CreateAnimation("Number.bmp", "3", 3, 3, 0.0f, false);
	HNumber4->CreateAnimation("Number.bmp", "4", 4, 4, 0.0f, false);
	HNumber4->CreateAnimation("Number.bmp", "5", 5, 5, 0.0f, false);
	HNumber4->CreateAnimation("Number.bmp", "6", 6, 6, 0.0f, false);
	HNumber4->CreateAnimation("Number.bmp", "7", 7, 7, 0.0f, false);
	HNumber4->CreateAnimation("Number.bmp", "8", 8, 8, 0.0f, false);
	HNumber4->CreateAnimation("Number.bmp", "9", 9, 9, 0.0f, false);
	
	HNumber5 = CreateRenderer("Number.bmp");
	HNumber5->SetPivot(float4{ 432,50 });
	HNumber5->SetIndex(0);
	
	HNumber5->CreateAnimation("Number.bmp", "0", 0, 0, 0.0f, false);
	HNumber5->CreateAnimation("Number.bmp", "1", 1, 1, 0.0f, false);
	HNumber5->CreateAnimation("Number.bmp", "2", 2, 2, 0.0f, false);
	HNumber5->CreateAnimation("Number.bmp", "3", 3, 3, 0.0f, false);
	HNumber5->CreateAnimation("Number.bmp", "4", 4, 4, 0.0f, false);
	HNumber5->CreateAnimation("Number.bmp", "5", 5, 5, 0.0f, false);
	HNumber5->CreateAnimation("Number.bmp", "6", 6, 6, 0.0f, false);
	HNumber5->CreateAnimation("Number.bmp", "7", 7, 7, 0.0f, false);
	HNumber5->CreateAnimation("Number.bmp", "8", 8, 8, 0.0f, false);
	HNumber5->CreateAnimation("Number.bmp", "9", 9, 9, 0.0f, false);
	
	HNumber6 = CreateRenderer("Number.bmp");
	HNumber6->SetPivot(float4{ 400,50 });
	HNumber6->SetIndex(0);
	
	HNumber6->CreateAnimation("Number.bmp", "0", 0, 0, 0.0f, false);
	HNumber6->CreateAnimation("Number.bmp", "1", 1, 1, 0.0f, false);
	HNumber6->CreateAnimation("Number.bmp", "2", 2, 2, 0.0f, false);
	HNumber6->CreateAnimation("Number.bmp", "3", 3, 3, 0.0f, false);
	HNumber6->CreateAnimation("Number.bmp", "4", 4, 4, 0.0f, false);
	HNumber6->CreateAnimation("Number.bmp", "5", 5, 5, 0.0f, false);
	HNumber6->CreateAnimation("Number.bmp", "6", 6, 6, 0.0f, false);
	HNumber6->CreateAnimation("Number.bmp", "7", 7, 7, 0.0f, false);
	HNumber6->CreateAnimation("Number.bmp", "8", 8, 8, 0.0f, false);
	HNumber6->CreateAnimation("Number.bmp", "9", 9, 9, 0.0f, false);
}

void Score::Update()
{
}

void Score::Render()
{
}
