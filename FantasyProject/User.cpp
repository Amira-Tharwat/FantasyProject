#include "User.h"
#include "Leagues.h"
int leagueId;
static int Id_Count = 1;
int UserId;
int countsOfPosition[4] = { 2,5,5,3 };
User::User(void)
{
	Id = Id_Count;
	Budget = 80000;
	Id_Count++;
}
User::User(string name, string password) {
	Id = Id_Count;
	Budget = 80000;
	Id_Count++;
	Name = name;
	Password = password;
}

void User::chooseLeague(int userId) {
	int legId;
	for (int i = 1; i <= 3; i++) {
		cout << i << "\t" << Leagues::leagues[i].LaegueName << endl;
	}
	cout << "Please Enter League Id\n";
	cin >> legId;
	leagueId = legId;
	UserId = userId;
	Home();
}
void User::Home() {
	if (squad[leagueId].squads.empty()) {
		cout << "1-set squad" << endl;
		cout << "2-Log Out" << endl;
		int answer;
		cout << "Enter Number Of Choice:";
		cin >> answer;
		switch (answer)
		{
		case 1:
			setSquad();
			break;
		case 2:
			/*LogOut();*/
			break;
		default:
			break;
		}
	}
	else {
		cout << "1-Show Points Of Squad in Round\n";
		cout << "2-Pick Squad\n";
		cout << "3-Transfers Squad\n";
		cout << "4-Show Ranking\n";
		cout << "5-Change League \n";
		cout << "6-Log Out\n";
		int answer;
		cout << "Enter Number Of Choice:";
		cin >> answer;
		switch (answer)
		{
		case 1:
			/*ShowPoints();*/
			break;
		case 2:
			/*PickSquad();*/
			break;
		case 3:
			/*TransfersSquad();*/
			break;
		case 4:
			/*ShowPoints();*/
			break;
		case 5:
			/*chooseLeague(Id);*/
			break;
		case 6:
			/*LogOut();*/
			break;
		default:
			break;
		}
	}
}
void User::setSquad() {
	int playerid;
	cout << "you must choose"<< countsOfPosition[0] <<" Goolkeepr - "<<countsOfPosition[1]<< "defenders - "<< countsOfPosition[2] <<"Midfielders - "<<countsOfPosition[4]<<" forward \n";
	cout << "Your Bidget:" << Budget;
	while (true) {
		cout << "1-Goolkeepr\n";
		cout << "2-defenders\n";
		cout << "3-Midfielders\n";
		cout << "4-forward\n";
		int answer;
		cout << "Enter the Choice:";
		cin >> answer;
		string position;
		switch (answer)
		{
		case 1:
			if (countsOfPosition[0] == 0) {
				cout << "you Choosen the max Number Of Goolkeeper\n";
				continue;
			}
			position = "Goolkeepr";
			countsOfPosition[0]--;
			
			break;
		case 2:
			if (countsOfPosition[1] == 0) {
				cout << "you Choosen the max Number Of defenders\n";
				continue;
			}
			position = "defenders";
			countsOfPosition[1]--;
			
			break;
		case 3:
			if (countsOfPosition[2] == 0) {
				cout << "you Choosen the max Number Of Midfielders\n";
				continue;
			}
			position = "Midfielders";
			countsOfPosition[2]--;
			
			break;
		case 4:
			if (countsOfPosition[3] == 0) {
				cout << "you Choosen the max Number Of forward\n";
				continue;
			}
			position = "forward";
			countsOfPosition[3]--;

			break;
		default:
			break;
		}
		for (auto i : Leagues::leagues[leagueId].Players) {
			if (i.second.PlayerPosition == position) {
				for (auto j : squad[leagueId].squads[position]) {
					if (j.PlayerId != i.second.PlayerId) {
						cout << i.first << '-' << i.second.PlayerName << '-' << i.second.PlayerPrice << '-' << i.second.PlayerPosition << endl;
					}
				}
			}
		}
		cout << "Enter the ID Of Player:";
		cin >> playerid;
		if (Budget < Leagues::leagues[leagueId].Players[playerid].PlayerPrice) {
			RemovePlayer();
		}
		else {
			Budget -= Leagues::leagues[leagueId].Players[playerid].PlayerPrice;
			squad[leagueId].squads[position].push_back(Leagues::leagues[leagueId].Players[playerid]);
		}
	}
}
void User::RemovePlayer() {
	int index=0;
	int count=0;
	string position;
	int playerid;
	for (auto i : squad[leagueId].squads) {
		for (auto j :i.second) {
			cout << j.PlayerId << "-" << j.PlayerName << "-" << j.PlayerPrice << "-" << j.PlayerPosition;

		}
	}
	cout << "Enter the ID Of Player To remove:";
	cin >> playerid;
	for (auto i : squad[leagueId].squads) {
		for (auto j : i.second) {
			if (j.PlayerId == playerid) {
				position = i.first;
				index = count;
			}
			count++;
		}
	}
	squad[leagueId].squads[position].erase(squad[leagueId].squads[position].begin() + index);
	if (position == "Goolkeepr")
		countsOfPosition[0]--;
	else if (position == "defenders")
		countsOfPosition[1]--;
	else if (position == "Midfielders")
		countsOfPosition[2]--;
	else
		countsOfPosition[3]--;
	setSquad();
}