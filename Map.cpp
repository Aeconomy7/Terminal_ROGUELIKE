// Mason Hobbs
// mhobbs1996@gmail.com
// Implementation file for generating maps
// "rlutil.h" created by Tapio: https://github.com/tapio/rlutil/

#include "Map.h"

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "rlutil.h"
#include "unistd.h"
#include "termios.h"
using namespace std;

// Change in Map.h as well!
int MAP_HEIGHT = 25;
int MAP_WIDTH = 60;
int mons_level;
void Map::gameCycle() {
	rlutil::cls();

	// Makes the input not buffered so we don't have to press enter
	struct termios old_tio, new_tio;
	unsigned char input;
	tcgetattr(STDIN_FILENO, &old_tio);

	// keep old settings
	new_tio = old_tio;

	// disable buffered input
	new_tio.c_lflag &=(~ICANON & ~ECHO);

	// set new settings
	tcsetattr(STDIN_FILENO, TCSANOW, &new_tio);

	// get input
	while(!getQuit()) {
		printMap();
		cout << "# W=UP -- A=LEFT -- S=DOWN -- D=RIGHT  #" << endl;
		cout << "# Q=QUIT                               #" << endl;
		input = getchar();
		cout << "\nEntered: " << input;
		// parse input
		if(input == 'q' || input == 'Q')
			setQuit(true);
		else {
			updateMap(input);
			if(getEncounter())
				break;
		}
		rlutil::cls();
	}

	// restore old settings
	tcsetattr(STDIN_FILENO, TCSANOW, &old_tio);

}

void Map::updateMap(char input) {
	bool movement = false;
	int spawnMonster = rand() % 30; // 1 in 30 chance to spawn a monster every time we successfully move
	// Up
	if(input == 'w' || input == 'W') {
		// Check if player can actually move there (is there an empty space?)
		if(tiles[getPlayerRow() - 1][getPlayerColumn()] != '#' && tiles[getPlayerRow() - 1][getPlayerColumn()] != '@') {
			// Did player encounter stairs? Exit the level if so!
			if(tiles[getPlayerRow() - 1][getPlayerColumn()] == 'E')
				setQuit(true);
			else {
				// If so, great! Move them and update map
				tiles[getPlayerRow() - 1][getPlayerColumn()] = 'P';
				tiles[getPlayerRow()][getPlayerColumn()] = ' ';
				// Update player position
				setPlayerRow(getPlayerRow() - 1);
				movement = true;
			}
		}
	}
	// Left
	if(input == 'a' || input == 'A') {
		// Check if player can actually move left(Is there an empty space?)
		if(tiles[getPlayerRow()][getPlayerColumn()-1] != '#' && tiles[getPlayerRow()][getPlayerColumn()-1] != '@') {
			// Did player encounter stairs? Exit the level if so!
			if(tiles[getPlayerRow()][getPlayerColumn()-1] == 'E')
				setQuit(true);
			else {
				// If so, great! Move them and update map
				tiles[getPlayerRow()][getPlayerColumn()-1] = 'P';
				tiles[getPlayerRow()][getPlayerColumn()] = ' ';
				// Update player position
				setPlayerColumn(getPlayerColumn()-1);
				movement = true;
			}
		}
	}
	// Down
	if(input == 's' || input == 'S') {
		// Check if player can actually move left(Is there an empty space?)
		if(tiles[getPlayerRow()+1][getPlayerColumn()] != '#' && tiles[getPlayerRow()+1][getPlayerColumn()] != '@') {
			// Did player encounter stairs? Exit the level if so!
			if(tiles[getPlayerRow()+1][getPlayerColumn()] == 'E')
				setQuit(true);
			else {
				// If so, great! Move them and update map
				tiles[getPlayerRow()+1][getPlayerColumn()] = 'P';
				tiles[getPlayerRow()][getPlayerColumn()] = ' ';
				// Update player position
				setPlayerRow(getPlayerRow()+1);
				movement = true;
			}
		}
	}

	// Right
	if(input == 'd' || input == 'D') {
		// Check if player can actually move left(Is there an empty space?)
		if(tiles[getPlayerRow()][getPlayerColumn()+1] != '#' && tiles[getPlayerRow()][getPlayerColumn()+1] != '@') {
			// Did player encounter stairs? Exit the level if so!
			if(tiles[getPlayerRow()][getPlayerColumn()+1] == 'E')
				setQuit(true);
			else {
				// If so, great! Move them and update map
				tiles[getPlayerRow()][getPlayerColumn()+1] = 'P';
				tiles[getPlayerRow()][getPlayerColumn()] = ' ';
				// Update player position
				setPlayerColumn(getPlayerColumn()+1);
				movement = true;
			}
		}
	}
	// Check for a random monster encounter
	if(movement && spawnMonster == 4) {
		setEncounter(true);
	}
	else
		setEncounter(false);
} // End updateMap

Map::Map(int seed_input) {
	// Create a blank map
	for(int row = 0; row < MAP_HEIGHT; row++) {
		for(int col = 0; col < MAP_WIDTH; col++) {
			tiles[row][col] = '_';
		}

	}
	// Map name options
	map_types[0] = "Dark";
	map_types[1] = "Cold";
	map_types[2] = "Desolate";
	map_types[3] = "Unforgiving";
	map_types[4] = "Terrifying";

	// Map scene options
	map_scenes[0] = "Cavern";
	map_scenes[1] = "Hall";
	map_scenes[2] = "Fortress";
	map_scenes[3] = "Chamber";
	map_scenes[4] = "Embrace";

	// Seed for random number generations
	initialize_srand(seed_input);

	// Make a name for our map
	setMapTypeAndScene();

	setQuit(false);
}

void Map::setMapTypeAndScene() {
	// generate two random numbers between 0 and 4
	int map_type_seed = rand() % 5;
	int map_scene_seed = rand() % 5;
	map_name = map_types[map_type_seed] + " " + map_scenes[map_scene_seed];

}

// Generate our map
void Map::generateMap() {

	bool made_path = false;

	// Fill edges with a wall
	for(int row = 0; row < MAP_HEIGHT; row++) {
		for(int col = 0; col < MAP_WIDTH; col++) {
			// fill entire row with wall if row is top or bottom of map
			if(row == 0 || row == MAP_HEIGHT-1)
				tiles[row][col] = '#';
			// fill entire row with wall if colum is left or right of map
			else if(col == 0 || col == MAP_WIDTH-1)
				tiles[row][col] = '#';
			else
				tiles[row][col] = '@';
		}

	}

	tiles[1][1] = ' ';
	// Now carve a path through the map, twice, starting at opposite corners
	// Top left
	for(int row = 1; row < MAP_HEIGHT-1; row++) {
		for(int col = 1; col < MAP_WIDTH-1; col++) {
			made_path = false;
			while(!made_path) {
			// decide which direction to go
				// 0 = NORTH
				// 1 = WEST
				// 2 = SOUTH
				// 3 = EAST
				int direction = generateRandomNum();
				if(direction == 0) {
					if(tiles[row-1][col] != '#')  {
						tiles[row-1][col] = ' ';
						made_path = true;
					}
				}

				else if(direction == 1) {
					if(tiles[row][col-1] != '#') {
						tiles[row][col-1] =' ';
						made_path = true;
					}
				}

				else if(direction == 2) {
					if(tiles[row+1][col] != '#') {
						tiles[row+1][col] = ' ';
						made_path = true;
					}
				}

				else if(direction == 3) {
					if(tiles[row][col+1] != '#') {
						tiles[row][col+1] = ' ';
						made_path = true;
					}
				}
			}
		}
	}
	tiles[23][58] = ' ';
	// Bottom right corner
	for(int row = 23; row > 1; row-=2) {
		for(int col = 59; col > 1; col-=2) {
			made_path = false;
			while(!made_path) {
			// decide which direction to go
				// 0 = NORTH
				// 1 = WEST
				// 2 = SOUTH
				// 3 = EAST
				int direction = generateRandomNum();
				if(direction == 0) {
					if(tiles[row-1][col] != '#')  {
						tiles[row-1][col] = ' ';
						made_path = true;
					}
				}

				else if(direction == 1) {
					if(tiles[row][col-1] != '#') {
						tiles[row][col-1] =' ';
						made_path = true;
					}
				}

				else if(direction == 2) {
					if(tiles[row+1][col] != '#') {
						tiles[row+1][col] = ' ';
						made_path = true;
					}
				}

				else if(direction == 3) {
					if(tiles[row][col+1] != '#') {
						tiles[row][col+1] = ' ';
						made_path = true;
					}
				}
			}
		}
	}
	// Spawn the player on a random tile
	int playerX = rand() % (MAP_WIDTH-1);
	int playerY = rand() % (MAP_HEIGHT-1);
	// Check to see that generated values are within bounds
	bool inBoundsX = false;
	bool inBoundsY = false;
	while(!inBoundsX && !inBoundsY) {

		if(playerX == 0 || playerX == MAP_WIDTH)
			playerX = rand() % (MAP_WIDTH-1);
		else
			inBoundsX = true;

		if(playerY == 0 || playerY == MAP_HEIGHT)
			playerY = rand() % (MAP_HEIGHT-1);
		else
			inBoundsY = true;

	}

	setPlayerRow(playerY);
	setPlayerColumn(playerX);
	tiles[playerY][playerX] = 'P';

	// Spawn the exit stairs on a random tile
	int stairsX = rand() % (MAP_WIDTH-1);
	int stairsY = rand() % (MAP_HEIGHT-1);
	// Check to see that generated values are within bounds
	bool inStairsBoundsX = false;
	bool inStairsBoundsY = false;
	while(!inStairsBoundsX && !inStairsBoundsY) {

		if(stairsX == 0 || stairsX == MAP_WIDTH)
			stairsX = rand() % (MAP_WIDTH-1);
		else
			inStairsBoundsX = true;

		if(stairsY == 0 || stairsY == MAP_HEIGHT)
			stairsY = rand() % (MAP_HEIGHT-1);
		else
			inStairsBoundsY = true;

	}


	tiles[stairsY][stairsX] = 'E';

} // End function generateMap



// Change value of srand by 1 every time its called to make unique maps
void Map::initialize_srand(int input) {
	srand(input);
}
// Generates a number 0-3
int Map::generateRandomNum() {
	int generated_value;

	generated_value = rand() % 4;

	return generated_value;
}

// Print our map
void Map::printMap() {

/*enum {
	BLACK,
	BLUE,
	GREEN,
	CYAN,
	RED,
	MAGENTA,
	BROWN,
	GREY,
	DARKGREY,
	LIGHTBLUE,
	LIGHTGREEN,
	LIGHTCYAN,
	LIGHTRED,
	LIGHTMAGENTA,
	YELLOW,
	WHITE
}; */
	rlutil::setColor(15);
	for(int i = 0; i < MAP_WIDTH; i++)
		cout << "#";
	cout << "\n# " << map_name << " -- Floor " << getFloor() << endl;
	for(int row = 0; row < MAP_HEIGHT; row++) {
		for(int col = 0; col < MAP_WIDTH; col++) {
	  		if(tiles[row][col] == '#')
				rlutil::setColor(15);
			else if(tiles[row][col] == '@')
			{
				rlutil::setBackgroundColor(9);
				rlutil::setColor(6);
			}
			else if(tiles[row][col] == '_')
				rlutil::setColor(9);
	  		else if(tiles[row][col] == 'P')
				rlutil::setColor(10);
			else if(tiles[row][col] == 'E')
				rlutil::setColor(14);

			cout << tiles[row][col];
			rlutil::setBackgroundColor(0);
		}
		cout << endl;
	}
	rlutil::setColor(3);
}

// Simple setters/getters

void Map::setPlayerRow(int input) {
	playerRow = input;
}
void Map::setPlayerColumn(int input) {
	playerColumn = input;
}

int Map::getPlayerRow() {
	return playerRow;
}
int Map::getPlayerColumn() {
	return playerColumn;
}

void Map::setQuit(bool input) {
	quit = input;
}
bool Map::getQuit() {
	return quit;
}

void Map::setFloor(int input) {
	floor = input;
}
int Map::getFloor() {
	return floor;
}

void Map::setEncounter(bool input) {
	encounter = input;
}
bool Map::getEncounter() {
	return encounter;
}
