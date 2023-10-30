#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <fstream>
#include "nlohmann/json.hpp"

using json = nlohmann::json;

std::mutex mtx;
std::condition_variable cv;
bool game_over = false;
int team_size = 2;
int current_team = 1;
int current_player = 1;

void ping(int team_number, int player_number) {
    std::unique_lock<std::mutex> lock(mtx);
    cv.wait(lock, [team_number, player_number] {
        return current_team == team_number && current_player == player_number && !game_over;
        });

    std::cout << player_number << "/" << team_size << ", " << team_number << ": ping" << std::endl;

    current_team = (current_team == 1) ? 2 : 1;
    current_player = (current_player % team_size) + 1;
    cv.notify_all();
}

void pong(int team_number, int player_number) {
    std::unique_lock<std::mutex> lock(mtx);
    cv.wait(lock, [team_number, player_number] {
        return current_team == team_number && current_player == player_number && !game_over;
        });

    std::cout << player_number << "/" << team_size << ", " << team_number << ": pong" << std::endl;

    current_team = (current_team == 1) ? 2 : 1;
    current_player = (current_player % team_size) + 1;
    cv.notify_all();
}

void updateConfiguration(const std::string& config_file) {
    while (true) {
        std::this_thread::sleep_for(std::chrono::seconds(1));  // Simulate configuration update every second

        json config;
        {
            std::ifstream file(config_file);
            if (file.good()) {
                file >> config;
            }
        }

        if (config.contains("game_over") && config["game_over"].is_boolean()) {
            game_over = config["game_over"];
        }

        if (config.contains("team_size") && config["team_size"].is_number()) {
            team_size = config["team_size"];
        }
    }
}

int main() {
    std::thread configUpdater(updateConfiguration, "config.json");

    while (!game_over) {
        if (team_size <= 0) {
            std::this_thread::sleep_for(std::chrono::seconds(1));
            continue;
        }

        std::thread t1(team_size == 1 ? ping : ping, 1, 1);
        std::thread t2(pong, 2, 2);

        if (team_size == 2) {
            std::thread t3(ping, 2, 1);
            std::thread t4(pong, 1, 2);

            t3.join();
            t4.join();
        }

        t1.join();
        t2.join();
    }

    configUpdater.join();

    return 0;
}
