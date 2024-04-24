#include "Team.h"
#include <iostream>
Team::Team() {
	TeamId = CountTeamId;
	CountTeamId++;
}
//Team::Team(string TName, int TId) {
//	TeamName = TName;
//	TeamId = TId;
//	
//}
