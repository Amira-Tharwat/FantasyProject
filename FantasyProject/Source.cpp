#include <iostream>
#include <list>
#include "Admin.cpp"
#include <vector>
#include "User.cpp"
using namespace std;
int Id_counter = 1000;
vector<Admin>admins;
vector<User>users;
void First_Page();
void SignUp() {
	User user;
	cout << "Enter your name\n";
	cin >> user.Name;
	cout << "Enter your password\n";
	cin >> user.Password;
	users.push_back(user);
	cout << "your account created\n";
	First_Page();
}
void SignIn( ) {
	int answer1;
	string name,password;
	bool iffound = 0;
	cout << "Enter your name\n";
	cin >> name;
	cout << "Enter your password\n";
	cin >> password;
	for (int i = 0; i < 7; i++) {
		if (admins[i].Name == name && admins[i].Password == password)
		{
			iffound = 1;
			cout << "welcome " << name << " in home admin";//function home admin   
			Admin::Home();
			break;
		}
	}
	if (iffound == 0) {
		for (int i = 0; i < users.size(); i++) {
			if (users[i].Name == name && users[i].Password == password) {
				iffound = 1;
				cout << "welcome " << name << " in home user";//function home user
				break;
			}
		}
	}
	if (iffound == 0) {
		cout << "the name or password is uncorrect.. \n1-try again\n2-back to home page\n";
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
		
	}
}


void First_Page() {
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
	
	// will be written in database
	Admin amira("amira", "2022170076",101);
	Admin simon("simon", "2022170201",102);
	Admin mariem("mariem", "2022170419",103);
	Admin menna("menna", "2022170445",104);
	Admin momen("momen", "2022170612",105);
	Admin minam("minam", "2022170459",106);
	Admin minaa("minaa", "2022170455",107);
	admins.push_back(amira);
	admins.push_back(simon);
	admins.push_back(mariem);
	admins.push_back(menna);
	admins.push_back(momen);
	admins.push_back(minam);
	admins.push_back(minaa);


	//-----------------------------------------------------
	First_Page();

}