#include "Player.h"
#include <vector>
#include <stack>
class Squad
{
public:
	map <string,vector<Player>>squads;  
	stack <Player> deka ;
	map<int, int> RoundPoints;
	int TotalPoints;
	Player captain , ViceCaptain;
	bool tribleCaptain , wildCard;
	int numOfSubestitution; 
	Squad();
};

