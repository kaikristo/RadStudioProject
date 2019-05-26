#include "PathFinder2D.h"

void PathFinder2D::EraseLengthArray() {
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++)
			fLengthToPoint[j][i] = cols * rows + 1;
}

PathFinder2D::PathFinder2D(int cols, int rows, int *firstObstacleMapCell) {

	// set nessesary parameters
	this->cols = cols;
	this->rows = rows;

	iObstacleMap = firstObstacleMapCell;

	// create map of length

	fLengthToPoint = new float*[rows];

	for (int i = 0; i < rows; i++) {
		fLengthToPoint[i] = new float[cols];
	}

	for (int y = 0; y < rows; y++)
		for (int x = 0; x < cols; x++)
			fLengthToPoint[x][y] = rows * cols + 1;

	bWasHere = new bool* [rows];
	for (int i = 0; i < rows; i++) {
		bWasHere[i] = new bool[cols];
	}

	for (int y = 0; y < rows; y++)
		for (int x = 0; x < cols; x++)
			bWasHere[x][y] = false;
}

PathFinder2D::~PathFinder2D() {
	for (int i = 0; i < rows; i++) {
		delete[]fLengthToPoint[i];
	}
	delete[]fLengthToPoint;

	for (int i = 0; i < rows; i++) {
		delete[]bWasHere[i];
	}
	delete[]bWasHere;
}

// can we use neigbors without errors?

inline bool PathFinder2D::PointInMap(int x, int y, int dx, int dy) {

	if (x + dx >= cols) {

		return false;
	}
	if (x + dx < 0) {
		return false;
	}
	if (y + dy >= rows) {
		return false;
	}
	if (y + dy < 0) {
		return false;
	}
	if (GetObstacleMap((x + dx), (y + dy)) == -1) {
		return false;
	}
	if (dx == 0 && dy == 0) {
		return false;
	}

	return true;
}

template<class Q>
void PathFinder2D::ClearQueue(Q& q) {
	q = Q();
}

std::vector<PathFinder2D::Point>PathFinder2D::FindPath(int fromX, int fromY,
	int toX, int toY) {
	// value is valid
	if (fromX >= cols)
		fromX = cols - 1;
	if (fromY >= rows)
		fromX = rows - 1;

	if (fromX < 0)
		fromX = 0;
	if (fromY < 0)
		fromY = 0;

	if (toX >= cols)
		toX = cols - 1;
	if (toY >= rows)
		toX = rows - 1;

	if (toX < 0)
		toX = 0;
	if (toY < 0)
		toY = 0;

	iEndX = toX;
	iEndY = toY;
	iStartX = fromX;
	iStartY = fromY;

	EraseLengthArray();
	ClearQueue(qPointsToScan);

	qPointsToScan.push(Point(fromX, fromY, this));

	fLengthToPoint[fromX][fromY] = 0;

	while (!qPointsToScan.empty()) {

		Point p = qPointsToScan.top();
		if (p.x == toX && p.y == toY) {
			return CreatePath();

		}
		qPointsToScan.pop();
		float fCurLength = fLengthToPoint[p.x][p.y];
		bWasHere[p.x][p.y] = true;
		for (int i = -1; i <= 1; i++)
			for (int j = -1; j <= 1; j++) {

				if (PointInMap(p.x, p.y, i, j)) {
					float fCost = 1.0f;
					// diagonal movement cost 1.5

					if (abs(i) == abs(j))
						fCost = 1.5f;

					if (bWasHere[p.x + i][p.y + j])
						// if new movement not better than older
						if (fCurLength + fCost >=
							fLengthToPoint[p.x + i][p.y + j]) {

							continue;
						}
					fLengthToPoint[p.x + i][p.y + j] = fCurLength + fCost;
					bWasHere[p.x + i][p.y + j] = true;
					qPointsToScan.push(Point(p.x + i, p.y + j, this));
				}

			}
	}
	std::vector<Point>s;
	return s;
}

float** PathFinder2D::GetLenghtToPointMap() {
	return fLengthToPoint;
}

PathFinder2D::Point::Point(PathFinder2D *ref) {
	x = 0;
	y = 0;
	this->ref = ref;
}

PathFinder2D::Point::Point() {
	x = 0;
	y = 0;
	this->ref = NULL;
}

PathFinder2D::Point::Point(int x, int y, PathFinder2D *ref) {
	this->x = x;
	this->y = y;
	this->ref = ref;
}

bool PathFinder2D::Point:: operator > (const Point& cmp) const {
	// check distance to destination
	int a1 = (x - ref->GetEndX()) * (x - ref->GetEndX());
	int b1 = (y - ref->GetEndY()) * (y - ref->GetEndY());
	float d1 = std::sqrt(a1 + b1) + ref->GetLengthToPoint(x, y);

	int a2 = (cmp.x - ref->GetEndX()) * (cmp.x - ref->GetEndX());
	int b2 = (cmp.y - ref->GetEndY()) * (cmp.y - ref->GetEndY());
	float d2 = std::sqrt(a2 + b2) + ref->GetLengthToPoint(cmp.x, cmp.y);

	if (d1 > d2)
		return false;

	return true;
}

bool PathFinder2D::Point:: operator < (const Point& cmp) const {

	// check distance to destination
	int a1 = (x - ref->GetEndX()) * (x - ref->GetEndX());
	int b1 = (y - ref->GetEndY()) * (y - ref->GetEndY());
	float d1 = std::sqrt(a1 + b1) + ref->GetLengthToPoint(x, y);

	int a2 = (cmp.x - ref->GetEndX()) * (cmp.x - ref->GetEndX());
	int b2 = (cmp.y - ref->GetEndY()) * (cmp.y - ref->GetEndY());
	float d2 = std::sqrt(a2 + b2) + ref->GetLengthToPoint(cmp.x, cmp.y);

	if (d1 > d2)
		return true;

	return false;

}

int PathFinder2D::GetEndX() {
	return iEndX;
}

int PathFinder2D::GetEndY() {
	return iEndY;
}

void PathFinder2D::SetObstacleMap(int x, int y, int value) {
	iObstacleMap[y * cols + x] = value;
}

int PathFinder2D::GetObstacleMap(int x, int y) {
	return iObstacleMap[y * cols + x];
}

float PathFinder2D::GetLengthToPoint(int x, int y) {
	return fLengthToPoint[x][y];

}

std::vector<PathFinder2D::Point>PathFinder2D::CreatePath() {
	// finding a path
	PathFinder2D::Point p;
	p.x = iEndX;
	p.y = iEndY;

	PathFinder2D::Point tmp;

	std::vector<PathFinder2D::Point>path;
    path.push_back(p);
	int n = 0;

	while (n < cols * rows) {
		float min = fLengthToPoint[p.x][p.y];

		for (int i = -1; i <= 1; i++)
			for (int j = -1; j <= 1; j++) {
				if (PointInMap(p.x, p.y, i, j)) {
					if (min > fLengthToPoint[p.x + i][p.y + j]) {
						tmp.x = p.x + i;
						tmp.y = p.y + j;
						min = fLengthToPoint[p.x + i][p.y + j];
					}
				}
			}
		if(p.x==tmp.x && p.y==tmp.y) break;
		p = tmp;
		path.push_back(p);
		if (p.x == iStartX && p.y == iStartY)
			return path;
		n++;
	}
    path.clear();
	return path;

}
