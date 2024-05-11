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

	Id_Count++;
}
User::User(string name, string password) {
	Id = Id_Count;

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

		while (true)

		{


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
				PickSquad(0);
				break;
			case 3:
				TransfersSquad();
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

}
void User::setSquad() {
	bool firstround = true;
	int roundid;
	for (auto i : Leagues::leagues[leagueId].rounds) {
		for (auto j : i.second.matches) {
			if (j.second.isPlayed == true) {
				firstround = false;
				break;
			}
		}
		if (firstround) {
			roundid = i.second.roundId;
			break;
		}
	}
	squad[leagueId].Budget = 80000;
	bool isFind = true;
	int playerid;
	vector<int> numplayersid;
	while (true) {
		int count = 0;
		for (auto i : squad[leagueId].squads[roundid])
		{
			count += i.second.size();
		}
		if (count == 15)
		{
			int choose;

			cout << " 1 : if you want change player \n";
			cout << " 2 : if you want submit\n";

			
          // cin.ignore();
			choose = Validation::ReadNumberInRange(1, 2);
			
			if (choose == 1)
			{
				RemovePlayer(roundid);
			}
			else
			{
				break;
			}
		}
		cout << " you must choose" << countsOfPosition[0] << " Goolkeepr - " << countsOfPosition[1] << " defenders - " << countsOfPosition[2] << " Midfielders - " << countsOfPosition[3] << " forward \n";
		cout << "Your Bidget:" << squad[leagueId].Budget << endl;
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
				for (auto j : squad[leagueId].squads[roundid][position]) {
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

		if (squad[leagueId].Budget < Leagues::leagues[leagueId].Players[playerid].PlayerPrice) {
			RemovePlayer(roundid);

		}
		else {
			squad[leagueId].Budget -= Leagues::leagues[leagueId].Players[playerid].PlayerPrice;
			squad[leagueId].squads[roundid][position].push_back(&Leagues::leagues[leagueId].Players[playerid]);
			countsOfPosition[va]--;
		}
	}
	squad[leagueId].numOfSubestitution = 2;
	PickSquad(roundid);
}
void User::RemovePlayer(int rid) {
	int index = 0;
	int count = 0;
	string position;
	int playerid;
	cout << " your budget is " << squad[leagueId].Budget << endl;

	for (auto i : squad[leagueId].squads[rid]) {
		for (auto j : i.second) {
			cout << j->PlayerId << "-" << j->PlayerName << "-" << j->PlayerPrice << "-" << j->PlayerPosition << endl;

		}
	}
	cout << "Enter the ID Of Player To remove:";
	cin >> playerid;
	for (auto i : squad[leagueId].squads[rid]) {
		count = 0;
		for (auto j : i.second) {
			if (j->PlayerId == playerid) {
				position = i.first;
				index = count;
			}
			count++;
		}
	}
	squad[leagueId].Budget += squad[leagueId].squads[rid][position][index]->PlayerPrice;
	squad[leagueId].squads[rid][position].erase(squad[leagueId].squads[rid][position].begin() + index);
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
		for (auto i : squad[leagueId].squads[roundid]) {

			for (auto j : i.second) {

				while (!squad[roundid].deka[roundid].empty()) {
					copydeka.push(squad[roundid].deka[roundid].top());
					if (squad[roundid].deka[roundid].top()->PlayerId == j->PlayerId) {

						dekaexist = 1;
						break;
					}
					squad[roundid].deka[roundid].pop();

				}
				if (!dekaexist) {
					cout << i.first << "  " << j->PlayerName << " has Point : " << j->PointsInRounds[roundid] << endl;

				}
				while (!copydeka.empty()) {
					squad[roundid].deka[roundid].push(copydeka.top());
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
void User::PickSquad(int roundid = 0) {
	bool isplayed = false, isfound = false, whoteam, teamisplayed = false, found = false, switchcaptin = false, switchvaicecaptin = false, setcaptin = false;
	Round round;
	Player* tempplayer;
	int matchid, answer, playerid, position = 0, size;
	vector <int>playersid;
	stack <Player*>copyDeka;
	if (squad[leagueId].deka[roundid].empty()) {
		for (auto i : squad[leagueId].squads[roundid]) {
			for (auto j : i.second) {
				squad[leagueId].deka[roundid].push(j);
				break;
			}
		}
		for (auto i : squad[leagueId].squads[roundid]) {
			for (auto j : i.second) {
				while (!(squad[leagueId].deka[roundid].empty())) {
					copyDeka.push(squad[leagueId].deka[roundid].top());
					if (j->PlayerId == copyDeka.top()->PlayerId) {
						isfound = true;
						break;
					}
					squad[leagueId].deka[roundid].pop();
				}
				if (i.first != "Goolkeepr") {
					if (!found && !setcaptin) {
						squad[leagueId].captain = j;
						setcaptin = true;
					}
					else if (!found && setcaptin) {
						squad[leagueId].ViceCaptain = j;
						break;
					}
				}
				while (!(copyDeka.empty())) {
					squad[leagueId].deka[roundid].push(copyDeka.top());
					copyDeka.pop();
				}
			}
		}
	}
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
		cout << i.first << " - " << i.second.team1->TeamName << "   VS    " << i.second.team2->TeamName << endl;
	}
	isfound = false;
	for (auto i : squad[leagueId].squads[round.roundId]) {
		for (auto j : i.second) {
			while (!(squad[leagueId].deka[round.roundId].empty())) {
				copyDeka.push(squad[leagueId].deka[round.roundId].top());
				if (j->PlayerId == copyDeka.top()->PlayerId) {
					isfound = true;
					break;
				}
				squad[leagueId].deka[round.roundId].pop();
			}
			if (!isfound) {
				if (j->PlayerId == squad[leagueId].captain->PlayerId) {
					cout << j->PlayerId << " - " << j->PlayerName << "       " << j->PlayerPosition << "       " << "captain";
				}
				else if (j->PlayerId == squad[leagueId].ViceCaptain->PlayerId) {
					cout << j->PlayerId << " - " << j->PlayerName << "       " << j->PlayerPosition << "       " << "vice captain";
				}
				else {
					cout << j->PlayerId << " - " << j->PlayerName << "       " << j->PlayerPosition << "       ";
				}

			}
			for (auto k : round.matches) {
				auto m = k.second.team1->Players.find(j->PlayerId);
				if (m != k.second.team1->Players.end()) {
					matchid = k.second.MatchId;
					whoteam = true;
					teamisplayed = true;
					break;
				}
				m = k.second.team2->Players.find(j->PlayerId);
				if (m != k.second.team2->Players.end()) {
					matchid = k.second.MatchId;
					whoteam = false;
					teamisplayed = true;
					break;
				}
			}
			if (!teamisplayed) {
				cout << "-" << endl;
			}
			else {
				if (whoteam) {
					cout << round.matches[matchid].team2->TeamName << endl;
				}
				else if (!whoteam) {
					cout << round.matches[matchid].team1->TeamName << endl;
				}
			}
			while (!(copyDeka.empty()))
			{
				squad[leagueId].deka[roundid].push(copyDeka.top());
				copyDeka.pop();
			}
		}
		cout << " this is the main squad\n\n\n";
		while (!(squad[leagueId].deka[roundid].empty())) {
			copyDeka.push(squad[leagueId].deka[roundid].top());
			cout << copyDeka.top()->PlayerId << " - " << copyDeka.top()->PlayerName << "       " << copyDeka.top()->PlayerPosition << "       ";
			for (auto k : round.matches) {
				auto m = k.second.team1->Players.find(copyDeka.top()->PlayerId);
				if (m != k.second.team1->Players.end()) {
					matchid = k.second.MatchId;
					whoteam = true;
					teamisplayed = true;
					break;
				}
				m = k.second.team2->Players.find(copyDeka.top()->PlayerId);
				if (m != k.second.team2->Players.end()) {
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
					cout << round.matches[matchid].team2->TeamName << endl;
				}
				else if (!whoteam) {
					cout << round.matches[matchid].team1->TeamName << endl;
				}
			}
			squad[leagueId].deka[roundid].pop();

		}

		while (!(copyDeka.empty()))
		{
			squad[leagueId].deka[roundid].push(copyDeka.top());
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
		for (auto i : squad[leagueId].squads[roundid]) {
			for (auto j : i.second) {
				while (!(squad[leagueId].deka.empty())) {
					copyDeka.push(squad[leagueId].deka[roundid].top());
					if (j->PlayerId == copyDeka.top()->PlayerId) {
						isfound = true;
						break;
					}
					squad[leagueId].deka[roundid].pop();
				}
				if (!isfound) {
					if (j->PlayerId != squad[leagueId].captain->PlayerId) {
						if (j->PlayerId == squad[leagueId].ViceCaptain->PlayerId) {
							cout << j->PlayerId << " - " << j->PlayerName << "       " << j->PlayerPosition << "       " << "Vice Captin";
						}
						else {
							cout << j->PlayerId << " - " << j->PlayerName << "       " << j->PlayerPosition << "       ";
							playersid.push_back(j->PlayerId);

						}
					}
				}
				for (auto k : round.matches) {
					auto m = k.second.team1->Players.find(j->PlayerId);
					if (m != k.second.team1->Players.end()) {
						matchid = k.second.MatchId;
						whoteam = true;
						teamisplayed = true;
						break;
					}
					m = k.second.team2->Players.find(j->PlayerId);
					if (m != k.second.team2->Players.end()) {
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
						cout << round.matches[matchid].team2->TeamName << endl;
					}
					else if (!whoteam) {
						cout << round.matches[matchid].team1->TeamName << endl;
					}
				}
				while (!(copyDeka.empty()))
				{
					squad[leagueId].deka[roundid].push(copyDeka.top());
					copyDeka.pop();
				}
			}
		}
		do {
			found = false;
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
		if (playerid == squad[leagueId].ViceCaptain->PlayerId) {
			Player* player;
			player = squad[leagueId].captain;
			squad[leagueId].captain = &Leagues::leagues[leagueId].Players[playerid];
			squad[leagueId].ViceCaptain = player;
		}
		else {
			squad[leagueId].captain = &Leagues::leagues[leagueId].Players[playerid];
		}
		cout << " you select captin successfully \n";
		cout << "1-if youe want set vice \n 2-go back to Home:";
		answer = Validation::ReadNumberInRange(1, 2);
		switch (answer)
		{
		case 1:
			playersid.clear();
			for (auto i : squad[leagueId].squads[roundid]) {
				for (auto j : i.second) {
					while (!(squad[leagueId].deka[roundid].empty())) {
						copyDeka.push(squad[leagueId].deka[roundid].top());
						if (j->PlayerId == copyDeka.top()->PlayerId) {
							isfound = true;
							break;
						}
						squad[leagueId].deka[roundid].pop();
					}
					if (!isfound) {
						if (j->PlayerId != squad[leagueId].ViceCaptain->PlayerId) {
							if (j->PlayerId == squad[leagueId].captain->PlayerId) {
								cout << j->PlayerId << " - " << j->PlayerName << "       " << j->PlayerPosition << "       " << "Captin";
							}
							else {
								cout << j->PlayerId << " - " << j->PlayerName << "       " << j->PlayerPosition << "       ";
								playersid.push_back(j->PlayerId);
							}

						}

					}
					for (auto k : round.matches) {
						auto m = k.second.team1->Players.find(j->PlayerId);
						if (m != k.second.team1->Players.end()) {
							matchid = k.second.MatchId;
							whoteam = true;
							teamisplayed = true;
							break;
						}
						m = k.second.team2->Players.find(j->PlayerId);
						if (m != k.second.team2->Players.end()) {
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
							cout << round.matches[matchid].team2->TeamName << endl;
						}
						else if (!whoteam) {
							cout << round.matches[matchid].team1->TeamName << endl;
						}
					}
					while (!(copyDeka.empty()))
					{
						squad[leagueId].deka[roundid].push(copyDeka.top());
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
			if (playerid == squad[leagueId].captain->PlayerId) {
				Player* player;
				player = squad[leagueId].ViceCaptain;
				squad[leagueId].ViceCaptain = &Leagues::leagues[leagueId].Players[playerid];
				squad[leagueId].captain = player;
			}
			else {
				squad[leagueId].ViceCaptain = &Leagues::leagues[leagueId].Players[playerid];
			}
			break;
		case 2:
			return;
		}
		break;
	case 2:
		playersid.clear();
		for (auto i : squad[leagueId].squads[roundid]) {
			for (auto j : i.second) {
				while (!(squad[leagueId].deka.empty())) {
					copyDeka.push(squad[leagueId].deka[roundid].top());
					if (j->PlayerId == copyDeka.top()->PlayerId) {
						isfound = true;
						break;
					}
					squad[leagueId].deka[round.roundId].pop();
				}
				if (!isfound) {
					if (j->PlayerId != squad[leagueId].captain->PlayerId) {
						if (j->PlayerId == squad[leagueId].ViceCaptain->PlayerId) {
							cout << j->PlayerId << " - " << j->PlayerName << "       " << j->PlayerPosition << "       " << "Vice Captin";
						}
						else {
							cout << j->PlayerId << " - " << j->PlayerName << "       " << j->PlayerPosition << "       ";
							playersid.push_back(j->PlayerId);

						}
					}
				}
				for (auto k : round.matches) {
					auto m = k.second.team1->Players.find(j->PlayerId);
					if (m != k.second.team1->Players.end()) {
						matchid = k.second.MatchId;
						whoteam = true;
						teamisplayed = true;
						break;
					}
					m = k.second.team2->Players.find(j->PlayerId);
					if (m != k.second.team2->Players.end()) {
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
						cout << round.matches[matchid].team2->TeamName << endl;
					}
					else if (!whoteam) {
						cout << round.matches[matchid].team1->TeamName << endl;
					}
				}
				while (!(copyDeka.empty()))
				{
					squad[leagueId].deka[round.roundId].push(copyDeka.top());
					copyDeka.pop();
				}
			}
		}

		do {
			found = false;
			cout << "Enter the player Id for switch ";
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
		if (playerid == squad[leagueId].captain->PlayerId) {
			switchcaptin = true;
		}
		else if (playerid == squad[leagueId].ViceCaptain->PlayerId) {
			switchvaicecaptin = true;
		}
		tempplayer = &Leagues::leagues[leagueId].Players[playerid];
		playersid.clear();
		while (!(squad[leagueId].deka[round.roundId].empty())) {
			copyDeka.push(squad[leagueId].deka[round.roundId].top());
			squad[leagueId].deka[round.roundId].pop();
			if (tempplayer->PlayerPosition == "Goolkeepr") {

				if (copyDeka.top()->PlayerPosition == "Goolkeepr") {
					cout << copyDeka.top()->PlayerId << " - " << copyDeka.top()->PlayerName << "       " << copyDeka.top()->PlayerPosition << "       ";
					playersid.push_back(copyDeka.top()->PlayerId);
					for (auto k : round.matches) {
						auto m = k.second.team1->Players.find(copyDeka.top()->PlayerId);
						if (m != k.second.team1->Players.end()) {
							matchid = k.second.MatchId;
							whoteam = true;
							teamisplayed = true;
							break;
						}
						m = k.second.team2->Players.find(copyDeka.top()->PlayerId);
						if (m != k.second.team2->Players.end()) {
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
							cout << round.matches[matchid].team2->TeamName << endl;
						}
						else if (!whoteam) {
							cout << round.matches[matchid].team1->TeamName << endl;
						}
					}
				}
			}
			else {
				cout << copyDeka.top()->PlayerId << " - " << copyDeka.top()->PlayerName << "       " << copyDeka.top()->PlayerPosition << "       ";
				playersid.push_back(copyDeka.top()->PlayerId);
				for (auto k : round.matches) {
					auto m = k.second.team1->Players.find(copyDeka.top()->PlayerId);
					if (m != k.second.team1->Players.end()) {
						matchid = k.second.MatchId;
						whoteam = true;
						teamisplayed = true;
						break;
					}
					m = k.second.team2->Players.find(copyDeka.top()->PlayerId);
					if (m != k.second.team2->Players.end()) {
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
						cout << round.matches[matchid].team2->TeamName << endl;
					}
					else if (!whoteam) {
						cout << round.matches[matchid].team1->TeamName << endl;
					}
				}
			}
		}
		do {
			found = false;
			cout << "Enter the player Id for switch ";
			playerid = Validation::ReadNumber();
			for (auto n : playersid) {
				if (playerid == n) {

					found = true;
					break;
				}
				position++;
			}
			if (!found) {
				cout << "Enter the playerID valid";
			}
		} while (!found);
		size = copyDeka.size();
		while (!(copyDeka.empty()))
		{
			if (position == size - copyDeka.size()) {
				squad[leagueId].deka[round.roundId].push(tempplayer);
				if (switchcaptin) {
					squad[leagueId].captain = &Leagues::leagues[leagueId].Players[playerid];
				}
				else if (switchvaicecaptin) {
					squad[leagueId].captain = &Leagues::leagues[leagueId].Players[playerid];
				}
			}
			else
			{
				squad[leagueId].deka[round.roundId].push(copyDeka.top());
				copyDeka.pop();
			}
		}
		cout << "you Switch Done \n";
		cout << "1-go back to pick squad again\n2-go bach to Home\n";
		answer = Validation::ReadNumberInRange(1, 2);
		switch (answer)
		{
		case 1:
			PickSquad();
			return;
		case 2:
			return;
		}
		break;
	case 3:
		if (squad[leagueId].tribleCaptain == 3) {
			cout << "The tripleCaptin is alredy actived from befor\n";
		}
		else if (squad[leagueId].tribleCaptain == 2) {
			cout << "The tripleCaptin is alredy actived Now\n";
		}
		else {
			cout << "Are You Sure To Active the triple captin?\n1-Yes\n2-No\n";
			answer = Validation::ReadNumberInRange(1, 2);
			switch (answer)
			{
			case 1:
				squad[leagueId].tribleCaptain == 2;
			case 2:
				PickSquad();
				return;
			}
		}
		break;
	case 4:
		return;
		break;
	}
}
void User::TransfersSquad() {
	vector<int>Idplayers;
	stack<Player*>copyDeka;
	Player* tempp, * newplayer;
	bool indeka = false;
	bool found = false;
	bool isfound = false;
	bool insquad = false;
	bool captintransfer = false;
	bool vicecaptintransfer = false;
	bool firstround = true;
	int playerid, ans, roundid;
	for (auto i : Leagues::leagues[leagueId].rounds) {
		for (auto j : i.second.matches) {
			if (j.second.isPlayed) {
				firstround = false;
				break;
			}
		}
		if (firstround) {
			roundid = i.second.roundId;
			break;
		}
	}
	for (auto i : squad[leagueId].squads[roundid]) {
		for (auto j : i.second) {
			cout << j->PlayerId << "   " << j->PlayerName << "    " << j->PlayerPrice << "    " << endl;
			Idplayers.push_back(j->PlayerId);
		}
	}
	cout << "Your Budget - " << squad[leagueId].Budget << endl;
	cout << "Number Of numOfSubestitution" << squad[leagueId].numOfSubestitution << endl;
	cout << "if you want to active waild card enter 1 else 2:";
	ans = Validation::ReadNumberInRange(1, 2);
	if (ans == 1) {
		if (squad[leagueId].wildCard = 1)
			squad[leagueId].wildCard = 2;
		else if (squad[leagueId].wildCard = 2) {
			cout << "is Alredy active in this round";
			TransfersSquad();
			return;
		}
		else if (squad[leagueId].wildCard = 3) {
			cout << "is played from befor";
			TransfersSquad();
			return;
		}
	}
	do {
		found = false;
		cout << "Enter Id the player " << endl;
		playerid = Validation::ReadNumber();
		for (auto n : Idplayers) {
			if (playerid == n) {
				found = true;
				break;
			}
		}
		if (!found) {
			cout << "Enter the playerID valid";
		}
	} while (!found);
	tempp = &Leagues::leagues[leagueId].Players[playerid];
	if (tempp->PlayerId == squad[leagueId].captain->PlayerId) {
		captintransfer = true;
	}
	else if (tempp->PlayerId == squad[leagueId].ViceCaptain->PlayerId) {
		vicecaptintransfer = true;
	}
	else {
		while (!(squad[leagueId].deka[roundid].empty())) {
			copyDeka.push(squad[leagueId].deka[roundid].top());
			if (tempp->PlayerId == copyDeka.top()->PlayerId) {
				insquad = true;
				break;
			}
			squad[leagueId].deka[roundid].pop();
		}
	}
	while (!(copyDeka.empty()))
	{
		squad[leagueId].deka[roundid].push(copyDeka.top());
		copyDeka.pop();
	}
	squad[leagueId].Budget += tempp->PlayerPrice;
	Idplayers.clear();
	while (true)
	{
		for (auto i : Leagues::leagues[leagueId].Players) {
			for (auto j : squad[leagueId].squads[roundid]) {
				for (auto k : j.second) {
					if (i.second.PlayerId == k->PlayerId) {
						insquad = true;
						break;
					}
				}
			}
			if (tempp->PlayerPosition == i.second.PlayerPosition) {

				cout << i.second.PlayerId << " - " << i.second.PlayerName << "      " << i.second.PlayerPosition << "      " << i.second.PlayerPrice << "        " << Leagues::leagues[leagueId].teams[i.second.TeamId].TeamName << endl;
				Idplayers.push_back(i.second.PlayerId);
			}
		}
		do {
			found = false;
			cout << "Enter Id of Player:";
			playerid = Validation::ReadNumber();
			for (auto n : Idplayers) {
				if (playerid == n) {
					found = true;
					break;
				}
			}
			if (!found) {
				cout << "Enter the playerID valid";
			}
		} while (!found);
		newplayer = &Leagues::leagues[leagueId].Players[playerid];
		if (Leagues::leagues[leagueId].Players[playerid].PlayerPrice > squad[leagueId].Budget) {
			cout << "The player price is greater than the Budget Try with player price" << endl;
		}
		else {
			if (squad[leagueId].wildCard = 2) {
				cout << "The wiald Card is played    " << "  and Budget is " << squad[leagueId].Budget - newplayer->PlayerPrice << endl;
			}
			else {
				if (squad[leagueId].numOfSubestitution > 0) {
					cout << "if you confirm this switch :number of transetion-" << squad[leagueId].numOfSubestitution - 1 << "and Budget is " << squad[leagueId].Budget - newplayer->PlayerPrice << endl;

				}
				else {
					cout << "if you confirm this switch the total points will -4 beacuse number of numOfSubestitution= 0" << "and Budget is " << squad[leagueId].Budget - newplayer->PlayerPrice << endl;
				}
			}

			cout << "1-confirm swhich\n2-swich anthor player\n3-go to home";
			ans = Validation::ReadNumberInRange(1, 3);
			switch (ans)
			{
			case 2:
				TransfersSquad();
				squad[leagueId].Budget -= tempp->PlayerPrice;
				return;
			case 3:
				squad[leagueId].Budget -= tempp->PlayerPrice;
				return;
			}
			break;
		}
	}
	squad[leagueId].Budget -= newplayer->PlayerPrice;
	if (squad[leagueId].wildCard != 2) {
		if (squad[leagueId].numOfSubestitution > 0) {
			squad[leagueId].numOfSubestitution -= 1;
		}
		else {
			squad[leagueId].TotalPoints -= 4;
		}
	}
	for (auto i : squad[leagueId].squads[roundid]) {
		for (auto j : i.second) {
			if (tempp->PlayerPosition == i.first) {
				if (tempp->PlayerId == j->PlayerId) {

					if (captintransfer) {
						squad[leagueId].captain = newplayer;
					}
					else if (vicecaptintransfer) {
						squad[leagueId].ViceCaptain = newplayer;
					}
					j = newplayer;
					isfound = true;
					break;
				}
			}
		}
		if (isfound)
			break;
	}
	if (indeka) {
		while (!(squad[leagueId].deka[roundid].empty())) {

			if (tempp->PlayerId == squad[leagueId].deka[roundid].top()->PlayerId) {
				copyDeka.push(newplayer);
				break;
			}
			else {
				copyDeka.push(squad[leagueId].deka[roundid].top());
				squad[leagueId].deka[roundid].pop();
			}

		}
		while (!(copyDeka.empty())) {
			squad[leagueId].deka[roundid].push(copyDeka.top());
			copyDeka.pop();
		}
	}
	cout << "switch is done \n 1-switch again\n 2-back to home";
	ans = Validation::ReadNumberInRange(1, 2);
	switch (ans)
	{
	case 1:
		TransfersSquad();
		return;
	case 2:
		return;
	}
}