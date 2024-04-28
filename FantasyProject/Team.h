#include "Player.h"
#include<map>
class Team
{
public:
	string TeamName;
	int TeamId;
	map <int, Player> Players;
	int LeagueId;
	Team(void);
	Team( string , int );
	void static setId();

};

