#ifndef _CONSTANTS_H_
#define _CONSTANTS_H_

namespace Constants {
	//bmp paths
	const char* const BMP_PATH_PLAYER = ".\\TestData\\circle.bmp";
	const char* const BMP_PATH_ENEMY = ".\\TestData\\purplemonster.png";
	const char* const BMP_PATH_ENEMY_RANDOM = ".\\TestData\\pinkmonster.png";
	const char* const BMP_PATH_NPC = ".\\TestData\\chicken.png";
	const char* const BMP_PATH_GRASS = ".\\TestData\\terrainv1.bmp";
	const char* const BMP_PATH_WOOD = ".\\TestData\\terrainv1.bmp";
	const char* const BMP_PATH_BATTERY = ".\\TestData\\terrainv1.bmp";
	const char* const BMP_PATH_BUSH = ".\\TestData\\terrainv1.bmp";

	//bmp dimensions
	const int const BMP_COLUMNS_PLAYER = 1;
	const int const BMP_ROWS_PLAYER = 1;
	const int const BMP_COLUMNS_ENEMY = 1;
	const int const BMP_ROWS_ENEMY = 1;
	const int const BMP_COLUMNS_NPC = 1;
	const int const BMP_ROWS_NPC = 1;
	const int const BMP_COLUMNS_GRASS = 8;
	const int const BMP_ROWS_GRASS = 4;
	const int const BMP_COLUMNS_WOOD = 8;
	const int const BMP_ROWS_WOOD = 4;
	const int const BMP_COLUMNS_BATTERY = 8;
	const int const BMP_ROWS_BATTERY = 4;
	const int const BMP_COLUMNS_BUSH = 8;
	const int const BMP_ROWS_BUSH = 4;

	//bmp scales
	const float const SCALE_PLAYER = 0.55f;
	const float const SCALE_ENEMY = 0.23f;
	const float const SCALE_NPC = 0.16f;
	const float const SCALE_FIELD = 0.359375f;

	//bmp indexes
	const int const BMP_INDEX_GRASS = 16;
	const int const BMP_INDEX_WOOD = 5;
	const int const BMP_INDEX_BATTERY = 22;
	const int const BMP_INDEX_BUSH = 24;

	//map constants
	const int const ROW_NUMBER = 13;
	const int const COLUMN_NUMBER = 13;
	const int const BMP_WIDTH_FIELD = 128;
	const int const BMP_HEIGHT_FIELD = 128;
	const float const MAP_X_OFFSET = 250.0f;
	const float const MAP_Y_OFFSET = 100.0f;

	//constants for game tracking
	const int const GAME_OVER = true;
	const int const NOT_GAME_OVER = false;
	const int const START_TIME = 3000;
	const int const DAMAGE_COUNTER = 25;
	const int const SCORE_GAIN_COUNTER = 25;

	//characters
	const float const STEP_SIZE_PLAYER = 1.5f;
	const float const STEP_SIZE_RANDOM_ENEMY = 1.0f;
	const float const STEP_SIZE_ENEMY = 1.0f;
	const float const PLAYER_START_X = MAP_X_OFFSET + COLUMN_NUMBER * BMP_WIDTH_FIELD * SCALE_FIELD - (BMP_WIDTH_FIELD * SCALE_FIELD / 2);
	const float const PLAYER_START_Y = MAP_Y_OFFSET + ROW_NUMBER * BMP_HEIGHT_FIELD * SCALE_FIELD - (BMP_HEIGHT_FIELD * SCALE_FIELD / 2);
	const int const PLAYER_START_HEALTH = 50;
	
	//other constants
	const int const NUMBER_OF_ENEMIES = 2;
	const int const DAMAGE_BATTERY = -1;
	const char* const BMP_PATH_KEYBOARD = ".\\TestData\\arrows.png";
	const char* const BMP_PATH_C = ".\\TestData\\letter_c.png";
};
#endif
