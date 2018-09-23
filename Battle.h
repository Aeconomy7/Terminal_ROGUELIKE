#ifndef BATTLE_H
#define BATTLE_H

#include"Monster.h"

class Battle
{
	friend class Character;
	friend class Monster;

	public:
		//Constructors & Destructors
		Battle();
		Battle(Character, Monster);
		//SETS
		//GETS
		Character get_hero(void);
		Monster get_enemy(void);
		//Functions
		double generate_attack(int, int);
		void hero_attack(void);
		void enemy_attack(void);
		int doesAttackHit(int);
	private:
		Character hero;
		Monster enemy;
		bool turn;	//0 is hero, 1 is enemy
};

#endif
