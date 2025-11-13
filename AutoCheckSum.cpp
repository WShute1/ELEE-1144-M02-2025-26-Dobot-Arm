#include <vector>

// To use functions replace all unsigned int with uint8_t
// Create a vector with the command params inside it
// LoadDataPacket will load all the data required into a vector using the correct format including little endian for params, it will also generate a checksum and add it to the end of the data packet.

//Function prototype for header file
void AutoCheckSum(vector<unsigned int>* payload);
void LoadDataPacket(vector<unsigned int>* emptyDataPacket, unsigned int* Header,
                    unsigned int* ID, unsigned int* len, unsigned int* RW,
                    unsigned int* isQueued, vector<unsigned int> *params);


void main(void){
    unsigned int Header = 0xAA;
    unsigned int ID = 31;
    unsigned int len = 3;
    unsigned int isQueued = 1;
    unsigned int RW = 1;
    vector<unsigned int> Params = {0x00};
    vector<unsigned int> dataPacket;
    LoadDataPacket(&dataPacket, &Header, &ID, &len, &RW, &isQueued, &Params);
    for(int i = 0; i < dataPacket.size();i++){
       cout << dataPacket[i] << "\n"; 
    }
    
}


//Function Definition
void AutoCheckSum(vector<unsigned int>* payload){
    unsigned int Packet_Size = (*payload).size();
    unsigned int CheckSum = 0;
    for(int scan = 3; scan < Packet_Size; scan++){
        CheckSum += (*payload).at(scan);
    }
    CheckSum = 256 - CheckSum;
    (*payload).push_back(CheckSum);
}

void LoadDataPacket(vector<unsigned int>* emptyDataPacket, unsigned int *Header,
                    unsigned int *ID, unsigned int *len, unsigned int *RW,
                    unsigned int *isQueued, vector<unsigned int>* Params){
                        unsigned int NumParams = (*len) - 2;
                        unsigned int CTRL = ((*isQueued) << 1) | (*RW);
                        (*emptyDataPacket).assign(2 ,*Header);
                        (*emptyDataPacket).push_back(*len);
                        (*emptyDataPacket).push_back(*ID);
                        (*emptyDataPacket).push_back(CTRL);
                        for(int scan = 0; scan < NumParams; scan++){
                            (*emptyDataPacket).push_back((*Params).back());
                            (*Params).pop_back();
                        }
                        AutoCheckSum(emptyDataPacket);

}
//use vectors for payload they are resizable arrays. 
//use this to take an vector array and sum all the elements in the payload part of the command packet
// resize the command packet adding the checksum to the end of the packet.

// in main file define the command packet as a vector of unsigned int.
// define the size of the vector based on the command to the robot. 
// define the param size using #define <name> "number" format 
// use pointer to move the vector in and out of the function 

// write function that defines and builds a datapacket. remembing to make multiple byte little endian as per datasheet


