#include "sam.h"

#include "drivers/memory/nds36p_api.h"

int main()
{
    SystemInit();

    while (1) 
    {
		nds36p_write_buffer(5, 23, 123);
		nds36p_write_buffer(7869, 657, 546);
		nds36p_write_buffer(765, 2345, 23415);
		
		nds36p_read_buffer(5, 23, 123);
		nds36p_read_buffer(7869, 657, 546);
		nds36p_read_buffer(765, 2345, 23415);
    }
}
