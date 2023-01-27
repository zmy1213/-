#include<iostream>
#include<string>
#include<climits>
#include<cmath>
using namespace std;
char* ManacherString(string s)
{
	const char* str = s.c_str();
	char* res = new char[2 * s.length() + 1];
	int index = 0;
	for (int i = 0; i < 2*s.length()+1; i++)
	{
		res[i] = (i & 1) == 0?'#':s[index++];
	}
	return res;
}
void MaxLcpsLength(string s)
{
	if (s.length() == 0)
		return;
	int str_len = 2 * s.length() + 1;
	const char* str = new char[str_len];
	str = ManacherString(s);
	int* ArrStr = new int[str_len];
	int C = -1;
	int R = -1;
	int Max = INT_MIN;
	int Max_te = Max;
	int left = 0;
	int right = 0;
	for (int i = 0; i < str_len; i++)
	{
		ArrStr[i] = R > i ? min(ArrStr[2 * C - i], R - i):1;
		while(ArrStr[i] + i<str_len && i - ArrStr[i]>-1)
		{
			if (str[ArrStr[i] + i] == str[i - ArrStr[i]])
			{
				ArrStr[i]++;
			}
			else
			{
				break;
			}
			if (ArrStr[i] + i > R)
			{
				R = ArrStr[i] + i;
				C = i;
			}
			Max = max(Max, ArrStr[i]);
			if (Max != Max_te)
			{
				left = C - (R - C-2);
				right = R+1;
				Max_te = Max;
			}
		}
	}
	string res(Max-1,0);
	int index = 0;
	for (int i = left; i < left+right-left; i++)
	{
		cout << str[i] << " ";
		if(str[i]!='#')
			res[index++] = str[i];
	}
	cout << endl;
	for (int i = 0; i < Max-1; i++)
	{
		cout << res[i] << " ";
	}
}
int main()
{
	string s= "eabcb";
	MaxLcpsLength(s);
}
