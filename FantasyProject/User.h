#include "Squad.h"
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
	/*void showRank();
	void LogOut();
	void ShowPoints();
	void PickSquad();
	void TransfersSquad();*/
};

