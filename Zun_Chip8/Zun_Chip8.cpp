// Using https://austinmorlan.com/posts/chip8_emulator/ as reference

#include <iostream>
#include <fstream>
#include "Chip8.hpp"
#include <random>
#include <chrono>

const unsigned int FONTSET_SIZE = 80;
const unsigned int FONTSET_START_ADDRESS = 0x50;
const unsigned int START_ADDRESS = 0x200;

Chip8::Chip8()
	: randGen(std::chrono::system_clock::now().time_since_epoch().count()) //seed random generator
{
	//load program counter
	pc = START_ADDRESS;

	// Load fonts into memory, takes up 80 bytes of memory
	for (unsigned int i = 0; i < FONTSET_SIZE; ++i)
	{
		memory[FONTSET_START_ADDRESS + i] = fontset[i];
	}

	// Initialize RNG
	randByte = std::uniform_int_distribution<uint8_t>(0, 255U);
}

//implement declaration of load rom from header file, char const* as the pointer is fixed and cannot change to point to anything else
void Chip8::LoadROM(char const* filename)
{
	//open file in binary mode and sets file pointer to the end of the stream on opening to get size of file
	std::ifstream file(filename, std::ios::binary | std::ios::ate);

	if (file.is_open())
	{
		// Get size of file and allocate a buffer that is the same size as the rom to hold the contents
		std::streampos size = file.tellg();
		char* buffer = new char[size];

		//go back to beginning of the rom file and fill the buffer
		file.seekg(0, std::ios::beg); //means offset of 0 from the beginning of file, i.e. the beginning
		file.read(buffer, size); 
		file.close();

		//load rom (the buffer) into chip 8 memory, starting at 0x200 
		for (long i = 0; i < size; i++)
		{
			memory[START_ADDRESS + i] = buffer[i];
		}

		//free the buffer
		delete[] buffer;
	}
}

uint8_t fontset[FONTSET_SIZE] =
{
	0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
	0x20, 0x60, 0x20, 0x20, 0x70, // 1
	0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
	0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
	0x90, 0x90, 0xF0, 0x10, 0x10, // 4
	0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
	0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
	0xF0, 0x10, 0x20, 0x40, 0x40, // 7
	0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
	0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
	0xF0, 0x90, 0xF0, 0x90, 0x90, // A
	0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
	0xF0, 0x80, 0x80, 0x80, 0xF0, // C
	0xE0, 0x90, 0x90, 0x90, 0xE0, // D
	0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
	0xF0, 0x80, 0xF0, 0x80, 0x80  // F
};





