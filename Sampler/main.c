#include "sam.h"

#include "states.h"

int main()
{
    SystemInit();

	states_init();

    while (1) 
    {		
		states_run();
    }
}