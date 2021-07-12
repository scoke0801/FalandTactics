#pragma once


class CSystemImage
{
private:
	CSystemImage();
public:
	static CSystemImage* GetInstance();

	void DrawTile(HDC hdc, POINT pos,int kind, Camera camera = { 0, });
	void DrawWay(HDC hdc, CUnit* unit, Camera camera = { 0, });
	void DrawPortal(HDC hdc, POINT pos, Camera camera = { 0, });
	BOOL DrawDamage(HDC hdc, POINT pos, DamageTeam phase,int damage,Camera camera = { 0, });
	void DrawDieAngel(HDC hdc, POINT pos, int imagePos, Camera = { 0, });

private:
	CImage m_imageTile;
	CImage m_imageWay;
	CImage m_imagePortal;
	CImage m_imageDamage;
	CImage m_imageDie;
	CImage m_imageMiss;

	static CSystemImage* instance;
};