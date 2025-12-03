#pragma once
#ifndef EngineDefinitions_h
#define EngineDefinitions_h


#include <vector>
#include <string>
#include <iostream>

#include <Random>

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

static inline void print(std::string msg) {
	std::cout << msg << std::endl;
}

static int math_random(int min, int max) {
	std::srand(min);
	return std::rand() % max;
}

//static float math_random(float min, float max) {
//	std::srand(min);
//	return std::rand() % max;
//}

namespace TaskDefinitions {


	struct FTaskLog {
		unsigned int type;
		unsigned int id;
		void(*callbackFunction) = nullptr;
		bool repeats;

		FTaskLog(unsigned int type, unsigned int id, bool repeats, void(*function)()) {
			this->type = type;
			this->id = id;
			this->repeats = repeats;
			this->callbackFunction = function;
		}
	};
}

namespace TimerDefinitions {
	struct FTimer {

	};
}


#endif // EngineDefinitions_h