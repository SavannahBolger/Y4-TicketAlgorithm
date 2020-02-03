#include <iostream>
#include "SFML/Graphics.hpp"
#include <thread>
#include <chrono>
#include <mutex>
//for thread safe multithreading
#include <atomic>

struct Vector2
{
	float x;
	float y;
};

const int n = 5;
static int counter = 0;
std::atomic<int> next = 1;
std::atomic<int> number = 1;
std::atomic<int> turn[n];
std::mutex m_lock;
Vector2 playerPosition;

void process()
{
	counter = counter + 1;
	int i = counter; 
	
	while (i < n)
	{
		//ticket
		turn[i] = number++;
		
		m_lock.lock();
		std::cout << "Thread: " << counter << "\nTurn:" << turn[i] << std::endl;
		//wait
		std::this_thread::sleep_for(std::chrono::seconds(1));
		m_lock.unlock();

		if (turn[i] == next)
		{
			playerPosition = Vector2{ (float)number, (float)number };
			next = next + 1;
		}
		
		//critical section
		m_lock.lock();
		std::cout << "Player Position: {" << playerPosition.x << ", " << playerPosition.y << "}\nNext:" << next << std::endl;
		std::this_thread::sleep_for(std::chrono::seconds(1));
		m_lock.unlock();
	}
}

int main(void)
{
	Vector2 playerPosition = { 0,0 };
	
	for (int i = 0; i < n; i++)
	{
		turn[i] = 0;
	}

	//thread processes
	std::thread t1(process);
	std::thread t2(process);
	std::thread t3(process);
	std::thread t4(process);

	t1.join();
	t2.join();
	std::cin.get();
}