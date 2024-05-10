#include "Validation.h"

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
				cout << "Invalid Number, Enter again:";
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
		cout << "Number is not within range, Enter again:";
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
		cout << " do not use spaces !" <<endl;
		check = 0;
	}
	else if (!((name[0] >= 'a' && name[0] <= 'z') || (name[0] >= 'A' && name[0] <= 'Z')))
	{
		cout << "can not uese special char or integer in the first"<<endl;
		check = 0;
	}
	else if(name.size() < 3)
	{
		cout << " minmum numeber of char is 3"<<endl;
		check = 0;
	}
	for (auto i : users)
	{
		if (name == i.Name) {
			cout << "this name already exist " << endl;
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
		
		getline(cin, pass);
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
			cout << " weak password !! at least 6 char and contan number and char and spical char " << endl;
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
			cout << " do not use spaces ! if you want add space add '_' " << endl;
			check = 0;
		}
		
		else if (name.size() < 3)
		{
			cout << " minmum numeber of char is 3" << endl;
			check = 0;
		}

		for (int i = 0; i < name.size(); i++)
		{
	     if (!((name[i] >= 'a' && name[i] <= 'z') || (name[i] >= 'A' && name[i] <= 'Z')||name[i]=='_'))
		 {
			cout << "can not uese special char or integer" << endl;
			check = 0;
		 }
		}
	} while (!check);

		return name;
}