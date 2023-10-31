#include "Player.h"
#include <iostream>

std::mutex Player::mtx;
std::condition_variable Player::cv;
bool Player::isGameOver = false;
int Player::currentPlayerTeam1 = 0;
int Player::currentPlayerTeam2 = 0;
int Player::currentTeam = 1;
int Player::team_size = 2;

Player::Player(int number, int team) : number_(number), team_(team) {}

void Player::play() {
    while (!isGameOver)
    {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, [this]{ return team_ == currentTeam && number_ == (currentTeam == 1 ? currentPlayerTeam1 : currentPlayerTeam2); });
        std::cout << number_ + 1 << "/" << team_size << ", " << team_ << ": " << (team_ == 1 ? "ping" : "pong") << std::endl;
        switch (currentTeam) {
        case 1:
            currentPlayerTeam1 = (currentPlayerTeam1 + 1) % team_size;
            currentTeam = 2;
            break;
        case 2:
            currentPlayerTeam2 = (currentPlayerTeam2 + 1) % team_size;
            currentTeam = 1;
            break;
        }
        std::this_thread::sleep_for(std::chrono::seconds(1));
        cv.notify_all();
    }
}