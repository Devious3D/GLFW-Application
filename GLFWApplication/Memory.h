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
		int newestElementcount = 0;

		for (;;) {

			newestUsage += sizeof(startingPoint);

			startingPoint->position = newestElementcount;
			newestElementcount++;


			if (startingPoint->nextHandle == nullptr) break;
			startingPoint = startingPoint->nextHandle;
		}

		this->usage = newestUsage;
		this->activeElements = newestElementcount;
	}

public:

	CMemoryHandler() {}
	~CMemoryHandler() {}

	void Init(int cap, int maxEle) {
		
		this->capacity = cap;
		this->maxElements = maxEle;
		this->maxElementDataSize = sizeof(T);
		this->maxMemoryHandleSize = sizeof(FMemoryHandle) + this->maxElementDataSize;

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
	virtual void Insert(T data, int position) {
		assert((this->activeElements + 1) > this->maxElements);
		//assert if the this next index is out of scope
		//Copy the bytes in the handle
		//Update
		
		if (FMemoryHandle* targetHandle = this->Get(position)) {
			memcpy(targetHandle->data, &data, this->maxMemoryHandleSize);
			Engine::print(Engine::FString("Memory.h"));
		}

		this->Update();
	}

	virtual FMemoryHandle* Get(int position)
	{
		assert(position > this->maxElements);

		FMemoryHandle* startingPoint = this->head;
		if (startingPoint == nullptr) Engine::print("Memory(Get func): starting point is nullptr");

		for (;;) {

			if (startingPoint->position == position) break;

			startingPoint = startingPoint->nextHandle;
		}

		return startingPoint;
	}


	virtual void Remove(int position) {

	}

	inline T operator[](int position) {

		Engine::print(position);
		return sizeof(T);
	}

};

#endif


