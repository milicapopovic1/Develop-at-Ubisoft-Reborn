#ifndef _MAP_H_
#define _MAP_H_
#include "..\app\app.h"
using namespace Constants;
class Field;

class Map {
private:
	Map();
	~Map();
	static Map* instance;
	float fieldWidth;
	float fieldHeight;
	Field** fields;
	Field* endField;
	bool isSafe(int i, int j);
	bool findPath(int i, int j);
	bool checkMap();
	bool isaPath(int matrix[][COLUMN_NUMBER], int i, int j, bool visited[][COLUMN_NUMBER]);
	void initializeGrass();
	void generateMaze();
	void generateBush(int i, int j);
	void generateWood(int i, int j);

public:
	static void deleteMap();
	static Map* getInstance(); //singleton class
	void Draw();
	Field* getField(float x, float y);
	Field* getFieldByPosition(int i, int j);
	void divide(int minX, int minY, int maxX, int maxY, int* horizontalWalls, int* verticalWalls);
	void getFieldPosition(float x,float y,int& i,int& j);
	bool isValidField(int i, int j);
	void getFieldCoordinates(int i, int j, float& x, float& y);
	void restart();
};
#endif