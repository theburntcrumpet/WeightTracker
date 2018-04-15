#include "WeightData.h"

bool CreateFileIfNotExists(string strFile){
  FILE * pFile;
  pFile = fopen(strFile.c_str(),"r");
  if(pFile==NULL){
    pFile = fopen(strFile.c_str(),"w");
    if(!pFile)
      return false;
    fputs("",pFile);
    fclose(pFile);
  }else{
    return true;
  }
  return true;
}


WeightData::WeightData(string strWeightFile){
  m_strWeightFile = strWeightFile;
}

WeightData::~WeightData(){

}

void WeightData::LbsToStLbs(int nTotalLbs, int * pSt, int * pLbs){
	*pSt = (int)((float)nTotalLbs / 14);
	*pLbs = nTotalLbs % 14;
}

 bool WeightData::StLbsToLbs(int nSt, int nLbs, int * pTotalLbs){
	if(!IsValidWeight(nSt,nLbs))
	 	return false;
	*pTotalLbs = (nSt * 14) + nLbs;
	return true;
 }

string WeightData::FormatWeight(string strMessage, int nSt, int nLbs){
	ostringstream streamFormattedWeight;
	streamFormattedWeight << strMessage
	<< nSt << " St "
	<< nLbs << " Lbs";
	return streamFormattedWeight.str();
}

bool WeightData::ReadWeights(){
	// Check if the file exists and make it if not
  if(!CreateFileIfNotExists(m_strWeightFile)){
    cout << "Write failed. Ensure you have write permissions" << endl;
    return false;
  }

  ifstream fWeights(m_strWeightFile);

	// If we have permission to read the file, it should currently be open
	if(!fWeights.is_open()){
    cout << "Read Failed. Ensure you have read permissions" << endl;
    return false;
  }

	// Until we see the end of the file, get the next line, and put it into an int if possible
  while(!fWeights.eof()){
    string strLine;
		int nLbs;
    getline(fWeights,strLine);
		try{
			nLbs = stoi(strLine);
			m_Weights.push_back(nLbs);
		} catch (exception e){
		}
  }

  return true;
}

string WeightData::GetRecordFormatted(){
	return GetRecordFormatted(m_Weights.size());
}

string WeightData::GetRecordFormatted(int nRecord){
	if(m_Weights.size() == 0){
		return "No weight data stored yet. See usage for how to store";
	}
	if(nRecord == 0)
		return "You must request a record above 0!";

	if(nRecord > m_Weights.size())
		return "You have requested a record greater than the total number of records";

  int nSt, nLbs, nLoss;
	LbsToStLbs(m_Weights.front(),&nSt,&nLbs);
  ostringstream streamFormattedWeight;
	streamFormattedWeight << FormatWeight("First Recorded Weight: ", nSt, nLbs) << endl;
	if(m_Weights.size() == 1){
		streamFormattedWeight << "This is the only recorded weight";
		return streamFormattedWeight.str();
	}
	LbsToStLbs(m_Weights[nRecord-1],&nSt,&nLbs);
	streamFormattedWeight << FormatWeight("Requested Weight: ", nSt, nLbs) << endl;
	nLoss = m_Weights.front() - m_Weights[nRecord-1];
	LbsToStLbs(nLoss,&nSt,&nLbs);
	streamFormattedWeight << FormatWeight("Loss Since First Record: ", nSt, nLbs) << endl;
	streamFormattedWeight << endl << "There are " << m_Weights.size() << " records stored";
	return streamFormattedWeight.str();
}

bool WeightData::AddWeight(int nSt, int nLbs){
	int nTotalLbs;
	if(!StLbsToLbs(nSt,nLbs,&nTotalLbs))
		return false;
	ofstream dFile;
	dFile.open(m_strWeightFile,ios_base::app);
	if(!dFile.is_open())
		return false;
	dFile << nTotalLbs << endl;
	return true;
}

bool WeightData::RemoveRecord(int nRecord){
	if(nRecord < 1 || nRecord > m_Weights.size())
		return false;
	m_Weights.erase(m_Weights.begin() + (nRecord - 1));
	ofstream fWeights(m_strWeightFile);
	if(!fWeights.is_open())
		return false;
	for(vector<int>::iterator it = m_Weights.begin(); it != m_Weights.end(); it++){
		fWeights << *it << endl;
	}
	return true;
}

bool WeightData::IsValidWeight(int nSt, int nLbs){
	return nSt > 0 && nLbs >= 0 && nLbs < 14;
}
