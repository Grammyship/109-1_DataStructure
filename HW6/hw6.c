#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <Windows.h>

typedef struct binary_tree
{
    int type;
    char data;
    struct binary_tree* left;
    struct binary_tree* right;
} BT;

typedef BT *bt;

bt create(bt node, int type , char data )
{
    node->type = type;
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    //printf("%d_%c\n", node->type, node->data);
    return node;
}

bt insert(bt node, int _type, char _data)
{
    bt new;
    bt now;

    // new node
    new = (bt) malloc(sizeof(BT));
    create(new , _type , _data );

    //printf("%d_%c\n" , new -> type , new -> data ); 
    now = node;
    if( _type == 2 )
    {
        while( now -> left != NULL )
        {
            now = now -> left;
            if( now -> left == NULL )
                break;
        }
        now -> left = new;
    }
    else
    {
        int check = 1;
        while( now -> right != NULL )
        {
            if (now-> left != NULL)
                now = now->left;
            else
            {
                now -> left = new;
                check = 0;
            }                        
        }
        if(check)
            now -> right = new;
    }

    return node;
}

void bt_print( bt node )
{
    if( node )
    {
        bt_print( node -> left );
        bt_print( node -> right );
        printf("%c", node->data);
    }
}

void free_tree( bt node )
{
    if( node)
    {
        free_tree(node->left);
        free_tree(node->right);
        free(node);
    }
}
// functions for stack

void push(float a[20], int *p, float value)
{
    if (*p >= 19)
    {
        printf("Stack full :(\n");
        return;
    }
    a[++*p] = value;
}

float pop(float a[20], int *p)
{
    if (*p <= -1)
    {
        printf("Stack empty :(\n");
        return 0;
    }
    return a[(*p)--];
}

void calu(float stack[20] , int *pt_top , char *p )
{
    if (*p >= 48 && *p <= 57)
        push(stack, pt_top , *p - 48);
    else
    {
        float num1 , num2 , ans;
        num1 = pop( stack , pt_top );
        num2 = pop( stack , pt_top );

        switch(*p)
        {
            case '+':
            {
                ans = num2 + num1;
                break;
            }
            case '-':
            {
                ans = num2 - num1;
                break;
            }
            case '*':
            {
                ans = num2 * num1;
                break;
            }
            case '/':
            {
                ans = num2 / num1;
                break;
            }
        }
        push( stack , pt_top , ans );
    }
}

// postfix

int pri(char s)
{
    switch (s)
    {
        case '*':
        case '/':
            return 2;
        case '+':
        case '-':
            return 1;

        default:
            return 0;
    }
}

void postfix(char* s , char* temp )
{
    char stack[20]=  {'\0'};
    int k = 0 , top = 0;
    for (int i = 0; i < strlen(s); i++)
    {
        switch (s[i])
        {
            // check the priority to stack
            case '+':
            case '*':
            case '/':
            {
                while (pri(stack[top]) >= pri(s[i])) // if bigger , save the answer
                {
                    temp[k] = stack[top];
                    top--;
                    k++;
                }
                stack[++top] = s[i]; // stack this operator
                break;
            }
            case '-': // calculate negative numbers
            {
                if( s[i-1] == '(' )
                {
                    temp[k] = '0';
                    k++;
                }
                while (pri(stack[top]) >= pri(s[i])) // if bigger , save the answer
                {
                    temp[k] = stack[top];
                    top--;
                    k++;
                }
                
                stack[++top] = s[i]; // stack this operator                          
                break;
            }
            case '(':
            {
                stack[++top] = s[i]; // just stack it
                break;
            }
            case ')':
            {
                while (stack[top] != '(') // search for the nearest '('
                {
                    temp[k++] = stack[top--];
                    //printf("%c", temp[k]);
                }
                top--;
                break;
            }
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
            {
                //printf( "%c" , s[i] );
                temp[k] = s[i];                
                k++;
                break;
            }
            default:
            {
                printf("Error.\n");
                break;
            }
        }
    }
    while (top > 0) // save all the things left
        temp[k++] = stack[top--];
}





// below are checking-input functions 

int length(char s[51])
{
    if (strlen(s) > 20)
    {
        printf("\nError - line contains more characters than allowed.\n");
        return 0;
    }
    return 1;
}

int num(char s) // not 0~9 or operator or '()'
{
    if (s == 32) // space
    {
        printf("\nSpace should not appear in this program.\n");
        return 0;
    }
    else if (s < 40 || s > 57 || s == 44 || s == 46)
    {
        printf("\nIllegal character.\n");
        return 0;
    }
    return 1;
}

int CO( char s ) // character is an operator
{
    if( s==42 || s==43 || s==45 || s==47 )
    {
        return 0;
    }
    return 1;
}
// end of the functions






int main()
{
    system("CLS");
    printf("40847041S朱自宇_Data Structure_HW6\n\n");
    while(1)
    {
        char s[51];
        int count = 0;
        int op = 0;
        int false = 0;

        // input
        printf("Please enter an infix expression and press enter:\n");
        if (fgets(s, 50, stdin) == NULL)
        {
            printf("\nError!\n");
            return -1;
        }

        if (s[strlen(s) - 1] == '\n')
            s[strlen(s) - 1] = '\0';
        if (!length(s))
        {
            false = 1;
        }

        if( !CO(s[0] ))
        {
            printf("\nFirst character an operator.\n");
            false = 1;
        }

        if( false )
        {
            printf("\nLooks like you have some problem :(\nShutting down...\n");
            return -1;
        }

        else
        {
            for (int i = 0; i < strlen(s); i++)
            {
                if (!num(s[i]))
                    false = 1;

                if (s[i] == 40)
                {
                    count++;
                    if (i == strlen(s) - 1);
                    else
                    {
                        if (s[i+1] == 41 )
                        {
                            printf("\nLeft parenthesis followed by a right parenthesis.\n");
                            false = 1;
                        }
                        else if(!CO(s[i+1]) )
                        {
                            if( s[i+1] == '-' )
                                continue;
                            else
                                printf("\nLeft parenthesis followed by an operator.\n");
                                false = 1;
                        }
                    }
                }

                if( s[i] == 41 )
                {
                    count--;
                    if (i == strlen(s) - 1);
                    else
                    {
                        if (s[i+1] == 40 )
                        {
                            printf("\nRight parenthesis followed by a left parenthesis.\n");
                            false = 1;
                        }
                        
                        if( CO(s[i+1]) && s[i+1] != 40 && s[i+1] != 41 )
                        {
                            printf("\nRight parenthesis followed by an identifier.\n");
                            false = 1;
                        }
                    }
                }

                if( !CO(s[i]) )
                {
                    op++;
                    if (i == strlen(s)-1 );
                    else
                    {
                        if (s[i+1] == 41 )
                        {
                            printf("\nOperator followed by a right parenthesis.\n");
                            false = 1;
                        }
                        if (!CO(s[i + 1]))
                        {
                            printf("\nOperator followed by an operator.\n");
                            false = 1;
                        }
                    }
                }

                if( CO(s[i]) && s[i] != 40 && s[i] != 41 )
                {
                    if (i == strlen(s) - 1)
                        continue;
                    else
                    {
                        if (s[i+1] == 40)
                        {
                            printf("\nIdentifier followed by a left parenthesis.\n");
                            false = 1;
                        }                    
                    }
                }
            }
        }

        if( op == 0 )
        {
            printf("\nIllegal operand.\n");
            false = 1;
        }

        if (!CO(s[strlen(s)-1]))
        {
            printf("\nLast character an operator.\n");
            false = 1;
        }

        if (count > 0)
        {
            printf("\nUnmatched left parenthesis.\n");
            false = 1;
        }
        else if (count < 0)
        {
            printf("\nUnmatched right parenthesis.\n");
            false = 1;
        }

        if( false )
        {
            printf("\nLooks like you have some problem :(\nShutting down...\n\n");
            return -1;
        }

        // postfix
        char temp[20] = {'0' , '\0'};
        printf("\nThe postfix expression: ");
        postfix( s , temp );

        // tree
        BT Tree;
        bt tree = &Tree;
        create(tree , 2 , temp[strlen(temp)-1] );
        for( int i = strlen(temp)-2; i >= 0; i-- )
        {
            if (temp[i] == '+' || temp[i] == '-' || temp[i] == '*' || temp[i] == '/' )
                insert( tree , 2 , temp[i] );
        }
        for (int i = strlen(temp) - 2; i >= 0; i--)
        {
            if (temp[i] >= 48 && temp[i] <= 57)
                insert(tree, 1, temp[i]);
        }
        for (int i = 0; i < strlen(temp); i++)
            printf("%c", temp[i]);
        //bt_print(tree);
        printf("\n");

        // calculate the answer
        char* p = temp;
        float stack[20];
        int top = -1;
        int *pt_top = &top;
        while( *p != '\0' )
        {
            calu(stack , pt_top , p );
            p++;
        }

        printf("\n= %.2f", pop(stack , pt_top) );
        printf("\n\nIf you want to end the program, please press esc to leave.\nElse, press any other key to continue.\n");

        free_tree(tree);
        if( getch() == 27 )
        {
            printf("\n\nBye! See you next time ：)\n\n");
            Sleep(2000);
            system("CLS");
            return 0;
        }

        system("CLS");
    }
    return -1;
}