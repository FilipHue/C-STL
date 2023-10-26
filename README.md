
# C STL Library for Containers

Hey there! 👋 I'm Phillip, and I've been tinkering with data structures and algorithms in C for a while now. What started as doodles on paper and random code snippets quickly grew into this project you see here. It's a reflection of my learning, countless hours of debugging, and, above all, passion.

## Why I Made This

- **To Learn and Share**: Each line of code, every function, was a lesson for me. And now, I'm hoping you can learn from it too. 
- **It's All About Being Generic**: Why stick to one datatype when you can play around with many? This library lets you do just that!
- **Custom Functions, Because Why Not?**: Want to print or free your data in a special way? Go ahead, I've got you covered.
- **Exploring Containers**: From simple structures like stacks to the more complex ones like hashtables, it's been quite the adventure. Join in and see for yourself!

## A Little Note

Yes, there are other libraries, some optimized to the teeth and streamlined for insane performance. This... isn't that. It's more of a playground—a place for you and me to learn, make mistakes, fix them, and grow as programmers.

## Dive In!

Feel free to explore, try out the code, break things, and put them back together. If you've got ideas or feedback, I'm all ears. And if you're just starting with C or data structures, I hope my journey can help light the path for yours.

I’ll try my best to guide you through how these structures work and uncover the logic behind each of them. It’s a journey through pointers, lists, stacks, and more, aiming to leave you with a solid understanding.

Alright now, enough chit-chat, let’s dive into the nitty-gritty of what this repository has in store, shall we?

## A Peek into the Branches :deciduous_tree:

Navigating through a project can be a bit overwhelming, can't it? But don't worry, I've got you covered! This library plays around in two main branches: **main** and **development**. Let's break it down:

### Main Branch – Your Go-To for Stability 🛡️
- **[Main Branch](https://github.com/FilipHue/C-STL/tree/main)**: This is where the magic happens after everything is tried and tested. It’s your safe space for stable code (hopefully :smile:).
  - **Source Code Galore** 📁: Peek inside the [**src**](src/) folder, and you'll find the heart of the library, all polished and ready to go.
  - **Easy Peasy Compilation** ⚙️: The [**Makefile**](Makefile) is there to make your life easier, helping you compile everything without breaking a sweat.
  - **Quick Start with main.c** 🧪: Wanna dive right in? The [**main.c**](main.c) file is your quick entry ticket to test the containers.

### Development Branch – For the Brave and Bold 🛠️
- **[Development Branch](https://github.com/FilipHue/C-STL/tree/development)**: This is the playground! It’s the creative (and sometimes chaotic) space where new features are born.
  - **Test and Learn**: Curious about how things work? Check out the [**test**](https://github.com/FilipHue/C-STL/tree/development/test) folder to see the containers in action and grab some insights 🧐.

So there you have it! I've tried to keep things clear and easy to navigate, just like I hope your experience will be with this library. Dive in, explore, and don't hesitate to reach out if you have any questions or just want to chat about code.

### 🚧 Heads Up! This project is still very much a work in progress. Not all data structures are complete, and the documentation is still under construction. But don't worry! I'm actively working on it, and there will be regular updates. So, do check back often.

## Summary of Topics
Now, with this out of the way, you can choose what topic you want to learn about.

 - Understanding Pointers in C
	 - [Arrays](#arrays)
	 - [Single Linked List](#single-linked-list)
 - Data Structures Explained:
	 - [Double Linked List (DLL)](#double-linked-list-dll) 
	 - [Stack](#stack) 
	 - [Queue](#queue)

## Understanding pointers in C

Like many other programming languages ([C++](https://cplusplus.com/doc/tutorial/), [Java](https://dev.java/learn/) (only for primitive types), [Python](https://docs.python.org/3/), [C#](https://learn.microsoft.com/en-us/dotnet/csharp/), [Fortran](https://fortran-lang.org/learn/) etc.), **C** operates on a **pass-by-value** basis. What this means is when you pass a variable to a function, C actually passes a copy of that variable’s value to the function, and any changes made to the parameter inside the function have no effect on the original argument outside of the function.

However, sometimes you need to work with the
variable itself from inside the function, keeping the modifications. In that case, you'd need to send the address of the variable to the function — and that’s where pointers come into play. With pointers, you can send over an address, work directly with the variable located at that address, and see the changes reflected outside the function as well.

So, to summarize:

**A pointer is a specialized type in C, capable of storing the memory address of other variables or memory locations.**

Furthermore, the size of a pointer is dependent on the system architecture, not the size of the data that is pointing to. For example, on a 64-bit system, a pointer would be 8 bytes in size, reflecting the 64-bit nature of the addresses on such a system.

There are various types of pointers, each with his unique purpose. However, there's one type that will be of most use to us for this project: the **void** pointer. This kind of pointer is type-agnostic, meaning it does not associate itself with any specific data type. This versatile nature allows it to point to any data type, and it can be typecasted to suit our needs. Due to this flexibility, **void** pointers are often referred to as generic pointers.

### Arrays

An array in C is essentially **a contiguous block of memory** allocated to hold a collection of elements, all of the same type. This contiguous nature ensures efficient access to the elements via indexing, where the memory address of each element can be easily calculated based on its position.

#### Declaring Arrays: Static vs. Dynamic

Arrays can be declared in two main ways: **statically** or **dynamically**.

-   **Static Arrays**: The size of a static array is determined at compile-time, making the array’s size constant throughout the program's execution. Here's how you can declare a static array:

	```C
	int staticArray[5]; // Declares an integer array of size 5.
	```

-   **Dynamic Arrays**: Unlike static arrays, dynamic arrays allow for flexibility in size. They are created at runtime using pointers and memory allocation functions like `malloc`, `calloc`, or `realloc`. Here's an example:
    
    ```C
    int* dynamicArray = (int*)malloc(5 * sizeof(int)); // Allocates memory for an integer array of size 5.
    ```
	
At a closer look, you'll notice that in dealing with arrays, we are inherently working with pointers. The array identifier serves as a pointer, directing us to the initial memory location where the data is stored.

### An interesting case: Matrices in C
To have a better understanding of arrays and pointers, lets look at the matrix.

In C, a matrix can be thought of as an array of arrays, or more specifically, a pointer to an array of pointers.

Let's break that down:

-   **Array of Arrays**: A matrix is a two-dimensional data structure where data is stored in rows and columns. To define a matrix, you essentially create an array where each element is itself an array.
	```C
	int matrix[3][3] = {
		{1, 2, 3},
		{4, 5, 6},
		{7, 8, 9}
	};
	```
    
-   **Pointer to an Array of Pointers**: A more nuanced way to look at matrices in C is to see them as pointers pointing to other pointers. The first pointer points to a location in memory where there are other pointers, and these second-level pointers point to the actual data in the matrix.
	```C
	int** matrix = (int**)malloc(rows * sizeof(int*));
	for (int i = 0; i < rows; i++) {
		matrix[i] = (int*)malloc(cols * sizeof(int));
	}
	```

## Double Linked List (DLL)

## Stack

## Queue

