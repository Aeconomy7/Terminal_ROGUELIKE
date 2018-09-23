#include"Battle.h"
#include"functions.h"

#include<iostream>
#include<cstdlib>
#include<ctime>

//CONSTRUCTORS & DESTRUCTORS
Battle::Battle()
{

}

Battle::Battle(Character h, Monster m)
{
	hero = h;
	hero.validate_char();

	enemy = m;
	enemy.validate_monster();
}

//SETS

//GETS
Character Battle::get_hero(void)
{
	return hero;
}

Monster Battle::get_enemy(void)
{
	return enemy;
}

//FUNCTIONS
double Battle::generate_attack(int low, int high)
{
	srand(time(NULL));

	int r = rand() % ((high - low) + 1);
	r = low + r;

	//std::cout << low << " - " << high << std::endl;

	return (double)r;
}

void Battle::hero_attack(void)
{

}

void Battle::enemy_attack(void)
{

}

//returns 0 if it hits
//returns 1 if it misses
//returns 2 if it is critical hit
//type 0 = hero
//type 1 = enemy
int Battle::doesAttackHit(int type)
{
	srand(time(NULL));

	double accuracyf;
	int max_roll = 100;
	int crit_chance;
	int r;

	if(type == 0)
	{
		accuracyf = hero.get_acc() * 100.0;
	}
	else if(type == 1)
	{
		accuracyf = enemy.get_acc() * 100.0;
	}

	if(accuracyf > 100.0)
	{
		max_roll = accuracyf;
		crit_chance = (int)accuracyf - 100;
	}

	r = rand() % (max_roll + 1);

	//TESTING PURPOSES
	//std::cout << "\nAccuracy: " << accuracyf << "/100\n";
	//std::cout << "Hit @: " << r << "/100\n";
	//standby();

	if(r < (int)accuracyf && r <= 100)
	{
		//attack misses
		return 1;
	}
	else if(r >= (int)accuracyf && r <= 100)
	{
		//attack hits
		return 0;
	}
	else if(r > 100)
	{
		//attack crits
		return 2;
	}
}
