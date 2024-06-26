#include "Validation.h"
string Validation::password()
{
	string pass;
	int ch;
	ch = _getch(); //cin
	while (ch != 13) //13 = enter in ascii code
	{
		if (ch == 8) //8 = backspace in ascii code
		{

			if (!pass.empty())
			{
				pass.erase(pass.size() - 1);
				cout << "\b \b"; //to delete last index in password
			}
		}
		else {
			pass.push_back(ch);
			cout << "*";
		}
		ch = _getch();

	}
	return pass;
}
int Validation::ReadNumber()
{
	int number;
	bool b = true;
	string Number;
	do
	{

		b = true;
		
		getline(cin, Number);
		if (Number == "")
			b = false;
		for (int i = 0; i < Number.size(); i++) {
			if (!(Number[i] >= '0' && Number[i] <= '9'))
			{
				b = false;
				cout << "\033[31m Invalid Number, Enter again: \033[0m";
				break;
			}
		}	
	} while (!b);
	number = stoi(Number);
	
	return number;
}


bool Validation::IsNumberInRange(int Number, int From, int To)
{
	return (Number >= From && Number <= To);

}


int Validation::ReadNumberInRange(int From, int To)
{
	int Number = ReadNumber();

	while (!IsNumberInRange(Number, From, To))
	{
		cout << "\033[31m Number is not within range, Enter again: \033[0m";
		Number = ReadNumber();
	}
	return Number;
}

string Validation::username(vector<User>users)
{
	string name;
		bool check=1;
	do {
		 check = 1;
		 
		 getline(cin, name);
	if (name.find(' ')!= string::npos) {
		cout << "\033[33m do not use spaces ! \033[0m" <<endl;
		check = 0;
	}
	else if (!((name[0] >= 'a' && name[0] <= 'z') || (name[0] >= 'A' && name[0] <= 'Z')))
	{
		cout << "\033[31m can not use special char or integer in the first \033[0m"<<endl;
		check = 0;
	}
	else if(name.size() < 3)
	{
		cout << "\033[33m minmum numeber of char is 3\033[0m"<<endl;
		check = 0;
	}
	for (auto i : users)
	{
		if (name == i.Name) {
			cout << "\033[31m this name already exist \033[0m" << endl;
			check = 0;
		}
	}
	} while (!check);

	return name;
}
string Validation::pass()
{
	
	bool check ,  character ,spicalcharacter  ,integer ;
	string pass;
	do {
		check = 1;
		character = 0; spicalcharacter = 0; integer = 0;
		
		pass = Validation::password();
		for (int i = 0; i < pass.size();i++)
		{
			if (pass[i] >= '0' && pass[i] <= '9') {
				integer = 1; 
			}
			else if ((pass[i] >= '!' && pass[i] <= '/')|| (pass[i] >= ':' && pass[i] <= '@') || (pass[i] >= '(' && pass[i] <= '`') || (pass[i] >= '{' && pass[i] <= '~'))
			{
				spicalcharacter = 1;
			}
			else if (((pass[i] >= 'a' && pass[i] <= 'z') || (pass[i] >= 'A' && pass[i] <= 'Z')))
			{
				character = 1;
			}
		}
		
		if ( pass.size() < 6 || !( character && spicalcharacter && integer))
		{
			cout << "\033[33m weak password !! at least 6 char and contan number and char and spical char \033[0m" << endl;
			check = 0;
		}

	} while (!check);
	return pass;
}
 
string Validation::nameVal() {
	string name;
	bool check;
	do {
		check = 1;

		getline(cin, name);
		
		if (name.find(' ') != string::npos) {
			cout << "\033[33m do not use spaces ! if you want add space add '_' \033[0m" << endl;
			check = 0;
		}
		
		else if (name.size() < 3)
		{
			cout << "\033[33m minimum numeber of char is 3 , Try Again: \033[0m" << endl;
			check = 0;
			
		}
		else {
			for (int i = 0; i < name.size(); i++)
			{
				if (!((name[i] >= 'a' && name[i] <= 'z') || (name[i] >= 'A' && name[i] <= 'Z') || name[i] == '_'))
				{
					cout << "\033[31m can not use special char or integer , Try Again: \033[0m" << endl;
					check = 0;
					break;
				}
			}
		}
	} while (!check);
	return name;
}