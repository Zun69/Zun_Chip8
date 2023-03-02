// Using https://austinmorlan.com/posts/chip8_emulator/ as reference

#include <iostream>
#include <fstream>

class Chip8
{
public:
    // Register is a dedicated location on a cpu for storage. Any operation that a CPU does must be done within its registers.
    // Operations involve loading data from memory into registers, operating on those registers, and then storing the result back into memory.
    // Chip 8 has 16 8-bit registers, labeled V0 to VF (hex) Register VF is a bit special. It’s used as a flag to hold information about the result of operations. 
    // Each register is able to hold any value from 0x00 to 0xFF.
    uint8_t registers[16]{};

    // Chip-8 has 4096 bytes of memory, address space is from 0x000 to 0xFFF
    // 0x000-0x1FF originally reserved for the chip 8 interpreter, but this emulator will never write or read from this area
    // 0x050-0x0A0 is storage space for the 16 built in characters (0 through F) which we will need to manually put into our memory because ROMs will be looking for those characters
    // 0x200-0xFFF stores instructions from the rom, anything left after the ROM's space is free to use
    uint8_t memory[4096]{};
    // 16-bit index register is a special register used to store memory addresses for use in operations. It's a a 16 bit register because last memory address (0xFFF) is too big for 8 bit register
    uint16_t index{};
    // 16-bit program counter is a special register that holds the address of the next instruction to execute, 16 bit because it needs to store (0xFFF memory address)
    // Program counter is a CPU's way of keeping track of which instruction to execute next
    // Opcode is 2 byes but memory is addressed as a single byte, so when we fetch an instrucion from memory we need to fetch a byte from PC and a byte from PC+1 and connect them into a single value
    // Then increment PC by 2 because we have to increment the PC before executing any instructions because some instructions will manipulate the PC to control program flow.
    uint16_t pc{};

    // 16 level stack, a stack is a way for a CPU to keep track of the order of execution when it calls into functions.
    // There is an instruction (CALL) that will cause the CPU to begin executing instructions in different region of the program.
    // When the program reaches another instruction (RET), it must be able to go back to where it was when it hit the (CALL) instruction.
    // The stack holds the PC value when the CALL instruction was executed, and the RETURN statement pulls that address from the stack and puts it back into the PC so the CPU will execute it on the next cycle.
    // Means the PC will return to address before CALL instruction was executed.
    // Chip-8 has 16 levels of stack, meaning it can hold 16 different PC's. Multiple levels allow for one function to call another function and so on, until they all return to the original caller site
    // Putting a PC onto the stack is called PUSHING and pulling a PC off the stack is called POPPING
    uint16_t stack[16]{};

    // 8-bit stack pointer, similar to how the PC is used to keep track of where in memory the CPU is executing, a SP is used to tell us where in the 16-levels of stack our most recent value was placed (i.e the top)
    // We only need 8 bits for our stack pointer because the stack will be represented as an array, so the SP can just be an index into that array. We only need sixteen indices then, which a single byte can manage
    // When we pop a value off the stack, we won’t actually delete it from the array but instead just copy the value and decrement the SP so it “points” to the previous value.
    uint8_t sp{};

    // 8-bit delay timer is a simple timer used for timing, if the timer value is zero it stays zero, if it's loaded with a value it will decrement at a rate of 60hz
    uint8_t delayTimer{};

    // 8-bit sound timer it will decrement at 60hz if non zero, but a single tone will buzz when it's non-zero
    uint8_t soundTimer{};

    //16 input keys, ill take input mapping from website
    uint8_t keypad[16]{};

    //64x32 monochrome display memory, memory buffer used for storing the graphics to display, each pixel is either on or off so only two colors can be represented
    uint32_t video[64 * 32]{};
    uint16_t opcode;
};

int main()
{
}




