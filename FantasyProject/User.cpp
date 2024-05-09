#include "Validation.h"
#include "Leagues.h"
#include <queue>
#include<utility>
vector<User> U;
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
void User::GetUsers(const  vector<User>& Users) {
	U.resize(Users.size());
	for (int i = 0; i < Users.size(); i++) {
		U[i] = Users[i];
	}
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
		cout << "2-Change League \n";
		cout << "3-Log Out" << endl;

		int answer;
		cout << "Enter Number Of Choice:";
		cin >> answer;
		cin.ignore();
		switch (answer)
		{
		case 1:
			setSquad();
			Home();
			break;
		case 2:
			chooseLeague(Id);
		case 3:
			return;
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
		cin.ignore();
		switch (answer)
		{
		case 1:
			ShowPoints();
			break;
		case 2:
			/*PickSquad();*/
			break;
		case 3:
			/*TransfersSquad();*/
			break;
		case 4:
			showRank();
			break;
		case 5:
			chooseLeague(Id);
			break;
		case 6:
			return;
		default:
			break;
		}
	}
}
void User::setSquad() {
	bool isFind = true;
	int playerid;
	while (true) {
		int count = 0;
		for (auto i : squad[leagueId].squads)
		{
			count += i.second.size();
		}
		if (count == 15)
		{
			int choose;

			cout << " 1 : if you want change player \n";
			cout << " 2 : if you want submit";
			cin >> choose;
			if (choose == 1)
			{
				RemovePlayer();
			}
			else
			{

				break;
			}

		}
		cout << " you must choose" << countsOfPosition[0] << " Goolkeepr - " << countsOfPosition[1] << " defenders - " << countsOfPosition[2] << " Midfielders - " << countsOfPosition[3] << " forward \n";
		cout << "Your Bidget:" << Budget << endl;
		cout << "1-Goolkeepr\n";
		cout << "2-defenders\n";
		cout << "3-Midfielders\n";
		cout << "4-forward\n";
		int answer;
		cout << "Enter the Choice:";
		cin >> answer;
		string position;
		int va;
		switch (answer)
		{
		case 1:
			if (countsOfPosition[0] == 0) {
				cout << "you Choosen the max Number Of Goolkeeper\n";
				continue;
			}
			position = "Goolkeepr";
			va = 0;

			break;
		case 2:
			if (countsOfPosition[1] == 0) {
				cout << "you Choosen the max Number Of defenders\n";
				continue;
			}
			position = "defenders";
			va = 1;

			break;
		case 3:
			if (countsOfPosition[2] == 0) {
				cout << "you Choosen the max Number Of Midfielders\n";
				continue;
			}
			position = "Midfielders";
			va = 2;

			break;

		case 4:

			if (countsOfPosition[3] == 0) {
				cout << "you Choosen the max Number Of forward\n";
				continue;
			}
			position = "forward";
			va = 3;

			break;
		default:
			break;
		}
		for (auto i : Leagues::leagues[leagueId].Players) {
			if (i.second.PlayerPosition == position) {
				for (auto j : squad[leagueId].squads[position]) {
					if (j.PlayerId == i.second.PlayerId) {
						isFind = false;
						break;
					}
				}
				if (isFind)
					cout << i.first << '-' << i.second.PlayerName << '-' << i.second.PlayerPrice << '-' << i.second.PlayerPosition << endl;
			}
			isFind = true;
		}
		cout << "Enter the ID Of Player:";
		cin >> playerid;
		if (Budget < Leagues::leagues[leagueId].Players[playerid].PlayerPrice) {
			RemovePlayer();

		}
		else {
			Budget -= Leagues::leagues[leagueId].Players[playerid].PlayerPrice;
			squad[leagueId].squads[position].push_back(Leagues::leagues[leagueId].Players[playerid]);
			countsOfPosition[va]--;
		}
	}

}
void User::RemovePlayer() {
	int index = 0;
	int count = 0;
	string position;
	int playerid;
	cout << " your budget is " << Budget << endl;

	for (auto i : squad[leagueId].squads) {
		for (auto j : i.second) {
			cout << j.PlayerId << "-" << j.PlayerName << "-" << j.PlayerPrice << "-" << j.PlayerPosition << endl;

		}
	}
	cout << "Enter the ID Of Player To remove:";
	cin >> playerid;
	for (auto i : squad[leagueId].squads) {
		count = 0;
		for (auto j : i.second) {
			if (j.PlayerId == playerid) {
				position = i.first;
				index = count;
			}
			count++;
		}
	}
	Budget += squad[leagueId].squads[position][index].PlayerPrice;
	squad[leagueId].squads[position].erase(squad[leagueId].squads[position].begin() + index);
	if (position == "Goolkeepr")
		countsOfPosition[0]++;
	else if (position == "defenders")
		countsOfPosition[1]++;
	else if (position == "Midfielders")
		countsOfPosition[2]++;
	else
		countsOfPosition[3]++;
	setSquad();
}
void User::ShowPoints() {
	int roundid;
	bool x = 0;
	bool dekaexist = 0;
	vector <int> exist;
	stack<Player>copydeka;
	for (auto i : Leagues::leagues[leagueId].rounds) {
		for (auto j : i.second.matches) {
			if (j.second.isPlayed == 1) {

				cout << i.first << "- Round " << i.first;
				exist.push_back(i.first);
				break;
			}
		}
	}

	do {
		x = 0;
		cout << "Enter Round Id\n";
		roundid = Validation::ReadNumber();
		for (auto i : exist)
		{
			if (i == roundid)
			{
				x = 1;
				break;
			}


		}
	} while (!x);
	if (x == 1) {
		cout << "Points of This Round is " << squad[leagueId].RoundPoints[roundid];

		cout << "Points of each Player is  ";
		for (auto i : squad[leagueId].squads) {

			for (auto j : i.second) {

				while (!squad[roundid].deka.empty()) {
					copydeka.push(squad[roundid].deka.top());
					if (squad[roundid].deka.top().PlayerId == j.PlayerId) {

						dekaexist = 1;
						break;
					}
					squad[roundid].deka.pop();

				}
				if (!dekaexist) {
					cout << i.first << "  " << j.PlayerName << " has Point : " << j.PointsInRounds[roundid];

				}
				while (!copydeka.empty()) {
					squad[roundid].deka.push(copydeka.top());
					copydeka.pop();
				}
			}
		}
	}



}
void User::showRank() {
	int count = 1;
	int ans;
	multimap<int, User, greater<int> >OrderUser;
	for (auto i : U) {
		OrderUser.insert(make_pair(i.squad[leagueId].TotalPoints, i));
	}
	for (auto i : OrderUser) {
		if (count <= 10)
			cout << count << '-' << i.second.Name << "  Total Points" << i.first << endl;
		if (i.second.Id == Id && count > 10) {
			cout << ".\n.\n.\n.\n";
			cout << count << '-' << i.second.Name << "    Total Points" << i.first << endl;
			break;
		}
		count++;
	}

	cout << "if You Want Go back to Home Enter 1:";
	cin.ignore();
	ans = Validation::ReadNumberInRange(1, 1);
	Home();
}


