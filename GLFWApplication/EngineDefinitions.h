#pragma once
#if EngineDefinitions_h == 0
#define EngineDefinitions_h

#include <iostream>

namespace Engine {
	
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