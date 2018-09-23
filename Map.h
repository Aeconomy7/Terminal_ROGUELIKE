// Mason Hobbs
// mhobbs1996@gmail.com
// Class file for generating maps

#ifndef MAPS_H
#define MAPS_H

#include <iostream>
using namespace std;


// Map class contains the current map.
// Will have unique map objects, all of a certain size.
// Will be responsible for displaying the map, enemies/players included.

class Map {

	private:
		char tiles[25][60]; // Holds map
		string map_name;    // Map name
		int seed;	    // Seed for random generation
		int playerRow;	    // Player Y position
		int playerColumn;   // Player X position
		int floor;	    // Keeps track of current depth
		string map_types[5];// Adjectives for a map
		string map_scenes[5]; // Places for a map
		bool quit;	    // Found the stairs or quit the game?
		bool encounter;	    // Battle an enemy?
	public:
		Map(int seed_input); 			// Constructor
		void generateMap(); 			// Generate the map, including player, stairs, and terrain
		int generateRandomNum();		// Generates a number 0-3 for direction. Used in map generation for carving a walkable path
		void initialize_srand(int input);	// Change our seed each time a new map is called
		void setMapTypeAndScene();		// Makes the name of our map
		void printMap();			// Prints our map
		void gameCycle();			// Game cycle; uses map and allows player to move around
		void updateMap(char input);		// Changes map as characters move around
		void setPlayerRow(int input);		// Keeps track of player Y
		void setPlayerColumn(int input);	// Keeps track of player X
		int getPlayerRow();			// Returns player Y
		int getPlayerColumn();			// Returns player X
		void setQuit(bool input);		// Found the stairs or quit
		bool getQuit();				// For use in determinng when to move on to the next map
		void setFloor(int input);		// For storing what floor we're on
		int  getFloor();			// For retrieving what floor we're on
		void setEncounter(bool input);		// Determines if player is going to encounter a monster
		bool getEncounter();			// For checking if we need to encounter a monster
};

#endif
