#include<iostream>
#include<string>
using namespace std;
int* getNextArray(const char* s,int length);
int Kmp(string s,string m)
{
	if (s.empty() || m.empty() || m.length() < 1 || s.length() < 1)
	{
		const char* str1 = s.c_str();
		const char* str2 = m.c_str();
		int i1 = 0;
		int i2 = 0;
		int* next = getNextArray(str2,m.length());
		while (i1 < s.length() && i2 < m.length())
		{
			if (str1[i1] == str2[i2])//相等的时候都相加
			{
				i1++;
				i2++;
			}
			else if (next[i2] == -1)
			{
				i1++;
			}
			else
			{
				i2 = next[i2];
			}
		}
		return i2 == m.length() ? i1 - i2 : -1;
	}
}
int* getNextArray(const char* ms,int length)
{
	if (length == 1)
	{
		int* res = new int(-1);
		return res;
	}
	int* next = new int[length];
	next[0] = -1;
	next[1] = 1;  
	int i = 2;
	int cn = 0;
	while (i < length)
	{
		if (ms[i - 1] == ms[cn])
		{
			next[i++] = ++cn;
		}
		else if (cn > 0)
		{
			cn = next[cn];
		}
		else
		{
			next[i++] = 0;
		}
	}
	return next;
}
int main()
{
	return 0;
}
