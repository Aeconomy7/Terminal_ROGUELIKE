#ifndef ITEM_H
#define ITEM_H

#include <string>
using namespace std;

class Item {

	private:
		int item_num;
		char name[50];
		string type; // weapons, armor, boots, misc
		string description;;
		double stat_value; // will be a a number. Say 9. If we check the item and find its a sword, it'll add damage. If its armor, it'll add protection
		double str_scaling;
		double dex_scaling;
		double int_scaling;
		double res_scaling;
	public:
		// CONSTRUCTORS
		Item();
		// For misc items
		Item(char [], string, string, double);
		// For weapons, armor, and boots
		Item(int, char [], string, string, double, double, double, double, double);
		// SETS
		void set_item_num(int);
		void set_name(char []);
		void set_type(string);
		void set_description(string);
		void set_stat_value(int);
		void set_str_scaling(double);
		void set_dex_scaling(double);
		void set_int_scaling(double);
		void set_res_scaling(double);
		// GETS
		int get_item_num();
		string get_name();
		string get_type();
		string get_description();
		int get_stat_value();
		double get_str_scaling();
		double get_dex_scaling();
		double get_int_scaling();
		double get_res_scaling();



};


#endif
