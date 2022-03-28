#pragma once
#include "GameEngineBase/GameEngineNameObject.h"
#include <map>
#include <list>

// ���� : 
class GameEngine;
class GameEngineActor;
class GameEngineLevel : public GameEngineNameObject
{
	// GameEngineLevel�� GameEngine���׸�ŭ�� ��� ���� ����(friend) - �̷��� �� ����? => Loading�� �� �� ȣ��Ǹ� �ȵǱ� ����
	friend GameEngine;
public:
	// constrcuter destructer
	GameEngineLevel();
	virtual ~GameEngineLevel();

	// delete Function
	GameEngineLevel(const GameEngineLevel& _Other) = delete;
	GameEngineLevel(GameEngineLevel&& _Other) noexcept = delete;
	GameEngineLevel& operator=(const GameEngineLevel& _Other) = delete;
	GameEngineLevel& operator=(GameEngineLevel&& _Other) noexcept = delete;

protected:
	// �����Լ�
	// ��������鼭 ���ҽ��� ���͸� ���� �� ���
	virtual void Loading() = 0;
	// �� ������ ���� ������ �� �ؾ��� ���� ����
	virtual void Update() = 0;
	// ���緹������ ���������� ������ �� ���緹���� �����ϴ� �Լ�
	virtual void SceneChangeStart() {}
	// ���緹������ ���������� ������ �� ���������� �����ϴ� �Լ�
	virtual void SceneChangeEnd() {}

	template<typename ActorType>
	ActorType* CreateActor(const std::string& _Name, int _Order)
	{
		ActorType* NewActor = new ActorType();
		NewActor->SetName(_Name);
		NewActor->SetLevel(this);

		// _Order : Actor���� ���ư��� ������ �ǹ�. ���� ������ �׷���
		// AllActor_[_Order] : insert�� find�� ���ÿ� ó��. �Ʒ� �ּ��� ���� ����
		/*
		std::map<int, std::list<GameEngineActor*>>::iterator FindGroup = AllActor_.find(_Order);

		if (FindGroup == AllActor_.end())
		{
			AllActor_.insert(std::make_pair(_Order, std::list<GameEngineActor*>()));
			FindGroup = AllActor_.find(_Order)
		}
		*/
		// ���۷����� �޾� push_back
		std::list<GameEngineActor*>& Group = AllActor_[_Order];
		Group.push_back(NewActor);

		return nullptr;
	}

private:
	// std::list���� std::vector�� �����ϴ� ���� �� ���ٰ� ����(���� ������ ���� �߻����� ���� �� ���� ����). ������ ����� ���⿡ ���� ��
	// map���� ���� 0�� 1�� ���� �ִ��� Ȯ�� ������ ������ָ� ��. �� ������ �����ֱ� ����
	// �׷� list�� �� ����? => �׳� list�� ����Ѱ� ���ϰ� �ͼ��ؼ�
	std::map<int, std::list<GameEngineActor*>> AllActor_;
	// �� �κ��� ����ϴ°� �־��� ��
	//std::map<std::string, std::list<GameEngineActor*>> AllActor_;

	void ActorUpdate();
	void ActorRender();
};

