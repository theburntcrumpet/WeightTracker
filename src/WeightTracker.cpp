#include <iostream>
#include "WeightData.h"
using namespace std;

int Usage(){
  cout
  << "Usage:" << endl
  << "\tWeightTracker add 10 12\tRecord a new record (10st 12lbs)" << endl
  << "\tWeightTracker rem 10   \tRemoves 10th record" << endl
  << "\tWeightTracker rec 10   \tShows 10th record" << endl
  << "\tWeightTracker rec      \tShows current stats" << endl;
  return 0;
}

int main(int argc, char ** argv){
  if(argc < 2)
    return Usage();

  // Create an instance of WeightData to interface with the file which holds the weights
  WeightData weigh("Weight.data");

  if(!weigh.ReadWeights())
    return 1;


  switch(argc){
    case 2:
      if(string(argv[1]) == string("rec")){
        cout << weigh.GetRecordFormatted() << endl;
				break;
			}
		case 3:
			if(string(argv[1]) == string("rec")){
				try{
					int nIndex = stoi((string)argv[2]);
					cout << weigh.GetRecordFormatted(nIndex) << endl;
					break;
				}catch(exception e) {
					Usage();
					return 1;
				}
			}
			if(string(argv[1]) == string("rem")){
				try{
					int nIndex = stoi((string)argv[2]);
					if(weigh.RemoveRecord(nIndex))
						break;
					else
						return 1;
				} catch(exception e){
					Usage();
					return 1;
				}
			}
		case 4:
			if(string(argv[1]) == string("add")){
				int nSt,nLbs;
				try{
					nSt = stoi((string)argv[2]);
					nLbs = stoi((string)argv[3]);
					if(!WeightData::IsValidWeight(nSt,nLbs)){
						cout << "Invalid Weight!" << endl;
						return 1;
					}
					weigh.AddWeight(nSt,nLbs);
					break;
				} catch(exception e){
					Usage();
					return 1;
				}
			}
    default:
      return Usage();
  }
  return 0;
}
