#include "Stack.h"
#ifndef _OJ_
#include <cstdlib>
#endif // !_OJ_

int main() {
#ifndef _OJ_
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif // !_OJ_

	Stack<int> S_Train;
	Queene<bool> S_op;  // True for push, False for pop

	int lenTrain, lenStack; 
	bool buffer;

	std::cin >> lenTrain >> lenStack;
	int *trainOut = new int[lenTrain];
	for (int i = 0; i < lenTrain; ++i)
		std::cin >> trainOut[i];

	// start simulate
	S_Train.push_back(1);
	S_op.push_back(true);
	int out_idx = 0, in_idx = 1;
	while ((in_idx <= lenTrain) && (S_Train.size() <= lenStack)) {
		if (S_Train.top() != trainOut[out_idx]) {  // not this train
			S_Train.push_back(++in_idx);
			S_op.push_back(true);
		} else {  // get the train out!
			S_Train.pop();
			S_op.push_back(false);
			++out_idx;
		}
	}
	// finish simulate
	if (S_Train.size())  // simulate failed
		std::cout << "No" << std::endl;
	else {
		while (buffer = S_op.pop()) {
			// True for push, False for pop
			if (buffer)
				std::cout << "push" << std::endl;
			else
				std::cout << "pop" << std::endl;
		}
	}

	delete[] trainOut;
#ifndef _OJ_
	fclose(stdin);
	fclose(stdout);
#endif // !_OJ_

	return 0;
}
