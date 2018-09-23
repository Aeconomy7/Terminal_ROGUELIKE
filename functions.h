#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include"Character.h"
#include"Monster.h"
#include"Battle.h"

#include<string>
#include<iostream>
#include<fstream>

//Menu Functions
void border(void);
void border2(void);
void border3(void);
void border4(void);
void clear_screen(void);
void standby(void);
void main_menu(void);
void character_menu(void);
void shop_menu(Character);
void magic_menu(Character);

//Character Functions
bool isCharacter(std::string, std::fstream&);
void save_char(Character, std::fstream&);
void remove_char(std::string, std::fstream&, std::fstream&);
void create_char(std::fstream&);
Character fetch_char(std::string, std::fstream&);
Character login(std::fstream&);
void print_char(Character);
void spend_s_points(Character);

//Monster functions
Monster create_mon_name(void);

//Battle functions
Character battle_scene_v2(Battle*);

#endif
