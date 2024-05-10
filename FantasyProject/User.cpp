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
	legId = Validation::ReadNumberInRange(1, 3);
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
		answer = Validation::ReadNumberInRange(1, 3);
		/*cin.ignore();*/
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
		answer = Validation::ReadNumberInRange(1, 6);
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
	vector<int> numplayersid;
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
			choose = Validation::ReadNumberInRange(1, 2);
			cin.ignore();
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
		answer = Validation::ReadNumberInRange(1, 4);
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
					if (j->PlayerId == i.second.PlayerId) {
						isFind = false;
						break;
					}
				}

				if (isFind) {
					cout << i.first << '-' << i.second.PlayerName << '-' << i.second.PlayerPrice << '-' << i.second.PlayerPosition << "       " << Leagues::leagues[leagueId].teams[i.second.TeamId].TeamName << endl;
					numplayersid.push_back(i.first);
				}
			}
			isFind = true;
		}
		bool validid = 0;
		do {
			cout << "Enter the ID Of Player:";
			playerid = Validation::ReadNumber();
			for (auto i : numplayersid) {
				if (playerid == i) {
					validid = 1;
					break;
				}
			}
			if (validid == 0) {
				cout << "the id is invalid ...\n1- please try again \n2- go back \n";
				int ans = Validation::ReadNumberInRange(1, 2);
				switch (ans)
				{
				case 1:
					continue;
				case 2:
					setSquad();
				default:
					break;
				}
			}

		} while (validid == 0);

		if (Budget < Leagues::leagues[leagueId].Players[playerid].PlayerPrice) {
			RemovePlayer();

		}
		else {
			Budget -= Leagues::leagues[leagueId].Players[playerid].PlayerPrice;
			squad[leagueId].squads[position].push_back(&Leagues::leagues[leagueId].Players[playerid]);
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
			cout << j->PlayerId << "-" << j->PlayerName << "-" << j->PlayerPrice << "-" << j->PlayerPosition << endl;

		}
	}
	cout << "Enter the ID Of Player To remove:";
	cin >> playerid;
	for (auto i : squad[leagueId].squads) {
		count = 0;
		for (auto j : i.second) {
			if (j->PlayerId == playerid) {
				position = i.first;
				index = count;
			}
			count++;
		}
	}
	Budget += squad[leagueId].squads[position][index]->PlayerPrice;
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
	stack<Player*>copydeka;
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
					if (squad[roundid].deka.top()->PlayerId == j->PlayerId) {

						dekaexist = 1;
						break;
					}
					squad[roundid].deka.pop();

				}
				if (!dekaexist) {
					cout << i.first << "  " << j->PlayerName << " has Point : " << j->PointsInRounds[roundid] << endl;

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
void User::PickSquad() {
	bool isplayed = false, isfound = false, whoteam, teamisplayed = false, found = false;
	Round round;
	int matchid, answer, playerid;
	vector <int>playersid;
	stack <Player*>copyDeka;
	for (auto i : Leagues::leagues[leagueId].rounds) {
		for (auto j : i.second.matches)
		{
			if (j.second.isPlayed) {
				isplayed = true;
				break;
			}
		}
		if (!isplayed) {
			round = i.second;
			break;
		}
	}
	for (auto i : round.matches) {
		cout << i.first << " - " << i.second.team1.TeamName << "   VS    " << i.second.team2.TeamName << endl;
	}
	for (auto i : squad[leagueId].squads) {
		for (auto j : i.second) {
			while (!(squad[leagueId].deka.empty())) {
				copyDeka.push(squad[leagueId].deka.top());
				if (j->PlayerId == copyDeka.top()->PlayerId) {
					isfound = true;
					break;
				}
				squad[leagueId].deka.pop();
			}
			if (!isfound) {
				if (j->PlayerId == squad[leagueId].captain.PlayerId) {
					cout << j->PlayerId << " - " << j->PlayerName << "       " << j->PlayerPosition << "       " << "captin";
				}
				else if (j->PlayerId == squad[leagueId].ViceCaptain.PlayerId) {
					cout << j->PlayerId << " - " << j->PlayerName << "       " << j->PlayerPosition << "       " << "vice captin";
				}
				else {
					cout << j->PlayerId << " - " << j->PlayerName << "       " << j->PlayerPosition << "       ";
				}

			}
			for (auto k : round.matches) {
				auto m = k.second.team1.Players.find(j->PlayerId);
				if (m != k.second.team1.Players.end()) {
					matchid = k.second.MatchId;
					whoteam = true;
					teamisplayed = true;
					break;
				}
				auto m = k.second.team2.Players.find(j->PlayerId);
				if (m != k.second.team2.Players.end()) {
					matchid = k.second.MatchId;
					whoteam = false;
					teamisplayed = true;
					break;
				}
			}
			if (!teamisplayed) {
				cout << " - " << endl;
			}
			else {
				if (whoteam) {
					cout << round.matches[matchid].team2.TeamName << endl;
				}
				else if (!whoteam) {
					cout << round.matches[matchid].team1.TeamName << endl;
				}
			}
			while (!(copyDeka.empty()))
			{
				squad[leagueId].deka.push(copyDeka.top());
				copyDeka.pop();
			}
		}
		cout << " this is the main squad\n\n\n";
		while (!(squad[leagueId].deka.empty())) {
			copyDeka.push(squad[leagueId].deka.top());
			cout << copyDeka.top()->PlayerId << " - " << copyDeka.top()->PlayerName << "       " << copyDeka.top()->PlayerPosition << "       ";
			for (auto k : round.matches) {
				auto m = k.second.team1.Players.find(copyDeka.top()->PlayerId);
				if (m != k.second.team1.Players.end()) {
					matchid = k.second.MatchId;
					whoteam = true;
					teamisplayed = true;
					break;
				}
				auto m = k.second.team2.Players.find(copyDeka.top()->PlayerId);
				if (m != k.second.team2.Players.end()) {
					matchid = k.second.MatchId;
					whoteam = false;
					teamisplayed = true;
					break;
				}
			}
			if (!teamisplayed) {
				cout << " - " << endl;
			}
			else {
				if (whoteam) {
					cout << round.matches[matchid].team2.TeamName << endl;
				}
				else if (!whoteam) {
					cout << round.matches[matchid].team1.TeamName << endl;
				}
			}

		}

		while (!(copyDeka.empty()))
		{
			squad[leagueId].deka.push(copyDeka.top());
			copyDeka.pop();
		}
		cout << " this is the Bench\n\n\n";
	}
	cout << "1-set captin and vice captin\n2-switch between main squad and Bench\n 3-if you want active triple captin\n4-back to Home\n";
	answer = Validation::ReadNumberInRange(1, 4);
	switch (answer)
	{
	case 1:
		playersid.clear();
		for (auto i : squad[leagueId].squads) {
			for (auto j : i.second) {
				while (!(squad[leagueId].deka.empty())) {
					copyDeka.push(squad[leagueId].deka.top());
					if (j->PlayerId == copyDeka.top()->PlayerId) {
						isfound = true;
						break;
					}
					squad[leagueId].deka.pop();
				}
				if (!isfound) {
					if (j->PlayerId != squad[leagueId].captain.PlayerId) {
						if (j->PlayerId == squad[leagueId].ViceCaptain.PlayerId) {
							cout << j->PlayerId << " - " << j->PlayerName << "       " << j->PlayerPosition << "       " << "Vice Captin";
						}
						else {
							cout << j->PlayerId << " - " << j->PlayerName << "       " << j->PlayerPosition << "       ";
							playersid.push_back(j->PlayerId);

						}

					}

				}
				for (auto k : round.matches) {
					auto m = k.second.team1.Players.find(j->PlayerId);
					if (m != k.second.team1.Players.end()) {
						matchid = k.second.MatchId;
						whoteam = true;
						teamisplayed = true;
						break;
					}
					auto m = k.second.team2.Players.find(j->PlayerId);
					if (m != k.second.team2.Players.end()) {
						matchid = k.second.MatchId;
						whoteam = false;
						teamisplayed = true;
						break;
					}
				}
				if (!teamisplayed) {
					cout << " - " << endl;
				}
				else {
					if (whoteam) {
						cout << round.matches[matchid].team2.TeamName << endl;
					}
					else if (!whoteam) {
						cout << round.matches[matchid].team1.TeamName << endl;
					}
				}
				while (!(copyDeka.empty()))
				{
					squad[leagueId].deka.push(copyDeka.top());
					copyDeka.pop();
				}
			}
		}
		do {
			cout << "First Enter the player Id for The Captin:";
			playerid = Validation::ReadNumber();
			for (auto n : playersid) {
				if (playerid == n) {
					found = true;
					break;
				}
			}
			if (!found) {
				cout << "Enter the playerID valid";
			}
		} while (!found);
		if (playerid == squad[leagueId].ViceCaptain.PlayerId) {
			Player player;
			player = squad[leagueId].captain;
			squad[leagueId].captain = Leagues::leagues[leagueId].Players[playerid];
			squad[leagueId].ViceCaptain = player;
		}
		else {
			squad[leagueId].captain = Leagues::leagues[leagueId].Players[playerid];
		}
		cout << " you select captin successfully \n";
		cout << "1-if youe want set vice \n 2-go back to Home:";
		answer = Validation::ReadNumberInRange(1, 2);
		switch (answer)
		{
		case 1:
			playersid.clear();
			for (auto i : squad[leagueId].squads) {
				for (auto j : i.second) {
					while (!(squad[leagueId].deka.empty())) {
						copyDeka.push(squad[leagueId].deka.top());
						if (j->PlayerId == copyDeka.top()->PlayerId) {
							isfound = true;
							break;
						}
						squad[leagueId].deka.pop();
					}
					if (!isfound) {
						if (j->PlayerId != squad[leagueId].ViceCaptain.PlayerId) {
							if (j->PlayerId == squad[leagueId].captain.PlayerId) {
								cout << j->PlayerId << " - " << j->PlayerName << "       " << j->PlayerPosition << "       " << "Captin";
							}
							else {
								cout << j->PlayerId << " - " << j->PlayerName << "       " << j->PlayerPosition << "       ";
								playersid.push_back(j->PlayerId);
							}

						}

					}
					for (auto k : round.matches) {
						auto m = k.second.team1.Players.find(j->PlayerId);
						if (m != k.second.team1.Players.end()) {
							matchid = k.second.MatchId;
							whoteam = true;
							teamisplayed = true;
							break;
						}
						auto m = k.second.team2.Players.find(j->PlayerId);
						if (m != k.second.team2.Players.end()) {
							matchid = k.second.MatchId;
							whoteam = false;
							teamisplayed = true;
							break;
						}
					}
					if (!teamisplayed) {
						cout << " - " << endl;
					}
					else {
						if (whoteam) {
							cout << round.matches[matchid].team2.TeamName << endl;
						}
						else if (!whoteam) {
							cout << round.matches[matchid].team1.TeamName << endl;
						}
					}
					while (!(copyDeka.empty()))
					{
						squad[leagueId].deka.push(copyDeka.top());
						copyDeka.pop();
					}
				}
			}
			do {
				cout << "First Enter the player Id for The vice Captin:";
				playerid = Validation::ReadNumber();
				for (auto n : playersid) {
					if (playerid == n) {
						found = true;
						break;
					}
				}
				if (!found) {
					cout << "Enter the playerID valid";
				}
			} while (!found);
			if (playerid == squad[leagueId].captain.PlayerId) {
				Player player;
				player = squad[leagueId].ViceCaptain;
				squad[leagueId].ViceCaptain = Leagues::leagues[leagueId].Players[playerid];
				squad[leagueId].captain = player;
			}
			else {
				squad[leagueId].ViceCaptain = Leagues::leagues[leagueId].Players[playerid];
			}
			break;
		case 2:
			return;
		}
		break;
	case 2:

		break;
	case 3:

		break;
	case 4:
		return;
		break;

	}
}

