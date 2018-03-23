#include <stdio.h>
#include <time.h>
#include <stdlib.h>
//All my declarations and some functiion for random values 
struct Node {
	char type;
	int arrival_t;
	int servise_t;
	int servise_start;
	int bank_id;
	struct Node *next;
};

struct QueueRecord{
	struct Node *front;
	struct Node *rear;
	int size;
	
	
};


char rand_prior(){

	int a= rand()%4 +1;
	if(a==1)return 'C';
	else if(a==2)return 'B';
	else if(a==3)return 'S';
	else if(a==4)return 'G';
	else printf("SUCH AN ERROR");
	
}
int priority_find(char a){

	if(a=='G')return 4;
	else if(a=='S')return 3;
	else if(a=='B')return 2;
	else if(a=='C')return 1;
	else return -1;
}
typedef struct Node * Noud;
typedef struct QueueRecord * Queue;
Noud dequeue(Queue my){
	
	if(my->size==0)return NULL;
	else{
		Noud tmpa=my->front;
		if(my->size==1){
			my->front=NULL;
			my->rear=NULL;
		}
		else{
			Noud tmp= my->rear;
			while(tmp->next!=my->front){
				tmp=tmp->next;
			}
			my->front=tmp;
		}
		my->size--;
		return tmpa;
	}
	
	
}

 
