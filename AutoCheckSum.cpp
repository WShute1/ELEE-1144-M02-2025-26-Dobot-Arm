// To use functions replace all unsigned int with uint8_t
// Create a vector with the command params inside it
// LoadDataPacket will load all the data required into a vector using the correct format including little endian for params, it will also generate a checksum and add it to the end of the data packet.

using namespace std;
//#include <iostream>
#include <SoftwareSerial.h>
#include <avr/io.h>
//Function prototype for header file

struct DataPacket{
    unsigned int Header;
    unsigned int len;
    unsigned int ID;
    unsigned int RW;
    unsigned int isQueued;
    unsigned int CTRL;
    unsigned int numParams;
    unsigned int params[32];
    unsigned int CheckSum;
} DataPacket_to_DOBOT, DOBOT_to_Ardunio;

enum softSerial_State {
    INIT,
    WRITE,
    READ,
    PARSING,
    ERROR
};


enum ERRORFLAG {
    NOERROR,
    BUFFER_FULL,
    BUSY,
    WRITE_ERROR
};


void AutoCheckSum(struct DataPacket *emptyDataPacket);
void LoadDataPacket(struct DataPacket *emptyDataPacket);
void SendDataPacket(struct DataPacket *packetToSend, struct DataPacket *packet_received, SoftwareSerial& SoftPort);

#define ReceiverPin 2
#define TransmitterPin 3


int main(void){

    //SOFTWARE SERIAL setup

    SoftwareSerial Dobot_Serial = SoftwareSerial(ReceiverPin, TransmitterPin);

    DDRD &= ~(1 << DDD2); //Set pin 2 in pin read mode
    DDRD |= (1 << DDD3); //Set pin 3 in pin write mode

    Dobot_Serial.begin(115200); //Initate software serial
    

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
    SendDataPacket(&DataPacket_to_DOBOT, &DOBOT_to_Ardunio, Dobot_Serial);
   /*
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
   */
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

void SendDataPacket(struct DataPacket *packetToSend, struct DataPacket *packet_received, SoftwareSerial& SoftPort){
    enum ERRORFLAG Error_Flag = NOERROR;
    enum softSerial_State Dobot_Serial_state = INIT;
    int ReadBufferIter = 0;
    unsigned int complete = 0;
    unsigned int ReadBuffer[38];
    while(complete != 1){
        switch(Dobot_Serial_state){
            case INIT:
                    if(SoftPort.isListening()){
                        Dobot_Serial_state = WRITE;
                    }
                    else{
                        SoftPort.listen();
                    }
                break;
            case WRITE:
                    if(SoftPort.available() > 0){
                        Dobot_Serial_state = ERROR;
                        Error_Flag = BUSY;
                    }
                    else{
                        SoftPort.write((*packetToSend).Header);
                        SoftPort.write((*packetToSend).Header);
                        SoftPort.write((*packetToSend).len);
                        SoftPort.write((*packetToSend).ID);
                        SoftPort.write((*packetToSend).CTRL);
                        for(int i = 0; i < (*packetToSend).numParams; i++){
                           SoftPort.write((*packetToSend).params[i]); 
                        }
                        SoftPort.write((*packetToSend).CheckSum);
                        Dobot_Serial_state = READ;
                    }
                break;
            case READ:
                    ReadBufferIter = 0;
                    while(SoftPort.available() > 0){
                        ReadBuffer[ReadBufferIter] = SoftPort.read();
                    }
                    delay(100);
                    Dobot_Serial_state = PARSING;
                break; 
            case PARSING:
                    packet_received->len = ReadBuffer[2];
                    packet_received->ID = ReadBuffer[3];
                    packet_received->numParams = packet_received->len - 2;
                    for(int j = packet_received->numParams; j > 0; j--){
                        packet_received->params[j-1] = ReadBuffer[5 + packet_received->numParams - j];
                    }
                    complete = 1;
                    break;
            case ERROR:
                    switch(Error_Flag){
                        case NOERROR:
                            break;
                        case BUFFER_FULL:
                            break;
                        case BUSY:
                            break;
                        case WRITE_ERROR:
                            break;
                    }
                break;
        }
    }
}

// create function that sends a completed DataPacket over software serial UART
// Create a function that sends the dobot a position
// create a function that reads the dobots current position
// create a function that hones the dobot position
// create a function that asks for the current size of the dobot queue