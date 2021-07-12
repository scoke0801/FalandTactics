#pragma once

class CSpriteImage
{
public:
	CSpriteImage(LPCTSTR szPath, int w, int h);
	virtual ~CSpriteImage();

	virtual void OnUpdate();
	void Draw(HDC hdc, int x, int y, Camera camera = { 0, });

	void SubSpritePos() { m_ptCurrentSpritePos.x--; }

	void SetCurrentSpritePos(POINT pos) { m_ptCurrentSpritePos = pos; }

	int GetSpriteWidth() { return m_nSpriteWidth; }
	int GetSpriteHeight() { return m_nSpriteHeight; }

	void LoadImage(LPCTSTR szPath);
protected:
	CImage m_spriteImage;

	int m_nSpriteXNum;						//스프라이트 가로 줄에 이미지가 몇 개 들어있는가를 나타냅니다.
	int m_nSpriteYNum;						//스프라이트 세로 줄에 이미지가 몇 개 들어있는가를 나타냅니다. 

	int m_nSpriteWidth;						//스프라이트 안 이미지 한 개의 가로 길이를 나타냅니다.
	int m_nSpriteHeight;					//스프라이트 안 이미지 한 개의 세로 길이를 나타냅니다.

	POINT m_ptCurrentSpritePos;				//스프라이트에서 현재 출력할 위치를 지정합니다.

	COLORREF m_transparent;					//투명값을 적용시킬 색상을 지정합니다.
};

