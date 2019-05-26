// ---------------------------------------------------------------------------

#ifndef CharacterH
#define CharacterH
#include "PathFinder2D.h"
#include "Map.h"
#include <vector>
#include <System.hpp>





class Character {
private:
	int x, y;

	std::vector<PathFinder2D::Point>vPath;

	PathFinder2D* PathFinder;
	std::wstring name;
	int* map;
	int cols, rows;

public:
	Character(int x, int y, std::wstring name, Map* map);
	~Character();

	int GetX();
	int GetY();
	void SetXY(int x, int y);

	std::wstring GetName();
 	void SetName(std::wstring name);

	void CalculatePathTo(int x,int y);
	void Move();

};

// ---------------------------------------------------------------------------
#endif
