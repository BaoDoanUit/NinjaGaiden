#include "Helpers/FileHelper.h"

#include <fstream>
#include <sstream>

using namespace std;

string FileHelper::ReadString(const std::string& filePath)
{
	ifstream file(filePath);

	stringstream buffer;

	buffer << file.rdbuf();

	string result = buffer.str();

	return result;
}