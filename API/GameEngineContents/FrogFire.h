#pragma once
#include <GameEngine/GameEngineActor.h>

enum class FireDir
{
	LEFT,
	RIGHT,
};
// Ό³Έν : 
class GameEngineImage;
class FrogFire : public GameEngineActor
{
public:
	// constrcuter destructer
	FrogFire();
	~FrogFire();

	// delete Function
	FrogFire(const FrogFire& _Other) = delete;
	FrogFire(FrogFire&& _Other) noexcept = delete;
	FrogFire& operator=(const FrogFire& _Other) = delete;
	FrogFire& operator=(FrogFire&& _Other) noexcept = delete;

	float Time;
	float4 SetDir(float4 _Dir)
	{
		FireDir_ = _Dir;
		return FireDir_;
	}
	void SetBDir(const std::string& _Name)
	{
		ChangeFDirText_ = _Name;
	}
	void DirFireCheck();

protected:

private:
	void Start() override;
	void Update() override;

	void CollisionFloorCheck();
	
	float XSpeed_;
	float DeathTime_;
	bool DeathCheck_;
	float4 FireDir_;

	GameEngineImage*		FloorColImage_;
	GameEngineCollision*	FireCollision_;
	GameEngineRenderer*		FireAnimationRender_;
	FireDir					FCurrentDir_;
	std::string				ChangeFDirText_;
};

