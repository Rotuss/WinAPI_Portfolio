#include "GameEngineLevel.h"
#include "GameEngineActor.h"
#include "GameEngineCollision.h"
#include "GameEngineRenderer.h"
#include <GameEngineBase/GameEngineDebug.h>

bool GameEngineLevel::IsDebug_ = false;

GameEngineLevel::GameEngineLevel()
	: CameraPos_(float4::ZERO)
{
}

GameEngineLevel::~GameEngineLevel()
{
	std::map<int, std::list<GameEngineActor*>>::iterator GroupStart = AllActor_.begin();
	std::map<int, std::list<GameEngineActor*>>::iterator GroupEnd = AllActor_.end();
	for (; GroupStart != GroupEnd; ++GroupStart)
	{
		std::list<GameEngineActor*>& Group = GroupStart->second;

		std::list<GameEngineActor*>::iterator StartActor = Group.begin();
		std::list<GameEngineActor*>::iterator EndActor = Group.end();

		for (; StartActor != EndActor; ++StartActor)
		{
			if (nullptr == (*StartActor))
			{
				continue;
			}
			delete (*StartActor);
			(*StartActor) = nullptr;
		}
	}
}

GameEngineActor* GameEngineLevel::FindActor(const std::string& _Name)
{
	std::map<std::string, GameEngineActor*>::iterator FindIter = RegistActor_.find(_Name);

	if (RegistActor_.end() == FindIter)
	{
		return nullptr;
	}
	return FindIter->second;
}

void GameEngineLevel::RegistActor(const std::string& _Name, GameEngineActor* _Actor)
{
	if (RegistActor_.end() != RegistActor_.find(_Name))
	{
		MsgBoxAssert("이미 존재하는 이름으로 또 등록하려고 했습니다.");
	}
	RegistActor_.insert(std::map<std::string, GameEngineActor*>::value_type(_Name, _Actor));
}

void GameEngineLevel::ActorLevelChangeStart(GameEngineLevel* _PrevLevel)
{
	std::map<int, std::list<GameEngineActor*>>::iterator GroupStart;
	std::map<int, std::list<GameEngineActor*>>::iterator GroupEnd;

	std::list<GameEngineActor*>::iterator StartActor;
	std::list<GameEngineActor*>::iterator EndActor;

	GroupStart = AllActor_.begin();
	GroupEnd = AllActor_.end();

	for (; GroupStart != GroupEnd; ++GroupStart)
	{
		std::list<GameEngineActor*>& Group = GroupStart->second;
		
		StartActor = Group.begin();
		EndActor = Group.end();

		for (; StartActor != EndActor; ++StartActor)
		{
			if (false == (*StartActor)->IsUpdate())
			{
				continue;
			}
			(*StartActor)->LevelChangeStart(_PrevLevel);
		}
	}
}

void GameEngineLevel::ActorLevelChangeEnd(GameEngineLevel* _NextLevel)
{
	std::map<int, std::list<GameEngineActor*>>::iterator GroupStart;
	std::map<int, std::list<GameEngineActor*>>::iterator GroupEnd;

	std::list<GameEngineActor*>::iterator StartActor;
	std::list<GameEngineActor*>::iterator EndActor;

	GroupStart = AllActor_.begin();
	GroupEnd = AllActor_.end();

	for (; GroupStart != GroupEnd; ++GroupStart)
	{
		std::list<GameEngineActor*>& Group = GroupStart->second;

		StartActor = Group.begin();
		EndActor = Group.end();

		for (; StartActor != EndActor; ++StartActor)
		{
			if (false == (*StartActor)->IsUpdate())
			{
				continue;
			}
			(*StartActor)->LevelChangeEnd(_NextLevel);
		}
	}
}

void GameEngineLevel::ObjectLevelMoveCheck(GameEngineLevel* _NextLevel)
{
	{
		std::map<int, std::list<GameEngineRenderer*>>::iterator GroupStart = AllRenderer_.begin();
		std::map<int, std::list<GameEngineRenderer*>>::iterator GroupEnd = AllRenderer_.end();

		std::list<GameEngineRenderer*>::iterator StartRenderer;
		std::list<GameEngineRenderer*>::iterator EndRenderer;

		for (; GroupStart != GroupEnd; ++GroupStart)
		{
			std::list<GameEngineRenderer*>& Group = GroupStart->second;

			StartRenderer = Group.begin();
			EndRenderer = Group.end();

			for (; StartRenderer != EndRenderer; )
			{
				if (false == (*StartRenderer)->GetActor()->NextLevelOn_)
				{
					++StartRenderer;
					continue;
				}
				GameEngineRenderer* Object = *StartRenderer;
				_NextLevel->AllRenderer_[Object->GetOrder()].push_back(Object);
				
				StartRenderer = Group.erase(StartRenderer);
			}
		}
	}
	// 콜리전은 레벨도 관리하고 있으므로 확인
	{
		std::map<std::string, std::list<GameEngineCollision*>>::iterator GroupStart = AllCollision_.begin();
		std::map<std::string, std::list<GameEngineCollision*>>::iterator GroupEnd = AllCollision_.end();

		std::list<GameEngineCollision*>::iterator StartCollision;
		std::list<GameEngineCollision*>::iterator EndCollision;

		for (; GroupStart != GroupEnd; ++GroupStart)
		{
			std::list<GameEngineCollision*>& Group = GroupStart->second;

			StartCollision = Group.begin();
			EndCollision = Group.end();

			for (; StartCollision != EndCollision; )
			{
				if (false == (*StartCollision)->GetActor()->NextLevelOn_)
				{
					++StartCollision;
					continue;
				}
				GameEngineCollision* Object = *StartCollision;
				_NextLevel->AllCollision_[Object->CollisionName_].push_back(Object);
				
				StartCollision = Group.erase(StartCollision);
			}
		}
	}
	// 액터 삭제
	{
		std::map<int, std::list<GameEngineActor*>>::iterator GroupStart;
		std::map<int, std::list<GameEngineActor*>>::iterator GroupEnd;

		std::list<GameEngineActor*>::iterator StartActor;
		std::list<GameEngineActor*>::iterator EndActor;

		GroupStart = AllActor_.begin();
		GroupEnd = AllActor_.end();

		for (; GroupStart != GroupEnd; ++GroupStart)
		{
			std::list<GameEngineActor*>& Group = GroupStart->second;

			StartActor = Group.begin();
			EndActor = Group.end();

			for (; StartActor != EndActor; )
			{
				if (true == (*StartActor)->NextLevelOn_)
				{
					// 이 부분에서 옮겨감
					GameEngineActor* Object = *StartActor;
					Object->SetLevel(_NextLevel);
					Object->NextLevelOff();
					_NextLevel->AllActor_[Object->GetOrder()].push_back(Object);

					StartActor = Group.erase(StartActor);
					continue;
				}
				++StartActor;
			}
		}
	}
}

void GameEngineLevel::ActorUpdate()
{
	std::map<int, std::list<GameEngineActor*>>::iterator GroupStart;
	std::map<int, std::list<GameEngineActor*>>::iterator GroupEnd;

	std::list<GameEngineActor*>::iterator StartActor;
	std::list<GameEngineActor*>::iterator EndActor;

	GroupStart = AllActor_.begin();
	GroupEnd = AllActor_.end();

	for (; GroupStart != GroupEnd; ++GroupStart)
	{
		std::list<GameEngineActor*>& Group = GroupStart->second;

		StartActor = Group.begin();
		EndActor = Group.end();

		for (; StartActor != EndActor; ++StartActor)
		{
			(*StartActor)->ReleaseUpdate();
			(*StartActor)->AddAccTime(GameEngineTime::GetDeltaTime());
			if (false == (*StartActor)->IsUpdate())
			{
				continue;
			}
			(*StartActor)->Update();
		}
	}
	// 체인지 오더 단계 ( 장점 : 업데이트에 영향을 안 줌, 단점 : 메모리를 좀 더 씀)
	for (size_t i = 0; i < ChangeOrderList.size(); ++i)
	{
		ChangeOrderItem& Data = ChangeOrderList[i];
		AllActor_[Data.TargetObject->GetOrder()].remove(Data.TargetObject);
		Data.TargetObject->GameEngineUpdateObject::SetOrder(Data.ChangeOrder);
		AllActor_[Data.TargetObject->GetOrder()].push_back(Data.TargetObject);
	}
	ChangeOrderList.clear();
}

void GameEngineLevel::ActorRender()
{
	// 렌더러 렌더
	{
		std::map<int, std::list<GameEngineRenderer*>>::iterator GroupStart = AllRenderer_.begin();
		std::map<int, std::list<GameEngineRenderer*>>::iterator GroupEnd = AllRenderer_.end();

		std::list<GameEngineRenderer*>::iterator StartRenderer;
		std::list<GameEngineRenderer*>::iterator EndRenderer;

		for (; GroupStart != GroupEnd; ++GroupStart)
		{
			std::list<GameEngineRenderer*>& Group = GroupStart->second;

			StartRenderer = Group.begin();
			EndRenderer = Group.end();

			for (; StartRenderer != EndRenderer; ++StartRenderer)
			{
				if (false == (*StartRenderer)->IsUpdate())
				{
					continue;
				}
				(*StartRenderer)->Render();
			}
		}
	}
	{
		std::map<int, std::list<GameEngineActor*>>::iterator GroupStart;
		std::map<int, std::list<GameEngineActor*>>::iterator GroupEnd;

		std::list<GameEngineActor*>::iterator StartActor;
		std::list<GameEngineActor*>::iterator EndActor;

		GroupStart = AllActor_.begin();
		GroupEnd = AllActor_.end();

		for (; GroupStart != GroupEnd; ++GroupStart)
		{
			std::list<GameEngineActor*>& Group = GroupStart->second;
			/*
			StartActor = Group.begin();
			EndActor = Group.end();

			for (; StartActor != EndActor; ++StartActor)
			{
				if (false == (*StartActor)->IsUpdate())
				{
					continue;
				}
				(*StartActor)->Rendering();
			}
			*/
			StartActor = Group.begin();
			EndActor = Group.end();

			for (; StartActor != EndActor; ++StartActor)
			{
				if (false == (*StartActor)->IsUpdate())
				{
					continue;
				}
				(*StartActor)->Render();
			}
		}
	}
}

void GameEngineLevel::CollisionDebugRender()
{
	if (false == IsDebug_)
	{
		return;
	}
	
	std::map<std::string, std::list<GameEngineCollision*>>::iterator GroupStart = AllCollision_.begin();
	std::map<std::string, std::list<GameEngineCollision*>>::iterator GroupEnd = AllCollision_.end();

	std::list<GameEngineCollision*>::iterator StartCollision;
	std::list<GameEngineCollision*>::iterator EndCollision;

	for (; GroupStart != GroupEnd; ++GroupStart)
	{
		std::list<GameEngineCollision*>& Group = GroupStart->second;
		
		StartCollision = Group.begin();
		EndCollision = Group.end();

		for (; StartCollision != EndCollision; ++StartCollision)
		{
			if (false == (*StartCollision)->IsUpdate())
			{
				continue;
			}
			(*StartCollision)->DebugRender();
		}
	}
}

void GameEngineLevel::ActorRelease()
{
	{
		std::map<int, std::list<GameEngineRenderer*>>::iterator GroupStart = AllRenderer_.begin();
		std::map<int, std::list<GameEngineRenderer*>>::iterator GroupEnd = AllRenderer_.end();

		std::list<GameEngineRenderer*>::iterator StartRenderer;
		std::list<GameEngineRenderer*>::iterator EndRenderer;

		for (; GroupStart != GroupEnd; ++GroupStart)
		{
			std::list<GameEngineRenderer*>& Group = GroupStart->second;

			StartRenderer = Group.begin();
			EndRenderer = Group.end();

			for (; StartRenderer != EndRenderer; )
			{
				if (false == (*StartRenderer)->IsDeath())
				{
					++StartRenderer;
					continue;
				}
				StartRenderer = Group.erase(StartRenderer);
			}
		}
	}
	// 콜리전은 레벨도 관리하고 있으므로 확인
	{
		std::map<std::string, std::list<GameEngineCollision*>>::iterator GroupStart = AllCollision_.begin();
		std::map<std::string, std::list<GameEngineCollision*>>::iterator GroupEnd = AllCollision_.end();

		std::list<GameEngineCollision*>::iterator StartCollision;
		std::list<GameEngineCollision*>::iterator EndCollision;

		for (; GroupStart != GroupEnd; ++GroupStart)
		{
			std::list<GameEngineCollision*>& Group = GroupStart->second;

			StartCollision = Group.begin();
			EndCollision = Group.end();

			for (; StartCollision != EndCollision; )
			{
				if (false == (*StartCollision)->IsDeath())
				{
					++StartCollision;
					continue;
				}
				StartCollision = Group.erase(StartCollision);
			}
		}
	}
	// 액터 삭제
	{
		std::map<int, std::list<GameEngineActor*>>::iterator GroupStart;
		std::map<int, std::list<GameEngineActor*>>::iterator GroupEnd;

		std::list<GameEngineActor*>::iterator StartActor;
		std::list<GameEngineActor*>::iterator EndActor;

		GroupStart = AllActor_.begin();
		GroupEnd = AllActor_.end();

		for (; GroupStart != GroupEnd; ++GroupStart)
		{
			std::list<GameEngineActor*>& Group = GroupStart->second;

			StartActor = Group.begin();
			EndActor = Group.end();

			for (; StartActor != EndActor; )
			{
				if (true == (*StartActor)->IsDeath())
				{
					delete (*StartActor);
					StartActor = Group.erase(StartActor);
					continue;
				}
				// 삭제가 안됐다면 콜리전이나 렌더러를 확인해 봄
				(*StartActor)->Release();
				++StartActor;
			}
		}
	}
}

void GameEngineLevel::ChangeUpdateOrder(GameEngineActor* _Actor, int _NewOrder)
{
	if (_Actor->GetOrder() == _NewOrder)
	{
		return;
	}
	ChangeOrderList.push_back({ _Actor , _NewOrder });
}

void GameEngineLevel::AddRenderer(GameEngineRenderer* _Renderer)
{
	AllRenderer_[_Renderer->GetOrder()].push_back(_Renderer);
}

void GameEngineLevel::ChangeRenderOrder(GameEngineRenderer* _Renderer, int _NewOrder)
{
	if (_Renderer->GetOrder() == _NewOrder)
	{
		return;
	}
	AllRenderer_[_Renderer->GetOrder()].remove(_Renderer);
	_Renderer->GameEngineUpdateObject::SetOrder(_NewOrder);
	AllRenderer_[_Renderer->GetOrder()].push_back(_Renderer);
}

void GameEngineLevel::AddCollision(const std::string& _GroupName, GameEngineCollision* _Collision)
{
	_Collision->CollisionName_ = _GroupName;
	// 찾아서 없으면 만듦
	AllCollision_[_GroupName].push_back(_Collision);
}