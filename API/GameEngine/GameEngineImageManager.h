#pragma once
#include <map>
#include <string>
#include <GameEngineBase/GameEngineMath.h>
#include "GameEngineImage.h"

// �⺻������ ���ҽ��� �׳� ��� ���������� �����Ǵ� ���ҽ����� ���� �̸��� �����Ѵ� ���� ���
// ���� : 
class GameEngineImageManager
{
public:
	GameEngineImage* Find(const std::string& _Name);
	
	// �̹����� ������ִ� �Լ�
	GameEngineImage* Create(const std::string& _Name, const float4& _Scale);
	GameEngineImage* Create(const std::string& _Name, HDC _DC);

	GameEngineImage* Load(const std::string& _Path);
	GameEngineImage* Load(const std::string& _Path, const std::string& _Name);

	static GameEngineImageManager* GetInst()
	{
		return Inst_;
	}

	static void Destroy()
	{
		if (nullptr == Inst_)
		{
			return;
		}
		delete Inst_;
		Inst_ = nullptr;
	}

protected:

private:
	// �̱����̹Ƿ� �����ڸ� private
	// constrcuter destructer
	GameEngineImageManager();
	~GameEngineImageManager();

	// delete Function
	GameEngineImageManager(const GameEngineImageManager& _Other) = delete;
	GameEngineImageManager(GameEngineImageManager&& _Other) noexcept = delete;
	GameEngineImageManager& operator=(const GameEngineImageManager& _Other) = delete;
	GameEngineImageManager& operator=(GameEngineImageManager&& _Other) noexcept = delete;
	
	std::map<std::string, GameEngineImage*> AllRes;

	static GameEngineImageManager* Inst_;
};

