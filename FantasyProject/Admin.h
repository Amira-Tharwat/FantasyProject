#pragma once
#include <iostream>
#include <vector>
using namespace std;
 class  Admin
{
public:
	string Name;
	string Password;
	int Id;
public :
	Admin(void);
	Admin(string, string,int);
	
	static  void  Home();
	void AddTeam();
};

