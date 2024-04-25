#include "Admin.h"
#include "League.h"
#include "Team.h"
#include <list>
#include <vector>
#include "Player.h"
#include<map>

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
		Player::AddPlayer();
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
	League l; int id;
	Team team;
	Team::player;
	Player p;
	string PlayerName;
	p.PlayerName = PlayerName;
	
	cout << "Enter The League Id : ";
	cin >> id;
	if (id == l.LeagueId) {
		cout << "Enter The Team Name : ";
		cin >> team.TeamName;
		cout << "Enter The Team Id : ";
		cin >> team.TeamId;
		cout << "Enter The Players Name : ";
		/*for (int i = 0;i < team.player.size();i++) {
			team.player.push_back(PlayerName);

		}*/
		cout << "Team " << team.TeamName << " is added successfully :)" << endl;
	}
	else {
		cout << "Wrong Id" << endl;
		AddTeam();
	}
}

bool Admin::FindTeamInLeague(League League, int TeamID) {

	for (Team& t : League.teams)
	{
		if (TeamID == t.TeamId) {
			return true;
		}
	}

	return false;

}

vector<Team> Admin::RemoveV(League League,int TeamID) {

	vector<Team> Teams;
	for (Team& t : League.teams)
	{
		if (TeamID == t.TeamId)
			continue;
		Teams.push_back(t);
	}
	return Teams;

}

void Admin::RemoveTeam() {

	int lID,tID;
	//Print Leagues (Name & ID)
	cout << "Enter The League Id : ";
	cin >> lID;

	/*for (League &l : Leagues)
	{
		if(lID == l.LeagueId)
		{
			//Print Teams
			for(Team &t : l.teams)
			{
				cout << t.TeamId << " " << t.TeamName << endl;
			}
			cout << "Enter The Team Id : ";
			cin >> tID;

			if(FindTeamInLeague(l,tId))
				l.teams = RemoveV(l,tId);
			else
			{
			cout << "Wrong ID\n";
			RemoveTeam();
			}
		}
		else
		{
			cout << "Wrong ID\n";
			RemoveTeam();
		}
	}*/

}
void Player::AddPlayer() {

	Team t;
	int leagueId;
	Player p;
	int ans;
	League l;

	cout << "Please Enter League id  \n";
	cin >> leagueId;
	int i = 0;
	while (i != l.players.size()) {
		if (leagueId == l.LeagueId)
		{
			int teamId;
			int j = 0;
			cout << "Please Enter Team ID ";
			cin >> teamId;
			while (j != l.teams.size()) {
			if (teamId == t.TeamId)
			{
				cout << "Enter Player Name";
				cin >> t.player[p.PlayerId].PlayerName;
				cout << "Enter Player Position";
				cin >> t.player[p.PlayerId].PlayerPosition;
				cout << "Enter Player Price";
				cin >> t.player[p.PlayerId].PlayerPrice;
				cout << "You Add Player " << p.PlayerName << " Successfully\n";
			}
			else 
			{
				cout << "This Team Id Not Available \n 1- try again 2-Exit";
				cin >> ans;
				switch (ans)
				{
				case 1:
					AddPlayer();
					break;
				case 2:
					Admin::Home();
					break;
				default:
					cout << "Invalid Answer \n ";

				}

			}
				j++; 
			}
		}

		i++;

	}


	/*l.players[i];
	i++;*/





	/*cout << "Teams ID Is \n";
	for(int i=0 ;i<t.player.size();i++){
		{
		 // lw 3wzen n show el id
		}*/


		/*cout << "Enter Team ID";
		cin >> id;
		if (id == t.TeamId) {
			cout << "Enter Player Name";
			cin >> p.PlayerName;
			cout << "Enter Player Position";
			cin >> p.PlayerPosition;
			cout << "Enter Player Price";
			cin >> p.PlayerPrice;
			cout << "You Add Player " << p.PlayerName << " Successfully\n";
		}
		else {
			cout << "This Team Id Not Available \n 1- try again 2-Exit";
			cin >> ans;
			switch (ans)
			{
			case 1:
				AddPlayer();
				break;
			case 2:
				Admin::Home();
				break;
			default:
				cout<<"Invalid Answer \n ";



		}
		*/

}
	
	


