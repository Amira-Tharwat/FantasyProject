#include "Admin.h"
#include <chrono>
#include <thread>
vector <User>us;
map<int, League> Leagues::leagues;
int LeagueId;
Admin::Admin() {}
Admin::Admin(int id, string name, string password)
{
	Name = name;
	Password = password;
	Id = id;
}
void Admin::SetLeagueId(const  vector<User>& Users)
{
	us.resize(Users.size());
	for (int i = 0; i < Users.size(); i++) {
		us[i] = Users[i];
	}
	int legId;
	for (int i = 1; i <= 3; i++) {
		cout << i << "\t" << Leagues::leagues[i].LaegueName << endl;
	}
	cout << "Please Enter League Id\n";
	legId = Validation::ReadNumberInRange(1, 3);

	LeagueId = legId;

	Home();

}
void Admin::Home()
{
	while (true)
	{
		cout << "Please Enter\n";
		cout << "1- Add Team\n";
		cout << "2- Remove Team\n";
		cout << "3- Add Player\n";
		cout << "4- Remove Player\n";
		cout << "5- Add Round\n";
		cout << "6- Add Match\n";
		cout << "7- Remove Match\n";
		cout << "8- Set Result\n";
		cout << "9-Logout\n";
		int answer = Validation::ReadNumberInRange(1, 10);
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
			AddMatch();
			break;
		case 7:
			RemoveMatch();
			break;
		case 8:
			setResult();
			break;
		case 9:
			return;
		}
	}
}
void Admin::AddTeam() {

	Team team;
	cout << "Enter The Team Name : ";
	bool b = true;
	do {
		b = 1;
		team.TeamName = Validation::nameVal();
		for (auto i : Leagues::leagues[LeagueId].teams)
		{
			if (i.second.TeamName == team.TeamName)
			{
				cout << "This name of team is already exist\n";
				b = false;
				break;
			}
		}
	} while (!b);
	cout << "Team " << team.TeamName << " is added successfully :)" << endl;
	team.LeagueId = LeagueId;
	team.TeamId = Leagues::leagues[LeagueId].teams.rbegin()->second.TeamId + 1;
	Leagues::leagues[LeagueId].teams[team.TeamId] = team;

	return;
}
void Admin::RemoveTeam() {
	bool b = true;
	if (!Leagues::leagues[LeagueId].teams.size())
	{
		int ans;
		cout << "Not Teams Found\n1-if you want to go back to home page\n2-if you want to add team\n";
		ans = Validation::ReadNumberInRange(1, 2);
		switch (ans)
		{
		case 1:
			return;
		case 2:
			AddTeam();
			break;
		}
	}
	else
	{
		int tID;
		for (auto i = Leagues::leagues[LeagueId].teams.begin(); i != Leagues::leagues[LeagueId].teams.end(); i++)
			cout << i->first << "\t" << i->second.TeamName << endl;
		cout << "Enter The Team Id : ";
		do {
			b = 1;
			tID = Validation::ReadNumber();
			auto j = Leagues::leagues[LeagueId].teams.find(tID);
			if (j == Leagues::leagues[LeagueId].teams.end())
			{
				b = 0;
				cout << "Not found team with this ID , try again\n";
			}
		} while (!b);
		Team teamRemove = Leagues::leagues[LeagueId].teams[tID];
		cout << "Team " << teamRemove.TeamName << " is Removed successfully :)" << endl;
		for (auto i : Leagues::leagues[LeagueId].teams[tID].Players) {
			Leagues::leagues[LeagueId].Players.erase(i.second->PlayerId);
		}
		Leagues::leagues[LeagueId].teams.erase(tID);
		return;
	}
}
void Admin::AddPlayer() {
	if (!Leagues::leagues[LeagueId].teams.size())
	{
		int ans;
		cout << "Not Rounds Found\n1-if you want to go back to home page\n2-if you want to add team\n";
		ans = Validation::ReadNumberInRange(1, 2);
		switch (ans)
		{
		case 1:
			return;
		case 2:
			AddTeam();
			break;
		}
	}
	bool b = 1;
	Player* p = new Player();
	int tID, ans = 0;
	cout << "Enter Player Name \n";
	p->PlayerName = Validation::nameVal();
	// ----------------------------------------
	cout << "Enter Player Position \n";
	cout << "1-GoalKeeper\n2-defenders\n3-Midfielders\n4-forward\n";
	ans = Validation::ReadNumberInRange(1, 4);
	if (ans == 1)
		p->PlayerPosition = "GoalKeeper";
	else if (ans == 2)
		p->PlayerPosition = "defenders";
	else if (ans == 3)
		p->PlayerPosition = "Midfielders";
	else
		p->PlayerPosition = "forward";
	//------------------------------------
	cout << "Enter Player Price" << endl;
	cout << "In Range 2500 to 12000 : ";
	p->PlayerPrice = Validation::ReadNumberInRange(2500, 12000);
	p->PlayerId = Leagues::leagues[LeagueId].Players.rbegin()->second.PlayerId + 1;
	while (true) {
		for (auto i = Leagues::leagues[LeagueId].teams.begin(); i != Leagues::leagues[LeagueId].teams.end(); i++)
			cout << i->first << "\t" << i->second.TeamName << endl;
		cout << "Enter The Team Id : ";

		do {
			b = 1;
			tID = Validation::ReadNumber();

			auto j = Leagues::leagues[LeagueId].teams.find(tID);
			if (j == Leagues::leagues[LeagueId].teams.end())
			{
				b = 0;
				cout << "Not found team with this ID , try again\n";
			}
		} while (!b);
		p->LeagueId = LeagueId;
		p->TeamId = tID;

		Leagues::leagues[LeagueId].Players[p->PlayerId] = *p;
		Leagues::leagues[LeagueId].teams[tID].Players[p->PlayerId] = p;
		break;
	}
	return;
}
void Admin::AddPlayer(int tID)
{
	bool b = 1;
	Player* p = new Player();
	int ans = 0;
	cout << "Enter Player Name: ";
	p->PlayerName = Validation::nameVal();

	// ----------------------------------------
	cout << "Enter Player Position: " << endl;
	cout << "1-GoalKeeper\n2-defenders\n3-Midfielders\n4-forward\n";
	ans = Validation::ReadNumberInRange(1, 4);

	if (ans == 1)
		p->PlayerPosition = "GoalKeeper";
	else if (ans == 2)
		p->PlayerPosition = "defenders";
	else if (ans == 3)
		p->PlayerPosition = "Midfielders";
	else
		p->PlayerPosition = "forward";
	//------------------------------------
	cout << "Enter Player Price: ";
	cout << "In Range 2500 to 12000" << endl;
	p->PlayerPrice = Validation::ReadNumberInRange(2500, 12000);
	p->PlayerId = Leagues::leagues[LeagueId].Players.rbegin()->second.PlayerId + 1;
	p->LeagueId = LeagueId;
	p->TeamId = tID;
	Leagues::leagues[LeagueId].Players[p->PlayerId] = *p;
	Leagues::leagues[LeagueId].teams[tID].Players[p->PlayerId] = p;
}
void Admin::RemovePlayer()
{
	int  tID, PID;
	bool b = 1;

	for (auto i = Leagues::leagues[LeagueId].teams.begin(); i != Leagues::leagues[LeagueId].teams.end(); i++)
		cout << i->first << "\t" << i->second.TeamName << endl;
	cout << "Enter The Team Id : ";
	do {
		b = 1;
		tID = Validation::ReadNumber();
		auto j = Leagues::leagues[LeagueId].teams.find(tID);
		if (j == Leagues::leagues[LeagueId].teams.end())
		{
			b = 0;
			cout << "Not found team with this ID , try again\n";
		}
	} while (!b);
	b = 1;
	if (!Leagues::leagues[LeagueId].teams[tID].Players.size())
	{
		int ans;
		cout << "No Players Found\n1-if you want to go back to home page\n2-if you want to add Player\n";
		ans = Validation::ReadNumberInRange(1, 2);
		switch (ans)
		{
		case 1:
			return;
			break;
		case 2:
			AddPlayer(tID);
			break;
		}
	}
	else
	{
		for (auto i = Leagues::leagues[LeagueId].teams[tID].Players.begin(); i != Leagues::leagues[LeagueId].teams[tID].Players.end(); i++)
			cout << i->first << "\t" << i->second->PlayerName << endl;
		cout << "Enter The Player Id : ";
		do {
			b = 1;
			PID = Validation::ReadNumber();
			auto j = Leagues::leagues[LeagueId].teams[tID].Players.find(PID);
			if (j == Leagues::leagues[LeagueId].teams[tID].Players.end())
			{
				cout << "Not found team with this ID , try again\n";
				b = 0;
			}
		} while (!b);
		Player* playerRemove = Leagues::leagues[LeagueId].teams[tID].Players[PID];
		Leagues::leagues[LeagueId].teams[tID].Players.erase(PID);
		Leagues::leagues[LeagueId].Players.erase(PID);

		cout << " Player " << playerRemove->PlayerName << " is Removed successfully :)" << endl;
		return;
	}
}
void Admin::AddRound()
{
	bool b = 1, found = false;
	char answer;
	int roundId;
	vector<int>idteams;
	if (Leagues::leagues[LeagueId].rounds.size() == (Leagues::leagues[LeagueId].teams.size() - 1) * 2)
	{
		cout << "All rounds is completed\n";
		int ans;
		cout << "1-if you want to go back to home page\n";
		ans = Validation::ReadNumberInRange(1, 1);
		return;
	}
	do {
		b = 1;
		cout << "Enter number of Round\n";
		roundId = Validation::ReadNumberInRange(1, (Leagues::leagues[LeagueId].teams.size() - 1) * 2);
		auto j = Leagues::leagues[LeagueId].rounds.find(roundId);
		if (j != Leagues::leagues[LeagueId].rounds.end())
		{
			cout << "This Round is exist\n";
			b = 0;
			int ans;
			cout << "1-if you want to go back to home page\n2-Try again\n";
			ans = Validation::ReadNumberInRange(1, 2);
			switch (ans)
			{
			case 1:
				return;
				break;
			case 2:
				break;
			}
		}
	} while (!b);
	vector<int> teamsid;
	int size = Leagues::leagues[LeagueId].teams.size() / 2;
	for (int i = 0; i < size; i++)
	{
		int t = 0;
		int tID;
		Match* match = new Match();
		while (t < 2)
		{
			for (auto ii = Leagues::leagues[LeagueId].teams.begin(); ii != Leagues::leagues[LeagueId].teams.end(); ii++) {
				for (auto i : idteams) {
					if (i == ii->first) {
						found = true;
					}
				}
				if (!found) {
					cout << ii->first << "\t" << ii->second.TeamName << endl;
					teamsid.push_back(ii->first);
				}
				found = false;
			}

			cout << "Enter The Team " << t + 1 << " Id For Match " << i + 1 << ":\n";
			do {
				b = 1;
				tID = Validation::ReadNumber();
				for (auto k : teamsid) {
					if (k == tID)
						b = false;
				}
				if (!b)
				{
					break;
				}
				cout << "Not found team with this ID , try again\n";
			} while (b);

			if (t == 1)
			{
				match->team1 = &Leagues::leagues[LeagueId].teams[tID];
			}
			else
				match->team2 = &Leagues::leagues[LeagueId].teams[tID];
			t++;
			idteams.push_back(tID);
		}
		if (Leagues::leagues[LeagueId].rounds[roundId].matches.empty()) {
			match->MatchId = 1;
		}
		else
			match->MatchId = Leagues::leagues[LeagueId].rounds[roundId].matches.rbegin()->second.MatchId + 1;
		cout << "the match Added Successfuly\n";
		Leagues::leagues[LeagueId].rounds[roundId].roundId = roundId;
		Leagues::leagues[LeagueId].rounds[roundId].leagueId = LeagueId;
		Leagues::leagues[LeagueId].rounds[roundId].matches[match->MatchId] = *match;
		cout << "1-if you want enter anthor match\n2-if you want to go back to home page\n";
		answer = Validation::ReadNumberInRange(1, 2);
		if (answer == 2) {
			return;
		}
	}
	cout << "You are added all Matches succesufully\n";
	return;
}
void Admin::AddMatch() {
	bool isfound = false, teamischosse = false;
	int teamid = 0;
	if (!Leagues::leagues[LeagueId].rounds.size())
	{
		int ans;
		cout << "Not Rounds Found\n1-if you want to go back to home page\n2-if you want to add Round\n";
		ans = Validation::ReadNumberInRange(1, 2);
		switch (ans)
		{
		case 1:
			return;
			break;
		case 2:
			AddRound();
			break;
		}
	}
	else
	{
		int answer;
		bool b = 1, flag = false;
		int roundId;
		while (true) {
			for (auto i : Leagues::leagues[LeagueId].rounds) {
				cout << i.first << '-' << "Round " << i.second.roundId << endl;
			}
			cout << "Enter the number of the round\n";

			do {
				b = 1;
				roundId = Validation::ReadNumber();
				auto s = Leagues::leagues[LeagueId].rounds.find(roundId);
				if (s == Leagues::leagues[LeagueId].rounds.end())
				{
					b = 0;
					cout << "Not found Round with this ID , try again\n";
				}

			} while (!b);
			if (Leagues::leagues[LeagueId].rounds[roundId].matches.size() == Leagues::leagues[LeagueId].teams.size() / 2) {
				cout << "this round is fully of matches\n";
				cout << "1-try again\n2-go to Home\n";
				answer = Validation::ReadNumberInRange(1, 2);
				switch (answer)
				{
				case 1:
					flag = true;
					break;
				case 2:
					return;
				}
			}
			if (!flag) {
				break;
			}
		}
		for (auto i : Leagues::leagues[LeagueId].rounds[roundId].matches) {
			cout << i.first << '-' << i.second.team1->TeamName << "     VS     " << i.second.team2->TeamName << endl;
		}
		cout << "this is Matches of this round\n";
		cout << "Now You Add Match on this Round\n";
		using namespace std::this_thread; // sleep_for, sleep_until
		using namespace std::chrono;
		sleep_until(system_clock::now() + seconds(2));
		for (int i = Leagues::leagues[LeagueId].rounds[roundId].matches.size(); i < 5; i++)
		{
			int t = 0;
			int tID;
			Match match;
			while (t < 2)
			{
				vector<int> teamsId;
				for (auto ii = Leagues::leagues[LeagueId].teams.begin(); ii != Leagues::leagues[LeagueId].teams.end(); ii++) {
					for (auto k : Leagues::leagues[LeagueId].rounds[roundId].matches) {
						auto j = k.second.team1->TeamId;
						auto jj = k.second.team2->TeamId;
						if (j == ii->second.TeamId || jj == ii->second.TeamId)
						{
							isfound = true;
						}
					}
					if (!isfound) {
						if (teamid == ii->first) {
							teamischosse = true;
						}
						if (!teamischosse) {
							cout << ii->first << "      " << ii->second.TeamName << endl;
							teamsId.push_back(ii->first);
						}
					}
					teamischosse = false;
					isfound = false;
				}
				bool exsit = 0;
				do {
					exsit = 1;
					cout << "Enter The Team " << t + 1 << " Id For Match " << i + 1 << ":\n";
					tID = Validation::ReadNumber();
					teamid = tID;
					for (auto l : teamsId) {
						if (l == tID) {
							exsit = false;
							break;
						}

					}
					if (!exsit) {
						break;
					}
					cout << "invalid ID-- Enter again\n";
				} while (exsit);

				if (t == 0)
				{
					match.team1 = &Leagues::leagues[LeagueId].teams[tID];
				}
				else if (t == 1)
					match.team2 = &Leagues::leagues[LeagueId].teams[tID];
				t++;
			}

			match.MatchId = Leagues::leagues[LeagueId].rounds[roundId].matches.rbegin()->second.MatchId + 1;
			cout << "the match Added Successfuly\n";
			if (Leagues::leagues[LeagueId].rounds[roundId].matches.size() == Leagues::leagues[LeagueId].teams.size() / 2) {
				cout << "the round is complete" << endl;
				return;
			}
			Leagues::leagues[LeagueId].rounds[roundId].matches[match.MatchId] = match;
			if (Leagues::leagues[LeagueId].rounds[roundId].matches.size() == Leagues::leagues[LeagueId].teams.size() / 2) {
				cout << "The Round is fully of matches\n";
				return;
			}
			cout << "1-if you want enter anthor match\n2-if you want to go back to home page\n";
			answer = Validation::ReadNumberInRange(1, 2);
			if (answer == 2) {
				return;
			}
		}
	}

}
void Admin::RemoveMatch() {
	int roundId, matchId, played = false, exist = false;
	vector<int>roundsId;
	vector <int>matchid;
	if (Leagues::leagues[LeagueId].rounds.size() == 0) {
		cout << " no Round exist\n";
		return;
	}
	for (auto i : Leagues::leagues[LeagueId].rounds) {
		for (auto j : i.second.matches) {
			if (j.second.isPlayed) {
				played = true;
				break;
			}
		}
		if (!played) {
			cout << i.first << '-' << "Round " << i.second.roundId << endl;
			roundsId.push_back(i.first);
		}
	}
	do {
		exist = false;
		cout << "Enter the number of the round\n";
		roundId = Validation::ReadNumber();
		for (auto j : roundsId) {
			if (j == roundId) {
				exist = true;
				break;
			}
		}
		if (exist) {
			break;
		}
		cout << "invalid Id Enter Again \n";
	} while (!exist);
	for (auto i : Leagues::leagues[LeagueId].rounds.find(roundId)->second.matches) {

		cout << i.first << '-' << i.second.team1->TeamName << "     VS     " << i.second.team2->TeamName << endl;
		matchid.push_back(i.first);
	}

	cout << "this is matches of this Round\n";
	do
	{
		exist = false;
		cout << "Enter the Id of the Match Which you Want set it's Result:";
		matchId = Validation::ReadNumber();
		for (auto i : matchid) {
			if (matchId == i) {
				exist = true;
				break;
			}
		}
		if (exist) {
			break;
		}
		cout << "invalid Id Enter again\n";
	} while (!exist);

	Leagues::leagues[LeagueId].rounds[roundId].matches.erase(matchId);
	if (Leagues::leagues[LeagueId].rounds[roundId].matches.size() == 0) {
		Leagues::leagues[LeagueId].rounds.erase(roundId);
	}
}
void Admin::setResult() {
	int roundId, matchId, playerId, countOfGoals, countOfassit, res1, res2, assist1, assist2, choicegoal, countOfYellow, countOfRed, numberOfYellow, counterwhile = 1, roundisplayed = false, roundexist = false, matchexist = false, playerexist = false;
	char yn;
	vector<int>roundsid;
	vector<int>matchsid;
	vector<int>playersid;
	for (auto i : Leagues::leagues[LeagueId].rounds) {
		cout << i.first << '-' << "Round " << i.second.roundId << endl;
		roundsid.push_back(i.first);
	}
	do
	{
		roundexist = false;
		cout << "Enter the number of the round\n";
		roundId = Validation::ReadNumber();
		for (auto k : roundsid) {
			if (roundId == k) {
				roundexist = true;
				break;
			}
		}
		if (roundexist) {
			break;
		}
		cout << "inavlid Id Enter Again\n";
	} while (!roundexist);
	for (auto i : Leagues::leagues[LeagueId].rounds[roundId].matches) {
		if (i.second.isPlayed) {
			roundisplayed = true;
			break;
		}
	}
	if (!roundisplayed) {
		for (auto i : us) {
			if (i.squad[LeagueId].wildCard == 2) {
				i.squad[LeagueId].wildCard = 3;
			}
			if (i.squad[LeagueId].numOfSubestitution < 2)
				i.squad[LeagueId].numOfSubestitution += 1;

		}
	}
	for (auto i : Leagues::leagues[LeagueId].rounds.find(roundId)->second.matches) {
		if (i.second.isPlayed == false) {
			cout << i.first << '-' << i.second.team1->TeamName << "     VS     " << i.second.team2->TeamName << endl;
			matchsid.push_back(i.first);
		}
	}
	cout << "these are matches of this Round\n";
	do {
		matchexist = false;
		cout << "Enter the Id of the Match Which you Want set it's Result:";
		matchId = Validation::ReadNumber();
		for (auto i : matchsid) {
			if (i == matchId) {
				matchexist = true;
				break;
			}
		}
		if (matchexist) {
			break;
		}
		cout << "invalid Id enter again\n";
	} while (!matchexist);
	cout << "/////////////////////////////////////////////////////////////////\n";
	cout << Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].MatchId << "-" << Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].team1->TeamName << "          VS          " << Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].team2->TeamName << endl;
	cout << "Now You Set the Squad of Tow Teams\n";
	setSquadfortowteams(roundId, matchId);
	cout << "Done----------- Now You Added Details of Match\n";
	cout << "Enter the Result of Team1:";
	Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].res1 = Validation::ReadNumber();
	cout << "Enter the Result of Team2:";
	Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].res2 = Validation::ReadNumber();
	res1 = Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].res1;
	res2 = Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].res2;
	while (res1) {
		cout << "if player from the anthor team score goal enter 1 else 2:";
		cin >> choicegoal;
		switch (choicegoal)
		{
		case 1:
			for (auto i : Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].XI[Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].team1->TeamId]) {
				auto j = Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].Details["Goals"].find(i.second->PlayerId);
				if (j == Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].Details["Goals"].end()) {
					cout << i.first << "-" << i.second->PlayerName << endl;
					playersid.push_back(i.first);
				}

			}
			for (auto i : Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].pdla[Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].team1->TeamId]) {
				auto j = Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].Details["Goals"].find(i.second->PlayerId);
				if (j == Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].Details["Goals"].end()) {
					cout << i.first << "-" << i.second->PlayerName << endl;
					playersid.push_back(i.first);
				}
			}
			cout << "That player who participated in the match\n";
			do {
				playerexist = false;
				cout << "enter the Id of player who score one or more:";
				playerId = Validation::ReadNumber();
				for (auto p : playersid) {
					if (p == playerId) {
						playerexist = true;
						break;
					}
				}
				if (playerexist) {
					break;
				}
				cout << "invalid id enter again\n";
			} while (!playerexist);
			if (Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].res1 > 1) {

				do {
					cout << "Enter the Number of Goals: ";
					countOfGoals = Validation::ReadNumber();
					if (countOfGoals <= res1) {
						break;
					}
					else {
						cout << "invalid number of goals\n";
					}
				} while (true);
			}
			else {
				countOfGoals = 1;
			}
			Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].Details["Goals"][playerId] = countOfGoals;
			res1 -= countOfGoals;
			break;
		case 2:
			playersid.clear();
			for (auto i : Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].XI[Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].team2->TeamId]) {
				auto j = Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].Details["OwnGoal"].find(i.second->PlayerId);
				if (j == Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].Details["OwnGoal"].end()) {
					cout << i.first << "-" << i.second->PlayerName << endl;
					playersid.push_back(i.first);
				}


			}
			for (auto i : Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].pdla[Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].team2->TeamId]) {
				auto j = Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].Details["OwnGoal"].find(i.second->PlayerId);
				if (j == Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].Details["OwnGoal"].end()) {
					cout << i.first << "-" << i.second->PlayerName << endl;
					playersid.push_back(i.first);
				}

			}
			cout << "That player who participated in the match\n";
			do {
				playerexist = false;
				cout << "enter the Id of player who score one or more:";
				playerId = Validation::ReadNumber();
				for (auto p : playersid) {
					if (p == playerId) {
						playerexist = true;
						break;
					}
				}
				if (playerexist) {
					break;
				}
				cout << "invalid Id enter again\n";

			} while (!playerexist);

			if (Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].res1 > 1) {
				
				do {
					cout << "Enter the Number of Goals: ";
					countOfGoals = Validation::ReadNumber();
					if (countOfGoals <= res1) {
						break;
					}
					else {
						cout << "invalid number of goals\n";
					}
				} while (true);
			}
			else {
				countOfGoals = 1;
			}
			Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].Details["OwnGoal"][playerId] = countOfGoals;
			res1 -= countOfGoals;
		default:
			break;
		}
	}
	while (res2) {
		cout << "if player from the anthor team score goal enter 1 else 2:";
		cin >> choicegoal;
		switch (choicegoal)
		{
		case 1:
			playersid.clear();
			for (auto i : Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].XI[Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].team2->TeamId]) {
				auto j = Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].Details["Goals"].find(i.second->PlayerId);
				if (j == Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].Details["Goals"].end()) {
					cout << i.first << "-" << i.second->PlayerName << endl;
					playersid.push_back(i.first);
				}


			}
			for (auto i : Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].pdla[Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].team2->TeamId]) {
				auto j = Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].Details["Goals"].find(i.second->PlayerId);
				if (j == Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].Details["Goals"].end()) {
					cout << i.first << "-" << i.second->PlayerName << endl;
					playersid.push_back(i.first);
				}
			}
			cout << "That player who participated in the match\n";
			do {
				playerexist = false;
				cout << "enter the Id of player who score one or more:";
				playerId = Validation::ReadNumber();
				for (auto p : playersid) {
					if (p == playerId) {
						playerexist = true;
						break;
					}
				}
				if (playerexist) {
					break;
				}
				cout << "invalid Id enter again\n";

			} while (!playerexist);
			if (Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].res2 > 1) {
				do {
					cout << "Enter the Number of Goals: ";
					countOfGoals = Validation::ReadNumber();
					if (countOfGoals <= res1) {
						break;
					}
					else {
						cout << "invalid number of goals\n";
					}
				} while (true);
			}
			else {
				countOfGoals = 1;
			}
			Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].Details["Goals"][playerId] = countOfGoals;
			res2 -= countOfGoals;
			break;
		case 2:
			playersid.clear();
			for (auto i : Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].XI[Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].team1->TeamId]) {
				auto j = Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].Details["OwnGoal"].find(i.second->PlayerId);
				if (j == Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].Details["OwnGoal"].end()){
					cout << i.first << "-" << i.second->PlayerName << endl;
				playersid.push_back(i.first);
				}
			}
			for (auto i : Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].pdla[Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].team1->TeamId]) {
				auto j = Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].Details["OwnGoal"].find(i.second->PlayerId);
				if (j == Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].Details["OwnGoal"].end()){
					cout << i.first << "-" << i.second->PlayerName << endl;
				playersid.push_back(i.first);
			}
			}
			cout << "That player who participated in the match\n";
			cout << "enter the Id of player who score one or more:";
			cin >> playerId;
			if (Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].res2 > 1) {
				cout << "Enter the Number of Goals: ";
				cin >> countOfGoals;
			}
			else {
				countOfGoals = 1;
			}
			Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].Details["Goals"][playerId] = countOfGoals;
			res2 -= countOfGoals;
		default:
			break;
		}
	}
	res1 = Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].res1;
	while (res1) {
		for (auto i : Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].XI[Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].team1->TeamId]) {
			auto j = Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].Details["Assist"].find(i.second->PlayerId);
			if (j == Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].Details["Assist"].end())
				cout << i.first << "-" << i.second->PlayerName << endl;
		}
		for (auto i : Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].pdla[Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].team1->TeamId]) {
			auto j = Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].Details["Assist"].find(i.second->PlayerId);
			if (j == Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].Details["Assist"].end())
				cout << i.first << "-" << i.second->PlayerName << endl;
		}
		cout << "That player who participated in the match\n";
		cout << "enter the Id of player who assist one or more Goal:";
		cin >> playerId;
		if (Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].res1 > 1) {
			cout << "Enter the Number of Goals: ";
			cin >> countOfassit;
		}
		else {
			countOfassit = 1;
		}
		Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].Details["Assist"][playerId] = countOfassit;
		res1 -= countOfassit;
		cout << "Do You Enter More (y/n)?";
		cin >> yn;
		if (yn == 'n' || yn == 'N')
			break;
	}
	res2 = Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].res2;
	while (res2) {
		for (auto i : Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].XI[Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].team2->TeamId]) {
			auto j = Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].Details["Assist"].find(i.second->PlayerId);
			if (j == Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].Details["Assist"].end())
				cout << i.first << "-" << i.second->PlayerName << endl;
		}
		for (auto i : Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].pdla[Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].team2->TeamId]) {
			auto j = Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].Details["Assist"].find(i.second->PlayerId);
			if (j == Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].Details["Assist"].end())
				cout << i.first << "-" << i.second->PlayerName << endl;
		}
		cout << "That player who participated in the match\n";
		cout << "enter the Id of player who assist one or more Goal:";
		cin >> playerId;
		if (Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].res2 > 1) {
			cout << "Enter the Number of Goals: ";
			cin >> countOfassit;
		}
		else {
			countOfassit = 1;
		}
		Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].Details["Assist"][playerId] = countOfassit;
		res1 -= countOfassit;
		cout << "Do You Enter More (y/n)?";
		cin >> yn;
		if (yn == 'n' || yn == 'N')
			break;
	}
	cout << "Enter the Number of Yellow card in Match:";
	cin >> countOfYellow;
	while (countOfYellow)
	{
		for (auto i : Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].XI[Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].team1->TeamId]) {
			auto j = Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].Details["Yellow"].find(i.second->PlayerId);
			if (j == Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].Details["Yellow"].end())
				cout << i.first << "-" << i.second->PlayerName << endl;
		}
		for (auto i : Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].pdla[Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].team1->TeamId]) {
			auto j = Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].Details["Yellow"].find(i.second->PlayerId);
			if (j == Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].Details["Yellow"].end())
				cout << i.first << "-" << i.second->PlayerName << endl;
		}
		for (auto i : Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].XI[Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].team2->TeamId]) {
			auto j = Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].Details["Yellow"].find(i.second->PlayerId);
			if (j == Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].Details["Yellow"].end())
				cout << i.first << "-" << i.second->PlayerName << endl;
		}
		for (auto i : Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].pdla[Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].team2->TeamId]) {
			auto j = Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].Details["Yellow"].find(i.second->PlayerId);
			if (j == Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].Details["Yellow"].end())
				cout << i.first << "-" << i.second->PlayerName << endl;
		}
		cout << "That player who participated in the match\n";
		cout << "enter the Id of player who get Yellow Card";
		cin >> playerId;
		if (countOfYellow > 1) {
			cout << "Enter the Number of Yellow card: ";
			cin >> numberOfYellow;
		}
		else
			numberOfYellow = 1;
		Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].Details["Yellow"][playerId] = numberOfYellow;
		countOfYellow -= numberOfYellow;
	}
	cout << "Enter the Number of Red card in Match:";
	cin >> countOfRed;

	while (countOfRed)
	{
		for (auto i : Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].XI[Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].team1->TeamId]) {
			auto j = Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].Details["Red"].find(i.second->PlayerId);
			if (j == Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].Details["Red"].end())
				cout << i.first << "-" << i.second->PlayerName << endl;
		}
		for (auto i : Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].pdla[Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].team1->TeamId]) {
			auto j = Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].Details["Red"].find(i.second->PlayerId);
			if (j == Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].Details["Red"].end())
				cout << i.first << "-" << i.second->PlayerName << endl;
		}
		for (auto i : Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].XI[Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].team2->TeamId]) {
			auto j = Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].Details["Red"].find(i.second->PlayerId);
			if (j == Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].Details["Red"].end())
				cout << i.first << "-" << i.second->PlayerName << endl;
		}
		for (auto i : Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].pdla[Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].team2->TeamId]) {
			auto j = Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].Details["Red"].find(i.second->PlayerId);
			if (j == Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].Details["Red"].end())
				cout << i.first << "-" << i.second->PlayerName << endl;
		}
		cout << "That player who participated in the match\n";
		cout << "enter the Id of player who get Red Card";
		cin >> playerId;
		Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].Details["Red"][playerId] = 1;
		countOfRed -= 1;
	}
	for (auto i : Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].Details) {
		for (auto j : i.second) {
			if (i.first == "Goals") {
				Leagues::leagues[LeagueId].Players[j.first].PointsInRounds[roundId] += 6 * j.second;
				Leagues::leagues[LeagueId].teams[Leagues::leagues[LeagueId].Players[j.first].TeamId].Players[j.first]->PointsInRounds[roundId] = 6 * j.second;
			}
			else if (i.first == "Assist") {
				Leagues::leagues[LeagueId].Players[j.first].PointsInRounds[roundId] += 4 * j.second;
				Leagues::leagues[LeagueId].teams[Leagues::leagues[LeagueId].Players[j.first].TeamId].Players[j.first]->PointsInRounds[roundId] = 4 * j.second;
			}
			else if (i.first == "Yellow") {
				Leagues::leagues[LeagueId].Players[j.first].PointsInRounds[roundId] += -1 * j.second;
				Leagues::leagues[LeagueId].teams[Leagues::leagues[LeagueId].Players[j.first].TeamId].Players[j.first]->PointsInRounds[roundId] = -1 * j.second;
			}

			else if (i.first == "Red") {
				Leagues::leagues[LeagueId].Players[j.first].PointsInRounds[roundId] += -3;
				Leagues::leagues[LeagueId].teams[Leagues::leagues[LeagueId].Players[j.first].TeamId].Players[j.first]->PointsInRounds[roundId] += -3;
			}
			else if (i.first == "OwnGoal") {
				Leagues::leagues[LeagueId].Players[j.first].PointsInRounds[roundId] += -4;
				Leagues::leagues[LeagueId].teams[Leagues::leagues[LeagueId].Players[j.first].TeamId].Players[j.first]->PointsInRounds[roundId] += -4;
			}
		}
	}
	for (auto i : Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].XI[Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].team1->TeamId]) {
		Leagues::leagues[LeagueId].Players[i.first].PointsInRounds[roundId] += 2;
	}
	for (auto i : Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].pdla[Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].team1->TeamId]) {
		Leagues::leagues[LeagueId].Players[i.first].PointsInRounds[roundId] += 1;
	}

	clacPoints(roundId, Leagues::leagues[LeagueId].rounds[roundId].matches[matchId]);
	return;
}
void Admin::setSquadfortowteams(int roundId, int matchId) {
	int playerId, counterwhile = 1;
	bool playerexist = false;
	vector<int>playersid;
	int yn;
	cout << "Now You Enter the The 11 Main Players of team 1\n";
	using namespace std::this_thread; // sleep_for, sleep_until
	using namespace std::chrono;
	sleep_until(system_clock::now() + seconds(2));
	Team* team = Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].team1;
	for (auto i : team->Players) {

		if (i.second->PlayerPosition == "Goolkeepr") {

			cout << i.second->PlayerId << '-' << i.second->PlayerName << '-' << i.second->PlayerPosition << endl;
			playersid.push_back(i.second->PlayerId);
		}
	}

	do {
		playerexist = false;
		cout << "Enter the Id of The main goalkeeper:";
		playerId = Validation::ReadNumber();
		playerexist = false;
		for (auto j : playersid) {
			if (j == playerexist) {
				playerexist = true;
				break;
			}
		}
		if (playerexist) {
			break;
		}
	} while (!playerexist);
	Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].XI[Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].team1->TeamId][playerId] = &Leagues::leagues[LeagueId].Players[playerId];
	cout << "Now we Enter The main players\n";
	sleep_until(system_clock::now() + seconds(2));
	playersid.clear();
	while (counterwhile <= 10) {
		for (auto j : Leagues::leagues[LeagueId].teams[Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].team1->TeamId].Players) {
			if (j.second->PlayerPosition != "Goolkeepr") {
				auto i = Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].XI[Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].team1->TeamId].find(j.second->PlayerId);
				if (i == Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].XI[Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].team1->TeamId].end()) {
					cout << j.second->PlayerId << '-' << j.second->PlayerName << '-' << j.second->PlayerPosition << endl;
					playersid.push_back(j.second->PlayerId);
				}
			}
		}
		do
		{
			playerexist = false;
			cout << "Enter the Id of The main Player" << counterwhile << ":";
			playerId = Validation::ReadNumber();

			for (auto f : playersid) {
				if (f == playerId) {
					playerexist = true;
				}
			}
			if (playerexist) {
				break;
			}
			cout << "invalid Id Enter Again\n";
		} while (!playerexist);
		counterwhile++;
		Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].XI[Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].team1->TeamId][playerId] = &Leagues::leagues[LeagueId].Players[playerId];
	}
	counterwhile = 1;
	cout << "You Added the 11 players successfully\n";
	cout << "1-if You need Enter The Substitute players\n2-no enter The Substitute players\n";
	yn = Validation::ReadNumberInRange(1, 2);
	if (yn == 1) {
		int numberOfsubtetution = 1;
		while (numberOfsubtetution <= 5)
		{
			playersid.clear();
			for (auto j : Leagues::leagues[LeagueId].teams[Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].team1->TeamId].Players) {
				auto i = Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].XI[Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].team1->TeamId].find(j.second->PlayerId);
				if (i == Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].XI[Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].team1->TeamId].end()) {
					cout << j.second->PlayerId << '-' << j.second->PlayerName << '-' << j.second->PlayerPosition << endl;
					playersid.push_back(j.second->PlayerId);
				}

			}
			do {
				playerexist = false;
				cout << "Enter the Substitute Player" << numberOfsubtetution << ":";
				playerId = Validation::ReadNumber();
				for (auto k : playersid) {
					if (k == playerId) {
						playerexist = true;
						break;
					}
				}
				if (!playerexist) {
					break;
				}
				cout << "invalid Id Enter again\n";
			} while (!playerexist);


			Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].pdla[Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].team1->TeamId][playerId] = &Leagues::leagues[LeagueId].Players[playerId];
			numberOfsubtetution++;
			cout << "1-You Need Add another\n2-no Need another\n";
			yn = Validation::ReadNumberInRange(1, 2);
			if (yn == 1)
				break;
		}
		cout << "You Added" << numberOfsubtetution << "Substitute Player successfully\n";
	}
	cout << "Now You Enter the The 11 Main Players of team 2\n";
	using namespace std::this_thread; // sleep_for, sleep_until
	using namespace std::chrono;
	sleep_until(system_clock::now() + seconds(2));
	playersid.clear();
	for (auto i : Leagues::leagues[LeagueId].teams[Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].team2->TeamId].Players) {

		if (i.second->PlayerPosition == "Goolkeepr") {
			auto j = Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].XI[Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].team2->TeamId].find(i.second->PlayerId);
			if (j == Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].XI[Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].team2->TeamId].end()) {
				cout << i.second->PlayerId << '-' << i.second->PlayerName << '-' << i.second->PlayerPosition << endl;
				playersid.push_back(i.second->PlayerId);
			}
		}
	}
	do {
		playerexist = false;
		cout << "Enter the Id of The main goalkeeper:";
		playerId = Validation::ReadNumber();
		for (auto s : playersid) {
			if (s == playerId)
			{
				playerexist = true;
				break;
			}
		}
		if (playerexist)
			break;
		cout << "invalid Id Enter again\n";
	} while (!playerexist);
	Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].XI[Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].team2->TeamId][playerId] = &Leagues::leagues[LeagueId].Players[playerId];
	cout << "Now we Enter The main players\n";
	sleep_until(system_clock::now() + seconds(2));
	while (counterwhile <= 10) {
		playersid.clear();
		for (auto j : Leagues::leagues[LeagueId].teams[Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].team2->TeamId].Players) {
			if (j.second->PlayerPosition != "Goolkeepr") {
				auto i = Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].XI[Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].team2->TeamId].find(j.second->PlayerId);
				if (i == Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].XI[Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].team2->TeamId].end()) {
					cout << j.second->PlayerId << '-' << j.second->PlayerName << '-' << j.second->PlayerPosition << endl;
					playersid.push_back(j.second->PlayerId);
				}

			}
		}
		do {
			cout << "Enter the Id of The main Player" << counterwhile << ":";
			playerId = Validation::ReadNumber();
			for (auto p : playersid) {
				if (p == playerId) {
					playerexist = true;
					break;
				}
			}
			if (playerexist)
				break;
			cout << "invalid id Enter again\n";
		} while (!playerexist);

		counterwhile++;
		Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].XI[Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].team2->TeamId][playerId] = &Leagues::leagues[LeagueId].Players[playerId];
	}
	counterwhile = 1;
	cout << "You Added the 11 players successfully\n";
	cout << "1-You need to  Enter The Substitute players\n2-no need\n";
	yn = Validation::ReadNumberInRange(1, 2);
	if (yn == 1) {
		int numberOfsubtetution = 1;
		while (numberOfsubtetution <= 5)
		{
			playersid.clear();
			for (auto j : Leagues::leagues[LeagueId].teams[Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].team2->TeamId].Players) {
				auto i = Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].XI[Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].team2->TeamId].find(j.second->PlayerId);
				if (i == Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].XI[Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].team2->TeamId].end()) {
					cout << j.second->PlayerId << '-' << j.second->PlayerName << '-' << j.second->PlayerPosition << endl;
					playersid.push_back(j.second->PlayerId);
				}
			}
			do {
				playerexist = false;
				cout << "Enter the Substitute Player" << numberOfsubtetution << ":";
				playerId = Validation::ReadNumber();
				for (auto l : playersid) {
					if (l == playerId) {
						playerexist = true;
						break;
					}
				}
				if (playerexist)
					break;
				cout << "invalid Id Enter id again\n";
			} while (!playerexist);

			Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].pdla[Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].team2->TeamId][playerId] = &Leagues::leagues[LeagueId].Players[playerId];
			numberOfsubtetution++;
			cout << "1-You Need to Add Another\n2-no need to add another\n";
			yn = Validation::ReadNumberInRange(1, 2);

			if (yn == 1)
				break;
		}
		cout << "You Added" << numberOfsubtetution << "Substitute Player successfully\n";
	}
}
void Admin::clacPoints(int roundId, Match match) {
	stack<Player*>CopyDeka;
	stack<Player*>CopyDeka2;
	bool found = 0;
	bool inteam = 0;
	bool played = 0;
	bool captinisplayed = 0;
	bool captininmatch = 0;

	for (auto i : us) {
		for (auto j : i.squad[LeagueId].squads[roundId]) {
			for (auto k : j.second) {
				while (!(i.squad[LeagueId].deka[roundId].empty())) {
					CopyDeka.push(i.squad[LeagueId].deka[roundId].top());
					if (k->PlayerId == CopyDeka.top()->PlayerId) {
						found = 1;
					}
					CopyDeka.pop();
				}
				while (!CopyDeka.empty())
				{
					i.squad[LeagueId].deka[roundId].push(CopyDeka.top());
					CopyDeka.pop();
				}
				if (!found) {
					for (auto m : match.XI) {
						for (auto n : m.second) {
							if (n.second->PlayerId == k->PlayerId) {
								played = 1;
								break;
							}
						}
						if (played)
							break;
						else if (!played) {
							for (auto m : match.pdla) {
								for (auto n : m.second) {
									if (n.second->PlayerId == k->PlayerId) {
										played = 1;
										break;
									}
								}
								if (played)
									break;
							}
						}
					}
					if (!played) {
						for (auto m : match.team1->Players) {
							if (m.second->PlayerId == k->PlayerId) {
								if (k->PlayerId == i.squad[LeagueId].captain->PlayerId) {
									captinisplayed = 1;
								}
								inteam = 1;
								break;
							}
						}
						if (!inteam) {
							for (auto m : match.team2->Players) {
								if (m.second->PlayerId == k->PlayerId) {
									if (k->PlayerId == i.squad[LeagueId].captain->PlayerId) {
										captinisplayed = 1;
									}
									inteam = 1;
									break;
								}
							}
						}
					}
					if (played) {
						if (k->PlayerId == i.squad[LeagueId].captain->PlayerId) {
							captinisplayed = 1;
							if (i.squad[LeagueId].tribleCaptain == 2) {
								i.squad[LeagueId].RoundPoints[roundId] += (k->PointsInRounds[roundId] * 3);
								i.squad[LeagueId].TotalPoints += (k->PointsInRounds[roundId] * 3);
								i.squad[LeagueId].tribleCaptain == 3;
							}
							else {
								i.squad[LeagueId].RoundPoints[roundId] += (k->PointsInRounds[roundId]) * 2;
								i.squad[LeagueId].TotalPoints += (k->PointsInRounds[roundId] * 2);
							}
						}
						else {
							i.squad[LeagueId].RoundPoints[roundId] += k->PointsInRounds[roundId];
							i.squad[LeagueId].TotalPoints += k->PointsInRounds[roundId];
						}
					}
					if (inteam && captinisplayed) {
						if (i.squad[LeagueId].tribleCaptain == 2) {
							i.squad[LeagueId].RoundPoints[roundId] += (i.squad[LeagueId].ViceCaptain->PointsInRounds[roundId]) * 2;
							i.squad[LeagueId].TotalPoints += (i.squad[LeagueId].ViceCaptain->PointsInRounds[roundId]) * 2;
							i.squad[LeagueId].tribleCaptain == 3;
						}
						else {
							i.squad[LeagueId].RoundPoints[roundId] += i.squad[LeagueId].ViceCaptain->PointsInRounds[roundId];
							i.squad[LeagueId].TotalPoints += i.squad[LeagueId].ViceCaptain->PointsInRounds[roundId];
						}
					}
					if (inteam) {
						while (!i.squad[LeagueId].deka[roundId].empty())
						{
							if (i.squad[LeagueId].deka[roundId].top()->PlayerPosition == "Goolkeepr" && k->PlayerPosition == "Goolkeepr") {
								i.squad[LeagueId].RoundPoints[roundId] += k->PointsInRounds[roundId];
							}
							else if (i.squad[LeagueId].deka[roundId].top()->PlayerPosition != "Goolkeepr") {
								CopyDeka2.push(i.squad[LeagueId].deka[roundId].top());
								for (auto m : match.XI) {
									for (auto n : m.second) {
										if (i.squad[LeagueId].deka[roundId].top()->PlayerId == n.second->PlayerId) {
											played = 1;
											break;
										}
									}
									if (played)
									{
										break;
									}
								}
								for (auto m : match.pdla) {
									for (auto n : m.second) {
										if (i.squad[LeagueId].deka[roundId].top()->PlayerId == n.second->PlayerId) {
											played = 1;
											break;
										}
									}
									if (played) {
										break;
									}
								}
								if (played) {
									i.squad[LeagueId].RoundPoints[roundId] += CopyDeka2.top()->PointsInRounds[roundId];
									i.squad[LeagueId].TotalPoints += CopyDeka2.top()->PointsInRounds[roundId];
									break;
								}
							}
							i.squad[LeagueId].deka[roundId].pop();
						}
						while (!CopyDeka2.empty())
						{
							i.squad[LeagueId].deka[roundId].push(CopyDeka2.top());
							CopyDeka2.pop();
						}
					}
				}
			}
			found = 0;
			inteam = 0;
			played = 0;
			captinisplayed = 0;
			captininmatch = 0;
		}
	}
}