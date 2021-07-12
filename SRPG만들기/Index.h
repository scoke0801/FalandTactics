#pragma once

/*
게임에서 사용하는 맵 데이터 배열을
보다 편하게 관리 및 사용하기 위하여 정의한 클래스 
*/
class CIndex
{
public:
	CIndex() {}
	CIndex(int x, int y, int height );

	BOOL CheckInRange(int mapSize = 1);
	BOOL CheckInRange(int row, int column);

	int GetXPos() const;
	int GetYPos() const;
	CIndex GetIndex();
	void SetXIndex();
	void SetYIndex();

	operator POINT const();
	bool operator<(CIndex index);
	//bool operator=(in);
	
	friend bool operator<(CIndex index1, CIndex index2);
public:
	int x, y;
	int height;
};

typedef CIndex INDEX;