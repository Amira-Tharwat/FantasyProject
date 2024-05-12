#include "Admin.h"
#include <fstream>
#include <sstream>
vector<User> users;
vector<Admin> admins;
void ReadFromFiles();
void WriteInFiles();
void First_Page();
void SignIn();
void SignUp();
int main() {
	ReadFromFiles();
	First_Page();
	WriteInFiles();
	exit(0);
}
void First_Page() {
	int answer;
	while (true) {
		cout << "1-SignIn \n2-SignUp\n3-exit program\n";
		answer = Validation::ReadNumberInRange(1, 3);
		switch (answer)
		{
		case 1:
			SignIn();
			break;
		case 2:
			SignUp();
			break;
		case 3:
			WriteInFiles();
			exit(0);
		default:
			cout << "Invaled choose" << endl;
		}
	}
}
void SignIn() {
	int answer1;
	string name, password;
	bool iffound = false;
	cout << "Enter your name\n";
	getline(cin, name);
	cout << "Enter your password\n";
	password = Validation::password();
	for (int i = 0; i < 7; i++) {
		if (admins[i].Name == name && admins[i].Password == password)
		{
			iffound = true;
			cout << "\nwelcome " << name << " in home admin" << endl;//function home admin  
			Admin::SetLeagueId(users);
			First_Page();
		}
	}
	if (!iffound) {
		for (int i = 0; i < users.size(); i++) {
			if (users[i].Name == name && users[i].Password == password) {
				iffound = true;
				cout << "\nwelcome " << name << " in home user" << endl;//function home user
				users[i].GetUsers(users);
				users[i].chooseLeague(users[i].Id);
				break;
			}
		}
	}
	if (!iffound) {
		cout << "the name or password is uncorrect.. \n";
		do {
			cout << "1-try again\n2-back to home page\n";
			answer1 = Validation::ReadNumberInRange(1, 2);

			switch (answer1)
			{
			case 1:

				SignIn();
				break;
			case 2:
				First_Page();
				break;
			default:
				break;
			}
			if (answer1 == 1 || answer1 == 2) {
				break;
			}
			else {
				cout << "enter 1 or 2 only\n";
			}
		} while (answer1 != 1 && answer1 != 2);
	}
}
void SignUp() {
	User user = User();
	cout << "Enter your name\n";
	user.Name = Validation::username(users);
	cout << "Enter your password\n";
	user.Password = Validation::pass();
	for (auto i : Leagues::leagues) {
		user.squad[i.first].TotalPoints = 0;
	}
	users.push_back(user);
	cout << "\nyour account created\n";
	First_Page();
}
void ReadFromFiles() {
	ifstream adminsfile, teamsfile, playersfile, playerpointsfile, leaguesfile, usersfile, squadfile, userroundpointsfile, matchsfile, detailsmatchs, roundsfile;
	leaguesfile.open("Leagues.txt");
	adminsfile.open("Admins.txt");
	usersfile.open("Users.txt");
	teamsfile.open("Teams.txt");
	playersfile.open("Players.txt");
	playerpointsfile.open("Playerspoints.txt");
	squadfile.open("Squad.txt");
	userroundpointsfile.open("UserRoundPoints.txt");
	matchsfile.open("Matchs.txt");
	detailsmatchs.open("DetailsMatchs");
	roundsfile.open("Rounds.txt");

	for (int i = 1; i < 4; i++) {
		Leagues::leagues[i].LeagueId = i;
		leaguesfile >> Leagues::leagues[i].LaegueName;

	}
	for (int i = 0; i < 7; i++) {
		Admin admin;
		adminsfile >> admin.Id;
		adminsfile >> admin.Name;
		adminsfile >> admin.Password;
		admins.push_back(admin);
	}
	string line;

	while (getline(teamsfile, line)) {
		istringstream iss(line);
		string token;
		Team team;
		vector<string> tokens;
		while (getline(iss, token, ',')) {

			tokens.push_back(token);

		}
		istringstream isss0(tokens[0]);
		isss0 >> team.LeagueId;
		istringstream isss1(tokens[1]);
		isss1 >> team.TeamName;
		istringstream isss2(tokens[2]);
		isss2 >> team.TeamId;

		Leagues::leagues[team.LeagueId].teams[team.TeamId] = team;

	}
	while (getline(playersfile, line)) {
		istringstream iss(line);
		string token;
		Player* player = new Player();
		vector<string> tokens;
		while (getline(iss, token, ',')) {

			tokens.push_back(token);

		}
		istringstream isss0(tokens[0]);
		isss0 >> player->TeamId;
		istringstream isss1(tokens[1]);
		isss1 >> player->LeagueId;
		istringstream isss2(tokens[2]);
		isss2 >> player->PlayerId;
		istringstream isss3(tokens[3]);
		isss3 >> player->PlayerName;
		istringstream isss4(tokens[4]);
		isss4 >> player->PlayerPosition;
		istringstream isss5(tokens[5]);
		isss5 >> player->PlayerPrice;



		Leagues::leagues[player->LeagueId].teams[player->TeamId].Players[player->PlayerId] = player;
		Leagues::leagues[player->LeagueId].Players[player->PlayerId] = *player;
	}

	while (getline(playerpointsfile, line)) {
		istringstream iss(line);
		string token;
		Player player;
		int roundid;
		int points;
		vector<string> tokens;
		while (getline(iss, token, ',')) {

			tokens.push_back(token);

		}
		istringstream isss0(tokens[0]);
		isss0 >> player.LeagueId;
		istringstream isss1(tokens[1]);
		isss1 >> player.TeamId;
		istringstream isss2(tokens[2]);
		isss2 >> player.PlayerId;
		istringstream isss3(tokens[3]);
		isss3 >> roundid;
		istringstream isss4(tokens[4]);
		isss4 >> points;
		Leagues::leagues[player.LeagueId].teams[player.TeamId].Players[player.PlayerId]->PointsInRounds[roundid] = points;
	}
	while (getline(usersfile, line)) {
		istringstream iss(line);
		string token;
		vector<string> tokens;
		while (getline(iss, token, ',')) {

			tokens.push_back(token);

		}
		User user;
		istringstream isss0(tokens[0]);
		isss0 >> user.Id;
		istringstream isss1(tokens[1]);
		isss1 >> user.Name;
		istringstream isss2(tokens[2]);
		isss2 >> user.Password;

		users.push_back(user);

	}
	while (getline(squadfile, line)) {
		istringstream iss(line);
		string token,deka;
		vector<string> tokens;

		int userid, roundid, leagueid;
		Squad squad;
		while (getline(iss, token, '-')) {

			tokens.push_back(token);

		}

		istringstream isss0(tokens[0]);
		isss0 >> leagueid;
		istringstream isss1(tokens[1]);
		isss1 >> userid;
		istringstream isss2(tokens[2]);
		isss2 >> roundid;
		for (int i = 3; i <= 17; i++) {
			int PlayerId;
			istringstream isss3(tokens[i]);
			isss3 >> PlayerId;
			users[userid - 1].squad[leagueid].squads[roundid][Leagues::leagues[leagueid].Players[PlayerId].PlayerPosition].push_back(&Leagues::leagues[leagueid].Players[PlayerId]);
		}
		istringstream isss3(tokens[18]);
		isss3 >> deka;
		string token2;
		int	playeriddeka;
		vector <string>tokens2;
		
		while (getline(isss3, token2, ',')) {
			tokens2.push_back(token2);
		}
		if (!tokens2.empty()) {
			for (int i = 0; i < 4; i++) {
				istringstream isss0(tokens2[i]);
				isss0 >> playeriddeka;
				users[userid - 1].squad[leagueid].deka[roundid].push(&Leagues::leagues[leagueid].Players[playeriddeka]);
			}
			
		}
		

		
		istringstream isss4(tokens[19]);
		isss4 >> users[userid - 1].squad[leagueid].TotalPoints;
		int playerid;
		istringstream isss5(tokens[20]);
		isss5 >> playerid;
		users[userid - 1].squad[leagueid].captain = &Leagues::leagues[leagueid].Players[playerid];
		istringstream isss6(tokens[21]);
		isss6 >> playerid;
		users[userid - 1].squad[leagueid].ViceCaptain = &Leagues::leagues[leagueid].Players[playerid];
		istringstream isss7(tokens[22]);
		isss7 >> users[userid - 1].squad[leagueid].tribleCaptain;
		istringstream isss8(tokens[23]);
		isss8 >> users[userid - 1].squad[leagueid].wildCard;
		istringstream isss9(tokens[24]);
		isss9 >> users[userid - 1].squad[leagueid].numOfSubestitution;
		istringstream isss10(tokens[25]);
		isss10 >> users[userid - 1].squad[leagueid].Budget;
	}
	while (getline(userroundpointsfile, line)) {
		istringstream iss(line);
		string token;
		vector<string> tokens;
		while (getline(iss, token, '-')) {

			tokens.push_back(token);

		}
		int leagueid, userid, roundid, points;
		istringstream isss0(tokens[0]);
		isss0 >> leagueid;
		istringstream isss1(tokens[1]);
		isss1 >> userid;
		istringstream isss2(tokens[2]);
		isss2 >> roundid;
		istringstream isss3(tokens[3]);
		isss3 >> points;
		users[userid].squad[leagueid].RoundPoints[roundid] = points;
	}
	while (getline(roundsfile, line)) {
		istringstream iss(line);
		string token;
		vector<string> tokens;
		while (getline(iss, token, ',')) {

			tokens.push_back(token);

		}
		int leagueid;
		Round round;
		istringstream isss0(tokens[0]);
		isss0 >> leagueid;
		istringstream isss1(tokens[1]);
		isss1 >> round.roundId;
		Leagues::leagues[leagueid].rounds[round.roundId] = round;
	}
	while (getline(matchsfile, line)) {
		istringstream iss(line);
		string token;
		vector<string> tokens;
		Match match;
		int leagueid;
		int roundid;

		while (getline(iss, token, '-')) {

			tokens.push_back(token);

		}
		istringstream isss0(tokens[0]);
		isss0 >> leagueid;
		istringstream isss1(tokens[1]);
		isss1 >> roundid;
		istringstream isss2(tokens[2]);
		isss2 >> match.MatchId;
		istringstream isss3(tokens[3]);
		isss3 >> match.isPlayed;
		istringstream isss4(tokens[4]);
		int teamid1;
		isss4 >> teamid1;

		istringstream isss5(tokens[5]);
		isss5 >> match.res1;
		istringstream isss7(tokens[7]);
		int teamid2;
		isss7 >> teamid2;
		istringstream isss8(tokens[8]);
		isss8 >> match.res2;
		istringstream isss6(tokens[6]);

		match.team1 = &Leagues::leagues[leagueid].teams[teamid1];
		match.team2 = &Leagues::leagues[leagueid].teams[teamid2];
		string token2;
		vector <string>tokens2;
		int playerid;
		while (getline(isss6, token2, ',')) {
			tokens2.push_back(token2);
		}
		if (!tokens2.empty()) {
			for (int i = 0; i < 11; i++) {
				istringstream isss0(tokens2[i]);
				isss0 >> playerid;
				match.XI[match.team1->TeamId][playerid] = &Leagues::leagues[leagueid].Players[playerid];
			}
			for (int i = 11; i < tokens2.size(); i++) {
				istringstream isss0(tokens2[i]);
				isss0 >> playerid;
				match.pdla[match.team1->TeamId][playerid] = &Leagues::leagues[leagueid].Players[playerid];
			}
		}

		istringstream isss9(tokens[9]);
		string token3;
		vector <string>tokens3;
		int playerid2;
		while (getline(isss9, token3, ',')) {
			tokens3.push_back(token3);
		}
		if (!tokens3.empty()) {
			for (int i = 0; i < 11; i++) {
				istringstream isss0(tokens3[i]);
				isss0 >> playerid2;
				match.XI[match.team2->TeamId][playerid2] = &Leagues::leagues[leagueid].Players[playerid2];
			}
			for (int i = 11; i < tokens3.size(); i++) {
				istringstream isss0(tokens3[i]);
				isss0 >> playerid2;
				match.pdla[match.team2->TeamId][playerid2] = &Leagues::leagues[leagueid].Players[playerid2];
			}
		}

		Leagues::leagues[leagueid].rounds[roundid].matches[match.MatchId] = match;
	}
	while (getline(detailsmatchs, line))
	{

		istringstream iss(line);
		string token;
		vector<string> tokens;
		int matchid;
		int leagueid;
		int roundid;

		while (getline(iss, token, ',')) {

			tokens.push_back(token);

		}
		istringstream isss0(tokens[0]);
		isss0 >> leagueid;
		istringstream isss1(tokens[1]);
		isss1 >> roundid;
		istringstream isss2(tokens[2]);
		isss2 >> matchid;
		for (int i = 3; i < tokens.size(); i++) {
			istringstream isss(tokens[i]);
			string token2;
			string position;
			vector <string>tokens2;
			while (getline(isss, token2, '>')) {
				tokens2.push_back(token2);
			}
			istringstream isss0(tokens2[0]);
			isss0 >> position;
			for (int j = 1; j < tokens2.size(); j++) {
				istringstream isss(tokens[j]);
				string token3;
				int playerid;
				int count;
				vector <string>tokens3;
				while (getline(isss, token3, '-')) {
					tokens3.push_back(token3);
				}
				istringstream isss0(tokens[0]);
				isss0 >> playerid;
				istringstream isss1(tokens[1]);
				isss1 >> count;
				Leagues::leagues[leagueid].rounds[roundid].matches[matchid].Details[position][playerid] = count;
			}
		}
	}
	adminsfile.close();
	teamsfile.close();
	playersfile.close();

	playerpointsfile.close();
	usersfile.close();
	squadfile.close();
	userroundpointsfile.close();
	matchsfile.close();
	detailsmatchs.close();
	roundsfile.close();
}
void WriteInFiles() {
	ofstream adminsfile, teamsfile, playersfile, usersfile, squadfile, userroundpointsfile, matchsfile, detailsfile, roundfile;

	adminsfile.open("Admins.txt");
	teamsfile.open("Teams.txt");
	playersfile.open("Players.txt");

	usersfile.open("Users.txt");
	squadfile.open("Squad.txt");
	userroundpointsfile.open("UserRoundPoints.txt");
	matchsfile.open("Matchs.txt");
	detailsfile.open("DetailsMatchs");
	roundfile.open("Rounds.txt");
	map<int, stack <Player*>> copydeka;
	for (auto i = admins.begin(); i != admins.end(); i++) {
		adminsfile << i->Id << endl;
		adminsfile << i->Name << endl;
		adminsfile << i->Password << endl;
	}
	for (int i = 1; i < 4; i++) {
		if (Leagues::leagues[i].rounds.size() != 0) {
			roundfile << i << ',';
			for (auto r : Leagues::leagues[i].rounds) {
				roundfile << r.first << ',';
			}
			roundfile << endl;
		}
		for (auto j = Leagues::leagues[i].teams.begin(); j != Leagues::leagues[i].teams.end(); j++) {
			teamsfile << j->second.LeagueId << ',' << j->second.TeamName << ',' << j->second.TeamId << endl;

		}
		for (auto p = Leagues::leagues[i].Players.begin(); p != Leagues::leagues[i].Players.end(); p++) {
			playersfile << p->second.TeamId << ',' << p->second.LeagueId << ',' << p->second.PlayerId << ',' << p->second.PlayerName << ',' << p->second.PlayerPosition << ',' << p->second.PlayerPrice << endl;
		}


		for (auto r = Leagues::leagues[i].rounds.begin(); r != Leagues::leagues[i].rounds.end(); r++) {

			for (auto m : r->second.matches) {
				matchsfile << i << '-' << r->first << '-';
				matchsfile << m.first << '-' << m.second.isPlayed << '-';
				detailsfile << i << ',' << r->first << ',';
				detailsfile << m.first << ',';
				matchsfile << m.second.team1->TeamId << '-' << m.second.res1 << '-';
				for (auto p : m.second.XI[m.second.team1->TeamId]) {
					matchsfile << p.first << ',';
				}
				for (auto d : m.second.pdla[m.second.team1->TeamId]) {
					matchsfile << d.first << ',';
				}

				matchsfile << '-' << m.second.team2->TeamId << '-' << m.second.res2 << '-';
				for (auto p : m.second.XI[m.second.team2->TeamId]) {
					matchsfile << p.first << ',';
				}
				for (auto d : m.second.pdla[m.second.team2->TeamId]) {
					matchsfile << d.first << ',';
				}
				matchsfile << '-' << endl;
				for (auto de : m.second.Details) {
					detailsfile << de.first << '>';
					for (auto dep : de.second) {
						detailsfile << dep.first << '-' << dep.second << '>';
					}
					detailsfile << ',';
				}
				detailsfile << endl;
			}

		}
	}
	for (auto i = users.begin(); i != users.end(); i++) {
		usersfile << i->Id << ',' << i->Name << ',' << i->Password << endl;

		for (auto j : i->squad) {
			if (!(j.second.squads.empty())) {
				squadfile << j.first << '-' << i->Id << '-';
				for (auto ps : j.second.squads) {
					if (ps.first == 0) {
						continue;
					}
					squadfile << ps.first << '-';
					copydeka[ps.first] = j.second.deka[ps.first];
					for (auto r : ps.second) {
						for (auto p : r.second) {
							squadfile << p->PlayerId << '-';
						}
					}



					while (!copydeka[ps.first].empty()) {
						squadfile << copydeka[ps.first].top()->PlayerId << ',';
						copydeka[ps.first].pop();
					}
					squadfile << '-';
					squadfile << j.second.TotalPoints << '-';
					squadfile << j.second.captain->PlayerId << '-';
					squadfile << j.second.ViceCaptain->PlayerId << '-';
					squadfile << j.second.tribleCaptain << '-';
					squadfile << j.second.wildCard << '-';
					squadfile << j.second.numOfSubestitution << '-';
					squadfile << j.second.Budget << endl;


				}

				/*for (auto r : users[i->Id].squad[j.first].RoundPoints) {
					userroundpointsfile << j.first << '-' << i->Id << '-' << r.first << '-' << r.second << endl;

				}*/
			}

		}

	}

	adminsfile.close();
	teamsfile.close();
	playersfile.close();
	usersfile.close();
	squadfile.close();
	userroundpointsfile.close();
	matchsfile.close();
	detailsfile.close();
	roundfile.close();
}