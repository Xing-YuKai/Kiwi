//
// Created by kiwi on 19-1-5.
//
#include <chrono>
#include "../Kiwi/ThreadPool/ThreadPool.h"

using namespace std;

struct F1
{
	void operator()(int flag)
	{
		cout << flag << endl;
		this_thread::sleep_for(chrono::milliseconds(300));
		cout << flag << endl;
	}
};

void F2(int flag)
{
	cout << flag << endl;
	this_thread::sleep_for(chrono::milliseconds(300));
	cout << flag << endl;
}

class A
{
public:
	static void F4(int flag)
	{
		cout << flag << endl;
		this_thread::sleep_for(chrono::milliseconds(300));
		cout << flag << endl;
	}
};

int main()
{
	{
		A f4;
		F1 f1;
		auto f3 = [](int flag)
		{
			cout << flag << endl;
			this_thread::sleep_for(chrono::milliseconds(300));
			cout << flag << endl;
		};

		Kiwi::ThreadPool tp(4);
		tp.commit(f1, 1);
		tp.commit(F2, 2);
		tp.increase_pool(2);
		tp.commit(f3, 3);
		tp.commit(f1, 4);
		tp.commit(f3, 5);
		tp.decrease_pool(5);
		tp.commit(F2, 6);
		tp.commit(f4.F4,8);
		auto fu = tp.commit(f3, 7);
		fu.get();
	}
	cout << "destructed";
	return 0;
}
