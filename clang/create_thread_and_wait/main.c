#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define NUM_THREADS 10
#define SUCCESS 0
#define ERROR -1


void *thread_func(void *arg) {
  int id = (int)arg;
  for (int i = 0; i < 5; i++) {
    printf("thread_id = %d, i = %d\n", id, i);
    sleep(1);
  }

  return "Finished";
}

int main(void) {
  pthread_t v[NUM_THREADS];
  // CREATE THREAD
  for (int i = 0; i < NUM_THREADS; i++) {
    if (pthread_create(&v[i], NULL, thread_func, (void *)i) != SUCCESS) {
      perror("pthread_create");
      return ERROR;
    }
  }

  // WAIT THE END OF THREAD
  for (int i = 0; i < NUM_THREADS; i++) {
    char *ptr;
    if (pthread_join(v[i], (void **)&ptr) == SUCCESS) {
      printf("msg = %s\n", ptr);
    } else {
      perror("pthread_join");
      return ERROR;
    }
  }
  return 0;
}
