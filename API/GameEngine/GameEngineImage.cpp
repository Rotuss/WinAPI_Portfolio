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

bool GameEngineImage::Load(const std::string& _Path)
{
	BitMap_ = static_cast<HBITMAP>(LoadImageA(nullptr, _Path.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE));
	
	if (nullptr == BitMap_)
	{
		MsgBoxAssertString(_Path + "이미지 로드에 실패했습니다. 확인해야 되는 문제 1. 경로가 제대로 되어있나요? 2. 디버깅은 제대로 확인했나요?");
	}

	ImageDC_ = CreateCompatibleDC(nullptr);

	if (nullptr == ImageDC_)
	{
		MsgBoxAssert("ImageDC 생성에 실패했습니다.");
	}

	OldBitMap_ = (HBITMAP)SelectObject(ImageDC_, BitMap_);

	ImageScaleCheck();

	return true;
}

void GameEngineImage::BitCopy(GameEngineImage* _Other)
{
	BitCopy(_Other, { 0, 0 }, _Other->GetScale(), { 0, 0 });
}

void GameEngineImage::BitCopy(GameEngineImage* _Other, const float4& _CopyPos)
{
	BitCopy(_Other, _CopyPos, _Other->GetScale(), float4{ 0, 0 });
}

void GameEngineImage::BitCopyCenter(GameEngineImage* _Other, const float4& _CopyPos)
{
	BitCopy(_Other, _CopyPos - _Other->GetScale().Half(), _Other->GetScale(), float4{ 0, 0 });
}

void GameEngineImage::BitCopyCenterPivot(GameEngineImage* _Other, const float4& _CopyPos, const float4& _CopyPivot)
{
	BitCopy(_Other, _CopyPos - _Other->GetScale().Half() + _CopyPivot, _Other->GetScale(), float4{ 0, 0 });
}

void GameEngineImage::BitCopyBot(GameEngineImage* _Other, const float4& _CopyPos)
{
	float4 ImagePivot = _Other->GetScale().Half();
	ImagePivot.y = _Other->GetScale().y;
	
	BitCopy(_Other, _CopyPos - ImagePivot, _Other->GetScale(), float4{ 0, 0 });
}

void GameEngineImage::BitCopyBotPivot(GameEngineImage* _Other, const float4& _CopyPos, const float4& _CopyPivot)
{
	float4 ImagePivot = _Other->GetScale().Half();
	ImagePivot.y = _Other->GetScale().y;

	BitCopy(_Other, _CopyPos - ImagePivot + _CopyPivot, _Other->GetScale(), float4{ 0, 0 });
}

// 다른 이미지가 들어와서 복사
void GameEngineImage::BitCopy(GameEngineImage* _Other, const float4& _CopyPos, const float4& _CopyScale, const float4& _OtherPivot)
{
	// 윈도우에서 지원해주는 일반적인 DC vs DC의 복사함수
	BitBlt(ImageDC_				// 여기에 복사
		, _CopyPos.ix()			// 내 이미지의 x
		, _CopyPos.iy()			// 내 이미지의 y에 복사
		, _CopyScale.ix()	// 내 이미지의 x
		, _CopyScale.iy()	// 내 이미지의 y 크기만큼
		, _Other->ImageDC_		// 복사하려는 대상
		, _OtherPivot.ix()		// 복사하려는 대상의 시작점 x
		, _OtherPivot.iy()		// 복사하려는 대상의 시작점 y
		, SRCCOPY);				// 복사하라는 명령
}

void GameEngineImage::TransCopyCenter(GameEngineImage* _Other, const float4& _CopyPos, unsigned int _TransColor)
{
	TransCopy(_Other, _CopyPos - _Other->GetScale().Half(), _Other->GetScale(), float4{ 0, 0 }, _Other->GetScale(), _TransColor);
}

void GameEngineImage::TransCopyCenterScale(GameEngineImage* _Other, const float4& _CopyPos, const float4& _RenderScale, unsigned int _TransColor)
{
	TransCopy(_Other, _CopyPos - _RenderScale.Half(), _RenderScale, float4{ 0, 0 }, _Other->GetScale(), _TransColor);
}

void GameEngineImage::TransCopyBot(GameEngineImage* _Other, const float4& _CopyPos, unsigned int _TransColor)
{
	TransCopy(_Other, _CopyPos - _Other->GetScale().Half(), _Other->GetScale(), float4{ 0, 0 }, _Other->GetScale(), _TransColor);
}

void GameEngineImage::TransCopy(GameEngineImage* _Other, const float4& _CopyPos, const float4& _CopyScale, const float4& _OtherPivot, const float4& _OtherScale, unsigned int _TransColor)
{
	// 윈도우에서 지원해주는 일반적인 DC vs DC의 복사함수
	TransparentBlt(ImageDC_		// 여기에 복사
		, _CopyPos.ix()			// 내 이미지의 x
		, _CopyPos.iy()			// 내 이미지의 y에 복사
		, _CopyScale.ix()		// 내 이미지의 x
		, _CopyScale.iy()		// 내 이미지의 y 크기만큼
		, _Other->ImageDC_		// 복사하려는 대상
		, _OtherPivot.ix()		// 복사하려는 대상의 시작점 x
		, _OtherPivot.iy()		// 복사하려는 대상의 시작점 y
		, _OtherScale.ix()		// 복사하려는 대상의 시작점 x
		, _OtherScale.iy()		// 복사하려는 대상의 시작점 y
		, _TransColor);			// 복사하라는 명령
}

void GameEngineImage::ImageScaleCheck()
{
	// DC 내부에 박혀있는 BITMAP을 꺼내오는 함수
	HBITMAP CurrentBitMap = (HBITMAP)GetCurrentObject(ImageDC_, OBJ_BITMAP);
	GetObject(CurrentBitMap, sizeof(BITMAP), &Info_);
}
