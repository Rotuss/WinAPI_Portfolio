#pragma once
#include <map>
#include "GameEngineEnum.h"
#include "GameEngineActorSubObject.h"

// ���� : 
class GameEngineImage;
class GameEngineCollision : public GameEngineActorSubObject
{
	friend GameEngineActor;
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

	// �浹�� ����� �����ϴ����� Ȯ���ϴ� �Լ�
	bool CollisionCheck(const std::string& _TargetGroup, CollisionType _This = CollisionType::RECT, CollisionType _Target = CollisionType::RECT);

protected:

private:
	friend class FrameAnimation;

	// ���Ϳ��� Pivot_{n, n}��ŭ ������ Scale_{n, n}��ŭ(�߽��� ����)
	float4 Pivot_;
	float4 Scale_;
};

