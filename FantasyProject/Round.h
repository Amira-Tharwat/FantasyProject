#include "Match.h"

class Round
{
public:
	int roundId;
	int leagueId;
	map<int,Match> matches;
	Round();
};

