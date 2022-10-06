// #include <stdlib.h>
// #include <unistd.h>

// // struct mab
// // {
// //     int offset;
// //     int size;
// //     int allocated;
// //     struct mab *next;
// //     struct mab *prev;
// // };

// // typedef struct mab Mab;
// // typedef Mab *MabPtr;

// // MabPtr memCheck(MabPtr m, int size);
// // MabPtr memAlloc(MabPtr m, int size);
// // MabPtr memFree(MabPtr m);

// // int total_memory = 1024 * 1024;
// // int block_size = 64;
// // int no_of_blocks = (1024*1024) / 64;

// // int main()
// // {

// // }

// #include <stdio.h>
// struct node;

// int blk_size = 2000;

// typedef struct node *ptrtonode;
// typedef ptrtonode memory;
// typedef struct node nodetype;
// int pro_id, pro_size;
// memory create();
// struct node
// {
//     int id;
//     int start;
//     int hole;
//     int end;
//     ptrtonode next;
// };
// memory create()
// {
//     memory mem;
//     mem = (ptrtonode)malloc(sizeof(nodetype));
//     mem->next = NULL;
//     return mem;
// }
// void insert(memory mem, int s, int e)
// {
//     ptrtonode tmp;
//     tmp = (ptrtonode)malloc(sizeof(nodetype));
//     tmp->next = mem->next;
//     tmp->start = s;
//     tmp->end = e;
//     tmp->hole = e - s;
//     tmp->id = 0;
//     mem->next = tmp;
// }
// void firstfit(memory mem)
// {
//     int diff;
//     ptrtonode tmp;
//     tmp = mem->next;
//     while (tmp != NULL)
//     {
//         if (tmp->hole >= pro_size && tmp->id == 0)
//         {
//             tmp->id = pro_id;
//             diff = tmp->hole - pro_size;
//             tmp->hole = 0;
//             tmp->end = tmp->start + pro_size;
//             if (tmp->next != NULL && tmp->next->hole == 0)
//             {
//                 tmp = tmp->next;
//                 tmp->hole += diff;
//                 tmp->start -= diff;
//             }
//             else
//             {
//                 ptrtonode t;
//                 t = (ptrtonode)malloc(sizeof(nodetype));
//                 t->next = tmp->next;
//                 tmp->next = t;
//                 t->id = 0;
//                 t->hole = diff;
//                 t->start = tmp->end;
//                 t->end = t->start + t->hole;
//             }
//             break;
//         }
//         else
//         {
//             tmp = tmp->next;
//             if (!tmp)
//             {
//                 printf("Memory Exceeded... ooops\n");
//                 exit(0);
//             }
//         }
//     }
// }

// void best_fit(memory mem)
// {
//     int diff, count = 0, c, min;
//     ptrtonode tmp;
//     tmp = mem->next;
//     min = 2000;
//     while (tmp != NULL)
//     {
//         count++;
//         if (tmp->hole >= pro_size && tmp->id == 0)
//             if (tmp->hole < min)
//             {
//                 min = tmp->hole;
//                 c = count;
//             }
//         tmp = tmp->next;
//     }
//     tmp = mem->next;
//     count = 0;
//     while (tmp != NULL)
//     {
//         count++;
//         if (c == count)
//         {
//             tmp->id = pro_id;
//             diff = tmp->hole - pro_size;
//             tmp->hole = 0;
//             tmp->end = tmp->start + pro_size;
//             if (tmp->next != NULL && tmp->next->hole == 0)
//             {
//                 tmp = tmp->next;
//                 tmp->hole += diff;
//                 tmp->start -= diff;
//             }
//             else
//             {
//                 ptrtonode t;
//                 t = (ptrtonode)malloc(sizeof(nodetype));
//                 t->next = tmp->next;
//                 tmp->next = t;
//                 t->id = 0;
//                 t->hole = diff;
//                 t->start = tmp->end;
//                 t->end = t->start + t->hole;
//             }
//             break;
//         }
//         tmp = tmp->next;
//     }
// }
// void worst_fit(memory mem)
// {
//     int diff, count = 0, c, max;
//     ptrtonode tmp;
//     tmp = mem->next;
//     max = -1;
//     while (tmp != NULL)
//     {
//         count++;
//         if (tmp->hole >= pro_size && tmp->id == 0)
//             if (tmp->hole > max)
//             {
//                 max = tmp->hole;
//                 c = count;
//             }
//         tmp = tmp->next;
//         {
//             count++;

//             if (c == count)
//             {
//                 tmp->id = pro_id;
//                 diff = tmp->hole - pro_size;
//                 tmp->hole = 0;
//                 tmp->end = tmp->start + pro_size;
//                 if (tmp->next != NULL && tmp->next->hole == 0)
//                 {
//                     tmp = tmp->next;
//                     tmp->hole += diff;
//                     tmp->start -= diff;
//                 }
//                 else
//                 {
//                     ptrtonode t;
//                     t = (ptrtonode)malloc(sizeof(nodetype));
//                     t->next = tmp->next;
//                     tmp->next = t;
//                     t->hole = diff;
//                     t->id = 0;
//                     t->start = tmp->end;
//                     t->end = t->start + t->hole;
//                 }
//                 break;
//             }
//             tmp = tmp->next;
//         }
//     }
// }
// void allocate(memory mem)
// {
//     int opt;
//     printf("\nEnter the process ID:");
//     scanf("%d", &pro_id);
//     printf("\n Enter the process size :");
//     scanf("%d", &pro_size);
//     printf("\nMENU");
//     printf("\n1.FIRST FIT");
//     printf("\n2.BEST FIT");
//     printf("\n3.WORST FIT");
//     printf("\nEnter your option");
//     scanf("%d", &opt);
//     switch (opt)
//     {
//     case 1:
//         firstfit(mem);
//         break;
//     case 2:
//         best_fit(mem);
//         break;
//     }
// }
// void deallocate(memory mem)
// {
//     ptrtonode tmp;
//     int diff;
//     printf("\nEnter the process ID:");
//     scanf("%d", &pro_id);
//     tmp = mem;
//     while (tmp->next != NULL)
//     {
//         ptrtonode t;
//         if (tmp->next->id == pro_id)
//         {
//             t = tmp->next;
//             t->id = 0;
//             t->next->start = t->start;
//             t->next->hole = t->next->end - t->next->start;
//             tmp->next = t->next;
//             free(t);
//         }
//         else
//         {
//             t->id = 0;
//             t->hole = t->end - t->start;
//         }
//         break;
//     }
//     tmp = tmp->next;
// }

// void display(memory mem)
// {
//     ptrtonode tmp;
//     tmp = mem->next;
//     while (tmp != NULL)

//     {
//         printf("Process id: %d, Start: %d, End: %d\n\n", tmp->id, tmp->start, tmp->end);
//         tmp = tmp->next;
//     }
// }
// void del(memory mem)
// {
//     ptrtonode tmp, t;
//     tmp = mem;
//     while (tmp != NULL)
//     {
//         t = tmp->next;
//         free(t);
//         tmp = t;
//     }
//     free(mem);
// }
// int main()
// {
//     int i, opt, mem_end = 8000, mem_start;
//     memory mem;
//     mem = create();
//     insert(mem, 0, 10000);
//     for (;;)
//     {
//         printf("\nMENU");
//         printf("\n1.Allocate memory");
//         printf("\n2.Deallocate Memory");
//         printf("\n3.Display");
//         printf("\n4.Exit");
//         printf("\nEnter your Option");
//         scanf("%d", &opt);
//         switch (opt)
//         {
//         case 1:
//             allocate(mem);
//             break;
//         case 2:
//             deallocate(mem);
//             break;
//         case 3:
//             display(mem);
//             break;
//         case 4:
//             del(mem);
//             exit(0);
//         }
//     }
//     return 0;
// }

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

struct Mem
{
    int offset;
    int size;
    int allocated;
};
typedef struct Mem mem;
mem arr[10];
int sizes[] = {5, 6, 4, 7, 3, 8, 2, 9, 1, 5};

void printmem()
{
    for (int i = 0; i < 10; i++)
    {
        printf("%d: offset: %d, size: %d, allocated: %d\n", i, arr[i].offset, arr[i].size, arr[i].allocated);
    }
}

void memCheck(int size)
{
    int choice = 0;
    printf("1. first fit\t2. best fit\t3. worst fit\n");
    scanf("%d", &choice);

    if (choice == 1)
    {
        for (int i = 0; i < 10; i++)
        {
            if (arr[i].size - arr[i].allocated >= size)
            {
                printf("memory available at position %d\n", i);
                break;
            }
        }
    }
    else if (choice == 2)
    {
        int bestPos = -1;
        int bestRem = INT_MAX;
        for (int i = 0; i < 10; i++)
        {
            int rem = arr[i].size - arr[i].allocated;
            if (rem >= size)
            {
                if (rem < bestRem)
                {
                    bestRem = rem;
                    bestPos = i;
                }
            }
        }
        printf("memory available at position %d\n", bestPos);
    }
    else if (choice == 3)
    {
        int worstPos = -1;
        int worstRem = INT_MIN;
        for (int i = 0; i < 10; i++)
        {
            int rem = arr[i].size - arr[i].allocated;
            if (rem >= size)
            {
                if (rem > worstRem)
                {
                    worstRem = rem;
                    worstPos = i;
                }
            }
        }
        printf("memory available at position %d\n", worstPos);
    }
    else
    {
        printf("invalid choice\n");
    }
}

void memAlloc(int size)
{
    int choice = 0;
    printf("1. first fit\t2. best fit\t3. worst fit\n");
    scanf("%d", &choice);

    if (choice == 1)
    {
        for (int i = 0; i < 10; i++)
        {
            if (arr[i].size - arr[i].allocated >= size)
            {
                arr[i].allocated += size;
                printf("memory allocated at position %d\n", i);
                break;
            }
        }
    }
    else if (choice == 2)
    {
        int bestPos = -1;
        int bestRem = INT_MAX;
        for (int i = 0; i < 10; i++)
        {
            int rem = arr[i].size - arr[i].allocated;
            if (rem >= size)
            {
                if (rem < bestRem)
                {
                    bestRem = rem;
                    bestPos = i;
                }
            }
        }
        if (bestPos != -1)
        {
            arr[bestPos].allocated += size;
        }
        printf("memory allocated at position %d\n", bestPos);
    }
    else if (choice == 3)
    {
        int worstPos = -1;
        int worstRem = INT_MIN;
        for (int i = 0; i < 10; i++)
        {
            int rem = arr[i].size - arr[i].allocated;
            if (rem >= size)
            {
                if (rem > worstRem)
                {
                    worstRem = rem;
                    worstPos = i;
                }
            }
        }
        if (worstPos != -1)
        {
            arr[worstPos].allocated += size;
        }
        printf("memory allocated at position %d\n", worstPos);
    }
    else
    {
        printf("invalid choice\n");
    }
    printmem();
}

void memFree(int ptr)
{
    if (ptr <= 10)
    {
        arr[ptr].allocated = 0;
        printf("memory freed at position %d\n", ptr);
    }
    printmem();
}

int main()
{

    for (int i = 0; i < 10; i++)
    {
        arr[i].offset = (i == 0) ? 0 : (arr[i - 1].offset + arr[i - 1].size);
        arr[i].size = sizes[i];
        arr[i].allocated = 0;
    }

    printf("initial memory:\n");
    printmem();

    while (1)
    {
        printf("1. mem check\t2. mem alloc\t3. mem free\n");
        int choice = 0;
        scanf("%d", &choice);
        if (choice == 1)
        {
            printf("enter size\n");
            int size;
            scanf("%d", &size);
            memCheck(size);
        }
        else if (choice == 2)
        {
            printf("enter size\n");
            int size;
            scanf("%d", &size);
            memAlloc(size);
        }
        else if (choice == 3)
        {
            printf("enter position\n");
            int pos;
            scanf("%d", &pos);
            memFree(pos);
        }
        else
        {
            printf("invalid choice\n");
        }
    }
}