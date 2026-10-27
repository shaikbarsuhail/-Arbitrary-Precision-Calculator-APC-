#include"calculator.h"

// Perform multiplication using partial products
int start_mult(Dlist *tail1, Dlist *tail2, Dlist **head, Dlist **tail)
{
    /* Temporary pointer for the first list */
    Dlist *temp1;

    /* Temporary pointer for the second list */
    Dlist *temp2 = tail2;

    /* Head and tail of the accumulated result */
    Dlist *head_R1 = NULL;
    Dlist *tail_R1 = NULL;

    /* Head and tail of the current partial product */
    Dlist *head_R2 = NULL;
    Dlist *tail_R2 = NULL;

    /* Head and tail used when adding partial products */
    Dlist *head_R = NULL;
    Dlist *tail_R = NULL;

    int count = 0;
    int data;
    int carry;
    int result;

    // Traverse the second number from right to left
    while (temp2 != NULL)
    {
        // Start from the last digit of the first number
        temp1 = tail1;

        // Reset carry for the current multiplication row
        carry = 0;

        // Free the previous partial product before creating a new one
        free_list(&head_R2, &tail_R2);

        // Insert zeros for the current decimal place
        // Example: the second partial product has one trailing zero
        for (int i = 0; i < count; i++)
        {
            if (insert_first(&head_R2, &tail_R2, 0) == FAILURE)
            {
                free_list(&head_R1, &tail_R1);
                return FAILURE;
            }
        }

        // Multiply each digit of the first number by the current digit
        while (temp1 != NULL)
        {
            // Multiply the digits and add the previous carry
            data = (temp1->data * temp2->data) + carry;

            // Extract the current result digit
            result = data % 10;

            // Calculate the carry for the next multiplication
            carry = data / 10;

            // Insert the result digit at the beginning of the partial product
            if (insert_first(&head_R2, &tail_R2, result) == FAILURE)
            {
                free_list(&head_R1, &tail_R1);
                free_list(&head_R2, &tail_R2);
                return FAILURE;
            }

            // Move to the previous digit of the first number
            temp1 = temp1->prev;
        }

        // Insert the remaining carry, if any
        if (carry != 0)
        {
            if (insert_first(&head_R2, &tail_R2, carry) == FAILURE)
            {
                free_list(&head_R1, &tail_R1);
                free_list(&head_R2, &tail_R2);
                return FAILURE;
            }
        }

        // If this is the first partial product, make it the accumulated result
        if (head_R1 == NULL)
        {
            head_R1 = head_R2;
            tail_R1 = tail_R2;

            // Transfer ownership of the partial product nodes
            head_R2 = NULL;
            tail_R2 = NULL;
        }
        else
        {
            // Add the accumulated result and the new partial product
            if (start_addition(tail_R1, tail_R2, &head_R, &tail_R) == FAILURE)
            {
                free_list(&head_R1, &tail_R1);
                free_list(&head_R2, &tail_R2);
                return FAILURE;
            }

            // Free the old lists after their values have been added
            free_list(&head_R1, &tail_R1);
            free_list(&head_R2, &tail_R2);

            // Store the newly calculated result as the accumulated result
            head_R1 = head_R;
            tail_R1 = tail_R;

            // Reset temporary result pointers
            head_R = NULL;
            tail_R = NULL;

            head_R2 = NULL;
            tail_R2 = NULL;
        }

        // Move to the next digit of the second number
        temp2 = temp2->prev;

        // Increase the decimal-place counter
        count++;
    }

    // Return the final result list through the output parameters
    *head = head_R1;
    *tail = tail_R1;

    // Reset local pointers after transferring the result
    head_R1 = NULL;
    tail_R1 = NULL;

    // Free any remaining temporary lists
    free_list(&head_R2, &tail_R2);
    free_list(&head_R, &tail_R);

    return SUCCESS;
}