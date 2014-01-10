#include "UPCCodeScanner.h"

using namespace NUnit::Framework;
using namespace System;
[TestFixture]
public ref class UnitTestForMapConvert
{
	
	[Test]
	void TestUPCMap()
	{
		UPCCodeScanner scanner;
		std::string resultTmp;
		int testValues [12] = {1101,11001,10011,111101,100011,110001,101111,111011,110111,1011};
		for(int i = 0; i < 12; i++)
		{
			resultTmp += scanner.bitToStringMap.convertBitToString(testValues[i]);
		}
		String ^result = gcnew String(resultTmp.c_str());
		String^ exceptedResult = "0123456789";
		Assert::AreEqual(exceptedResult,result);
	}
};					
								 