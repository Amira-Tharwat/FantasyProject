#include "Squad.h"

class User
{
public:
	string Name;
	int Id;
	string Password;
	map<int,Squad>squad;
	User(void);
	User(string, string);
	void chooseLeague(int);
	void Home();
	void setSquad();
	void RemovePlayer(int);
	void ShowPoints();
	void showRank();
	void GetUsers(const vector<User>&);
	void PickSquad(int);
	void TransfersSquad();
};

