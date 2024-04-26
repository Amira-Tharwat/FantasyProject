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
void Admin::SetLeagueId()
{
	int legId;

	cout << "Please Enter League Id\n";
	cin >> legId;

	LeagueId = legId;
	Home();
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
		Admin::RemovePlayer();
		break;

	case 5:
		Admin::AddRound();
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
	Team team = Team();
	Player p = Player();
	int tID, ans;
	cout << "Enter Player Name";
	cin >> p.PlayerName;
	cout << "Enter Player Position";
	cin >> p.PlayerPosition;
	cout << "Enter Player Price";
	cin >> p.PlayerPrice;

	Leagues::leagues[LeagueId].teams[team.TeamId].Players[p.PlayerId]=p;
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

void Admin::RemovePlayer()
{
	int  tID,PID;
	for (auto i = Leagues::leagues[LeagueId].teams.begin(); i != Leagues::leagues[LeagueId].teams.end(); i++)
		cout << i->first << "\t" << i->second.TeamName << endl;
	cout << "Enter The Team Id : ";
	cin >> tID;
	for (auto i = Leagues::leagues[LeagueId].teams[tID].Players.begin(); i != Leagues::leagues[LeagueId].teams[tID].Players.end(); i++)
		cout << i->first << "\t"  <<  i->second.PlayerName << endl;
	cout << "Enter The Player Id : "; 
	cin >> PID;
	Leagues::leagues[LeagueId].teams[tID].Players.erase(PID);

	Player playerRemove = Leagues::leagues[LeagueId].teams[tID].Players[PID];
	cout << " Player" << playerRemove.PlayerName << " is Removed successfully :)" << endl;


}
void Admin::AddRound()
{
	int roundId;
	cout << "Enter number of Round\n";
	cin >> roundId;
	 map<int, Team> tempTeams;
	for (int i = 0; i < Leagues::leagues[LeagueId].teams.size() / 2; i++)
	{
	 
		int t = 2;
		int tID;
		Match match;
		while (t--)
		{
			
			for (auto i = Leagues::leagues[LeagueId].teams.begin(); i != Leagues::leagues[LeagueId].teams.end(); i++)
				cout << i->first << "\t" << i->second.TeamName << endl;
			cout << "Enter The Team Id For Match " << i+1<<" :\n";
			cin >> tID;
			tempTeams[tID] = Leagues::leagues[LeagueId].teams[tID];
			Leagues::leagues[LeagueId].teams.erase(tID);
			if (t == 1)
			{
				match.team1 = tempTeams[tID];
			}
			else 
				match.team2 = tempTeams[tID];
		}
		Leagues::leagues[LeagueId].rounds[roundId].matches.push(match);
    }
	for (auto i : tempTeams)
	{
		Leagues::leagues[LeagueId].teams[i.first] = i.second;
	}
}