#include "stdafx.h"
#include "Sprite.h"

CSpriteImage::CSpriteImage(LPCTSTR szPath, int w, int h)
{
	m_spriteImage.Load(szPath);

	m_nSpriteXNum = w;
	m_nSpriteYNum = h;

	m_nSpriteWidth = m_spriteImage.GetWidth() / m_nSpriteXNum;
	m_nSpriteHeight = m_spriteImage.GetHeight() / m_nSpriteYNum;

	m_ptCurrentSpritePos.x = 0;
	m_ptCurrentSpritePos.y = 0;
	//지정한 위치의 이미지 색상을 가져옵니다.
	m_transparent = ::GetPixel(m_spriteImage.GetDC(), 0, 0);
}
CSpriteImage::~CSpriteImage()
{
	if (!m_spriteImage)
		m_spriteImage.Destroy();
}

void CSpriteImage::OnUpdate()
{
	m_ptCurrentSpritePos.x++;

	if (m_ptCurrentSpritePos.x >= m_nSpriteXNum)
	{
		m_ptCurrentSpritePos.x = 0;
		m_ptCurrentSpritePos.y++;
	}

	if (m_ptCurrentSpritePos.y >= m_nSpriteYNum)
	{
		m_ptCurrentSpritePos.y = 0;
	}
}

void CSpriteImage::Draw(HDC hdc, int x, int y, Camera camera)
{
	m_spriteImage.TransparentBlt(
		hdc
		, x + camera.viewPoint.x
		, y + camera.viewPoint.y
		, m_nSpriteWidth
		, m_nSpriteHeight
		, m_ptCurrentSpritePos.x * m_nSpriteWidth
		, m_ptCurrentSpritePos.y * m_nSpriteHeight
		, m_nSpriteWidth
		, m_nSpriteHeight
		, m_transparent
		);
}
void CSpriteImage::LoadImage(LPCTSTR szPath)
{
	m_spriteImage.Load(szPath);
}