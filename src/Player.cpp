#include "Player.h"
#include <iostream>

#include "ConfigManager.h"
ConfigManager config("config.json");
std::mutex Player::mtx;
std::condition_variable Player::cv;
int Player::current_Team = 2;
int Player::prev_Player = 1;
int Player::team_size = config.getTeamSize();

Player::Player(int number, int team) : number_(number), team_(team) {}

void Player::play() {
	std::unique_lock<std::mutex> lock(mtx);
	while (current_Team == team_) {
	/*	while (prev_Player + 1 != number_ && prev_Player != 1) {
			cv.wait(lock);
		}*/
		/*while (team_size - prev_Player + 1 != number_) {
			cv.wait(lock);
		}*/
		cv.wait(lock);
	}


	current_Team = team_;
	prev_Player = number_;
	std::cout << number_ << "/" << team_ << ": " << (team_ == 1 ? "ping" : "pong") << std::endl;
	team_size = config.getTeamSize();
	cv.notify_all();
}