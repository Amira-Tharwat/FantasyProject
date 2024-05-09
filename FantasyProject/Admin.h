#include "Leagues.h"
#include "Validation.h"
class Admin
{

public:
	string Name;
	string Password;
	int Id;

	Admin(void);
	Admin(int, string, string);
	static int  Home();
	static void AddTeam();
	static int SetLeagueId(const vector<User>&);
	static void RemoveTeam();
	static void AddPlayer();
	static void RemovePlayer();
    static void AddPlayer(int);
	static void AddRound();
	static void AddMatch();
	static void RemoveMatch();
	static void clacPoints(int,Match);
	static void setResult();
	static void setSquadfortowteams(int,int);
};

