#pragma once

class CSkillImage
{
private:
	CSkillImage();
public:
	static CSkillImage* GetInstance();

public:
	void DrawBurst(HDC hdc, POINT pos, int imagePos, Camera camera = { 0, });
	void DrawCurse(HDC hdc, POINT pos, int imagePos, Camera camera = { 0, });
	void DrawEdge(HDC hdc, POINT pos, int imagePos, Camera camera = { 0, });
	void DrawHurricane(HDC hdc, POINT pos, int imagePos, Camera camera = { 0, });
	void DrawAid(HDC hdc, POINT pos, int imagePos, int kind, Camera camera = { 0, });
	void DrawResurrection(HDC hdc, POINT pos, int imagePos, Camera camera = { 0, });
	void DrawThunder(HDC hdc, POINT pos, int imagePos, Camera camera = { 0, });
private:
	CImage m_imageBurst;
	CImage m_imageAid[2];
	CImage m_imageCurse;
	CImage m_imageHurricane;
	CImage m_imageThunder;
	CImage m_imageResurrection;
	CImage m_imageEdge;

	static CSkillImage* instance;
};