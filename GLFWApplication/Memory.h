#pragma once
#if Memory_h == 0 
#define Memory_h 1

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

	int activeElements = 0;

	int usage = 0;
	int capacity = 0;
	int maxElements = 0;

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
	virtual void Insert(T data) {

		Engine::print("Trying To insert");

	}

	virtual void Remove(int position) {

	}

	inline T operator[](int position) {

		Engine::print(position);
		return sizeof(T);
	}

};

#endif


