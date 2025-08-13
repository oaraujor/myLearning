#include "linkedList.h"

int main()
{
	LLNode head;
	initList(&head);
	
	if(head.next == NULL) {
		printf("INIT HEAD OK\n");
		updateValueNode(&head);
		printf("%d is the value of the first node\n", head.value);
	}
	else
		printf("Something wrong\n");

	return 0;
}
