#include "Squad.h"
#include<vector>
class User
{
public:
	string Name;
	int Id;
	string Password;
	float Budget;
	map<int,Squad>squad;
	User(void);
	User(string, string);
	void chooseLeague(int);
	void Home();
	void setSquad();
	void RemovePlayer();
	//void LogOut();
	void ShowPoints();
	void showRank();
	void GetUsers(const vector<User>&);
	/*void PickSquad();
	void TransfersSquad();*/
	
};

