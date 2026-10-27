#ifndef CALCULATOR_H
#define CALCULATOR_H

/*Including standard input/output functions like printf()*/
#include<stdio.h>

/*Including standard library functions like malloc() and free()*/
#include<stdlib.h>

/*Defining macros to represent operation status*/
#define SUCCESS 0
#define FAILURE 1


/*Defining an enumeration to represent different operator types*/
typedef enum 
{
    first ,second,third,fourth
}status;

/*Defining a node structure for a doubly linked list*/
typedef struct node
{
    /*Pointer to the previous node*/
    struct node * prev;

    /*Stores a single digit of the number*/
    int data;

    /*Pointer to the next node*/
    struct node *next;

}Dlist;

/*Function declaration to compare two numbers using their tail pointers*/
int compare_list(Dlist *tail1,Dlist *tail2);

/*Function declaration to check whether the operand contains valid characters*/
int checking_operands(char *ch );

/*Function declaration to validate the arithmetic operator*/
int checking_operator(char *ch);

/*Function declaration to identify the operator and return its corresponding status*/
status operator(char *ch);

/*Function declaration to free all nodes in the doubly linked list*/
void free_list(Dlist **head ,Dlist ** tail);

/*Function declaration to display the digits stored in the linked list*/
void print(Dlist *temp);

/*Function declaration to insert the digits of a number at the end of the list*/
int Dlist_insert_last(Dlist **head1, Dlist **tail1 ,char * ch);

/*Function declaration to create and insert a node containing the given data at the end*/
int dlist_insert_last(Dlist **head1, Dlist **tail1 ,int data);

/*Function declaration to perform addition of two numbers*/
int start_addition(Dlist *tail1,Dlist *tail2,Dlist ** head,Dlist ** tail);

/*Function declaration to perform subtraction of two numbers*/
int start_sub(Dlist *tail1,Dlist *tail2,Dlist ** head,Dlist ** tail);

/*Function declaration to perform multiplication of two numbers*/
int start_mult(Dlist *tail1,Dlist *tail2,Dlist ** head,Dlist ** tail);

/*Function declaration to perform division of two numbers*/
int start_div(Dlist *head1 ,Dlist*head2,Dlist *tail2 ,Dlist **R_head, Dlist **R_tail);

/*Function declaration to compare the data values of two nodes*/
int compare_data(Dlist *head, Dlist *head2);

/*Function declaration to check and update the result and carry values*/
void checking_result(int * result , int *carry);

/*Function declaration to insert a new node at the beginning of the list*/
int insert_first(Dlist **head,Dlist **tail,int data);

/*Function declaration to remove unnecessary zeros from the beginning of the result*/
void remove_leading_zeros(Dlist **head);

#endif