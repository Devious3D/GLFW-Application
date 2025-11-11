#pragma once
#ifndef EngineDefinitions_h
#define EngineDefinitions_h


#define Bytes(n) (n)
#define Kilobytes(n) (1024 * Bytes(n))
#define Megabytes(n) (1024 * Kilobytes(n))
#define Gigabytes(n) (1024 * Megabytes(n))


#define cast static_cast 
#define dynCast dynamic_cast

typedef unsigned int uint;


#endif