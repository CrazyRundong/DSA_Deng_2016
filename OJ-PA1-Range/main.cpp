#include <iostream>
#include "Vector.h"

int main(int argc, char *argv[]) {
	// get first ine
	int length, que_num, idxBegin, idxEnd, answer;
	float buffer, begin, end;
	std::cin >> length >> que_num;

	// get x-axis
	Vector<float> x_axis;
	Vector<int> answers;
	for (int i = 0; i < length; ++i) {
		std::cin >> buffer;
		x_axis.push_back(buffer);
	}
	x_axis.sort(0, x_axis.size());

	// test: print
	/*std::cout << "length: " << length
		<< "  que_num: " << que_num << std::endl;
	x_axis.print_all();*/

	// get solution
	for (int i = 0; i < que_num; ++i) {
		std::cin >> begin >> end;
		idxBegin = x_axis.search(begin);
		idxEnd = x_axis.search(end);
		// test: print
		/*std::cout << "Begin_idx:" << begin << "_" << idxBegin
			<< "  End_idx: " << end << "_" << idxEnd << std::endl;*/
		answer = idxEnd - idxBegin - 1;
		if (x_axis[idxBegin] == begin)
			++answer;
		if (x_axis[idxEnd] == end)
			++answer;
		answers.push_back(answer);
	}

	// print
	answers.print_all();

	return 0;
}