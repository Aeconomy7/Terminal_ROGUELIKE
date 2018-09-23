#include"Character.h"
#include"rlutil.h"
#include"functions.h"
#include<string>
#include<iostream>
#include<iomanip>
#include<fstream>
#include<cmath>

//Constructors & Deconstructors
Character::Character()
{

}

Character::Character(std::string cn, int pn)
{
	char_name = cn;
	pin = pn;
	hp = 20;
	max_hp = 20;
	mana = 10;
	max_mana = 10;
	level = 1;
	exp = 0;
	total_exp = 0;
	etn = 25;
	str = 2;
	magic = 2;
	dex = 2;
	acc = 0.5;
	//avoid = 0.0;
	s_points = 4;
	gold = 0;
	gold_mult = 1.0;
	rich = 0;
	weapon_eqpd = false;
        armor_eqpd = false;
        boots_eqpd = false;
        str_scaling = 0.0;
        dex_scaling = 0.0;
        armor_res_scaling = 0.0;
        boots_res_scaling = 0.0;
	generic_res_scaling = 0.0;
	res_scaling = 0.0;
}

Character::~Character()
{

}

//SETS
void Character::set_char_name(std::string nm)
{
	char_name = nm;
}

void Character::set_hp(double h)
{
	hp = h;
}

void Character::set_mana(double m)
{
	mana = m;
}

void Character::set_gold(int g)
{
	gold = g;
}

void Character::set_str(int s)
{
	str = s;
}

void Character::set_magic(int m)
{
	magic = m;
}

void Character::set_dex(int d)
{
	dex = d;
}

void Character::set_acc(double ac)
{
	acc = ac;
}

/*void Character::set_avoid(double av)
{
	avoid = av;
}*/

void Character::set_level(int lvl)
{
	level = lvl;
}

void Character::set_str_scaling(double strscl)
{
        str_scaling = str_scaling + strscl;
}

void Character::set_dex_scaling(double dexscl) {
        dex_scaling = dex_scaling + dexscl;
}

void Character::set_generic_res_scaling(double gresscl) {
	generic_res_scaling = generic_res_scaling + gresscl;
}

void Character::set_res_scaling(double fresscl) {
	res_scaling = res_scaling + fresscl;
}

void Character::set_int_scaling(double intscl) {
	int_scaling = int_scaling + intscl;
}

void Character::set_armor_res_scaling(double armorresscl)
{
        armor_res_scaling = armor_res_scaling + armorresscl;
}

void Character::set_boots_res_scaling(double bootsresscl) {
	boots_res_scaling = boots_res_scaling + bootsresscl;
}

void Character::set_weapon_equipped(bool input) {
	weapon_eqpd = input;
}

void Character::set_armor_equipped(bool input) {
	armor_eqpd = input;
}

void Character::set_boots_equipped(bool input) {
	boots_eqpd = input;
}

void Character::add_weapon(int i, char n[], string t, string d, double v, double str, double dex, double intel, double res)
{
	weapons.insertItem(i, n, t, d, v, str, dex, intel, res);
}

void Character::add_armor(int i, char n[], string t, string d, double v, double str, double dex, double intel, double res)
{
	armor.insertItem(i, n, t, d, v, str, dex, intel, res);
}

void Character::add_boots(int i, char n[], string t, string d, double v, double str, double dex, double intel, double res)
{
	boots.insertItem(i, n, t, d, v, str, dex, intel, res);
}

void Character::add_misc(int i, char n[], string t, string d, double v, double str, double dex, double intel, double res) 
{
	misc.insertItem(i, n, t, d, v, str, dex, intel, res);
}

// ALL EQUIP FUNCTIONS
void Character::search_weapons(int input) {
	// Equipping!
	if(!get_weapon_equipped()) {
		set_str_scaling(weapons.searchItemStr(input));
		set_dex_scaling(weapons.searchItemDex(input));
		set_int_scaling(weapons.searchItemInt(input));
		set_generic_res_scaling(weapons.searchItemRes(input));
		set_res_scaling(get_armor_res_scaling() + get_boots_res_scaling() + get_generic_res_scaling());
		std::cout << "Successfully equipped. New scaling info: \nStr: " << get_str_scaling() << "\n";
		std::cout << "Dex: " << get_dex_scaling() << "\nInt: " << get_int_scaling() << "\nRes: " << get_res_scaling();
		set_weapon_equipped(true);
	}
	else {
		std::cout << "Weapon currently equipped. Removing...\n";
		set_str_scaling((get_str_scaling() - (2.00 * get_str_scaling())) + weapons.searchItemStr(input));
		set_dex_scaling((get_dex_scaling() - (2.00 * get_dex_scaling())) + weapons.searchItemDex(input));
		set_int_scaling((get_int_scaling() - (2.00 * get_int_scaling())) + weapons.searchItemInt(input));
		set_generic_res_scaling((get_generic_res_scaling() - (2.00 * get_generic_res_scaling())) + weapons.searchItemRes(input));
		set_res_scaling(get_armor_res_scaling() + get_boots_res_scaling() + get_generic_res_scaling());
                std::cout << "Successfully equipped. New scaling info: \nStr: " << get_str_scaling() << "\n";
                std::cout << "Dex: " << get_dex_scaling() << "\nInt: " << get_int_scaling() << "\nRes: " << get_res_scaling();
                set_weapon_equipped(true);

	}
	standby();
}

void Character::search_armor(int input) {
        // Equipping!
        if(!get_armor_equipped()) {
                set_str_scaling(armor.searchItemStr(input));
                set_dex_scaling(armor.searchItemDex(input));
                set_int_scaling(armor.searchItemInt(input));
                set_armor_res_scaling(armor.searchItemRes(input));
		set_res_scaling(get_armor_res_scaling() + get_boots_res_scaling() + get_generic_res_scaling());
                std::cout << "Successfully equipped. New scaling info: \nStr: " << get_str_scaling() << "\n";
                std::cout << "Dex: " << get_dex_scaling() << "\nInt: " << get_int_scaling() << "\nRes: " << get_res_scaling();
                set_armor_equipped(true);
        }
        else {
                std::cout << "Armor currently equipped. Removing...\n";
                set_str_scaling((get_str_scaling() - (2.00 * get_str_scaling())) + armor.searchItemStr(input));
                set_dex_scaling((get_dex_scaling() - (2.00 * get_dex_scaling())) + armor.searchItemDex(input));
                set_int_scaling((get_int_scaling() - (2.00 * get_int_scaling())) + armor.searchItemInt(input));
                set_armor_res_scaling((get_armor_res_scaling() - (2.00 * get_armor_res_scaling())) + armor.searchItemRes(input));
		set_res_scaling(get_armor_res_scaling() + get_boots_res_scaling() + get_generic_res_scaling());
                std::cout << "Successfully equipped. New scaling info: \nStr: " << get_str_scaling() << "\n";
                std::cout << "Dex: " << get_dex_scaling() << "\nInt: " << get_int_scaling() << "\nRes: " << get_res_scaling();
                set_armor_equipped(true);

        }
        standby();
}

void Character::search_boots(int input) {
        // Equipping!
        if(!get_boots_equipped()) {
                set_str_scaling(boots.searchItemStr(input));
                set_dex_scaling(boots.searchItemDex(input));
                set_int_scaling(boots.searchItemInt(input));
                set_boots_res_scaling(boots.searchItemRes(input));
		set_res_scaling(get_armor_res_scaling() + get_boots_res_scaling() + get_generic_res_scaling());
                std::cout << "Successfully equipped. New scaling info: \nStr: " << get_str_scaling() << "\n";
                std::cout << "Dex: " << get_dex_scaling() << "\nInt: " << get_int_scaling() << "\nRes: " << get_res_scaling();
                set_boots_equipped(true);
        }
        else {
                std::cout << "Boots currently equipped. Removing...\n";
                set_str_scaling((get_str_scaling() - (2.00 * get_str_scaling())) + boots.searchItemStr(input));
                set_dex_scaling((get_dex_scaling() - (2.00 * get_dex_scaling())) + boots.searchItemDex(input));
                set_int_scaling((get_int_scaling() - (2.00 * get_int_scaling())) + boots.searchItemInt(input));
                set_boots_res_scaling((get_boots_res_scaling() - (2.00 * get_boots_res_scaling())) + boots.searchItemRes(input));
		set_res_scaling(get_armor_res_scaling() + get_boots_res_scaling() + get_generic_res_scaling());
                std::cout << "Successfully equipped. New scaling info: \nStr: " << get_str_scaling() << "\n";
                std::cout << "Dex: " << get_dex_scaling() << "\nInt: " << get_int_scaling() << "\nRes: " << get_res_scaling();
                set_boots_equipped(true);

        }
        standby();
}

void Character::equip() {
        rlutil::cls();
	rlutil::setColor(1);
	border3();
        border();
	std::cout << "||             Equip/Use                 ||\n";
	border();
	border3();
	rlutil::setColor(7);
        std::cout << "\n(1): Weapons\n(2): Armor\n(3): Boots\n(4): Misc\n";
        char ans = ' ';
	rlutil::setColor(1);
        std::cout << "\nSELECTION: ";
        if(!(std::cin >> ans))
        {
                std::cout << "Input Error: Invalid input, please retry.\n";
                std::cin.clear();
                std::cin.ignore(10000, '\n');
        }
        // figure out which item to print/display
        int item_cat = ans - '0';

        if(item_cat == 1) {
                // Weapons
                show_weapons();
                std::cout << "\n\nITEM NUMBER TO EQUIP: ";
                if(!(std::cin >> ans))
                {
                        std::cout << "Input Error: Invalid input, please retry.\n";
                        std::cin.clear();
                        std::cin.ignore(10000, '\n');

                }
                int item_choice = ans - '0';
                search_weapons(item_choice);
        }

        else if(item_cat == 2) {
		// Armor
		show_armor();
		std::cout << "\n\nITEM NUMBER TO EQUIP: ";
		if(!(std::cin >> ans)) 
		{
			std::cout << "Input Error: Invalid input, please retry.\n";
			std::cin.clear();
			std::cin.ignore(10000, '\n');
		}
		int item_choice = ans - '0';
		search_armor(item_choice);
        }
        else if(item_cat == 3) {
		// Boots
                show_boots();
                std::cout << "\n\nITEM NUMBER TO EQUIP: ";
                if(!(std::cin >> ans))
                {
                        std::cout << "Input Error: Invalid input, please retry.\n";
                        std::cin.clear();
                        std::cin.ignore(10000, '\n');
                }
                int item_choice = ans - '0';
                search_boots(item_choice);

        }
        else if(item_cat == 4) {

        }
}

//GETS
std::string Character::get_char_name(void)
{
	return char_name;
}

int Character::get_pin(void)
{
	return pin;
}

double Character::get_hp(void)
{
	return hp;
}

double Character::get_max_hp(void)
{
	return max_hp;
}

double Character::get_mana(void)
{
	return mana;
}

double Character::get_max_mana(void)
{
	return max_mana;
}

long int Character::get_gold(void)
{
	return gold;
}

double Character::get_gold_mult(void)
{
	return gold_mult;
}

string Character::get_rich(void)
{
	string richness_rating[5] = {"Trash", "Poor", "Average", "Well-Off", "Wealthy as $#&%"};

	return richness_rating[rich];
}

int Character::get_rich_num(void)
{
	return rich;
}

int Character::get_level(void)
{
	return level;
}

int Character::get_exp(void)
{
	return exp;
}

long int Character::get_total_exp(void)
{
	return total_exp;
}

int Character::get_etn(void)
{
	return etn;
}

int Character::get_str(void)
{
	return str;
}

int Character::get_magic(void)
{
	return magic;
}

int Character::get_dex(void)
{
	return dex;
}

double Character::get_acc(void)
{
	return acc;
}

/*double Character::get_avoid(void)
{
	return avoid;
}*/

int Character::get_s_points(void)
{
	return s_points;
}

//bound = 0: low range
//bound = 1: high range
double Character::get_att_range(int bound)
{
	if(bound == 0)
	{
		return att_range[0];
	}
	else if(bound == 1)
	{
		return att_range[1];
	}
}

double Character::get_dmg() {
	return dmg;
}

double Character::get_def() {
	return def;
}

double Character::get_str_scaling() {
	return str_scaling;
}

double Character::get_dex_scaling() {
	return dex_scaling;
}

double Character::get_generic_res_scaling() {
	return generic_res_scaling;
}

double Character::get_int_scaling() {
	return int_scaling;
}

double Character::get_armor_res_scaling() {
	return armor_res_scaling;
}

double Character::get_boots_res_scaling() {
	return boots_res_scaling;
}

double Character::get_res_scaling() {
	return res_scaling;
}

bool Character::get_weapon_equipped() {
	return weapon_eqpd;
}

bool Character::get_armor_equipped() {
	return armor_eqpd;
}

bool Character::get_boots_equipped() {
	return boots_eqpd;
}

Inventory Character::get_weapons(void)
{
	return weapons;
}

Inventory Character::get_armor(void)
{
	return armor;
}

Inventory Character::get_boots(void)
{
	return boots;
}

Inventory Character::get_misc(void)
{
	return misc;
}

int Character::get_weapons_length() {
        return weapons.getLength();
}

int Character::get_armor_length() {
        return armor.getLength();
}

int Character::get_boots_length() {
        return boots.getLength();
}

int Character::get_misc_length() {
        return misc.getLength();
}

//Functions

//validate character function:
//needs to be called anytime a character is fetched from the list
//used to calculate current max_hp and exp needed to next level
void Character::validate_char(void)
{
	max_hp = (level*5) + 15;			//validate max hp
	max_mana = (10 + ((floor(level/5))*5)) + ((magic/2)-1);				//subject to change
	etn = level*10 + (level*level*level);		//validate exp to next level (CHANGE THIS)
	att_range[0] = ceil(str*.5);			//lower bound of range
	att_range[1] = ceil(str*1.5);			//upper bound of range
}

void Character::get_exp_bar(void)
{
	int exp_earned, exp_needed;
	double percent_earned;

	percent_earned = ((double)exp/(double)etn);	//% to next level
	exp_earned = (percent_earned*40);

	//to not give the impression that
	//you have leveled up 100% when you havent
	//and vice versa
	if(exp_earned == 40)
	{
		exp_earned = 39;
	}
	else if(exp_earned == 0 && exp != 0)
	{
		exp_earned = 1;
	}

	exp_needed = 40 - exp_earned;

	rlutil::setColor(14);
	std::cout << "[";

	rlutil::setColor(9);
	for(int i = 0; i < exp_earned; i++)
	{
		//rlutil::setBackgroundColor(15);
		std::cout << "#";
	}
	for(int i = 0; i < exp_needed; i++)
	{
		//rlutil::setBackgroundColor(0);
		rlutil::setColor(7);
		std::cout << "-";
	}

	rlutil::setBackgroundColor(0);
	rlutil::setColor(14);
	std::cout << "]\n";
}

void Character::get_hp_bar(void)
{
	//ADD BACKGROUND COLOURS

	int curr_hp, missing_hp;
	double percent_hp;

	percent_hp = (hp/max_hp);
	curr_hp = (percent_hp*40);
	missing_hp = 40 - curr_hp;

	if(curr_hp == 0)
	{
		curr_hp = 1;
		missing_hp = 39;
	}

	rlutil::setColor(9);
	std::cout << "[";

	rlutil::setColor(12);
	for(int i = 0; i < curr_hp; i++)
	{
		//rlutil::setBackgroundColor(12);
		std::cout << "@";
	}
	for(int i = 0; i < missing_hp; i++)
	{
		//rlutil::setBackgroundColor(0);
		rlutil::setColor(7);
		std::cout << "-";
	}

	rlutil::setBackgroundColor(0);
	rlutil::setColor(9);
	std::cout << "]\n";
}

void Character::get_mana_bar(void)
{
	int curr_mana, missing_mana;
	double percent_mana;

	percent_mana = (mana/max_mana);
	curr_mana = (percent_mana*40);
	missing_mana = 40 - curr_mana;

	/*if(curr_mana == 0)
	{
		curr_mana = 1;
		missing_mana = 39;
	}*/

	rlutil::setColor(5);
	std::cout << "[";

	rlutil::setColor(11);
	for(int i = 0; i < curr_mana; i++)
	{
		//rlutil::setBackgroundColor(6);
		std::cout << "@";
	}
	for(int i = 0; i < missing_mana; i++)
	{
		//rlutil::setBackgroundColor(0);
		rlutil::setColor(7);
		std::cout << "-";
	}

	rlutil::setBackgroundColor(0);
	rlutil::setColor(5);
	std::cout << "]\n";
}

void Character::inc_hp(double h)
{
	hp = hp + h;

	if(hp > max_hp)
	{
		hp = max_hp;
	}
}

void Character::dec_hp(double h)
{
	hp = hp - h;
}

void Character::inc_mana(double m)
{	
	mana = mana + m;

	if(mana > max_mana)
	{
		mana = max_mana;
	}
}

void Character::dec_mana(double m)
{
	mana = mana - m;
}


void Character::inc_gold(long int g)
{
	gold = gold + g;
}

void Character::dec_gold(long int g)
{
	gold = gold - g;
}

void Character::inc_gold_mult(void)
{
	gold_mult = gold_mult + 0.25;
}

void Character::inc_rich(void)
{
	rich = rich + 1;
}

void Character::inc_exp(int e)
{
	exp += e;
	total_exp += e;

	level_up_check:
	if(exp >= etn)
	{
		exp -= etn;
		level_up();
		hp = max_hp;
		mana = max_mana;

		goto level_up_check;
	}
}

void Character::level_up(void)
{
	rlutil::setColor(11);
	std::cout << "\n\t   ";
	//rlutil::setBackgroundColor(10);
	std::cout << level;
	rlutil::setColor(1);
	std::cout << " <> ";
	rlutil::setColor(10);
	std::cout << "LEVEL UP";
	rlutil::setColor(1);
	std::cout << " <> ";
	rlutil::setColor(11);
	std::cout << level+1;
	//rlutil::setBackgroundColor(0);
	std::cout << "\n";
	level++;
	s_points += 4;
	validate_char();
}

void Character::inc_str(void)
{
	if(s_points > 0)
	{
		str += 1;
		s_points--;
	}
	else
	{
		std::cout << "You don't have any skill points!\n";
	}
}

void Character::inc_magic(void)
{
	if(s_points > 0)
	{
		magic += 1;
		s_points--;
		validate_char();
		inc_mana(1);
	}
	else
	{
		std::cout << "You don't have any skill points!\n";
	}
}

void Character::inc_dex(void)
{
	if(s_points > 0)
	{
		dex += 1;
		s_points--;
	}
	else
	{
		std::cout << "You don't have any skill points!\n";
	}
}

void Character::inc_acc(void)
{
	if(s_points > 0)
	{
		if(acc < 1.50)
		{
			acc += 0.02;
			s_points--;
		}
		else
		{
			std::cout << "You already have max accuracy!\n";
		}
	}
	else
	{
		std::cout << "You don't have enough skill points!\n";
	}
}

/*void Character::inc_avoid(void)
{
	if(s_points > 0)
	{
		avoid += 0.01;
		s_points--;
	}
	else
	{
		std::cout << "You don't have any skill points!\n";
	}
}*/

//returns true if dead
//returns false if alive
bool Character::isDead(void)
{
	if(hp <= 0)
	{
		hp = 0;
		return true;
	}
	else
	{
		return false;
	}
}

void Character::show_weapons(void) 
{
	weapons.printList();
}

void Character::show_armor(void)
{
	armor.printList();
}

void Character::show_boots(void)
{
	boots.printList();
}

void Character::show_misc(void)
{
	misc.printList();
}

//Operator Overloads
std::fstream& operator<<(std::fstream& os, const Character& chr_o)
{
	os << std::setprecision(2) << std::fixed;
	os << chr_o.char_name << " ";
	os << chr_o.pin << " ";
	os << chr_o.hp << " ";
	os << chr_o.mana << " ";
	os << chr_o.level << " ";
	os << chr_o.exp << " ";
	os << chr_o.total_exp << " ";
	os << chr_o.str << " ";
	os << chr_o.magic << " ";
	os << chr_o.dex << " ";
	os << chr_o.acc << " ";
	//os << chr_o.avoid << " ";
	os << chr_o.s_points << " ";
	os << chr_o.gold << " ";
	os << chr_o.gold_mult << " ";
	os << chr_o.rich << std::endl;
	return os;
}

std::fstream& operator>>(std::fstream& is, Character& chr_i)
{
	is >> chr_i.char_name;	//possibly not neccesary
	is >> chr_i.pin;
	is >> chr_i.hp;
	is >> chr_i.mana;
	is >> chr_i.level;
	is >> chr_i.exp;
	is >> chr_i.total_exp;
	is >> chr_i.str;
	is >> chr_i.magic;
	is >> chr_i.dex;
	is >> chr_i.acc;
	//is >> chr_i.avoid;
	is >> chr_i.s_points;
	is >> chr_i.gold;
	is >> chr_i.gold_mult;
	is >> chr_i.rich;
	return is;
}

/*std::ostream& operator<<(std::ostream& os, const Character& chr_o)
{
	os << chr_o.char_name << " ";
	os << chr_o.pin << " ";
	os << chr_o.hp << " ";
	os << chr_o.level << " ";
	os << chr_o.exp << " ";
	os << chr_o.str << " ";
	os << chr_o.acc << " ";
	os << chr_o.avoid << " ";
	os << chr_o.s_points << std::endl;
	return os;
}*/
