#include "rlutil.h"
#include "Inventory.h"
#include <iostream>
#include <string>
using namespace std;

// Constructor
Inventory::Inventory() {
	items= NULL;
	tail = NULL;
	length = 0;
}


/***********
* Getters  *
************/

// Returns the current node at index x in our linked list
node * Inventory::getItem(int x) {
	node * temp_node;
	temp_node = items;

	for(int i = 0; i < x; i++)
		temp_node = temp_node->next;

	return temp_node;

}

// Returns whatever element we're at in the linked list
node * Inventory::getItems() {
	return items;
}
// Returns the last element of the linked list
node * Inventory::getTail() {
	return tail;
}
// Returns the length of the linked list
int Inventory::getLength() {
	return length;
}

/************
* Setters   *
*************/

// Sets node integer to input
void Inventory::setItems(node * input) {
	items = input;
}
// Sets node tail to input
void Inventory::setTail(node * input) {
	tail = input;
}
// Increases or decreases length, based on input of change
void Inventory::changeLength(int change) {
	length = length + change;
}


/**********************************
* Functions for manipulating data *
**********************************/

// Insert a new node the list with num = value.
void Inventory::insertItem(int i, char name[], string type, string description, double value, double str, double dex, double intel, double res) {
	
	// Two cases: 
		// 1) Item is an item with scaling. In this case, any weapon, armor, or boots.
		// 2) Item is misc. In this case, we will set each scaling value to 0.0 and then just not display it by checking what type we're printing when displaying misc info.
		//    which is what our input values will be anyways, we just had to acknowledge that we will have to not display it otherwise it'll look weird.
	// Node to append to list
	node * addValue = new node;
	addValue->some_item.set_item_num(i);
	addValue->some_item.set_name(name);
	addValue->some_item.set_type(type);
	addValue->some_item.set_description(description);
	addValue->some_item.set_stat_value(value);
	addValue->some_item.set_str_scaling(str);
	addValue->some_item.set_dex_scaling(dex);
	addValue->some_item.set_int_scaling(intel);
	addValue->some_item.set_res_scaling(res);
	addValue->next = NULL;
	//cout << "Inserting " << name << endl;
	// If list is empty, simply add our node, make head and tail equal to it
	if(items == NULL) {
		items = addValue;
		tail = addValue;
		changeLength(1);
	}
	// If list has more than 0 elements, add it to the tail
	else {
		// Make the tail's next slot the value we're adding
		tail->next = addValue;
		// Then make the tail that new value to expand it out
		tail = tail->next;
		changeLength(1);
	}
	return;
	
}

// Delete a node by its value.
void Inventory::deleteItem(int input) {

	node * start = NULL;
	node * item_to_delete = NULL;
	node * tail = NULL;

	// Check if our beginning of the LL is the value
	if(items->some_item.get_item_num() == input) {
		// If it does, current node is the one to delete.
		item_to_delete = items;
		// Make the next value our new head
		items = item_to_delete->next;
		// Now delete it
		delete item_to_delete;
		changeLength(-1);
		// Print updated values
		printList();
		// Done
		return;
	}

	// If it is not...
	start = items;
	tail  = items->next;
	
	while(tail != NULL) {
		// If the next node contains the value, delete it
		if(tail->some_item.get_item_num() == input) {
			// Change the next value of integers to the value after del since we're deleting the node between them
			start->next = tail->next;
			// Now delete it
			delete tail;
			changeLength(-1);
			// Done
			break;
		}
		// If no match was found, move on
		else {
			start = tail;
			tail = tail->next;
		}
	}

} 


// Search and return the index # for the value
node * Inventory::searchItem(int input) {
	int element = 1;
	bool found = false;
	node * copy = items;
	// loop until found (or end of list is reached, in which case tell user it was not found)
	while(copy != NULL && !found) {
		
		if(copy->some_item.get_item_num() == input) {
			found = true;
			return copy;
		}
		else {
			copy = copy->next;
			element++;
		}
	}
	if(!found) {
		cout << "**Item not found!" << endl;
		copy = NULL;
		return copy;
	}
}

double Inventory::searchItemStr(int input) {
	// Decide which item to use
	node * equipment = searchItem(input);
	// now return its str scaling
	if(equipment == NULL)
		return 0.0;
	else
		return equipment->some_item.get_str_scaling();
	
}

double Inventory::searchItemDex(int input) {
	// Decide which item to use
        node * equipment = searchItem(input);
        // now return its dex scaling
	if(equipment == NULL)
		return 0.0;
	else
        	return equipment->some_item.get_dex_scaling();
	
}

double Inventory::searchItemInt(int input) {
	// Decide which item to use
        node * equipment = searchItem(input);
        // now return its int scaling
	if(equipment == NULL)
		return 0.0;
	else
        	return equipment->some_item.get_int_scaling();

}

double Inventory::searchItemRes(int input) {
	// Decide which item to use
        node * equipment = searchItem(input);
        // now return its res scaling
	if(equipment == NULL)
		return 0.0;
        else
		return equipment->some_item.get_res_scaling();

}

void Inventory::printList() {
	rlutil::setColor(9);
	cout << "\n--------------------------------\n";
	rlutil::setColor(4);
	node * printer = items;
	if(printer != NULL)
		cout << printer->some_item.get_type() << " (NAME / DESCRIPTION / STAT VALUE / STR SCALING / DEX SCALING / INT SCALING / RES SCALING)" << endl;	
	else
		cout << "\nNo items yet! Go get some!\n";
	rlutil::setColor(15);
	while(printer != NULL) {
		cout << "(" << printer->some_item.get_item_num() << ") " << printer->some_item.get_name() << " / " << printer->some_item.get_description() << " / " << printer->some_item.get_stat_value();
		cout << " / " << printer->some_item.get_str_scaling() << " / " << printer->some_item.get_dex_scaling() << " / " << printer->some_item.get_int_scaling();
		cout << " / " << printer->some_item.get_res_scaling() << "\n";
		
		printer = printer->next;
	}
	rlutil::setColor(9);
	cout << "\n--------------------------------" << endl;
}
