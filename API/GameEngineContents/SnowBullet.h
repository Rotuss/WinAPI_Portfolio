#pragma once
#include <GameEngine/GameEngineActor.h>

enum class BulletDir
{
	LEFT,
	RIGHT,
};
// Ό³Έν : 
class GameEngineImage;
class GameEngineCollision;
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
	void SetBDir(const std::string& _Name)
	{
		ChangeBDirText_ = _Name;
	}
	void DirBulletCheck();

protected:

private:
	void Start() override;
	void Update() override;
	
	void CollisionFloorCheck();

	float XSpeed_;
	float YSpeed_;
	float DownSpeed_;
	float4 SnowBulletDir_;
	float4 YDir_;

	GameEngineImage*		FloorColImage_;
	GameEngineCollision*	BulletCollision_;
	GameEngineRenderer*		BulletAnimationRender_;
	BulletDir				BCurrentDir_;
	std::string				ChangeBDirText_;
};

