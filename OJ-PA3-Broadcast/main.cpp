#include <cstdlib>
#include <iostream>

int main() {
#ifndef _OJ_
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif // !_OJ_

	size_t num_town, num_edge, town_a, town_b, town_frist = 1, town_buffer, i, j;
	bool valid_map = true;

	std::cin >> num_town >> num_edge;

	bool **adjMat = new bool*[num_town];
	for (i = 0; i < num_town; ++i) {
		adjMat[i] = new bool[num_town];
		for (j = 0; j < num_town; ++j)
			adjMat[i][j] = false;
	}
	for (i = 0; i < num_edge; ++i) {
		std::cin >> town_a >> town_b;  town_a -= 1;  town_b -= 1;  // idx start with 1
		town_buffer = (town_a < town_b ? town_a : town_b);
		town_frist = (town_frist < town_buffer ? town_frist : town_buffer);
		adjMat[town_a][town_b] = adjMat[town_b][town_a] = true;
	}

	// start BFS
	size_t *buffer = new size_t[num_town];  // head buffer in BFS
	size_t *town_statu = new size_t[num_town];  // 0:untouch, 1:found, 2:visited
	size_t buffer_trail = 0, buffer_head = 0;
	// initlize town_statu:
	for (i = 0; i < num_town; ++i)
		town_statu[i] = 0;
	// start with first town:
	bool *head_town = adjMat[town_frist];  town_statu[town_frist] = 1;
	for (i = 0; i < num_town; ++i) {
		if (head_town[i] == true) {
			buffer[buffer_trail++] = i;
		}
	}
	// BFS each town:
	while (buffer_head != buffer_trail) {
		size_t head_idx = buffer[buffer_head++];
		bool *trail_town = adjMat[head_idx];
		for (i = 0; i < num_town; ++i) {
			if (trail_town[i] == true) {
				if (town_statu[i] == 2) {
					valid_map = false;
					break;
				}
				buffer[buffer_trail++] = i;
				town_statu[i] = 1;
			}
		}
		town_statu[head_idx] = 2;
		if (valid_map == false)
			break;
	}
	
	if (valid_map == false)
		std::cout << -1;
	else
		std::cout << 1;

	// clean mem:
	for (i = 0; i < num_town; ++i)
		delete[] adjMat[i];
	delete[] buffer, town_statu, adjMat;

#ifndef _OJ_
	fclose(stdin);
	fclose(stdout);
#endif // !_OJ_

	return 0;
}