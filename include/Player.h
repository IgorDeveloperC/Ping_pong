#pragma once
#ifndef PLAYER_H
#define PLAYER_H

#include <thread>
#include <mutex>
#include <condition_variable>

class Player {
public:
    Player(int number, int team);
    void play();
    static std::mutex mtx;
    static std::condition_variable cv;
    static int current_Team;
    static int prev_Player;
    static int team_size;
private:
    int number_;
    int team_;
};

#endif