#include "PlayLevel.h"
#include "Player.h"
#include "Monster.h"

enum class ORDER
{
	BACKGROUND,
	PLAYER,
	MONSTER,
};

PlayLevel::PlayLevel()
{
}

PlayLevel::~PlayLevel()
{
}

void PlayLevel::Loading()
{
}

void PlayLevel::Update()
{
}

void PlayLevel::LevelChangeStart()
{
	CreateActor<Player>((int)ORDER::PLAYER, "Player");
	CreateActor<Monster>((int)ORDER::MONSTER, "Monster");
}
