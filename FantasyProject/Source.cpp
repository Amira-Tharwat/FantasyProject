#include "Admin.h"
#include "User.h"
#include "Leagues.h"
#include <fstream>
#include <sstream>
#include "Validation.h"
using namespace std;
vector<Admin>admins;
vector<User>users;
Validation v;
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
			cout << "welcome " << name << " in home admin" << endl;//function home admin  
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
				cout << "welcome " << name << " in home user" << endl;//function home user
				users[i].chooseLeague(users[i].Id);
				break;
			}
		}
	}
	if (!iffound) {
		
		cout << "the name or password is uncorrect.. \n";
		do{
			cout<<"1-try again\n2-back to home page\n";
			cin >> answer1;		
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
	answer = v.ReadNumberInRange(1, 3);
		
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
	
	return 1;
}
int main() {

	
	ReadFromFiles();
	First_Page();
	WriteInFiles();
}
void ReadFromFiles() {
	ifstream adminsfile,teamsfile,playersfile,roundsfile,playerpointsfile,leaguesfile,usersfile,squadfile,userroundpointsfile;
	leaguesfile.open("Leagues.txt");
	adminsfile.open("Admins.txt");
	usersfile.open("Users.txt");
	teamsfile.open("Teams.txt");
	playersfile.open("Players.txt");
	roundsfile.open("Rounds.txt");
	playerpointsfile.open("Playerspoints.txt");
	squadfile.open("Squad.txt");
	userroundpointsfile.open("UserRoundPoints.txt");
	
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
		istringstream isss3(tokens[3]);
		isss3 >> user.Budget;
		users.push_back(user);

	}
	while (getline(squadfile, line)) {
		istringstream iss(line);
		string token;
		vector<string> tokens;
		int leagueid;
		int userid;
		Squad squad;
		while (getline(iss, token, '-')) {

			tokens.push_back(token);

		}
		
		istringstream isss0(tokens[0]);
		isss0 >> leagueid;
		istringstream isss1(tokens[1]);
		isss1 >> userid;
		for (int i = 2; i <= 16; i++) {
			int PlayerId;
			istringstream isss2(tokens[i]);
			isss2 >> PlayerId;
			users[userid].squad[leagueid].squads[Leagues::leagues[leagueid].Players[PlayerId].PlayerPosition].push_back(Leagues::leagues[leagueid].Players[PlayerId]);
		}
		
		
		for (int i = 17; i <= 20; i++) {
			int playerid;
			istringstream isss3(tokens[i]);
			isss3 >>playerid;
			users[userid].squad[leagueid].deka.push(Leagues::leagues[leagueid].Players[playerid]);
		}
		istringstream isss4(tokens[21]);
		isss4 >> users[userid].squad[leagueid].TotalPoints;
		int playerid;
		istringstream isss5(tokens[22]);
		isss5 >> playerid;
		users[userid].squad[leagueid].captain = Leagues::leagues[leagueid].Players[playerid];
		istringstream isss6(tokens[23]);
		isss6 >> playerid;
		users[userid].squad[leagueid].ViceCaptain = Leagues::leagues[leagueid].Players[playerid];
		istringstream isss7(tokens[24]);
		isss7 >> users[userid].squad[leagueid].tribleCaptain ;
		istringstream isss8(tokens[25]);
		isss8 >> users[userid].squad[leagueid].wildCard;
		istringstream isss9(tokens[26]);
		isss9 >> users[userid].squad[leagueid].numOfSubestitution;
	}
	while (getline(userroundpointsfile, line)) {
		istringstream iss(line);
		string token;
		vector<string> tokens;
		while (getline(iss, token, '-')) {

			tokens.push_back(token);

		}
		int leagueid, userid,roundid,points;
		istringstream isss0(tokens[0]);
		isss0 >> leagueid;
		istringstream isss1(tokens[1]);
		isss1 >> userid;
		istringstream isss2(tokens[2]);
		isss1 >> roundid;
		istringstream isss3(tokens[3]);
		isss3 >> points;
		users[userid].squad[leagueid].RoundPoints[roundid] = points;
	}
	adminsfile.close();
	teamsfile.close();
	playersfile.close();
	roundsfile.close();
	playerpointsfile.close();
	usersfile.close();
	squadfile.close();
	userroundpointsfile.close();
}
void WriteInFiles() {
	ofstream adminsfile,teamsfile,playersfile,roundsfile,usersfile,squadfile,userroundpointsfile;
	
	adminsfile.open("Admins.txt");
	teamsfile.open("Teams.txt");
	playersfile.open("Players.txt");
	roundsfile.open("Rounds.txt");
	usersfile.open("Users.txt");
	squadfile.open("Squad.txt");
	userroundpointsfile.open("UserRoundPoints.txt");
	stack <Player> copydeka;
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
	for (auto i = users.begin(); i != users.end(); i++) {
		usersfile << i->Id << ',' << i->Name << ',' << i->Password << ',' << i->Budget<<endl;
		for (auto j : i->squad) {
			squadfile << j.first<<'-'<<i->Id<<'-';
			for (auto ps : j.second.squads) {
				for (auto p : ps.second) {
					squadfile << p.PlayerId << '-';
				}
			}
			copydeka = j.second.deka;
			while (!copydeka.empty()){
				squadfile << copydeka.top().PlayerId<<'-';
			    copydeka.pop();
			}
			squadfile << j.second.TotalPoints;
			squadfile << j.second.captain.PlayerId;
			squadfile << j.second.ViceCaptain.PlayerId;
			squadfile << j.second.tribleCaptain;
			squadfile << j.second.wildCard;
			squadfile << j.second.numOfSubestitution;
			
			for (auto r : users[i->Id].squad[j.first].RoundPoints) {
				userroundpointsfile << j.first << '-' << i->Id << '-'<<r.first<<'-'<<r.second<<endl;

			}
		}
		
	}

	adminsfile.close();
	teamsfile.close();
	playersfile.close();
	roundsfile.close();
	usersfile.close();
	squadfile.close();
	userroundpointsfile.close();
}