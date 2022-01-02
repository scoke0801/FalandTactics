#include "stdafx.h"
#include "SystemImage.h"

CSystemImage* CSystemImage::instance = NULL;

CSystemImage::CSystemImage()
{
	m_imageTile.Load(_T("resource/SystemImage/tile.png"));
	m_imageWay.Load(_T("resource/SystemImage/way.png"));
	m_imagePortal.Load(_T("resource/SystemImage/portal.png"));
	m_imageDamage.Load(_T("resource/SystemImage/number.png"));
	m_imageDie.Load(_T("resource/SystemImage/die.png"));
	m_imageMiss.Load(_T("resource/SystemImage/miss.png"));
}
CSystemImage* CSystemImage::GetInstance()
{
	if (instance == NULL)
	{
		instance = new CSystemImage();
	}
	return instance;
}

void CSystemImage::DrawTile(HDC hdc, POINT pos,int kind, Camera camera )
{
	m_imageTile.TransparentBlt
		(hdc, pos.x + camera.viewPoint.x
			, pos.y + camera.viewPoint.y
			, 64, 32
			, kind * 64, 0, 64, 32,
			RGB(255, 0, 255)
			);
}

void CSystemImage::DrawWay(HDC hdc, CUnit* unit, Camera camera )
{
	m_imageWay.TransparentBlt(
		hdc 
		,unit->GetUnitPos().x  + camera.viewPoint.x 
		,unit->GetUnitPos().y + camera.viewPoint.y
		, 15, 11
		, 0, 0
		, 15, 11
		, RGB(255,0,0));

	m_imageWay.TransparentBlt(
		hdc
		, unit->GetUnitPos().x + camera.viewPoint.x + 48
		, unit->GetUnitPos().y + camera.viewPoint.y
		, 15, 11
		, 15, 0
		, 15, 11
		, RGB(255, 0, 0));

	m_imageWay.TransparentBlt(
		hdc
		, unit->GetUnitPos().x + camera.viewPoint.x
		, unit->GetUnitPos().y + camera.viewPoint.y + 24
		, 15, 11
		, 0, 11
		, 15, 11
		, RGB(255, 0, 0));

	m_imageWay.TransparentBlt(
		hdc
		, unit->GetUnitPos().x + camera.viewPoint.x + 48
		, unit->GetUnitPos().y + camera.viewPoint.y + 24
		, 15, 11
		, 15, 11
		, 15, 11
		, RGB(255, 0, 0));
}


void CSystemImage::DrawPortal(HDC hdc, POINT pos, Camera camera)
{
	static int delay[2] = { 0, };

	m_imagePortal.TransparentBlt(
		hdc
		, pos.x + camera.viewPoint.x, pos.y + camera.viewPoint.y
		, TILE_WIDTH * 2, TILE_HEIGHT * 2
		, delay[1] * TILE_WIDTH * 2, 0
		, TILE_WIDTH * 2, TILE_HEIGHT * 2
		, RGB(255, 0, 255));
	
	delay[0]++;
	if (delay[0] > 3)
	{
		delay[0] = 0;
		delay[1]++;
	}
	if (delay[1] > 5)
		delay[1] = 0;
}

BOOL CSystemImage::DrawDamage(HDC hdc, POINT pos, DamageTeam phase, int damage,Camera camera)
{
	//damage�� �ִ� ������ ���ѿ� ���ؼ� 3�ڸ��� �̻��� ���� �� �����ϴ�.
	int num[3];
	int maxIndex = 0;

	if (damage >= 1000)	//������� 4�ڸ��� ��� MISS���
	{
		m_imageMiss.TransparentBlt(hdc
			, pos.x + camera.viewPoint.x 
			, pos.y + camera.viewPoint.y - 53
			, 64, 19
			, 0
			, (int)phase * 19
			, 64, 19
			, RGB(255, 0, 255)
			);
		return FALSE;
	}
	if (damage >= 0 && damage < 10)	//�� �ڸ�
	{
		num[0] = damage;
		maxIndex = 0;
	}
	else if (damage >= 10 && damage < 99)	//�� �ڸ�
	{
		num[0] = damage / 10;				//�� �ڸ�
		num[1] = damage % 10;				//�� �ڸ�
		maxIndex = 1;
	}
	else if (damage >= 100 && damage < 999)	//�� �ڸ�
	{
		num[0] = damage / 100;					//�� �ڸ�
		num[1] = damage / 10 - num[0] * 10;		//�� �ڸ�
		num[2] = damage % 10;					//�� �ڸ�
		maxIndex = 2;
	}
	//16,32
	if (maxIndex == 0)
	{
		m_imageDamage.TransparentBlt(hdc
			, pos.x + camera.viewPoint.x + 26
			, pos.y + camera.viewPoint.y - 60
			, 16, 32
			, (int)phase * 128
			, num[0] * 32
			, 16, 32
			, RGB(255, 0, 255)
			);
	}
	else
	{
		for (int i = 0; i <= maxIndex; ++i)
		{
			m_imageDamage.TransparentBlt(hdc
				, pos.x + camera.viewPoint.x + (16 * i) + 15
				, pos.y + camera.viewPoint.y - 60
				, 16, 32
				, (int)phase * 128
				, num[i] * 32
				, 16, 32
				, RGB(255, 0, 255)
				);
		}
	}
	return FALSE;
}
void CSystemImage::DrawDieAngel(HDC hdc, POINT pos, int imagePos, Camera camera)
{
	m_imageDie.TransparentBlt(hdc
		, pos.x + camera.viewPoint.x
		, pos.y + camera.viewPoint.y - 40
		, 53, 23
		, 53 * imagePos, 0
		, 53, 23
		, RGB(255, 0, 0)
		);
}