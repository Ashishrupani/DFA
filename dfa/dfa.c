#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "util.h"

#define BUFFER 1024
char *LOADING = "\\|/-";

int make_a_machine(dfa **head, int size);

int main()
{
    // system("clear");
    //  int control = 3;
    //  dfa **states = create_states(control);

    // set_transition(states, 0, 1, 0);
    // set_transition(states, 1, 1, 2);
    // set_transition(states, 2, 0, 0);

    // set_acceptstate(states, 1);

    // char *buffer = "abaaabbaabababbabbab";
    // // int count = strlen(buffer);
    // // printf("%d", count);
    // int temp = traverse_machine(states, buffer);

    // if (temp == 0)
    // {
    //     printf("\nString Accepted");
    // }
    // else
    // {
    //     printf("\nString Not Accepted");
    // }

    // free_mem(states, control);

    // main program
    char buff[BUFFER]; // buffer for input for string
    int choice = 0;    // choice of the user
    int machine_size;  // size of the machine
    dfa **machine = NULL;
    int accept_state = -1;
    int display = -2;
    while (choice <= 999)
    {
#ifdef _WIN32
        system("cls");
#elif __linux__
        system("clear");

#endif
        printf("\n-----MENU-----");
        printf("\n1. Make a machine");
        printf("\n2. Set transitions--(You will have to set all states.)");
        printf("\n3. Set multiple accept states.");
        printf("\n4. Enter a string(a,b)");
        printf("\n5. Reset the machine");
        printf("\n6. Randomize transitions.");
        printf("\nExit...(enter value above 999)");
        printf("\n");

        // Machine.................
        if (machine != NULL)
        {
            printf("\n-----MACHINE-----");
            printf("\nStates: %d", machine_size);
            for (int i = 0; i < machine_size; i++)
            {
                if (machine[i]->a == NULL || machine[i]->b == NULL)
                    continue;
                printf("\nState %d: a->%d  b->%d", i + 1, machine[i]->a->index + 1, machine[i]->b->index + 1);
            }

            printf("\nAccept states: ");
            for(int i = 0; i < machine_size; i++)
            {
                if(machine[i]->accept_state == 0) printf("%d ", machine[i]->index + 1); 
            }

            if (display == 0)
            {
                printf("\nString Accepted");
            }
            if (display == -1)
            {
                printf("\nString Not Accepted");
            }
        }
        // Choice..................
        printf("\n\nEnter choice: ");
        scanf("%d", &choice);

        if (choice == 1)
        {
            if (machine != NULL)
                continue;
            printf("\nHow many states?");
            scanf("%d", &machine_size);
            while (machine_size == 0)
            {
                scanf("%d", &machine_size);
            }

            machine = create_states(machine_size);
            // reset_1 = 1;
        }
        if (choice == 2)
        {
            if (machine == NULL)
                continue;
            for (int i = 0; i < machine_size; i++)
            {
                while (machine[i]->a == NULL || machine[i]->b == NULL)
                {
                    int a = 0;
                    while(a == 0){
                    printf("\nEnter the transition to a: ");
                    scanf("%d", &a);}

                    int b = 0;
                    while(b == 0){
                    printf("\nEnter the transition to b: ");
                    scanf("%d", &b);}

                    set_transition(machine, i, a - 1, b - 1);
                }
            }
            if(accept_state == -1){
            printf("\nEnter Accept State: ");
            int entry = 0;
            scanf("%d", &entry);
            while (entry > machine_size || entry <= 0)
            {
                printf("\nEnter Accept State: ");
                scanf("%d", &entry);
            }

            set_acceptstate(machine, entry - 1);
            accept_state = entry - 1;
            }
        }
        if(choice == 3)
        {
            if (machine == NULL)
            continue;
            printf("\nHow many accept states?");
            int num_accept_states = 0;
            scanf("%d", &num_accept_states);
            while(num_accept_states <= 0 || num_accept_states > machine_size)
            {
                scanf("%d", &num_accept_states);
            }

            for(int i = 0; i < num_accept_states; i++)
            {
            int entry = 0;
            printf("\nEnter Accept State[%d]: ", i + 1);
            scanf("%d", &entry);
            while (entry > machine_size || entry <= 0)
            {
                printf("\nEnter Accept State[%d]: ", i + 1);
                scanf("%d", &entry);
            }
            set_acceptstate(machine, entry - 1);
            accept_state = entry - 1;
            }

        }
        if (choice == 4)
        {
            if (machine == NULL || accept_state == -1)
                continue;
            printf("\nEnter the string: ");
            while (scanf("%s", buff) == '\n')
            printf("\nInput string: %s", buff);

            display = traverse_machine(machine, buff);
        }
        if (choice == 5)
        {
            free_mem(machine, machine_size);
            machine = NULL;
            display = -2;
            accept_state = -1;
        }
        if(choice == 6)
        {
            srand(time(NULL));
            if (machine == NULL)
                continue;
                for (int i = 0; i < machine_size; i++)
            {
                while (machine[i]->a == NULL || machine[i]->b == NULL)
                {
                    int lower = 0;
                    int a = 0;
                    int b = 0;
                    int upper = machine_size - 1;

                    a = (rand() % ( upper - lower + 1)) + lower;
                    b = (rand() % ( upper - lower + 1)) + lower;
                    // while(a == 0){
                    // printf("\nEnter the transition to a: ");
                    // scanf("%d", &a);}

                    
                    // while(b == 0){
                    // printf("\nEnter the transition to b: ");
                    // scanf("%d", &b);}


                    //printf("a: %d  b: %d", a, b);
                    set_transition(machine, i, a, b);
                }
            }
        }
        if (choice >= 999 || choice <= 0)
        {
            free_mem(machine, machine_size);
            machine = NULL;
        }
    }

    // int yyy;
    // printf("\nENTER ANY NUMBER TO EXIT.......");
    // scanf("%d", &yyy);

    return 0;
}
