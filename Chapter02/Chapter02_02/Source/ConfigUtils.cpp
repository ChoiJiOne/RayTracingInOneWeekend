#include <fstream>

#include "ConfigUtils.h"

Json::Value LoadConfigFile(const std::string& path)
{
	std::ifstream configFileStream(path);
	if (!configFileStream.is_open())
	{
		std::ostringstream oss;
		oss << "FAILED_TO_LOAD_CONFIG(path: " << path << ")";
		throw std::runtime_error(oss.str());
	}

	Json::CharReaderBuilder builder;
	builder["collectComments"] = false;
	Json::Value root;
	std::string errs;

	if (!Json::parseFromStream(builder, configFileStream, &root, &errs))
	{
		std::ostringstream oss;
		oss << "JSON_PARSE_ERROR(path: " << path << ", errors: " << errs << ")";
		throw std::runtime_error(oss.str());
	}

	return root;
}

void GetConfigValue(const Json::Value& root, const std::string& key, int32_t& outValue)
{
	if (!root.isMember(key))
	{
		std::ostringstream oss;
		oss << "INVALID_CONFIG_KEY(key: " << key << ")";
		throw std::invalid_argument(oss.str());
	}

	if (!root[key].isInt())
	{
		std::ostringstream oss;
		oss << "INVALID_CONFIG_VALUE(key: " << key << ")";
		throw std::invalid_argument(oss.str());
	}

	outValue = root[key].asInt();
}

void GetConfigValue(const Json::Value& root, const std::string& key, float& outValue)
{
	if (!root.isMember(key))
	{
		std::ostringstream oss;
		oss << "INVALID_CONFIG_KEY(key: " << key << ")";
		throw std::invalid_argument(oss.str());
	}

	if (!root[key].isDouble())
	{
		std::ostringstream oss;
		oss << "INVALID_CONFIG_VALUE(key: " << key << ")";
		throw std::invalid_argument(oss.str());
	}

	outValue = root[key].asFloat();
}

void GetConfigValue(const Json::Value& root, const std::string& key, bool& outValue)
{
	if (!root.isMember(key))
	{
		std::ostringstream oss;
		oss << "INVALID_CONFIG_KEY(key: " << key << ")";
		throw std::invalid_argument(oss.str());
	}

	if (!root[key].isBool())
	{
		std::ostringstream oss;
		oss << "INVALID_CONFIG_VALUE(key: " << key << ")";
		throw std::invalid_argument(oss.str());
	}

	outValue = root[key].asBool();
}

void GetConfigValue(const Json::Value& root, const std::string& key, std::string& outValue)
{
	if (!root.isMember(key))
	{
		std::ostringstream oss;
		oss << "INVALID_CONFIG_KEY(key: " << key << ")";
		throw std::invalid_argument(oss.str());
	}

	if (!root[key].isString())
	{
		std::ostringstream oss;
		oss << "INVALID_CONFIG_VALUE(key: " << key << ")";
		throw std::invalid_argument(oss.str());
	}

	outValue = root[key].asString();
}
