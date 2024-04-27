#include<vector>
#include "Admin.h"
#include "User.h"
#include "Leagues.h"
using namespace std;
vector<Admin>admins;
vector<User>users;
void SignIn() {
	int answer1;
	string name, password;
	bool iffound = false;
	cout << "Enter your name\n";
	cin >> name;
	cout << "Enter your password\n";
	cin >> password;
	for (int i = 1; i <= 7; i++) {
		if (admins[i].Name == name && admins[i].Password == password)
		{
			iffound = true;
			cout << "welcome " << name << " in home admin";//function home admin   
			Admin::SetLeagueId();
			break;
		}
	}
	if (!iffound) {
		for (int i = 0; i < users.size(); i++) {
			if (users[i].Name == name && users[i].Password == password) {
				iffound = true;
				cout << "welcome " << name << " in home user";//function home user
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
				/*F();*/
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
	/*F();*/
}
void F() {
	int answer;
	cout << "1-SignIn \n2-SignUp\n";
	cin >> answer;
	switch (answer)
	{
	case 1:
		SignIn();
		break;
	case 2:
		SignUp();
		break;

	default:
		break;
	}
}
int main() {

	Admin amira(101, "amira", "2022170076");
	Admin simon(102, "simon", "2022170201");
	Admin mariem(103, "mariem", "2022170419");
	Admin menna(104, "menna", "2022170445");
	Admin momen(105, "momen", "2022170612");
	Admin minam(106, "minam", "2022170459");
	Admin minaa(107, "minaa", "2022170455");
	admins.push_back(amira);
	admins.push_back(simon);
	admins.push_back(mariem);
	admins.push_back(menna);
	admins.push_back(momen);
	admins.push_back(minam);
	admins.push_back(minaa);
	F();

}