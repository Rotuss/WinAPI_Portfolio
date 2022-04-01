#include "GameEngineImage.h"
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngineBase/GameEngineWindow.h>

// 이미지 라이브러리가 필요
#pragma comment(lib,"msimg32.lib")

GameEngineImage::GameEngineImage()
	: ImageDC_(nullptr)
{
}

GameEngineImage::~GameEngineImage()
{
	// window에서 할당한 것들은 릭으로 체크가 안되지만 지워주는 것이 깔끔
	// window에게 할당한 것이므로 window의 함수를 이용하여 제거
	if (nullptr != ImageDC_)
	{
		DeleteObject(ImageDC_);
		ImageDC_ = nullptr;
	}

	if (nullptr != BitMap_)
	{
		DeleteObject(BitMap_);
		BitMap_ = nullptr;
	}

	if (nullptr != OldBitMap_)
	{
		DeleteObject(OldBitMap_);
		OldBitMap_ = nullptr;
	}
}

bool GameEngineImage::Create(float4 _Scale)
{
	if (true == _Scale.IsZero2D())
	{
		MsgBoxAssert("크기가 0인 이미지를 제작하려고 했습니다.");
		return false;
	}
	
	// 먼저 이미지 크기만한 비트맵을 생성
	BitMap_ = CreateCompatibleBitmap(GameEngineWindow::GetHDC(), _Scale.ix(), _Scale.iy());
	// 비어있지 않은, 크기가 1인 HBITMAP 존재(OldBitMap)
	ImageDC_ = CreateCompatibleDC(nullptr);

	if (nullptr == ImageDC_)
	{
		MsgBoxAssert("ImageDC 생성에 실패했습니다.");
	}

	OldBitMap_ = (HBITMAP)SelectObject(ImageDC_, BitMap_);

	ImageScaleCheck();

	return true;
}

// 이미 만들어진 DC를 편입시키려는 것
bool GameEngineImage::Create(HDC _DC)
{
	ImageDC_ = _DC;
	ImageScaleCheck();

	return true;
}

void GameEngineImage::BitCopy(GameEngineImage* _Other)
{
	BitCopy(_Other, { 0, 0 }, { 0, 0 }, _Other->GetScale());
}

// 다른 이미지가 들어와서 복사
void GameEngineImage::BitCopy(GameEngineImage* _Other, const float4& _CopyPos, const float4& _OtherPivot, const float4& _OtherPivotScale)
{
	// 윈도우에서 지원해주는 일반적인 DC vs DC의 복사함수
	BitBlt(ImageDC_				// 여기에 복사
		, _CopyPos.ix()			// 내 이미지의 x
		, _CopyPos.iy()			// 내 이미지의 y에 복사
		, _OtherPivotScale.ix()	// 내 이미지의 x
		, _OtherPivotScale.iy()	// 내 이미지의 y 크기만큼
		, _Other->ImageDC_		// 복사하려는 대상
		, _OtherPivot.ix()		// 복사하려는 대상의 시작점 x
		, _OtherPivot.iy()		// 복사하려는 대상의 시작점 y
		, SRCCOPY);				// 복사하라는 명령
}

void GameEngineImage::ImageScaleCheck()
{
	// DC 내부에 박혀있는 BITMAP을 꺼내오는 함수
	HBITMAP CurrentBitMap = (HBITMAP)GetCurrentObject(ImageDC_, OBJ_BITMAP);
	GetObject(CurrentBitMap, sizeof(BITMAP), &Info_);
}
