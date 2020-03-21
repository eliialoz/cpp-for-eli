/*
File: main.cpp
Description:
Course: 150018 C++ Workshop, Exercise 1, Question 1
Author: Dan Zilberstein
Students: eli iluz 311201354
		& avishay farkash 205918790
*/
#include <iostream>
#include <iomanip>
#include "mytypes.h"
#include "bus.h"
//#include "line.h"

using namespace std;

// These are all of the main menu options.  Note that the numbers:
// 0, 1, 2, etc., show up /nowhere/ in the code, even though the
// user will see them on the screen, and will input them for
// choosing a menu option.
// Add your menu options according the the exercise requirements
enum MenuOption {
	EXIT_MENU,
	CREATE_BUS_50_SITS,
	CREATE_BUS_N_SITS,
	ASSIGN_LINE_TO_BUS,
	ASSIGN_DRIVER_TO_BUS,
	REMOVE_BUS,
	SHOW_AMOUNT_OF_BUSES,
	SHOW_BUS,
	SHOW_LINE,
	SHOW_ALL_BUSES,
	// a neat trick for for-loop initial and final values
	FIRST_MENU_OPTION = EXIT_MENU,
	LAST_MENU_OPTION = SHOW_ALL_BUSES
};

// These strings will be seen by the user, on the main menu.  They
// must be kept consistent with the operations of menu_option
// above.
const char* const menuOptionStrings[] = {
	"exit the program",
	"create a bus with 50 seats",
	"create a bus with N seats",
	"assign line to a bus",
	"assign driver to a bus",
	"remove a bus from the fleet",
	"show the amount of the buses in the fleet",
	"show a bus information",
	"show line bus list",
	"show all the the buses in the fleet"
};

// Function main - this is the entry code for the program
// It prints menu and performs the action according to the chosen option.
int main(void) {
	MenuOption chosen;

	// Everything happens inside of this do-while loop, until the user
	//     has decided to exit (or an error occurs).
	do {
		cout << endl << "Menu options:" << endl << endl;

		const int menuIndent = 10;

		// The user will see:
		//
		//           0 -- exit
		//           1 -- set dollars to shekkels conversion rate
		//           2 -- input an account
		// etc.
		//
		// The casts are for doing the "++" as an int type since
		// they are not allowed as a MenuOption type.
		for (chosen = FIRST_MENU_OPTION; chosen <= LAST_MENU_OPTION;
			chosen = (MenuOption)((int)chosen + 1)) {
			cout << setw(menuIndent) << " " << chosen << " -- ";
			cout << menuOptionStrings[chosen] << endl;
		}
		cout << endl;

		int chosenInt;
		cout << "Please choose a menu option: ";
		cin >> chosenInt;
		// After the user has input an int, it is cast to a
		//   MenuOption variable.
		chosen = (MenuOption)chosenInt;

		Bus* bus;
		int id, line, seats;
		//Assumes that the name is not greater than 100 characters
		cstring driverName = new char(101);

		// Note how the individual cases, match nicely to the
		//     operations they will perform.
		switch (chosen)
		{
		case EXIT_MENU:
			cout << "Thanx for using Bus Fleet Management Program!" << endl;
			break;
		case CREATE_BUS_50_SITS:
			cout << "\nEnter ID licence(between 1 to 9999) for the new bus: " << endl;
			cin >> id;

			if (!busCtor(id))
				cout << "ERROR" << endl;
			break;
		case CREATE_BUS_N_SITS:
			cout << "\nEnter ID licence(between 1 to 9999) for the new bus:" << endl;
			cin >> id;
			cout << "Enter number of seats(between 8 to 60) for the new bus:" << endl;
			cin >> seats;

			if (!busCtor(id, seats)) 
				cout << "ERROR" << endl;
			break;
		case ASSIGN_LINE_TO_BUS:
			cout << "\nEnter ID licence(between 1 to 9999) for the bus that you want to assign a line:" << endl;
			cin >> id;
			cout << "Enter a number between 1 to 9 to assign a line," << endl << "to unassign enter 0:" << endl;
			cin >> line;

			if (!(bus = getBus(id)) || !busLine(*getBus(id), line))
				cout << "ERROR" << endl;
			break;
		case ASSIGN_DRIVER_TO_BUS:
			cout << "\nEnter ID licence(between 1 to 9999) for the bus that you want to assign a line:" << endl;
			cin >> id;
			cout << "Enter a name(til 100 charecters) to assign a name for a driver:" << endl;
			cin >> setw(101) >> driverName;

			if (!(bus = getBus(id)) || !busDriver(*bus, driverName))
				cout << "ERROR" << endl;
			break;
		case REMOVE_BUS:
			cout << "\nEnter ID licence(between 1 to 9999) for the bus that you want to delete:" << endl;
			cin >> id;

			if (!delBus(id))
				cout << "ERROR" << endl;
			break;
		case SHOW_AMOUNT_OF_BUSES:
			cout << "\nAmount of buses: " << busFleetCount << endl;
			break;
		case SHOW_BUS:
			cout << "\nEnter the ID licence(between 1 to 9999) of the bus that you want to see his details:" << endl;
			cin >> id;
			if (bus = getBus(id))
				busPrint(*bus);
			else
				cout << "ID Not found" << endl;
			break;
		case SHOW_LINE:
			cout << "\nEnter the line that you want to see his details:" << endl;
			cin >> line;
			if (lineGetAmount(line))
				for (uint i = 0; i < lineGetAmount(line); i++)
				{
					busPrint(*getBus(lineGetBuses(line)[i]));
					cout << endl;
				}
			else
				cout << "there isnt buses in this line" << endl;
			break;
		case SHOW_ALL_BUSES:
			if (busFleetCount)
				busesPrint();
			else
				cout << "there isnt buses in the fleet" << endl;
			break;
		default:
			cout << "ERROR" << endl;
			break;
		}
	} while (chosen != EXIT_MENU);

	// destroying all the data and freeing all the memory
	busFleetDtor();

	return 0;
}
