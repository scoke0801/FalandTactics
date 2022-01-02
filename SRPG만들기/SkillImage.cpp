#include "stdafx.h"
#include "SkillImage.h"

CSkillImage* CSkillImage::instance = NULL;

CSkillImage::CSkillImage()
{
	m_imageBurst.Load(_T("resource/Skill/burst.png"));
	m_imageAid[0].Load(_T("resource/skill/aid.png"));
	m_imageAid[1].Load(_T("resource/skill/manaaid.png"));
	m_imageCurse.Load(_T("resource/skill/curse.png"));
	m_imageHurricane.Load(_T("resource/skill/Hurricane.png"));
	m_imageThunder.Load(_T("resource/skill/thunder.png"));
	m_imageResurrection.Load(_T("resource/skill/Resurrection.png"));
	m_imageEdge.Load(_T("resource/skill/edge.png"));
}
CSkillImage* CSkillImage::GetInstance()
{
	if (instance == NULL)
	{
		instance = new CSkillImage();
	}
	return instance;
}

void CSkillImage::DrawBurst(HDC hdc, POINT pos, int imagePos, Camera camera)
{
	m_imageBurst.TransparentBlt(hdc
		, pos.x + camera.viewPoint.x - 11
		, pos.y + camera.viewPoint.y - 96
		, 75, 128
		, 75 * imagePos, 0
		, 75, 128
		, RGB(255, 0, 255)
		);
}
void CSkillImage::DrawCurse(HDC hdc, POINT pos, int imagePos, Camera camera )
{
	//���� 70, ���� 150
	m_imageCurse.TransparentBlt(hdc
		, pos.x + camera.viewPoint.x - 4
		, pos.y + camera.viewPoint.y - 118
		, 70, 150
		, 70 * imagePos, 0
		, 70, 150
		, RGB(255, 0, 255)
		);
}
void CSkillImage::DrawEdge(HDC hdc, POINT pos, int imagePos, Camera camera)
{
	//����60, ����120
	m_imageEdge.TransparentBlt(hdc
		, pos.x + camera.viewPoint.x + 4
		, pos.y + camera.viewPoint.y - 88
		, 60, 120
		, 60 * imagePos, 0
		, 60, 120
		, RGB(255, 0, 255)
		);
}

void CSkillImage::DrawHurricane(HDC hdc, POINT pos, int imagePos, Camera camera )
{
	//���� 72, ���� 68
	m_imageHurricane.TransparentBlt(hdc
		, pos.x + camera.viewPoint.x - 8
		, pos.y + camera.viewPoint.y - 36
		, 72, 68
		, 72 * imagePos, 0
		, 72, 68
		, RGB(255, 0, 255)
		);
}

void CSkillImage::DrawAid(HDC hdc, POINT pos, int imagePos, int kind, Camera camera )
{
	//���� 90, ���� 85
	if (kind < 0 && kind > 1)
		return;
	m_imageAid[kind].TransparentBlt(hdc
		, pos.x + camera.viewPoint.x - 15
		, pos.y + camera.viewPoint.y - 100
		, 90, 85
		, 90 * imagePos, 0
		, 90, 85
		, RGB(255, 0, 255)
		);
}

void CSkillImage::DrawResurrection(HDC hdc, POINT pos, int imagePos, Camera camera)
{
	//���� 64, ���� 192
	if (imagePos < 12)
	{
		m_imageResurrection.TransparentBlt(hdc
			, pos.x + camera.viewPoint.x
			, pos.y + camera.viewPoint.y - 160
			, 64, 192
			, 64 * imagePos, 0
			, 64, 192
			, RGB(255, 0, 255)
			);
	}
	else
	{
		m_imageResurrection.TransparentBlt(hdc
			, pos.x + camera.viewPoint.x
			, pos.y + camera.viewPoint.y - 160
			, 64, 192
			, 64 * (23 - imagePos), 0
			, 64, 192
			, RGB(255, 0, 255)
			);
	}
}

void CSkillImage::DrawThunder(HDC hdc, POINT pos, int imagePos, Camera camera)
{
	//���� 85, ���� 378
	m_imageThunder.TransparentBlt(hdc
		, pos.x + camera.viewPoint.x - 21
		, pos.y + camera.viewPoint.y - 346
		, 85, 378
		, 85 * imagePos, 0
		, 85, 378
		, RGB(255, 0, 255)
		);
}