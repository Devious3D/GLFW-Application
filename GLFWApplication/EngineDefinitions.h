#pragma once
#if EngineDefinitions_h == 0
#define EngineDefinitions_h

#include <iostream>

namespace Engine {

	#define Bytes(n) (n)
	#define Kilobytes(n) (1024 * Bytes(n))
	#define Megabytes(n) (1024 * Kilobytes(n))
	#define Gigabytes(n) (1024 * Megabytes(n))

	
	void print(const char* msg) {
		std::cout << msg << std::endl;
	}

	void print(int msg) {
		std::cout << msg << std::endl;
	}

	void print(float msg) {
		std::cout << msg << std::endl;
	}

	void print(double msg) {
		std::cout << msg << std::endl;
	}
}

#endif