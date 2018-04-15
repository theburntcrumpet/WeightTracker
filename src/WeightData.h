#include <sstream>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
using namespace std;


class WeightData{
private:
  string m_strWeightFile;
  vector<int> m_Weights;
private:
	void LbsToStLbs(int nTotalLbs, int * pSt, int * pLbs);
	bool StLbsToLbs(int nSt, int nLbs, int * pTotalLbs);
	string FormatWeight(string strMessage, int nSt, int nLbs);
public:
  bool ReadWeights();
	string GetRecordFormatted();
	string GetRecordFormatted(int nRecord);
	bool AddWeight(int nSt, int nLbs);
	bool RemoveRecord(int nRecord);
	static bool IsValidWeight(int nSt, int nLbs);
  WeightData(string strWeightFile);
  ~WeightData();
};
