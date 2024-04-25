#include "Admin.h"
#include "Player.h"
#include "League.h"
#include "Leagues.h"
#include "Team.h"
#include<map>
using namespace std;

int LeagueId;
Admin::Admin(void){}
Admin::Admin(string name, string password,int id)
{
	Name = name;
	Password = password;
	Id = id;
}
void Admin::Home()
{
	cout << "Please Enter\n";
	cout << "1- Add Team\n";
	cout << "2- Remove Team\n";
	cout << "3- Add Player\n";
	cout << "4- Remove Player\n";
	cout << "5- Add Round\n";
	cout << "6- End Round\n";
	cout << "7- View All users\n";
	
	 
	int answer;
	cin >> answer;
	switch (answer)
	{
	case 1:
		Admin::AddTeam();
		break;

	case 2:
		Admin::RemoveTeam();
		break;

	case 3:
		Admin::AddPlayer();
		break;

	case 4:
		//Call Remove Player
		break;

	case 5:
		// Call Add Round
		break;
	case 6:
		//Call End Round
		break;
	case 7:
		//Call  View All users
		break;
	}
		

}
void Admin::AddTeam() {
	
	Team team = Team();
	cout << "Enter The Team Name : ";
	cin >> team.TeamName;
	cout << "Team " << team.TeamName << " is added successfully :)" << endl;
	team.TeamId = LeagueId;
	Leagues::leagues[LeagueId].teams[team.TeamId] = team;
	Home();
}
void Admin::RemoveTeam() {

	int tID;
	for (auto i = Leagues::leagues[LeagueId].teams.begin(); i != Leagues::leagues[LeagueId].teams.end(); i++)
		cout << i->first << "\t" << i->second.TeamName<< endl;
	cout << "Enter The Team Id : ";
	cin >> tID;
	Team teamRemove = Leagues::leagues[LeagueId].teams[tID];
	cout << "Team " << teamRemove.TeamName << " is Removed successfully :)" << endl;
	Leagues::leagues[LeagueId].teams.erase(tID);
}
void Admin::AddPlayer() {

	Player p = Player();
	int tID, ans;
	cout << "Enter Player Name";
	cin >> p.PlayerName;
	cout << "Enter Player Position";
	cin >> p.PlayerPosition;
	cout << "Enter Player Price";
	cin >> p.PlayerPrice;
	while (true) {
		for (auto i = Leagues::leagues[LeagueId].teams.begin(); i != Leagues::leagues[LeagueId].teams.end(); i++)
			cout << i->first << "\t" << i->second.TeamName << endl;
		cout << "Enter The Team Id : ";
		cin >> tID;
		auto s = Leagues::leagues[LeagueId].teams.find(tID);
		if (s != Leagues::leagues[LeagueId].teams.end()) {
			cin >> ans;
			while (ans != 1 && ans != 2) {
				cout << "This Team Id Not Available \n 1- try again 2-Exit";
				cin >> ans;
				switch (ans)
				{
				case 1:
					AddPlayer();
				case 2:
					Admin::Home();

				default:
					cout << "Invalid Answer \n ";
				}

			}

		}
		break;
	}
}