#include "Admin.h"
#include "User.h"
#include "Leagues.h"
#include <fstream>
#include <sstream>
using namespace std;
vector<Admin>admins;
vector<User>users;
void ReadFromFiles();
 void WriteInFiles();
int First_Page();
void SignIn() {
	int answer1;
	string name, password;
	bool iffound = false;
	cout << "Enter your name\n";
	cin >> name;
	cout << "Enter your password\n";
	cin >> password;
	for (int i = 0; i < 7; i++) {
		if (admins[i].Name == name && admins[i].Password == password)
		{
			iffound = true;
			cout << "welcome " << name << " in home admin"<<endl;//function home admin  
			if (Admin::SetLeagueId() == 0) {
				First_Page();
			}
			Admin::SetLeagueId();
			break;
		}
	}
	if (!iffound) {
		for (int i = 0; i < users.size(); i++) {
			if (users[i].Name == name && users[i].Password == password) {
				iffound = true;
				cout << "welcome " << name << " in home user";//function home user
				users[i].chooseLeague(users[i].Id);
				break;
			}
		}
	}
	if (!iffound) {
		cout << "the name or password is uncorrect.. \n1-try again\n2-back to home page\n";
		cin >> answer1;
		while (answer1 != 1 && answer1 != 2)
		{
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
		}


	}
}
void SignUp() {
	User user = User();
	cout << "Enter your name\n";
	cin >> user.Name;
	cout << "Enter your password\n";
	cin >> user.Password;
	users.push_back(user);
	cout << "your account created\n";
	First_Page();
}
int First_Page() {
	int answer;
	cout << "1-SignIn \n2-SignUp\n3-exit program";
	cin >> answer;
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
		break;
	}
	return 1;
}
int main() {

	
	ReadFromFiles();

	First_Page();
	WriteInFiles();
}
void ReadFromFiles() {
	ifstream adminsfile,teamsfile,playersfile,roundsfile,playerpointsfile,leaguesfile;
	leaguesfile.open("Leagues.txt");
	adminsfile.open("Admins.txt");
	teamsfile.open("Teams.txt");
	playersfile.open("Players.txt");
	roundsfile.open("Rounds.txt");
	playerpointsfile.open("Playerspoints.txt");
	for (int i = 1; i < 4; i++) {
		Leagues::leagues[i].LeagueId = i;
		leaguesfile >> Leagues::leagues[i].LaegueName;

	}
	for (int i = 0; i < 7; i++) {
		Admin admin;
		adminsfile>> admin.Id;
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
		Player player;
		vector<string> tokens;
		while (getline(iss, token, ',')) {

			tokens.push_back(token);

		}
		istringstream isss0(tokens[0]);
		isss0 >> player.TeamId;
		istringstream isss1(tokens[1]);
		isss1 >> player.LeagueId;
		istringstream isss2(tokens[2]);
		isss2 >> player.PlayerId;
		istringstream isss3(tokens[3]);
		isss3 >> player.PlayerName;
		istringstream isss4(tokens[4]);
		isss4 >> player.PlayerPosition;
		istringstream isss5(tokens[5]);
		isss5 >> player.PlayerPrice;
	
		
		
			Leagues::leagues[player.LeagueId].teams[player.TeamId].Players[player.PlayerId] = player;
			Leagues::leagues[player.LeagueId].Players[player.PlayerId] = player;
	}
	while (getline(roundsfile, line)) {
		istringstream iss(line);
		string token;
		Round round;
		vector<string> matchs;

		while (getline(iss, token, '-')) {
			
			matchs.push_back(token);

		}
		
		istringstream isss0(matchs[0]);
		isss0 >> round.leagueId;
		istringstream isss1(matchs[1]);
		isss1 >> round.roundId;
		for (int i = 2; i < matchs.size(); i++) {
			vector<string>mdata;
			string token2;
			Match match;
			istringstream issss(matchs[i]);
			while (getline(issss, token2, ',')) {
				mdata.push_back(token2);
			}
			istringstream isss0(mdata[0]);
			isss0 >> match.team1.TeamId;
			istringstream isss1(mdata[1]);
			isss1 >> match.team2.TeamId;
			istringstream isss2(mdata[2]);
			isss2 >> match.res1;
			istringstream isss3(mdata[3]);
			isss3 >> match.res2;
			match.team1 = Leagues::leagues[round.leagueId].teams.find(match.team1.TeamId)->second;
			match.team2 = Leagues::leagues[round.leagueId].teams.find(match.team2.TeamId)->second;
			round.matches.push(match);
		}

		Leagues::leagues[round.leagueId].rounds[round.roundId] = round;

		
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
		Leagues::leagues[player.LeagueId].teams[player.TeamId].Players[player.PlayerId].PointsInRounds[roundid]=points;
	}
	adminsfile.close();
	teamsfile.close();
	playersfile.close();
	roundsfile.close();
	playerpointsfile.close();
}
void WriteInFiles() {
	ofstream adminsfile,teamsfile,playersfile,roundsfile;
	
	adminsfile.open("Admins.txt");
	teamsfile.open("Teams.txt");
	playersfile.open("Players.txt");
	roundsfile.open("Rounds.txt");
	for (auto i = admins.begin(); i != admins.end();i++) {
		adminsfile << i->Id << endl;
		adminsfile << i->Name << endl;
		adminsfile << i->Password << endl;
	}
	for (int i = 1; i < 4; i++) {
		for (auto j = Leagues::leagues[i].teams.begin(); j != Leagues::leagues[i].teams.end(); j++) {
			teamsfile << j->second.LeagueId<<',' << j->second.TeamName << ',' << j->second.TeamId<<endl;
			
		}
		for (auto p = Leagues::leagues[i].Players.begin(); p != Leagues::leagues[i].Players.end(); p++) {
			playersfile << p->second.TeamId << ',' << p->second.LeagueId << ',' << p->second.PlayerId << ',' << p->second.PlayerName << ',' << p->second.PlayerPosition << ',' << p->second.PlayerPrice << endl;
		}
		
		
		for (auto r = Leagues::leagues[i].rounds.begin(); r != Leagues::leagues[i].rounds.end(); r++) {
			queue <Match> copyq = r->second.matches;
			roundsfile << i << "-";
			roundsfile << r->first<<"-";
			while (!(copyq.empty()))
			{
				roundsfile << copyq.front().team1.TeamId<<',';
				roundsfile << copyq.front().team2.TeamId<<',';
				roundsfile << copyq.front().res1<<',';
				roundsfile << copyq.front().res2<<'-';
				copyq.pop();
			}
			roundsfile << endl;
		}
	}
	adminsfile.close();
	teamsfile.close();
	playersfile.close();
	roundsfile.close();
}