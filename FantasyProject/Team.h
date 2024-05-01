#include "Player.h"

class Team
{
public:
	string TeamName;
	int TeamId;
	map <int, Player> Players;
	int LeagueId;
	Team(void);
	Team( string , int );
	

};

