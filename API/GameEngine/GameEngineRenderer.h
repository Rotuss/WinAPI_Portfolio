#pragma once
#include "GameEngineEnum.h"
#include "GameEngineActorSubObject.h"

// 설명 : 
class GameEngineImage;
class GameEngineRenderer : public GameEngineActorSubObject
{
	friend GameEngineActor;
public:
	// constrcuter destructer
	GameEngineRenderer();
	~GameEngineRenderer();

	// delete Function
	GameEngineRenderer(const GameEngineRenderer& _Other) = delete;
	GameEngineRenderer(GameEngineRenderer&& _Other) noexcept = delete;
	GameEngineRenderer& operator=(const GameEngineRenderer& _Other) = delete;
	GameEngineRenderer& operator=(GameEngineRenderer&& _Other) noexcept = delete;

	void SetImage(const std::string& _Name);
	void SetImageScale();
	void SetIndex(size_t _Index, float4 _Scale = { -1.0f, -1.0f });
	inline void SetType(const RenderPivot& _Type)
	{
		PivotType_ = _Type;
	}
	inline void SetScaleMode(const RenderScaleMode& _Mode)
	{
		ScaleMode_ = _Mode;
	}
	inline void SetPivot(const float4& _Pos)
	{
		RenderPivot_ = _Pos;
	}
	inline void SetScale(const float4& _Scale)
	{
		RenderScale_ = _Scale;
	}
	inline void SetTransColor(unsigned int _Color)
	{
		TransColor_ = _Color;
	}

protected:
	void Render();

private:
	GameEngineImage*	Image_;
	RenderPivot			PivotType_;
	RenderScaleMode		ScaleMode_;
	float4				RenderPivot_;
	float4				RenderImagePivot_;
	float4				RenderScale_;				// 화면에 그려지는 크기
	float4				RenderImageScale_;			// 이미지에서 잘라내는 크기
	unsigned int		TransColor_;
};

