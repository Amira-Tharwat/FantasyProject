#include "User.h"
static int Id_Count = 1;
User::User(void)
{
	Id = Id_Count;
	Budget = 80000;
	Id_Count++;
}
User::User(string name, string password) {
	Id = Id_Count;
	Budget = 80000;
	Id_Count++;
	Name = name;
	Password = password;
}