//AUTHOR: Alexander Economy
//DATE CREATED: 5/10/2017
//EMAIL: aeconomy7@gmail.com
//DESCRIPTION: A game

//CO-AUTHOR: Mason Hobbs
//EMAIL: mhobbs1996@gmail.com
//RESPONSIBLE FOR MAP AND PLAYER MOVEMENT

#include"Character.h"
#include"Monster.h"
#include"Battle.h"
#include"functions.h"
#include "Map.h"
#include"rlutil.h"

#include <vector>
#include <time.h>
#include <cstdlib>
#include<iostream>
#include<fstream>

std::fstream chars, temp;


int main()
{
	rlutil::setBackgroundColor(0);

	chars.open("Characters.txt", std::ios::app);
	if(chars.fail())
	{
		std::cout << "\nError opening 'Characters.txt'...\n";
		return -1;
	}

     /*	// Generate all of our game maps
	vector<Map> maps;
	srand(time(NULL));
	int seed = rand() % 500;
	for(int i = 0; i < 10; i++) {
		maps.push_back(Map(seed+i));
		maps[i].generateMap();
		maps[i].setFloor(i+1);
	}
	// Done generating maps */

	Character play;
	int monst_level;
	int amnt;
	int cost;
	char ans = '0';
	int choice;

	struct termios old_tio, new_tio;
	unsigned char input;

	while(ans != 'q' && ans != 'Q')
	{
		//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
		//		MAIN MENU
		//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
		main:

		//unbuffered input
		/*tcgetattr(STDIN_FILENO, &old_tio);
		new_tio = old_tio;
		new_tio.c_lflag &=(~ICANON & ~ECHO);
		tcsetattr(STDIN_FILENO, TCSANOW, &new_tio);*/

		main_menu();
		std::cout << "SELECTION:   ";
		if(!(std::cin >> ans))
		{
			std::cout << "Input Error: Invalid input, please retry.\n";
			std::cin.clear();
			std::cin.ignore(10000, '\n');

			goto main;
		}

		border2();

		//Create Character
		if(ans == '1')
		{
			//buffered input
			//tcsetattr(STDIN_FILENO, TCSANOW, &old_tio);

			create_char(chars);
		}
		//Login to character and generate a set of unique maps for the logged in character every time
		else if(ans == '2')
		{
			// Generate all of our game maps
			vector<Map> maps;
			srand(time(NULL));
			int seed = rand() % 500;
			for(int i = 0; i < 10; i++) {
				maps.push_back(Map(seed+i));
				maps[i].generateMap();
				maps[i].setFloor(i+1);
			}

			//Buffered input
			//tcsetattr(STDIN_FILENO, TCSANOW, &old_tio);

			// Done generating maps
			play = login(chars);

			if(play.get_char_name() == "NULL_CHAR_NAME")
			{
				goto main;
			}

			while(ans != 'q' && ans != 'Q')
			{
				//&&&&&&&&&&&&&&&&&&&&&&
				//	CHARACTER MENU
				//&&&&&&&&&&&&&&&&&&&&&&
				charm:

				//unbuffered input
				/*tcgetattr(STDIN_FILENO, &old_tio);
				new_tio = old_tio;
				new_tio.c_lflag &=(~ICANON & ~ECHO);
				tcsetattr(STDIN_FILENO, TCSANOW, &new_tio);*/

				play.validate_char();
				character_menu();

				std::cout << "SELECTION:   ";
				if(!(std::cin >> ans))
				{
					std::cout << "Input Error: Invalid input, please retry.\n";
					std::cin.clear();
					std::cin.ignore(10000, '\n');

					goto charm;
				}

				//Character stats
				if(ans == '1')
				{
					print_char(play);
				}
				//Spend Skill points
				else if(ans == '2')
				{
					sp:
					spend_s_points(play);
					std::cout << "SELECTION:   ";
					std::cin >> ans;
					//std::cin.ignore();

					//buffered input
					//tcsetattr(STDIN_FILENO, TCSANOW, &old_tio);

					catcher:

					clear_screen();

					//RAISE STR
					if(ans == '1')
					{
						std::cout << "\nHow many Skill Points would you like to spend on STRENGTH:\n";
						if(!(std::cin >> amnt))
						{
							std::cout << "Input Error: Invalid input\n";

							std::cin.clear();
							std::cin.ignore(10000, '\n');

							goto catcher;
						}

						for(int i = 0; i < amnt; i++)
						{
							play.inc_str();
						}
					}
					//RAISE MAGIC
					else if(ans == '2')
					{
						std::cout << "\nHow many Skill Points would you like to spend on MAGIC:\n";
						if(!(std::cin >> amnt))
						{
							std::cout << "Input Error: Invalid input\n";

							std::cin.clear();
							std::cin.ignore(10000, '\n');

							goto catcher;
						}

						for(int i = 0; i < amnt; i++)
						{
							play.inc_magic();
						}
					}
					else if(ans == '3')
					{
						std::cout << "\nHow many Skill Points would you like to spend on DEXTERITY:\n";
						if(!(std::cin >> amnt))
						{
							std::cout << "Input Error: Invalid input\n";

							std::cin.clear();
							std::cin.ignore(10000, '\n');

							goto catcher;
						}

						for(int i = 0; i < amnt; i++)
						{
							play.inc_dex();
						}
					}
					//RAISE ACCURACY
					else if(ans == '4')
					{
						std::cout << "\nHow many Skill Points would you like to spend on ACCURACY:\n";
						if(!(std::cin >> amnt))
						{
							std::cout << "Input Error: Invalid input\n";

							std::cin.clear();
							std::cin.ignore(10000, '\n');

							goto catcher;
						}

						for(int i = 0; i < amnt; i++)
						{
							play.inc_acc();
						}
					}
					else if(ans == 'q' || ans == 'Q')
					{
						goto charm;
					}
					else
					{
						goto sp;
					}

					goto sp;
				}
				//(WIP)
/*				else if(ans == '3')
				{
					inventory:

                                        clear_screen();
                                        rlutil::setColor(1);
                                        border3();
                                        border();
                                        std::cout << "||            Inventory                  ||\n";
                                        border();
                                        border3();
                                        rlutil::setColor(7);
                                        std::cout << "\n(1): View weapons               \n";
                                        std::cout << "(2): View armor                 \n";
                                        std::cout << "(3): View boots                 \n";
                                        std::cout << "(4): View misc                  \n";
                                        std::cout << "(Q): Return to character menu\n\n";
                                        rlutil::setColor(1);
                                        border3();
                                        std::cout << "SELECTION: ";

                                        if(!(std::cin >> ans))
                                        {
                                                std::cout << "Input Error: Invalid input, please retry.\n";
                                                std::cin.clear();
                                                std::cin.ignore(10000, '\n');

                                                goto inventory;
                                        }

					 if(ans == '1')
                                                play.show_weapons();
                                        else if(ans == '2')
                                                play.show_armor();
                                        else if(ans == '3')
                                                play.show_boots();
                                        else if(ans == '4')
                                                play.show_misc();
                                        else if(ans == 'Q' || ans == 'q')
                                                goto charm;
                                        else
                                                std::cout << "Invalid choice!\n";
                                        // Now equip or use an item if the player has items to equip or use
                                        if(ans == '1' && play.get_weapons_length() == 0) {
                                                std::cout << "\nNo weapons available!\n";
                                                standby();
                                                goto charm;
                                        }
                                        else if(ans == '2' && play.get_armor_length() == 0) {
                                                std::cout << "\nNo armor available!\n";
                                                standby();
                                                goto charm;
                                        }
                                        else if(ans == '3' && play.get_boots_length() == 0) {
                                                std::cout << "\nNo boots available!\n";
                                                standby();
                                                goto charm;
                                        }
                                        else if(ans == '4' && play.get_misc_length() == 0) {
                                                std::cout << "\nNo misc items available!\n";
                                                standby();
                                                goto charm;
                                        }

					std::cout << "\n";
                                        border3();
                                        rlutil::setColor(7);
                                        std::cout << "\n(1) Equip/use\n(2) Quit\n\n";
                                        rlutil::setColor(1);
                                        border3();
                                        std::cout << "\nSELECTION: ";
                                        if(!(std::cin >> ans))
                                        {
                                                std::cout << "Input Error: Invalid input, please retry.\n";
                                                std::cin.clear();
                                                std::cin.ignore(10000, '\n');
                                        }

                                        // If equip/use, go to equip function
                                        // Otherwise go back to charm
                                        if(ans == '1')
                                                play.equip();
                                        else if(ans == 'q' || ans == 'Q')
                                                goto charm;

                                        std::cin.clear();
                                        std::cin.ignore();
				}*/
				// Return to map/go to map
				else if(ans == '4') {
					// Determine which floor we were on by checking completion status of all maps starting at the beginning
					int floor_num;
					bool found_floor = false;
					for(int i = 0; i < 10; i++) {
						if(maps[i].getQuit() == false && !found_floor) {
							floor_num = i;
							found_floor = true;
						}
					}
					// On floor i, so load that map.
					maps[floor_num].gameCycle();

					//Where monsters will be determined at
					//Chance of an extra tough monster maybe? game is too ez!!
					if(maps[floor_num].getEncounter())
					{
						Monster new_mon = create_mon_name();

						//CHECK IDENTIFIERS

						new_mon.set_level(play.get_level());
						new_mon.validate_monster();

						Battle btl(play, new_mon);

						//buffered input
						//tcsetattr(STDIN_FILENO, TCSANOW, &old_tio);

						//int outcome = battle_scene_v2(&btl, &play);
						play = battle_scene_v2(&btl);

						if(play.get_hp() == 0)
						{
							//MECHANIC IDEA: Character gets deleted upon death?
							remove_char(play.get_char_name(), chars, temp);

							goto main;
						}
						else
						{
							remove_char(play.get_char_name(), chars, temp);
							save_char(play, chars);

							goto charm;
						}
					}
				}
				else if(ans == 's' || ans == 'S')
				{
					shop:
					shop_menu(play);
					std::cout << "SELECTION:   ";

					if(!(std::cin >> ans))
					{
						std::cout << "Input Error: Invalid input\n";

						std::cin.clear();
						std::cin.ignore(10000, '\n');

						goto shop;
					}

					if(ans == '1')
					{
						cost = ((play.get_max_mana() - play.get_mana())*2) + ((play.get_max_hp() - play.get_hp())*2);
						if(play.get_gold() < cost)
						{
							clear_screen();
							border2();
							rlutil::setColor(7);
							std::cout << "\n     You don't have enough gold!!!\n\n";
							border2();
							standby();

							goto shop;
						}
						else
						{
							if(play.get_hp() == play.get_max_hp() && play.get_mana() == play.get_max_mana())
							{
								clear_screen();
								border2();
								rlutil::setColor(7);
								std::cout << "\n    You are already at max HP / MP!!!\n\n";
								border2();
								standby();

								goto shop;
							}

							play.dec_gold(cost);
							play.set_hp(play.get_max_hp());
							play.set_mana(play.get_max_mana());

							clear_screen();
							border2();
							rlutil::setColor(7);
							std::cout << "\n   You are restored to max HP / MP!!!\n\n";
							border2();
							standby();

							goto shop;
						}
					}
					if(ans == '2')
					{
						if(play.get_gold() < 25)
						{
							clear_screen();
							border2();
							rlutil::setColor(7);
							std::cout << "\n     You don't have enough gold!!!\n\n";
							border2();
							standby();

							goto shop;
						}
						else
						{
							play.dec_gold(25);
							play.inc_hp(10);
							play.inc_mana(5);

							clear_screen();
							border2();
							rlutil::setColor(7);
							std::cout << "\n      You restored 10 HP / 5 MP!!!\n\n";
							border2();
							standby();

							goto shop;
						}
					}
					else if(ans == '3')
					{
						cost = 25 * ((play.get_gold_mult()/0.25)-3);

						if(play.get_gold() < cost)
						{
							clear_screen();
							border2();
							rlutil::setColor(7);
							std::cout << "\n     You don't have enough gold!!!\n\n";
							border2();
							standby();

							goto shop;
						}
						else
						{
							play.inc_gold_mult();
							play.dec_gold(cost);

							goto shop;
						}
					}
					else if(ans == '4' && play.get_rich_num() < 4)
					{
						if(play.get_rich_num() == 0)
						{
							cost = 200;
						}
						else if(play.get_rich_num() == 1)
						{
							cost = 400;
						}
						else if(play.get_rich_num() == 2)
						{
							cost = 1200;
						}
						else if(play.get_rich_num() == 3)
						{
							cost = 20000;
						}

						if(play.get_gold() < cost)
						{
							clear_screen();
							border2();
							rlutil::setColor(7);
							std::cout << "\n     You don't have enough gold!!!\n\n";
							border2();
							standby();

							goto shop;
						}
						else
						{
							play.inc_rich();
							play.dec_gold(cost);

							goto shop;
						}
					}
					else if(ans == 'q' || ans == 'Q')
					{
						goto charm;
					}
					else
					{
						goto shop;
					}
				}
				else if(ans == 'q' || ans == 'Q')
				{
					remove_char(play.get_char_name(), chars, temp);
					save_char(play, chars);

					goto main;
				}
				//TESTING PURPOSES
/*				else if(ans == 'P')
				{
					play.set_hp(play.get_max_hp());
					play.set_mana(play.get_max_mana());
				}
*/			}
		}
		else if(ans == 'q' || ans == 'Q')
		{
			//buffered input
			//tcsetattr(STDIN_FILENO, TCSANOW, &old_tio);

			std::cout << "\nPeace\n";
		}
	}

	return 0;
}
