#include "StrList.h"
#include <stdio.h>
#include <stdlib.h>

int main () {
    int option = 0;
    StrList* n = StrList_alloc();
    char* inputStr = NULL;
    int index=0;

    do {
        scanf("%d", &option); 

    switch (option)
    {
        case 1: {
            int wordsCount = 0;
            scanf("%d", &wordsCount);
            for (int i = 0; i < wordsCount; i++)
            {
                char* input = malloc(sizeof(char)* 1000);
                scanf ("%s\n", input);
                if (input !=NULL)
                {
                    StrList_insertLast(n,input);
                    free(input);
                }
            }
            break;
        }

            
        case 2: 
            scanf("%d", &index);
            inputStr = malloc(sizeof(char)* 1000);
            scanf ("%s\n", inputStr);
            if (inputStr !=NULL) 
            {
                StrList_insertAt(n,inputStr,index);
                free(inputStr);
            }
            break;
        
        case 3:
            if (n==NULL);
            else
            {
                StrList_print(n);   
            }
            printf("\n");
            break;
        
        case 4: {
            int size = 0;
            size = StrList_size(n);
            printf("%d\n",size);
            printf("\n");
            break;
        }
        
   
        case 5: {
            scanf("%d", &index);
            StrList_printAt(n, index);
            printf("\n");
            break;
        }

        case 6: {
            int len = 0;
            len = StrList_printLen(n);
            printf("%d",len);
            printf("\n");
            break;
        }

        case 7: {
            inputStr = malloc(sizeof(char) * 1000);
            scanf("%s",inputStr);
            if (inputStr != NULL)
            {
                int count = 0;
                count = StrList_count(n, inputStr);
                printf("%d", count);
                printf("\n");
                free(inputStr);
            }
            break;
        }
        
        case 8:
            inputStr = malloc(sizeof(char) * 1000);
            scanf("%s",inputStr);
            if (inputStr != NULL)
            {
                StrList_remove(n,inputStr);
                free(inputStr);
            }
            break;

        case 9:
            scanf("%d", &index);
            StrList_removeAt(n, index);
            break;
        
        case 10:
            StrList_reverse(n);
            break;
        
        case 11:
            StrList_free(n);
            n=StrList_alloc();
            break;
        
        case 12:
            StrList_sort(n);
            break;

        case 13:
            if (StrList_isSorted(n)!=1)
            {
                printf("%s\n","false");
            }
            else 
            {
                printf("%s\n","true");
            }
            break;

            default:
            break;
    }
    }
    while(option!=0);
    StrList_free(n);
    return 0;
}
