#ifndef CHARACTER_H
#define CHARACTER_H

#include<string>
#include<iostream>
#include<fstream>
#include "Inventory.h"
class Character
{
	friend class Battle;

	public:
		//Constructors & Deconstructors
		Character();
		Character(std::string, int);
		~Character();

		//SETS
		void set_char_name(std::string);
		void set_hp(double);
		void set_mana(double);
		void set_gold(int);
		void set_str(int);
		void set_magic(int);
		void set_dex(int);
		void set_acc(double);
		//void set_avoid(double);
		void set_level(int);
		void set_dmg(double);
                void set_def(double);
                void set_str_scaling(double);
                void set_dex_scaling(double);
		void set_int_scaling(double);
		void set_generic_res_scaling(double);
                void set_armor_res_scaling(double);
                void set_boots_res_scaling(double);
		void set_res_scaling(double);
                void set_weapon_equipped(bool);
                void set_armor_equipped(bool);
                void set_boots_equipped(bool);
		// Equipment functions variables:
		// Weapon name, weapon description, weapon type, stat value increase (dmg or def), str scaling, dmg scaling, int scaling
		void add_weapon(int, char [], string, string, double, double, double, double, double);
		void add_armor(int, char [], string, string, double, double, double, double, double);
		void add_boots(int, char [], string, string, double, double, double, double, double);
		void add_misc(int, char [], string, string, double, double, double, double, double);
		void search_weapons(int);
                void search_armor(int);
                void search_boots(int);
                void search_misc(int);
		void equip();
		//GETS
		std::string get_char_name(void);
		int get_pin(void);
		double get_hp(void);
		double get_max_hp(void);
		double get_mana(void);
		double get_max_mana(void);
		long int get_gold(void);
		double get_gold_mult(void);
		string get_rich(void);
		int get_rich_num(void);
		int get_level(void);
		int get_exp(void);
		long int get_total_exp(void);
		int get_etn(void);
		int get_str(void);
		int get_magic(void);
		int get_dex(void);
		double get_acc(void);
		double get_dmg(void);
		double get_def(void);
		//double get_avoid(void);
		int get_s_points(void);
		double get_att_range(int);
		int get_weapons_length();
                int get_armor_length();
                int get_boots_length();
                int get_misc_length();
                double get_str_scaling();
                double get_dex_scaling();
		double get_int_scaling();
		double get_generic_res_scaling();
                double get_armor_res_scaling();
                double get_boots_res_scaling();
		double get_res_scaling();
                bool get_weapon_equipped();
                bool get_armor_equipped();
                bool get_boots_equipped();
		Inventory get_weapons(void);
		Inventory get_armor(void);
		Inventory get_boots(void);
		Inventory get_misc(void);

		//Functions
		void validate_char(void);
		void get_exp_bar(void);
		void get_hp_bar(void);
		void get_mana_bar(void);
		void inc_hp(double);
		void dec_hp(double);
		void inc_mana(double);
		void dec_mana(double);
		void inc_gold(long int);
		void dec_gold(long int);
		void inc_gold_mult(void);
		void inc_rich(void);
		void inc_exp(int);
		void level_up(void);
		void inc_str(void);
		void inc_magic(void);
		void inc_dex(void);
		void inc_acc(void);
		//void inc_avoid(void);
		bool isDead(void);
		void show_weapons(void);
		void show_armor(void);
		void show_boots(void);
		void show_misc(void);

		// Item functions

		//Overloads
		friend std::fstream& operator<<(std::fstream& os, const Character& chr_o);
		friend std::fstream& operator>>(std::fstream& is, Character& chr_i);
		//friend std::ostream& operator<<(std::ostream& os, const Character& chr_o);

	protected:
		std::string char_name;	//character name
		int pin;		//pin to login
		double hp;		//health points
		double max_hp;		//max hit points
		double mana;		//mana
		double max_mana;	//max mana
		long int gold;		//gold (tenative)
		double gold_mult;	//gold multiplier
		int rich;		//richness rating in number form
		int level;		//character level
		int dmg;		//attack damage based on str/dex scaling
		int def;		//dmg reduction based on res scaling
		int exp;		//experience
		long int total_exp;	//total accumulated exp
		int etn;		//experience to next level
		int str;		//strength
		int magic;		//magic level
		int dex;		//dexterity (necessary to weild weapons)
		double acc;		//accuracy
		//double avoid;		//avoidability
		int s_points;		//skill points
		double att_range[2];	//range of attack, between first and second number
		bool weapon_eqpd;
                bool armor_eqpd;
                bool boots_eqpd;
                // Scaling values from current weapon/armor
                double str_scaling;
                double dex_scaling;
		double generic_res_scaling;
		double int_scaling;
                double armor_res_scaling;
                double boots_res_scaling;
		double res_scaling;
		Inventory weapons;
		Inventory armor;
		Inventory boots;
		Inventory misc;
};

#endif
