#include"calculator.h"

// Perform subtraction of two numbers represented by doubly linked lists
int start_sub(Dlist *tail1, Dlist *tail2, Dlist **head, Dlist **tail)
{
    int result = 0;
    int borrow = 0;

    // Process digits from right to left
    while (tail1 != NULL || tail2 != NULL)
    {
        // Apply the borrow from the previous digit
        if (borrow == 1)
        {
            tail1->data = tail1->data - 1;
        }

        // If both lists contain digits
        if (tail1 != NULL && tail2 != NULL)
        {
            // Subtract directly if the first digit is greater than or equal
            if (tail1->data >= tail2->data)
            {
                result = tail1->data - tail2->data;
                borrow = 0;
            }
            // Borrow 1 from the next digit when necessary
            else
            {
                result = (tail1->data + 10) - tail2->data;
                borrow = 1;
            }

            // Move to the previous digits in both lists
            tail1 = tail1->prev;
            tail2 = tail2->prev;
        }
        // If only the first list contains digits
        else if (tail1 != NULL && tail2 == NULL)
        {
            // Store the remaining digit
            if (tail1->data != -1)
            {
                result = tail1->data;
            }
            else
            {
                result = tail1->data + 10;
            }

            // Move to the previous digit
            tail1 = tail1->prev;
        }

        // Insert the calculated digit at the beginning of the result list
        if (insert_first(head, tail, result) == FAILURE)
        {
            printf("Result list inserting failed\n");
            return FAILURE;
        }
    }

    return SUCCESS;
}