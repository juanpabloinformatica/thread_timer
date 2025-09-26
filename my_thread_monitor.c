#define _GNU_SOURCE
#include "my_thread_monitor.h"

void init_thread(my_thread_monitor *my_thread_monitor_obj, int thread_index,
		 void(*callback), char *thread_name, void *callback_args)
{
	assert(pthread_create(&(my_thread_monitor_obj->threads[thread_index]),
			      NULL, callback, callback_args) == 0);

	assert(pthread_setname_np(my_thread_monitor_obj->threads[thread_index],
				  thread_name) == 0);
}
void init_thread_sync(my_thread_monitor *my_thread_monitor_obj)
{
	pthread_cond_init(my_thread_monitor_obj->sync_mm->condition, NULL);

	pthread_mutex_init(my_thread_monitor_obj->sync_mm->condition_mutex,
			   NULL);

	pthread_cond_init(my_thread_monitor_obj->sync_hh->condition, NULL);

	pthread_mutex_init(my_thread_monitor_obj->sync_hh->condition_mutex,
			   NULL);
}
void join_threads(my_thread_monitor *my_thread_monitor_obj)
{
	for (int i = 0; i < THREADS_NUMBER; i++) {
		assert(pthread_join(my_thread_monitor_obj->threads[i], NULL) ==
		       0);
	}
}
void destroy_my_thread_monitor(my_thread_monitor *my_thread_monitor_obj)
{
	if (my_thread_monitor_obj->sync_mm->condition) {
		pthread_cond_destroy(my_thread_monitor_obj->sync_mm->condition);
		free(my_thread_monitor_obj->sync_mm->condition);
	}

	if (my_thread_monitor_obj->sync_mm->condition_mutex) {
		pthread_mutex_destroy(
			my_thread_monitor_obj->sync_mm->condition_mutex);
		free(my_thread_monitor_obj->sync_mm->condition_mutex);
	}

	if (my_thread_monitor_obj->sync_hh->condition) {
		pthread_cond_destroy(my_thread_monitor_obj->sync_hh->condition);
		free(my_thread_monitor_obj->sync_hh->condition);
	}

	if (my_thread_monitor_obj->sync_hh->condition_mutex) {
		pthread_mutex_destroy(
			my_thread_monitor_obj->sync_hh->condition_mutex);
		free(my_thread_monitor_obj->sync_hh->condition_mutex);
	}

	if (my_thread_monitor_obj->sync_mm)
		free(my_thread_monitor_obj->sync_mm);

	if (my_thread_monitor_obj->sync_hh)
		free(my_thread_monitor_obj->sync_hh);

	if (my_thread_monitor_obj)
		free(my_thread_monitor_obj);
}
my_thread_monitor *new_my_thread_monitor()
{
	my_thread_monitor *my_thread_monitor_obj =

		calloc(1, sizeof(my_thread_monitor));
	assert(my_thread_monitor_obj != NULL);

	my_thread_monitor_obj->init_thread = init_thread;
	my_thread_monitor_obj->join_threads = join_threads;
	my_thread_monitor_obj->sync_mm = calloc(1, sizeof(sync_thread));
	assert(my_thread_monitor_obj->sync_mm != NULL);
	my_thread_monitor_obj->sync_mm->condition =
		calloc(1, sizeof(pthread_cond_t));
	my_thread_monitor_obj->sync_mm->condition_mutex =
		calloc(1, sizeof(pthread_mutex_t));

	my_thread_monitor_obj->sync_hh = calloc(1, sizeof(sync_thread));
	assert(my_thread_monitor_obj->sync_hh != NULL);
	my_thread_monitor_obj->sync_hh->condition =
		calloc(1, sizeof(pthread_cond_t));
	my_thread_monitor_obj->sync_hh->condition_mutex =
		calloc(1, sizeof(pthread_mutex_t));
	my_thread_monitor_obj->init_thread_sync = init_thread_sync;

	return my_thread_monitor_obj;
}
