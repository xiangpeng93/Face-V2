#pragma once
#include <json/json.h>
#include <algorithm> // sort
#include <sstream>

#include <Windows.h>
#include <iostream>

class CParseJson;

struct Options
{
	std::string path;
	Json::Features features;
	bool parseOnly;
	typedef std::string(CParseJson::*writeFuncType)(Json::Value const&);
	writeFuncType write;
};

class CParseJson
{
public:
	CParseJson();
	~CParseJson();
private:
	std::string readInputTestFile(const char* path);

	std::string useStyledWriter(
		Json::Value const& root);

	std::string useStyledStreamWriter(
		Json::Value const& root);

	std::string useBuiltStyledStreamWriter(
		Json::Value const& root);
	int printUsage(const char* argv[]);

	void printConfig();

	int parseCommandLine(
		int argc, const char* argv[], Options* opts);

	int parseAndSaveValueTree(const std::string& input,
		const std::string& actual,
		const std::string& kind,
		const Json::Features& features,
		bool parseOnly,
		Json::Value* root);
public:
	std::string CParseJson::parseString(const std::string& input,
		Json::Value* root,
		std::string type);
	int getJsonValue(const std::string& input,
		Json::Value* root);
};

