#pragma once
#include <map>
#include <vector>
#include "GameEngineEnum.h"
#include "GameEngineActorSubObject.h"

// 설명 : 
class GameEngineImage;
class GameEngineCollision : public GameEngineActorSubObject
{
	friend GameEngineActor;
	friend GameEngineLevel;
public:
	// constrcuter destructer
	GameEngineCollision();
	~GameEngineCollision();

	// delete Function
	GameEngineCollision(const GameEngineCollision& _Other) = delete;
	GameEngineCollision(GameEngineCollision&& _Other) noexcept = delete;
	GameEngineCollision& operator=(const GameEngineCollision& _Other) = delete;
	GameEngineCollision& operator=(GameEngineCollision&& _Other) noexcept = delete;

	inline void SetPivot(const float4& _Pos)
	{
		Pivot_ = _Pos;
	}
	inline void SetScale(const float4& _Scale)
	{
		Scale_ = _Scale;
	}
	inline float4 GetCollisionPos()
	{
		return GetActor()->GetPosition() + Pivot_;
	}
	inline GameEngineRect GetRect()
	{
		return GameEngineRect(GetActor()->GetPosition() + Pivot_ + NextPos_, Scale_);
	}
	
	void CameraEffectOff()
	{
		IsCameraEffect_ = false;
	}
	void CameraEffectOn()
	{
		IsCameraEffect_ = true;
	}
	
	// 충돌한 대상이 존재하는지만 확인하는 함수
	bool CollisionCheck(const std::string& _TargetGroup, CollisionType _This = CollisionType::RECT, CollisionType _Target = CollisionType::RECT);
	bool NextPostCollisionCheck(const std::string& _TargetGroup, float4 _NextPos, CollisionType _This = CollisionType::CIRCLE, CollisionType _Target = CollisionType::CIRCLE);
	bool CollisionResult(const std::string& _TargetGroup, std::vector<GameEngineCollision*>& _ColResult, CollisionType _This = CollisionType::RECT, CollisionType _Target = CollisionType::RECT);
	void DebugRender();
protected:

private:
	friend class FrameAnimation;

	// 액터에서 Pivot_{n, n}만큼 떨어진 Scale_{n, n}만큼(중심이 기준)
	float4 Pivot_;
	float4 Scale_;
	float4 NextPos_;

	bool IsCameraEffect_;

	std::string CollisionName_;

	void NextPosReset()
	{
		NextPos_ = float4::ZERO;
	}
};

