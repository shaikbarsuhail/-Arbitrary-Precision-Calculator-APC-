#include"calculator.h"

// Perform addition of two numbers represented by doubly linked lists
int start_addition(Dlist *tail1, Dlist *tail2, Dlist **head, Dlist **tail)
{
    int result = 0;
    int carry = 0;

    // Process digits from right to left until both lists are exhausted
    while (tail1 != NULL || tail2 != NULL)
    {
        // If both lists contain digits
        if (tail1 != NULL && tail2 != NULL)
        {
            // Add the current digits and the previous carry
            result = tail1->data + tail2->data + carry;

            // Separate the result digit and calculate the next carry
            checking_result(&result, &carry);

            // Insert the result digit at the beginning of the result list
            if (insert_first(head, tail, result) == FAILURE)
            {
                printf("Result list inserting failed\n");
                return FAILURE;
            }

            // Move to the previous digits in both lists
            tail1 = tail1->prev;
            tail2 = tail2->prev;
        }
        // If only the first list contains digits
        else if (tail1 != NULL && tail2 == NULL)
        {
            // Add the remaining digit and carry
            result = tail1->data + carry;
            checking_result(&result, &carry);

            if (insert_first(head, tail, result) == FAILURE)
            {
                printf("Result list inserting failed\n");
                return FAILURE;
            }

            // Move to the previous digit of the first list
            tail1 = tail1->prev;
        }
        // If only the second list contains digits
        else if (tail1 == NULL && tail2 != NULL)
        {
            // Add the remaining digit and carry
            result = tail2->data + carry;
            checking_result(&result, &carry);

            if (insert_first(head, tail, result) == FAILURE)
            {
                printf("Result list inserting failed\n");
                return FAILURE;
            }

            // Move to the previous digit of the second list
            tail2 = tail2->prev;
        }
    }

    // If a carry remains after processing all digits, insert it
    if (carry == 1)
    {
        if (insert_first(head, tail, carry) == FAILURE)
        {
            printf("Result list inserting failed\n");
            return FAILURE;
        }
    }

    return SUCCESS;
}
