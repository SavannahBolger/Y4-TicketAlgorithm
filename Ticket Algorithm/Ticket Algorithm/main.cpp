#include <iostream>

int main()
{
	int number = 1, next = 1, turn[1:n] = ([n] 0);

	process CS[i= 1 to n]
	{
		while (true)
		{
			< turn[i] = number; number = number + 1; >
			< await(turn[i] == next); >
			critical section;
			< next = next + 1; >
			noncritical section;
		} 
	}
}