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
void join_threads(my_thread_monitor *my_thread_monitor_obj)
{
	for (int i = 0; i < THREADS_NUMBER; i++) {
		assert(pthread_join(my_thread_monitor_obj->threads[i], NULL) ==
		       0);
	}
}
void destroy_my_thread_monitor(my_thread_monitor *my_thread_monitor_obj)
{
	if (my_thread_monitor_obj)
		free(my_thread_monitor_obj);
}
my_thread_monitor *new_my_thread_monitor()
{
	my_thread_monitor *my_thread_monitor_obj =
		calloc(1, sizeof(my_thread_monitor));
	if (!my_thread_monitor_obj)
		return NULL;
	//pthreads -> is init by compiler
	//my_thread_monitor_obj->threads
	my_thread_monitor_obj->init_thread = init_thread;
	my_thread_monitor_obj->join_threads = join_threads;
}
