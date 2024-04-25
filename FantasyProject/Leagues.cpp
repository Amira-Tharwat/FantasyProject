#include "Leagues.h"
Leagues::Leagues() {
	League league1 = League(1, "premier league");
	leagues[1] = league1;
	League league2 = League(2, "La Liga");
	leagues[2] = league2;
	League league3 = League(3, "Serie A");
	leagues[3] = league3;

}
