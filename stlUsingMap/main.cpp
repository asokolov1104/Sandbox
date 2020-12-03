//
#include <iostream>
#include <map>
#include <functional>
//
int sum(int a, int b) { return a + b; }
int sub(int a, int b) { return a - b; }
//
auto main() -> int {
	//
	if(false)
	{
		std::map<char, int (*) (int, int)> op;
		op['+'] = sum;
		op['-'] = sub;

		int x, y;
		char c;
		std::cin >> x >> y >> c;
		//std::cout << op[c](x, y) << std::endl;	//	exeception occur if 'c' not in map
		auto it = op.find(c);
		if(it != op.end())
			std::cout << it->second(x, y) << std::endl;

	}
	//
	if (true)
	{
		std::map<char, std::function<int(int, int)>> op;
		op['+'] = [](int a, int b) { return a + b; };
		op['-'] = [](int a, int b) { return a - b; };

		int x, y;
		char c;
		std::cin >> x >> y >> c;
		std::cout << op[c](x, y) << std::endl;	//	exeception occur if 'c' not in map
		//	catch std::bad_function_call

	}
	//
	return 0;
}