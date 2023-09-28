##### Description

There are some key points in **src-0** that need consideration.

1. Forward declaration of the struct name before the struct 
definition without providing the actual struct members. 

In **list.h** 
```
struct list_t;
```
is forward declaration. This allows to hide structure fields in **list.c** 
and it is not possible to get access to these fields from **test.c**.

**NOTE:**
It is not possible to declare a variable of incomplete type.
It can be used with pointers only.

2. Function signature in **list.c** is differ then in **list.h**.

3. It is not necessary to include **list.h** inside **list.c**. 
Including leads to type conflict.

4. It is not possible to use **malloc** inside **test.c** directly.
In case of **malloc** we need to specify size:
```
sizeof(struct list_t);
```
that is why this is done where size can be calculated (in list.c).

5. This approach allows isolate **list** implemantation from usage.
There is no need to re-compile **test.c** in case **list.c** implamantation modified.

