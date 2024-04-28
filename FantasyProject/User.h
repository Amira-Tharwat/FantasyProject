#include<iostream>
#include <vector>
#include "Squad.h"
using namespace std;
class User
{

public:
	string Name;
	int Id;
	string Password;
	float Budget;
	vector<Squad> squad[4]; 
	User(void);
	User(string, string);
    void setSquad(); 
	void updateSquad();
	void showRank();
};

