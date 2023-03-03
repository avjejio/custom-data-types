#include <iostream>
#include "Vector.h"

using vector = Custom::Vector<int>;
namespace Custom {
	void VectorTest() {
		vector vec = { 5, 2, 7 };

		PrintVectorInfo(vec);
		vec.PushBack(9);
		PrintVectorInfo(vec);

		vector vec2;
		for (int i = 0; i < 50; ++i) {
			vec2.PushBack(i);
		}
		PrintVectorInfo(vec2);

		for (int i = 0; i < 5; ++i) {
			vec2.Pop();
		}

		vec2.Insert(17, 2);
		vec2.Insert(17, vec2.Size());

		PrintVectorInfo(vec2);

		vec2.RemoveItem(17);
		vec2.RemoveAt(0);
		vec2.RemoveAt(vec2.Size() - 1);

		PrintVectorInfo(vec2);

		vector vec3 = vec2;

		PrintVectorInfo(vec3);

		for (int i = 0; i < 39; ++i) {
			vec2.Pop();
		}

		vec2.PushBack(100);

		PrintVectorInfo(vec2);

		vec2[0] = 100;
		vec2.AtIndex(1) = 200;

		PrintVectorInfo(vec2);

		int sum = 0;
		for (int i = 0; i < vec2.Size(); ++i) {
			sum += vec2[i];
		}

		std::cout << sum << std::endl;

		vector vec4 = { 4 };
		PrintVectorInfo(vec4);
	}
}