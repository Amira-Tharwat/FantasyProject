#include "Team.h"
#include <vector>
class Match
{
public:
	Team *team1, *team2;
	int res1, res2;
	map<int,map<int,Player*>>XI;
	map<int,map<int, Player*>>pdla;
	map <string,map<int,int>> Details;
	int MatchId;
	bool isPlayed;
	Match();
};

