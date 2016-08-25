#include "List.h"

int main() {

#ifndef _OJ_
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif // !_OJ_

	List<char> list1;
	ListNode<char> *p;
	char buffer;
	int opNum, numBuffer;

	// get list
	while (std::cin.get(buffer)) {
		if (buffer == '\n')
			break;
		list1.push_back(buffer);
	}

	// get op num
	std::cin >> opNum;
	for (int i = 0; i < opNum; ++i) {
		std::cin >> numBuffer >> buffer;
		p = list1.insert(buffer, numBuffer);
		list1.de3duplicate(p);
		list1.show_result();
	}

#ifndef _OJ_
	fclose(stdin);
	fclose(stdout);
#endif // !_OJ_

	return 0;
}
