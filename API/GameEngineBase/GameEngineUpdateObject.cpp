#include "GameEngineUpdateObject.h"

GameEngineUpdateObject::GameEngineUpdateObject()
	: DeathTime_(0.0f)
	, AccTime_(0.0f)
	, IsUpdate_(true)
	, IsReleaseUpdate_(false)
	, IsDeath_(false)
{
}

GameEngineUpdateObject::~GameEngineUpdateObject()
{
}
