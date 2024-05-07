
#include "Admin.h"
#include <chrono>
#include <thread>
map<int, League> Leagues::leagues;
int LeagueId;
Admin::Admin() {}
Admin::Admin(int id, string name, string password)
{
	Name = name;
	Password = password;
	Id = id;
}
int Admin::SetLeagueId()
{
	int legId;
	for (int i = 1; i <= 3; i++) {
		cout << i << "\t" << Leagues::leagues[i].LaegueName << endl;
	}
	cout << "Please Enter League Id\n";
	cin >> legId;

	LeagueId = legId;
	if (Home() == 0) {
		return 0;
	}
	Home();

}
int Admin::Home()
{



	cout << "Please Enter\n";
	cout << "1- Add Team\n";
	cout << "2- Remove Team\n";
	cout << "3- Add Player\n";
	cout << "4- Remove Player\n";
	cout << "5- Add Round\n";
	cout << "6- End Round\n";
	cout << "7- Set Result\n";
	cout << "8- View All users\n";
	cout << "9-Logout\n";



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
		setResult();
		break;
	case 8:
		return 0;


	}


}
void Admin::AddTeam() {

	Team team;
	cout << "Enter The Team Name : ";
	cin >> team.TeamName;
	cout << "Team " << team.TeamName << " is added successfully :)" << endl;
	team.LeagueId = LeagueId;
	team.TeamId = Leagues::leagues[LeagueId].teams.rbegin()->second.TeamId + 1;
	Leagues::leagues[LeagueId].teams[team.TeamId] = team;

	Home();
}
void Admin::RemoveTeam() {

	int tID;
	for (auto i = Leagues::leagues[LeagueId].teams.begin(); i != Leagues::leagues[LeagueId].teams.end(); i++)
		cout << i->first << "\t" << i->second.TeamName << endl;
	cout << "Enter The Team Id : ";
	cin >> tID;
	Team teamRemove = Leagues::leagues[LeagueId].teams[tID];
	cout << "Team " << teamRemove.TeamName << " is Removed successfully :)" << endl;
	Leagues::leagues[LeagueId].teams.erase(tID);
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
	p.PlayerId = Leagues::leagues[LeagueId].Players.rbegin()->second.PlayerId + 1;
	while (true) {
		for (auto i = Leagues::leagues[LeagueId].teams.begin(); i != Leagues::leagues[LeagueId].teams.end(); i++)
			cout << i->first << "\t" << i->second.TeamName << endl;
		cout << "Enter The Team Id : ";
		cin >> tID;
		p.LeagueId = LeagueId;
		p.TeamId = tID;

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
			Leagues::leagues[LeagueId].Players[p.PlayerId] = p;
			Leagues::leagues[LeagueId].teams[tID].Players[p.PlayerId] = p;

		}
		break;
	}
	Home();
}
void Admin::RemovePlayer()
{
	int  tID, PID;
	for (auto i = Leagues::leagues[LeagueId].teams.begin(); i != Leagues::leagues[LeagueId].teams.end(); i++)
		cout << i->first << "\t" << i->second.TeamName << endl;
	cout << "Enter The Team Id : ";
	cin >> tID;
	for (auto i = Leagues::leagues[LeagueId].teams[tID].Players.begin(); i != Leagues::leagues[LeagueId].teams[tID].Players.end(); i++)
		cout << i->first << "\t" << i->second.PlayerName << endl;
	cout << "Enter The Player Id : ";
	cin >> PID;
	Leagues::leagues[LeagueId].teams[tID].Players.erase(PID);
	Leagues::leagues[LeagueId].Players.erase(PID);
	Player playerRemove = Leagues::leagues[LeagueId].teams[tID].Players[PID];
	cout << " Player" << playerRemove.PlayerName << " is Removed successfully :)" << endl;
	Home();

}
void Admin::AddRound()
{
	char answer;
	int roundId;
	cout << "Enter number of Round\n";
	cin >> roundId;
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
			cin >> tID;
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
		cout << "Are you want enter anthor match (y/n)?";
		cin >> answer;
		if (answer == 'n' || answer == 'N') {
			return;
		}
	}
	for (auto i : tempTeams)
	{
		Leagues::leagues[LeagueId].teams[i.first] = i.second;
	}
	Home();
}
void Admin::RemoveRound()
{
	int roundId;
	for (auto i = Leagues::leagues[LeagueId].rounds.begin(); i != Leagues::leagues[LeagueId].rounds.end(); i++)
	{
		cout << "Round " << i->first << endl;
	}
	cout << "Enter number of Round that you want to remove \n";
	cin >> roundId;
	Leagues::leagues[LeagueId].rounds.erase(roundId);
	cout << " Round " << roundId << " is Removed successfully :)" << endl;
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
		cout << i.first << '-' << i.second.team1.TeamName <<"     VS     " << i.second.team2.TeamName << endl;
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
				if (j== Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].Details["Goals"].end())
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
			res1 -= countOfGoals;
			break;
		case 2:
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
			if (Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].res2 > 1) {
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
			if (i.first == "Goals")
				Leagues::leagues[LeagueId].Players[j.first].PointsInRounds[roundId] += 6 * j.second;
			else if (i.first == "Assist")
				Leagues::leagues[LeagueId].Players[j.first].PointsInRounds[roundId] += 4 * j.second;
			else if (i.first == "Yellow")
				Leagues::leagues[LeagueId].Players[j.first].PointsInRounds[roundId] += -1 * j.second;
			else if (i.first == "Red")
				Leagues::leagues[LeagueId].Players[j.first].PointsInRounds[roundId] += -2;
		}
	}
	for (auto i : Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].XI[Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].team1.TeamId]) {
		Leagues::leagues[LeagueId].Players[i.first].PointsInRounds[roundId] += 2;
	}
	for (auto i : Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].pdla[Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].team1.TeamId]) {
		Leagues::leagues[LeagueId].Players[i.first].PointsInRounds[roundId] += 1;
	}
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
			auto j = Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].XI[Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].team1.TeamId].find(i.second.PlayerId);
			if (j == Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].XI[Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].team1.TeamId].end())
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
		Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].XI[Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].team1.TeamId][playerId] = Leagues::leagues[LeagueId].Players[playerId];
	}
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
		Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].XI[Leagues::leagues[LeagueId].rounds[roundId].matches[matchId].team2.TeamId][playerId] = Leagues::leagues[LeagueId].Players[playerId];
	}
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
