/**
Problem: A sound digital communication scheme would involve encoding data before it is sent to the receiver. A simple class of encoding schemes utilized in digital 
communications are the Hamming codes. The Hamming(7,4) code works as follows. A 4bit data sequence is sent along with 3 parity bits.

data =  d_1 d_2 d_3 d_4 P_1 P_2 P_3

The parity bits P_k allow for perfect recovery of the original data, even if the data is corrupted in the channel during transmission. The Hamming(7,4) code is used in schemes
where it is incredibly unlikely for two bits to be in error. Therefore, assume only one bit in the sequence is possibly in error. 
The parity bits are generated before transmission of the data as follows: 

P_1 = d_1 XOR d_2 XOR d_4
P_2 = d_1 XOR d_3 XOR d_4
P_3 = d_2 XOR d_3 XOR d_4

Given a set of 7 incoming bits, generate a function which checks if the data is corrupted, and if the data is in fact corrupted, fix the data.
Note that one or more of the parity bits could be corrupted.

Sample received data:       1101001.
Sample corrected output: 1001001 
*/

#include <iostream>

// -- function declerations.
static void checkHammingCode(bool* code, bool* output);


int main() {
    bool code[7] = {1,1,1,1,0,1,0};
    bool corrected[7] = {1,1,1,1,0,1,0}; // -- copy of code[7]
    checkHammingCode(code, corrected);
    
    // -- print results
    std::cout << "INPUT: ";
    for(int i = 0; i < 7; i++){
        std::cout << code[i];
    }
    std::cout << std::endl;
    
    std::cout << "OUTPUT: ";
    for(int i = 0; i < 7; i++){
        std::cout << corrected[i];
    }
    return 0;
}


static void checkHammingCode(bool* code, bool* output){
    // -- generate parity bits based on given data.
    bool parity[3];
    parity[0] = (code[0] != code[1]) != code[3];
    parity[1] = (code[0] != code[2]) != code[3];
    parity[2] = (code[1] != code[2]) != code[3];
    
    // -- check bit differences and find which bits are different.
    int bitsDifferentCount = 0;
    bool diffBits[3];
    for (int i = 0; i < 3; i++){
        if(parity[i] != code[4 + i]){ bitsDifferentCount++; }
        diffBits[i] = (parity[i] != code[4 + i]);
    }
    
    
    // -- based on bit differences create the new corrected code.
    if(bitsDifferentCount == 1){
        output[4] = (diffBits[0]) ? !code[4] : code[4];
        output[5] = (diffBits[1]) ? !code[5] : code[5];
        output[6] = (diffBits[2]) ? !code[6] : code[6];
    }
    else{
        if(diffBits[0] && diffBits[1] && diffBits[2]){ output[3] = !code[3]; }
        else if(diffBits[0] && diffBits[1]){ output[0] = !code[0]; }
        else if(diffBits[0] && diffBits[2]){ output[1] = !code[1]; }
        else if(diffBits[1] && diffBits[2]){ output[2] = !code[2]; }
    }
}

