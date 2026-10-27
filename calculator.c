#include "calculator.h"

// Insert each digit of the given number into the doubly linked list
int Dlist_insert_last(Dlist **head, Dlist **tail, char *ch)
{
    int num;

    // Traverse the input string character by character
    for (int i = 0; ch[i] != '\0'; i++)
    {
        // Skip the positive and negative signs
        if (ch[i] != '+' && ch[i] != '-')
        {
            // Convert the character digit into an integer
            // Example: '5' - '0' = 5
            num = ch[i] - '0';

            // Insert the digit at the end of the list
            if (dlist_insert_last(head, tail, num) == FAILURE)
            {
                return FAILURE;
            }
        }
    }

    return SUCCESS;
}

// Create a new node and insert it at the end of the list
int dlist_insert_last(Dlist **head, Dlist **tail, int data)
{
    // Allocate memory for a new node
    Dlist *new_node = malloc(sizeof(Dlist));

    // Check whether memory allocation was successful
    if (new_node == NULL)
    {
        printf("Memory allocation failed\n");
        return FAILURE;
    }

    // Initialize the node data and links
    new_node->data = data;
    new_node->next = NULL;
    new_node->prev = NULL;

    // If the list is empty, the new node becomes both head and tail
    if (*head == NULL && *tail == NULL)
    {
        *head = new_node;
        *tail = new_node;
        return SUCCESS;
    }

    // Connect the new node after the current tail
    new_node->prev = *tail;
    (*tail)->next = new_node;

    // Update the tail to point to the new last node
    *tail = new_node;

    return SUCCESS;
}



// Compare two numbers represented by linked lists
int compare_data(Dlist *head1, Dlist *head2)
{
    Dlist *temp1 = head1; // Pointer used to traverse the first list
    Dlist *temp2 = head2; // Pointer used to traverse the second list

    int num1 = 0, num2 = 0;
    int result;

    // Convert the first list's digits into an integer
    while (temp1 != NULL)
    {
        result = temp1->data;
        num1 = num1 * 10 + result;
        temp1 = temp1->next;
    }

    // Convert the second list's digits into an integer
    while (temp2 != NULL)
    {
        result = temp2->data;
        num2 = num2 * 10 + result;
        temp2 = temp2->next;
    }

    // Return SUCCESS when the second number is greater than or equal
    // to the first number
    if (num2 >= num1)
    {
        return SUCCESS;
    }

    return FAILURE;
}

// Separate a sum into its result digit and carry
void checking_result(int *result, int *carry)
{
    // If the sum is greater than 9, a carry is generated
    if (*result > 9)
    {
        // Keep only the units digit
        *result = (*result) % 10;

        // Carry 1 to the next digit
        *carry = 1;
    }
    else
    {
        // No carry is required
        *carry = 0;
    }
}

// Create a new node and insert it at the beginning of the list
int insert_first(Dlist **head, Dlist **tail, int data)
{
    // Allocate memory for a new node
    Dlist *new_node = malloc(sizeof(Dlist));

    // Check whether memory allocation succeeded
    if (new_node == NULL)
    {
        printf("Memory allocation failed\n");
        return FAILURE;
    }

    // Initialize the node
    new_node->data = data;
    new_node->prev = NULL;
    new_node->next = NULL;

    // If the list is empty, the new node becomes both head and tail
    if (*head == NULL && *tail == NULL)
    {
        *head = new_node;
        *tail = new_node;
        return SUCCESS;
    }

    // Link the new node before the current head
    new_node->next = *head;
    (*head)->prev = new_node;

    // Update the head pointer
    *head = new_node;

    return SUCCESS;
}