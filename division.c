#include"calculator.h"

// Perform division using repeated subtraction
int start_div(Dlist *head1, Dlist *head2, Dlist *tail2,
              Dlist **R_head, Dlist **R_tail)
{
    // List used to hold the current dividend portion
    Dlist *head3 = NULL;
    Dlist *tail3 = NULL;

    /* Temporary list used to store subtraction results */
    Dlist *temp_head = NULL;
    Dlist *temp_tail = NULL;

    int result = 0;
    int count;

    // Traverse the dividend from left to right
    while (head1 != NULL)
    {
        // Reset the quotient digit for the current portion
        count = 0;

        // Append the next dividend digit to the current portion
        if (dlist_insert_last(&head3, &tail3, head1->data) == FAILURE)
        {
            return FAILURE;
        }

        // Remove leading zeros while keeping at least one node
        while (head3 != NULL && head3->data == 0 && head3->next != NULL)
        {
            Dlist *temp = head3;
            head3 = head3->next;
            head3->prev = NULL;
            free(temp);
        }

        // Repeatedly subtract the divisor while the current portion
        // is greater than or equal to the divisor
        while (compare_data(head2, head3) == SUCCESS)
        {
            // Subtract the divisor from the current portion
            start_sub(tail3, tail2, &temp_head, &temp_tail);

            // Free the previous current-portion list
            free_list(&head3, &tail3);

            // Make the subtraction result the new current portion
            head3 = temp_head;
            tail3 = temp_tail;

            // Reset temporary pointers after transferring the list
            temp_head = NULL;
            temp_tail = NULL;

            // Count how many times the divisor was subtracted
            count++;
        }

        // Append the calculated quotient digit to the quotient list
        if (count >= 0)
        {
            dlist_insert_last(R_head, R_tail, count);
        }

        // Move to the next dividend digit
        head1 = head1->next;
    }

    // If the quotient is a single zero node, return immediately
    if (*R_head != NULL && (*R_head)->data == 0 && (*R_head)->next == NULL)
    {
        free_list(&head3, &tail3);
        free_list(&temp_head, &temp_tail);
        return SUCCESS;
    }

    // Remove leading zeros from the quotient
    while (*R_head != NULL && (*R_head)->data == 0)
    {
        Dlist *temp = *R_head;
        *R_head = (*R_head)->next;
        (*R_head)->prev = NULL;
        free(temp);
    }

    // Free temporary lists before returning
    free_list(&head3, &tail3);
    free_list(&temp_head, &temp_tail);

    return SUCCESS;
}