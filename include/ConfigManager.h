#pragma once
#ifndef CONFIG_MANAGER_H
#define CONFIG_MANAGER_H

#include <string>
#include "nlohmann/json.hpp"

class ConfigManager {
public:
    ConfigManager(const std::string& filepath);
    void refreshConfig();

    int getTeamSize() const;
    bool isGameOver() const;

private:
    std::string filepath_;
    nlohmann::json config_;
};

#endif