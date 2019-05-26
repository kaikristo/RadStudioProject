// ---------------------------------------------------------------------------

#pragma hdrstop

#include "Character.h"
// ---------------------------------------------------------------------------
#pragma package(smart_init)

Character::Character(int x, int y, std::wstring name, Map* map) {
	this->x = x;
	this->y = y;
	this->name = name;
	this->map = map->GetMap();
	this->cols = map->GetColsCount();
	this->rows = map->GetRowsCount();
	PathFinder = new PathFinder2D(cols, rows, this->map);
}

Character::~Character() {
	delete PathFinder;
}

int Character::GetX() {
	return x;
}
int Character::GetY() {
	return y;
}
std::wstring Character::GetName()
{
    return name;
}
void Character::SetName(std::wstring name)
{
    this->name = name;
}
void Character::Move() {
if (vPath.size()>0)
{
int x,y;
x = vPath[vPath.size()-1].x;
y = vPath[vPath.size()-1].y;
SetXY(x,y);
vPath.erase(vPath.end()-1);
}
};

void Character::CalculatePathTo(int x, int y)
{
  if (x>0 && x<cols && y>0 && y<rows)
  vPath = PathFinder->FindPath(this->x,this->y,x,y);
}

void Character::SetXY(int x, int y) {
	this->x = x;
	this->y = y;
}
