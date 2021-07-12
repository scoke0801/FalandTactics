#pragma once
#include "base.h"
class Tile {
private:
	float Left, Top;
	int Type, Image, Height;
public:
#pragma region ����
	void Init(int, int);
	void Draw(HDC, CImage*, int, int, int*, int*);
#pragma region
#pragma region ����
	float GetLeft();
	float GetTop();
	int GetType();
	int GetImage();
	int GetHeight();
#pragma endregion
#pragma region ����
	void SetLeft(float);
	void SetTop(float);
	void SetType(int);
	void SetImage(int);
	void SetHeight(int);
#pragma endregion
};