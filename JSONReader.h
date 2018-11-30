#ifndef _JSONREADER_H
#define _JSONREADER_H

#include "JSON.h"
#include "LevelData.h"
#include <fstream>
#include <iostream>

////////////////////////////////////////////////////////////
/// \brief A class to load all the configuration data
///        required by the game. 
///
////////////////////////////////////////////////////////////

class JSONReader {
public:

	JSONReader(std::string const & filename);
	~JSONReader();

	void load(std::string const & filename);
	void loadLevel(int level);
	LevelData Level(){ return m_levelData; };

private:
	JSONValue *m_value;
	std::string m_JSONData;

	void loadJSONData(std::string const & filename);

	LevelData m_levelData;

	// Utility methods.
	JSONObject getTopLevelJSONObject();
	std::string wStringToString(std::wstring const & wstr);
};
#endif