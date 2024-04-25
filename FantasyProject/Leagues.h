#pragma once
#include <iostream>
#include <map>
#include "League.h"
using namespace std;
class Leagues
{
public:
	static map<int, League> leagues;
public:
	Leagues();
};

