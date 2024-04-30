#include "Match.h"
#include<queue>
class Round
{
public:
	int roundId;
	int leagueId;
	queue<Match> matches;
	Round();
};

