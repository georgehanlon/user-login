#include <iostream>
#include <string>
#include "userMgmt.h"
#include "commandHelp.h"
using namespace std;


int main()
{
	string usrInp;
	commandHelp helpCenter; //creates object for help
	userMgmt user; //creates object for the user class
	user.loadUsers(); //update struct from file
	
	cout << "Type 'help' for list of commands or 'quit' to exit\n\n";

	while (usrInp != "quit")
	{
		usrInp = "";
		cout << ">>";
		getline(cin, usrInp);
		for (string::size_type i = 0; i < usrInp.length(); i++) //converts input to lower case
		{
			usrInp[i] = tolower(usrInp[i]);
		}

		if (usrInp == "user -n") //new user
		{
			user.addUser();
		}
		else if (usrInp == "user -d") //delete user
		{
			user.deleteUser();
		}
		else if (usrInp == "user -l") //list users
		{
			user.displayUsers();
		}
		else if (usrInp == "help") //displays list of commands
		{
			helpCenter.help();
		}
		else if (usrInp == "help -user") //help related to users
		{
			helpCenter.userCmds();
		}
		else if (usrInp == "help -system") //help related to system
		{
			helpCenter.systemCmds();
		}
		else if (usrInp == "login") //starts login process for users
		{
			user.login();
		}
		else if (usrInp == "logout") //logs user out only if they're logged in
		{
			user.logout();
		}
	}
	return 0;
}