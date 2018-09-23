#include"functions.h"
#include"rlutil.h"
#include"unistd.h"
#include"termios.h"

#include<string>
#include<ctime>
#include<cstdlib>
#include<iostream>
#include<iomanip>
#include<fstream>
#include<cstring>
#include<cmath>

//MENU FUNCTIONS
//Border functions
void border(void)
{
	rlutil::setColor(2);
	std::cout << "||				         ||\n";
}

void border2(void)
{
	rlutil::setColor(11);
	std::cout << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%\n";
}

void border3(void)
{
	rlutil::setColor(10);
	std::cout << "&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&\n";
}

void border4(void)
{
	rlutil::setColor(3);
	std::cout << "___________________________________________\n";
}

void versus(void)
{
	rlutil::setColor(5);
	std::cout << "<	   V      V      SSS		  >\n";
	std::cout << "<	    V    V      S   		  >\n";
	std::cout << "<	     V  V        SSS		  >\n";
	std::cout << "<	      VV    ..      S		  >\n";
	std::cout << "<	      V     ..   SSS		  >\n";
}

void clear_screen(void)
{
	std::cout << "\033[2J\033[1;1H";
}

void standby(void)
{
	struct termios old_tio, new_tio;
	unsigned char input;
	tcgetattr(STDIN_FILENO, &old_tio);

	new_tio = old_tio;

	new_tio.c_lflag &= (~ICANON & ~ECHO);

	tcsetattr(STDIN_FILENO, TCSANOW, &new_tio);

	std::cout << "\nPress any key to continue...\n";
	std::getchar();
	std::cin.ignore();
	std::cin.clear();

	//OLD SETTINGS: buffered
	tcsetattr(STDIN_FILENO, TCSANOW, &old_tio);
}

//Main Menu
void main_menu(void)
{
	clear_screen();
	border2();
	border();
	std::cout << "||		MAIN MENU                ||\n";
	border();
	border2();
	rlutil::setColor(7);
	std::cout << "\n(1): Create a new character\n";
	std::cout << "(2): Login to an existing character\n\n";
	std::cout << "(Q): Quit\n\n";
	border2();
}

void character_menu(void)
{
	clear_screen();
	border3();
	border();
	std::cout << "||	    CHARACTER MENU               ||\n";
	border();
	border3();
	rlutil::setColor(7);
	std::cout << "\n(1): View character statistics\n";
	std::cout << "(2): Spend skill points\n\n";
//	std::cout << "(3): View inventory\n";
	std::cout << "(4): Return to map\n\n";
	std::cout << "(S): Shop\n";
	std::cout << "(Q): Logout\n\n";
	border3();
}

void shop_menu(Character c)
{
	//FULL RESTORE COST
	long int cost1;
	cost1 = ((c.get_max_mana() - c.get_mana())*2) + ((c.get_max_hp() - c.get_hp())*2);

	//RICHNESS LEVEL COST
	long int cost2;
	if(c.get_rich_num() == 0)
	{
		cost2 = 200;
	}
	else if(c.get_rich_num() == 1)
	{
		cost2 = 400;
	}
	else if(c.get_rich_num() == 2)
	{
		cost2 = 1200;
	}
	else if(c.get_rich_num() == 3)
	{
		cost2 = 20000;
	}

	//GOLD MULTIPLIER COST
	long int cost3;
	cost3 = 25 * ((c.get_gold_mult()/0.25)-3);

	clear_screen();
	border3();
	border();
	std::cout << "||	        SHOP MENU                ||\n";
	border();
	std::cout << "||	    ";
	rlutil::setColor(14);
	std::cout << "Current Gold: ";
	rlutil::setColor(2);
	std::cout << std::setw(15) << std::left << c.get_gold() << "||\n";
	border();
	border3();
	rlutil::setColor(10);
	std::cout << "\n   (1): FULL RESTORE\n";
	rlutil::setColor(7);
	std::cout << "\t   -> COST: " << cost1 << "\n";
	rlutil::setColor(13);
	std::cout << "\n   (2): QUICK RESTORE\n";
	rlutil::setColor(7);
	std::cout << "\t   -> COST: " << 25 << "\n";
	rlutil::setColor(11);
	std::cout << "\n   (3): INCREASE GOLD MULTIPLIER\n";
	rlutil::setColor(7);
	std::cout << "\t   -> COST: " << cost3 << "\n";
	if(c.get_rich_num() < 4)
	{
		rlutil::setColor(14);
		std::cout << "\n   (4): INCREASE RICHNESS LEVEL\n";
		rlutil::setColor(7);
		std::cout << "\t   -> COST: " << cost2 << "\n\n";
	}
	std::cout << "\n   (Q): Return to CHARACTER MENU\n\n";
	border3();
}

void magic_menu(Character c)
{
	clear_screen();
	border3();
	border2();
	rlutil::setColor(7);
	std::cout << "\nCurrent Magic Stat:   ";
	rlutil::setColor(11);
	std::cout << c.get_magic();
	rlutil::setColor(7);
	std::cout << "\n\nMana: (" << c.get_mana() << " / " << c.get_max_mana() << ")\n";
	c.get_mana_bar();
	rlutil::setColor(7);
	if(c.get_magic() < 3)
	{
		std::cout << "\n   You have no spells unlocked yet!\n\n";
	}
	if(c.get_magic() >= 3)
	{
		rlutil::setColor(10);
		std::cout << "\n   (1): HEAL";
		rlutil::setColor(7);
		std::cout << "\n\t   -> COST: 5 Mana";
		std::cout << "\n\t   -> Heals between " << c.get_magic() - 2 << " - " << c.get_magic() + 2 << "\n\n";
	}
	if(c.get_magic() >= 5)
	{
		rlutil::setColor(9);
		std::cout << "   (2): RESEARCH MONSTER";
		rlutil::setColor(7);
		std::cout << "\n\t   -> COST: 2 Mana";
		std::cout << "\n\t   -> Reveals monster information\n\n";
	}
	if(c.get_magic() >= 10)
	{
		rlutil::setColor(12);
		std::cout << "   (3): TARGETED COMBUSTION";
		rlutil::setColor(7);
		std::cout << "\n\t   -> COST: 10 Mana";
		std::cout << "\n\t   -> Successfully deals " << 15 + c.get_magic() << " damage\n\n";
	}
	if(c.get_magic() >= 12)
	{
		rlutil::setColor(11);
		std::cout << "   (4): EMPOWERED LIFESTEAL";
		rlutil::setColor(7);
		std::cout << "\n\t   -> COST: 7 Mana";
		std::cout << "\n\t   -> Empowers next attack with\n\t\t 100% Lifesteal\n\n";
	}
	if(c.get_magic() >= 20)
	{
		rlutil::setColor(14);
		std::cout << "   (5): JACKPOT HIT";
		rlutil::setColor(7);
		std::cout << "\n\t   -> COST: 12 Mana";
		std::cout << "\n\t   -> Empowers next attack with\n\t\t" << 100 + (25 * ((c.get_gold_mult()/0.25)-4)) << "% Gold-gain\n\n";
	}
	std::cout << "   (Q): Return to Battle\n\n";
	border2();
	border3();
}

//CHARACTER FUNCTIONS
bool isCharacter(std::string name, std::fstream& chars)
{
	chars.close();
	chars.open("Characters.txt");

	Character temp;
	bool exist = false;

	while(chars >> temp)
	{
		if(temp.get_char_name() == name)
		{
			exist = true;
		}
	}

	return exist;
}

//save character to file
void save_char(Character c, std::fstream& chars)
{
	chars.close();
	chars.open("Characters.txt", std::ios::app);

	chars << c;
}

void remove_char(std::string cnm, std::fstream& chars, std::fstream& temp)
{
	chars.close();
	chars.open("Characters.txt");
	temp.open("temp.txt", std::ios::app);

	Character del;

	while(chars >> del)
	{
		if(del.get_char_name() == cnm)
		{
		}
		else
		{
			temp << del;
		}
	}

	temp.close();
	chars.close();
	std::remove("Characters.txt");
	std::rename("temp.txt", "Characters.txt");
}

void create_char(std::fstream& chars)
{
	clear_screen();

	chars.close();
	chars.open("Characters.txt", std::ios::app);

	std::string cname;
	int pn;
	char ans;

	//Name of the new character
	name:
	std::cout << "Enter the name of your character ('Q' for Main Menu):\n\t";
	if(!(std::cin >> cname))
	{
		std::cout << "Input Error: Unnacceptable name, please retry.\n";
		std::cin.clear();
		std::cin.ignore(10000, '\n');

		goto name;
	}

	if(cname == "Q" || cname == "q")
	{
		return;
	}

	if(isCharacter(cname, chars))
	{
		std::cout << "That name is already in use, please choose another!\n";

		goto name;
	}

	//Users pin (unencrypted LOL)
	pin:
	std::cout << "Enter your new PIN for your character:\n";
	std::cout << "(This will be what you use to login, REMEMBER IT)\n";
	if(!(std::cin >> pn))
	{
		std::cout << "Input Error: Pin must be number (0-9) combination, please retry.\n";
		std::cin.clear();
		std::cin.ignore(10000, '\n');

		goto pin;
	}

	sure:
	std::cout << "Continue (Y/N)?\n\n";
	std::cout << "Character Name:\t" << cname << std::endl;
	std::cout << "Character Pin:\t" << pn << std::endl;
	if(!(std::cin >> ans))
	{
		std::cout << "Input Error: Enter Y or N, please retry.\n";
		std::cin.clear();
		std::cin.ignore(10000, '\n');

		goto sure;
	}

	if(ans == 'Y' || ans == 'y')
	{
		Character new_char(cname, pn);
		new_char.validate_char();
		save_char(new_char, chars);

		return;
	}
	else if(ans == 'n' || ans == 'N')
	{
		return;
	}
	else
	{
		goto sure;
	}
}

//fetch character from file
Character fetch_char(std::string name, std::fstream& chars)
{
	chars.close();
	chars.open("Characters.txt");

	Character fetch;

	while(chars >> fetch)
	{
		if(fetch.get_char_name() == name)
		{
			return fetch;
		}
	}

//	std::cout << "Could not find any character named '" << name <<"'\n";

	Character NULLc("NULL_CHAR_NAME", 0001);

	return NULLc;
}

//login to character
Character login(std::fstream& chars)
{
	clear_screen();

	Character chr;

	std::string cname;
	int pn;
	bool flag = true;

	login:
	std::cout << "Character Name:\n\t";
	if(!(std::cin >> cname))
	{
		std::cout << "Input Error: Invalid input, please retry.\n";
		std::cin.clear();
		std::cin.ignore(10000, '\n');

		goto login;
	}

	chr = fetch_char(cname, chars);
	if(chr.get_char_name() == "NULL_CHAR_NAME")
	{
		flag = false;
	}

	std::cout << "Character PIN:\n\t";
	if(!(std::cin >> pn))
	{
		std::cout << "Input Error: Invalid input, please retry.\n";
		std::cin.clear();
		std::cin.ignore(10000, '\n');

		goto login;
	}

	if(pn == chr.get_pin() && flag == true)
	{
		std::cout << "LOGIN SUCCESSFUL\n";
		standby();

		return chr;
	}
	else
	{
		std::cout << "INCORRECT CHARACTER NAME OR PIN\n";
		Character NULLc("NULL_CHAR_NAME", 0001);
		standby();

		return NULLc;
	}
}

//print character stats
void print_char(Character c)
{
	clear_screen();
	border3();
	border2();
	border4();
	std::cout << std::endl;
	rlutil::setColor(7);
	std::cout << "Character Name:\n\t" << c.get_char_name();
	std::cout << "\n\nLEVEL " << c.get_level();
	std::cout << "\n\nExperience:\t" << c.get_exp() << " / " << c.get_etn() << "\n";
	c.get_exp_bar();
	std::cout << "\nTotal Experience:\t";
	rlutil::setColor(7);
	std::cout << c.get_total_exp() << "\n";
	border4();
	std::cout << std::endl;
	border2();
	border4();
	rlutil::setColor(7);
	std::cout << std::endl;
	std::cout << "Hit Points:\t" << c.get_hp() << " / " << c.get_max_hp() << std::endl;
	c.get_hp_bar();
	rlutil::setColor(7);
	std::cout << "\nMana:\t\t" << c.get_mana() << " / " << c.get_max_mana() << std::endl;
	c.get_mana_bar();
	rlutil::setColor(10);
	std::cout << "\nAttack Range:\t";
	rlutil::setColor(7);
	std::cout << c.get_att_range(0) << " - " << c.get_att_range(1);
	rlutil::setColor(9);
	std::cout << "\n\nStrength:\t";
	rlutil::setColor(7);
	std::cout << c.get_str();
	rlutil::setColor(9);
	std::cout << "\nMagic:\t\t";
	rlutil::setColor(7);
	std::cout << c.get_magic();
	rlutil::setColor(9);
	std::cout << "\nDexterity:\t";
	rlutil::setColor(7);
	std::cout << c.get_dex();
	rlutil::setColor(11);
	std::cout << "\n\nAccuracy:\t";
	rlutil::setColor(7);
	std::cout << c.get_acc()*100 << "%";
	//std::cout << "\nAvoidability:\t" << c.get_avoid()*100 << "%";
	rlutil::setColor(13);
	std::cout << "\n\nSkill Points:\t";
	rlutil::setColor(7);
	std::cout << c.get_s_points() << "\n\n";
	rlutil::setColor(14);	
	std::cout << "Gold:\t\t\t";
	rlutil::setColor(7);
	std::cout << c.get_gold() << "\n";
	rlutil::setColor(14);
	std::cout << "Gold Multiplier:\tx ";
	rlutil::setColor(7);
	std::cout << c.get_gold_mult() << "\n";
	rlutil::setColor(14);
	std::cout << "Richness Rating:\t";
	rlutil::setColor(7);
	std::cout << c.get_rich() << "\n";
	border4();
	border2();
	border3();
	standby();
}

//used to spend skill points
void spend_s_points(Character c)
{
	clear_screen();
	border2();
	border3();
	rlutil::setColor(7);
	std::cout << "\nSKILL POINTS AVAILABLE:  " << c.get_s_points() << " SP";
	std::cout << "\n\n(1): Raise STRENGTH\n";
	std::cout << "\t(Current: " << c.get_str() << ")\n\n";
	std::cout << "(2): Raise MAGIC\n";
	std::cout << "\t(Current: " << c.get_magic() << ")\n\n";
	std::cout << "(3): Raise DEXTERITY\n";
	std::cout << "\t(Current: " << c.get_dex() << ")\n\n";
	std::cout << "(4): Raise ACCURACY\n";
	std::cout << "\t(Current: " << c.get_acc()*100 << "%)\n\n\n";
//	std::cout << "(3): Raise avoidability\n";
//	std::cout << "\t(Current: " << c.get_avoid()*100 << "%)\n\n\n";
	std::cout << "(Q): Return to CHARACTER MENU\n\n";
	border3();
	border2();
}

//MONSTER FUNCTIONS
Monster create_mon_name(void)
{
	//BUG INC
	Monster new_monf("", 0);

	int rt, ri;

	int num_mon_types = 16;			//this must always match the number of types
	std::string mon_types[num_mon_types] = {"Stickbug", "Nugget", "Goop",
						"Sqworp", "Dragon", "Kitten",
						"Glib-Glob III", "Snake", "Dog",
						"Skeleton", "Wormy", "Snailo",
						"Rockmon", "Zombo", "Dude", "LeCroy Johnson"};

	rt = rand() % (num_mon_types - 0) - 0;

	int num_mon_ident = 16;			//this must always match the number of identifiers
	std::string mon_ident[num_mon_ident] = {"Blue", "Bumpy", "Squirmy",
						"Giant-Ass", "Fiery", "Teeny-Tiny",
						"Chocolate", "Spooky", "Unfriendly",
						"Questionable", "Ugly", "Screaming",
						"Mildly-Upset", "Passive-Aggressive", "Mortifying", "Legendary"};

	ri = rand() % (num_mon_ident - 0) - 0;

	new_monf.set_mon_ident(mon_ident[ri]);
	new_monf.set_mon_type(mon_types[rt]);
	new_monf.set_char_name(mon_ident[ri] + " " + mon_types[rt]);

	return new_monf;
}

//BATTLE SCENE VERSION 2
//return type int:
//returns: 0 if quit
//	   1 if hero wins
//	   2 if hero dies
//
//return type Character:
//return hero
Character battle_scene_v2(Battle* btl)
{
	srand(time(NULL));

	struct termios old_tio, new_tio;
	unsigned char input;
	tcgetattr(STDIN_FILENO, &old_tio);

	new_tio = old_tio;

	new_tio.c_lflag &=(~ICANON & ~ECHO);

	tcsetattr(STDIN_FILENO, TCSANOW, &new_tio);

	Character hero;
	hero = btl->get_hero();

	Monster enemy;
	enemy = btl->get_enemy();

	double att_dmg;	//dmg dealt by successful attack
	double heal;	//amount healed
	int att_hit;	//does attack hit?
	int turn = -1;	//-1 = battle start
			//0 = hero turn
			//1 = monster turn
			//2 = end battle
	int gold_earned;	//gold earned
	int exp_gained;		//base exp
	int exp_gained_m;	//monster exo bonus
	int total_exp;		//exp_gained + exp_gained_m
	int prior_exp;
	char ans;
	bool defended_this_turn;	//true = has
					//false = has not
	bool isMonsterResearched = false;	//true = yes
						//false = no
	bool isLifesteal = false;	//true = lifesteal next hit
					//false = no lifesteal
	bool isGoldgain = false;	//true = gold-gain next hit
					//false = no gold-gain


/*****************************************************************
 * 	ITEM DROPS. Continues into the hero's turn in battle.    *
 *****************************************************************/

	// Chance to get an item (currently 1 in 3 (33%)) at end of combat
	int item_chance = 1;
	int item_category = rand() % 3; // for determining whether to drop a weapon, armor, or boots. 0 = weapon, 1 = armor, 2 = boots
	int weapon_drop = rand() % 10; // decide which weapon to give
	int armor_drop = rand() % 4; // decide which armor to give
	int boots_drop = rand() % 4; // decide which boots to give
	int special_choice = rand() % 4; // decide which special modifier to give
	int special_item = rand() % 8; // 1 in 8 chance for a special item
	int describer_choice; // determines which tier to give based on p level
	double dmg; // different weapon types deal more damage (greatswords obviously hurt more than a dagger)
	double def; // different armor and boots will grant difference levels of defense
	// How many of each item exist in our game
	int num_modifiers = 4;
	int num_describers = 5;
	int num_weapons = 10;
	int num_armor = 4;
	int num_boots = 4;
	int num_misc = 4;
	int num_stats = 4;

	// Adjectives used to describe weapons, armor, boots, etc.
	string modifiers[num_modifiers] = {"Fiery ", "Freezing ", "Shocking ", "Lucky "};
	string armor_modifiers[num_modifiers] = {"Protective ", "Aggressive ", "Quick ", "Intelligent "};
	string describers[num_describers] = {"Bronze ", "Steel ", "Mithril ", "Adamantite ", "Rune "};

	// All possible item drops from monsters
	string weapons[num_weapons] = {"sword", "dagger", "spear", "katana",
				       "staff", "mace", "greatsword", "greataxe",
				       "wand", "whip"};
	string armor[num_armor] = {"vest", "chestplate", "tunic", "robe" };
	string boots[num_boots] = {"sandals", "plateboots", "leather boots", "sock"};
	string misc[num_misc] = {"Health potion I", "Health potion II", "Gold", "Rock"};

	// Base damage values of all weapons
	double sword = 1.10;
	double dagger = 0.60;
	double spear = 0.95;
	double katana = 0.90;
	double staff = 0.40;
	double mace = 1.20;
	double greatsword = 1.60;
	double greataxe = 1.80;
	double battleaxe = 1.30;
	double whip = 0.50;

	// Base damage def of all armor
	double vest = 0.90;
	double chestplate = 1.25;
	double tunic = 0.60;
	double robe = 0.35;

	// Base damage def of all boots
	double sandals = 0.10;
	double plateboots = 0.40;
	double leather_boots = 0.25;
	double sock = 0.05;
	
	// Scaling values for all weapons. Str/dex/int/resistance
	double weapon_scaling[num_weapons][num_stats] = {
		{0.40, 0.40, 0.00, 0.00}, // Sword
		{0.10, 0.80, 0.00, 0.00}, // Dagger
		{0.25, 0.50, 0.00, 0.00}, // Spear
		{0.30, 0.50, 0.00, 0.00}, // Katana
		{0.15, 0.10, 0.70, 0.00}, // Staff
		{0.50, 0.15, 0.00, 0.00}, // Mace
		{0.80, 0.15, 0.00, 0.00}, // Greatsword
		{0.90, 0.05, 0.00, 0.00}, // Greataxe
		{0.05, 0.15, 0.40, 0.00}, // Wand
		{0.10, 0.45, 0.00, 0.00} // Whip
	};
				
	// Scaling def values for all armor. Scales off of a resistance stat.
	double armor_scaling[num_armor][num_stats] = {
		{0.00, 0.00, 0.00, 1.10}, // Vest
		{0.00, 0.00, 0.00, 1.90}, // Chestplate
		{0.00, 0.00, 0.00, 1.30}, // Tunic
		{0.00, 0.00, 0.00, 0.65} // Robe
	};
	// Scaling def values for all boots. Scales off a resistance stat.
	double boots_scaling[num_boots][num_stats] = {
		{0.00, 0.00, 0.00, 0.35}, // Sandals
		{0.00, 0.00, 0.00, 0.75}, // Plateboots
		{0.00, 0.00, 0.00, 0.55}, // Leather boots
		{0.00, 0.00, 0.00, 1.20}  // Sock (op as fuck? lmao)
	};	
	// Which scaling values to use, depending on which equipment was generated
	double str_scaling;
	double dex_scaling;
	double int_scaling;
	double res_scaling;
	// Weapon
	if(item_category == 0) {
		str_scaling = weapon_scaling[weapon_drop][0];
		dex_scaling = weapon_scaling[weapon_drop][1];
		int_scaling = weapon_scaling[weapon_drop][2];
		res_scaling = weapon_scaling[weapon_drop][3];
	}
	// Which item we're on
	int weapon_item_num = hero.get_weapons_length() + 1;
        int armor_item_num = hero.get_armor_length() + 1;
        int boots_item_num = hero.get_boots_length() + 1;
        int misc_item_num = hero.get_misc_length() + 1;
	
	// Armor
	if(item_category == 1) {
		str_scaling = armor_scaling[armor_drop][0];
		dex_scaling = armor_scaling[armor_drop][1];
		int_scaling = armor_scaling[armor_drop][2];
		res_scaling = armor_scaling[armor_drop][3];
	}
	// Boots
	if(item_category == 2) {
		str_scaling = boots_scaling[boots_drop][0];
		dex_scaling = boots_scaling[boots_drop][1];
		int_scaling = boots_scaling[boots_drop][2];
		res_scaling = boots_scaling[boots_drop][3];
	}
	// What tier of items to give
	// Copper
	if(hero.get_level() >= 1 && hero.get_level() <= 4)
		describer_choice = 0;
	// Steel
	else if(hero.get_level() >= 5 && hero.get_level() <= 11)
		describer_choice = 1;
	// Mithril
 	else if(hero.get_level() >= 12 && hero.get_level() <= 17)
		describer_choice = 2;
	// Adamantite
	else if(hero.get_level() >= 18 && hero.get_level() <= 24)
		describer_choice = 3;
	// Rune
	else if(hero.get_level() >= 25)
		describer_choice = 4;
	// What modifier to apply to a weapon drop
	string modifier = modifiers[special_choice];
	// What modifier to apply to an armor drop
	string a_modifier = armor_modifiers[special_choice];
	// what modifier to apply to boots drop
	string b_modifier = armor_modifiers[special_choice];
	// What tier we will apply to the item drop
	string describer = describers[describer_choice];
	
	// Combine all of those strings into one for weapons
	char weapon_result[50] = "";
	// Combine all of those strings into one for armor
	char armor_result[50] = "";
	// Combine all of those strings into one for boots
	char boots_result[50] = "";
	
/**********************************************
 * 	WEAPON				      *
 *********************************************/
	// make weapon name
	string weapon_option = weapons[weapon_drop];
	// If the item will be special, give it a special modifier 
	if(special_item == 1) {
		strcat(weapon_result, modifier.c_str());
		strcat(weapon_result, describer.c_str());
	}
	else // Otherwise, don't
		strcat(weapon_result, describer.c_str());
	strcat(weapon_result, weapon_option.c_str());


/*********************************************
 *	ARMOR				     *
 *********************************************/
	// make armor name
	string armor_option = armor[armor_drop];
	// If armor will be special, give it a special modifier
	if(special_item == 1) {
		strcat(armor_result, a_modifier.c_str());
		strcat(armor_result, describer.c_str());
	}
	else
		strcat(armor_result, describer.c_str());
	strcat(armor_result, armor_option.c_str());

/*********************************************
 * 	BOOTS				     *
 *********************************************/
	// make boots name
	string boots_option = boots[boots_drop];
	// If boots will be special, give them a special modifier
	if(special_item == 1) {
		strcat(boots_result, b_modifier.c_str());
		strcat(boots_result, describer.c_str());
	}
	else
		strcat(boots_result, describer.c_str());
	strcat(boots_result, boots_option.c_str());

/*********************************************
 *	MISC				     *
 *********************************************/


	//record exp before battle
	prior_exp = hero.get_exp();

	while(turn != 2)
	{
		//isLifesteal = false;

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//		
	//		    INTRO TURN(WIP)		     //
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
		if(turn == -1)
		{
			clear_screen();
			border2();
			border();
			rlutil::setColor(14);
			std::cout << "\n\t" << hero.get_char_name();
			std::cout << "\n\tLevel " << hero.get_level();
			rlutil::setColor(7);
			std::cout << "\n\nHP ( " << hero.get_hp() << " / " << hero.get_max_hp() << " ):\n";
			hero.get_hp_bar();
			rlutil::setColor(7);
			std::cout << "\n\nEXP ( " << hero.get_exp() << " / " << hero.get_etn() << " ):\n";
			hero.get_exp_bar();
			std::cout << "\n";
			border();
			border2();
			versus();
			border2();
			border();
			rlutil::setColor(14);
			std::cout << "\t" << enemy.get_char_name();
			std::cout << "\n\tLevel " << enemy.get_level();
			rlutil::setColor(7);
			std::cout << "\n";
			border();
			border2();
			standby();

			turn = 0;
		}

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//		
	//		    HERO TURN			     //
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
		else if(turn == 0)
		{
			hero_turn:
			clear_screen();
			border2();
			border();
			rlutil::setColor(14);
			std::cout << "\n\t" << hero.get_char_name();
			std::cout << "\n\tLevel " << hero.get_level();
			rlutil::setColor(7);
			std::cout << "\n\nHP ( " << hero.get_hp() << " / " << hero.get_max_hp() << " ):\n";
			hero.get_hp_bar();
			rlutil::setColor(7);
			std::cout << "\n\nEXP ( " << hero.get_exp() << " / " << hero.get_etn() << " ):\n";
			hero.get_exp_bar();
			std::cout << "\n";
			border();
			border2();
			border();
			rlutil::setColor(14);
			std::cout << "\n\t" << enemy.get_char_name();
			std::cout << "\n\tLevel " << enemy.get_level();
			rlutil::setColor(7);
			std::cout << "\n\nHP ";
			if(isMonsterResearched == true)
			{
				std::cout << "( " << enemy.get_hp() << " / " << enemy.get_max_hp() << " ):";
			}
			std::cout << "\n";
			enemy.get_hp_bar();
			std::cout << "\n";
			border();
			border2();
			border4();
			border4();
			rlutil::setColor(2);
			std::cout << "\n   (1): ATTACK\t    (2): SPELLS\n\n   (I): INVENTORY";
			rlutil::setColor(14);
			std::cout << "\n\n   (R): RUN (COST: " << enemy.get_level() * 5 << " gold)\n";
			border4();
			border4();
			input = getchar();
			if(input == '1')
			{
				clear_screen();

				border3();
				rlutil::setColor(3);
				std::cout << std::endl;

				att_hit = btl->doesAttackHit(0);

				if(att_hit == 0)
				{
					rlutil::setColor(7);
					std::cout << "> " << hero.get_char_name() << "'s attack ";
					rlutil::setColor(12);
					std::cout << "MISSED";
					rlutil::setColor(7);
					std::cout << "!\n";
				}
				if(att_hit == 1 || att_hit == 2)
				{
					rlutil::setColor(7);
					std::cout << "> " << hero.get_char_name() << "'s attack ";
					rlutil::setColor(10);
					std::cout << "HIT";
					rlutil::setColor(7);
					std::cout << "!\n";

					if(att_hit == 1)
					{
						att_dmg = btl->generate_attack(hero.get_att_range(0), hero.get_att_range(1));
						std::cout << "> Attack hit for ";
						rlutil::setColor(11);
						std::cout << att_dmg;
						rlutil::setColor(7);
						std::cout << " damage.\n";

						if(isLifesteal)
						{
							std::cout << "> You healed ";
							rlutil::setColor(10);
							std::cout << att_dmg;
							rlutil::setColor(7);
							std::cout << "!\n";
							hero.inc_hp(att_dmg);
							isLifesteal = false;
						}

						if(isGoldgain)
						{
							std::cout << "> You gained ";
							rlutil::setColor(14);
							std::cout << (long int)(att_dmg * hero.get_gold_mult());
							rlutil::setColor(7);
							std::cout << " gold!\n";
							hero.inc_gold((long int)(att_dmg * hero.get_gold_mult()));
							isGoldgain = false;
						}
					}
					else if(att_hit == 2)
					{
						att_dmg = btl->generate_attack(hero.get_att_range(0), hero.get_att_range(1)) * 2;
						std::cout << "> Attack hit CRITICALLY for ";
						rlutil::setColor(14);
						std::cout << att_dmg;
						rlutil::setColor(7);
						std::cout << " damage (";
						rlutil::setColor(11);
						std::cout << att_dmg/2;
						rlutil::setColor(7);
						std::cout << " x 2).\n";

						if(isLifesteal)
						{
							std::cout << "> You healed ";
							rlutil::setColor(10);
							std::cout << att_dmg;
							rlutil::setColor(7);
							std::cout << "!\n";
							hero.inc_hp(att_dmg);
							isLifesteal = false;
						}

						if(isGoldgain)
						{
							std::cout << "> You gained ";
							rlutil::setColor(14);
							std::cout << (long int)(att_dmg * hero.get_gold_mult());
							rlutil::setColor(7);
							std::cout << " gold!\n";
							hero.inc_gold((long int)(att_dmg * hero.get_gold_mult()));
							isGoldgain = false;
						}
					}

					enemy.dec_hp(att_dmg);

					//bool item_drop = false;
					// Enemy is dead, grant XP and a chance of an item!
					if(enemy.isDead())
					{
						std::cout << std::endl;
						border3();
						standby();
						clear_screen();

						enemy_kill:
						bool item_drop = false;

						//Calculating gold earned
						gold_earned = (rand() % 10) + enemy.get_level();

						//Calculating exp gained
						exp_gained = ceil((((enemy.get_level()+1) * 3) + (ceil((enemy.get_level() * enemy.get_level() * enemy.get_level()))))/enemy.get_level());
						exp_gained_m = (enemy.get_str() * 1.5) + (enemy.get_acc() * 10);
						total_exp = exp_gained + exp_gained_m;

						// Item?
						if(item_chance == 1) {
							item_drop = true;
						// What category of item?
							// Weapon
							if(item_category == 0) {
							    // Determine how much dmg the weapon will have, with some randomness
								// Sword
								if(weapon_drop == 0)
									dmg = 2 + rand() % 4;
								// Dagger
								else if(weapon_drop == 1)
									dmg = 2 + rand() % 2;
								// Spear
								else if(weapon_drop == 2)
									dmg = 3 + rand() % 3;
								// Katana
								else if(weapon_drop == 3)
									dmg = 3 + rand() % 4;
								// Staff
								else if(weapon_drop == 4)
									dmg = 5 +  rand() % 2;
								// Mace
								else if(weapon_drop == 5)
									dmg = 3 + rand() % 2;
								// Greatsword
								else if(weapon_drop == 6)
									dmg = 6 + rand() % 3;
								// Greataxe
								else if(weapon_drop == 7)
									dmg = 5 + rand() % 4;
								// Battleaxe
								else if(weapon_drop == 8)
									dmg = 2 + rand() % 6;
								// Whip
								else if(weapon_drop == 9)
									dmg = 1 + rand() % 8;
								// Damage will also go up depending on tier! Add it in add_weapon below.
								// Bronze = +0, Steel = +2, Mithril = +4, Adamantite = +7, Rune = +10
								// Figure out what value to add to damage
								if(describer_choice == 0)
									dmg += 0;
								else if(describer_choice == 1)
									dmg += 2;
								else if(describer_choice == 2)
									dmg += 4;
								else if(describer_choice == 3)
									dmg += 7;
								else if(describer_choice == 4)
									dmg += 10;

								// Now simply add our weapon!
								hero.add_weapon(weapon_item_num, weapon_result, "Weapon", "A weapon", dmg, str_scaling, dex_scaling, int_scaling, res_scaling);
							}
							// Armor
							if(item_category == 1) {
								// Same as weapons. Use the kind of armor to determine how much defense it will offer.
								// Vest
								if(armor_drop == 0)
									def = 4 + rand() % 3;
								// Chestplate
								else if(armor_drop == 1)
									def = 6 + rand() % 5;
								// Tunic
								else if(armor_drop == 2)
									def = 3 + rand() % 3;
								// Robe
								else if(armor_drop == 3)
									def = 2 + rand() % 2;
					
								// Determine how tier affects the stats (and also add what the modifiers will grant in addition to defense, but later)
								if(describer_choice == 0)
									def += 1;
								else if(describer_choice == 1)
									def += 3;
								else if(describer_choice == 2)
									def += 6;
								else if(describer_choice == 3)
									def += 10;
								else if(describer_choice == 4)
									def += 16;
								
								// Now add armor
								hero.add_armor(armor_item_num, armor_result, "Armor", "Some armor", def, str_scaling, dex_scaling, int_scaling, res_scaling);
							}

							// Boots
							if(item_category == 2) {
								// Same as previous two. Use kind of boots to determine stat values
								// Sandals
								if(boots_drop == 0)
									def = 1 + rand() % 2;
								// Plateboots
								if(boots_drop == 1)
									def = 4 + rand() % 3;
								// Leather boots
								if(boots_drop == 2)
									def = 2 + rand() % 3;
								// Sock
								if(boots_drop == 3)
									def = 0 + rand() % 6;
								// Determine how tier will increase def
								if(describer_choice == 0)
									def += 1;
								else if(describer_choice == 1)
									def += 3;
								else if(describer_choice == 2)
									def += 6;
								else if(describer_choice == 3)
									def += 10;	
								else if(describer_choice == 4)
									def += 16;

								// Now add to inventory
								hero.add_boots(boots_item_num, boots_result, "Boots", "Some boots", def, str_scaling, dex_scaling, int_scaling, res_scaling);
							}
						}

						//std::cout << std::endl;
						border3();
						border();
						rlutil::setColor(14);
						std::cout << "\t   You have defeated\n\t\t";
						rlutil::setColor(5);
						std::cout << enemy.get_char_name();
						rlutil::setColor(11);
						std::cout << "\n\t\t\tLevel " << enemy.get_level() << std::endl;
						border();
						border3();
						border2();
						std::cout << "\nREWARDS:\n\n";
						rlutil::setColor(15);
						std::cout << "BASE EXP EARNED:\t\t";
						rlutil::setColor(5);
						std::cout << exp_gained;
						rlutil::setColor(15);
						std::cout << "\nMONSTER LEVEL EXP BONUS:\t";
						rlutil::setColor(5);
						std::cout << exp_gained_m;
						rlutil::setColor(7);
						std::cout << "\n-------------------------------------------";
						rlutil::setColor(15);
						std::cout << "\nTOTAL EXP EARNED:\t\t";
						rlutil::setColor(10);
						std::cout << total_exp;
						rlutil::setColor(11);
						std::cout << "\n\n     You went from ";
						rlutil::setColor(5);
						std::cout << prior_exp << " EXP ";
						rlutil::setColor(11);
						std::cout << "to ";
						rlutil::setColor(5);
						std::cout << total_exp + prior_exp << " EXP";
						rlutil::setColor(11);
						std::cout << "!\n";
						hero.inc_exp(total_exp);
						hero.inc_gold(gold_earned * hero.get_gold_mult());
						hero.inc_mana(5);
						rlutil::setColor(15);
						std::cout << "\nGOLD EARNED:\t\t\t";
						rlutil::setColor(14);
						std::cout << gold_earned;
						rlutil::setColor(15);
						std::cout << "\nBONUS GOLD:\t\t\t";
						rlutil::setColor(14);
						std::cout << (int)(gold_earned * hero.get_gold_mult()) - gold_earned;
						rlutil::setColor(7);
						std::cout << "\n-------------------------------------------";
						rlutil::setColor(15);
						std::cout << "\nTOTAL GOLD EARNED:\t\t";
						rlutil::setColor(14);
						std::cout << (int)(gold_earned * hero.get_gold_mult());
						rlutil::setColor(15);
						std::cout << "\n\nITEM(S) EARNED:\t\t";
						rlutil::setColor(9);
						if(item_drop && item_category == 0) {
							std::cout << weapon_result;
							std::cout << "\n\n";
						}
						else if(item_drop && item_category == 1) {
							std::cout << armor_result;
							std::cout << "\n\n";
						}
						else if(item_drop && item_category == 2) {
							std::cout << boots_result;
							std::cout << "\n\n";
						}
						else
						{
							std::cout << "\n\n";
						}
						border2();
						border3();
						standby();

						tcsetattr(STDIN_FILENO, TCSANOW, &old_tio);

						return hero;
					}
				}

				std::cout << std::endl;
				border3();
				standby();

				//Pass to monster turn
				turn = 1;
			}
			//MAGIC SPELLS
			else if(input == '2')
			{
				magic:
				magic_menu(hero);
				std::cout << "SELECTION:   ";
				if(!(std::cin >> ans))
				{
					std::cout << "Input Error: Invalid input, please retry.\n";
					std::cin.clear();
					std::cin.ignore(10000, '\n');

					goto magic;
				}
				//HEAL
				if(ans == '1')
				{
					clear_screen();

					if(hero.get_mana() < 5)
					{
						border2();
						rlutil::setColor(7);
						std::cout << "\n   You don't have enough Mana!!!\n\n";
						border2();
						standby();
					}
					else
					{
						heal = (double)(rand() % (hero.get_magic() + 2) + (hero.get_magic() - 2));
						hero.inc_hp(heal);
						hero.dec_mana(5);
						
						border3();
						rlutil::setColor(7);
						std::cout << "\n\t   You healed for ";
						rlutil::setColor(11);
						std::cout << heal;
						rlutil::setColor(7);
						std::cout << " HP!\n\n";
						border3();
						standby();
					}
				}
				//RESEARCH MONSTER
				else if(ans == '2')
				{
					clear_screen();

					if(hero.get_mana() < 2)
					{
						border2();
						rlutil::setColor(7);
						std::cout << "\n   You don't have enough Mana!!!\n\n";
						border2();
						standby();
					}
					else if(isMonsterResearched)
					{
						border2();
						rlutil::setColor(7);
						std::cout << "\nYou have already researched this monster!!!\n\n";
						border2();
						standby();
					}
					else
					{
						hero.dec_mana(2);

						border3();
						rlutil::setColor(7);
						std::cout << "\n     You successfully researched\n\t";
						rlutil::setColor(11);
						std::cout << enemy.get_char_name();
						rlutil::setColor(7);
						std::cout << "\n\n     It hits with " << enemy.get_acc() * 100 << "% accuracy.";
						std::cout << "\n     It can hit between " << enemy.get_att_range(0) << " - " << enemy.get_att_range(1) << " damage.";
						std::cout << "\n\n";
						border3();
						standby();

						isMonsterResearched = true;
					}
				}
				//TARGETED COMBUSTION
				else if(ans == '3')
				{
					clear_screen();

					if(hero.get_mana() < 10)
					{
						border2();
						rlutil::setColor(7);
						std::cout << "\n   You don't have enough Mana!!!\n\n";
						border2();
						standby();
					}
					else
					{
						hero.dec_mana(10);
						enemy.dec_hp(15 + hero.get_magic());

						border3();
						rlutil::setColor(7);
						std::cout << "\n     You dealt ";
						rlutil::setColor(12);
						std::cout << 15 + hero.get_magic();
						rlutil::setColor(7);
						std::cout << " damage!\n\n";
						border3();
						standby();

						clear_screen();

						if(enemy.isDead())
						{
							goto enemy_kill;
						}
					}
				}
				//EMPOWERED LIFESTEAL
				else if(ans == '4')
				{
					clear_screen();

					if(hero.get_mana() < 7)
					{
						border2();
						rlutil::setColor(7);
						std::cout << "\n   You don't have enough Mana!!!\n\n";
						border2();
						standby();
					}
					else if(isLifesteal)
					{
						border2();
						rlutil::setColor(7);
						std::cout << "\n  You already have Lifesteal activated!!!\n\n";
						border2();
						standby();
					}
					else
					{
						hero.dec_mana(7);

						border3();
						rlutil::setColor(7);
						std::cout << "\n  Your next attack is empowered with";
						rlutil::setColor(5);
						std::cout << "\n\t      100% Lifesteal\n\n";
						border3();
						standby();

						isLifesteal = true;
					}
				}
				//JACKPOT HIT
				else if(ans == '5')
				{
					clear_screen();

					if(hero.get_mana() < 12)
					{
						border2();
						rlutil::setColor(7);
						std::cout << "\n   You don't have enough Mana!!!\n\n";
						border2();
						standby();
					}
					else if(isGoldgain)
					{
						border2();
						rlutil::setColor(7);
						std::cout << "\n  You already have Gold-gain activated!!!\n\n";
						border2();
						standby();
					}
					else
					{
						hero.dec_mana(12);

						border3();
						rlutil::setColor(7);
						std::cout << "\n  Your next attack is empowered with";
						rlutil::setColor(14);
						std::cout << "\n\t      " << 100 + (25 * ((hero.get_gold_mult()/0.25)-4)) << "% Gold-gain\n\n";
						border3();
						standby();

						isGoldgain = true;
					}
				}
				else if(ans == 'q' || ans == 'Q')
				{
					goto hero_turn;
				}
				else
				{
					goto magic;
				}
			}
			//QUIT
			else if(input == 'r' || input == 'R')
			{
				if(hero.get_gold() < (5*enemy.get_level()))
				{
					clear_screen();
					border2();
					rlutil::setColor(7);
					std::cout << "\n     You don't have enough gold!!!\n\n";
					border2();
					standby();

					goto hero_turn;
				}

				hero.dec_gold(5*enemy.get_level());

				tcsetattr(STDIN_FILENO, TCSANOW, &old_tio);

				return hero;
			}
			else
			{
				goto hero_turn;
			}
		}

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//		
	//		    MONSTER TURN		     //
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
		else if( turn == 1 )
		{
			defended_this_turn = false;

			enemy_turn:
			clear_screen();
			border2();
			border();
			rlutil::setColor(14);
			std::cout << "\n\t" << hero.get_char_name();
			std::cout << "\n\tLevel " << hero.get_level();
			rlutil::setColor(7);
			std::cout << "\n\nHP ( " << hero.get_hp() << " / " << hero.get_max_hp() << " ):\n";
			hero.get_hp_bar();
			rlutil::setColor(7);
			std::cout << "\n\nEXP ( " << hero.get_exp() << " / " << hero.get_etn() << " ):\n";
			hero.get_exp_bar();
			std::cout << "\n";
			border();
			border2();
			border();
			rlutil::setColor(14);
			std::cout << "\n\t" << enemy.get_char_name();
			std::cout << "\n\tLevel " << enemy.get_level();
			rlutil::setColor(7);
			std::cout << "\n\nHP";
			if(isMonsterResearched == true)
			{
				std::cout << " ( " << enemy.get_hp() << " / " << enemy.get_max_hp() << " ):";
			}
			std::cout << "\n";
			enemy.get_hp_bar();
			std::cout << "\n\n";
			border();
			border2();
			border4();
			border4();
			//border();
			rlutil::setColor(12);
			std::cout << "\n   IT IS " << enemy.get_char_name() << "'s TURN NOW\n\n";
			rlutil::setColor(7);
			std::cout << "   (1): TAKE HIT\n";
			//std::cout << "   (2): DEFEND\n";
			//border();
			border4();
			border4();
			input = getchar();

			defend:
			att_hit = btl->doesAttackHit(1);

			if(input == '1')
			{
				clear_screen();

				border2();
				std::cout << std::endl;

				if(att_hit == 0)
				{
					rlutil::setColor(7);
					std::cout << "> " << enemy.get_char_name() << "'s attack ";
					rlutil::setColor(12);
					std::cout << "MISSED\n";
					if(isMonsterResearched == true)
					{
						rlutil::setColor(7);
						std::cout << "> This monster is known to hit between:\n\t\t";
						rlutil::setColor(12);
						std::cout << enemy.get_att_range(0) << " - " << enemy.get_att_range(1) << std::endl;
					}
				}
				else if(att_hit == 1 || att_hit == 2)
				{
					rlutil::setColor(7);
					std::cout << "> " << enemy.get_char_name() << "'s attack ";
					rlutil::setColor(10);
					std::cout << "HIT";
					rlutil::setColor(7);
					std::cout << "!\n";

					if(att_hit == 1)
					{
						att_dmg = btl->generate_attack(enemy.get_att_range(0), enemy.get_att_range(1));
						std::cout << "> Attack hit for ";
						rlutil::setColor(11);
						std::cout << att_dmg;
						rlutil::setColor(7);
						std::cout << " damage.\n";
						if(isMonsterResearched == true)
						{
							std::cout << "> This monster is known to hit between:\n\t\t";
							rlutil::setColor(12);
							std::cout << enemy.get_att_range(0) << " - " << enemy.get_att_range(1) << std::endl;
						}
					}
					else if(att_hit == 2)
					{
						att_dmg = btl->generate_attack(enemy.get_att_range(0), enemy.get_att_range(1)) * 2;
						std::cout << "> Attack hit CRITICALLY for ";
						rlutil::setColor(14);
						std::cout << att_dmg;
						rlutil::setColor(7);
						std::cout << " damage (";
						rlutil::setColor(11);
						std::cout << att_dmg/2;
						rlutil::setColor(7);
						std::cout << " x 2).\n";
					}

					hero.dec_hp(att_dmg);

					if(hero.isDead())
					{
						std::cout << std::endl;
						border2();
						standby();
						clear_screen();
						border2();
						border();
						std::cout << "\t\tYOU ARE DEAD\n";
						border();
						border2();
						standby();

						tcsetattr(STDIN_FILENO, TCSANOW, &old_tio);

						return hero;
					}
				}
			}
			//DEFENSE (WIP)
			/*else if(input == '2')
			{
				clear_screen();

				border3();
				rlutil::setColor(3);
				std::cout << std::endl;

				if(att_hit == 0)
				{
					std::cout << ">" << enemy.get_char_name() << "'s attack MISSED!\n";
				}
				else if(att_hit == 1 || att_hit == 2)
				{
					if(input == '2' && !defended_this_turn)
					{
						std::cout << "You successfully dodge the attack!\n";
						defended_this_turn = true;
						goto defend;
					}
				}

				std::cout << ">" << enemy.get_char_name() << "'s attack HIT!\n";

				if(att_hit == 1)
				{
					att_dmg = btl->generate_attack(enemy.get_att_range(0), enemy.get_att_range(1));
					std::cout << ">Attack hit for " << att_dmg << " damage.\n";
				}
				else if(att_hit == 2)
				{
					att_dmg = btl->generate_attack(enemy.get_att_range(0), enemy.get_att_range(1)) * 2;
				} */

			else
			{
				goto enemy_turn;
			}

			std::cout << std::endl;
			border2();
			standby();

			//Pass to hero turn
			turn = 0;
		}
	}

	tcsetattr(STDIN_FILENO, TCSANOW, &old_tio);

	return hero;
}
