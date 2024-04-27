#include "Admin.h"
#include "Leagues.h"

Leagues leagues = Leagues();
int LeagueId;
Admin::Admin() {}
Admin::Admin(int id, string name, string password)
{
	Name = name;
	Password = password;
	Id = id;
}
void Admin::SetLeagueId()
{
	int legId;
	for (int i = 1; i <= 3; i++) {
		cout << i << "\t"<<leagues.leagues[i].LaegueName<<endl;
	}
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
		AddTeam();
		break;

	case 2:
		RemoveTeam();

		break;

	case 3:
		AddPlayer();

		break;

	case 4:
		RemovePlayer();
		
		break;

	case 5:
		AddRound();

		break;
	case 6:
		RemoveRound();

		break;
	case 7:
		//Call  View All users
		break;
	}


}
void Admin::AddTeam() {

	Team team;
	cout << "Enter The Team Name : ";
	cin >> team.TeamName;
	cout << "Team " << team.TeamName << " is added successfully :)" << endl;
	team.LeagueId = LeagueId;
	leagues.leagues[LeagueId].teams[team.TeamId] = team;
	Team::setId();
	Home();
}
void Admin::RemoveTeam() {

	int tID;
	for (auto i = leagues.leagues[LeagueId].teams.begin(); i != leagues.leagues[LeagueId].teams.end(); i++)
		cout << i->first << "\t" << i->second.TeamName << endl;
	cout << "Enter The Team Id : ";
	cin >> tID;
	Team teamRemove = leagues.leagues[LeagueId].teams[tID];
	cout << "Team " << teamRemove.TeamName << " is Removed successfully :)" << endl;
	leagues.leagues[LeagueId].teams.erase(tID);
	Home();
}
void Admin::AddPlayer() {
	
	
	Player p = Player();
	int tID, ans = 0;
	cout << "Enter Player Name";
	cin >> p.PlayerName;
	cout << "Enter Player Position";
	cin >> p.PlayerPosition;
	cout << "Enter Player Price";
	cin >> p.PlayerPrice;
	while (true) {
		for (auto i = leagues.leagues[LeagueId].teams.begin(); i != leagues.leagues[LeagueId].teams.end(); i++)
			cout << i->first << "\t" << i->second.TeamName << endl;
		cout << "Enter The Team Id : ";
		cin >> tID;
		auto s = leagues.leagues[LeagueId].teams.find(tID);
		if (s == leagues.leagues[LeagueId].teams.end()) {
			cin >> ans;
			while (ans != 1 && ans != 2) {
				cout << "This Team Id Not Available \n 1- try again 2-Exit";
				cin >> ans;
				switch (ans)
				{
				case 1:
					AddPlayer();
				case 2:
					Home();

				default:
					cout << "Invalid Answer \n ";
				}

			}

		}
		else {
			leagues.leagues[LeagueId].Players[p.PlayerId] = p;
			leagues.leagues[LeagueId].teams[tID].Players[p.PlayerId]=p;
			Player::setId();
		}
		break;
	}
	Home();
}
void Admin::RemovePlayer()
{
	int  tID, PID;
	for (auto i = leagues.leagues[LeagueId].teams.begin(); i != leagues.leagues[LeagueId].teams.end(); i++)
		cout << i->first << "\t" << i->second.TeamName << endl;
	cout << "Enter The Team Id : ";
	cin >> tID;
	for (auto i = leagues.leagues[LeagueId].teams[tID].Players.begin(); i != leagues.leagues[LeagueId].teams[tID].Players.end(); i++)
		cout << i->first << "\t" << i->second.PlayerName << endl;
	cout << "Enter The Player Id : ";
	cin >> PID;
	leagues.leagues[LeagueId].teams[tID].Players.erase(PID);

	Player playerRemove = leagues.leagues[LeagueId].teams[tID].Players[PID];
	cout << " Player" << playerRemove.PlayerName << " is Removed successfully :)" << endl;
	Home();

}
void Admin::AddRound()
{
	int roundId;
	cout << "Enter number of Round\n";
	cin >> roundId;
	map<int, Team> tempTeams;
	for (int i = 0; i < leagues.leagues[LeagueId].teams.size() / 2; i++)
	{
		int t = 2;
		int tID;
		Match match;
		while (t--)
		{
			for (auto i = leagues.leagues[LeagueId].teams.begin(); i != leagues.leagues[LeagueId].teams.end(); i++)
				cout << i->first << "\t" << i->second.TeamName << endl;
			cout << "Enter The Team Id For Match " << i + 1 << " :\n";
			cin >> tID;
			tempTeams[tID] = leagues.leagues[LeagueId].teams[tID];
			leagues.leagues[LeagueId].teams.erase(tID);
			if (t == 1)
			{
				match.team1 = tempTeams[tID];
			}
			else
				match.team2 = tempTeams[tID];
		}
		leagues.leagues[LeagueId].rounds[roundId].matches.push(match);
	}
	for (auto i : tempTeams)
	{
		leagues.leagues[LeagueId].teams[i.first] = i.second;
	}
	Home();
}
void Admin::RemoveRound()
{
	int roundId;
	for (auto i = leagues.leagues[LeagueId].rounds.begin(); i != leagues.leagues[LeagueId].rounds.end(); i++)
	{
		cout << "Round " << i->first << endl;
	}
	cout << "Enter number of Round that you want to remove \n";
	cin >> roundId;
	leagues.leagues[LeagueId].rounds.erase(roundId);
	cout << " Round " << roundId << " is Removed successfully :)" << endl;
}