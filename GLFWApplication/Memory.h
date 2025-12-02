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
	unsigned int Id = 0;

	inline FMemoryHandle(size_t size) {
		data = (uint8*)malloc(size);
	}
};

static void MemoryHandleErrorHandling(std::string msg) {
	ThrowError(std::string("Memory"));
}

template <typename T>
class CMemoryHandler {


private:

	FMemoryHandle* head = nullptr;
	FMemoryHandle* tail = nullptr; // this is the end of whats allocated to the handles
	FMemoryHandle* lastElement = nullptr; // this is the end of the array

	uint usage = 0;
	uint capacity = 0;
	uint maxElements = 0;
	uint activeElements = 0;

	size_t maxElementDataSize = 0;
	size_t maxMemoryHandleSize = 0;

	void* emptyData = nullptr;

	void Update() {

		if (FMemoryHandle* startingPoint = this->head) {
			if (startingPoint == nullptr) { return; }

			int newestUsage = 0;
			int newestActiveElementCount = 0;

			for (;;) {

				newestUsage += sizeof(startingPoint);

				if (IsHandleEmpty(startingPoint) == false) {
					newestActiveElementCount++;

					if (startingPoint->nextHandle == nullptr) break;
					startingPoint = startingPoint->nextHandle;
				}
				else
				{
					tail = startingPoint;
					break;
				}

			}

			this->usage = newestUsage;
			this->activeElements = newestActiveElementCount;
		}
	}
	

	bool IsHandleEmpty(FMemoryHandle* handle) {
		return handle->Id == 0;
	} 

	void clearHandle(FMemoryHandle* handle) {
		handle->Id = 0;
		std::memcpy(handle->data, &this->emptyData, this->maxElementDataSize);
	}


	FMemoryHandle* Get(unsigned int Id) {

		FMemoryHandle* startingPoint = this->head;

		if (startingPoint == nullptr) ThrowError("Starting point is nullptr");
		for (;;) {
			if (startingPoint->Id == Id) break;
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

		//optimize this for loop, your doing infinite loops many times
		for (int i = 0; i < maxElements; i++) {

			FMemoryHandle* newHandle = new FMemoryHandle(this->maxElementDataSize);
			std::memcpy(newHandle->data, &this->emptyData, this->maxElementDataSize);


			bool isHeadValid = (this->head == nullptr);
			switch (isHeadValid) {

			case true:
			{
				if (FMemoryHandle* newTailHandle = new FMemoryHandle(this->maxElementDataSize)) {
					head = newHandle;
					head->nextHandle = newTailHandle;

					tail = newTailHandle;
				}
			}
			break;

			case false:

				//Check if there are 2 or more elemenets initalized
				//If not, set the next handle on head to the newest handle. Set the tail to the newest handle
				//If so, next handle on the tail to the newest handle. Set the tail to the newest handle.

				tail->nextHandle = newHandle;
				tail = newHandle;

				//if (FMemoryHandle* startingPoint = this->head) {
				//	if (startingPoint == nullptr) { return; }

				//	for (;;) {

				//		if (startingPoint->nextHandle == nullptr) {
				//			startingPoint->nextHandle = newHandle;
				//			//this->tail = newHandle;
				//			break;
				//		}

				//		startingPoint = startingPoint->nextHandle;
				//	}
				//}
				
				break;
			}

			this->tail = head;
			this->lastElement = newHandle;
		}

		this->Update();
	}

	void DeConstruct() {
		FMemoryHandle* startingPoint = head;
		FMemoryHandle* nextHandle = nullptr;

		for (;;) {

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


	inline unsigned int Insert(T data) {
		if (this->tail->nextHandle == nullptr) ThrowError("Exceed element count");
		 
		if (IsHandleEmpty(head) == true) {
			print("Insterting to Head");
			head->Id = math_random(100, 1000);
			std::memcpy(head->data, &data, this->maxElementDataSize);
			return head->Id;
		}

		tail = tail->nextHandle;
		tail->Id = math_random(100, 1000);
		std::memcpy(tail->data, &data, this->maxElementDataSize);

		this->Update();
		return tail->Id;
	}



	inline bool Remove(unsigned int Id) {
		FMemoryHandle* handleBeforeCurrentTail = nullptr;

		//swap back
		//Move the tail to the point of removal
		//Then set the newest tail

		if (FMemoryHandle* startingPoint = this->head) {
			for (;;) {
				if (startingPoint->Id == Id) {

					//cpy the tail to the starting point
					//set the tail to the handle before the tail
					std::memcpy(startingPoint->data, &this->tail->data, this->maxElementDataSize);
					startingPoint->Id = tail->Id;

					clearHandle(tail);
					print(std::to_string(IsHandleEmpty(tail)));

					tail = handleBeforeCurrentTail;

					break;
				}

				if (startingPoint->nextHandle == nullptr) ThrowError("Handle Not Found");

				handleBeforeCurrentTail = startingPoint;
				startingPoint = startingPoint->nextHandle;
			}
		}

		handleBeforeCurrentTail = nullptr;
		this->Update();

		return true;
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

	inline uint getUsage() {
		return this->usage;
	}

	inline T operator[](unsigned int Id) {

		FMemoryHandle* targetHandle = this->Get(Id);
		T* castedData = static_cast<T*>(targetHandle->data);

		return *castedData;
	}

};

#endif // Memory_h