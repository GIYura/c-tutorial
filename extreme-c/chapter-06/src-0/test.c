#include <stdio.h>
#include "list.h"

int main(int argc, char* argv[])
{
    struct list_t* m_list1 = ListCreate();

    ListInit(m_list1);

    for (int i = 0; i < 100; i++)
    {
        if (!ListAdd(m_list1, (i * 10)))
        {
            printf("List is Full\n");
            break;
        }
    }

    printf("List size: %d\n", ListSize(m_list1));

    int index = 4;
    int item;
    if (ListGetByIndex(m_list1, index, &item))
    {
        printf("List item at index [%d]: %d\n", index, item);
    }

    ListPrint(m_list1);
    
    return 0;
}

