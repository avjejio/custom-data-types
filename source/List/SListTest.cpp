#include <iostream>
#include "SList.h"

namespace Custom {
	template <std::regular T>
	void PrintSListInfo(SList<T>& slist) {
		std::cout << "Size is " << slist.Size() << std::endl;
		std::cout << "First is " << slist.GetFirst() << std::endl;
		std::cout << "Last is " << slist.GetLast() << std::endl;

		for (int i = 0; i < slist.Size(); ++i) {
			std::cout << slist.GetVal(i) << " ";
		}
		std::cout << std::endl << std::endl;
	}

	void SListTest() {
		SList<int> slist;
		slist.PushFront(5);
		slist.PushFront(4);

		PrintSListInfo(slist);

		slist.Insert(9, 2);
		slist.Insert(1, 0);
		slist.Insert(7, 2);

		PrintSListInfo(slist);

		for (int i = 1; i < 6; ++i) {
			slist.PushFront(i * 10);
		}

		PrintSListInfo(slist);

		slist.PopFront();
		slist.PopFront();

		PrintSListInfo(slist);

		slist.RemoveItem(7);
		slist.RemoveItem(1);
		slist.RemoveAt(2);
		slist.Insert(1000, 5);

		PrintSListInfo(slist);
	}
}