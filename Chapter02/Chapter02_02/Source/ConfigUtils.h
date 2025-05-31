#pragma once

#include <string>

#include <json/json.h>

Json::Value LoadConfigFile(const std::string& path);

void GetConfigValue(const Json::Value& root, const std::string& key, int& outValue);
void GetConfigValue(const Json::Value& root, const std::string& key, float& outValue);
void GetConfigValue(const Json::Value& root, const std::string& key, bool& outValue);
void GetConfigValue(const Json::Value& root, const std::string& key, std::string& outValue);