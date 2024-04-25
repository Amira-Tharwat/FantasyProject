#include "User.h"

int Id_Count = 1;
User::User(void) 
{
	Id = Id_Count;
	Budget = 80000;
	Id_Count++;
}
User::User(string name, string password) {
	Name = name;
	Id = Id_Count;
	Password = password;
	Budget = 80000;
	Id_Count++;
}
