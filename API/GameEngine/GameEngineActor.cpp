#include "GameEngineActor.h"
#include "GameEngineRenderer.h"
#include "GameEngineCollision.h"
#include "GameEngineLevel.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngine.h>

GameEngineActor::GameEngineActor()
	:Level_(nullptr)
{
}

GameEngineActor::~GameEngineActor()
{
	{
		std::list<GameEngineRenderer*>::iterator StartIter = RenderList_.begin();
		std::list<GameEngineRenderer*>::iterator EndIter = RenderList_.end();

		for (; StartIter != EndIter; ++StartIter)
		{
			if (nullptr == (*StartIter))
			{
				continue;
			}
			delete (*StartIter);
			(*StartIter) = nullptr;
		}
	}
	{
		std::list<GameEngineCollision*>::iterator StartIter = CollisionList_.begin();
		std::list<GameEngineCollision*>::iterator EndIter = CollisionList_.end();

		for (; StartIter != EndIter; ++StartIter)
		{
			if (nullptr == (*StartIter))
			{
				continue;
			}
			delete (*StartIter);
			(*StartIter) = nullptr;
		}
	}
}

void GameEngineActor::SetOrder(int _Order)
{
	if (nullptr == GetLevel())
	{
		MsgBoxAssert("레벨이 세팅되지 않았습니다.");
	}

	if (_Order == GetOrder())
	{
		return;
	}
	GetLevel()->ChangeUpdateOrder(this, _Order);
}

void GameEngineActor::Release()
{
	{
		std::list<GameEngineRenderer*>::iterator StartIter = RenderList_.begin();
		std::list<GameEngineRenderer*>::iterator EndIter = RenderList_.end();

		for (; StartIter != EndIter; )
		{
			if (false == (*StartIter)->IsDeath())
			{
				++StartIter;
				continue;
			}
			delete (*StartIter);
			(*StartIter) = nullptr;
			StartIter = RenderList_.erase(StartIter);
		}
	}
	{
		std::list<GameEngineCollision*>::iterator StartIter = CollisionList_.begin();
		std::list<GameEngineCollision*>::iterator EndIter = CollisionList_.end();

		for (; StartIter != EndIter; )
		{
			if (false == (*StartIter)->IsDeath())
			{
				++StartIter;
				continue;
			}
			delete (*StartIter);
			(*StartIter) = nullptr;
			StartIter = CollisionList_.erase(StartIter);
		}
	}
}

void GameEngineActor::DebugRectRender()
{
	GameEngineRect DebugRect(Position_, Scale_);
	
	Rectangle(GameEngine::BackBufferDC(), DebugRect.CenterLeft(), DebugRect.CenterTop(), DebugRect.CenterRight(), DebugRect.CenterBot());
}

void GameEngineActor::LevelRegist(std::string _RegistName)
{
	if (_RegistName == "")
	{
		GetLevel()->RegistActor(GetNameConstPtr(), this);
		return;
	}
	GetLevel()->RegistActor(_RegistName, this);
}

GameEngineRenderer* GameEngineActor::CreateRenderer(int _Order, RenderPivot _PivotType, const float4& _PivotPos)
{
	GameEngineRenderer* NewRenderer = new GameEngineRenderer();

	NewRenderer->SetActor(this);
	if (_Order != static_cast<int>(EngineMax::RENDERORDERMAX))
	{
		// GameEngineUpdateObject:: 를 붙이지 않으면 렌더링 2배..
		NewRenderer->GameEngineUpdateObject::SetOrder(_Order);
	}
	else
	{
		NewRenderer->GameEngineUpdateObject::SetOrder(GetOrder());
	}
	NewRenderer->SetPivotType(_PivotType);
	NewRenderer->SetPivot(_PivotPos);

	GetLevel()->AddRenderer(NewRenderer);
	RenderList_.push_back(NewRenderer);
	return NewRenderer;
}

GameEngineRenderer* GameEngineActor::CreateRenderer(const std::string& _ImageName, int _Order, RenderPivot _PivotType /*= RenderPivot::CENTER*/, const float4& _PivotPos /*= { 0, 0 }*/)
{
	GameEngineRenderer* NewRenderer = new GameEngineRenderer();

	NewRenderer->SetActor(this);
	if (_Order != static_cast<int>(EngineMax::RENDERORDERMAX))
	{
		NewRenderer->GameEngineUpdateObject::SetOrder(_Order);
	}
	else
	{
		NewRenderer->GameEngineUpdateObject::SetOrder(GetOrder());
	}
	NewRenderer->SetImage(_ImageName);
	NewRenderer->SetPivotType(_PivotType);
	NewRenderer->SetPivot(_PivotPos);

	GetLevel()->AddRenderer(NewRenderer);
	RenderList_.push_back(NewRenderer);
	return NewRenderer;
}

GameEngineRenderer* GameEngineActor::CreateRendererToScale(const std::string& _ImageName, const float4& _Scale, int _Order, RenderPivot _PivotType, const float4& _PivotPos)
{
	GameEngineRenderer* NewRenderer = new GameEngineRenderer();

	NewRenderer->SetActor(this);
	if (_Order != static_cast<int>(EngineMax::RENDERORDERMAX))
	{
		NewRenderer->GameEngineUpdateObject::SetOrder(_Order);
	}
	else
	{
		NewRenderer->GameEngineUpdateObject::SetOrder(GetOrder());
	}
	NewRenderer->SetImage(_ImageName);
	NewRenderer->SetScale(_Scale);
	NewRenderer->SetPivotType(_PivotType);
	NewRenderer->SetPivot(_PivotPos);

	GetLevel()->AddRenderer(NewRenderer);
	RenderList_.push_back(NewRenderer);
	
	return NewRenderer;
}
/*
void GameEngineActor::Rendering()
{
	StartRenderIter = RenderList_.begin();
	EndRenderIter = RenderList_.end();

	for (; StartRenderIter != EndRenderIter; ++StartRenderIter)
	{
		if (false == (*StartRenderIter)->IsUpdate())
		{
			continue;
		}
		(*StartRenderIter)->Render();
	}
}
*/
GameEngineCollision* GameEngineActor::CreateCollision(const std::string& _GroupName, float4 _Scale, float4 _Pivot)
{
	GameEngineCollision* NewCollision = new GameEngineCollision();
	NewCollision->SetActor(this);
	NewCollision->SetScale(_Scale);
	NewCollision->SetPivot(_Pivot);
	GetLevel()->AddCollision(_GroupName, NewCollision);
	CollisionList_.push_back(NewCollision);
	return NewCollision;
}
