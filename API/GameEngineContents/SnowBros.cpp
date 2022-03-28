#include "SnowBros.h"
#include "TitleLevel.h"
#include "PlayLevel.h"
#include "EndingLevel.h"

SnowBros::SnowBros()
{}

SnowBros::~SnowBros()
{}

void SnowBros::GameInit()
{
	CreateLevel<TitleLevel>("Title");
	CreateLevel<PlayLevel>("Play");
	CreateLevel<EndingLevel>("Ending");
	ChangeLevel("Title");
}

void SnowBros::GameLoop()
{
}

void SnowBros::GameEnd()
{
}
