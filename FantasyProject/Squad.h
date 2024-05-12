#include "Player.h"
#include <vector>
#include <stack>
class Squad
{
public:
	map <int,map<string,vector<Player*>>>squads;  
	map<int,stack <Player*>> deka ;
	map<int, int> RoundPoints;
	int TotalPoints=0;
	Player *captain , *ViceCaptain;
	int  wildCard=1;
	int tribleCaptain=1;
	int numOfSubestitution=2;
	float Budget;
	Squad();
};