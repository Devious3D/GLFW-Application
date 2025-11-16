#pragma once  
#ifndef Memory_h
#define Memory_h

#include "EngineDefinitions.h"

enum class MemoryHandlerErrorType {
	ClassNotInitialized,
	HeadIsNullptr,
	CapacityReached,
	MaxElementsReached,
	DataExceedsLimit
};

//Change the position to id
//Set the id to the amount of active elements + 1
//Change the insert to take data only
//since the order of the handles will not matter. Swap the handle at the end to the empty one (Swapback)

struct FMemoryHandle {
	FMemoryHandle* nextHandle = nullptr;
	void* data = nullptr;
	unsigned int position = 0;

	inline FMemoryHandle(size_t size) {
		data = (uint8*)malloc(size);
	}
};

template <typename T>
class CMemoryHandler {


private:

	FMemoryHandle* head = nullptr;
	FMemoryHandle* tail = nullptr;
	FMemoryHandle* lastElement = nullptr;

	uint usage = 0;
	uint capacity = 0;
	uint maxElements = 0;
	uint activeElements = 0;

	size_t maxElementDataSize = 0;
	size_t maxMemoryHandleSize = 0;

	void* emptyData = nullptr;

	void Update() {

		FMemoryHandle* startingPoint = this->head;
		if (startingPoint == nullptr) { return; }

		int newestUsage = 0;
		int newestActiveElementCount = 0;

		for (;;) {

			newestUsage += sizeof(startingPoint);

			if (IsHandleEmpty(startingPoint) == false)
				newestActiveElementCount++;


			if (startingPoint->nextHandle == nullptr) break;
			startingPoint = startingPoint->nextHandle;
		}

		if (usage > capacity) ThrowError("Exceeded Memory");

		this->usage = newestUsage;
		this->activeElements = newestActiveElementCount;
		lastElement = startingPoint;
	}
	

	bool IsHandleEmpty(FMemoryHandle* handle) {
		return handle->data == this->emptyData;
	}


	FMemoryHandle* Get(unsigned int position) {
		if (position + 1 > this->maxElements) ThrowError("Position out of scope");

		FMemoryHandle* startingPoint = this->head;
		if (startingPoint == nullptr) ThrowError("Starting point is nullptr");

		for (;;) {

			if (startingPoint->position == position) break;
			if (startingPoint->nextHandle == nullptr) break;
			startingPoint = startingPoint->nextHandle;
		}

		return startingPoint;
	}

public: 

	void Construct(unsigned int capacity = 0, unsigned int maxElements = 0, unsigned int extraDataCapcityAmount = 0) {

		this->capacity = capacity;
		this->maxElements = maxElements;
		this->maxElementDataSize = sizeof(T) + cast<size_t>(extraDataCapcityAmount);
		this->maxMemoryHandleSize = sizeof(FMemoryHandle) + this->maxElementDataSize;

		this->emptyData = (uint8*)malloc(this->maxElementDataSize);

		for (int i = 0; i < maxElements; i++) {

			FMemoryHandle* newHandle = new FMemoryHandle(this->maxElementDataSize);
			newHandle->data = this->emptyData;
			newHandle->position = i;

			bool isHeadValid = (this->head == nullptr);
			switch (isHeadValid) {

			case true:
			{
				i++;
				FMemoryHandle* extraHandle = new FMemoryHandle(this->maxElementDataSize);
				extraHandle->position = i;

				head = newHandle;
				head->nextHandle = extraHandle;
				tail = extraHandle;
			}
			break;

			case false:

				tail->nextHandle = newHandle;
				tail = newHandle;

				break;
			}
		}


		lastElement = tail;
		tail = head;

		this->Update();
	}

	void Deconstruct() {
		FMemoryHandle* startingPoint = head;
		FMemoryHandle* nextHandle = nullptr;

		for (;;) {

			//Check is the handle is empty, if so clear it
			//At the end of Deconstruction, free the empty data

			free(startingPoint->data);

			if (startingPoint->nextHandle == nullptr) {
				delete startingPoint;
				break;
			}
			else
			{
				nextHandle = startingPoint->nextHandle;
				delete startingPoint;

				startingPoint = nextHandle;
				nextHandle = nullptr;
			}

			
		}

		this->usage = 0;
		this->capacity = 0;
		this->activeElements = 0;
		this->maxElements = 0;
		this->maxElementDataSize = 0; 
		this->maxMemoryHandleSize = 0;

		free(this->emptyData);
	}


	void Insert(T data) {
		if (activeElements + 1 >= this->maxElements) ThrowError("Exceed element count");
		tail = tail->nextHandle;
		std::memcpy(&tail->data, &data, this->maxElementDataSize);

		this->Update();	
	}

	void Insert(T data, unsigned int position) {
		if (position + 1 > this->maxElements) ThrowError("Position out of scope");
		if (FMemoryHandle* targetHandle = this->Get(position)) std::memcpy(targetHandle->data, &data, this->maxElementDataSize);

		this->Update();
	}



	inline void Remove(unsigned int position) {
		if (position + 1 > this->maxElements) ThrowError("Position out of scope");

		FMemoryHandle* startingPoint = this->head;
		FMemoryHandle* nextHandle = nullptr;
		FMemoryHandle* lastHandle = nullptr;

		for (;;) {
			if (startingPoint->position == position) {
				startingPoint->data = this->emptyData;

				//from the last handle, set its nextHandle to the nextHandle var

				for (;;) {



					nextHandle = startingPoint->nextHandle;
					lastHandle->nextHandle = nextHandle;

					nextHandle = lastHandle->nextHandle;

				}

				break;
			}


			if (startingPoint->nextHandle->position == position) lastHandle = startingPoint;
			startingPoint = startingPoint->nextHandle;
		}
		//save the handle before the empty handle
		//store the next handle
		//set the last handle to the current handle
		//set the last handle's "nextHandle to nextHandle;


		this->Update();
	}

	//This will loop through the list and return active elements
	inline void forEach(void(*loopFunc)(const int it, T data)) {
		if (loopFunc == nullptr) ThrowError("Must include a lambda");

		if (FMemoryHandle* startingPoint = head) {
			int currentIt = 0;

			for (;;) {

				if (this->IsHandleEmpty(startingPoint)) continue;

				if (T* castedData = cast<T*>(startingPoint->data)) {
					loopFunc(currentIt, *castedData);
				}

				if (startingPoint->nextHandle == nullptr) break;
				startingPoint = startingPoint->nextHandle;

				currentIt++;
			}
		}

	}

	inline uint size() {
		return this->activeElements;
	}

	inline uint getMaxSize() {
		return this->maxElements;
	}

	inline uint getUsage() {
		return this->usage;
	}

	

	inline T operator[](unsigned int position) {
		if (position + 1 > this->maxElements) ThrowError("Position out of scope");

		FMemoryHandle* targetHandle = this->Get(position);
		if (IsHandleEmpty(targetHandle)) 
			ThrowError("Handle is empty");

		T* castedData = static_cast<T*>(targetHandle->data);

		return *castedData;
	}

};

#endif // Memory_h