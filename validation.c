#include "calculator.h"


/*Function definitions for argument validation and linked list utility operations*/

/*Checking whether the operands are valid*/
int checking_operands(char * argument)
{
    int i = 0;

    /*Skipping the first character if it is a positive or negative sign*/
    if(argument[0] == '+'  || argument[0] == '-' )
    {
        i++;
    }

    /*Checking whether every remaining character is a digit*/
    for(; argument[i] != '\0'; i++)
    {
        /*Returning FAILURE if the character is not between 0 and 9*/
        if(argument[i] < '0' || argument[i] > '9')
        {
            return FAILURE;
        }     

    }

    /*Returning SUCCESS if all checked characters are digits*/
    return SUCCESS;
}


/*Checking whether the given operator is valid*/
int checking_operator(char *ch)
{
    /*Checking that the operator contains exactly one character
       and is one of +, -, x, X, or /*/
    if(ch[1] == '\0' && (ch[0] == '+' || ch[0] == '-' ||
        ch[0] == 'x' || ch[0] == 'X' ||
        ch[0] == '/'))
    {
        return SUCCESS;
    }

    /*Returning FAILURE if the operator is invalid*/
    return FAILURE;
}

/*Identifying the operator and returning its corresponding enum value*/
status operator(char *ch)
{
    /*Returning first for addition*/
    if(ch[0] == '+')
    {
        return first;
    }

    /*Returning second for subtraction*/
    if(ch[0] == '-')
    {
        return second;
    }

    /*Returning third for multiplication*/
    if(ch[0] == 'X' || ch[0] == 'x')
    {
        return third;
    }

    /*Returning fourth for division*/
    if(ch[0] == '/')
    {
        return fourth;
    }
}

/*Comparing two numbers represented by doubly linked lists*/
int compare_list(Dlist *tail1,Dlist *tail2)
{
    /*Initializing temporary pointers to traverse both lists backward*/
    Dlist *temp1 = tail1;
    Dlist *temp2 = tail2;

    /*Variables to count the number of nodes in each list*/
    int count1 = 0;
    int count2 = 0;

    /*Counting the nodes in the first list*/
    while(temp1 != NULL)
    {
        count1++;
        temp1 = temp1->prev;
    }

    /*Counting the nodes in the second list*/
    while(temp2 != NULL)
    {
        count2++;
        temp2 = temp2->prev;
    }

    /*The number with more digits is greater*/
    if(count1 > count2)
    {
        return SUCCESS;
    }
    else if(count1 < count2)
    {
        return FAILURE;
    }
    else
    {
        /*If both numbers have the same number of digits,
          compare corresponding digits from left to right
          by traversing backward from the tail pointers*/
        while(tail1 != NULL && tail2 != NULL)
        {
            /*Moving to the previous nodes when the digits are equal*/
            if(tail1->data == tail2->data )
            {
                tail1 = tail1->prev;
                tail2 = tail2->prev;
            }

            /*The first number is greater if its current digit is larger*/
            else if(tail1->data > tail2->data) 
            {
                return SUCCESS;
            }
            else
                /*The first number is smaller if its current digit is smaller*/
                return FAILURE;
        }
    }

    /*Returning SUCCESS if both numbers are equal*/
    return SUCCESS;
}

/*Freeing the memory allocated for all nodes in a doubly linked list*/
void free_list(Dlist **head ,Dlist ** tail)
{
    /*Temporary pointer used to hold the node being freed*/
    Dlist *temp;

    /*Traversing the list from the head and freeing each node*/
    while (*head != NULL)
    {
        temp = *head;
        *head = (*head)->next;
        free(temp);
    }

    /*Setting both pointers to NULL after freeing the list*/
    *head = NULL;
    *tail = NULL;

}

/*Displaying all digits stored in the linked list*/
void print(Dlist *temp)
{
    /*Traversing the list from the head to the last node*/
    while (temp != NULL)
    {
        /*Printing the digit stored in the current node*/
        printf("%d",temp->data);
        temp = temp->next;
    }

    /*Moving to the next line after printing the number*/
    printf("\n");
}

/*Removing unnecessary zeros from the beginning of the result list*/
void remove_leading_zeros(Dlist **head3)
{
    /*Removing leading zero nodes while preserving at least one node
      so that a result of zero remains represented by a single zero*/
    while(*head3 != NULL && (*head3)->next != NULL && (*head3)->data == 0)
    {
        /*Temporarily storing the current head node*/
        Dlist *temp = *head3;

        /*Moving the head pointer to the next node*/
        *head3 = (*head3)->next;

        /*Updating the previous pointer of the new head*/
        (*head3)->prev = NULL;

        /*Freeing the removed leading-zero node*/
        free(temp);

    }
}