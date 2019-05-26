#pragma once

#define OUT

#include <queue>
#include <cmath>
class PathFinder2D
{

private:
	//Obstacle Array
	// Size of array
	int cols, rows;
	//array
	int* iObstacleMap;
	//Array of Length to the point;
	//It's size equal  size of Obstacle array
	//close points
	bool** bWasHere;
	

	struct Point {
		int x, y;
                PathFinder2D *ref;
		Point(PathFinder2D *ref);
		Point(int x, int y, PathFinder2D *ref);
		bool operator>(const Point& cmp) const;
		bool operator==(const Point& cmp) const;
		bool operator<(const Point& cmp) const;
	};
          int iStartX, iStartY,iEndX, iEndY;
        float** fLengthToPoint;

	void SetObstacleMap(int x,int y, int value);
        int GetObstacleMap(int x,int y);

public:

	//Use existing map
	PathFinder2D(int cols, int rows, int *firstObstacleMapCell);
        float GetLengthToPoint(int x,int y);
	~PathFinder2D();
	std::priority_queue<Point> qPointsToScan;
	//can we use neigbors without errors?
	bool PointInMap(int x, int y, int dx, int dy);
        
	bool FindPath(int fromX, int fromY, int toX, int toY);
	float** GetLenghtToPointMap();

        void GetObstaclesArray();
        int GetEndX();
        int GetEndY();


private:
	void EraseLengthArray();
	template<class Q>
	void ClearQueue(Q& q);

};