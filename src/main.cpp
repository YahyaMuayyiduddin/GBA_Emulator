#include <iostream>
#include "bitw.hpp"
#include "cpu.hpp"
#include "gb_program.hpp"
#include <SDL3/SDL.h>
#include "bus.hpp"


void test_daa(Ram& ram, Bus& bus, SharpSM83& cpu){
    cpu.A = 0x7D;
    cpu.daa(0x00);
    // cpu.set_carry();
    // cpu.set_h_carry();
    cpu.set_subtract();
    cpu.A = (0x4B);
    cpu.daa(0x00);
    std::cout << (int)(extract_high_nibble(cpu.A));
    std::cout << (int)(extract_low_nibble(cpu.A)) << endl;
    std::cout << (int)(cpu.A == 0x45);




}

using namespace std;

using Short = uint16_t;
using Byte = uint8_t;
// 1
// 0000 1110
int main(){
    Ram ram{8000};
    Bus bus{ram};
    SharpSM83 cpu{bus};

    test_daa(ram, bus, cpu);
   
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