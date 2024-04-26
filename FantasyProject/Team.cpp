#include "Team.h"
#include"Player.h"
#include <iostream>
using namespace std;

Team::Team() {
	CountTeamId++;
	TeamId = CountTeamId;
	
}
Team::Team(string TName, int TId) {
	TeamName = TName;
	TeamId = TId;
	
}
