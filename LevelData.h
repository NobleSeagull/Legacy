#ifndef _LEVELDATA_H
#define _LEVELDATA_H

#include <iostream>
#include <vector>

#include "Row.h"

class LevelData
{
public:
	LevelData() {
		for (int i = 0; i < 12; i++)
		{
			elements.push_back(Row());
		}
	};
	~LevelData() {};

	std::vector<Row> elements;
};
#endif