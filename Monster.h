#ifndef MONSTER_H
#define MONSTER_H

#include"Character.h"

#include<string>

class Monster : public Character
{
	friend class Battle;

	public:
		//Constructors and Destructors
		Monster();
		Monster(std::string nm, int ml) : Character(nm, ml)
		{
			mon_level = ml;
			mon_ident = " ";
			mon_type = " ";
		}
		//SETS
		void set_mon_ident(std::string);
		void set_mon_type(std::string);
		//GETS
		std::string get_mon_ident(void);
		std::string get_mon_type(void);
		//Functions
		void validate_monster(void);
	private:
		int mon_level;
		std::string mon_ident;
		std::string mon_type;
};

#endif
