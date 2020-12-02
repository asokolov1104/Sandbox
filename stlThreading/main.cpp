//
#include <iostream>
#include <thread>
#include <mutex>
//
//	defered locks example
struct glAccount {
	int iBalance = 0;
	glAccount() {}
	glAccount(int n) : iBalance(n) {}
	std::mutex mut_;
};

glAccount account1(50500), account2;

void transfer_money(glAccount& ac_from, glAccount& ac_to, int amount) {
	auto lock1 = std::unique_lock<std::mutex>{ ac_from.mut_, std::defer_lock };
	auto lock2 = std::unique_lock<std::mutex>{ ac_to.mut_, std::defer_lock };

	std::lock(lock1, lock2);

	ac_from.iBalance -= amount;
	ac_to.iBalance += amount;
}

auto thread_transfer(int amount) {
	for (int i = 0; i < amount; ++i) {
		transfer_money(account1, account2, 1);
	}
}

//
auto glCounter = 0;
std::mutex glCounter_mutex;//auto glCounter_mutex = std::mutex();
//
auto thr_increment(int n) {
	//
	std::thread::id thread_id = std::this_thread::get_id();
	std::cout << "Thread ID: " << thread_id << " started " << std::endl;
	//
	for (int i = 0; i < n; ++i) {
		std::lock_guard<std::mutex> guard(glCounter_mutex);	//	RAII class template for handling locking
		glCounter++;		//	this line of code is critical section
	}
	//
	std::cout << "Thread ID: " << thread_id << " finished " << std::endl;
}
//
auto my_thread() {
	//
	std::thread::id thread_id = std::this_thread::get_id();
	std::cout << "Thread ID: " << thread_id << " started " <<std::endl;
	//
	std::cout << "Hardware concurrency: "<< std::thread::hardware_concurrency() << std::endl;
	//
	std::cout << "Sleep for 1 second: " << std::endl;
	std::this_thread::sleep_for(std::chrono::seconds{ 1 });
	//
	std::cout << "Thread ID: " << thread_id << " finished " << std::endl;
}
//
auto main() -> int {
	//
	std::cout << "Thread (main) ID: " << std::this_thread::get_id() << " started " << std::endl;
	//	defered locks example
	{
		std::cout << "Account 1 : " << account1.iBalance << " before" << std::endl;
		std::cout << "Account 2 : " << account2.iBalance << " before" << std::endl;

		auto t1 = std::thread{ thread_transfer, 10000 };
		auto t2 = std::thread{ thread_transfer, 10000 };
		auto t3 = std::thread{ thread_transfer, 10000 };
		t1.join();
		t2.join();
		t3.join();

		std::cout << "Account 1 : " << account1.iBalance << " after" << std::endl;
		std::cout << "Account 2 : " << account2.iBalance << " after" << std::endl;
	}
	//	mutex example
	if(false)
	{
		constexpr auto n_times = int{ 100000 };	// one hundred thousand
		auto t1 = std::thread{ thr_increment, n_times };
		auto t2 = std::thread{ thr_increment, n_times };
		auto t3 = std::thread{ thr_increment, n_times };

		t1.join();
		t2.join();
		t3.join();

		std::cout << "Counter : " << glCounter << std::endl;
	}
	//
	if(false)
	{
		auto t1 = std::thread{ my_thread };
		t1.detach();//t1.join();
	}
	//
	std::cout << "Thread (main) ID: " << std::this_thread::get_id() << " finished " << std::endl;
	//
	//std::this_thread::sleep_for(std::chrono::seconds{ 5 });
	return 0;
}