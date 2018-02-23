#include <iostream>
#include <SFML/Graphics.hpp>

#include "gpu.h"

using namespace std;

Gpu::Gpu(std::string filename){
    string title;
    title = "Chip 8 : " + filename;

    this->window.create(sf::VideoMode(640, 320), title);
    this->window.clear(sf::Color::Black);

    for(int i = 0; i < 64; i++){
        for(int j = 0; j < 32; j++){
            gfx[i][j] = 0;
            pixels[i][j].setSize(sf::Vector2f(10, 10));
            pixels[i][j].setFillColor(sf::Color(0, 0, 0));
            pixels[i][j].setPosition(sf::Vector2f(i*10,j*10));
            this->window.draw(this->pixels[i][j]);
        }
    }
    this->window.display();
}

unsigned char Gpu::draw(unsigned char x, unsigned char y, unsigned char height, vector<unsigned char> sprite){
    unsigned char VF(0);
    int xi,yi;
    for (int j = 0; j < height; j++)
    {
        yi = (y + j) % 32;
        for(int i = 0; i < 8; i++)
        {
            xi = (x + i) % 64;
            if((sprite[j] & (0x80 >> i)) != 0)
            {
                if(this->gfx[xi][yi] == 1){
                    VF = 1;                   
                }
                this->gfx[xi][yi] ^= 1;
            }
        }
    }

    for(int i = 0; i < 64; i++){
        for(int j = 0; j < 32; j++){
            if(this->gfx[i][j] == 0){
                this->pixels[i][j].setFillColor(sf::Color(0, 128, 128));
                this->window.draw(this->pixels[i][j]);
            }
            else{
                this->pixels[i][j].setFillColor(sf::Color(255, 0, 0));
                this->window.draw(this->pixels[i][j]);
            }
            
        }
    }

    this->window.display();

    return VF;

}

bool Gpu::isOpen(){
    return this->window.isOpen();
}

void Gpu::clear(){
    this->window.clear();
    for(int i = 0; i < 64; i++){
        for(int j = 0; j < 32; j++){
            this->pixels[i][j].setFillColor(sf::Color(0, 128, 128));
            this->gfx[i][j] = 0;
            this->window.draw(this->pixels[i][j]);     
        }
    }
    this->window.display();
}

unsigned char Gpu::waitEvent(sf::Event *event){
    while(this->window.waitEvent(*event)){
        if(event->type == sf::Event::KeyPressed){
            switch(event->key.code){
                case sf::Keyboard::Num1:
                    return 0x01;
                
                case sf::Keyboard::Num2:
                    return 0x02;
                
                case sf::Keyboard::Num3:
                    return 0x03;

                case sf::Keyboard::Num5:
                    return 0x0C;

                case sf::Keyboard::A:
                    return 0x04;
                
                case sf::Keyboard::Z:
                    return 0x05;
                
                case sf::Keyboard::E:
                    return 0x06;

                case sf::Keyboard::R:
                    return 0x0D;

                case sf::Keyboard::Q:
                    return 0x07;
                
                case sf::Keyboard::S:
                    return 0x08;
                
                case sf::Keyboard::D:
                    return 0x09;

                case sf::Keyboard::F:
                    return 0x0E;
                
                case sf::Keyboard::W:
                    return 0x0A;
                
                case sf::Keyboard::X:
                    return 0x00;
                
                case sf::Keyboard::C:
                    return 0x0C;

                case sf::Keyboard::V:
                    return 0x0F;

                default:
                    break;
            }
        }
    };
}

unsigned short Gpu::pollEvent(sf::Event *event){
    this->window.pollEvent(*event);
    if(event->type == sf::Event::KeyReleased){
        switch(event->key.code){
            case sf::Keyboard::Num1:
                return 0x0001;
            
            case sf::Keyboard::Num2:
                return 0x0002;
            
            case sf::Keyboard::Num3:
                return 0x0003;

            case sf::Keyboard::Num5:
                return 0x000C;

            case sf::Keyboard::A:
                return 0x0004;
            
            case sf::Keyboard::Z:
                return 0x0005;
            
            case sf::Keyboard::E:
                return 0x0006;

            case sf::Keyboard::R:
                return 0x000D;

            case sf::Keyboard::Q:
                return 0x0007;
            
            case sf::Keyboard::S:
                return 0x0008;
            
            case sf::Keyboard::D:
                return 0x0009;

            case sf::Keyboard::F:
                return 0x000E;
            
            case sf::Keyboard::W:
                return 0x000A;
            
            case sf::Keyboard::X:
                return 0x0000;
            
            case sf::Keyboard::C:
                return 0x000B;

            case sf::Keyboard::V:
                return 0x000F;

            default:
                return 0x00FF;
        }
    }
    else if(event->type == sf::Event::KeyPressed){
       switch(event->key.code){
            case sf::Keyboard::Num1:
                return 0x0101;
            
            case sf::Keyboard::Num2:
                return 0x0102;
            
            case sf::Keyboard::Num3:
                return 0x0103;

            case sf::Keyboard::Num5:
                return 0x010C;

            case sf::Keyboard::A:
                return 0x0104;
            
            case sf::Keyboard::Z:
                return 0x0105;
            
            case sf::Keyboard::E:
                return 0x0106;

            case sf::Keyboard::R:
                return 0x010D;

            case sf::Keyboard::Q:
                return 0x0107;
            
            case sf::Keyboard::S:
                return 0x0108;
            
            case sf::Keyboard::D:
                return 0x0109;

            case sf::Keyboard::F:
                return 0x010E;
            
            case sf::Keyboard::W:
                return 0x010A;
            
            case sf::Keyboard::X:
                return 0x0100;
            
            case sf::Keyboard::C:
                return 0x010B;

            case sf::Keyboard::V:
                return 0x010F;

            default:
                return 0x00FF;
        }     
    }

    return 0x00FF;
}