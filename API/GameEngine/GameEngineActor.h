#pragma once
#include <GameEngineBase/GameEngineNameObject.h>
#include <GameEngineBase/GameEngineMath.h>
#include <GameEngineBase/GameEngineUpdateObject.h>
#include <list>
#include "GameEngineEnum.h"

// 설명 : 
class GameEngineRenderer;
class GameEngineLevel;
// 다중상속 : 넣어준 순으로 메모리가 잡힘. 두가지 모두 상속한 것
class GameEngineActor : public GameEngineNameObject, public GameEngineUpdateObject
{
	//=======================ActorBase==========================
public:
	// 레벨에게만 나를 세팅한 권한을 부여
	friend GameEngineLevel;
	
	// constrcuter destructer
	GameEngineActor();
	virtual ~GameEngineActor();

	// delete Function
	GameEngineActor(const GameEngineActor& _Other) = delete;
	GameEngineActor(GameEngineActor&& _Other) noexcept = delete;
	GameEngineActor& operator=(const GameEngineActor& _Other) = delete;
	GameEngineActor& operator=(GameEngineActor&& _Other) noexcept = delete;

	inline GameEngineLevel* GetLevel()
	{
		return Level_;
	}
	
	inline float4 GetPosition()
	{
		return Position_;
	}

	inline float4 GetScale()
	{
		return Scale_;
	}

	inline void SetPosition(float4 _Value)
	{
		Position_ = _Value;
	}

	inline void SetMove(float4 _Value)
	{
		Position_ += _Value;
	}

	inline void SetScale(float4 _Value)
	{
		Scale_ = _Value;
	}

protected:
	// 시점함수들은 protected로

	// 시작할 때 무언가를 하고 싶은데 생성자에서는 절대로 못할 부분들을 처리
	virtual void Start() = 0;
	// 지속적으로 게임이 실행될 때 호출
	virtual void Update() {}
	// 지속적으로 게임이 실행될 때 호출
	virtual void Render() {}

	void DebugRectRender();

private:
	GameEngineLevel* Level_;
	float4 Position_;
	float4 Scale_;

	// 나를 만들어준 레벨
	inline void SetLevel(GameEngineLevel* _Level)
	{
		Level_ = _Level;
	}

	//==========================Render==========================
public:
	// 그린다는 기능만 따로 모아 놓음(코드 반복이 너무 많기 때문)
	// 디폴트 인자는 선언에서만 지정 가능
	GameEngineRenderer* CreateRenderer(const std::string& _ImageName, RenderPivot _PivotType = RenderPivot::CENTER, const float4& _PivotPos = { 0, 0 });
	GameEngineRenderer* CreateRendererToScale(const std::string& _ImageName, const float4& _Scale, RenderPivot _PivotType = RenderPivot::CENTER, const float4& _PivotPos = { 0, 0 });

	void Rendering();

private:
	std::list<GameEngineRenderer*> RenderList_;

	std::list<GameEngineRenderer*>::iterator StartRenderIter;
	std::list<GameEngineRenderer*>::iterator EndRenderIter;
};

