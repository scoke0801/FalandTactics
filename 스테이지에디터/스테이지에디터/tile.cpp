#include "tile.h"
#include "base.h"
#define WIDTH 64
#define HEIGHT 32
#pragma region 도구
void Tile::Init(int i, int j)
{
	if (i % 2 == 0)
	{
		this->Left = (i / 2) * WIDTH;
		this->Top = j * HEIGHT;
	}
	else
	{
		this->Left = (i - 1) / 2 * WIDTH + WIDTH / 2;
		this->Top = j * HEIGHT + HEIGHT / 2;
	}
	this->Type = 1;
	this->Image = 0;
	this->Height = 0;
}
void Tile::Draw(HDC memdc, CImage* tile, int i, int j, int CamX[2], int CamY[2])
{
	tile->TransparentBlt(memdc, this->Left + CamX[0] + CamX[1], this->Top + CamY[0] + CamY[1],
		WIDTH, HEIGHT,
		WIDTH * this->Type, HEIGHT * this->Image,
		WIDTH, HEIGHT, RGB(255, 0, 255));
	if (this->Height >= 1)
	{
		for (int k = this->Height; k > 0; --k)
		{
			tile->TransparentBlt(memdc, this->Left + CamX[0] + CamX[1], this->Top + CamY[0] + CamY[1] + k * HEIGHT / 2,
				WIDTH, HEIGHT,
				WIDTH * this->Type, HEIGHT * 12,
				WIDTH, HEIGHT, RGB(255, 0, 255));
		}
	}
}
#pragma endregion
#pragma region 게터
float Tile::GetLeft()
{
	return this->Left;
}
float Tile::GetTop()
{
	return this->Top;
}
int Tile::GetType()
{
	return this->Type;
}
int Tile::GetImage()
{
	return this->Image;
}
int Tile::GetHeight()
{
	return this->Height;
}
#pragma endregion
#pragma region 세터
void Tile::SetLeft(float Left)
{
	this->Left = Left;
}
void Tile::SetTop(float Top)
{
	this-> Top = Top;
}
void Tile::SetType(int Type)
{
	this->Type = Type;
}
void Tile::SetImage(int Image)
{
	this->Image = Image;
}
void Tile::SetHeight(int Height)
{
	this->Height = Height;
}
#pragma endregion