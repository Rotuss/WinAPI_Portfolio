#include "Monster.h"

Monster::Monster()
{
}

Monster::~Monster()
{
}

void Monster::Start()
{
	SetPosition({ 640,600 });
	SetScale({ 100,100 });
}

void Monster::Render()
{
	DebugRectRender();
}
