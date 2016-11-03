#include <iostream>
#include <random>
#include <time.h>
#include <chrono>

using namespace std;



void randomProblem()
{
	const int upper_bound = 100;
	const int lower_bound = 1;

	time_t system_time = time(0);
	default_random_engine e(system_time);
	uniform_int_distribution<int> u(lower_bound, upper_bound);

	cout 	<< '#' << '\t' << "system time" << endl
			<< "-------------------" << endl;

	for (int counter = 1; counter <= 5; counter++)
	{
		int secret = u(e);
		cout << secret << '\t' << system_time << endl;
	}

	system("pause");
}


void randomProblem2()
{
	const int upper_bound = 100;
	const int lower_bound = 1;

	auto t = std::chrono::high_resolution_clock::now().time_since_epoch().count();
	std::mt19937 e;
	e.seed(static_cast<unsigned int>(t));	//seed engine with timed value
	std::uniform_int_distribution<int> u(lower_bound, upper_bound);

	cout 	<< '#' << '\t' << "system time" << endl
			<< "-------------------" << endl;

	for (int counter = 1; counter <= 5; counter++)
	{
		int secret = u(e);
		cout << secret << '\t' << t << endl;
	}

	system("pause");
}



int main()
{
	randomProblem();

	return 0;
}