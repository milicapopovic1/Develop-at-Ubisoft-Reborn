#include "stdafx.h"

Map* Map::instance = nullptr;

void Map::initializeGrass() {
	for (int i = 0; i < ROW_NUMBER; i++) {
		for (int j = 0; j < COLUMN_NUMBER; j++) {
			fields[i * COLUMN_NUMBER + j] = new Grass();
			fields[i * COLUMN_NUMBER + j]->SetPosition(MAP_X_OFFSET + fieldWidth / 2 + j * fieldWidth, MAP_Y_OFFSET + fieldHeight / 2 + i * fieldHeight);
		}
	}
	fields[ROW_NUMBER * COLUMN_NUMBER - 1] = new Battery(fields[ROW_NUMBER * COLUMN_NUMBER - 1]);
}

Map::Map() {
	fieldHeight = SCALE_FIELD * BMP_HEIGHT_FIELD;
	fieldWidth = SCALE_FIELD * BMP_WIDTH_FIELD;
	endField = new Wood();
	fields = new Field*[ROW_NUMBER * COLUMN_NUMBER];
	initializeGrass(); //first we fill all the fields with grass
	generateMaze();//then we place the walls of the maze where they should be
}

Map::~Map() {
	for (int i = 0; i < ROW_NUMBER; i++) {
		for (int j = 0; j < COLUMN_NUMBER; j++) {
			delete fields[i * COLUMN_NUMBER + j];
		}
	}
	delete fields;
}

void Map::deleteMap() {
	delete instance;
}

Map* Map::getInstance() {
	if (!instance) instance = new Map();
	return instance;
}

void Map::Draw() {
	for (int i = 0; i < ROW_NUMBER; i++) {
		for (int j = 0; j < COLUMN_NUMBER; j++) {
			fields[i * COLUMN_NUMBER + j]->Draw();
		}
	}
}

Field* Map::getField(float x, float y) {//getting field based on x and y coordinate
	int x1 = x - MAP_X_OFFSET;
	int y1 = y - MAP_Y_OFFSET;
	if (x1 < 0 || x1 >= COLUMN_NUMBER * fieldWidth || y1 < 0 || y1 >= ROW_NUMBER * fieldHeight) return endField;
	int columnNumber = x1 / fieldWidth;
	int rowNumber = y1 / fieldHeight;
	int index = rowNumber * COLUMN_NUMBER + columnNumber;
	return fields[index];
}

Field* Map::getFieldByPosition(int i, int j) {//getting field based on map index
	return fields[i * ROW_NUMBER + j];
}

void Map::generateWood(int i, int j) {
	Field* oldField = fields[i * COLUMN_NUMBER + j];
	fields[i * COLUMN_NUMBER + j] = new Wood(oldField);
	delete oldField;
}

void Map::generateBush(int i, int j) {
	Field* oldField = fields[i * COLUMN_NUMBER + j];
	fields[i * COLUMN_NUMBER + j] = new Bush(oldField);
	delete oldField;
}

void Map::divide(int minX, int minY, int maxX, int maxY, int* horizontalWalls, int* verticalWalls) {
	if (maxX - minX <= 1 || maxY - minY <= 1) return; 
	bool horizontal = RANDOMBOOL(); //if numbers of horizontal and vertical walls are equal, generate the following randomly
	if (*horizontalWalls - *verticalWalls >= 1) horizontal = true; //generate horizontal wall
	if (*verticalWalls - *horizontalWalls >= 1) horizontal = false;//generate vertical wall
	if (horizontal) *horizontalWalls++;
	else *verticalWalls++;
	int wallPos;
	while (true) {
		wallPos = horizontal ? RANDOMINT(minY, maxY) : RANDOMINT(minX, maxX);
		if (wallPos % 2) break; //generate only on even positions
	}

	int passagePos1 = horizontal ? RANDOMINT(minX, maxX) : RANDOMINT(minY, maxY);
	int passagePos2 = horizontal ? RANDOMINT(minX, maxX) : RANDOMINT(minY, maxY);

	for (int i = minX; i <= maxX; i++) {
		for (int j = minY; j <= maxY; j++) {
			if ((horizontal && j == wallPos && (i != passagePos1 && i != passagePos2)) || (!horizontal && i == wallPos && (j != passagePos1 && j != passagePos2))) {
				float randomNumber = RANDOMFLOAT(0, 1);
				if (randomNumber < 0.3) generateBush(ROW_NUMBER - 1 - j, i); //generate bush with probability 0.3
				else generateWood(ROW_NUMBER - 1 - j, i);
			}
		}
	}

	if (!horizontal) {
		divide(minX, minY, wallPos-1, maxY, horizontalWalls, verticalWalls); //Recursively repeat for top and bottom of the map
		divide(wallPos + 1, minY, maxX, maxY, horizontalWalls, verticalWalls);
	} else {
		divide(minX, minY, maxX, wallPos-1, horizontalWalls, verticalWalls); //Recursively repeat for left and right part of the map
		divide(minX, wallPos + 1, maxX, maxY, horizontalWalls, verticalWalls);
	}
}


bool Map::isSafe(int i, int j) { //if it is not out of range
	if (i >= 0 && i < ROW_NUMBER && j >= 0 && j < COLUMN_NUMBER) return true;
	return false;
}


bool Map::isaPath(int matrix[][COLUMN_NUMBER], int i, int j, bool visited[][COLUMN_NUMBER]) {
	if (isSafe(i, j) && matrix[i][j] != 0 && !visited[i][j]) {
		visited[i][j] = true;
		if (matrix[i][j] == 2) return true;

		bool up = isaPath(matrix, i - 1, j, visited); //recursively checks whether the fields around can lead us to the goal
		if (up) return true;

		bool left = isaPath(matrix, i, j - 1, visited);
		if (left) return true;

		bool down = isaPath(matrix, i + 1, j, visited);
		if (down) return true;

		bool right = isaPath(matrix, i, j + 1, visited);
		if (right) return true;
	}
	return false;
}

bool Map::findPath(int i, int j) {
	int matrix[ROW_NUMBER][COLUMN_NUMBER]; //generating a matrix of flags to help us find a path to the battery
	for (int i = 0; i < ROW_NUMBER; i++) {
		for (int j = 0; j < COLUMN_NUMBER; j++) {
			if (getFieldByPosition(ROW_NUMBER - i - 1, j)->isPassableGeneral()) matrix[i][j] = 3;//passble
			else matrix[i][j] = 0; //not passable
		}
	}
	matrix[i][j] = 1; //current position
	matrix[0][COLUMN_NUMBER - 1] = 2; //goal
	bool visited[ROW_NUMBER][COLUMN_NUMBER];
	memset(visited, 0, sizeof(visited));
	return isaPath(matrix, i, j, visited);
}


bool Map::checkMap() { //checking if it is possible to reach the battery from all passable fields
	for (int i = 0; i < ROW_NUMBER; i++) {
		for (int j = 0; j < COLUMN_NUMBER; j++) {
			if (i == ROW_NUMBER - 1 && j == COLUMN_NUMBER - 1) continue;
			if (getFieldByPosition(i, j)->isPassableGeneral()) {
				if (j != 0)if (fields[i * COLUMN_NUMBER + j - 1]->isPassableGeneral()){continue;} //if the previous field is passable and checked we don't need to check this one **optimization**
				if (i != 0)if (fields[(i - 1) * COLUMN_NUMBER + j]->isPassableGeneral()){continue;}
				if (findPath(ROW_NUMBER - i - 1, j))continue; //if it's not
				return false;
			}
		}
	}
	return true;
}

void Map::generateMaze() {
	while (true) {
		int horizontal = 0;
		int vertical = 0;
		initializeGrass();
		divide(0, 0, COLUMN_NUMBER - 1, ROW_NUMBER - 1, &horizontal, &vertical);
		if (checkMap()) return; 
	}
}

void Map::getFieldPosition(float x, float y, int& i, int& j) { //getting map index based on x and y coordinate
	int x1 = x - MAP_X_OFFSET;
	int y1 = y - MAP_Y_OFFSET;
	i = y1 / fieldHeight;
	j = x1 / fieldWidth;
}

bool Map::isValidField(int i, int j) {
	return !(i < 0 || j < 0 || i >= ROW_NUMBER || j >= COLUMN_NUMBER);
}

void Map::getFieldCoordinates(int i, int j, float& x, float& y) {
	x = MAP_X_OFFSET + fieldWidth / 2 + j * fieldWidth;
	y = MAP_Y_OFFSET + fieldHeight / 2 + i * fieldHeight;
}

void Map::restart() {
	Map* oldInstance = instance;
	instance = new Map();
	generateMaze();
	delete oldInstance;
}
