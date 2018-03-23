	#include<stdio.h>
	#include<stdlib.h>
	#include<string.h>
	#include "queue.h"
	//bankSimulator 10 2 100 5
	Noud createCustomerList();
	Queue initializeSimulator(int **);
	Noud ServeCustomer(Queue,int **,int);
	void newCustomer(Queue, Noud);
	void reportStatistics(Noud);
	void ParseInput(char*);
	int tmm;
	int cust_num,off_num,max_arr_t,max_ser_t;//My beginning variables will be changed in ParseINput() function
	int main(){
		
		int *officers;//My officer array will be allocated in InitializeSimulator() function
		Queue myQueue;
		srand(time(NULL));//Seed
		char str[100];//My first string which I will Parse in ParseInput() function
		printf("Enter 4 inputs with 'bankSimulator #Number of customers #Number of officers #Max arrival time #Max service time'  Ex: bankSimulator 10 2 100 5  \n");
		gets(str);
		ParseInput(str);
		Noud head,tmp;
		Noud linking[off_num]={NULL};// CRUISIAL: Here I have created an array of * Nodes which is basically the connection between each bank officer and the person he is serving!!!
		head=createCustomerList();//My linked List is Ready!!!
	
		tmp=head;
	
		int i;
	myQueue=initializeSimulator(&officers);
		tmp=head;
		while(tmp!=NULL){
			i=0;
			while(i<off_num){
				//This function will finish Serving a constumer if its finishing time preceeds that of a new arriving person!!
				if(officers[i]==0){
					if(linking[i]!=NULL && ((linking[i]->servise_start)+(linking[i]->servise_t)) <= tmp->arrival_t){
						linking[i]->bank_id=i+1;
						officers[i]=1;
						if(tmm<((linking[i]->servise_start)+ (linking[i]->servise_t)))tmm=linking[i]->servise_start+ linking[i]->servise_t;
						linking[i]=NULL;
						
						
					}
					
				}
				i++;
			}
			newCustomer(myQueue, tmp);//Taking in a new customer to the Queue
			i=0;
			// Below is the part of function which will check if a bank officer is empty, If yes the person in queue will be allocated there
			while((i<off_num) && officers[i]==0){
				i++;
			}
			if(i<off_num){
				linking[i]=ServeCustomer(myQueue,&officers, i);
				
				
			}
			tmp=tmp->next;
			
		}
		if(myQueue->size==0){
			//If after the allocation the queue is empty we will just finish the rest of the customers and finish with the job
			i=0;
			while(i<off_num){
				if(officers[i]==0){
					if(linking[i]!=NULL){
						linking[i]->bank_id=i+1;
						officers[i]=1;
						if(tmm<((linking[i]->servise_start)+ (linking[i]->servise_t)))tmm=linking[i]->servise_start+ linking[i]->servise_t;
						
						linking[i]=NULL;
					}
					
				}
				i++;
			}
		}
	else{
		// If not we need to allocate the remaining queue and only after deal with finishing 
		while(myQueue->size!=0){
			i=0;
			while(i<off_num){
				if(officers[i]==1 && myQueue->size!=0){
						linking[i]=ServeCustomer(myQueue,&officers, i);
					
				}
				
				i++;
				
			}	
			int min_op_time=100000;
				i=0;
				while(i<off_num){
					if(officers[i]==0){
						if(min_op_time<(linking[i]->servise_start + linking[i]->servise_t))min_op_time=(linking[i]->servise_start + linking[i]->servise_t);
					}
					i++;
					
				}
				i=0;
				while(i<off_num){
					if(officers[i]==0){
						if((linking[i]->servise_start + linking[i]->servise_t)==min_op_time){
						linking[i]->bank_id=i+1;
						officers[i]=1;
						if(tmm<((linking[i]->servise_start)+ (linking[i]->servise_t)))tmm=linking[i]->servise_start+ linking[i]->servise_t;
						linking[i]=NULL;
						}
					}
				}
			
			
			
			
		}
		
			i=0;
			while(i<off_num){
				if(officers[i]==0){
					if(linking[i]!=NULL){
						linking[i]->bank_id=i+1;
						officers[i]=1;
						if(tmm<((linking[i]->servise_start)+ (linking[i]->servise_t)))tmm=linking[i]->servise_start+ linking[i]->servise_t;
						
						linking[i]=NULL;
					}
					
				}
				i++;
			}
				
}
	reportStatistics(head);
	}
	void reportStatistics(Noud head){
		int stat_officer[off_num]={0};
		int i;
		int time_spent=0;
		int time_spent_max=0;
		while(head!=NULL){
			
			stat_officer[(head->bank_id)-1]++;
			if(time_spent_max< ((head->servise_start)-(head->arrival_t))){
				time_spent_max=(head->servise_start)-(head->arrival_t);
			}
			time_spent+=(head->servise_start)-(head->arrival_t);
			
			
			
			
			
			head=head->next;
			
			
		}
		
		printf("\n\nREPORT \n");
		printf("# of Bank Officers %d",off_num);
		printf("\n\n # of Customers %d",cust_num);
		for(i=0;i<off_num;i++){
			printf("\nBank officer number %d has a statistic of %d\n",i+1,stat_officer[i]);
			
			
		}
		printf("It took %d time to complete\n",tmm);
		printf("\nAverage Time spent in the Queue: %f\n",time_spent/cust_num*1.0);
		printf("Max time spent %d",time_spent_max);
		
		
	}
	void ParseInput(char* str){
		char name[50];
		sscanf(str,"%s %d %d %d %d",&name,&cust_num,&off_num,&max_arr_t,&max_ser_t);
		while(strcmp(name,"bankSimulator")){
			printf("Wrong Program Name please enter again\n");
			gets(str);
			sscanf(str,"%s %d %d %d %d",&name,&cust_num,&off_num,&max_arr_t,&max_ser_t);
		}
		
		
	};
	Noud ServeCustomer(Queue myQueue,int** workers,int id){
		if(myQueue->size==0){
			return NULL;
		}
		else{
		
	myQueue->front->servise_start=tmm;

	(*workers)[id]=0;
	return dequeue(myQueue);
		}
		
	}
	void newCustomer(Queue myQueue, Noud  customer){
		tmm=customer->arrival_t;//Change The Time
		if(myQueue->size==0){
			
			myQueue->front=customer;
			myQueue->rear=customer;
			
			
		}
		
		else{
			Noud tmp=myQueue->rear;
			int prior=priority_find(customer->type);
			
			
			while(tmp!=NULL && priority_find(tmp->type)<prior ){
				
				tmp=tmp->next;
				
				
			}
			if(tmp==myQueue->rear){
				customer->next=myQueue->rear;
				myQueue->rear=customer;
				
			}
			else if(tmp==NULL){
				myQueue->front->next=customer;
				customer->next=NULL;
				myQueue->front=customer;
			}
			else{
				Noud tmp1=myQueue->rear;
				while(tmp1->next!=tmp){
					
					tmp1=tmp1->next;
					
					
				}
				customer->next=tmp1->next;
				tmp1->next=customer;
				
			}
			
		}
	
		
		
		
		myQueue->size++;
		
	}
	
	Queue initializeSimulator(int **officer_arr){
		(*officer_arr)=(int *)malloc(sizeof(int)*off_num);
		int i;
		for(i=0;i<off_num;i++){
			(*officer_arr)[i]=1;
		}
		Queue haha;
		haha=(Queue)malloc(sizeof(struct QueueRecord));
		haha->size=0;
		haha->front=NULL;
		haha->rear=NULL;
		return haha;
	
		
	}
	
	
	Noud createCustomerList(){
		Noud head,t;
		int i,tmp_arr_t=0;
		for(i=0;i<cust_num;i++){
			if(i==0){
				head=(Noud)malloc(sizeof(struct Node));
				head->type=rand_prior();	
				head->servise_start=0;
				head->bank_id=0;
				head->servise_t=rand()%max_ser_t+1;
				head->arrival_t=rand()%5+1;
				printf("%c %d %d\n",head->type,head->arrival_t,head->servise_t);
				tmp_arr_t=head->arrival_t;
				t=head;
				head->next=NULL;
				
			}
			else{
				t->next=(Noud)malloc(sizeof(struct Node));
				t=t->next;
				t->type=rand_prior();	
				t->servise_start=0;
				t->bank_id=0;
				t->servise_t=rand()%max_ser_t+1;
				do{
					t->arrival_t=rand()%max_arr_t+1;
					
				}while(t->arrival_t<tmp_arr_t || (t->arrival_t-tmp_arr_t)>15);//THe value 15 is needed so that the gap is not too high, not necessary but makes it easier)
				printf("%c %d %d\n",t->type,t->arrival_t,t->servise_t);
				tmp_arr_t=t->arrival_t;
				t->next=NULL;
	
			}
	
		}
		return head;
	}
