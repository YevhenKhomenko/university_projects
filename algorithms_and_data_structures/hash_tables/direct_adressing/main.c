#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define KEY int
#define N 6001
#define HASH(x,y) (x)%(y)
#define EQUAL(x,y) (x)==(y)
#define MAX 823

typedef struct {
    KEY * key;
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
int hash_tbl_insert(hash_tbl * ht, item * it,cnt*c);
item *hash_tbl_search(hash_tbl * ht, KEY k,cnt*c);
int hash_tbl_free(hash_tbl * ht);
int hash_tbl_delete(hash_tbl * ht, item * it,cnt*c);

void item_free(item ** v);

int main()
{
    cnt* cn=(cnt*)malloc(sizeof(cnt));
    //cnt* cn_cmp = (cnt*)malloc(sizeof(cnt));
    cn->avg=0;
    cn->max=0;
    cn->min=MAX;
    item * it = NULL;
    hash_tbl * h = (hash_tbl *)malloc(sizeof(hash_tbl));
    if (!h)
    {
        printf("\nBad allocation!");
        exit(1);
    }
    printf("\n-------- INIT HASH-TABLE --------\n");
    hash_tbl_init(h, MAX);
    srand(13);
    cn->min=MAX;
    cn->max=0;
    cn->avg=0;
    printf("\n-------- INSERT --------\n");
    for(int i = 0; i < MAX; i++)
    {
        it = (item*)malloc(sizeof(item));
        it->key = (KEY*)malloc(sizeof(KEY));
        if (!it) {
            printf("\nBad allocation!");
            exit(1);
        }
        *(it->key) = rand() % N;
        if(!(h->array)[*(it->key)])
            hash_tbl_insert(h, it,cn);
        else{
            //printf("Item with index %d  has been inserted\n",*(it->key));
        }
    }
    printf("Minimum:%d, Maximum:%d, Average:%0.3f",cn->min,cn->max,cn->avg/MAX);
    cn->min=MAX;
    cn->max=0;
    cn->avg=0;
    printf("\n-------- SEARCH --------\n");
    for(int i = 0; i < MAX; i++)
    {
        int key = 0;
        it = (h->array)[rand()%N];
        if (it)    key = *(it->key);
        else key = rand()% N;
        hash_tbl_search(h, key,cn);
    }
    printf("Minimum:%d, Maximum:%d, Average:%0.3f",cn->min,cn->max,cn->avg/MAX);
    cn->min=MAX;
    cn->max=0;
    cn->avg=0;
    printf("\n-------- DELETE --------\n");
    for(int i = 0; i < MAX; i++)
    {
        it = (h->array)[rand()%N];
        if (it)
        {
            hash_tbl_delete(h, it,cn);
        }
    }
    printf("Minimum:%d, Maximum:%d, Average:%0.3f",cn->min,cn->max,cn->avg/MAX);
    printf("\n-------- FREE HASH-TABLE --------\n");
    hash_tbl_free(h);
    free(h);
    free(cn);
    return 0;
}
void hash_tbl_init(hash_tbl * ht,int max)
{
    ht->n = max;
    ht->array = (item **)malloc((N) * sizeof(item *));
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
    cpy++;
    (ht->array)[*(it->key)]=it;
    if(cpy>c->max)
    {
        c->max=cpy;
    }
    if(cpy<c->min)
    {
        c->min=cpy;
    }
    c->avg+=cpy;
    return *(it->key);
}
item*hash_tbl_search(hash_tbl * ht, KEY k,cnt *c)
{
    int cmp=0;
    cmp++;
    if(cmp>c->max)
    {
        c->max=cmp;
    }
    if(cmp<c->min)
    {
        c->min=cmp;
    }
    c->avg+=cmp;
    return (ht->array)[k];
}

int hash_tbl_delete(hash_tbl * ht, item * it, cnt*c)
{
    int cmp =1;            //ÔÂÂÏ≥ÌÛ ÏÓÊÌ‡ ·ÛÎÓ · ÒÚ‚ÓËÚË ‚ main
    int cpy=0;
    cpy++;
    (ht->array)[*(it->key)]=NULL;
    if(cpy>c->max)
    {
        c->max=cpy;
    }
    if(cpy<c->min)
    {
        c->min=cpy;
    }
    c->avg+=cpy;
    return *(it->key);
}
void item_free(item ** v)
{
    if (*v)
    {
        if ((*v)->key) free((*v)->key);
        (*v)->key = NULL;
        free((*v));
    }
    (*v) = NULL;
}
int hash_tbl_free(hash_tbl * ht)
{
    int cnt = 0;
    if (ht)
    {
        if (ht->array)
        {
            for (int i = 0; i < ht->n ; i++)
            {
                if ((ht->array)[i]) cnt++;
                item_free(&((ht->array)[i]));
            }
        }
        free(ht->array);
        ht->array = NULL;
    }
    return cnt;
}
