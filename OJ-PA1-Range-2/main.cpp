#include <iostream>

int main(int argc, char *argv[]) {
#ifndef _OJ_
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif // !_OJ_

	int length, que_num, _begin, _end, _count;
	std::cin >> length >> que_num;

	int *data = new int[length];
	for (int idx = 0; idx < length; ++idx)
		std::cin >> data[idx];

	for (int i = 0; i < que_num; ++i) {
		_count = 0;
		std::cin >> _begin >> _end;
		for (int idx = 0; idx < length; ++idx) {
			if ((_begin <= data[idx]) && (data[idx] <= _end))
				++_count;
		}
		std::cout << _count << std::endl;
	}

	delete[] data;
#ifndef _OJ_
	fclose(stdin);
	fclose(stdout);
#endif // !_OJ_

	return 0;
}