#include "ConfigManager.h"
#include "Player.h"
#include <vector>

#include<iostream>
int main() {
    ConfigManager config("config.json");

    while (!config.isGameOver()) {
        config.refreshConfig();
        int teamSize = config.getTeamSize();
        if (teamSize <= 0) {
            std::this_thread::sleep_for(std::chrono::seconds(1));  // Wait for a second and check again
            continue;
        }

        std::vector<std::thread> players;
        for (int i = 0; i < teamSize; i++) {
            players.push_back(std::thread([i]() {
                Player(i+1, 1).play();               
                }));
            players.push_back(std::thread([i,teamSize]() {
                Player(teamSize-i, 2).play();
                }));
        }
        
        for (auto& player : players) {
                player.join();
        }
    }

    return 0;
}