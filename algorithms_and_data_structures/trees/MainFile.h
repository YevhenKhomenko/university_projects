#include <stdio.h>
#include <stdlib.h>

typedef struct node_tree{
    int key;
    int level;
    struct node_tree * left, * right, * next;
} ntree;

typedef struct queue{
    ntree * rear,* front;
}nqueue;

ntree * build_tree(ntree *, ntree *, int);
void in_order(ntree *);
void pre_order(ntree *);
void post_order(ntree *);
int free_tree(ntree *);
ntree* create_node(ntree * );
void enqueue (nqueue*, ntree *);
ntree* dequeue (nqueue*);
void level_order(ntree*);
void sum(ntree*);

ntree * build_tree(ntree * root, ntree * node, int key){
    if (!node){
        
        node = (ntree *) malloc(sizeof(ntree));
        if (!node) {
            printf("\nERROR: Bad allocation!");
            exit(1);
        }
        
        node->left = node->right = NULL;
        node->key = key;
        
        if (!root){
            node -> level = 0;
            return node; // create root
        }
        node-> level = root->level + 1;
        if (key < root->key) root->left = node;
        else root->right = node;
        return node;
    }
    if (key < node->key) build_tree(node, node->left, key);
    else build_tree(node, node->right, key);
    
    return root;
}


void in_order(ntree * h){
    if (h->left) in_order(h->left);
    printf("%d\t", h->key);
    if (h->right) in_order(h->right);
}
void pre_order(ntree * h){
    printf("%d\t",h->key);
    if(h->left) pre_order(h->left);
    if(h->right) pre_order(h->right);
}
void post_order(ntree * h){
    if(h->left) post_order(h->left);
    if(h->right) post_order(h->right);
    printf("%d\t",h->key);
}

int free_tree(ntree * h){
    static int c = 0;
    
    if (h->left) free_tree(h->left);
    if (h->right) free_tree(h->right);
    
    if (h) {
        c++;
        free(h);
    }
    return c;
}

ntree * create_node(ntree * node){
    ntree * new_node = node;
    new_node -> next = NULL;
    return new_node;
}

nqueue* create_queue(){
    nqueue * queue = (nqueue*)malloc(sizeof(nqueue));
    queue -> rear = NULL;
    queue -> front = NULL;
    return queue;
}

void enqueue ( nqueue* queue, ntree * node ){
    ntree * temp = create_node(node);
    if (!(queue->rear))
    {
        queue->front = queue->rear = temp;
        return;
    }
    (queue->rear)->next = temp;
    queue->rear = temp;
}
ntree * dequeue(nqueue * queue){
    if(!(queue -> front))  return NULL;
    ntree * temp = queue -> front;
    queue -> front = (queue -> front) -> next;
    if (!(queue->front))  queue->rear = NULL;
    return temp;
}

void level_order(ntree* root){
    nqueue * queue = create_queue();
    ntree * temp = root;
    enqueue(queue, root);
    int i = 0;
    while(temp){
         if(i > 0) printf("%d(%d) ", temp->key, temp -> level);
        if(temp -> left){
            enqueue(queue, temp->left);
        }
        if (temp->right) {
            enqueue(queue, temp->right);
        }
         temp =  dequeue(queue);
         i++;
    }
    free(queue->rear);
    free(queue->front);
    free(queue);
    }

void sum(ntree* root){
    nqueue * queue = create_queue();
    ntree * temp = root;
    enqueue(queue, root);
    int sum = root->key;
    int level ;
    while(temp){
        level = temp-> level;
        if(temp -> left){
            enqueue(queue, temp->left);
        }
        if (temp->right) {
            enqueue(queue, temp->right);
        }
        temp =  dequeue(queue);
        if((temp)&&(temp->level != level)){
            sum += temp->key;
        }
    }
    free(queue->rear);
    free(queue->front);
    free(queue);
    printf("\n\n sum: %d", sum);
    
}



