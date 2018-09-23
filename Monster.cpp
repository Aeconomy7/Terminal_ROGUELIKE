#include"Monster.h"

#include<string>
#include<cmath>
#include<cstdlib>

Monster::Monster()
{

}

//SETS
void Monster::set_mon_ident(std::string ident)
{
	mon_ident = ident;
}

void Monster::set_mon_type(std::string type)
{
	mon_type = type;
}

//GETS
std::string Monster::get_mon_ident(void)
{
	return mon_ident;
}

std::string Monster::get_mon_type(void)
{
	return mon_type;
}

//FUNCTIONS
//MONSTERS MAY BE BALANCED HERE
void Monster::validate_monster(void)
{
	max_hp = 5+(Character::level*5)+(2*(rand() % 3));
	hp = max_hp;
	str = 3+(Character::level*(rand() % 4));
	acc = .45+(Character::level*.02)+(.01*(rand() % 3));
	att_range[0] = ceil(str*.5);
	att_range[1] = ceil(str*1);
}
