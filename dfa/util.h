typedef struct dfa_struct{
    int index;
    struct dfa_struct *a;
    struct dfa_struct *b;
    int accept_state;
}dfa;


//create a state or states
dfa* create_state(int state_index);
dfa** create_states(int size);

//free the allocated memory blocks
void free_mem(dfa **block, int size);

//set the a and b transition of a state
void set_transition(dfa **block, int index, int a, int b);

//set accept state
void set_acceptstate(dfa** block, int index);

//traverse machine
int traverse_machine(dfa** block, char *str);

