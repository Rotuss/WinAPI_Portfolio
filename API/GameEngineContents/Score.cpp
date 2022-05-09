#include "Score.h"

int Score::ScoreUI_ = 0;
int Score::HIScore_ = 0;
bool Score::StartScore_ = true;
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
	int Score10 = ScoreUI_ / 10;
	int Score100 = ScoreUI_ / 100;
	int Score1000 = ScoreUI_ / 1000;
	int Score10000 = ScoreUI_ / 10000;
	//int Score100000 = ScoreUI_ / 100000;

	if ((0 == Score10 % 10))
	{
		Number1->ChangeAnimation("0");
		//HNumber1->ChangeAnimation("0");
	}
	if (1 == Score10 % 10)
	{
		Number1->ChangeAnimation("1");
		//HNumber1->ChangeAnimation("1");
	}
	if (2 == Score10 % 10)
	{
		Number1->ChangeAnimation("2");
		//HNumber1->ChangeAnimation("2");
	}
	if (3 == Score10 % 10)
	{
		Number1->ChangeAnimation("3");
		//HNumber1->ChangeAnimation("3");
	}
	if (4 == Score10 % 10)
	{
		Number1->ChangeAnimation("4");
		//HNumber1->ChangeAnimation("4");
	}
	if (5 == Score10 % 10)
	{
		Number1->ChangeAnimation("5");
		//HNumber1->ChangeAnimation("5");
	}
	if (6 == Score10 % 10)
	{
		Number1->ChangeAnimation("6");
		//HNumber1->ChangeAnimation("6");
	}
	if (7 == Score10 % 10)
	{
		Number1->ChangeAnimation("7");
		//HNumber1->ChangeAnimation("7");
	}
	if (8 == Score10 % 10)
	{
		Number1->ChangeAnimation("8");
		//HNumber1->ChangeAnimation("8");
	}
	if (9 == Score10 % 10)
	{
		Number1->ChangeAnimation("9");
		//HNumber1->ChangeAnimation("9");
	}

	//==========================================================

	if ((0 == Score100 % 10))
	{
		Number2->ChangeAnimation("0");
		//HNumber2->ChangeAnimation("0");
	}
	if (1 == Score100 % 10)
	{
		Number2->ChangeAnimation("1");
		//HNumber2->ChangeAnimation("1");
	}
	if (2 == Score100 % 10)
	{
		Number2->ChangeAnimation("2");
		//HNumber2->ChangeAnimation("2");
	}
	if (3 == Score100 % 10)
	{
		Number2->ChangeAnimation("3");
		//HNumber2->ChangeAnimation("3");
	}
	if (4 == Score100 % 10)
	{
		Number2->ChangeAnimation("4");
		//HNumber2->ChangeAnimation("4");
	}
	if (5 == Score100 % 10)
	{
		Number2->ChangeAnimation("5");
		//HNumber2->ChangeAnimation("5");
	}
	if (6 == Score100 % 10)
	{
		Number2->ChangeAnimation("6");
		//HNumber2->ChangeAnimation("6");
	}
	if (7 == Score100 % 10)
	{
		Number2->ChangeAnimation("7");
		//HNumber2->ChangeAnimation("7");
	}
	if (8 == Score100 % 10)
	{
		Number2->ChangeAnimation("8");
		//HNumber2->ChangeAnimation("8");
	}
	if (9 == Score100 % 10)
	{
		Number2->ChangeAnimation("9");
		//HNumber2->ChangeAnimation("9");
	}

	//==========================================================

	if ((0 == Score1000 % 10))
	{
		Number3->ChangeAnimation("0");
		//HNumber3->ChangeAnimation("0");
	}
	if (1 == Score1000 % 10)
	{
		Number3->ChangeAnimation("1");
		//HNumber3->ChangeAnimation("1");
	}
	if (2 == Score1000 % 10)
	{
		Number3->ChangeAnimation("2");
		//HNumber3->ChangeAnimation("2");
	}
	if (3 == Score1000 % 10)
	{
		Number3->ChangeAnimation("3");
		//HNumber3->ChangeAnimation("3");
	}
	if (4 == Score1000 % 10)
	{
		Number3->ChangeAnimation("4");
		//HNumber3->ChangeAnimation("4");
	}
	if (5 == Score1000 % 10)
	{
		Number3->ChangeAnimation("5");
		//HNumber3->ChangeAnimation("5");
	}
	if (6 == Score1000 % 10)
	{
		Number3->ChangeAnimation("6");
		//HNumber3->ChangeAnimation("6");
	}
	if (7 == Score1000 % 10)
	{
		Number3->ChangeAnimation("7");
		//HNumber3->ChangeAnimation("7");
	}
	if (8 == Score1000 % 10)
	{
		Number3->ChangeAnimation("8");
		//HNumber3->ChangeAnimation("8");
	}
	if (9 == Score1000 % 10)
	{
		Number3->ChangeAnimation("9");
		//HNumber3->ChangeAnimation("9");
	}

	//==========================================================

	if ((0 == Score10000 % 10))
	{
		Number4->ChangeAnimation("0");
		//HNumber4->ChangeAnimation("0");
	}
	if (1 == Score10000 % 10)
	{
		Number4->ChangeAnimation("1");
		//HNumber4->ChangeAnimation("1");
	}
	if (2 == Score10000 % 10)
	{
		Number4->ChangeAnimation("2");
		//HNumber4->ChangeAnimation("2");
	}
	if (3 == Score10000 % 10)
	{
		Number4->ChangeAnimation("3");
		//HNumber4->ChangeAnimation("3");
	}
	if (4 == Score10000 % 10)
	{
		Number4->ChangeAnimation("4");
		//HNumber4->ChangeAnimation("4");
	}
	if (5 == Score10000 % 10)
	{
		Number4->ChangeAnimation("5");
		//HNumber4->ChangeAnimation("5");
	}
	if (6 == Score10000 % 10)
	{
		Number4->ChangeAnimation("6");
		//HNumber4->ChangeAnimation("6");
	}
	if (7 == Score10000 % 10)
	{
		Number4->ChangeAnimation("7");
		//HNumber4->ChangeAnimation("7");
	}
	if (8 == Score10000 % 10)
	{
		Number4->ChangeAnimation("8");
		//HNumber4->ChangeAnimation("8");
	}
	if (9 == Score10000 % 10)
	{
		Number4->ChangeAnimation("9");
		//HNumber4->ChangeAnimation("9");
	}

	//==========================================================
	//==========================================================

	if (true == StartScore_)
	{
		if (0 != ScoreUI_)
		{
  			HIScore_ = ScoreUI_;
			HIScoreCal();
		}
		else if (0 == ScoreUI_)
		{
			return;
		}
	}
	else if (false == StartScore_)
	{
		if (HIScore_ <= ScoreUI_)
		{
			HIScore_ = ScoreUI_;
			HIScoreCal();
		}
		else if(HIScore_ > StartScore_)
		{
			HIScoreCal();
		}
	}
}

void Score::Render()
{
}

void Score::HIScoreCal()
{
	int HScore10 = HIScore_ / 10;
	int HScore100 = HIScore_ / 100;
	int HScore1000 = HIScore_ / 1000;
	int HScore10000 = HIScore_ / 10000;
	//int Score100000 = HIScore_ / 100000;

	if ((0 == HScore10 % 10))
	{
		HNumber1->ChangeAnimation("0");
	}
	if (1 == HScore10 % 10)
	{
		HNumber1->ChangeAnimation("1");
	}
	if (2 == HScore10 % 10)
	{
		HNumber1->ChangeAnimation("2");
	}
	if (3 == HScore10 % 10)
	{
		HNumber1->ChangeAnimation("3");
	}
	if (4 == HScore10 % 10)
	{
		HNumber1->ChangeAnimation("4");
	}
	if (5 == HScore10 % 10)
	{
		HNumber1->ChangeAnimation("5");
	}
	if (6 == HScore10 % 10)
	{
		HNumber1->ChangeAnimation("6");
	}
	if (7 == HScore10 % 10)
	{
		HNumber1->ChangeAnimation("7");
	}
	if (8 == HScore10 % 10)
	{
		HNumber1->ChangeAnimation("8");
	}
	if (9 == HScore10 % 10)
	{
		HNumber1->ChangeAnimation("9");
	}

	//==========================================================

	if ((0 == HScore100 % 10))
	{
		HNumber2->ChangeAnimation("0");
	}
	if (1 == HScore100 % 10)
	{
		HNumber2->ChangeAnimation("1");
	}
	if (2 == HScore100 % 10)
	{
		HNumber2->ChangeAnimation("2");
	}
	if (3 == HScore100 % 10)
	{
		HNumber2->ChangeAnimation("3");
	}
	if (4 == HScore100 % 10)
	{
		HNumber2->ChangeAnimation("4");
	}
	if (5 == HScore100 % 10)
	{
		HNumber2->ChangeAnimation("5");
	}
	if (6 == HScore100 % 10)
	{
		HNumber2->ChangeAnimation("6");
	}
	if (7 == HScore100 % 10)
	{
		HNumber2->ChangeAnimation("7");
	}
	if (8 == HScore100 % 10)
	{
		HNumber2->ChangeAnimation("8");
	}
	if (9 == HScore100 % 10)
	{
		HNumber2->ChangeAnimation("9");
	}

	//==========================================================

	if ((0 == HScore1000 % 10))
	{
		HNumber3->ChangeAnimation("0");
	}
	if (1 == HScore1000 % 10)
	{
		HNumber3->ChangeAnimation("1");
	}
	if (2 == HScore1000 % 10)
	{
		HNumber3->ChangeAnimation("2");
	}
	if (3 == HScore1000 % 10)
	{
		HNumber3->ChangeAnimation("3");
	}
	if (4 == HScore1000 % 10)
	{
		HNumber3->ChangeAnimation("4");
	}
	if (5 == HScore1000 % 10)
	{
		HNumber3->ChangeAnimation("5");
	}
	if (6 == HScore1000 % 10)
	{
		HNumber3->ChangeAnimation("6");
	}
	if (7 == HScore1000 % 10)
	{
		HNumber3->ChangeAnimation("7");
	}
	if (8 == HScore1000 % 10)
	{
		HNumber3->ChangeAnimation("8");
	}
	if (9 == HScore1000 % 10)
	{
		HNumber3->ChangeAnimation("9");
	}

	//==========================================================

	if ((0 == HScore10000 % 10))
	{
		HNumber4->ChangeAnimation("0");
	}
	if (1 == HScore10000 % 10)
	{
		HNumber4->ChangeAnimation("1");
	}
	if (2 == HScore10000 % 10)
	{
		HNumber4->ChangeAnimation("2");
	}
	if (3 == HScore10000 % 10)
	{
		HNumber4->ChangeAnimation("3");
	}
	if (4 == HScore10000 % 10)
	{
		HNumber4->ChangeAnimation("4");
	}
	if (5 == HScore10000 % 10)
	{
		HNumber4->ChangeAnimation("5");
	}
	if (6 == HScore10000 % 10)
	{
		HNumber4->ChangeAnimation("6");
	}
	if (7 == HScore10000 % 10)
	{
		HNumber4->ChangeAnimation("7");
	}
	if (8 == HScore10000 % 10)
	{
		HNumber4->ChangeAnimation("8");
	}
	if (9 == HScore10000 % 10)
	{
		HNumber4->ChangeAnimation("9");
	}
}
