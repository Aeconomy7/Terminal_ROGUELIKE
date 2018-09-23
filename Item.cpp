#include "Item.h"
#include <iostream>
#include <string>
using namespace std;

// CONSTRUCTORS
Item::Item() {
	/*
	name = "";
	description = "";
	type = "";
	stat_value = 0; */
}

// For misc
Item::Item(char n[], string d, string t, double sv) {
	for(int i = 0; i < 50; i++) 
		name[i] = n[i];
	description = d;
	type = t;
	stat_value = sv;
}
// For all other items that will have scaling
Item::Item(int i, char n[], string d, string t, double sv, double str, double dex, double intel, double res) {
	item_num = i; 
	for(int i = 0; i < 50; i++) 
		name[i] = n[i];
	description = d;
	type = t;
	stat_value = sv;
	str_scaling = str;
	dex_scaling = dex;
	int_scaling = intel;
	res_scaling = res;
}
// SETS
void Item::set_item_num(int i) {
	item_num = i;
}
void Item::set_name(char input[]) {
	for(int i = 0; i < 50; i++)
		name[i] = input[i];
}

void Item::set_description(string input) {
	description = input;
}

void Item::set_type(string input) {
	type = input;
}

void Item::set_stat_value(int input) {
	stat_value = input;
}

void Item::set_str_scaling(double input) {
	str_scaling = input;
}

void Item::set_dex_scaling(double input) {
	dex_scaling = input;
}

void Item::set_int_scaling(double input) {
	int_scaling = input;
}

void Item::set_res_scaling(double input) {
	res_scaling = input;
}
// GETS
int Item::get_item_num() {
	return item_num;
}
string Item::get_name() {
	return name;
}

string Item::get_description() {
	return description;
}

string Item::get_type() {
	return type;
}

int Item::get_stat_value() {
	return stat_value;
}

double Item::get_str_scaling() {
	return str_scaling;
}

double Item::get_dex_scaling() {
	return dex_scaling;
}

double Item::get_int_scaling() {
	return int_scaling;
}

double Item::get_res_scaling() {
	return res_scaling;
}
