#pragma once

// I am not sure if it's efficient,
// Probably would be better to use T** array
// But I can't say for now,
// Maybe will implement version with pointers array later


#include <initializer_list>
#include <stdexcept>

namespace Custom {
	template <typename T> class Vector {
	public:
		Vector();
		Vector(const Vector&);
		Vector(std::initializer_list<T>);
		~Vector();
		Vector& operator=(const Vector&) = delete;

		int Size() const { return size; }
		int Capacity() const { return capacity - 1; } // -1 because we need empty space for End()
		bool IsEmpty() const { size == 0 ? true : false; }

		T& AtIndex(int index) const;
		T& operator[](int index) const;
		void Insert(const T& item, int index);
		void PushBack(const T& item);
		void Pop();
		void RemoveItem(const T& item);
		void RemoveAt(int index);
		int FindItem(const T& item);

		T* Begin() { return array[0]; }
		T* End() { return array[size]; }
		

	private:
		void AddCapacity();
		void SubtractCapacity();
		int CalculateCapacity(int);
		void Resize();

		int size;
		int capacity;
		T* array;
	};


	// Non-class function declarations //

	template <typename T>
	void PrintVectorInfo(const Vector<T>& v);

	void VectorTest();


	// Vector<T> definitions //

	template <typename T>
	Vector<T>::Vector() :
		size{ 0 },
		capacity{ 1 },
		array{ new T [1] }
	{}

	template <typename T>
	Vector<T>::Vector(const Vector& other) :
		size{ other.size },
		capacity{ CalculateCapacity(size + 1) },
		array{ new T[capacity] }
	{
		for (int i = 0; i < size; ++i) {
			*(array + i) = *(other.array + i);
		}
	}

	template <typename T>
	Vector<T>::Vector(std::initializer_list<T> list) :
		size{ (int) list.size() },
		capacity{ CalculateCapacity(size + 1)},
		array{ new T[capacity] }
	{
		int i = 0;
		for (auto iterator = list.begin(); iterator < list.end(); ++iterator) {
			array[i] = *iterator;
			++i;
		}
	}

	template <typename T>
	Vector<T>::~Vector() {
		delete[] array;
	}

	template <typename T>
	T& Vector<T>::AtIndex(int index) const {
		if (index < 0 || index >= size) {
			throw std::out_of_range("Vector<T>::AtIndex(int) : Out of range");
		}
		return *(array + index);
	}

	template <typename T>
	T& Vector<T>::operator[](int index) const {
		if (index < 0 || index >= size) {
			throw std::out_of_range("Vector<T>::operator[](int) : Out of range");
		}
		return array[index];
	}

	template <typename T>
	void Vector<T>::Insert(const T& item, int index) {

		if (index < 0 || index > size) {
			throw std::out_of_range("Vector<T>::Insert(const T&, int) : Index out of range");
		}
		if (size + 2 > capacity) { // Here (size + 2) for new item and End()
			AddCapacity();
			Resize();
		}
		for (int i = size - 1; i >= index; --i) {
			array[i + 1] = array[i];
		}
		array[index] = item;
		++size;
	}

	template <typename T>
	void Vector<T>::PushBack(const T& item) {
		if (size + 2 > capacity) {
			AddCapacity();
			Resize();
		}
		array[size] = item;
		++size;
	}

	template <typename T>
	void Vector<T>::Pop() {
		if (size <= 0) {
			throw std::exception("Vector<T>::Pop() : Vector is empty");
		}
		array[size - 1] = 0;
		--size;

		if (capacity / size >= 4) {
			SubtractCapacity();
			Resize();
		}
	}

	template <typename T>
	void Vector<T>::RemoveItem(const T& item) {
		for (int i = 0; i < size; ++i) {
			if (array[i] == item) {
				RemoveAt(i);
				return;
			}
		}
	}

	template <typename T>
	void Vector<T>::RemoveAt(int index) {
		for (int i = index; i < size - 1; ++i) {
			array[i] = array[i + 1];
		}
		array[size - 1] = 0;
		--size;

		if (capacity / size >= 4) {
			SubtractCapacity();
			Resize();
		}
	}

	template <typename T>
	int Vector<T>::FindItem(const T& item) {
		for (int i = 0; i < size; ++i) {
			if (item == array[i]) {
				return i;
			}
		}
		return -1;
	}

	template <typename T>
	inline void Vector<T>::AddCapacity() {
		capacity *= 2;
	}

	template<typename T>
	inline void Vector<T>::SubtractCapacity() {
		capacity /= 2;
	}

	template <typename T>
	inline int Vector<T>::CalculateCapacity(int size) {
		int i = 1;
		for (; i < size; i *= 2);
		return i;
	}

	template <typename T>
	void Vector<T>::Resize() {
		T* temp = new T[capacity];
		for (int i = 0; i < size; ++i) {
			temp[i] = array[i];
		}
		delete[] array;
		array = temp;
	}


	// Non-class function definitions

	template <typename T>
	void PrintVectorInfo(const Vector<T>& v) {
		std::cout << "Vector: ";
		for (int i = 0; i < v.Size(); ++i) {
			std::cout << v[i] << " ";
		}
		std::endl(std::cout);

		std::cout << "Size: " << v.Size() << std::endl;
		std::cout << "Capacity " << v.Capacity() << std::endl;
		std::endl(std::cout);
	}
}
