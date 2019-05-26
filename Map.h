//---------------------------------------------------------------------------

#include <stdlib>
#ifndef MapH
#define MapH

class Map
{


private:
int cols,rows;
int* map;

public:

Map(int cols,int rows);
~Map();
int GetRowsCount();
int GetColsCount();
void RandomMap(float ObstaclePercent);
void SetObstacle(int x,int y);
int* GetMap();

};

//---------------------------------------------------------------------------
#endif
