#include "userMgmt.h"
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <stdexcept>
#include <Windows.h>
#include <conio.h>
#include <algorithm>
#include "cryptopp\filters.h"
#include "cryptopp\hex.h"
#include "cryptopp\sha.h"
using namespace std;


void userMgmt::loadUsers() //updates the struct from the file of users
{
	varFile.open("userFiles/values.txt", ios::in); //opens file to read
	varFile >> numUsers; //gets the number of user entries that already exist
	varFile.close();

	userFile.open("userFiles/userDB.txt", ios::in); //opens file for reading
	for (int i = 0; i < numUsers; i++) //reads existing users and puts into array of structs
	{
		list_of_users.push_back(user()); //pushback new user with default constructor to give vector an element at index value
		userFile >> list_of_users[i].username >> list_of_users[i].passwordHash >> list_of_users[i].userType;
		//cout << list_of_users[i].username << " is usnm " << list_of_users[i].passwordHash << endl;
	}
	userFile.close();
}

void userMgmt::updateFile()
{
	varFile.open("userFiles/values.txt", ios::out);
	varFile << numUsers; //gets the number of user entries that already exist
	varFile.close();

	userFile.open("userFiles/userDB.txt", ios::out); //opens file for reading
	for (int i = 0; i < numUsers; i++) //reads existing users and puts into array of structs
	{
		list_of_users.push_back(user()); //pushback new user with default constructor to give vector an element at index value
		userFile << list_of_users[i].username << "\t" << list_of_users[i].passwordHash << " " << list_of_users[i].userType << "\n";
	}
	userFile.close();
}

string userMgmt::getPassword()
{
	string password;

	char input = _getch();
	while (input != '\r') // \r means return key
	{
		password += input;
		input = _getch();
	}

	cout << endl;

	return password;
}

void userMgmt::addUser()
{
	if (adminBool == true)
	{
		loadUsers(); //to update the vector
		add_user_bool = false;
		bool userHit = true;
		bool breakBool = false;

		cout << "Username up to 12 char, Password up to 25 char, enter CANCEL as username to exit process\n";
		list_of_users.push_back(user());

		while (add_user_bool == false)
		{
			cout << "Enter a username: ";
			getline(cin, tempUsnm);
			tempUsnm.erase(remove(tempUsnm.begin(), tempUsnm.end(), ' '), tempUsnm.end()); //removes any whitespaces if user enters any
			if (tempUsnm == "CANCEL")
			{
				cout << "Create user process terminated\n\n";
				breakBool = true;
				break;
			}
			for (int i = 0; i < numUsers; i++)
			{
				if (tempUsnm == list_of_users[i].username) //checks if username already taken
				{
					cout << "Username already taken, please try another\n\n";
					break;
				}
				if (i == (numUsers - 1)) //if at end of struct
				{
					userHit = false;
				}
				if (tempUsnm != "" && tempUsnm.length() < 12 && userHit == false)
				{
					add_user_bool = true;
					list_of_users[numUsers].username = tempUsnm; //write to struct
				}
			}
		}

		if (breakBool == true)
		{
			return;
		}

		while (tempPass == "" || tempPass.length() > 25)
		{
			cout << "Enter password: ";
			tempPass = getPassword();
		}
		tempPass = encrypt(tempPass); //create hash
		list_of_users[numUsers].passwordHash = tempPass;

		while (list_of_users[numUsers].userType != 'a' && list_of_users[numUsers].userType != 'u') //continues loop until valid user type chosen
		{
			cout << "Enter user type (a = admin, u = default user): ";
			cin >> list_of_users[numUsers].userType;
		}

		userFile.open("userFiles/userDB.txt", ios::app); //write new user to file
		userFile << list_of_users[numUsers].username << "\t" << list_of_users[numUsers].passwordHash << " " << list_of_users[numUsers].userType << "\n";
		userFile.close();

		numUsers += 1;
		varFile.open("userFiles/values.txt", ios::out); //update num of users
		varFile << numUsers;
		varFile.close();

		cout << "User " << list_of_users[numUsers-1].username << ", successfully created\n\n";
	}
	else
	{
		cout << "You do not have permissions to do this, login to an admin account\n\n";
	}
	
}

void userMgmt::deleteUser()
{
	if (adminBool == true)
	{
		loadUsers(); //update the struct
		delete_user_bool = false;
		userHit = false;
		tempUsnm = "";
		deleteconf = "";
		
		cout << "Enter username of user to delete, or CANCEL to cancel\n";

		while (delete_user_bool == false)
		{
			cout << "Username to delete: ";
			getline(cin, tempUsnm);
			if (tempUsnm != "CANCEL")
			{
				for (int i = 0; i < numUsers; i++)
				{
					if (tempUsnm == list_of_users[i].username) //if find match
					{
						while (deleteconf != "y" && deleteconf != "n") //confirms if want to delete
						{
							userHit = true;
							cout << "Deleting user: " << list_of_users[i].username << ", are you sure?(y/n): ";
							getline(cin, deleteconf);
							if (deleteconf == "y")
							{
								cout << "User " << list_of_users[i].username << ", has been removed\n\n";
								list_of_users.erase(list_of_users.begin() + i); //removes entry [i] from vector
								numUsers -= 1;
								updateFile(); //update that 1 less user
								delete_user_bool = true;
								break;
							}
							else if (deleteconf == "n")
							{
								cout << "User delete process terminated\n\n";
								delete_user_bool = true;
								break;
							}
						}
					}
					if (i == (numUsers - 1) && userHit == false) //if no match found for username
					{
						cout << "Username not found\n\n";
					}
				}
			}
			else
			{
				cout << "User delete process terminated\n\n";
				break;
			}
		}
	}
	else
	{
		cout << "You do not have permissions to do this, login to an admin account\n\n";
	}
}

void userMgmt::displayUsers() //shows list of all users
{
	loadUsers();
	if (adminBool == true)
	{
		for (int i = 0; i < numUsers; i++)
		{
			cout << "User(" << i << "): " << list_of_users[i].username << "    " << list_of_users[i].passwordHash << " " << list_of_users[i].userType << endl;
		}
	}
	else
	{
		cout << "You do not have permissions to do this, login to an admin account";
	}
	cout << "\n\n";
}

void userMgmt::login()
{
	if (loginBool == true)
	{
		cout << "You must logout first\n\n";
	}
	else
	{
		loginBool = false;
	}
	usernameMatch = false;
	pass_hash_match = false;
	tempUsnm = "";
	tempPass = "";
	usnmIndex = 0;

	loadUsers(); //to update the struct incase any new users have been added since start of program

	while (loginBool == false)
	{
		while (usernameMatch == false) //check username exists
		{
			cout << "Username: ";
			getline(cin, tempUsnm); //get user inp
			if (tempUsnm != "")
			{
				for (int i = 0; i < numUsers; i++)
				{
					if (tempUsnm == list_of_users[i].username)
					{
						usnmIndex = i; //so know which password needs to be checked against
						usernameMatch = true;
						break;
					}
					if (i == (numUsers-1))
					{
						cout << "Username not found, please retry\n" << endl;
					}
				}
			}
		}
		while (pass_hash_match == false) //checks password matches
		{
			cout << "Password: ";
			tempPass = getPassword();
			if (tempPass != "")
			{
				tempPass = encrypt(tempPass);
				if (tempPass == list_of_users[usnmIndex].passwordHash)
				{
					pass_hash_match = true;
					break;
				}
			}
		}
		if (usernameMatch == true && pass_hash_match == true) //if both correct, login
		{
			if (list_of_users[usnmIndex].userType == 'a') //check if user is an admin
			{
				adminBool = true;
			}
			else
			{
				adminBool = false;
			}
			loginBool = true;
			cout << "\nCredentials OK, access granted\n\n";
		}
	}
	userFile.close();
}

void userMgmt::logout()
{
	if (loginBool == false)
	{
		cout << "You are not yet logged in\n\n";
	}
	else
	{
		adminBool = false;
		loginBool = false;
		cout << "You have been logged out\n\n";
	}
}

string userMgmt::encrypt(string pwd)
{
	//Following code sourced from https://stackoverflow.com/a/7045815
	CryptoPP::SHA256 hash; //uses SHA-2
	string digest; //the resulting hash
	string message = pwd;

	CryptoPP::StringSource s(message, true, new CryptoPP::HashFilter(hash, new CryptoPP::HexEncoder(new CryptoPP::StringSink(digest))));

	return digest;
	//End of sourced code from https://stackoverflow.com/a/7045815
}
