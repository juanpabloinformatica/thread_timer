#include "my_timer.h"
#include <stdio.h>
int main()
{
	my_timer *my_timer = new_my_timer();
	my_timer->start_timer(my_timer);
	destroy_my_timer(my_timer);

	return EXIT_SUCCESS;
}
