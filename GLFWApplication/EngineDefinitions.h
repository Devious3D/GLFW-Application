#pragma once
#ifndef EngineDefinitions_h
#define EngineDefinitions_h


#include <vector>
#include <string>
#include <iostream>

#define Bytes(n) (n)
#define Kilobytes(n) (1024 * Bytes(n))
#define Megabytes(n) (1024 * Kilobytes(n))
#define Gigabytes(n) (1024 * Megabytes(n))


#define cast static_cast 
#define dynCast dynamic_cast

typedef unsigned int uint;
typedef uint8_t uint8;



static inline void ThrowError(std::string msg) {
	std::cout << "(Error) | " << msg << std::endl;
	return throw;
}

static void print(std::string msg) {
	std::cout << msg << std::endl;
}

namespace TaskDefinitions {


	struct FTaskLog {
		unsigned int type;
		unsigned int id;
		const void(*function) = nullptr;
		bool repeats;
	};
}

namespace TimerDefinitions {
	struct FTimer {

	};
}


#endif // EngineDefinitions_h