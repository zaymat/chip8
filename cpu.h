#ifndef CPU_H_INCLUDED
#define CPU_H_INCLUDED

#include <string>
#include <vector>

class Cpu
{
    public:
        Cpu(std::string filename);
        void call();
        void return();
        void jump();
        void ifEq(unsigned char x, unsigned char val);
        void ifNotEq(unsigned char x, unsigned char val);
        void ifEqReg(unsigned char x, unsigned char y);
        void set(unsigned char x, unsigned char val);
        void add(unsigned char x, unsigned char val);
        void assign(unsigned char x, unsigned char y);
        void or(unsigned char x, unsigned char y);
        void and(unsigned char x, unsigned char y);
        void xor(unsigned char x, unsigned char y);
        void add(unsigned char x, unsigned char y);
        void sub(unsigned char x, unsigned char y);
        void shiftRight(unsigned char x, unsigned char y);
        void sub(unsigned char x, unsigned char y);
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
