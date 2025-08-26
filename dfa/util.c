#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "util.h"

dfa *create_state(int state_index)  //creates one dfa state and gives the proper index
{
    dfa *temp = NULL;
    temp = (dfa *)calloc(1, sizeof(dfa));
    temp->a = NULL;
    temp->b = NULL;
    temp->index = state_index;
    temp->accept_state = -1;
    return temp;
}

dfa** create_states(int size)  //creates multiple dfa states and gives each an index
{
    dfa** temp = NULL;
    temp = (dfa **)calloc(size, sizeof(dfa*));
    for(int i = 0; i < size; i++)
    {
        temp[i] = create_state(i);
    }
    printf("\n[Debug]: Allocated memory for %d states\n", size);

    return temp;
}

void free_mem(dfa **block, int size)  //frees all the blocks created
{
    if(block == NULL) return;
    for(int i = 0; i < size; i++)
    {
        free(block[i]);
    }
    printf("\n[Debug]: Freed %d blocks of data\n", size);

    free(block);
}


void set_transition(dfa **block, int index, int a, int b) //sets the transition of a and b
{
    if(block == NULL) return;
    if(block[index] == NULL) return;
    block[index]->a = block[a];
    block[index]->b = block[b];
    printf("\n[Debug]: State %d : a->%d b->%d..\n", index + 1, a + 1, b + 1);

}

void set_acceptstate(dfa** block, int index)
{
    if(block == NULL) return;
    if(block[index] == NULL) return;

    block[index]->accept_state = 0;
}

int traverse_machine(dfa** block, char *str)
{
    if(block == NULL) return;

    int ind = 0;
    int str_index = 0;
    //str[strlen(str) - 1] = '\0';
    int count = strlen(str);
    //printf("%d", count);
    while(str_index < count)
    {
        if(str[str_index] == 'a') //str[str_index] == 'a'
        {
            if(block[ind] != NULL)
            {
            ind = block[ind]->a->index;
            }
        }
        if(str[str_index] == 'b') //str[str_index] == 'b'
        {
            if(block[ind] != NULL)
            {
            ind = block[ind]->b->index;
            }
        }

        str_index++;
    }

    return block[ind]->accept_state;
}