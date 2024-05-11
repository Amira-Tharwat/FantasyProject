#include "Player.h"
#include <vector>
#include <stack>
class Squad
{
public:
	map <int,map<string,vector<Player*>>>squads;  
	map<int,stack <Player*>> deka ;
	map<int, int> RoundPoints;
	int TotalPoints;
	Player *captain , *ViceCaptain;
	int  wildCard=1;
	int tribleCaptain=1;
	int numOfSubestitution;
	float Budget;
	Squad();
};