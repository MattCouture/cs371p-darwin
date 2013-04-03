#ifndef Darwin_h
#define Darwin_h

#include <iostream>
#include <string>

class Creature {
	Creature();
        Creature(int, string);
	string turn();
}

class World {
  	World(int, int);

	void addCreature(string, int, int, int);

	bool isWall(int, int, int);

	bool isEmpty(int, int, int);

	bool isEnemy(int, int, int);

	bool creatureExists(int, int);

	void takeTurn();

	void print();
}
#endif

