#pragma once
#include <string>
#include <algorithm>

// 설명 : 
class GameEngineString
{
public:
	static void ToUpper(std::string& _Text)
	{
		for (size_t i = 0; i < _Text.size(); i++)
		{
			_Text[i] = std::toupper(_Text[i]);
		}
		// String의 처음부터 끝까지 시작부터 모두 대문자로 변환
		//std::transform(_Text.begin(), _Text.end(), _Text.begin(), std::toupper);
	}

	static std::string ToUpperReturn(const std::string& _Text)
	{
		std::string NewText = _Text;
		for (size_t i = 0; i < NewText.size(); i++)
		{
			NewText[i] = std::toupper(NewText[i]);
		}
		//std::transform(NewText.begin(), NewText.end(), NewText.begin(), std::toupper);
		return NewText;
	}

protected:

private:
	// constrcuter destructer
	GameEngineString();
	~GameEngineString();

	// delete Function
	GameEngineString(const GameEngineString& _Other) = delete;
	GameEngineString(GameEngineString&& _Other) noexcept = delete;
	GameEngineString& operator=(const GameEngineString& _Other) = delete;
	GameEngineString& operator=(GameEngineString&& _Other) noexcept = delete;
};

