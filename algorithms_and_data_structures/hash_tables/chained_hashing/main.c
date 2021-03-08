#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include<math.h>

#define KEY int
#define EQUAL(x,y) x==y
#define MAX 100 //823
#define N 6001
#define HASH(x) (x)%MAX

typedef struct item{
    KEY * key;
    struct item *next;
} item;

typedef struct{
    int n;
    item ** array;
} hash_tbl;

typedef struct{
    int max,min;
    float avg;
}cnt;


void hash_tbl_init(hash_tbl * ht,int max);
int hash_tbl_insert(hash_tbl * ht, item * it,cnt*);
item *hash_tbl_search(hash_tbl * ht, KEY k,cnt*);
int hash_tbl_free(hash_tbl * ht,cnt*);
int hash_tbl_delete(hash_tbl * ht, item * it,cnt*);

void item_free(item ** v);

int main()
{
    cnt* cn=(cnt *)malloc(sizeof(cnt));
    item * it = NULL;
    cn->avg=0;
    cn->max=0;
    cn->min=MAX;
    hash_tbl * h = (hash_tbl *)malloc(sizeof(hash_tbl));
    if (!h) {
        printf("\nBad allocation!");
        exit(1);
    }
    printf("\n-------- INIT HASH-TABLE --------\n");
    hash_tbl_init(h, MAX);
    srand(time(NULL));
    printf("\n-------- INSERT --------\n");
    for(int i = 0; i < MAX; i++)
    {
        it = (item*)malloc(sizeof(item));
        it->key = (KEY*)malloc(sizeof(KEY));
        it->next=NULL;
        if (!it) {
            printf("\nBad allocation!");
            exit(1);
        }
        *(it->key) = rand() % N;
        hash_tbl_insert(h, it,cn);
    }
    printf("Minimum:%d, Maximum:%d, Average:%0.3f",cn->min,cn->max,cn->avg/MAX);
    cn->min=MAX;
    cn->max=0;
    cn->avg=0;
    printf("\n-------- SEARCH --------\n");
    for(int i = 0; i < MAX; i++){
        int key = 0;
        it = (h->array)[rand()%MAX];
        if (it)    key = *(it->key);
        else key = rand() % N;
        hash_tbl_search(h, key,cn);
    }
    printf("Minimum:%d, Maximum:%d, Average:%0.3f",0,cn->max,cn->avg/MAX);
    cn->min=MAX;
    cn->max=0;
    cn->avg=0;
    printf("\n-------- DELETE --------\n");
    for(int i = 0; i < MAX; i++){
        it = (h->array)[HASH(rand()%N)];
        if (it)
        {
            hash_tbl_delete(h, it,cn);
        }
        else
        {
            item*temp=NULL;
            temp = (item*)malloc(sizeof(item));
            temp->key=(KEY*)malloc(sizeof(KEY));
            *(temp->key)=rand()%N;
            temp->next=NULL;
            hash_tbl_delete(h, temp,cn);
        }
    }
    printf("Minimum:%d, Maximum:%d, Average:%0.3f",cn->min,cn->max,cn->avg/MAX);
    printf("\n-------- FREE HASH-TABLE --------\n");
    printf("\n%d items were deleted\n", hash_tbl_free(h,cn));
    free(h);
    free(cn);
    free(it);
    return 0;
}
void hash_tbl_init(hash_tbl * ht,int max){
    ht->n = max;
    ht->array = (item **)malloc((MAX) * sizeof(item *));
    int i=0;
    while(i<ht->n)
    {
        (ht->array)[i]=NULL;
        i++;
    }
}

int hash_tbl_insert(hash_tbl * ht, item * it,cnt*c)
{
    int cpy=0;
    if((ht->array)[HASH(*(it->key))]!=NULL)
    {
        it->next=(ht->array)[HASH(*(it->key))];
        (ht->array)[HASH(*(it->key))]=it;
        cpy++;
    }
    else
    {
        (ht->array)[HASH(*(it->key))]=it;
        cpy++;
    }
    if(cpy>c->max)
    {
        c->max=cpy;
    }
    if(cpy<c->min)
    {
        c->min=cpy;
    }
    c->avg+=cpy;
    return HASH(*(it->key));
}
item*hash_tbl_search(hash_tbl * ht, KEY k,cnt*c)
{
    item*temp=(ht->array)[HASH(k)];
    int cmp=0;
    cmp++;
    if(temp)
    {
        while(temp!=NULL)
        {
            cmp++;
            if(k==*(temp->key))
            {
                return temp;
            }
            else
            {
                temp=temp->next;
            }
        }
    }
    if(c->max<cmp)
    {
        c->max=cmp;
    }
    if(c->min>cmp)
    {
        c->min=cmp;
    }
    c->avg+=cmp;
    free(temp);
    return NULL;
}

int hash_tbl_delete(hash_tbl * ht, item * it,cnt*c)
{
    int cmp=0;
    int cpy=0;
    cmp++;
    if((ht->array)[HASH(*(it->key))])
    {
        item*temp=(ht->array)[HASH(*(it->key))];
        cmp++;
        if(*(it->key)==*((ht->array)[HASH(*(it->key))]->key))
        {
            cpy++;
            (ht->array)[HASH(*(it->key))]=(ht->array)[HASH(*(it->key))]->next;
            free(temp);
        }
        else
        {
            cmp++;
            while(temp->next)
            {
                cmp++;
                if(*(it->key)==*((temp->next)->key))
                {
                    cpy++;
                    temp->next=(temp->next)->next;
                    return 0;
                }
                else
                {
                    temp=temp->next;
                }
            }
        }
    }
    if(c->max<cmp)
    {
        c->max=cmp;
    }
    if(c->min>cmp)
    {
        c->min=cmp;
    }
    if(c->max<cpy)
    {
        c->max=cpy;
    }
    
    c->avg+=cmp;
    c->avg+=cpy;
    return -1;
}

void item_free(item ** v){
    if (*v){
        if ((*v)->key) free((*v)->key);
        (*v)->key = NULL;
        free((*v));
    }
    (*v) = NULL;
}
int hash_tbl_free(hash_tbl * ht,cnt*c){
    int cnt = 0;
    if (ht) {
        if (ht->array) {
            for (int i = 0; i < ht->n ; i++){
                if ((ht->array)[i]) cnt++;
                item_free(&((ht->array)[i]));
            }
        }
        free(ht->array);
        ht->array = NULL;
    }
    return cnt;
}

