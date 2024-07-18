#include "stdafx.h"


struct pairValues {
	int first;
	int second;
	pairValues(int firstSet, int secondSet) {
		first = firstSet;
		second = secondSet;
	}
};

struct Node {
	double pathCost;
	double heuristics;
	int i;
	int j;
	vector<pairValues> path;
	Node(double p, double h, int i, int j, vector<pairValues>path1) {
		pathCost = p;
		heuristics = h;
		path = path1;
		path.push_back(pairValues(i,j));
		this->i = i;
		this->j = j;
	}
	~Node() {
		path.clear();
	}
};

EnemyMovement::EnemyMovement(Enemy* enemy) {
	this->enemy = enemy;
	backupX = RANDOMINT(0, ROW_NUMBER - 1);
	backupY = RANDOMINT(0, COLUMN_NUMBER - 1);
}

bool EnemyMovement::updateMovement(){
	Map* map = Map::getInstance();
	vector<Node*> nodes;
	CSimpleSprite* testSprite = enemy->getSprite();
	float x, y;
	testSprite->GetPosition(x, y);
	int i, j;
	map->getFieldPosition(x, y, i, j);
	int ip, jp;
	float xp, yp;
	CSimpleSprite* playerSprite = Characters::getPlayer()->getSprite();
	playerSprite->GetPosition(xp, yp);
	map->getFieldPosition(xp, yp, ip, jp);
	if (enemy->isOverlayed(xp, yp, playerSprite->GetWidth(), playerSprite->GetHeight(), SCALE_PLAYER)) return GAME_OVER; //collision with the player

	if (enemy->getIsRandomType()) {//a random type of enemy chases a random point until it reaches it
		while (!map->getFieldByPosition(backupX, backupY)->isPassableGeneral() || (i == backupX && j == backupY)) {
			backupX = RANDOMINT(0, ROW_NUMBER - 1);
			backupY = RANDOMINT(0, COLUMN_NUMBER - 1);
		}
		ip = backupX;
		jp = backupY;
	} else {//regular enemy chases the player unless unreachable
		if (!map->getFieldByPosition(ip, jp)->isPassableGeneral()) {
			while (!map->getFieldByPosition(backupX, backupY)->isPassableGeneral() || (i == backupX && j == backupY)) {
				backupX = RANDOMINT(0, ROW_NUMBER - 1);
				backupY = RANDOMINT(0, COLUMN_NUMBER - 1);
			}
			ip = backupX;
			jp = backupY;
		}
	}
	float stepSize = enemy->getIsRandomType() ? STEP_SIZE_RANDOM_ENEMY : STEP_SIZE_ENEMY;
	double distance = sqrt((ip - i) * (ip - i) + (jp - j) * (jp - j));
	int pathCost = 0;
	vector<pairValues> path;
	Node* node = new Node(0, distance, i, j, path);
	float fieldWidth = SCALE_FIELD * BMP_WIDTH_FIELD;
	vector<pairValues> visited;// keep track of already visited fields
	while (true) { //A* algorithm to get the shortest path
		visited.push_back(pairValues(node->i, node->j));
		if (node->i == ip && node->j == jp) {
			path = node->path;
			break;
		}

		if (map->isValidField(node->i + 1, node->j) && map->getFieldByPosition(node->i + 1, node->j)->isPassableGeneral()) { //if the field above is passable
			int ci = node->i + 1;
			int cj = node->j;
			bool getOut = false;
			for (int it = 0; it < visited.size(); it++) {
				if (visited[it].first == ci && visited[it].second == cj) { 
					getOut = true; 
					break;
				}
			}
			if (!getOut) {
				double distance = sqrt((ci - ip) * (ci - ip) + (cj - jp) * (cj - jp));
				Node* node1 = new Node(node->pathCost + 1, distance, ci, cj, node->path);
				nodes.push_back(node1); //add path to the list of paths
			}
		}
		if (map->isValidField(node->i, node->j + 1) && map->getFieldByPosition(node->i, node->j + 1)->isPassableGeneral()) { //if the field to the right is passable
			int ci = node->i;
			int cj = node->j + 1;
			bool getOut = false;
			for (int it = 0; it < visited.size(); it++) {
				if (visited[it].first == ci && visited[it].second == cj) { 
					getOut = true; 
					break; }
			}
			if (!getOut) {
				double distance = sqrt((ci - ip) * (ci - ip) + (cj - jp) * (cj - jp));
				Node* node1 = new Node(node->pathCost + 1, distance, ci, cj, node->path);
				nodes.push_back(node1); //add path to the list of paths
			}
		}
		if (map->isValidField(node->i, node->j - 1) && map->getFieldByPosition(node->i, node->j - 1)->isPassableGeneral()) { //if the field to the left is passable
			int ci = node->i;
			int cj = node->j - 1;
			bool getOut = false;
			for (int it = 0; it < visited.size(); it++) {
				if (visited[it].first == ci && visited[it].second == cj) { 
					getOut = true; 
					break; 
				}
			}
			if (!getOut){
				double distance = sqrt((ci - ip) * (ci - ip) + (cj - jp) * (cj - jp));
				Node* node1 = new Node(node->pathCost + 1, distance, ci, cj, node->path);
				nodes.push_back(node1); //add path to the list of paths
			}
		}
		if (map->isValidField(node->i - 1, node->j) && map->getFieldByPosition(node->i - 1, node->j)->isPassableGeneral()) { //if the field below is passable
			int ci = node->i - 1;
			int cj = node->j;
			bool getOut = false;
			for (int it = 0; it < visited.size(); it++) {
				if (visited[it].first == ci && visited[it].second == cj) { 
					getOut = true; 
					break; 
				}
			}
			if (!getOut) {
				double distance = sqrt((ci - ip) * (ci - ip) + (cj - jp) * (cj - jp));
				Node* node1 = new Node(node->pathCost + 1, distance, ci, cj, node->path);
				nodes.push_back(node1); //add path to the list of paths
			}
		}
		if (nodes.size() == 0) return NOT_GAME_OVER;
		int minIndex = 0;
		double minValue = 10000;
		for (int i = 0; i < nodes.size(); ++i) {
			const double currentSum = nodes[i]->pathCost + nodes[i]->heuristics;
			if (currentSum < minValue) {
				minValue = currentSum;
				minIndex = i;
			}
		}
		delete node;
		node = nodes[minIndex];
		nodes.erase(nodes.begin() + minIndex);
	}
	if (path.size() <= 1) return NOT_GAME_OVER;
	int nexti = path[1].first; //next i position for the enemy
	int nextj = path[1].second; //next j position for the enemy
	float xf, yf;
	map->getFieldCoordinates(nexti, nextj, xf, yf);
	xf = round(xf);
	yf = round(yf);
	testSprite->GetPosition(x, y);
	if (abs(x-xf) < abs(y-yf)) { //ensure that the enemy moves regularly
		if (xf > x) x += stepSize;
		else if (xf < x) x -= stepSize;
		else if (yf > y) y += stepSize;
		else if (yf < y) y -= stepSize;
	}else {
		if (yf > y) y += stepSize;
		else if (yf < y) y -= stepSize;
		else if (xf > x) x += stepSize;
		else if (xf < x) x -= stepSize;
	}
	testSprite->SetPosition(x, y); //move the enemy
	nodes.clear();
	return NOT_GAME_OVER;
}