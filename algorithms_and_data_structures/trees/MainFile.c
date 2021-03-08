#include "MainFile.h"
#include <stdio.h> 
#include <stdlib.h>

#define N 20

int main(){

    FILE *fp = fopen("MyTxt.txt","r+");
    int *c = (int*) malloc(N*sizeof(int));

    for(int i = 0;i < N; i++){ 
        fscanf(fp,"%d",&c[i]);
    } 
    fclose(fp);

    ntree * root = NULL;

    for (int i=0; i<N; i++) { 
        int key = c[i];
        printf("%d\t", key);
        root = build_tree(root, root, key);
        }

    printf("\n");
    printf("inorder: \n");
    in_order(root);
    printf("\n");
    printf("preorder:\n");
    pre_order(root);
    printf("\n");
    printf("postorder:\n");
    post_order(root);
    printf("\n");
    printf("levelorder:\n");
    level_order(root);
    sum(root);
    printf("\n\n%d nodes were deleted\n", free_tree(root));
    free(c);
    return 0;
}