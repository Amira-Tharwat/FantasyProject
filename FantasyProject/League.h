#include "Round.h"
class League
{
public:
	string LaegueName;
	int LeagueId;
	map<int, Team> teams;
	map<int, Player> Players;
	map<int, Round> rounds;
public:
	League();
	League(int, string);
};


