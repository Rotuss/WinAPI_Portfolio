#pragma once
#include <map>
#include "GameEngineEnum.h"
#include "GameEngineActorSubObject.h"

// 설명 : 
class GameEngineImage;
class GameEngineFolderImage;
class GameEngineRenderer : public GameEngineActorSubObject
{
	friend GameEngineActor;
	friend GameEngineLevel;
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
	void SetIndex(size_t _Index, const float4& _Scale = { -1.0f, -1.0f });
	inline void SetPivotType(const RenderPivot& _Type)
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
	inline void SetAlpha(unsigned int _Alpha)
	{
		Alpha_ = _Alpha;

		if (Alpha_ >= 255)
		{
			Alpha_ = 255;
		}
	}
	void SetOrder(int _Order) override;

	inline GameEngineImage* GetImage()
	{
		return Image_;
	}
	inline float4 GetPivot()
	{
		return RenderPivot_;
	}
	inline float4 GetImagePivot()
	{
		return RenderImagePivot_;
	}
	inline float4 GetScale()
	{
		return RenderScale_;
	}
	inline float4 GetImageScale()
	{
		return RenderImageScale_;
	}
	void SetPause(bool _Value)
	{
		Pause_ = _Value;
	}
	void PauseOn()
	{
		Pause_ = true;
	}
	void PauseOff()
	{
		Pause_ = false;
	}
	void PauseSwitch()
	{
		Pause_ = !Pause_;
	}
	void CameraEffectOn()
	{
		IsCameraEffect_ = true;
	}
	void CameraEffectOff()
	{
		IsCameraEffect_ = false;
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
	unsigned int		Alpha_;
	bool				Pause_;
	bool				IsCameraEffect_;

	//=========================Animation========================
public: 
	void CreateAnimation(const std::string& _Image, const std::string& _Name, int _StartIndex, int _EndIndex, float _InterTime, bool _Loop = true);
	void CreateFolderAnimation(const std::string& _Image, const std::string& _Name, int _StartIndex, int _EndIndex, float _InterTime, bool _Loop = true);
	void CreateFolderAnimationTimeKey(const std::string& _Image, const std::string& _Name, int _TimeScaleKey, int _StartIndex, int _EndIndex, float _InterTime, bool _Loop = true);
	void ChangeAnimation(const std::string& _Name);
	bool IsEndAnimation();
	bool IsAnimationName(const std::string& _Name);

protected:

private:
	class FrameAnimation : public GameEngineNameObject
	{
	public:
		FrameAnimation()
			: Renderer_(nullptr)
			, Image_(nullptr)
			, FolderImage_(nullptr)
			, CurrentFrame_(-1)
			, StartFrame_(-1)
			, EndFrame_(-1)
			, TimeKey_(0)
			, CurrentInterTime_(0.1f)
			, InterTime_(0.1f)
			, Loop_(true)
			, IsEnd_(false)
		{}
		
		void Update();
		void Reset()
		{
			IsEnd_ = false;
			CurrentFrame_ = StartFrame_;
			CurrentInterTime_ = InterTime_;
		}

		inline int WorldCurrentFrame() const
		{
			return CurrentFrame_;
		}
		inline int WorldStartFrame() const
		{
			return StartFrame_;
		}
		inline int WorldEndFrame() const
		{
			return EndFrame_;
		}
		inline int LocalCurrentFrame() const
		{
			return CurrentFrame_ - StartFrame_;
		}
	private:
		friend GameEngineRenderer;
		//friend std::map<std::string, FrameAnimation>;

		GameEngineRenderer*		Renderer_;
		GameEngineImage*		Image_;
		GameEngineFolderImage*	FolderImage_;
		int						CurrentFrame_;
		int						StartFrame_;
		int						EndFrame_;
		int						TimeKey_;
		float					CurrentInterTime_;
		float					InterTime_;
		bool					Loop_ = false;
		bool					IsEnd_;
	};

	std::map<std::string, FrameAnimation> Animations_;
	FrameAnimation* CurrentAnimation_;

public:
	const FrameAnimation* FindAnimation(const std::string& _Name);
	inline const FrameAnimation* CurrentAnimation()
	{
		return CurrentAnimation_;
	}
};

