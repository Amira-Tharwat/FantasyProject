#include "User.h"
int Id_Counter = 1;
User::User(void) 
{
	Id = Id_Counter;
	Budget = 80000;
	Id_Counter++;
}
User::User(string name, string password) {
	Name = name;
	Id = Id_Counter;
	Password = password;
	Budget = 80000;
	Id_Counter++;
}
