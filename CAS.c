int compare_and_swap(int* ptr, int oldValue, int newValue)
{
    int temp = *ptr;
    if (temp == oldValue) {
        *ptr = newValue;
    }
    return temp;
}