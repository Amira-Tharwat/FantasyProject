#include "User.h"
class Validation {
public:

    static int ReadNumber();
	static bool IsNumberInRange(int Number, int From,int To);
    static int ReadNumberInRange(int From, int To);
	static string username(vector<User>);
	static string pass();
}; 


