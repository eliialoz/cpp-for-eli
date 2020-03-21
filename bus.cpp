/*
File: bus.cpp
Description:
Course: 150018 C++ Workshop, Exercise 1, Question 1
Author: Dan Zilberstein
Students: eli iluz 311201354
		& avishay farkash 205918790
*/

#include <iostream>
#include "bus.h"
#pragma warning (disable:4996)
using namespace std;

// Global variables
Bus** buses = nullptr;
uint busFleetCount = 0;

uint* getBusList()
{
	uint* busList = new uint[busFleetCount];
	for (int i = 0; i < busFleetCount; i++)
		busList[i] = buses[i]->_busId;

	return busList;
}

bool checkBus(uint id)
{
	return (getBus(id));
}

Bus* getBus(int id)
{
	if (busFleetCount)
	{
		uint* busList = getBusList();
		bool isFound = true;
		int beg = 0, end = busFleetCount - 1, med = (beg + end) / 2;

		for (; (beg <= end) && (isFound = (id != busList[med])); med = (beg + end) / 2)//Binary search
			(id < busList[med]) ? end = med - 1 : beg = med + 1;

		delete[] busList;
		if (!isFound)
			return buses[med];
		else
			return nullptr;
	}
	return nullptr;
}

void busDtor(const Bus* dBus)
{
	delete[] dBus->_busDriver;
	delete dBus;

}

bool delBus(int id)
{
	Bus* dBus = getBus(id);

	if (dBus && !dBus->_busLine)
	{
		Bus** temp = new Bus * [--busFleetCount];

		for (int i = 0, j = 0; i < busFleetCount + 1; i++)
			if (buses[i] != dBus)
				temp[j++] = buses[i];

		busDtor(dBus);
		buses = temp;

		return true;
	}
	return false;
}

// Adds a bus to the fleet
bool addBus(const Bus& bus)
{
	if (!checkBus(bus._busId))
	{
		Bus** temp = new Bus * [++busFleetCount];
		bool isInsert = false;

		for (int i = 0, j = 0; i < busFleetCount; i++)
			if ((!isInsert) && ((i == busFleetCount - 1) || (isInsert = bus._busId < buses[i]->_busId)))
				temp[i] = const_cast<Bus*>(&bus);
			else
				temp[i] = buses[j++];

		buses = temp;

		return true;
	}
	return false;
}

Bus* busCtor(int id, int seats)
{
	Bus* bus = nullptr;
	if ((id <= MAX_ID && id > 0) && (seats <= MAX_SEATS && seats > 7))
	{
		bus = new Bus;
		bus->_busId = id;
		bus->_busSеаts = seats;

		if (!addBus(*bus))
			bus = nullptr;
	}
	return bus;
}

void busFleetDtor()
{
	for (int i = 0; i < busFleetCount; i++)
		busDtor(buses[i]);
	for (int i = 1; i <= MAX_LINES; i++)
		delete[] lineGetBuses(i);
	delete[] buses;
	buses = nullptr;
}

void busPrint(const Bus& bus)
{
	cout << "Bus id: " << bus._busId << endl << "Bus seats: " << bus._busSеаts << endl;
	(busLine(bus)) ? cout << "Bus line: " << busLine(bus) << endl : cout << "No line is assigned" << endl;
	(busDriver(bus)) ? cout << "Bus driver: " << busDriver(bus) << endl : cout << "No Driver is assigned" << endl;

}

void busesPrint()
{
	for (int i = 0; i < busFleetCount; i++)
	{
		busPrint(*buses[i]);
		cout << endl;
	}
}

bool busDriver(Bus& bus, const cstring dName)
{
	if (dName && dName != "")
	{
		delete[] bus._busDriver;
		bus._busDriver = new char[strlen(dName) + 1];
		strcpy(bus._busDriver, dName);

		return true;
	}
	return false;
}

cstring busDriver(const Bus& bus)
{
	return bus._busDriver;
}

bool busLine(Bus& bus, int line)
{
	if (line > -1 && line < MAX_LINE)
	{
		if (line && bus._busLine != line && lineAddBus(bus._busId, line))
		{
			if (bus._busLine)
				lineDelBus(bus._busId, bus._busLine);
			bus._busLine = line;

			return true;
		}
		else if (!line && bus._busLine)
		{
			lineDelBus(bus._busId, bus._busLine);
			bus._busLine = line;
			return true;
		}
		return false;
	}
	return false;
}

int busLine(const Bus& bus)
{
	return bus._busLine;
}