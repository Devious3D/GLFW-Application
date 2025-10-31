#pragma once  
#if Memory_h == 0 
#define Memory_h 1

#include <cassert>

template<typename t>
struct vector;

struct FMemoryHandle {

	int position;
	void* data = nullptr;
	FMemoryHandle* nextHandle = nullptr;
};

template <typename T>
class CMemoryHandler {


private:

	FMemoryHandle* head = nullptr;
	FMemoryHandle* tail = nullptr;

	int usage = 0;
	int capacity = 0;
	int maxElements = 0;
	int activeElements = 0;

	size_t maxElementDataSize = 0;
	size_t maxMemoryHandleSize = 0;

	void Update() {

		FMemoryHandle* startingPoint = this->head;
		if (startingPoint == nullptr) { return; }
		
		int newestUsage = 0;
		int positionCount = 0;
		int newestActiveElementCount = 0;

		for (;;) {

			newestUsage += sizeof(startingPoint);
			
			//
			if (startingPoint->data != nullptr) {
				newestActiveElementCount++;
			}

			startingPoint->position = positionCount;
			positionCount++;


			if (startingPoint->nextHandle == nullptr) break;
 			startingPoint = startingPoint->nextHandle;
		}

		this->usage = newestUsage;
		this->activeElements = newestActiveElementCount;
	}

public:

	CMemoryHandler() {}
	~CMemoryHandler() {}

	void Init(int cap, int maxEle) {
		
		this->capacity = cap;
		this->maxElements = maxEle;
		this->maxElementDataSize = sizeof(T);
		this->maxMemoryHandleSize = sizeof(FMemoryHandle) + this->maxElementDataSize;


		//Change the handles to exsist on the stack
		//Keep the data ptrs in the heap 

		for (int i = 0; i < maxEle; i++) {

			FMemoryHandle* newHandle = new FMemoryHandle;

			bool isHeadValid = (this->head == nullptr);
			switch (isHeadValid) {

			case true:
			{
				head = newHandle;
				tail = newHandle;
			}
			break;

			case false:
				FMemoryHandle* startingPoint = this->head;
				if (startingPoint == nullptr) { return; }

				for (;;) {

					if (startingPoint->nextHandle == nullptr) {
						startingPoint->nextHandle = newHandle;
						this->tail = newHandle;
						break;
					}

					startingPoint = startingPoint->nextHandle;
				}
				break;
			}
		}

		this->Update();
	}
	virtual void Insert(T* data, int position) {
		if (position + 1 > this->maxElements) {
			Engine::ThrowError("Position out of scope");
		}

		if (FMemoryHandle* targetHandle = this->Get(position)) {
			targetHandle->data = data;
		}

		this->Update();
	}

	virtual FMemoryHandle* Get(int position)
	{
		if (position + 1 > this->maxElements) {
			Engine::ThrowError("Position out of scope");
		}

		FMemoryHandle* startingPoint = this->head;
		if (startingPoint == nullptr) Engine::print("Memory(Get func): starting point is nullptr");

		for (;;) {

			if (startingPoint->position == position) break;
			startingPoint = startingPoint->nextHandle;
		}

		return startingPoint;
	}


	virtual void Remove(int position) {
		if (position + 1 > this->maxElements) {
			Engine::ThrowError("Position out of scope");
		}

		FMemoryHandle* startingPoint = this->head;

		for (;;) {
			if (startingPoint->position == position) {
				std::free(startingPoint->data);
				break;
			}

			startingPoint = startingPoint->nextHandle;
		}
	}

	inline T operator[](int position) {
		if (position + 1 > this->maxElements) {
			Engine::ThrowError("Position out of scope");
		}

		FMemoryHandle* targetHandle = this->Get(position);
		if (targetHandle->data == nullptr) {
			//Engine::ThrowError(("No data at position %s", position));
		}
		
		
		T* castedData = cast<T*>(targetHandle->data);

		return *castedData;
	}

};

#endif