#ifndef _ROW_H
#define _ROW_H

#include <iostream>
#include <vector>

class Row
{
public:
	Row() {
		for (int i = 0; i < 12; i++)
		{
			elements.push_back(0);
		}
	};
	~Row() {};

	std::vector<int> elements;

};
#endif