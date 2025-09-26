#include "my_timer.h"

static void *update_ss(void *arg)
{
	my_timer *my_timer_obj = (my_timer *)arg;
	for (;;) {
		sleep(1);
		my_timer_obj->ss += 1;
		if (my_timer_obj->ss == MAX_SS) {
			my_timer_obj->ss = 0;
			pthread_cond_signal(my_timer_obj->my_thread_monitor
						    ->sync_mm->condition);
		}
		pthread_cond_signal(my_timer_obj->my_thread_monitor
					    ->sync_display->condition);
	}
}

static void *update_mm(void *arg)
{
	my_timer *my_timer_obj = (my_timer *)arg;
	for (;;) {
		pthread_cond_wait(
			my_timer_obj->my_thread_monitor->sync_mm->condition,
			my_timer_obj->my_thread_monitor->sync_mm
				->condition_mutex);
		my_timer_obj->mm += 1;
		if (my_timer_obj->mm == MAX_MM) {
			my_timer_obj->mm = 0;
			pthread_cond_signal(my_timer_obj->my_thread_monitor
						    ->sync_hh->condition);
		}
	}
}
static void *update_hh(void *arg)
{
	my_timer *my_timer_obj = (my_timer *)arg;
	for (;;) {
		pthread_cond_wait(
			my_timer_obj->my_thread_monitor->sync_hh->condition,
			my_timer_obj->my_thread_monitor->sync_hh
				->condition_mutex);
		my_timer_obj->hh += 1;
		if (my_timer_obj->hh == MAX_HH) {
			my_timer_obj->hh = 0;
			pthread_cond_signal(my_timer_obj->my_thread_monitor
						    ->sync_hh->condition);
		}
	}
}

static void *show_current_time(void *arg)
{
	my_timer *my_timer_obj = (my_timer *)arg;
	for (;;) {
		pthread_cond_wait(
			my_timer_obj->my_thread_monitor->sync_display->condition,
			my_timer_obj->my_thread_monitor->sync_display
				->condition_mutex);
		char time_buffer[TIME_BUFFER_LENGTH];
		int ret;
		ret = snprintf(time_buffer, TIME_BUFFER_LENGTH, "%i:%i:%i",
			       my_timer_obj->hh, my_timer_obj->mm,
			       my_timer_obj->ss);
		printf("TIME:\t%s\n", time_buffer);
		assert(ret >= 0);
		assert(ret <= TIME_BUFFER_LENGTH);
	}
}
static void start_timer(my_timer *my_timer)
{
	if (!my_timer)
		return;

	my_timer->my_thread_monitor->init_thread_sync(
		my_timer->my_thread_monitor);

	my_timer->my_thread_monitor->init_thread(my_timer->my_thread_monitor, 0,
						 my_timer->update_ss,
						 "update_ss", my_timer);

	my_timer->my_thread_monitor->init_thread(my_timer->my_thread_monitor, 1,
						 my_timer->update_mm,
						 "update_mm", my_timer);

	my_timer->my_thread_monitor->init_thread(my_timer->my_thread_monitor, 2,
						 my_timer->update_hh,
						 "update_hh", my_timer);

	my_timer->my_thread_monitor->init_thread(my_timer->my_thread_monitor, 3,
						 my_timer->show_current_time,
						 "show_timer", my_timer);

	my_timer->my_thread_monitor->join_threads(my_timer->my_thread_monitor);
}

void destroy_my_timer(my_timer *my_timer_obj)
{
	if (my_timer_obj->my_thread_monitor)
		destroy_my_thread_monitor(my_timer_obj->my_thread_monitor);

	if (my_timer_obj)
		free(my_timer_obj);
}
my_timer *new_my_timer(void)
{
	my_timer *my_timer_obj = calloc(1, sizeof(my_timer));

	if (!my_timer_obj)
		return NULL;

	my_timer_obj->ss = 0;
	my_timer_obj->mm = 0;
	my_timer_obj->hh = 0;
	my_timer_obj->update_ss = update_ss;
	my_timer_obj->update_mm = update_mm;
	my_timer_obj->update_hh = update_hh;
	my_timer_obj->start_timer = start_timer;
	my_timer_obj->show_current_time = show_current_time;
	my_timer_obj->my_thread_monitor = new_my_thread_monitor();
	return my_timer_obj;
}
