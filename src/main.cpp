#include <iostream>
#include "bitw.hpp"
#include "cpu.hpp"
#include "gb_program.hpp"
#include <SDL3/SDL.h>
#include "bus.hpp"





using namespace std;

using Short = uint16_t;
using Byte = uint8_t;
// 1
// 0000 1110
int main(){
    Ram ram{8000};
    Bus bus{ram};
    SharpSM83 cpu{bus};

    // cpu.PC = 0x00FF;
    // ram.write(0x88, 0x0100);
    // ram.write(0x13, 0x0101);
    // cpu.inc_pc();
    // cpu.ld_r16_imm16(0x21);
    // std::cout << cpu.read_r16(0x02) << std::endl;
    // cpu.A = 0xFF;
    // cpu.ld_r16mem_a(0x21);
    // std::cout << (int)cpu.bus.read_memory(0x1388) << endl;
    cpu.A = 0x0E;
    cpu.set_carry();
    cpu.rra(0x00);
    std::cout << (std::bitset<8>)cpu.A << endl;
    std::cout << (int)cpu.get_carry() << endl;

    // std::cout << (0xFF + (int8_t)0x80); 
    // ####
//     CPU cpu;
//     GB_Program program{cpu,ram};
//     SDL_Window *window = SDL_CreateWindow("Pong", 1200, 675, SDL_WINDOW_OPENGL);
//     SDL_Renderer *renderer = SDL_CreateRenderer(window, NULL);
   
//     // Player player2;
//     // player2.sprite.x = 1000;
    

    
//     SDL_Init(SDL_INIT_VIDEO);


//     bool running = true;

//     uint64_t ticks = SDL_GetTicks();
//     while(running){


//         float delta = (SDL_GetTicks()-ticks)/ 1000.0f;
//         ticks = SDL_GetTicks();

//         SDL_Event event;
//         while(SDL_PollEvent(&event)){
//             if(event.type == SDL_EVENT_QUIT){
//                 running = false;
//             }
            
//         }

//         const bool* state = SDL_GetKeyboardState(NULL);
//         if(state[SDL_SCANCODE_W]) {
//             program.ram.write(0x02, 0xFF);
        
//         }if(!state[SDL_SCANCODE_W]){
//             program.ram.write(0x00, 0xFF);

//         }
//     std::cout << (bitset<8>)program.ram.read(0x00FF) << endl;
   

//     }
    
    



}