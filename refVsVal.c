#include <stdio.h>

/*
    Runnable example of passing by reference vs passing by value.
*/

void add_byRef(int x, int y, int* result)
{
    *result = x+y;
}

int add_byVal(int x, int y)
{
    return x+y;
}

int main()
{
    int x=6, y=4, z=0;

    z = add_byVal(x,y);
    printf("%d\n", z);

    // & is called referencing, and passes a pointer.
    add_byRef(x,y,&z);
    printf("%d\n", z);

}