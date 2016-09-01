#include <iostream>
#include "Eval.h"

int main() {
	std::string eval_s, RPN;
	float result;

	while (std::cin >> eval_s) {
		if (eval_s.c_str() == "q" || eval_s.c_str() == "Q")
			break;
		else {
			result = eval(eval_s, RPN);
			std::cout << "Result:\t" << result << std::endl
				<< "RPN:\t" << RPN << std::endl;
		}
	}
	return 0;
}
