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

int main()
{
	rlutil::setBackgroundColor(0);
	clear_screen();

	for(int i = 0; i < 16; i++)
	{
		rlutil::setColor(i);
		std::cout << "THIS IS COLOR #" << i << "\n\n";
	}

	return 0;
}
