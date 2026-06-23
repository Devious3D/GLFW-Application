#pragma once
#ifndef EngineDefinitions_h
#define EngineDefinitions_h

#include <string>
#include <iostream>

#include <Random>

#include <initializer_list>

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

namespace Vector {

	struct vec2;
	struct vec3;
	struct vec4;

	struct VectorComponent {
		
		/*template <typename T>
		static T operator+(T) {

		}*/


	};

	struct vec2 {
		float x;
		float y;

		vec2() {}
		vec2(float _x, float _y) : x(_x), y(_y) {}

		vec2 operator+ (vec2 vectorToAdd) {
			return vec2(x + vectorToAdd.x, y + vectorToAdd.y);
		}

	};

	struct vec3 {
		float x;
		float y;
		float z;

		vec3() {}
		vec3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}

	};

	struct Vertex {

	public:

		float glData[6] = {
			0.f, 0.f, 0.f, // Position
			//0.f, 0.f, 0.f, // color
		};

		vec3 position;
		vec3 color;
		vec2 texCoords;
	

		Vertex(float position_x, float position_y, float position_z) 
		{
			this->position = vec3(position_x, position_y, position_z);
		}


		void setGlData() {

			//Position
			glData[0] = position.x;
			glData[1] = position.y;
			glData[2] = position.z;

			//color
			//glData[3] = color.x;
			//glData[4] = position.x;
			//glData[5] = position.x;

		}

	};

}




#endif // EngineDefinitions_h