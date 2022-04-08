#pragma once
#include <map>
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
	
	inline GameEngineImage* GetImage()
	{
		return Image_;
	}

protected:
	void Render();

private:
	friend class FrameAnimation;

	GameEngineImage*	Image_;
	RenderPivot			PivotType_;
	RenderScaleMode		ScaleMode_;
	float4				RenderPivot_;
	float4				RenderImagePivot_;
	float4				RenderScale_;				// 화면에 그려지는 크기
	float4				RenderImageScale_;			// 이미지에서 잘라내는 크기
	unsigned int		TransColor_;

	//=========================Animation========================
public:
	void CreateAnimation(const std::string& _Image, const std::string& _Name, int _StartIndex, int _EndIndex, float _InterTime, bool _Loop = true);
	void ChangeAnimation(const std::string& _Name);

protected:

private:
	class FrameAnimation
	{
	public:
		GameEngineRenderer* Renderer_;
		GameEngineImage*	Image_;
		int					CurrentFrame_;
		int					StartFrame_;
		int					EndFrame_;
		float				CurrentInterTime_;
		float				InterTime_;
		bool				Loop_;

		FrameAnimation()
			: Image_(nullptr)
			, CurrentFrame_(-1)
			, StartFrame_(-1)
			, EndFrame_(-1)
			, CurrentInterTime_(0.1f)
			, InterTime_(0.1f)
			, Loop_(true)
		{}

		void Update();
		void Reset()
		{
			CurrentFrame_ = StartFrame_;
			CurrentInterTime_ = InterTime_;
		}
	};

	std::map<std::string, FrameAnimation> Animations_;
	FrameAnimation* CurrentAnimation_;
};

