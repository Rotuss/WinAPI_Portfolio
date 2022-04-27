#include "GameEngineFont.h"
#include "GameEngine.h"
#include <GameEngineBase/GameEnginePath.h>
#include <GameEngineBase/GameEngineString.h>
#include <Windows.h>
#include <WinUser.h>

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

void GameEngineFont::Draw(const std::string& _Text, float4 _Postion, int _TextColor, float _Size, float _Weight)
{
	hFont_ = CreateFontA(static_cast<int>(_Size), 0, 0, 0, static_cast<int>(_Weight), 0, 0, 0, JOHAB_CHARSET, 0, 0, 0, VARIABLE_PITCH || FF_ROMAN, FontName_.c_str());

	if (nullptr == hFont_)
	{
		MsgBoxAssert("����� �� ���� ��Ʈ�Դϴ�.");
	}

	std::wstring WText;
	GameEngineString::AnsiToUnicode(_Text, WText);

	//��Ʈ�� �����Լ�
	SetTextColor(GameEngine::BackBufferDC(), _TextColor);
	SetBkMode(GameEngine::BackBufferDC(), 1);
	oldFont_ = (HFONT)SelectObject(GameEngine::BackBufferDC(), hFont_);
	
	RECT NewRect = { _Postion.ix(), _Postion.iy(), 1280, 720 };
	DrawTextW(GameEngine::BackBufferDC(), WText.c_str(), static_cast<int>(WText.size()), &NewRect, DT_LEFT);

	DeleteObject(hFont_);
	(HFONT)SelectObject(GameEngine::BackBufferDC(), oldFont_);
}

void GameEngineFont::Draw(const std::wstring& _Text, float4 _Postion, int _TextColor, float _Size, float _Weight)
{
	hFont_ = CreateFontA(static_cast<int>(_Size), 0, 0, 0, static_cast<int>(_Weight), 0, 0, 0, JOHAB_CHARSET, 0, 0, 0, VARIABLE_PITCH || FF_ROMAN, FontName_.c_str());

	if (nullptr == hFont_)
	{
		MsgBoxAssert("����� �� ���� ��Ʈ�Դϴ�.");
	}

	//��Ʈ�� �����Լ�
	SetTextColor(GameEngine::BackBufferDC(), _TextColor);
	SetBkMode(GameEngine::BackBufferDC(), 1);
	oldFont_ = (HFONT)SelectObject(GameEngine::BackBufferDC(), hFont_);
	
	RECT NewRect = { _Postion.ix(), _Postion.iy(), 1280, 720 };
	DrawTextW(GameEngine::BackBufferDC(), _Text.c_str(), static_cast<int>(_Text.size()), &NewRect, DT_LEFT);

	DeleteObject(hFont_);
	(HFONT)SelectObject(GameEngine::BackBufferDC(), oldFont_);
}
