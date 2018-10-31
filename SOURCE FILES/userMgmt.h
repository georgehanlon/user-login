#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;

class userMgmt
{
public:
	void loadUsers();
	void updateFile();
	string getPassword();
	void addUser();
	void deleteUser();
	void displayUsers();
	void login();
	void logout();
	string encrypt(string pwd);
	struct user //had to define here else gave error if tried to define in .cpp
	{
		string username;
		string passwordHash;
		char userType; //admin or user
	};
private:
	fstream varFile;
	fstream userFile;
	int numUsers;
	string tempPass;
	string tempUsnm;
	vector<user> list_of_users;
	string input;
	string deleteconf;
	bool add_user_bool;
	bool delete_user_bool;
	bool userHit;
	bool loginBool;
	bool usernameMatch;
	bool pass_hash_match;
	bool adminBool;
	int usnmIndex;
};