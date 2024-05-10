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
void	Admin::SetLeagueId(const  vector<User>& Users)
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
void	 Admin::Home()
{
	cout << "Please Enter\n";
	cout << "1- Add Team\n";
	cout << "2- Remove Team\n";
	cout << "3- Add Player\n";
	cout << "4- Remove Player\n";
	cout << "5- Add Round\n";
	cout << "6- Add Match\n";
	cout << "7- Remove Round\n";
	cout << "8- Set Result\n";
	cout << "9- View All users\n";
	cout << "10-Logout\n";



	int answer;
	answer = Validation::ReadNumberInRange(1, 10);
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
		return ;
	}
	

}
void Admin::AddTeam() {

	Team team;
	cout << "Enter The Team Name : ";
	bool b = true;
	do {

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

	Home();
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
			Home();
			break;
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
		Leagues::leagues[LeagueId].teams.erase(tID);
		Home();
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
			Home();
			break;
		case 2:
			AddTeam();
			break;

		}
	}
	bool b = 1;
	Player p = Player();
	int tID, ans = 0;
	cout << "Enter Player Name \n";
	p.PlayerName = Validation::nameVal();

	// ----------------------------------------
	cout << "Enter Player Position \n";
	cout << "1-GoalKeeper\n2-defenders\n3-Midfielders\n4-forward\n";
	ans = Validation::ReadNumberInRange(1, 4);

	if (ans == 1)
		p.PlayerPosition = "GoalKeeper";
	else if (ans == 2)
		p.PlayerPosition = "defenders";
	else if (ans == 3)
		p.PlayerPosition = "Midfielders";
	else
		p.PlayerPosition = "forward";
	//------------------------------------
	cout << "Enter Player Price";
	p.PlayerPrice = Validation::ReadNumberInRange(2500, 12000);
	p.PlayerId = Leagues::leagues[LeagueId].Players.rbegin()->second.PlayerId + 1;
	while (true) {
		for (auto i = Leagues::leagues[LeagueId].teams.begin(); i != Leagues::leagues[LeagueId].teams.end(); i++)
			cout << i->first << "\t" << i->second.TeamName << endl;
		cout << "Enter The Team Id : ";

		do {

			tID = Validation::ReadNumber();

			auto j = Leagues::leagues[LeagueId].teams.find(tID);
			if (j == Leagues::leagues[LeagueId].teams.end())
			{
				b = 0;
				cout << "Not found team with this ID , try again\n";
			}
		} while (!b);
		p.LeagueId = LeagueId;
		p.TeamId = tID;
		/*
		auto s = Leagues::leagues[LeagueId].teams.find(tID);
		if (s == Leagues::leagues[LeagueId].teams.end()) {
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


		}*/
		Leagues::leagues[LeagueId].Players[p.PlayerId] = p;
		Leagues::leagues[LeagueId].teams[tID].Players[p.PlayerId] = p;
		break;
	}
	Home();
}
void Admin::AddPlayer(int tID)
{
	bool b = 1;
	Player p = Player();
	int ans = 0;
	cout << "Enter Player Name";
	p.PlayerName = Validation::nameVal();
	cin.ignore();
	// ----------------------------------------
	cout << "Enter Player Position";
	cout << "1-GoalKeeper\n2-defenders\n3-Midfielders\n4-forward\n";
	ans = Validation::ReadNumberInRange(1, 4);

	if (ans == 1)
		p.PlayerPosition = "GoalKeeper";
	else if (ans == 2)
		p.PlayerPosition = "defenders";
	else if (ans == 3)
		p.PlayerPosition = "Midfielders";
	else
		p.PlayerPosition = "forward";
	//------------------------------------
	cout << "Enter Player Price";
	p.PlayerPrice = Validation::ReadNumberInRange(2500, 12000);
	p.PlayerId = Leagues::leagues[LeagueId].Players.rbegin()->second.PlayerId + 1;
	p.LeagueId = LeagueId;
	p.TeamId = tID;
	Leagues::leagues[LeagueId].Players[p.PlayerId] = p;
	Leagues::leagues[LeagueId].teams[tID].Players[p.PlayerId] = p;
}
void Admin::RemovePlayer()
{
	int  tID, PID;
	bool b = 1;

	for (auto i = Leagues::leagues[LeagueId].teams.begin(); i != Leagues::leagues[LeagueId].teams.end(); i++)
		cout << i->first << "\t" << i->second.TeamName << endl;
	cout << "Enter The Team Id : ";
	do {
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
		cout << "Not Teams Found\n1-if you want to go back to home page\n2-if you want to add Player\n";
		ans = Validation::ReadNumberInRange(1, 2);
		switch (ans)
		{
		case 1:
			Home();
			break;
		case 2:
			AddPlayer(tID);
			break;
		}
	}
	else
	{
		for (auto i = Leagues::leagues[LeagueId].teams[tID].Players.begin(); i != Leagues::leagues[LeagueId].teams[tID].Players.end(); i++)
			cout << i->first << "\t" << i->second.PlayerName << endl;
		cout << "Enter The Player Id : ";
		do {
			PID = Validation::ReadNumber();
			auto j = Leagues::leagues[LeagueId].teams.find(tID);
			if (j == Leagues::leagues[LeagueId].teams.end())
			{
				cout << "Not found team with this ID , try again\n";
				b = 0;
			}
		} while (!b);
		Leagues::leagues[LeagueId].teams[tID].Players.erase(PID);
		Leagues::leagues[LeagueId].Players.erase(PID);
		Player playerRemove = Leagues::leagues[LeagueId].teams[tID].Players[PID];
		cout << " Player" << playerRemove.PlayerName << " is Removed successfully :)" << endl;
		Home();
	}
}
void Admin::AddRound()
{
	bool b = 1;
	char answer;
	int roundId;
	if (Leagues::leagues[LeagueId].rounds.size() == (Leagues::leagues[LeagueId].teams.size() - 1) * 2)
	{
		cout << "All rounds is completed\n";
		int ans;
		cout << "1-if you want to go back to home page\n";
		ans = Validation::ReadNumberInRange(1, 1);
		Home();
	}
	do {
		b = 1;
		cout << "Enter number of Round\n";
		roundId = Validation::ReadNumberInRange(1, (Leagues::leagues[LeagueId].teams.size() - 1) * 2);
		auto j = Leagues::leagues[LeagueId].teams.find(roundId);
		if (j != Leagues::leagues[LeagueId].teams.end())
		{
			cout << "This Round is exist\n";
			b = 0;
			int ans;
			cout << "1-if you want to go back to home page\n2-Try again\n";
			ans = Validation::ReadNumberInRange(1, 2);
			switch (ans)
			{
			case 1:
				Home();
				break;
			case 2:
				break;
			}
		}
	} while (!b);
	map<int, Team> tempTeams;
	for (int i = 0; i < 5; i++)
	{
		int t = 0;
		int tID;
		Match match;
		while (t < 2)
		{
			for (auto ii = Leagues::leagues[LeagueId].teams.begin(); ii != Leagues::leagues[LeagueId].teams.end(); i++)
				cout << ii->first << "\t" << ii->second.TeamName << endl;
			cout << "Enter The Team" << t << "Id For Match " << i + 1 << ":\n";
			do {
				tID = Validation::ReadNumber();
				auto j = Leagues::leagues[LeagueId].teams.find(tID);
				if (j == Leagues::leagues[LeagueId].teams.end())
				{
					b = 0;
					cout << "Not found team with this ID , try again\n";
				}
			} while (!b);
			tempTeams[tID] = Leagues::leagues[LeagueId].teams[tID];
			Leagues::leagues[LeagueId].teams.erase(tID);
			if (t == 1)
			{
				match.team1 = tempTeams[tID];
			}
			else
				match.team2 = tempTeams[tID];
			t++;
		}
		match.MatchId = Leagues::leagues[LeagueId].rounds[roundId].matches.rbegin()->second.MatchId + 1;
		cout << "the match Added Successfuly\n";
		Leagues::leagues[LeagueId].rounds[roundId].matches[match.MatchId] = match;
		cout << "1-if you want enter anthor match\n2-if you want to go back to home page\n";
		answer = Validation::ReadNumberInRange(1, 2);
		if (answer == 2) {
			Home();
		}
	}
	cout << "You are added all Matches succesufully\n";
	for (auto i : tempTeams)
	{
		Leagues::leagues[LeagueId].teams[i.first] = i.second;
	}
	Home();
}
void Admin::AddMatch() {
	if (!Leagues::leagues[LeagueId].rounds.size())
	{
		int ans;
		cout << "Not Rounds Found\n1-if you want to go back to home page\n2-if you want to add Round\n";
		ans = Validation::ReadNumberInRange(1, 2);
		switch (ans)
		{
		case 1:
			Home();
			break;
		case 2:
			AddRound();
			break;

		}
	}
	else
	{
		char answer;
		bool b = 1;
		int roundId;
		for (auto i : Leagues::leagues[LeagueId].rounds) {
			cout << i.first << '-' << "Round " << i.second.roundId << endl;
		}
		cout << "Enter the number of the round\n";

		do {
			roundId = Validation::ReadNumber();
			auto s = Leagues::leagues[LeagueId].rounds.find(roundId);
			if (s == Leagues::leagues[LeagueId].rounds.end())
			{
				b = 0;
				cout << "Not found Round with this ID , try again\n";
			}

		} while (!b);

		for (auto i : Leagues::leagues[LeagueId].rounds.find(roundId)->second.matches) {
			cout << i.first << '-' << i.second.team1.TeamName << "     VS     " << i.second.team2.TeamName << endl;
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
						auto j = k.second.team1.TeamId; auto jj = k.second.team2.TeamId;
						if (j != ii->second.TeamId && jj != ii->second.TeamId)
						{
							cout << ii->first << "\t" << ii->second.TeamName << endl;
							teamsId.push_back(ii->first);
						}

					}
				}
				bool exsit = 0;
				do {
					exsit = 0;
					cout << "Enter The Team" << t << "Id For Match " << i + 1 << ":\n";
					tID = Validation::ReadNumber();
					for (int i = 0; i < teamsId.size(); i++)
					{
						if (tID == teamsId[i])
							exsit = 1;
					}
				} while (!exsit);

				if (t == 1)
				{
					match.team1 = Leagues::leagues[LeagueId].teams[tID];
				}
				else
					match.team2 = Leagues::leagues[LeagueId].teams[tID];
				t++;
			}
			match.MatchId = Leagues::leagues[LeagueId].rounds[roundId].matches.rbegin()->second.MatchId + 1;
			cout << "the match Added Successfuly\n";
			Leagues::leagues[LeagueId].rounds[roundId].matches[match.MatchId] = match;
			cout << "1-if you want enter anthor match\n2-if you want to go back to home page\n";
			answer = Validation::ReadNumberInRange(1, 2);
			if (answer == 2) {
				Home();
			}
		}
	}

}
void Admin::RemoveMatch() {
	int roundId, matchId;
	for (auto i : Leagues::leagues[LeagueId].rounds) {
		cout << i.first << '-' << "Round " << i.second.roundId << endl;
	}
	cout << "Enter the number of the round\n";
	cin >> roundId;

	for (auto i : Leagues::leagues[LeagueId].rounds.find(roundId)->second.matches) {
		cout << i.first << '-' << i.second.team1.TeamName << "     VS     " << i.second.team2.TeamName << endl;
	}
	cout << "this is matches of this Round\n";
	cout << "Enter the Id of the Match Which you Want set it's Result:";
	cin >> matchId;
	Leagues::leagues[LeagueId].rounds[roundId].matches.erase(matchId);
	if (Leagues::leagues[LeagueId].rounds[roundId].matches.size() == 0) {
		Leagues::leagues[LeagueId].rounds.erase(roundId);
	}
}
void Admin::setResult() {
	int roundId, matchId, playerId, countOfGoals, countOfassit, res1, res2, assist1, assist2, choicegoal, countOfYellow, countOfRed, numberOfYellow, counterwhile = 1;
	char yn;
	for (auto i : Leagues::leagues[LeagueId].rounds) {
		cout << i.first << '-' << "Round " << i.second.roundId << endl;
	}
	cout << "Enter the number of the round\n";
	cin >> roundId;
	for (auto i : Leagues::leagues[LeagueId].rounds.find(roundId)->second.matches) {
		cout << i.first << '-' << i.second.team1.TeamName << "     VS     " << i.second.team2.TeamName << endl;
	}
	cout << "this is matches of this Round\n";
	cout << "Enter the Id of the Match Which you Want set it's Result:";
	cin >> matchId;
	cout << "/////////////////////////////////////////////////////////////////\n";
	cout << Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].MatchId << "-" << Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].team1.TeamName << "          VS          " << Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].team2.TeamName << endl;
	cout << "Now You Set the Squad of Tow Teams\n";
	setSquadfortowteams(roundId, matchId);
	cout << "Done----------- Now You Added Details of Match";
	cout << "Enter the Result of Team1:";
	cin >> Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].res1;
	cout << "Enter the Result of Team2:";
	cin >> Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].res2;
	res1 = Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].res1;
	res2 = Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].res2;
	while (res1) {
		cout << "if player from the anthor team score goal enter 1 else 2:";
		cin >> choicegoal;
		switch (choicegoal)
		{
		case 1:
			for (auto i : Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].XI[Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].team1.TeamId]) {
				auto j = Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].Details["Goals"].find(i.second.PlayerId);
				if (j == Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].Details["Goals"].end())
					cout << i.first << "-" << i.second.PlayerName << endl;
			}
			for (auto i : Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].pdla[Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].team1.TeamId]) {
				auto j = Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].Details["Goals"].find(i.second.PlayerId);
				if (j == Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].Details["Goals"].end())
					cout << i.first << "-" << i.second.PlayerName << endl;
			}
			cout << "That player who participated in the match\n";
			cout << "enter the Id of player who score one or more:";
			cin >> playerId;
			if (Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].res1 > 1) {
				cout << "Enter the Number of Goals: ";
				cin >> countOfGoals;
			}
			else {
				countOfGoals = 1;
			}
			Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].Details["Goals"][playerId] = countOfGoals;
			res1 -= countOfGoals;
			break;
		case 2:
			for (auto i : Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].XI[Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].team2.TeamId]) {
				auto j = Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].Details["OwnGoal"].find(i.second.PlayerId);
				if (j == Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].Details["OwnGoal"].end())
					cout << i.first << "-" << i.second.PlayerName << endl;

			}
			for (auto i : Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].pdla[Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].team2.TeamId]) {
				auto j = Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].Details["OwnGoal"].find(i.second.PlayerId);
				if (j == Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].Details["OwnGoal"].end())
					cout << i.first << "-" << i.second.PlayerName << endl;
			}
			cout << "That player who participated in the match\n";
			cout << "enter the Id of player who score one or more:";
			cin >> playerId;
			if (Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].res1 > 1) {
				cout << "Enter the Number of Goals: ";
				cin >> countOfGoals;
			}
			else {
				countOfGoals = 1;
			}
			Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].Details["Goals"][playerId] = countOfGoals;
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
			for (auto i : Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].XI[Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].team2.TeamId]) {
				auto j = Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].Details["Goals"].find(i.second.PlayerId);
				if (j == Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].Details["Goals"].end())
					cout << i.first << "-" << i.second.PlayerName << endl;

			}
			for (auto i : Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].pdla[Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].team2.TeamId]) {
				auto j = Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].Details["Goals"].find(i.second.PlayerId);
				if (j == Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].Details["Goals"].end())
					cout << i.first << "-" << i.second.PlayerName << endl;

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
			break;
		case 2:
			for (auto i : Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].XI[Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].team1.TeamId]) {
				auto j = Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].Details["OwnGoal"].find(i.second.PlayerId);
				if (j == Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].Details["OwnGoal"].end())
					cout << i.first << "-" << i.second.PlayerName << endl;
			}
			for (auto i : Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].pdla[Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].team1.TeamId]) {
				auto j = Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].Details["OwnGoal"].find(i.second.PlayerId);
				if (j == Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].Details["OwnGoal"].end())
					cout << i.first << "-" << i.second.PlayerName << endl;
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
		for (auto i : Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].XI[Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].team1.TeamId]) {
			auto j = Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].Details["Assist"].find(i.second.PlayerId);
			if (j == Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].Details["Assist"].end())
				cout << i.first << "-" << i.second.PlayerName << endl;
		}
		for (auto i : Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].pdla[Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].team1.TeamId]) {
			auto j = Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].Details["Assist"].find(i.second.PlayerId);
			if (j == Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].Details["Assist"].end())
				cout << i.first << "-" << i.second.PlayerName << endl;
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
		for (auto i : Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].XI[Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].team2.TeamId]) {
			auto j = Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].Details["Assist"].find(i.second.PlayerId);
			if (j == Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].Details["Assist"].end())
				cout << i.first << "-" << i.second.PlayerName << endl;
		}
		for (auto i : Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].pdla[Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].team2.TeamId]) {
			auto j = Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].Details["Assist"].find(i.second.PlayerId);
			if (j == Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].Details["Assist"].end())
				cout << i.first << "-" << i.second.PlayerName << endl;
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
		for (auto i : Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].XI[Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].team1.TeamId]) {
			auto j = Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].Details["Yellow"].find(i.second.PlayerId);
			if (j == Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].Details["Yellow"].end())
				cout << i.first << "-" << i.second.PlayerName << endl;
		}
		for (auto i : Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].pdla[Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].team1.TeamId]) {
			auto j = Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].Details["Yellow"].find(i.second.PlayerId);
			if (j == Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].Details["Yellow"].end())
				cout << i.first << "-" << i.second.PlayerName << endl;
		}
		for (auto i : Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].XI[Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].team2.TeamId]) {
			auto j = Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].Details["Yellow"].find(i.second.PlayerId);
			if (j == Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].Details["Yellow"].end())
				cout << i.first << "-" << i.second.PlayerName << endl;
		}
		for (auto i : Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].pdla[Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].team2.TeamId]) {
			auto j = Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].Details["Yellow"].find(i.second.PlayerId);
			if (j == Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].Details["Yellow"].end())
				cout << i.first << "-" << i.second.PlayerName << endl;
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
		Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].Details["Yellow"][playerId] = countOfassit;
		countOfYellow -= countOfassit;
	}
	cout << "Enter the Number of Red card in Match:";
	cin >> countOfRed;
	while (countOfRed)
	{
		for (auto i : Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].XI[Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].team1.TeamId]) {
			auto j = Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].Details["Red"].find(i.second.PlayerId);
			if (j == Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].Details["Red"].end())
				cout << i.first << "-" << i.second.PlayerName << endl;
		}
		for (auto i : Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].pdla[Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].team1.TeamId]) {
			auto j = Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].Details["Red"].find(i.second.PlayerId);
			if (j == Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].Details["Red"].end())
				cout << i.first << "-" << i.second.PlayerName << endl;
		}
		for (auto i : Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].XI[Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].team2.TeamId]) {
			auto j = Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].Details["Red"].find(i.second.PlayerId);
			if (j == Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].Details["Red"].end())
				cout << i.first << "-" << i.second.PlayerName << endl;
		}
		for (auto i : Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].pdla[Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].team2.TeamId]) {
			auto j = Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].Details["Red"].find(i.second.PlayerId);
			if (j == Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].Details["Red"].end())
				cout << i.first << "-" << i.second.PlayerName << endl;
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
				Leagues::leagues[LeagueId].teams[Leagues::leagues[LeagueId].Players[j.first].TeamId].Players[j.first].PointsInRounds[roundId] = 6 * j.second;
			}
			else if (i.first == "Assist") {
				Leagues::leagues[LeagueId].Players[j.first].PointsInRounds[roundId] += 4 * j.second;
				Leagues::leagues[LeagueId].teams[Leagues::leagues[LeagueId].Players[j.first].TeamId].Players[j.first].PointsInRounds[roundId] = 4 * j.second;
			}
			else if (i.first == "Yellow") {
				Leagues::leagues[LeagueId].Players[j.first].PointsInRounds[roundId] += -1 * j.second;
				Leagues::leagues[LeagueId].teams[Leagues::leagues[LeagueId].Players[j.first].TeamId].Players[j.first].PointsInRounds[roundId] = -1 * j.second;
			}

			else if (i.first == "Red") {
				Leagues::leagues[LeagueId].Players[j.first].PointsInRounds[roundId] += -3;
				Leagues::leagues[LeagueId].teams[Leagues::leagues[LeagueId].Players[j.first].TeamId].Players[j.first].PointsInRounds[roundId] += -3;
			}
			else if (i.first == "OwnGoal") {
				Leagues::leagues[LeagueId].Players[j.first].PointsInRounds[roundId] += -4;
				Leagues::leagues[LeagueId].teams[Leagues::leagues[LeagueId].Players[j.first].TeamId].Players[j.first].PointsInRounds[roundId] += -4;
			}
		}
	}
	for (auto i : Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].XI[Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].team1.TeamId]) {
		Leagues::leagues[LeagueId].Players[i.first].PointsInRounds[roundId] += 2;
	}
	for (auto i : Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].pdla[Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].team1.TeamId]) {
		Leagues::leagues[LeagueId].Players[i.first].PointsInRounds[roundId] += 1;
	}
	clacPoints(roundId, Leagues::leagues[LeagueId].rounds[roundId].matches[matchId]);
}
void Admin::setSquadfortowteams(int roundId, int matchId) {
	int playerId, counterwhile = 1;
	char yn;
	cout << "Now You Enter the The 11 Main Players of team 1\n";
	using namespace std::this_thread; // sleep_for, sleep_until
	using namespace std::chrono;
	sleep_until(system_clock::now() + seconds(2));
	for (auto i : Leagues::leagues[LeagueId].teams[Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].team1.TeamId].Players) {

		if (i.second.PlayerPosition == "Goolkeepr") {
			/*auto j = Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].XI[Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].team1.TeamId].find(i.second.PlayerId);
			if (j == Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].XI[Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].team1.TeamId].end())*/
			cout << i.second.PlayerId << '-' << i.second.PlayerName << '-' << i.second.PlayerPosition << endl;
		}
	}
	cout << "Enter the Id of The main goalkeeper:";
	cin >> playerId;
	Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].XI[Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].team1.TeamId][playerId] = Leagues::leagues[LeagueId].Players[playerId];
	cout << "Now we Enter The main players\n";
	sleep_until(system_clock::now() + seconds(2));
	while (counterwhile <= 10) {
		for (auto j : Leagues::leagues[LeagueId].teams[Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].team1.TeamId].Players) {
			if (j.second.PlayerPosition != "Goolkeepr") {
				auto i = Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].XI[Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].team1.TeamId].find(j.second.PlayerId);
				if (i == Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].XI[Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].team1.TeamId].end())
					cout << j.second.PlayerId << '-' << j.second.PlayerName << '-' << j.second.PlayerPosition << endl;
			}
		}
		cout << "Enter the Id of The main Player" << counterwhile << ":";
		cin >> playerId;
		counterwhile++;
		Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].XI[Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].team1.TeamId][playerId] = Leagues::leagues[LeagueId].Players[playerId];
	}
	counterwhile = 1;
	cout << "You Added the 11 players successfully\n";
	cout << " You need Enter The Substitute players(y/n)?\n";
	cin >> yn;
	if (yn == 'y' || yn == 'Y') {
		int numberOfsubtetution = 1;
		while (numberOfsubtetution <= 5)
		{
			for (auto j : Leagues::leagues[LeagueId].teams[Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].team1.TeamId].Players) {
				auto i = Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].XI[Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].team1.TeamId].find(j.second.PlayerId);
				if (i == Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].XI[Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].team1.TeamId].end())
					cout << j.second.PlayerId << '-' << j.second.PlayerName << '-' << j.second.PlayerPosition << endl;
			}
			cout << "Enter the Substitute Player" << numberOfsubtetution << ":";
			cin >> playerId;

			Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].pdla[Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].team1.TeamId][playerId] = Leagues::leagues[LeagueId].Players[playerId];
			numberOfsubtetution++;
			cout << "You Need Add Anthor (y/n)?";
			cin >> yn;
			if (yn == 'n' || yn == 'N')
				break;
		}
		cout << "You Added" << numberOfsubtetution << "Substitute Player successfully\n";
	}
	cout << "Now You Enter the The 11 Main Players of team 2\n";
	using namespace std::this_thread; // sleep_for, sleep_until
	using namespace std::chrono;
	sleep_until(system_clock::now() + seconds(2));
	for (auto i : Leagues::leagues[LeagueId].teams[Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].team2.TeamId].Players) {

		if (i.second.PlayerPosition == "Goolkeepr") {
			auto j = Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].XI[Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].team2.TeamId].find(i.second.PlayerId);
			if (j == Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].XI[Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].team2.TeamId].end())
				cout << i.second.PlayerId << '-' << i.second.PlayerName << '-' << i.second.PlayerPosition << endl;
		}
	}
	cout << "Enter the Id of The main goalkeeper:";
	cin >> playerId;
	Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].XI[Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].team2.TeamId][playerId] = Leagues::leagues[LeagueId].Players[playerId];
	cout << "Now we Enter The main players\n";
	sleep_until(system_clock::now() + seconds(2));
	while (counterwhile <= 10) {
		for (auto j : Leagues::leagues[LeagueId].teams[Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].team2.TeamId].Players) {
			if (j.second.PlayerPosition != "Goolkeepr") {
				auto i = Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].XI[Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].team2.TeamId].find(j.second.PlayerId);
				if (i == Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].XI[Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].team2.TeamId].end())
					cout << j.second.PlayerId << '-' << j.second.PlayerName << '-' << j.second.PlayerPosition << endl;
			}
		}
		cout << "Enter the Id of The main Player" << counterwhile << ":";
		cin >> playerId;
		counterwhile++;
		Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].XI[Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].team2.TeamId][playerId] = Leagues::leagues[LeagueId].Players[playerId];
	}
	counterwhile = 1;
	cout << "You Added the 11 players successfully\n";
	cout << " You need Enter The Substitute players(y/n)?\n";
	cin >> yn;
	if (yn == 'y' || yn == 'Y') {
		int numberOfsubtetution = 1;
		while (numberOfsubtetution <= 5)
		{
			for (auto j : Leagues::leagues[LeagueId].teams[Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].team2.TeamId].Players) {
				auto i = Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].XI[Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].team2.TeamId].find(j.second.PlayerId);
				if (i == Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].XI[Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].team2.TeamId].end())
					cout << j.second.PlayerId << '-' << j.second.PlayerName << '-' << j.second.PlayerPosition << endl;
			}
			cout << "Enter the Substitute Player" << numberOfsubtetution << ":";
			cin >> playerId;
			Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].pdla[Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].team2.TeamId][playerId] = Leagues::leagues[LeagueId].Players[playerId];
			numberOfsubtetution++;
			cout << "You Need Add Anthor (y/n)?";
			cin >> yn;
			if (yn == 'n' || yn == 'N')
				break;
		}
		cout << "You Added" << numberOfsubtetution << "Substitute Player successfully\n";
	}
}
void Admin::clacPoints(int roundId, Match match) {
	stack<Player>CopyDeka;
	stack<Player>CopyDeka2;
	bool found = 0;
	bool inteam = 0;
	bool played = 0;
	bool captinisplayed = 0;
	bool captininmatch = 0;

	for (auto i : us) {
		for (auto j : i.squad[LeagueId].squads) {
			for (auto k : j.second) {
				while (!(i.squad[LeagueId].deka.empty())) {
					CopyDeka.push(i.squad[LeagueId].deka.top());
					if (k.PlayerId == CopyDeka.top().PlayerId) {
						found = 1;
					}
					CopyDeka.pop();
				}
				while (!CopyDeka.empty())
				{
					i.squad[LeagueId].deka.push(CopyDeka.top());
					CopyDeka.pop();
				}
				if (!found) {
					for (auto m : match.XI) {
						for (auto n : m.second) {
							if (n.second.PlayerId == k.PlayerId) {
								played = 1;
								break;
							}
						}
						if (played)
							break;
						else if (!played) {
							for (auto m : match.pdla) {
								for (auto n : m.second) {
									if (n.second.PlayerId == k.PlayerId) {
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
						for (auto m : match.team1.Players) {
							if (m.second.PlayerId == k.PlayerId) {
								if (k.PlayerId == i.squad[LeagueId].captain.PlayerId) {
									captinisplayed = 1;
								}
								inteam = 1;
								break;
							}
						}
						if (!inteam) {
							for (auto m : match.team2.Players) {
								if (m.second.PlayerId == k.PlayerId) {
									if (k.PlayerId == i.squad[LeagueId].captain.PlayerId) {
										captinisplayed = 1;
									}
									inteam = 1;
									break;
								}
							}
						}
					}
					if (played) {
						if (k.PlayerId == i.squad[LeagueId].captain.PlayerId) {
							captinisplayed = 1;
							if (i.squad[LeagueId].tribleCaptain) {
								i.squad[LeagueId].RoundPoints[roundId] += (k.PointsInRounds[roundId] * 3);
								i.squad[LeagueId].TotalPoints += (k.PointsInRounds[roundId] * 3);
							}
							else {
								i.squad[LeagueId].RoundPoints[roundId] += (k.PointsInRounds[roundId]) * 2;
								i.squad[LeagueId].TotalPoints += (k.PointsInRounds[roundId] * 2);
							}
						}
						else {
							i.squad[LeagueId].RoundPoints[roundId] += k.PointsInRounds[roundId];
							i.squad[LeagueId].TotalPoints += k.PointsInRounds[roundId];
						}
					}
					if (inteam && captinisplayed) {
						if (i.squad[LeagueId].tribleCaptain) {
							i.squad[LeagueId].RoundPoints[roundId] += (i.squad[LeagueId].ViceCaptain.PointsInRounds[roundId]) * 2;
							i.squad[LeagueId].TotalPoints += (i.squad[LeagueId].ViceCaptain.PointsInRounds[roundId]) * 2;
						}
						else {
							i.squad[LeagueId].RoundPoints[roundId] += i.squad[LeagueId].ViceCaptain.PointsInRounds[roundId];
							i.squad[LeagueId].TotalPoints += i.squad[LeagueId].ViceCaptain.PointsInRounds[roundId];
						}
					}
					if (inteam) {
						while (!i.squad[LeagueId].deka.empty())
						{
							if (i.squad[LeagueId].deka.top().PlayerPosition == "Goolkeepr" && k.PlayerPosition == "Goolkeepr") {
								i.squad[LeagueId].RoundPoints[roundId] += k.PointsInRounds[roundId];
							}
							else if (i.squad[LeagueId].deka.top().PlayerPosition != "Goolkeepr") {
								CopyDeka2.push(i.squad[LeagueId].deka.top());
								for (auto m : match.XI) {
									for (auto n : m.second) {
										if (i.squad[LeagueId].deka.top().PlayerId == n.second.PlayerId) {
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
										if (i.squad[LeagueId].deka.top().PlayerId == n.second.PlayerId) {
											played = 1;
											break;
										}
									}
									if (played) {
										break;
									}
								}
								if (played) {
									i.squad[LeagueId].RoundPoints[roundId] += CopyDeka2.top().PointsInRounds[roundId];
									i.squad[LeagueId].TotalPoints += CopyDeka2.top().PointsInRounds[roundId];
									break;
								}
							}
							i.squad[LeagueId].deka.pop();
						}
						while (!CopyDeka2.empty())
						{
							i.squad[LeagueId].deka.push(CopyDeka2.top());
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
