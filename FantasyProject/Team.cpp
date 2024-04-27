#include "Team.h"
static int CountTeamId = 0;
Team::Team() {
	CountTeamId++;
	TeamId = CountTeamId;
}
Team::Team(string TName, int TId) {
	CountTeamId++;
	TeamId = CountTeamId;
	TeamName = TName;
	TeamId = TId;

}
void Team::setId() {
	CountTeamId--;
}
