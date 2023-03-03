#pragma once

#include <stdexcept>
#include <concepts>

namespace Custom {
	template <std::regular T>
	class SList {
	public:
		SList() : size(0), first(nullptr), last(nullptr) {}
		SList(const SList&) = delete; // will not implement because it's not interesting
		~SList();

		SList& operator=(const SList&) = delete; // same

		int Size() const { return size; }
		bool IsEmpty() const { return (size == 0); }

		T& GetVal(int index);
		void PushFront(const T& item);
		void PopFront();
		void Insert(const T& item, int index);
		void RemoveItem(const T& item);
		void RemoveAt(int index);

		T& GetFirst() { return first->item; }
		T& GetLast() { return last->item; }

	private:
		int size;

		struct SListNode;
		SListNode* first;
		SListNode* last;


		struct SListNode {
			SListNode(const T& i, SListNode* n = nullptr) : item(i), next(n) {}
			T item;
			SListNode* next;
		};
	};

	// Test declaration
	void SListTest();


	// SList definitions

	template <std::regular T>
	SList<T>::~SList() {
		SListNode* prev = first;
		SListNode* current = first->next;

		while (current != nullptr) {
			delete prev;
			prev = current;
			current = current->next;
		}
		delete prev;
	}

	template <std::regular T>
	T& SList<T>::GetVal(int index) {
		if (index < 0 || index >= size) {
			throw std::out_of_range("SList<T>::GetVal(int index) : Out of range");
		}
		if (size == 0) {
			throw std::exception("SList<T>::GetVal(int index) : List is empty");
		}

		SListNode* temp = first;
		for (int i = 0; i < index; ++i) {
			temp = temp->next;
		}
		return temp->item;
	}

	template <std::regular T>
	void SList<T>::PushFront(const T& item) {
		SListNode* temp = new SListNode(item, first);
		first = temp;
		if (last == nullptr) {
			last = temp;
		}
		++size;
	}

	template <std::regular T>
	void SList<T>::PopFront() {
		if (first == nullptr) {
			return;
		}
		SListNode* temp = first;
		first = first->next;
		delete temp;
		--size;
	}

	template <std::regular T>
	void SList<T>::Insert(const T& item, int index) {
		if (index < 0 || index > size) {
			throw std::out_of_range("SList<T>::GetVal(int index) : Out of range");
		}
		if (index == 0) {
			PushFront(item);
			return;
		}

		SListNode* temp = new SListNode(item);


		SListNode* prev = first;
		for (int i = 0; i < index - 1; ++i) { // get previous node
			prev = prev->next;
		}

		temp->next = prev->next;
		prev->next = temp;

		if (index == size) {
			last = temp;
		}
		++size;
	}

	template <std::regular T>
	void SList<T>::RemoveItem(const T& item) {
		SListNode* temp;
		int count = 0;
		for (temp = first; temp != nullptr; temp = temp->next) {
			if (temp->item == item) {
				RemoveAt(count); // i know this isn't a way to do it but i really don't care
				return;
			}
			++count;
		}
	}

	template <std::regular T>
	void SList<T>::RemoveAt(int index) {
		if (index < 0 || index >= size) {
			return;
		}

		SListNode* prev = first;
		for (int i = 0; i < index - 1; ++i) { // get prev
			prev = prev->next;
		}
		SListNode* temp = prev->next;
		prev->next = temp->next;
		delete temp;
		--size;
	}
}