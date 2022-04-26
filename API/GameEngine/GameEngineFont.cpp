#include "GameEngineFont.h"
#include "GameEngine.h"
#include <GameEngineBase/GameEnginePath.h>
#include <GameEngineBase/GameEngineString.h>
#include <Windows.h>

GameEngineFont::GameEngineFont()
{
}

GameEngineFont::~GameEngineFont()
{
}

// window system font ������ ������ ���ϸ����� ����
bool GameEngineFont::Load(const std::string& _Path)
{
	//LPCSTR FontSrc = "../Resources/UI/KO.ttf";
	if (0 == AddFontResourceA(_Path.c_str()))
	{
		MsgBoxAssert("����� �� ���� ��Ʈ�Դϴ�.");
	}

	GameEnginePath FilePath(_Path);

	FontName_ = FilePath.GetFileName();

	setlocale(LC_ALL, "");

	return true;
}

void GameEngineFont::Draw(const std::string& _Text, float4 _Postion, float _Size, float _Weight)
{
	hFont_ = CreateFontA(static_cast<int>(_Size), 0, 0, 0, static_cast<int>(_Weight), 0, 0, 0, JOHAB_CHARSET, 0, 0, 0, VARIABLE_PITCH || FF_ROMAN, FontName_.c_str());

	if (nullptr == hFont_)
	{
		MsgBoxAssert("����� �� ���� ��Ʈ�Դϴ�.");
	}

	std::wstring WText;
	GameEngineString::AnsiToUnicode(_Text, WText);

	oldFont_ = (HFONT)SelectObject(GameEngine::BackBufferDC(), hFont_);
	TextOutW(GameEngine::BackBufferDC(), _Postion.ix(), _Postion.iy(), WText.c_str(), static_cast<int>(WText.size()));
	DeleteObject(hFont_);
	(HFONT)SelectObject(GameEngine::BackBufferDC(), oldFont_);
}
