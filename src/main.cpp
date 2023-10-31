#include "ConfigManager.h"
#include "Player.h"
#include <vector>

#include <iostream>
int main()
{
    ConfigManager config("config.json");
    int teamSize = config.getTeamSize();
    int maxTeamSize = teamSize;

    std::vector<std::thread> players;

    // Function to initialize additional player threads
    auto initPlayers = [&](int from, int count) {
        for (int i = from; i < from + count; i++) {
            players.push_back(std::thread([i](){
                Player(i, 1).play();
            }));
            players.push_back(std::thread([i](){
                Player(i, 2).play();
            }));
        }
    };

    initPlayers(0, teamSize);

    while (!config.isGameOver()) {
        std::this_thread::sleep_for(std::chrono::seconds(5));
        config.refreshConfig();
        teamSize = config.getTeamSize();
        if (teamSize > maxTeamSize) {
            // initialize additional players if needed
            int delta = teamSize - maxTeamSize;
            initPlayers(maxTeamSize, delta);
            maxTeamSize = teamSize;
        }
        Player::team_size = teamSize;
    }

    Player::isGameOver = true;

    // Wait for player threads to finish
    for (auto &player : players) {
        player.join();
    }

    std::cout << "Game over!" << std::endl;

    return 0;
}