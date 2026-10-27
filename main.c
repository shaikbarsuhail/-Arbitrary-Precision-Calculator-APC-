#include"calculator.h"



int main(int argc, char *argv[])
{
    /*First number: head1 points to the first node and tail1 points to the last node*/
    Dlist * head1 = NULL  ;
    Dlist * tail1 = NULL;

    /*Second number: head2 points to the first node and tail2 points to the last node*/
    Dlist * head2 = NULL;
    Dlist * tail2 = NULL;

    /*Storing the result of arithmetic operations*/
    Dlist * head3 = NULL;
    Dlist * tail3 = NULL;


    /*Checking whether the correct number of command-line arguments is passed*/
    if(argc != 4)
    {
        printf("PASS ./a.out operand1 operator operand2\n");
        return FAILURE;
    }

    /*Checking whether the first operand contains valid numeric characters*/
    if (checking_operands(argv[1])  == FAILURE)
    {
        printf("Arguments 1 must should contain only constant number\n");
        return FAILURE;
    }

    /*Checking whether the second operand contains valid numeric characters*/
    if(checking_operands(argv[3])  == FAILURE)
    {
        printf("Arguments 2 must should contain only constant number\n");
        return FAILURE;
    }


    /*Checking whether the operator is one of +, -, X, or */
    if(checking_operator(argv[2]) == FAILURE)
    {
        printf("ERROR - pass any one + - X / operator\n");
        return FAILURE;
    }

    /*Inserting the digits of the first operand into the first doubly linked list*/
    if(Dlist_insert_last(&head1,&tail1,argv[1]) == FAILURE)
    {
        printf("Failed to insert digit in node\n");
        return FAILURE;
    }

    /*Inserting the digits of the second operand into the second doubly linked list*/
    if(Dlist_insert_last(&head2,&tail2,argv[3]) == FAILURE)
    {
        printf("Failed to insert digit in node\n");
        return FAILURE;
    }

    /*Extracting the signs of the first and second operands*/
    char sign1 = argv[1][0];
    char sign2 = argv[3][0];


    /*Displaying the first number along with its negative sign, if present*/
    printf("First number = ");
    if(sign1 == '-')
    {
        printf("-");
        print(head1);
    }

    else
    {
        print(head1);
    }


    /*Displaying the selected arithmetic operator*/
    printf("operator = %s\n",argv[2]);

    /*Displaying the second number along with its negative sign, if present*/
    printf("Second number = ");
    if(sign2 == '-')
    {
        printf("-");
        print(head2);
    }

    else
    {
        print(head2);
    }


    /*Identifying the operator and performing the corresponding arithmetic operation*/
    switch(operator(argv[2]))
    {
        case 0: // Addition
        {
            /*Addition: when the operands have different signs, subtract the smaller
               absolute value from the larger absolute value*/
            if((sign1 == '-' && sign2 !='-') || (sign1 != '-' && sign2 == '-'))
            {
                /*Comparing the absolute values of both operands*/
                int len = compare_list(tail1,tail2);

                if(len == SUCCESS)
                {
                    /*Subtracting the second operand from the first operand*/
                    if(start_sub(tail1,tail2,&head3,&tail3) == FAILURE)
                    {
                        /*Freeing allocated nodes if subtraction fails*/
                        free_list(&head1 ,&tail1);
                        free_list(&head2,&tail2);
                        return FAILURE;
                    }

                    /*Assigning the sign based on the first operand*/
                    if(sign1 == '-')
                    {
                        printf("SUM  = -");
                    }
                    else
                    {
                        printf("SUM  = ");
                    }
                    print(head3);

                }
                else
                {
                    /*Subtracting the first operand from the second operand*/
                    if(start_sub(tail2,tail1,&head3,&tail3) == FAILURE)
                    {
                        /*Freeing allocated nodes if subtraction fails*/
                        free_list(&head1 ,&tail1);
                        free_list(&head2,&tail2);
                        return FAILURE;
                    }

                    /*Assigning the sign based on the second operand*/
                    if(sign2 == '-')
                    {
                        printf("SUM  = -");
                    }
                    else
                    {
                        printf("SUM  = ");
                    }
                    print(head3);
                }
            }
            else
            {
                /*Adding the absolute values when both operands have the same sign*/
                if(start_addition(tail1,tail2,&head3,&tail3) == FAILURE)
                {
                    /*Freeing allocated nodes if addition fails*/
                    free_list(&head1 ,&tail1);
                    free_list(&head2,&tail2);
                    return FAILURE;
                }


                /*Displaying the addition result*/
                printf("SUM  = ");

                /*If both operands are negative, the result is negative*/
                if(sign1 == '-' && sign2 == '-')
                    printf("-");
                print(head3);
            }


        }
        break;

        case 1: // subtraction

        {
            /*Comparing the absolute values of both operands*/
            short result = compare_list(tail1, tail2);

            /*If the operands have different signs, subtracting their absolute
              values is equivalent to adding them*/
            if((sign1 == '-' && sign2 !='-') || (sign1 != '-' && sign2 =='-' ))
            {
                /*Adding the absolute values of both operands*/
                if(start_addition(tail1,tail2,&head3,&tail3) == FAILURE)
                {
                    /*Freeing allocated nodes if addition fails*/
                    free_list(&head1 ,&tail1);
                    free_list(&head2,&tail2);
                    return FAILURE;
                }

            }
            else if (result == SUCCESS)
            {
                /*Subtracting the second operand from the first when the first
                  absolute value is greater than or equal to the second*/
                if (start_sub(tail1, tail2, &head3, &tail3) == FAILURE)
                {  
                    /*Freeing allocated nodes if subtraction fails*/
                    free_list(&head1 ,&tail1);
                    free_list(&head2,&tail2);
                    return FAILURE;
                }
            }
            else
            {
                /*Subtracting the first operand from the second when the second
                  absolute value is greater than the first*/
                if (start_sub(tail2, tail1, &head3, &tail3) == FAILURE)
                {  
                    /*Freeing allocated nodes if subtraction fails*/
                    free_list(&head1 ,&tail1);
                    free_list(&head2,&tail2);
                    return FAILURE;
                }

            }


            /*Removing unnecessary zeros from the beginning of the result*/
            remove_leading_zeros(&head3);

            /*Displaying the subtraction result*/
            printf("Difference = ");

            /*Determining the result sign based on the operand signs and magnitudes*/
            if(sign1 == '-' && sign2 != '-')
            {
                printf("-");
            }
            else if(result == SUCCESS && sign1 == '-')
            {
                printf("-");
            }
            else if(result == FAILURE && sign2 != '-')
            {
                printf("-");
            }
            print(head3);
        }
        break;

        case 2: //Multiplication
        {
            /*Multiplying the absolute values of both operands*/
            if(start_mult(tail1,tail2 ,&head3,&tail3) == FAILURE)
            {
                printf("Multiplication failed\n");

                /*Freeing allocated nodes if multiplication fails*/
                free_list(&head1,&tail1);
                free_list(&head2,&tail2);
                return FAILURE;
            }

            /*Removing unnecessary zeros from the beginning of the result*/
            remove_leading_zeros(&head3);

            /*Displaying the multiplication result*/
            printf("Multiplication = ");

            /*The result is negative when exactly one operand is negative*/
            if((sign1 == '-' && sign2 != '-') || (sign1 != '-' && sign2 == '-'))
            {
                /*Avoiding a negative sign when the result is zero*/
                if(head3->data != 0)
                    printf("-");
            }

            print(head3);
        }

        break;

        case 3:// Division
        {
            /*Checking whether the divisor is zero*/
            if( head2->data == 0 && head2->next == NULL)
            {
                printf("Division by zero is not allowed\n");
                return FAILURE;
            }

            /*If the dividend's absolute value is smaller than the divisor,
              the integer division result is zero*/
            else if(compare_list(tail1,tail2) == FAILURE)
            {
                printf("Result = ");
                printf("0\n");
                break;
            }

            /*Performing division using the linked lists*/
            else if(start_div(head1,head2,tail2,&head3,&tail3) == FAILURE)
            {
                printf("Division failed\n");

                /*Freeing allocated nodes if division fails*/
                free_list(&head1,&tail1);
                free_list(&head2,&tail2);
                return FAILURE;
            }

            /*Displaying the division result*/
            printf("Division = ");

            /*The quotient is negative when exactly one operand is negative*/
            if((sign1 =='-' && sign2 != '-') || (sign1 !='-' && sign2 == '-' ))
            {
                printf("-");
            }
            print(head3);

        }
        break;
    }

    /*Freeing the memory allocated for all three doubly linked lists*/
    free_list(&head1 ,&tail1);
    free_list(&head2,&tail2);
    free_list(&head3,&tail3);

    /*Returning SUCCESS to indicate successful program execution*/
    return SUCCESS; 

}