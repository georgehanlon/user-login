#include "commandHelp.h"
#include <string>
#include <iostream>

using namespace std;

void commandHelp::userCmds()
{
	cout << \
		"--------------------------------------------\n" \
		"| User Commands                            |\n" \
		"|                                          |\n" \
		"|  Command Name        Function            |\n" \
		"|------------------------------------------|\n" \
		"|  user -n          |  create new user     |\n" \
		"|  user -d          |  delete user         |\n" \
		"|  user -l          |  list all users      |\n" \
		"--------------------------------------------\n\n\n";
}

void commandHelp::systemCmds()
{
	cout << \
		"--------------------------------------------\n" \
		"| System Commands                          |\n" \
		"|                                          |\n" \
		"|  Command Name        Function            |\n" \
		"|------------------------------------------|\n" \
		"|  login            |  start login process |\n" \
		"|  logout           |  user is logged out  |\n" \
		"|  quit             |  exit program        |\n" \
		"--------------------------------------------\n\n\n";
}

void commandHelp::help()
{
	cout << \
		"--------------------------------------------\n" \
		"| Availible Commands                       |\n" \
		"|                                          |\n" \
		"|  Command Name        Function            |\n" \
		"|------------------------------------------|\n" \
		"|  help -user       |  user processes help |\n" \
		"|  help -system     |  system process help |\n" \
		"|  help             |  brings up this      |\n" \
		"|                   |  menu                |\n" \
		"--------------------------------------------\n\n\n";
}
