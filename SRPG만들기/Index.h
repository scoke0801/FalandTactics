#pragma once

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