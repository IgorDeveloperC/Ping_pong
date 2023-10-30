#include "ConfigManager.h"
#include <fstream>

ConfigManager::ConfigManager(const std::string& filepath) : filepath_(filepath) {
    refreshConfig();
}

void ConfigManager::refreshConfig() {
    std::ifstream file(filepath_);
    file >> config_;
}

int ConfigManager::getTeamSize() const {
    return config_.value("team_size", 0);
}

bool ConfigManager::isGameOver() const {
    return config_.value("game_over", true);
}