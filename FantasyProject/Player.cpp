#include "Player.h"
static int CountPlayerId = 1;
Player::Player() {
	PlayerId = CountPlayerId;
	CountPlayerId++;
	PlayerPrice = 0;
}
Player::Player(int Id, string Name, string Position, int Price) {
	PlayerId = Id;
	PlayerName = Name;
	PlayerPosition = Position;
	PlayerPrice = Price;
}

