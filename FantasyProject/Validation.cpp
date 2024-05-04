
#include "Validation.h"
#include <string>
int Validation::ReadNumber()
{
	int Number;
	while (!(cin >> Number)) {
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Invalid Number, Enter again:";
	}
	return Number;
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
		cout << "Number is not within range, Enter again:";
		Number = ReadNumber();
	}
	return Number;
}

string Validation::username()
{
	string name;
		bool check=1;
	do {
		 check = 1;
		 cin.ignore();
		 getline(cin, name);
	if (name.find(' ')!= string::npos) {
		cout << " do not use spaces !" <<endl;
		check = 0;
	}
	else if (!((name[0] >= 'a' && name[0] <= 'z') || (name[0] >= 'A' && name[0] <= 'Z')))
	{
		cout << "can not uese special char or integer"<<endl;
		check = 0;
	}
	else if(name.size() < 3)
	{
		cout << " minmum numeber of char is 3"<<endl;
		check = 0;
	}
	/*for (auto i : users)
	{
		if (name == i.Name) {
			cout << "this name already exist " << endl;
			check = 0;
		}
	}*/
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
		cin.ignore();
		getline(cin, pass);
		for (int i = 0; i < pass.size();i++)
		{
			if (pass[i] >= '0' && pass[i] <= '9') { integer = 1; }
			else if ((pass[i] >= '!' && pass[i] <= '/')|| (pass[i] >= ':' && pass[i] <= '@') || (pass[i] >= '(' && pass[i] <= '`') || (pass[i] >= '{' && pass[i] <= '~'))
			{
				spicalcharacter = 1;
			}
			else if (((pass[0] >= 'a' && pass[0] <= 'z') || (pass[0] >= 'A' && pass[0] <= 'Z')))
			{
				character = 1;
			}
		}
		
		if ( pass.size() < 6 || !( character && spicalcharacter && integer))
		{
			cout << " weak password !! at least 6 char and contan number and char and spical char " << endl;
			check = 0;
		}

	} while (!check);
	return pass;
}
 

