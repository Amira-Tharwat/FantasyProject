#include "Admin.h"

#include "Validation.h"
#include <string>

class Person
{
public:
	static vector<User> users;
	static vector<Admin> admins;
	static int First_Page();
	static void SignIn();
	static void SignUp();

};

