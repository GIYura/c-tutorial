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

##### Инкапсуляция и сокрытие данных

Под икапсуляцией понимается возможность (или способность языка) объединять 
данные по определенным признакам. В СИ инкапсуляция достигается за счет
структур, которые могуг хранить как данные так и методы их обработки. В СИ нет 
возможности хранить методы (функции) внутри структур, но можно хранить 
указатели на функции.

**Например:**

**file.h**
```
typedef void(*func_t)(void);

typedef struct
{
    char brand[20];
    float mileage;
    int year;
    
    func_t start;
    func_t stop;
} car_t;
```

**file.c**
```
static car_t m_car;

static void CarStart(void)
{
    /* some code here */
}

static void CarStop(void)
{
    /* some code here */
}

/*  some code here */

m_car.start = &CarStart;
m_car.stop = &CarStop

```

**NOTE:**

Ключевое слово **typedef** не объявляет новый тип данных, оно используется 
для задания псевдонима. Новый тип данных создается за счет структур.

Под сокрытием данных понимается подход, при котором данные скрыты от 
пользователя. В СИ этого можно достигнуть за счет объявления неполного типа
в файле **.h**, при этом все данные будут скрыты в файле **.c**.

