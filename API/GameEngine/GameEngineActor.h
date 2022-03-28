#pragma once
#include <GameEngineBase/GameEngineNameObject.h>
#include <GameEngineBase/GameEngineMath.h>
// ���� : 
class GameEngineLevel;
class GameEngineActor : public GameEngineNameObject
{
public:
	// �������Ը� ���� ������ ������ �ο�
	friend GameEngineLevel;
	
	// constrcuter destructer
	GameEngineActor();
	virtual ~GameEngineActor();

	// delete Function
	GameEngineActor(const GameEngineActor& _Other) = delete;
	GameEngineActor(GameEngineActor&& _Other) noexcept = delete;
	GameEngineActor& operator=(const GameEngineActor& _Other) = delete;
	GameEngineActor& operator=(GameEngineActor&& _Other) noexcept = delete;

protected:
	// �����Լ����� protected��

	// ������ �� ���𰡸� �ϰ� ������ �����ڿ����� ����� ���� �κе��� ó��
	virtual void Start() = 0;
	// ���������� ������ ����� �� ȣ��
	virtual void Update() {}
	// ���������� ������ ����� �� ȣ��
	virtual void Render() {}

private:
	GameEngineLevel* Level_;
	float4 Position_;
	float4 Scale_;

	// ���� ������� ����
	inline void SetLevel(GameEngineLevel* _Level)
	{
		Level_ = _Level;
	}
};

