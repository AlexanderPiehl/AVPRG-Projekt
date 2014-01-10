#ifndef BITTOSTRINGMAP_H_
#define BITTOSTRINGMAP_H_
#include <opencv2\opencv.hpp>
#include "OpenCV_Tools.h"


class BitToStringMap
{	
private:
	
protected:


public:
	BitToStringMap();
	~BitToStringMap(void);
	OpenCV_Tools cvTools;
	void setMap(int key, std::string value);
	void clearMap();
	std::string convertBitToString(int key);

	std::map<int,std::string> binToStringMap;
	std::string path;

};
#endif
