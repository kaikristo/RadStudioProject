// ---------------------------------------------------------------------------

#pragma hdrstop

#include "Map.h"
// ---------------------------------------------------------------------------
#pragma package(smart_init)

Map::Map(int cols, int rows) {

	this->cols = cols;
	this->rows = rows;
	this->map = new int[rows * cols];
	for (int i = 0; i < rows * cols; i++)
		this->map[i] = 0;
}

Map::~Map() {

	delete[]map;
}

void Map::RandomMap(float ObstaclePercent) {
	for (int i = 0; i < rows * cols; i++) {
		if (random(100) < ObstaclePercent)
			this->map[i] = -1;
	}
}

int* Map::GetMap() {
	return this->map;
}

int Map::GetRowsCount()
{
	return this->rows;
}
int Map::GetColsCount(){
    return this->cols;
}
void Map::SetObstacle(int x,int y)
{
  map[ y*cols + x] = -1;
}
