#include <vector>

//Function prototype for header file
void AutoCheckSum(vector<unsigned int>* payload);


void main(void){
    unsigned int Header = 0xAA;
    unsigned int ID = 31;
    unsigned int len = 3;
    unsigned int CTRL = 3;
    unsigned int Params = 0x00;
    vector<unsigned int> dataPacket = {Header, Header, len, ID, CTRL, Params};
    AutoCheckSum(&dataPacket);
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

//use vectors for payload they are resizable arrays. 
//use this to take an vector array and sum all the elements in the payload part of the command packet
// resize the command packet adding the checksum to the end of the packet.

// in main file define the command packet as a vector of unsigned int.
// define the size of the vector based on the command to the robot. 
// define the param size using #define <name> "number" format 
// use pointer to move the vector in and out of the function 

// write function that defines and builds a datapacket. remembing to make multiple byte little endian as per datasheet
