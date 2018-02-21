#ifndef CPU_H_INCLUDED
#define CPU_H_INCLUDED

#include <string>
#include <vector>

class Cpu
{
    public:
        Cpu(std::string filename);
        void call(unsigned short address);
        void ret();
        void jump(unsigned short address);
        void ifEq(unsigned char x, unsigned char val);
        void ifNotEq(unsigned char x, unsigned char val);
        void ifEqReg(unsigned char x, unsigned char y);
        void set(unsigned char x, unsigned char val);
        void add(unsigned char x, unsigned char val);
        void assign(unsigned char x, unsigned char y);
        void BitOr(unsigned char x, unsigned char y);
        void BitAnd(unsigned char x, unsigned char y);
        void BitXor(unsigned char x, unsigned char y);
        void addReg(unsigned char x, unsigned char y);
        void subReg(unsigned char x, unsigned char y);
        void shiftRight(unsigned char x, unsigned char y);
        void subCopy(unsigned char x, unsigned char y);
        void shiftLeft(unsigned char x, unsigned char y);
        void ifNotEqReg(unsigned char x, unsigned char y);
        void setI(unsigned short val);
        void JumpV0(unsigned short val);
        void andRand(unsigned char x, unsigned char val);
        void getDelay(unsigned char x);
        void addI(unsigned char x);
        void getFont(unsigned char x);
        void BCD(unsigned char x);
        void regDump(unsigned char x);
        void regLoad(unsigned char x);

        // Getters and Setters 
        unsigned char getMemory(unsigned short i);
        unsigned short getPc();
        unsigned short getIndex();

    private:
        unsigned short index;
        unsigned short pc;
        unsigned char memory[4096];
        unsigned char V[16];
        std::vector<unsigned short> stack;
        unsigned char delay_timer;
        unsigned char sound_timer;

};

#endif // CPU_H_INCLUDED
