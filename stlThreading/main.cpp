//
#include <iostream>
#include <thread>
//
auto my_thread() {
	//
	std::cout << "Thread ID: " << std::this_thread::get_id() << std::endl;
	//
	std::cout << "Sleep for 1 second: " << std::endl;
	std::this_thread::sleep_for(std::chrono::seconds{ 1 });
}
//
auto main() -> int {
	//
	std::cout << "Thread (main) ID: " << std::this_thread::get_id() << std::endl;
	//
	{
		auto t1 = std::thread{ my_thread };
		t1.join();
	}
	//
	return 0;
}