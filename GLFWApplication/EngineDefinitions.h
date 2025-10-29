#pragma once
#if EngineDefinitions_h == 0
#define EngineDefinitions_h 
#include <iostream>


namespace Engine {

#include <stdint.h>
#include <cstring>

	typedef int8_t int8;
	typedef int16_t int16;
	typedef int32_t int32;
	typedef int64_t int64;
	typedef uint8_t uint8;
	typedef uint16_t uint16;
	typedef uint32_t uint32;
	typedef uint64_t uint64;
	
	struct FString : std::string {

	};

	
	#define cast static_cast
	#define dynCast dynamic_cast

	#define Bytes(n) (n)
	#define Kilobytes(n) (1024 * Bytes(n))
	#define Megabytes(n) (1024 * Kilobytes(n))
	#define Gigabytes(n) (1024 * Megabytes(n))

	static inline void ThrowError(const char* msg) {
		std::cout << "(Error) | " << msg << std::endl;
		return throw;
	}

	static void print(const char* msg) {
		std::cout << msg << std::endl;
	}

	static void print(int msg) {
		std::cout << msg << std::endl;
	}

	static void print(float msg) {
		std::cout << msg << std::endl;
	}

	static void print(double msg) {
		std::cout << msg << std::endl;
	}
}

#endif