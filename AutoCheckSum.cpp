// To use functions replace all unsigned int with uint8_t
// Create a vector with the command params inside it
// LoadDataPacket will load all the data required into a vector using the correct format including little endian for params, it will also generate a checksum and add it to the end of the data packet.

using namespace std;
#include <iostream>
//Function prototype for header file

struct DataPacket{
    unsigned int Header;
    unsigned int len;
    unsigned int ID;
    unsigned int RW;
    unsigned int isQueued;
    unsigned int CTRL;
    unsigned int numParams;
    unsigned int params[16];
    unsigned int CheckSum;
} DataPacket_to_DOBOT;

void AutoCheckSum(struct DataPacket *emptyDataPacket);
void LoadDataPacket(struct DataPacket *emptyDataPacket);



int main(void){
    DataPacket_to_DOBOT.Header = 0xAA;
    DataPacket_to_DOBOT.ID = 31;
    DataPacket_to_DOBOT.len = 3;
    DataPacket_to_DOBOT.isQueued = 1;
    DataPacket_to_DOBOT.RW = 1;
    DataPacket_to_DOBOT.numParams = 5;
    DataPacket_to_DOBOT.params[0] = {0x00};
    DataPacket_to_DOBOT.params[1] = {0x01};
    DataPacket_to_DOBOT.params[2] = {0x02};
    DataPacket_to_DOBOT.params[3] = {0x03};
    DataPacket_to_DOBOT.params[4] = {0x04};
   
    LoadDataPacket(&DataPacket_to_DOBOT);
    cout << DataPacket_to_DOBOT.Header << "\n";
    cout << DataPacket_to_DOBOT.Header << "\n";
    cout << DataPacket_to_DOBOT.len << "\n";
    cout << DataPacket_to_DOBOT.CTRL << "\n";
   
    cout << DataPacket_to_DOBOT.params[0] << "\n";
    cout << DataPacket_to_DOBOT.params[1] << "\n";
    cout << DataPacket_to_DOBOT.params[2] << "\n";
    cout << DataPacket_to_DOBOT.params[3] << "\n";
    cout << DataPacket_to_DOBOT.params[4] << "\n";
    cout << DataPacket_to_DOBOT.CheckSum << "\n";
   
}


//Function Definition
void AutoCheckSum(struct DataPacket *tempDataPacket){
    unsigned int Sum = 0;
    Sum += (*tempDataPacket).ID;
    Sum += (*tempDataPacket).CTRL;
    for(int scan = 0; scan < (*tempDataPacket).numParams; scan++){
        Sum += (*tempDataPacket).params[scan];
    }
    (*tempDataPacket).CheckSum = 256 - Sum;
}

void LoadDataPacket(struct DataPacket *tempDataPacket){
                        (*tempDataPacket).CTRL = (((*tempDataPacket).isQueued) << 1) | (*tempDataPacket).RW;
                        unsigned int swap =  0;
                        for(int scan = 0; scan < ((*tempDataPacket).numParams)/2; scan++){
                            swap = (*tempDataPacket).params[scan];
                            (*tempDataPacket).params[scan] = (*tempDataPacket).params[(*tempDataPacket).numParams - scan - 1];
                            (*tempDataPacket).params[(*tempDataPacket).numParams - scan - 1] = swap;
                        }
                        AutoCheckSum(tempDataPacket);
}

