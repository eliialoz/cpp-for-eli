/*
File: line.cpp
Description:
Course: 150018 C++ Workshop, Exercise 1, Question 1
Author: Dan Zilberstein
Students: eli iluz 311201354
		& avishay farkash 205918790
*/


#include<iostream>
#include "line.h"
using namespace std;

Line lines[MAX_LINES];

bool lineAddBus(uint lineId, uint nuberOFline)
{
	if (lines[nuberOFline - 1].busesAmount < 5)
	{
		uint* temp = new uint[++lines[nuberOFline - 1].busesAmount];
		if (lines[nuberOFline - 1].busesAmount == 1)
		{
			temp[0] = lineId;
			lines[nuberOFline - 1].lineId = temp;
			temp = nullptr;
			return true;
		}
		uint i = 0;
		for (; ((i < lines[nuberOFline - 1].busesAmount - 1) && (lineId > lines[nuberOFline - 1].lineId[i])); i++)// Fine the right place for lineId
			temp[i] = lines[nuberOFline - 1].lineId[i];

		for (uint j = lines[nuberOFline - 1].busesAmount - 1; j >= 0 && lines[nuberOFline - 1].lineId[j - 1] > lineId; j--)
			temp[j] = lines[nuberOFline - 1].lineId[j - 1];

		temp[i] = lineId;
		lines[nuberOFline - 1].lineId = temp;
		temp = nullptr;
		return true;
	}
	return false;
}

bool lineDelBus(uint lineId, uint nuberOFline)
{
	bool isFound;
	int beg = 0, end = lines[nuberOFline - 1].busesAmount - 1, med = (beg + end) / 2;
	if (lines[nuberOFline - 1].busesAmount)
	{
		for (; (beg <= end) && (isFound = (lineId != lines[nuberOFline - 1].lineId[med])); med = (beg + end) / 2)//Binary search
			(lineId < lines[nuberOFline - 1].lineId[med]) ? end = med - 1 : beg = med + 1;

		if ((!isFound) && (--lines[nuberOFline - 1].busesAmount > 0))//Fine the right place for lineId
		{
			uint* temp = new uint[lines[nuberOFline - 1].busesAmount];
			for (uint i = 0, j = 0; i <= lines[nuberOFline - 1].busesAmount; i++)
				if (i != med)
					temp[j++] = lines[nuberOFline - 1].lineId[i];

			delete[]lines[nuberOFline - 1].lineId;
			lines[nuberOFline - 1].lineId = temp;
		}

		else if (!isFound)
			delete[]lines[nuberOFline - 1].lineId;
	}
	return false;
}

uint* lineGetBuses(uint nuberOFline)
{
	return lines[nuberOFline - 1].lineId;
}

uint lineGetAmount(uint amuontINline)
{
	return lines[amuontINline - 1].busesAmount;
}
//shalom