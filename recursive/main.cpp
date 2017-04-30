#include <iostream>

using namespace std;

typedef unsigned long u64;
typedef unsigned int u32;

u64 fib_func1(u64 n)
{
	if (n==1||n==2)
		return 1;
	else
		return fib_func1(n-1)+fib_func1(n-2);
}
u64 fib_func(u64 n)
{
	return fib1+fib2	
} 
int main(int argc, char** argv) {
	u64 result=0;
	u32 index=0;
	 
	for (index=1;index<50;index++)
	{
		result = fib_func1(index);
		cout << "the "<<index<<"th of the fib array is: "<<result<<endl; 
	} 
	return 0;
}
