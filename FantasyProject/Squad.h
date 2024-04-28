#include "Player.h"
#include <map>
#include <vector>
#include <stack>
class Squad
{
public:
	map < string, vector<Player> > squad;  
	stack <Player> deka ;
	map<int, int> RoundPoints;
	int TotalPoints;
	Player captain , ViceCaptain;
	bool tribleCaptain , wildCard;
	int numOfSubestitution; 
	Squad();
};

