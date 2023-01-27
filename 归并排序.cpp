#include<iostream>
#include<algorithm>
using namespace std;

void merge(int* data, int start, int end, int* result)
{
    int left_length = (end - start + 1) / 2 + 1;
    int left_index = start;
    int result_index = start;
    int right_index = start + left_length;
    while (left_index < start + left_length && right_index < end + 1)
    {
        if (data[left_index] <= data[right_index])
            result[result_index++] = data[left_index++];
        else
            result[result_index++] = data[right_index++];
    }

    while (left_index < start + left_length)
    {
        result[result_index++] = data[left_index++];
    }
    while (right_index < end + 1)
    {
        result[result_index++] = data[right_index++];
    }
}
void Merge_sort(int* data, int left, int right, int* result)
{
    if (right - left == 1)
    {
        if (data[right] < data[left])
        {
            int temp = data[right];
            data[right] = data[left];
            data[left] = temp;
        }
        return;
    }
    else if (right == left)
    {
        return;
    }
    else
    {
        Merge_sort(data, left, (right - left + 1) / 2 + left, result);
        Merge_sort(data, (right - left + 1) / 2 + 1 + left, right, result);
        merge(data, left, right, result);
        for (int i = left; i <= right; i++)
        {
            data[i] = result[i];
        }
    }
}
//example
int main()
{
    int data[] = { 5,3,6,7,3,2,7,9,8,6,34,32,5,4,43,12,37 };
    const int length = 17;
    int result[length];
    cout << "before sorted:" << '\n';
    for (int i = 0; i < length; i++)
        cout << data[i] << ' ';
    cout << '\n'
        << "after sorted:" << '\n';
    Merge_sort(data, 0, length - 1, result);
    for (int i = 0; i < length; i++)
        cout << result[i] << ' ';
    return 0;
}
