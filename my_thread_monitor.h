#ifndef __MY_THREAD_MONITOR__
#define __MY_THREAD_MONITOR__
#define THREADS_NUMBER 3
#include <stdlib.h>
#include <assert.h>
#include <pthread.h>
typedef struct my_thread_monitor my_thread_monitor;
typedef struct sync_thread sync_thread;
struct sync_thread {
	pthread_cond_t *condition;
	pthread_mutex_t *condition_mutex;
};

struct my_thread_monitor {
	pthread_t threads[THREADS_NUMBER];
	sync_thread *sync_mm;
	sync_thread *sync_hh;
	void (*init_thread)(my_thread_monitor *my_thread_monitor_obj,
			    int thread_index, void(*callback),
			    char *thread_name, void *callback_args);

	void (*join_threads)(my_thread_monitor *my_thread_monitor_obj);
	void (*init_thread_sync)(my_thread_monitor *my_thread_monitor_obj);
};
my_thread_monitor *new_my_thread_monitor();
void destroy_my_thread_monitor(my_thread_monitor *my_thread_monitor_obj);
#endif
