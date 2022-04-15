#pragma once
#include <GameEngine/GameEngineActor.h>

// Ό³Έν : 
class SnowBullet : public GameEngineActor
{
public:
	// constrcuter destructer
	SnowBullet();
	~SnowBullet();

	// delete Function
	SnowBullet(const SnowBullet& _Other) = delete;
	SnowBullet(SnowBullet&& _Other) noexcept = delete;
	SnowBullet& operator=(const SnowBullet& _Other) = delete;
	SnowBullet& operator=(SnowBullet&& _Other) noexcept = delete;
	
	float Time;
	float4 SetDir(float4 _Dir)
	{
		SnowBulletDir_ = _Dir;
		return SnowBulletDir_;
	}

protected:

private:
	void Start() override;
	void Update() override;

	float XSpeed_;
	float YSpeed_;
	float DownSpeed_;
	float4 SnowBulletDir_;
	float4 YDir_;
};

