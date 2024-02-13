# Struct Pointers

In `code.c` you can see an example of a program which is using a struct pointer to pass around the `image1` struct between different functions.

You can use the makefile to compile this, and run the executable `pgmCheck`. Two pgm files have been provided for this.

# What is a struct pointer?

A pointer to an instance of a struct.

A struct is a special sort of variable in C, and like any other variable you can create a pointer to them. This allows us to **pass by reference** into a function.

## By Reference vs By Value

When we use arguments in a function, we are either passing in a value by reference or by value.

### By Value

We pass by value when we just want to use the current value of the variable inside of a function, and don't intend to edit it in any way.

### By Reference

If we want to change the value stored inside the variable, then we need to pass it by **reference** - which we do by passing in a pointer.

## Example - By Ref / By Val

Provided below, runnable version in `refVsVal.c`.

```c
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

    // & passes a pointer.
    add_byRef(x,y,&z);
    printf("%d\n", z);
}
```

# Initialising a Struct Pointer

One thing which people often struggle with is creating a struct pointer.

You can do this in a lot of different ways, but I prefer:
```c
structname* variable = malloc(sizeof(structname));
```

This creates a pointer called `variable` (obviously, change this to whatever variable name you want!) and also assigns it an instance of a struct. This is a nice, one-line method and means you won't need to worry about referencing and de-referencing in future.

# Using a Struct Pointer

The key difference between using a struct and using a struct pointer is that you will need to use the `->` operator to access attributes of the struct, instead of the `.` operator.

```c
typedef struct __Example{
    int age;
    char name[100];
}example;

example* tom = malloc(sizeof(example));
tom->age = 20;
strcpy(tom->name, "Thomas");
```

# Memory Management

Now you're using malloc() (or calloc()), you will need to think about memory management.

Dynamic memory allocation allows us to do things like create arrays which change size during runtime, as well as create these useful struct pointers, but alongside allocating memory we now need to think about how we **free** that memory.

## Memory Leaks

A memory leak occurs when you fail to release allocated memory, even though you aren't using it any more. In the small and contained systems which we are making, a memory leak isn't very serious- but in larger systems, this can be a huge problem as it causes processes to crash as the system simply runs out of memory. You can see this particularly in computer games, where online game servers are often affected when a memory leak is accidentally introduced leading to cycles of running then crashing.

## Free()

`free()` is the function we use to tell C 'I have finished with this memory, and you can release it'.

You should free() any data which you have dynamically allocated before you exit the program - this includes exiting due to an error, or exiting on success.

In many scenarios, it's easiest to just make a function which can handle your frees for you - usually this will involve:
- making sure the pointer isn't already null
- freeing any allocated data
- setting pointers to NULL afterwards

You can see an example of this in `code.c` using the function `free_image()`. This releases all the memory which had been allocated, removing any risk of a memory leak.