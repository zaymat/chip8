#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <fstream>

#include "cpu.h"

using namespace std;

Cpu::Cpu(string filename){
    ifstream file(filename);

    if(file)
    {
        for(int i = 0; i<4096; i++){
            file.get(this->memory[i]);
        }
        this->index = 0;
        this->pc = 0;
        for(int i = 0; i<4096; i++){
            this->V[i] = 0;
        }
        this->delay_timer = 60;
        this->sound_timer = 60;
    }
    else
    {
        cout << "ERREUR: Impossible d'ouvrir le fichier en lecture." << endl;
    }

}

void Cpu::call(){
    this->stack.push_back(this->pc+1);
    this->pc = this->index;
}

void Cpu::ret(){
    this->pc = this->stack.pop_back();
}

void Cpu::jump(){
    this->pc = this->index;
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

void Cpu::or(unsigned char x, unsigned char y){
    this->V[x] = this->V[x] | this->V[y];
    this->pc += 2;
}

void Cpu::and(unsigned char x, unsigned char y){
    this->V[x] = this->V[x] & this->V[y];
    this->pc += 2;
}

void Cpu::xor(unsigned char x, unsigned char y){
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
    this->V[15] = (this->V[y] << 3 & x0F) >> 3;
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
    this->V[15] = (this->V[y] >> 3 & x0F) >> 3;
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

void Cpu::JumpV0(unsigned short val){
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

void Cpu::addI(unsigned char x){
    this->I += this->V[x];
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