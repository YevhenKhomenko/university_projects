//
//  main.c
//
//
//  Created by Ievgen Khonenko on 20.05.18.
//  Copyright © 2018 Ievgen Khonenko. All rights reserved.
//
/*
 Задание
 а)определить число элементов в линейном списке;
 б)разработать функцию конкатенации двух линейных списков;
 в)из упорядоченного списка исключить все элементы, значения   ключей которых находятся взаданных пределах. Из исключенных элементов образовать новый список.
 Организовать интерфейс работы с функциями.
 */

#include <stdio.h>
#include<stdlib.h>
#include <locale.h>

/* Eлемент односвязного списка */
typedef struct list{
    int data;
    struct list* next;
}Node;

/* Обьявление функций */
void push( Node** head_ref, int new_data);
void insertAfter( Node* prev_node, int new_data);
void append(Node** head_ref, int new_data);
void printList( Node *node);
int getCount(Node* head);
Node *getUnion( Node *head1,  Node *head2);
Node *delRange(Node ** head_ref,int min,int max);
void instructions();
void single_list();
void sort(Node **root);
void list_union();
Node *find_node(Node *head,int data);

int main(){
     setlocale(LC_ALL, "Russian");
    int input;
    instructions();
    scanf("%d", &input);
    while (input != 0) {
        switch (input) {
            case 1:
                single_list();
                break;
            case 2:
                list_union();
                break;
            default:
                break;
        }
         instructions();
        scanf("%d", &input);
    }
    return 0;
}

void instructions(){
    printf("/////////////////////////////////////////////////\n");
    printf("Нажмите 1 для работы с одним связным списком\n");
     printf("Нажмите 2 для конкатенации 2-х линейных списков\n ");
     printf("Нажмите 0 для завершения роботы с программмой\n");
     printf("/////////////////////////////////////////////////\n");
}

/* Для работы с одним линейным списком */
void single_list(){
    printf("Введите кол-во елементов , которое Вы хотите добавить: ");
    int n,elem;
    Node *head = NULL;
    scanf("%d",&n);
    for (int i = 0; i < n; i++) {
        printf("\nВведите елемент: ");         // создание списка и добавление елементов в него
        scanf("%d",&elem);
        append(&head, elem);
    }
    printf("\nСписок: ");
    printList(head);
    printf("\nКоличество елеметов в списке: %d\n",getCount(head));
    sort(&head);
    printf("\nОтсортированый список: ");
    printList(head);
    
    int answer;
    int prevElem;
    printf("\nХотите добавить елeмент? 1 - да, 2 - нет\n ");
    scanf("%d", &answer);                                       //разные варианты вставки елементов в
    while (answer != 2) {                                       // список
        printf("\n Введите 3 для добавления в конец списка,4- в начало,5-после заданого елемента\n ");
        scanf("%d", &answer);
        switch (answer) {
            case 3:
                printf("\nВведите елемент: ");          //  вставка в конец списка
                scanf("%d",&elem);
                append(&head, elem);
                break;
            case 4:
                printf("\nВведите елемент: ");          //  вставка в начало списка
                scanf("%d",&elem);
                push(&head, elem);
                break;
            case 5:
                printf("\nВведите елемент: ");          //  вставка после заданого елемента
                scanf("%d",&elem);
                printf("\nВведите елемент, после которого вы хотите сделать вставку: ");
                scanf("%d",&prevElem);
                Node *previous = find_node(head, prevElem);
                if (previous) {
                    insertAfter(previous, elem);
                }else{
                    printf("\nEлемент не найден\n");
                }
                break;
                
            default:
                break;
        }
        printf("\nСписок: ");
        printList(head);
        printf("\nКоличество елеметов в списке: %d\n",getCount(head));
        sort(&head);
        printf("\nОтсортированый список: ");
        printList(head);
        printf("\nХотите добавить елeмент? 1 - да, 2 - нет\n ");
        scanf("%d", &answer);
    }
    
    /*из упорядоченного списка исключаем все элементы, значения ключей которых находятся в заданных пределах. Из исключенных элементов образовываем новый список. */
    Node *head1 = NULL;
    int min,max;
    printf("Введите диапазон удаления елементов из данного списка:\n");
    printf("От: ");
    scanf("%d",&min);
     printf("До: ");
    scanf("%d",&max);
    head1 = delRange(&head, min, max);
    printf("\nСписок после удаления елементов:\n");
    printList(head);
    printf("\nКоличество елеметов в списке: %d\n",getCount(head));
     printf("\nНовый список из удаленных елементов:\n");
    printList(head1);
    printf("\nКоличество елеметов в списке: %d\n",getCount(head1));
}

/* Для конкатенации 2-х линейных списков */
void list_union(){
    printf("Введите кол-во елементов , которое Вы хотите добавить в 1 список: ");
    int n,elem;
    Node *head1 = NULL;
    scanf("%d",&n);
    for (int i = 0; i < n; i++) {
        printf("\nВведите елемент: ");      //создание первого списка
        scanf("%d",&elem);
        append(&head1, elem);
    }
    printf("\nСписок: ");
    printList(head1);
    printf("\nКоличество елеметов в списке: %d\n",getCount(head1));
    printf("Введите кол-во елементов , которое Вы хотите добавить во 2 список: ");
    Node *head2 = NULL;
    scanf("%d",&n);
    for (int i = 0; i < n; i++) {
        printf("\nВведите елемент: ");          //создание второго списка
        scanf("%d",&elem);
        append(&head2, elem);
    }
    printf("\nСписок: ");
    printList(head1);
    printf("\nКоличество елеметов в списке: %d\n",getCount(head1));
    Node *new = getUnion(head1, head2);                          //обьеденяем списки
    printf("\nCписок составленный из 1 и 2: ");
    printList(new);
    printf("\nКоличество елеметов в списке: %d\n",getCount(new));
}

/*Получает двойной указатель на голову списка и передаваемое значение типа int, вставляет елемент в начало списка. */
void push( Node** head_ref, int new_data)
{
    Node* new_node = (Node*) malloc(sizeof( Node));

    new_node->data  = new_data;

    new_node->next = (*head_ref);
    
    (*head_ref)    = new_node;
}

/* получает указатель на предшествующий елемент и значения типа int, вставляет новый елемент после него */
void insertAfter( Node* prev_node, int new_data)
{
    if (prev_node == NULL)
    {
        printf("the given previous node cannot be NULL");
        return;
    }

     Node* new_node =( Node*) malloc(sizeof(Node));
    
    new_node->data  = new_data;
    
    new_node->next = prev_node->next;
    
    prev_node->next = new_node;
}

/* Получает двойной указатель на голову списка и значение типа int , присоединяет новый узел к концу линейного списка appends a new node at the end  */
void append( Node** head_ref, int new_data)
{
     Node* new_node = (Node*) malloc(sizeof( Node));
    
     Node *last = *head_ref;
    
    new_node->data  = new_data;
    
    new_node->next = NULL;
    
    if (*head_ref == NULL)
    {
        *head_ref = new_node;
        return;
    }
    
    while (last->next != NULL)
        last = last->next;
    
    last->next = new_node;
    return;
}

// Получает указатель на голову списка, печатает на экран содержимое списка , начиная с его головы
void printList( Node *node)
{
    while (node != NULL)
    {
        printf("%d->", node->data);
        node = node->next;
    }
    printf("NULL\n");
}

/* Получает указатель на голову списка, считает количество узлов и возвращает это значение  */
int getCount(Node* head)
{
    int count = 0;
    Node* current = head;
    while (current != NULL)
    {
        count++;
        current = current->next;
    }
    return count;
}

/* функция, которая получаем указатели на головы 2-х списков, обьеденяет их и возвращает указатель на голову новго списка, который содержит в себе два данных */
Node *getUnion( Node *head1,  Node *head2)
{
    Node *result = NULL;
    Node *t1 = head1, *t2 = head2;
    
    while (t1 != NULL)
    {
        push(&result, t1->data);
        t1 = t1->next;
    }
    

    while (t2 != NULL)
    {
            push(&result, t2->data);
        t2 = t2->next;
    }
    
    return result;
}
/*  Принимает двойной указатель на начало списка,границы удаления(min,max),возвращает указатель на голову нового списка, составленного из удаленных елементов */
Node *delRange(Node ** head_ref,int min,int max){
    Node *currentL = *head_ref;
    while (((currentL->next)->data)<min) {
        currentL = currentL->next;
    }
    Node *new_head = currentL->next;
    Node *currentR = currentL->next;
    while ((currentR->data)<max) {
        currentR = currentR->next;
    }
    currentL->next =currentR->next;
    currentR->next = NULL;
    return new_head;
}
/*  Принимает двойной указатель на начало списка,сортирует его */
void sort(Node **root)
{
    Node *p = NULL;
    Node *head = *root;
    
    if (head != NULL) {
        while (head->next != NULL) {
            p = head->next;
            
            do {
                if (p->data < head->data) {
                    int tmp_s = p->data;
                    p->data = head->data;
                    head->data = tmp_s;
                }
                p = p->next;
            } while (p != NULL);
            
            head = head->next;
        }
    }
}
/* Принимает указатель на голову списка, искомое значение, ищет соответсвующий елемент связного списка , возвращает указательн на него, если его не сущетсвует - возвращает NULL */
Node *find_node(Node *head,int data){
    Node* current = head;  // Initialize current
    while (current != NULL)
    {
        if(current->data == data) return current;
        current = current->next;
    }
    return NULL;
}



