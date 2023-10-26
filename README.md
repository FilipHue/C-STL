
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


Whether you choose to declare them statically or dynamically, accessing the data inside an array is straightforward: you can use either index notation or pointer arithmetic. However, when it comes to adding an element, let's say insert it in the middle of the array, things get a bit more complex.

For both static and dynamic arrays, resizing is often necessary. With dynamic arrays, functions such as `malloc`, `calloc`, and `realloc` come in handy for allocating new memory blocks and resizing. However, in both cases, you would still need to create a new memory location and copy the data from the old array to the new one. Afterward, shifting the elements is required to make space for inserting the new data.

A notable concern also lies in memory utilization. Static arrays might occupy unnecessary space, whereas dynamic allocation can hit a snag if `realloc` fails to find a suitable memory block, resulting in a NULL return.

This is where alternative data structures, like the Single Linked List, become beneficial. These structures offer more flexibility for insertions and deletions, providing a more efficient solution for these operations.

### Single Linked List

We've previously discussed how an array represents a contiguous block of memory used to store data elements. In contrast, a linked list operates quite differently. Its elements, referred to as nodes, are dispersed throughout the memory, with each node pointing to the next one in the sequence. This connection is established through pointers. Here's a closer look at the structure of a node:

```C
struct node {
	int data;
	struct node *next;
};
```

As we can see, a node is defined as a structure comprising two parts: the `data` field, which holds the value of the node, and the `next` field, which is a pointer to another node. By having the `next` pointer hold the address of the following node, we create a chain of nodes, effectively forming a linked list.

The linked list is commonly represented by a structure that encompasses essential information about the list. This structure will always include a pointer, typically named `head`, which points directly to the first node in the list. To enhance the list's functionality and provide quick access to various elements, additional attributes can be included. For instance, the `tail` pointer can be added to directly reference the list's last node, and a `size` attribute can be incorporated to keep track of the number of nodes in the list. A representation of this linked list structure might appear as follows:

```C
strucure linked_list {
	struct node *head;
	struct node *tail;
	
	unsigned int size;
};
```

This data structure offers a solution to the issues faced with arrays, especially in terms of memory utilization and flexibility for modifications. With dynamic memory allocation employed to create both the list structure and its individual nodes, we gain precise control over the memory we consume.

In instances where we anticipate the need to insert nodes later but do not have any immediate data to store, we can initiate the list structure and set the `head` pointer to NULL. This action signifies that the list is currently empty. Unlike arrays, adding a node to a linked list does not necessitate resizing of the entire structure. Instead, we simply establish connections between nodes using pointers. The same principle holds true for deletion operations.

However, it's important to note a trade-off in terms of element accessibility. Unlike arrays, where index notation provides rapid direct access to any element (due to the contiguous memory layout), linked lists require traversal from the head of the list through each preceding node to reach a specific element (since the nodes are scattered). This characteristic can lead to increased time complexity for certain operations, making linked lists less efficient for scenarios where fast, random access is a priority.

Now, let’s delve into a couple of fundamental and critical operations in linked lists: insertion and deletion.

**Insertion**

Inserting a new node into a linked list is a common operation, and it can take place in various scenarios, such as:

1.  Adding a node at the beginning of the list.
2.  Append node at the end of the list.
3.  Inserting a node at a specific position within the list.

For all these scenarios, the initial steps are similar. First, we need to create the new node, populate it with the desired data, and set its `next` pointer to NULL. This precaution ensures that we don’t end up with a dangling pointer, as the exact connection point in the list is not yet determined.

Next, we must ascertain whether the list is currently empty. If it is, the process is straightforward: we simply set the list’s head pointer to our new node.

If the list is not empty and we are in the first scenario, inserting at the beginning, we update the new node’s `next` pointer to point to the current head of the list. Subsequently, we update the head of the list to be our new node. This operation is commonly referred to as “prepend.”

In the second scenario, adding a node to the end of the list, the process depends on whether we have a tail pointer. If we do, we can directly connect the tail’s next pointer to the new node and then update the tail pointer to our new node, much like the “append” operation. If a tail pointer is not available, we must traverse the entire list to find the last node and update its `next` pointer to our new node.

The third scenario, inserting at a specific position, is a bit trickier since single linked lists are inherently one-directional, and we can’t traverse backwards. To handle this, we iterate through the list until we reach the node just before our desired insertion point. At this juncture, we engage in a bit of pointer manipulation: we set the `next` pointer of our new node to point to the current node’s next node. Then, we update the current node’s next pointer to our new node. This operation, also known as “insert,” effectively places our new node at the specified position in the list[^1].

[^1]: For a much better understanding, I recommend taking a look at [this](https://visualgo.net/en/list).


**Deletion**

Deletion in a linked list involves the removal of a specific node and this task can be performed under various circumstances:

1.  Removing from the beginning of the list.
2.  Eliminating from the end of the list.
3.  Excising a node positioned at a specific location in the list.

In every scenario mentioned above, the initial step is to ascertain whether the list is empty. If that turns out to be the case, we promptly return from the function as there is nothing to remove.

If the list is not empty and we find ourselves in the first situation, the resolution is relatively simple – we shift the head pointer to the next node in the list, thereby effectively removing the first node.

In the second situation, where we aim to delete from the end, we traverse the entire list until reaching the penultimate node. Subsequently, we update the next pointer of this node to NULL, effectively excising the last node from the list. If our linked list structure includes a tail pointer, we ensure to update that as well.

The third situation calls for a more meticulous approach. We traverse the list to locate the node just before the one we wish to delete. After finding this node, we adjust its next pointer to bypass the node slated for deletion, thus removing it from the list.

A crucial aspect to highlight here is the importance of memory management: **ENSURE YOU RELEASE THE MEMORY OCCUPIED BY THE DELETED NODE**. Once the node is disconnected from the list, accessing it becomes impossible unless you’ve saved its address elsewhere (which is unlikely). A practical approach might be to return the address of the deleted node, offering the user the option to utilize the data within if needed, or handle the memory deallocation themselves.


Absolutely, the world of linked lists is vast, and there are plenty of additional features and functions you could tack on to really power up this data structure. However, I'm going to put a pin in that conversation for now, because our next topic is all about exploring those possibilities in depth. I really hope this little intro has set the stage for you, giving you a solid grasp of the basics to confidently jump into the project’s code.

Alright, buckle up – our coding journey is just getting started! 🚀
		
## Double Linked List (DLL)

## Stack

## Queue
