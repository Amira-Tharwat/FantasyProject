#include "Person.h"
int Person::First_Page(){
	int answer;
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
			return 0;
		default:
			cout << "Invaled choose" << endl;
		}
		return 0;
}
void Person::SignIn() {
	int answer1;
	string name, password;
	bool iffound = false;
	cout << "Enter your name\n";
	getline(cin, name);

	cout << "Enter your password\n";

	getline(cin, password);

	for (int i = 0; i < 1; i++) {
		if (Person::admins[i].Name == name && Person::admins[i].Password == password)
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
			if (Person::users[i].Name == name && Person::users[i].Password == password) {
				iffound = true;
				cout << "welcome " << name << " in home user" << endl;//function home user
				Person::users[i].GetUsers(users);
				Person::users[i].chooseLeague(users[i].Id);
				break;
			}
		}
	}
	if (!iffound) {

		cout << "the name or password is uncorrect.. \n";
		do {
			cout << "1-try again\n2-back to home page\n";
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
void Person::SignUp() {
	User user = User();
	cout << "Enter your name\n";
	user.Name = Validation::username(users);
	cout << "Enter your password\n";
	user.Password = Validation::pass();
	Person::users.push_back(user);
	cout << "your account created\n";
	First_Page();
}
