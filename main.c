#include "my_timer.h"
#include "my_thread_monitor.h"
#include <stdio.h>

int main()
{
	my_timer *my_timer = new_my_timer();
	my_thread_monitor *my_thread_monitor = new_my_thread_monitor();
	my_thread_monitor->init_thread(my_thread_monitor, 0,
				       my_timer->update_ss, "update_ss",
				       my_timer);
	my_thread_monitor->init_thread(my_thread_monitor, 1,
				       my_timer->update_mm, "update_mm",
				       my_timer);
	my_thread_monitor->init_thread(my_thread_monitor, 2,
				       my_timer->update_hh, "update_hh",
				       my_timer);
	my_thread_monitor->join_threads(my_thread_monitor);
	my_timer->show_current_time(my_timer);
	return EXIT_SUCCESS;
}
