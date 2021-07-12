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

	int m_nSpriteXNum;						//��������Ʈ ���� �ٿ� �̹����� �� �� ����ִ°��� ��Ÿ���ϴ�.
	int m_nSpriteYNum;						//��������Ʈ ���� �ٿ� �̹����� �� �� ����ִ°��� ��Ÿ���ϴ�. 

	int m_nSpriteWidth;						//��������Ʈ �� �̹��� �� ���� ���� ���̸� ��Ÿ���ϴ�.
	int m_nSpriteHeight;					//��������Ʈ �� �̹��� �� ���� ���� ���̸� ��Ÿ���ϴ�.

	POINT m_ptCurrentSpritePos;				//��������Ʈ���� ���� ����� ��ġ�� �����մϴ�.

	COLORREF m_transparent;					//������ �����ų ������ �����մϴ�.
};

