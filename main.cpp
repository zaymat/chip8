#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <SFML/Graphics.hpp>
#include <unistd.h>

#include "cpu.h"
#include "gpu.h"

using namespace std;

int main (int argc, char *argv[])
{
    if (argc != 2){
        cout << "Wrong number of argument: 1 is required but " << argc-1 << " were given" << endl;
        return 1;
    }

    string file;
    file = string(argv[1]);

    Cpu cpu(file);
    Gpu gpu(file);
    
    unsigned char x, y, val;
    unsigned short address, opcode, index;
    unsigned char height;
    vector<unsigned char> sprite;

    while(gpu.isOpen()){
        sf::Event event;
        opcode = cpu.getMemory(cpu.getPc()) << 8 | cpu.getMemory(cpu.getPc() + 1);
        switch(opcode & 0xF000){
            case 0x0000:
                switch(opcode & 0x00FF){
                    case 0x00E0:
                        gpu.clear();
                        cpu.setPc(cpu.getPc() + 2);
                        break;

                    case 0x00EE:
                        cpu.ret();
                        break;

                    default:
                        address = opcode & 0x0FFF;
                        cpu.call(address);
                        break;
                }
                break;

            case 0x1000:
                address = opcode & 0x0FFF;
                cpu.jump(address);
                break;

            case 0x2000:
                address = opcode & 0x0FFF;
                cpu.call(address);
                break;
            
            case 0x3000:
                x = (opcode & 0x0F00) >> 8;
                val = opcode & 0x00FF;
                cpu.ifEq(x, val);
                break;
            
            case 0x4000:
                x = (opcode & 0x0F00) >> 8;
                val = opcode & 0x00FF;
                cpu.ifNotEq(x, val);
                break;

            case 0x5000:
                x = (opcode & 0x0F00) >> 8;
                y = (opcode & 0x00F0) >> 4;
                cpu.ifEqReg(x, y);
                break;
            
            case 0x6000:
                x = (opcode & 0x0F00) >> 8;
                val = opcode & 0x00FF;
                cpu.set(x, val);
                break;

            case 0x7000:
                x = (opcode & 0x0F00) >> 8;
                val = opcode & 0x00FF;
                cpu.add(x, val);
                break;
            
            case 0x8000:
                x = (opcode & 0x0F00) >> 8;
                y = (opcode & 0x00F0) >> 4;
                switch(opcode & 0x000F){
                    case 0x0000:
                        cpu.assign(x, y);
                        break;

                    case 0x0001:
                        cpu.BitOr(x, y);
                        break;

                    case 0x0002:
                        cpu.BitAnd(x, y);
                        break;
                    
                    case 0x0003:
                        cpu.BitXor(x, y);
                        break;
                    
                    case 0x0004:
                        cpu.addReg(x, y);
                        break;

                    case 0x0005:
                        cpu.subReg(x, y);
                        break;

                    case 0x0006:
                        cpu.shiftRight(x, y);
                        break;
                    
                    case 0x0007:
                        cpu.subCopy(x, y);
                        break;
                    
                    case 0x000E:
                        cpu.shiftLeft(x, y);
                        break;
            
                    default:
                        break;
                }
                break;
        
            case 0x9000:
                x = (opcode & 0x0F00) >> 8;
                y = (opcode & 0x00F0) >> 4;
                cpu.ifNotEqReg(x, y);
                break;

            case 0xA000:
                address = opcode & 0x0FFF;
                cpu.setI(address);
                break;

            case 0xB000:
                address = opcode & 0x0FFF;
                cpu.jumpV0(address);
                break;
            
            case 0xC000:
                x = (opcode & 0x0F00) >> 8;
                val = opcode & 0x00FF;
                cpu.andRand(x, val);
                break;
            
            case 0xD000:
                x = (opcode & 0x0F00) >> 8;
                y = (opcode & 0x00F0) >> 4;
                height = opcode & 0x000F;
                index = cpu.getIndex();
                sprite.clear();

                for(int i = 0; i < height; i++){
                    sprite.push_back(cpu.getMemory(index + i));
                }
                val =  gpu.draw(cpu.getReg(x), cpu.getReg(y), height, sprite);
                cpu.set(15, val);

                break;
            
            case 0xE000:
                x = (opcode & 0x0F00) >> 8;
                switch(opcode & 0x00FF){
                    case 0x009E:
                        cpu.ifKey(x);
                        break;

                    case 0x00A1:
                        cpu.ifNotKey(x);
                        break;
                    
                    default:
                        break;
                }
                break;
            
            case 0xF000:
                x = (opcode & 0x0F00) >> 8;
                switch(opcode & 0x00FF){
                    case 0x0007:
                        cpu.getDelay(x);
                        break;

                    case 0x000A:
                        val = gpu.waitEvent(&event);
                        cpu.setKey(val, 1);
                        cpu.set(x, val);
                        break;
                    
                    case 0x0015:
                        cpu.setDelay(x);
                        break;
                    
                    case 0x0018:
                        cpu.setSound(x);
                        break;

                    case 0x001E:
                        cpu.addI(x);
                        break;
                    
                    case 0x0029:
                        cpu.getFont(x);
                        break;
                    
                    case 0x0033:
                        cpu.BCD(x);
                        break;
                    
                    case 0x0055:
                        cpu.regDump(x);
                        break;
                    
                    case 0x0065:
                        cpu.regLoad(x);
                        break;
                    
                    default:
                        break;
                }
                break;

            default:
                cout << "Unknown opcode" << opcode << endl;
                break;
            
        }
    
    unsigned short res;

    res = gpu.pollEvent(&event);
    if(res != 0x00FF){
        cpu.setKey(res & 0x00FF, (res & 0xFF00) >> 8);
    }

    if(cpu.getDelayTimer() > 0){
        cpu.updateDelay();
    }

    if(cpu.getSoundTimer() > 0)
    {
        if(cpu.getSoundTimer() == 1){
            printf("BEEP!\n");
        }
        cpu.updateSound();
    }  

    usleep(200);
    }
    



    return 0;
}
