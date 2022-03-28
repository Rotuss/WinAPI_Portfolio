#pragma once
#include "GameEngineBase/GameEngineNameObject.h"

// 설명 : 
class GameEngine;
class GameEngineLevel : public GameEngineNameObject
{
	// GameEngineLevel은 GameEngine한테만큼은 모든 것을 공개(friend) - 이렇게 한 이유? => Loading은 두 번 호출되면 안되기 때문
	friend GameEngine;
public:
	// constrcuter destructer
	GameEngineLevel();
	virtual ~GameEngineLevel();

	// delete Function
	GameEngineLevel(const GameEngineLevel& _Other) = delete;
	GameEngineLevel(GameEngineLevel&& _Other) noexcept = delete;
	GameEngineLevel& operator=(const GameEngineLevel& _Other) = delete;
	GameEngineLevel& operator=(GameEngineLevel&& _Other) noexcept = delete;

protected:
	virtual void Loading() = 0;
	
	// 레벨수준의 업데이트
	virtual void Update() = 0;

private:
	template<typename ActorType>
	ActorType* CreateActor(const std::string& _Name)
	{
		return nullptr;
	}
};

