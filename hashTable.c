#include <stdio.h>
#include <stdlib.h>

#define HASHTAB_SIZE 10
struct node{
    int val;
    struct node *next;
};

typedef struct node node;

void addnode(node** head,int value){
//    collusion olması durumunda linked list yapısına node ekleyen fonksiyon
    node * new_node = malloc(sizeof(node*));
    new_node-> val = value;
    new_node->next = NULL;

    if(*head == NULL){
        *head = new_node;
    }
    else {
        node *p = *head;

        while(p->next != NULL){
            p = p-> next ;
        }
        p -> next = new_node;
    }
}

int hashing(int new_value){
//    index elde etmemizi sağlayan hash fonksiyonu
    if(new_value < 0){
        new_value = -1;
    }
    return (new_value*3 + 3) % HASHTAB_SIZE;
}

void inserting_table(node **hashtable,int new_value){
//    Hash Tablosuna eleman eklememizi saglayan fonksiyon
    int index = hashing(new_value);

    if (hashtable[index] == NULL){
        hashtable[index] = malloc(sizeof (node*));
        node* head = NULL;
        addnode(&head,new_value);

        hashtable[index] = head ;
    }
    else {
        node* head = hashtable[index];
        addnode(&head,new_value);
        hashtable[index] = head;
    }
}

void dispHt(node **hashtable){
//  Hash Tablosunu ekrana bastıran fonksiyon.
    printf("\n-- HASH TABLE --\n");

    for(int i = 0;i<HASHTAB_SIZE;i++ ){
        node *head = hashtable[i];

        printf("%d : ",i);
        if(head  == NULL) {
            printf("----");
        }else {
            node *tmp = head;

            while (tmp != NULL){
                printf("%d ->",tmp->val);
                tmp = tmp ->next;
            }
        }
        printf("\n");
    }
    printf("-------------\n");
}

int searching(node **hashtable,int val){
//    Hash tablosunda istenilen verinin olup olmadığını kontrol eden fonksiyon
    int index = hashing(val);
    node *tmp;
    if(hashtable[index] == NULL){
        printf("\n%d hashtable'da yoktur\n",val);
        return -1;
    }
    else if (hashtable[index]->val == val){
        printf("\n%d hashtable'da vardır\n",val);
        return 0;
    }
    else {
        tmp = hashtable[index];
        while (tmp->val !=val ){
            tmp = tmp->next;
            if(tmp->next == NULL){
                break;
            }
        }
        if(tmp->val == val){
            printf("\n%d hashtableda vardır\n",val);
            return 0;
        }
        else{
            printf("\n%d hashtable'da yoktur\n",val);
            return -1;
        }
    }
}

void delete(node **hashtable,int val){
//  Hash Tablosundan veri silme işlemini yapan fonksiyon
    int index = hashing(val);
    node *tmp;
    int control = searching(hashtable,val);
    if(control == 0){
        if(hashtable[index]->val == val) {
            tmp = hashtable[index];
            if(hashtable[index] != NULL){
                hashtable[index] = hashtable[index] ->next;
                printf("\n%d silindi\n",*tmp);
                free(tmp);}
            else {
                hashtable[index]->val = NULL;
                printf("\n%d silindi\n",*tmp);
                free(tmp);
            }

        } else {
            tmp = hashtable[index];
            node *p;
            while (tmp->next->val != val ){
                tmp = tmp->next;
                if(tmp->next == NULL){
                    break;
                }
            }
            p = tmp->next;
            if(p->next == NULL){
                printf("\n%d silindi\n",*p);
                free(p);
                tmp->next = NULL;
            }
            else {
                tmp -> next = p ->next;
                printf("\n%d silindi\n",*p);
                free(p);
            }
        }
    }

}


node ** init_table() {
//    hash tablosunu initialize eden fonksiyon
    node **hashtable = calloc(HASHTAB_SIZE, sizeof(node*));
    return hashtable;
}


int main( ){

    node **table = init_table();
    int secim,data;

    while(secim != 5){
        printf("\nYapmak Istediginiz Islemi Secin\n1-Yeni veri ekle\n2-Veri ara\n3-Veri sil\n4-Hash Table'ı goruntule\n5-Cıkıs\nislem:");
        scanf("%d",&secim);

        switch (secim) {
            case 1:
                printf("\nEklemek istediginiz sayıyı giriniz: ");
                scanf("%d",&data);
                inserting_table(table,data);
                break;
            case 2:
                printf("\nAramak istediginiz sayıyı giriniz: ");
                scanf("%d",&data);
                searching(table,data);
                break;
            case 3:
                printf("\nSilmek istediginiz sayıyı giriniz: ");
                scanf("%d",&data);
                delete(table,data);
                break;
            case 4:
                dispHt(table);
                break;

        }
    }
    return 0;
}
