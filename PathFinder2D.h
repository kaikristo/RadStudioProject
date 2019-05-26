#pragma once

#define OUT

#include <queue>
#include <cmath>
#include <vector>

class PathFinder2D {

private:
	// Obstacle Array
	// Size of array
	int cols, rows;
	// array
	int* iObstacleMap;
	// Array of Length to the point;
	// It's size equal  size of Obstacle array
	// close points
	bool** bWasHere;

	int iStartX, iStartY, iEndX, iEndY;
	float** fLengthToPoint;

public:
	struct Point {
		int x, y;
		PathFinder2D *ref;
		Point();
		Point(PathFinder2D *ref);
		Point(int x, int y, PathFinder2D *ref);
		bool operator > (const Point& cmp) const ;
		bool operator == (const Point& cmp) const ;
		bool operator < (const Point& cmp) const ;
	};
   	std::priority_queue<Point>qPointsToScan;
	// Use existing map
	PathFinder2D(int cols, int rows, int *firstObstacleMapCell);

	~PathFinder2D();
	float GetLengthToPoint(int x, int y);

	std::vector<Point> FindPath(int fromX, int fromY, int toX, int toY);
	float** GetLenghtToPointMap();

	void GetObstaclesArray();
	int GetEndX();
	int GetEndY();

	std::vector<Point>  CreatePath();

private:
	void EraseLengthArray();
	void SetObstacleMap(int x, int y, int value);
	int GetObstacleMap(int x, int y);
	bool PointInMap(int x, int y, int dx, int dy);
	template<class Q>
	void ClearQueue(Q& q);

};
