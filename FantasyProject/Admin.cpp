#include "Admin.h"
Admin::Admin(void){}
Admin::Admin(string name, string password,int id)
{
	Name = name;
	Password = password;
	Id = id;
}
void Admin::Home()
{
	cout << "Please Enter\n";
	cout << "1- Add Team\n";
	cout << "2- Remove Team\n";
	cout << "3- Add Player\n";
	cout << "4- Remove Player\n";
	cout << "5- Add Round\n";
	cout << "6- End Round\n";
	cout << "7- View All users\n";
	
	 
	int answer;
	cin >> answer;
	switch (answer)
	{
	case 1:
		// Call Add team 
		break;

	case 2:
		//Call Remove team
		break;

	case 3:
		// Call Add Player 
		break;

	case 4:
		//Call Remove Player
		break;

	case 5:
		// Call Add Round
		break;
	case 6:
		//Call End Round
		break;
	case 7:
		//Call  View All users
		break;
	}
		

}

