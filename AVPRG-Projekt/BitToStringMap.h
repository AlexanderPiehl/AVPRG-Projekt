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

	std::map<int,std::string> binToIntMap;
	std::string path;

};
#endif
