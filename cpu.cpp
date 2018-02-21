#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <fstream>

#include "cpu.h"

using namespace std;

Cpu::Cpu(string filename){

    char a;

    ifstream file;
    file.open(filename, ios::in | ios::binary);
    if(file)
    {
        for(int i = 0; i<4096; i++){
            if(file.read(&a, sizeof(char))){
            memory[i] = a;
            }
            else{
                memory[i] = 0;
            }
        }
        index = 0;
        pc = 0x200;
        for(int i = 0; i<16; i++){
            V[i] = 0;
        }
        delay_timer = 60;
        sound_timer = 60;
    }
    else
    {
        cout << "ERROR: Cannot open the file" << filename << endl;
    }

}

void Cpu::call(unsigned short address){
    this->stack.push_back(this->pc+1);
    this->pc = address;
}

void Cpu::ret(){
    this->pc = this->stack.back();
    this->stack.pop_back();
}

void Cpu::jump(unsigned short address){
    this->pc = address;
}

void Cpu::ifEq(unsigned char x, unsigned char val){
    if(this->V[x] == val){
        this->pc += 4;
    }
    else{
        this->pc += 2;
    }
}

void Cpu::ifNotEq(unsigned char x, unsigned char val){
    if(this->V[x] != val){
        this->pc += 4;
    }
    else{
        this->pc += 2;
    }
}

void Cpu::ifEqReg(unsigned char x, unsigned char y){
    if(this->V[x] == this->V[y]){
        this->pc += 4;
    }
    else{
        this->pc += 2;
    }
}

void Cpu::set(unsigned char x, unsigned char val){
    this->V[x] = val;
    this->pc += 2;
}

void Cpu::add(unsigned char x, unsigned char val){
    this->V[x] = (this->V[x] + val) % 256;
    this->pc += 2;
}

void Cpu::assign(unsigned char x, unsigned char y){
    this->V[x] = this->V[y];
    this->pc += 2;
}

void Cpu::BitOr(unsigned char x, unsigned char y){
    this->V[x] = this->V[x] | this->V[y];
    this->pc += 2;
}

void Cpu::BitAnd(unsigned char x, unsigned char y){
    this->V[x] = this->V[x] & this->V[y];
    this->pc += 2;
}

void Cpu::BitXor(unsigned char x, unsigned char y){
    this->V[x] = this->V[x] ^ this->V[y];
    this->pc += 2;
}

void Cpu::addReg(unsigned char x, unsigned char y){
    this->V[x] = (this->V[x] + this->V[y]) % 256;
    this->V[15] = (this->V[x] + this->V[y]) / 256;
    this->pc += 2;
}

void Cpu::subReg(unsigned char x, unsigned char y){
    this->V[x] = (this->V[x] - this->V[y]) % 256;
    this->V[15] = (256 - this->V[x] + this->V[y]) / 256;
    this->pc += 2;
}

void Cpu::shiftRight(unsigned char x, unsigned char y){
    char res = this->V[y] >> 1;
    this->V[x] = res;
    this->V[15] = (this->V[y] << 3 & 0x0F) >> 3;
    this->V[y] = res;
    this->pc += 2;
}

void Cpu::subCopy(unsigned char x, unsigned char y){
    this->V[x] = (this->V[y] - this->V[x]) % 256;
    this->V[15] = (256 - this->V[y] + this->V[x]) / 256;
    this->pc += 2;
}

void Cpu::shiftLeft(unsigned char x, unsigned char y){
    char res = this->V[y] << 1;
    this->V[x] = res;
    this->V[15] = (this->V[y] >> 3 & 0x0F) >> 3;
    this->V[y] = res;
    this->pc += 2;
}

void Cpu::ifNotEqReg(unsigned char x, unsigned char y){
    if(this->V[x] != this->V[y]){
        this->pc += 4;
    }
    else{
        this->pc += 2;
    }
}

void Cpu::setI(unsigned short val){
    this->index = val;
    this->pc += 2;
}

void Cpu::jumpV0(unsigned short val){
    this->pc = this->V[0] + this->index;
}

void Cpu::andRand(unsigned char x, unsigned char val){
    char randChar = rand() % (256);
    this->V[x] = randChar & val;
    this->pc += 2;
}

void Cpu::getDelay(unsigned char x){
    this->V[x] = this->delay_timer;
    this->pc += 2;
}

void Cpu::setDelay(unsigned char x){
    this->delay_timer = this->V[x];
    this->pc += 2;
}

void Cpu::setSound(unsigned char x){
    this->sound_timer = this->V[x];
    this->pc += 2;
}

void Cpu::addI(unsigned char x){
    this->index += this->V[x];
    this->pc += 2;
}

void Cpu::getFont(unsigned char x){
    this->index = 16 * x + 80;
    this->pc += 2;
}

void Cpu::BCD(unsigned char x){
    this->memory[this->index] = this->V[x] / 100;
    this->memory[this->index + 1] = (this->V[x] / 10) % 10;
    this->memory[this->index + 2] = (this->V[x]) % 100;
    this->pc += 2;
}

void Cpu::regDump(unsigned char x){
    for(int i = 0; i<= x; i++){
        this->memory[this->index + i] = this->V[i];
    }
    this->pc += 2;
}

void Cpu::regLoad(unsigned char x){
    for(int i = 0; i<= x; i++){
        this->V[i] = this->memory[this->index + i];
    }
    this->pc += 2;
}

// Getters and Setter

unsigned char Cpu::getMemory(unsigned short i){
    return this->memory[i];
}

unsigned short Cpu::getPc(){
    return this->pc;
}

unsigned short Cpu::getIndex(){
    return this->index;
}
