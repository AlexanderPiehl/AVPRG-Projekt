#ifndef BITTORESULTMAP_H_
#define BITTORESULTMAP_H_
class BitToResultMap
{
public:
	BitToResultMap(void);
	~BitToResultMap(void);
	bool convertBinToSign(int key,int value);
	std::string test = "test";
	std::map<int,string> binToSignMap;
};

#endif