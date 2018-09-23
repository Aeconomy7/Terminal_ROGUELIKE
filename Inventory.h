#ifndef INVENTORY_H
#define INVENTORY_H

#include <iostream>
#include "Item.h"
using namespace std;

struct node {

	Item some_item;
	node * next;

};

class Inventory {

	private:
		// Contains all of our items.
		node * items;
		node * tail;
		// For determining if the user can place a num in a certain position.
		int length;
	public:
		Inventory();
		// Setters, getters
		node * getItems();
		node * getTail();
		node * getItem(int x);
		void setItems(node * input);
		void setTail(node * input);
		void changeLength(int change);
		int getLength();
		// Functions for manipulating the Linked List's data.
		void insertItem(int, char n[], string d, string t, double v, double str, double dex, double intel, double res);
		void deleteItem(int input);
		node * searchItem(int input);
		double searchItemStr(int input);
		double searchItemDex(int input);
		double searchItemInt(int input);
		double searchItemRes(int input);
		void printList();

};

#endif
