/*
读旧值
if 旧值==真旧值 设新值
返旧值
*/
int compare_and_swap(int* ptr, int oldValue, int newValue)
{
    int temp = *ptr;
    if (temp == oldValue) {
        *ptr = newValue;
    }
    return temp;
}