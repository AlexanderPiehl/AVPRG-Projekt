#include "BitToStringMap.h"
using namespace std;
BitToStringMap::BitToStringMap(){}

BitToStringMap::~BitToStringMap(){}

void BitToStringMap::setMap(int key, string value)
{
	binToStringMap[key]= value;
}
void BitToStringMap::clearMap(){
	binToStringMap.clear();
}

string BitToStringMap::convertBitToString(int key)
{
	if(binToStringMap.find(key) != binToStringMap.end())
	{
		string value;
		value = binToStringMap.at(key);
		return value;
	}
	else
	{
		return "";
	}
}
