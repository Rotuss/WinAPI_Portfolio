#pragma once
#include <GameEngineBase/GameEngineNameObject.h>
#include <GameEngineBase/GameEngineMath.h>
#include <map>
#include <list>
#include <vector>
#include <set>

// 설명 : 화면을 등장! 오브젝트 관리 방법(map과 list)
class GameEngineActor;
struct ChangeOrderItem
{
	// TargetObject을 ChangeOrder으로 바꿔라
	GameEngineActor* TargetObject;
	int ChangeOrder;
};

class GameEngine;
class GameEngineActor;
class GameEngineCollision;
class GameEngineRenderer;
class GameEngineLevel : public GameEngineNameObject
{
	// GameEngineLevel은 GameEngine한테만큼은 모든 것을 공개(friend) - 이렇게 한 이유? => Loading은 두 번 호출되면 안되기 때문
	friend GameEngine;
	friend GameEngineActor;
	friend GameEngineCollision;
	friend GameEngineRenderer;

public:
	// constrcuter destructer
	GameEngineLevel();
	virtual ~GameEngineLevel();

	// delete Function
	GameEngineLevel(const GameEngineLevel& _Other) = delete;
	GameEngineLevel(GameEngineLevel&& _Other) noexcept = delete;
	GameEngineLevel& operator=(const GameEngineLevel& _Other) = delete;
	GameEngineLevel& operator=(GameEngineLevel&& _Other) noexcept = delete;

	template<typename ActorType>
	ActorType* CreateActor(int _Order = 0, const std::string& _Name = "")
	{
		ActorType* NewActor = new ActorType();
		GameEngineActor* StartActor = NewActor;
		NewActor->GameEngineUpdateObject::SetOrder(_Order);
		NewActor->SetName(_Name);
		NewActor->SetLevel(this);
		StartActor->Start();
		// _Order : Actor들이 돌아가는 순서를 의미. 낮은 순으로 그려짐
		// AllActor_[_Order] : insert와 find를 동시에 처리. 아래 주석과 같은 내용
		/*
		std::map<int, std::list<GameEngineActor*>>::iterator FindGroup = AllActor_.find(_Order);

		if (FindGroup == AllActor_.end())
		{
			AllActor_.insert(std::make_pair(_Order, std::list<GameEngineActor*>()));
			FindGroup = AllActor_.find(_Order)
		}
		*/
		// 래퍼런스로 받아 push_back
		std::list<GameEngineActor*>& Group = AllActor_[_Order];
		Group.push_back(NewActor);

		return NewActor;
	}

	inline float4 GetCameraPos()
	{
		return CameraPos_;
	}

	inline void SetCameraPos(const float4& _Value)
	{
		CameraPos_ = _Value;
	}

	inline void MoveCameraPos(const float4& _Value)
	{
		CameraPos_ + _Value;
	}

	inline void ResetOn()
	{
		IsReset_ = true;
	}
	
	static void IsDebugModeOn()
	{
		IsDebug_ = true;
	}

	static void IsDebugModeOff()
	{
		IsDebug_ = false;
	}

	static void IsDebugModeSwitch()
	{
		IsDebug_ = !IsDebug_;
	}
	
	//template<typename ConvertType>
	//ConvertType* FindActor(const std::string& _Name)
	//{
	//	return dynamic_cast<ConvertType*>(FindActor(_Name));
	//}

	GameEngineActor* FindActor(const std::string& _Name);
	void RegistActor(const std::string& _Name, GameEngineActor* _Actor);

	// 해당 오더는 sort할 것
	void YSortOn(int _SortOrder)
	{
		IsYSort_.insert(_SortOrder);
	}

protected:
	// 시점함수
	// 만들어지면서 리소스나 액터를 만들 때 사용
	virtual void Loading() = 0;
	// 이 레벨이 현재 레벨일 때 해야할 일을 실행
	virtual void Update() = 0;
	// 현재레벨에서 다음레벨로 이전할 때 현재레벨이 실행하는 함수
	void ActorLevelChangeStart(GameEngineLevel* _PrevLevel);
	virtual void LevelChangeStart(GameEngineLevel* _PrevLevel) {}
	// 현재레벨에서 다음레벨로 이전할 때 이전레벨이 실행하는 함수
	void ActorLevelChangeEnd(GameEngineLevel* _NextLevel);
	virtual void LevelChangeEnd(GameEngineLevel* _NextLevel) {}

	void ObjectLevelMoveCheck(GameEngineLevel* _NextLevel);

	void Reset();

	virtual void UserResetEnd() {}

private:
	// std::list보다 std::vector로 관리하는 것이 더 좋다고 생각(삽입 삭제가 많이 발생하지 않을 것 같기 때문). 무엇을 만들건 여기에 전부 들어감
	// map으로 먼저 0번 1번 등이 있는지 확인 없으면 만들어주면 됨. 즉 순서를 정해주기 위함
	// 그럼 list를 한 이유? => 그냥 list로 사용한게 편하고 익숙해서
	std::map<int, std::list<GameEngineActor*>> AllActor_;
	std::map<std::string, GameEngineActor*> RegistActor_;
	std::vector<ChangeOrderItem> ChangeOrderList;
	// 이 부분을 사용하는건 최악의 수
	//std::map<std::string, std::list<GameEngineActor*>> AllActor_;

	float4 CameraPos_;
	
	void ActorUpdate();
	void ActorRender();
	void CollisionDebugRender();
	void ActorRelease();

	std::map<int, std::list<GameEngineRenderer*>> AllRenderer_;
	// list로 하는 이유 : 충돌하여 Actor가 죽을 경우를 생각하면 됨
	// 삭제는 Actor가 하지만, 실제 사용은 Level. 따라서 여기서 함부로 GameEngineCollision*을 delete하는 일이 있으면 안됨
	std::map<std::string, std::list<GameEngineCollision*>> AllCollision_;

	// 존재유무
	std::set<int> IsYSort_;
	
	void ChangeUpdateOrder(GameEngineActor* _Actor, int _NewOrder);
	
	void AddRenderer(GameEngineRenderer* _Renderer);
	void ChangeRenderOrder(GameEngineRenderer* _Renderer, int _NewOrder);
	void AddCollision(const std::string& _GroupName, GameEngineCollision* _Collision);

	static bool IsDebug_;
	bool IsReset_;
};

