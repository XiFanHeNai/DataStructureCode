#include <iostream>
#include <vector>
#include <stdio.h>
 
using namespace std;

typedef  long long i64;
typedef  int i32;

i64 func_1 (vector <int> &a) 
{
	i32 i,j,k;
	i64 temp_sum=0,result=0;
	for (i=0;i<a.size();i++)
	{
		for (j=i;j<a.size();j++)
		{
			temp_sum=0;
			for (k=i;k<=j;k++)
				temp_sum += a[k];
			if (temp_sum >= result)
				result = temp_sum;
			printf("i=%d,j=%d,k=%d,temp_sum=%d,result=%d \n",i,j,k,temp_sum,result);
				
		}
	}
	return result;
}

i64 func_2 (vector <int> &a) 
{
	i32 i,j;
	i64 temp_sum=0,result=0;
	for (i=0;i<a.size();i++)
	{
		temp_sum=0;
		for (j=i;j<a.size();j++)
		{
			temp_sum += a[j];
			if (temp_sum >= result)
				result = temp_sum;
			printf("i=%d,j=%d,temp_sum=%d,result=%d \n",i,j,temp_sum,result);
				
		}
	}
	return result;
}



int main(int argc, char** argv) {
	int a[]={4,-3,5,-2,-1,2,6,-2};
	vector<int> t(a,a+sizeof(a)/sizeof(a[0]));
	vector<int> &s=t;
	i64 result = func_1(s);
	cout << "the first function result is :"<< result << endl;
	result = func_2(s);
	cout << "the first function result is :"<< result << endl;
	return 0;
}
