#include "stdafx.h"
#include "JSONReader.h"

////////////////////////////////////////////////////////////
JSONReader::JSONReader(std::string const & filename)
{
	loadJSONData(filename);
	m_value = JSON::Parse(m_JSONData.c_str());
	if (NULL == m_value)
	{
		std::string s("Could not parse json in " + filename);
		throw std::exception(s.c_str());
	}
}

////////////////////////////////////////////////////////////
JSONReader::~JSONReader() {
	delete m_value;
}

////////////////////////////////////////////////////////////
void JSONReader::load(std::string const & filename)
{
	loadJSONData(filename);
	m_value = JSON::Parse(m_JSONData.c_str());
	if (NULL == m_value)
	{
		std::string s("Could not parse json in " + filename);
		throw std::exception(s.c_str());
	}

}

////////////////////////////////////////////////////////////
void JSONReader::loadJSONData(std::string const & filename)
{
	m_JSONData.clear();

	// Loads all the data in the file into a std::string.
	std::ifstream myfile(filename);
	std::string line;
	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			m_JSONData.append(line);
		}
		myfile.close();
	}
	else
	{
		std::string errorMessage = "Could not open " + filename + " exiting!";
		std::cout << "Could not open " + filename + " exiting!" << std::endl;
		throw std::exception(errorMessage.c_str());
	}
}

////////////////////////////////////////////////////////////
JSONObject JSONReader::getTopLevelJSONObject() {
	// Retrieve the main (root) object
	JSONObject root;

	if (m_value->IsObject() == false)
	{
		throw std::exception("Problem with root element in json file, exiting");
	}
	root = m_value->AsObject();

	return root;
}

////////////////////////////////////////////////////////////
std::string JSONReader::wStringToString(std::wstring const & wstr)
{
	std::string s(wstr.begin(), wstr.end());
	return s;
}


void JSONReader::loadLevel(int level)
{
	// Retrieve the main (root) object
	JSONObject root = getTopLevelJSONObject();
	std::string word0("Level" + std::to_string(level));
	std::wstring wWord0;
	wWord0.assign(word0.begin(), word0.end());
	JSONObject levelData = root[wWord0]->AsObject();
	for (int i = 0; i < 10; i++)
	{
		std::string word("Row" + std::to_string(i));
		std::wstring wWord;
		wWord.assign(word.begin(), word.end());
		JSONObject row = levelData[wWord]->AsObject();
		for (int j = 0; j < 12; j++)
		{
			std::string word2(std::to_string(j));
			std::wstring wWord2;
			wWord2.assign(word2.begin(), word2.end());
			m_levelData.elements.at(i).elements.at(j) =std::stoi(row[wWord2]->AsString());
			std::cout << " " << std::stoi(row[wWord2]->AsString());
		}
		std::cout << "" << std::endl;
	}
}
