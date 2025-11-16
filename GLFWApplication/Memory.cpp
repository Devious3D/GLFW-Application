#ifndef Memory_cpp 
#define Memory_cpp

#include "EngineDefinitions.h"

template<typename T>
void CMemoryHandler<T>::Update() {

	FMemoryHandle* startingPoint = this->head;
	if (startingPoint == nullptr) { return; }

	int newestUsage = 0;
	int positionCount = 0;
	int newestActiveElementCount = 0;

	for (;;) {

		newestUsage += sizeof(startingPoint);

		
		/*if (startingPoint->data != nullptr) {
			newestActiveElementCount++;
		}*/

		startingPoint->position = positionCount;
		positionCount++;


		if (startingPoint->nextHandle == nullptr) break;
		startingPoint = startingPoint->nextHandle;
	}

	this->usage = newestUsage;
	this->activeElements = newestActiveElementCount;
}

template<typename T>
void CMemoryHandler<T>::Init(unsigned int capacity, unsigned int maxElements)
{

	

}


template<typename T>
void CMemoryHandler<T>::Insert(T data, unsigned int position)
{
	
}


template<typename T>
inline FMemoryHandle* CMemoryHandler<T>::Get(unsigned int position)
{
	
}

template<typename T>
inline void CMemoryHandler<T>::Remove(unsigned int position)
{
	if (position + 1 > this->maxElements) ThrowError("Position out of scope");


	FMemoryHandle* startingPoint = this->head;

	for (;;) {
		if (startingPoint->position == position) {
			std::memcpy(startingPoint->data, &this->emptyData, this->maxElementDataSize);
			break;
		}

		startingPoint = startingPoint->nextHandle;
	}
}

template<typename T>
inline T CMemoryHandler<T>::operator[](unsigned int position)
{
	if (position + 1 > this->maxElements) ThrowError("Position out of scope");


	FMemoryHandle* targetHandle = this->Get(position);
	//if (targetHandle->data == nullptr) {
	//	ThrowError(std::string("No dat at"))
	//	//Engine::ThrowError(("No data at position %s", position));
	//}


	T* castedData = static_cast<T*>(targetHandle->data);

	return *castedData;
	return T();
}




#endif // Memory_cpp