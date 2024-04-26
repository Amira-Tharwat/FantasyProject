#pragma once
#include <queue>
#include"Match.h"
using namespace std;
class Round
{
public :
	int roundId;
	queue<Match> matches;
	Round();
};

