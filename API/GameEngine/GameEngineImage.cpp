#include "GameEngineImage.h"
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngineBase/GameEngineWindow.h>

// �̹��� ���̺귯���� �ʿ�
#pragma comment(lib,"msimg32.lib")

GameEngineImage::GameEngineImage()
	: ImageDC_(nullptr)
{
}

GameEngineImage::~GameEngineImage()
{
	// window���� �Ҵ��� �͵��� ������ üũ�� �ȵ����� �����ִ� ���� ���
	// window���� �Ҵ��� ���̹Ƿ� window�� �Լ��� �̿��Ͽ� ����
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
		MsgBoxAssert("ũ�Ⱑ 0�� �̹����� �����Ϸ��� �߽��ϴ�.");
		return false;
	}
	
	// ���� �̹��� ũ�⸸�� ��Ʈ���� ����
	BitMap_ = CreateCompatibleBitmap(GameEngineWindow::GetHDC(), _Scale.ix(), _Scale.iy());
	// ������� ����, ũ�Ⱑ 1�� HBITMAP ����(OldBitMap)
	ImageDC_ = CreateCompatibleDC(nullptr);

	if (nullptr == ImageDC_)
	{
		MsgBoxAssert("ImageDC ������ �����߽��ϴ�.");
	}

	OldBitMap_ = (HBITMAP)SelectObject(ImageDC_, BitMap_);

	ImageScaleCheck();

	return true;
}

// �̹� ������� DC�� ���Խ�Ű���� ��
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
		MsgBoxAssertString(_Path + "�̹��� �ε忡 �����߽��ϴ�. Ȯ���ؾ� �Ǵ� ���� 1. ��ΰ� ����� �Ǿ��ֳ���? 2. ������� ����� Ȯ���߳���?");
	}

	ImageDC_ = CreateCompatibleDC(nullptr);

	if (nullptr == ImageDC_)
	{
		MsgBoxAssert("ImageDC ������ �����߽��ϴ�.");
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

// �ٸ� �̹����� ���ͼ� ����
void GameEngineImage::BitCopy(GameEngineImage* _Other, const float4& _CopyPos, const float4& _CopyScale, const float4& _OtherPivot)
{
	// �����쿡�� �������ִ� �Ϲ����� DC vs DC�� �����Լ�
	BitBlt(ImageDC_				// ���⿡ ����
		, _CopyPos.ix()			// �� �̹����� x
		, _CopyPos.iy()			// �� �̹����� y�� ����
		, _CopyScale.ix()	// �� �̹����� x
		, _CopyScale.iy()	// �� �̹����� y ũ�⸸ŭ
		, _Other->ImageDC_		// �����Ϸ��� ���
		, _OtherPivot.ix()		// �����Ϸ��� ����� ������ x
		, _OtherPivot.iy()		// �����Ϸ��� ����� ������ y
		, SRCCOPY);				// �����϶�� ���
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
	// �����쿡�� �������ִ� �Ϲ����� DC vs DC�� �����Լ�
	TransparentBlt(ImageDC_		// ���⿡ ����
		, _CopyPos.ix()			// �� �̹����� x
		, _CopyPos.iy()			// �� �̹����� y�� ����
		, _CopyScale.ix()		// �� �̹����� x
		, _CopyScale.iy()		// �� �̹����� y ũ�⸸ŭ
		, _Other->ImageDC_		// �����Ϸ��� ���
		, _OtherPivot.ix()		// �����Ϸ��� ����� ������ x
		, _OtherPivot.iy()		// �����Ϸ��� ����� ������ y
		, _OtherScale.ix()		// �����Ϸ��� ����� ������ x
		, _OtherScale.iy()		// �����Ϸ��� ����� ������ y
		, _TransColor);			// �����϶�� ���
}

void GameEngineImage::ImageScaleCheck()
{
	// DC ���ο� �����ִ� BITMAP�� �������� �Լ�
	HBITMAP CurrentBitMap = (HBITMAP)GetCurrentObject(ImageDC_, OBJ_BITMAP);
	GetObject(CurrentBitMap, sizeof(BITMAP), &Info_);
}
