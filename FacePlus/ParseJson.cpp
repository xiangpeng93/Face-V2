#include "ParseJson.h"


CParseJson::CParseJson()
{
}


CParseJson::~CParseJson()
{
}


std::string CParseJson::readInputTestFile(const char* path) {
	FILE* file = fopen(path, "rb");
	if (!file)
		return std::string("");
	fseek(file, 0, SEEK_END);
	long size = ftell(file);
	fseek(file, 0, SEEK_SET);
	std::string text;
	char* buffer = new char[size + 1];
	buffer[size] = 0;
	if (fread(buffer, 1, size, file) == (unsigned long)size)
		text = buffer;
	fclose(file);
	delete[] buffer;
	return text;
}

std::string CParseJson::useStyledWriter(
	Json::Value const& root)
{
	Json::StyledWriter writer;
	return writer.write(root);
}
std::string CParseJson::useStyledStreamWriter(
	Json::Value const& root)
{
	Json::StyledStreamWriter writer;
	std::ostringstream sout;
	writer.write(sout, root);
	return sout.str();
}
std::string CParseJson::useBuiltStyledStreamWriter(
	Json::Value const& root)
{
	Json::StreamWriterBuilder builder;
	return Json::writeString(builder, root);
}
int CParseJson::printUsage(const char* argv[]) {
	printf("Usage: %s [--strict] input-json-file", argv[0]);
	return 3;
}

void CParseJson::printConfig() {
	// Print the configuration used to compile JsonCpp
#if defined(JSON_NO_INT64)
	printf("JSON_NO_INT64=1\n");
#else
	printf("JSON_NO_INT64=0\n");
#endif
}
int CParseJson::parseCommandLine(
	int argc, const char* argv[], Options* opts)
{
	opts->parseOnly = false;
	opts->write = &CParseJson::useStyledWriter;
	if (argc < 2) {
		return printUsage(argv);
	}
	int index = 1;
	if (std::string(argv[index]) == "--json-checker") {
		opts->features = Json::Features::strictMode();
		opts->parseOnly = true;
		++index;
	}
	if (std::string(argv[index]) == "--json-config") {
		printConfig();
		return 3;
	}
	if (std::string(argv[index]) == "--json-writer") {
		++index;
		std::string const writerName(argv[index++]);
		if (writerName == "StyledWriter") {
			opts->write = &CParseJson::useStyledWriter;
		}
		else if (writerName == "StyledStreamWriter") {
			opts->write = &CParseJson::useStyledStreamWriter;
		}
		else if (writerName == "BuiltStyledStreamWriter") {
			opts->write = &CParseJson::useBuiltStyledStreamWriter;
		}
		else {
			printf("Unknown '--json-writer %s'\n", writerName.c_str());
			return 4;
		}
	}
	if (index == argc || index + 1 < argc) {
		return printUsage(argv);
	}
	opts->path = argv[index];
	return 0;
}

int CParseJson::parseAndSaveValueTree(const std::string& input,
	const std::string& actual,
	const std::string& kind,
	const Json::Features& features,
	bool parseOnly,
	Json::Value* root)
{
	Json::Reader reader(features);
	bool parsingSuccessful = reader.parse(input, *root);
	if (!parsingSuccessful) {
		printf("Failed to parse %s file: \n%s\n",
			kind.c_str(),
			reader.getFormattedErrorMessages().c_str());
		return 1;
	}
	if (!parseOnly) {
		FILE* factual = fopen(actual.c_str(), "wt");
		if (!factual) {
			printf("Failed to create %s actual file.\n", kind.c_str());
			return 2;
		}
		fclose(factual);
	}
	std::string upload_id = (*root)["face"][0]["face_id"].asString();  // 访问节点，upload_id = "UP000000" 
	return 0;
}

std::string CParseJson::parseString(const std::string& input,
	Json::Value* root,
	std::string type)
{
	Json::Features features;
	Json::Reader reader(features);
	bool parsingSuccessful = reader.parse(input, *root);
	if (!root) {
		printf("Failed to parse file: \n%s\n",
			reader.getFormattedErrorMessages().c_str());
		return "";
	}

	return (*root)["face"][0]["face_id"].asString();  // 访问节点，upload_id = "UP000000" 
}

int CParseJson::getJsonValue(const std::string& input,
	Json::Value* root)
{
	Json::Features features;
	Json::Reader reader(features);
	bool parsingSuccessful = reader.parse(input, *root);
	if (!root) {
		printf("Failed to parse file: \n%s\n",
			reader.getFormattedErrorMessages().c_str());
		return -1;
	}

	return 0;  // 访问节点，upload_id = "UP000000" 
}