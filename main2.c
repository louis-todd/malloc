#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <stdio.h>

typedef char ALIGN[24];

union header {
	struct {
		size_t size;
		unsigned is_free;
		union header *next;
        union header *prev;
	} s;
	ALIGN stub;
};

typedef union header header_t;

header_t *head, *tail;
pthread_mutex_t global_malloc_lock;

int main(){
    header_t *curr = head;
    printf("head = %p, tail = %p \n", (void*)head, (void*)tail);
	
    while(curr) {
		printf("addr = %p, size = %zu, is_free=%u, next=%p\n",
			(void*)curr, curr->s.size, curr->s.is_free, (void*)curr->s.next);
		curr = curr->s.next;
	}
    return 0;
}
