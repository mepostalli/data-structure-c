#include <stdio.h>
#include <stdlib.h>

struct queue{
    int data;
    struct queue *next;
};


typedef struct queue queue;
queue *root = NULL;
queue *rear = NULL;

void enqueue(int x){

    if(root == NULL){
        root =(queue*) malloc(sizeof(queue));
        root -> data = x;
        root -> next = NULL;
        rear = root;
        printf("%d elemanı kuyruga eklendi\n",rear->data);
    }
    else{
        rear -> next =(queue*) malloc(sizeof(queue));
        rear ->next->data = x;
        rear = rear -> next;
        printf("%d elemanı kuyruga eklendi\n",rear->data);
    }
}

int dequeue(){
    if(root == NULL){
        printf("Kuyruk Bos\n");
        return -1;
    }
    int retVal = root -> data;
    queue *tmp = root ;
    root = root -> next ;
    printf("%d elemanı kuyruktan silindi\n",tmp->data);
    free(tmp);
    return retVal;

}

void dispqueue(){
    queue *iter;
    iter = root;
    printf("QUEUE:\n");
    if(root == NULL){
        printf("Kuyruk Bos\n");
    }
    else {
        while(iter  != NULL){
            printf("%d ",iter->data);
            iter = iter->next;
        }
        printf("\n");
    }
}


int main() {

    
    dequeue();
    enqueue(10);
    enqueue(20);
    enqueue(30);
    dispqueue();
    dequeue();
    dequeue();
    dispqueue();
    enqueue(50);
    enqueue(60);
    dispqueue();

    return 0;

}
