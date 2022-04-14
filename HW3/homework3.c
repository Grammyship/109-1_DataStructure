#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

void print_menu()
{
    printf("Menu:                                                  \n");
    printf("(1) Enter a matrix                                     \n");
    printf("(2) Display a matrix                                   \n");
    printf("(3) Display a submatrix                                \n");
    printf("(4) Display a transpose matrix                         \n");
    printf("(5) Add two matrix together                            \n");
    printf("(6) Multiply a matrix with k times                     \n");
    printf("(7) Exit                                               \n\n");
}

int check_size(int32_t x)
{
    if (x > 10)
    {
        printf("The teacher says the matrix must be smaller than 10 x 10 :(\n");
        return 1;
    }
    else if (x < 1)
    {
        printf("You can't make a matrix be smaller than 1 x 1 :(\n");
        return 1;
    }

    return 0;
}

typedef struct Data
{
    int row, col;
    int element;
}data;

typedef struct Matrix
{
    int row, col; // must be < 10 (by teacher)
    int start, end;
    int num;
}matrix;

data m[1024]; // I can save at most 1024 elements
matrix n[20]; // I can save at most 20 matrices
char name[20][500]; // name of matrices


int enter_matrix( FILE *f , data m[1024] , matrix n[20] , int count )
{
    int x, y;
    // enter row
    printf( "Please enter row of the matrix:" );
    fscanf(f, "%d", &x);
    if(check_size(x))
    {
        return 0;
    }    
    // enter column
    printf( "Please enter column of the matrix:" );
    fscanf(f, "%d", &y);
    if (check_size(y))
    {
        return 0;
    }
    // enter element count
    int zero = 0;
    printf( "Please enter how many elements in \"%s\" are not zero:" , name[count] );
    fscanf(f, "%d" , &zero);
    if( zero < 0 || zero > x*y )
    {
        printf("Wrong elements number :(\n");
        return 0;
    }
    int i = 0;
    for(i = 0; i < 1024; i++)
    {
        if(m[i].element == 0 )
            break;
    }

    //printf("%d\n", i);

    n[count].row = x;
    n[count].col = y;
    n[count].num = zero;
    n[count].start = i;
    //printf("<%d>\n", n[count].start);

    for( int j = 0; j < zero; j++ )
    {
        printf("\nPlease enter data by rules of the sparse matrix\n");
        printf("row , col , element:");
        scanf("%d , %d , %d", &m[j+i].row , &m[j+i].col , &m[j+i].element );
        if( m[j+i].row < 0 || m[j+i].row >= x || m[j+i].col < 0 || m[j+i].col >= y || m[j+i].element == 0 )
        {
            printf("Wrong input :(\n");
            return 0;
        }
        printf("\n");
    }
    n[count].end = n[count].start+zero-1;
    //printf("<%d>\n", n[count].end);
    return 1;
}


void print_matrix( data *m, matrix *n, char name[20][500] , int count , int row[10] , int col[10] )
{
    int32_t s , e, zero;
    zero = 0;
    s = n[count].start;
    e = n[count].end;
    //printf("<%d>\n", n[count].start);
    //printf("<%d>\n\n", n[count].end);
    printf("Matrix \"%s\":\n", name[count] );
    for (int i = 0; i < n[count].row; i++)
    {
        for (int j = 0; j < n[count].col; j++)
        {
            if ( row[i] && col[j] )
            {
                int success = 0;
                for(int k = s; k <= e; k++ )
                {
                    if( i == m[k].row && j == m[k].col )
                    {
                        printf("%4d" , m[k].element );
                        success = 1;
                        break;
                    }       
                }
                if( !success )
                    printf("%4d", zero);
            }
            else
                printf("    ");
        }
        printf("\n");
    }
    printf("\n");
}

void transpose_matrix(data *m, matrix *n, char name[20][500], int count)
{
    int32_t s, e, zero;
    zero = 0;
    s = n[count].start;
    e = n[count].end;

    printf("Transpose matrix \"%s\":\n", name[count]);
    for (int i = 0; i < n[count].col; i++)
    {
        for (int j = 0; j < n[count].row; j++)
        {
            int success = 0;
            for (int k = s; k <= e; k++)
            {
                if (i == m[k].col && j == m[k].row)
                {
                    printf("%4d", m[k].element);
                    success = 1;
                    break;
                }
            }
            if (!success)
                printf("%4d", zero);
        }
        printf("\n");
    }
    printf("\n");
}

int ans = 0;

void add_matrix(matrix x , matrix y , data *m )
{
    // check size
    if( x.row != y.row || x.col != y.col )
    {
        printf("Wait! These two matrices aren't in the same size :(\n");
        return;
    }

    //calculate answer

    //printf("%d_%d\n" , x.start , x.end);
    //printf("%d_%d\n", y.start, y.end);
    printf("Result:\n\n");
    for (int i = 0; i < x.row; i++)
    {
        for (int j = 0; j < x.col; j++)
        {
            ans = 0;
            for (int k = x.start ; k <= y.end; k++)
            {
                //printf("%d_%d_%d\n", m[k].row , m[k].col, m[k].element);
                if (i == m[k].row && j == m[k].col)
                {
                    ans += m[k].element;                    
                }
            }
            printf("%4d" , ans );
        }
        printf("\n");
    }
    printf("\n");

}


int main()
{
    printf("Data Structure Homework3, written by 40847041S 朱自宇  \n");
    printf("                                                       \n");

    int count = 0, mode = 0;
    // initialize data
    for( int k = 0; k < 1024; k++)
    {
        m[k].row = 0;
        m[k].col = 0;
        m[k].element = 0;
    }
    while(1)
    {
        if( mode == 7 )
            break;
        print_menu();
        printf("Your choice(1~7):\n");

        if (scanf("%d", &mode) < 1)
        {
            printf("You have to enter number 1~7, not english words, please restart :(\n\n");
            return -1;
        }

        if(mode <= 0 || mode >= 8)
        {
            printf("You have to enter number 1~7 :(\n");
            continue;
        }

        printf( "\n" );

        switch(mode)
        {
            case 1:
            {   
                printf( "You choose case 1......\n\n" );

                // check capacity
                if( count == 20 )
                {
                    printf("Oops, the capacity is full, which means that you can't save any matrix now :(\n");
                    break;
                }

                printf("Please enter the matrix name:");
                scanf( "%s", &name[count]);
                if( !enter_matrix( stdin , m , n , count ) )
                {
                    printf("Error, stop working :(\n");
                    return -1;
                }
                printf("Your matrix \"%s\" has been saved :)\n", name[count] );
                printf("It has %d rows and %d columns, total of %d non-zero elements.\n" , n[count].row , n[count].col , n[count].num );
                count++;
                break;
            }
            
            case 2:
            {
                printf("You choose case 2......\n\n");
                printf("Please enter the matrix name:");

                char name_mat[20]; // name of matrix
                for (int i = 0; i < 20; i++)
                {
                    name_mat[i] = 0;
                }

                if (scanf("%s", &name_mat) <= 0)
                    return -1;
                //printf( "<%s>\n" , name_mat );

                int i = 0 , success = 0;

                for( i = 0; i < 20; i++ )
                {
                    if (strncmp(name[i], name_mat, strlen(name_mat)) == 0)
                    {
                        success = 1;
                        break;
                    }
                }

                if( !success )
                {
                    printf( "Oops, looks like we don't have a matrix called \"%s\" here :(\n", name_mat );
                    break;
                }

                int row[10] , col[10];
                for( int j = 0; j < 10; j++ )
                {
                    row[j] = 1;
                    col[j] = 1;
                }
                //printf("<%d>\n" , i );
                print_matrix( m , n , name , i , row , col );
                break;
            }
            
            case 3:
            {
                printf("You choose case 3......\n\n");
                printf("Please enter the matrix name:");

                char name_mat[20]; // name of matrix
                for (int i = 0; i < 20; i++)
                {
                    name_mat[i] = 0;
                }

                if (scanf("%s", &name_mat) <= 0)
                    return -1;
                //printf( "<%s>\n" , name_mat );

                int i = 0, success = 0;

                for (i = 0; i < 20; i++)
                {
                    if (strncmp(name[i], name_mat, strlen(name_mat)) == 0)
                    {
                        success = 1;
                        break;
                    }
                }

                if (!success)
                {
                    printf("Oops, looks like we don't have a matrix called \"%s\" here :(\n", name_mat);
                    break;
                }

                int sub_row = 0 , sub_col = 0;
                int Srow[10] = {0}, Scol[10] = {0}, temp = 0;

                // print submatrix row
                printf("The matrix \"%s\" has %d rows\n", name[i], n[i].row);
                printf("How many rows do you want to show of the matrix \"%s\" ?\n" , name[i] );
                scanf("%d" , &sub_row );
                if (sub_row < 0 || sub_row > n[i].row )
                {
                    printf("Oops, the matrix \"%s\" doesn't have that much rows :(\n");
                    break;
                }

                printf("Which rows do you want to show of the matrix \"%s\"(0~%d) ?\n", name[i] , n[i].row-1);
            
                success = 0;
                for( int j = 0; j < sub_row; j++ )
                {
                    scanf("%d" , &temp );
                    if(temp < 0 || temp > n[i].row)
                    {
                        success = 1;
                        printf("The matrix \"%s\" doesn't have this row :(\n" , name[i]);
                        break;
                    }
                    Srow[temp] = 1;
                }
                if( success )
                    break;

                // print submatrix column
                printf("\nThe matrix \"%s\" has %d columns\n", name[i], n[i].col);
                printf("How many columns do you want to show of the matrix \"%s\" ?\n", name[i]);

                scanf("%d", &sub_col);
                if (sub_col < 0 || sub_col >= n[i].col)
                {
                    printf("Oops, the matrix \"%s\" doesn't have that much columns :(\n" , name[i]);
                    break;
                }

                printf("Which columns do you want to show of the matrix \"%s\"(0~%d) ?\n", name[i], n[i].col-1);

                temp = 0;
                success = 0;
                for (int j = 0; j < sub_col; j++)
                {
                    scanf("%d", &temp);
                    if (temp < 0 || temp >= n[i].col)
                    {
                        success = 1;
                        printf("The matrix \"%s\" doesn't have this column :(\n");
                        break;
                    }
                    Scol[temp] = 1;
                }
                printf("\nYou choose to print:\n");
                printf("Rows: ");
                for( int k = 0; k < 10; k++ )
                {
                    if(Srow[k])
                        printf("%d " , k );
                }
                printf("\nColumns: ");
                for (int k = 0; k < 10; k++)
                {
                    if (Scol[k])
                        printf("%d ", k);
                }
                printf("\n\n");
                print_matrix(m, n, name, i, Srow, Scol);
                break;
            }
            case 4:
            {
                printf("You choose case 4......\n\n");
                printf("Please enter the matrix name:");

                char name_mat[20]; // name of matrix
                for (int i = 0; i < 20; i++)
                {
                    name_mat[i] = 0;
                }

                if (scanf("%s", &name_mat) <= 0)
                    return -1;
                //printf( "<%s>\n" , name_mat );

                int i = 0, success = 0;

                for (i = 0; i < 20; i++)
                {
                    if (strncmp(name[i], name_mat, strlen(name_mat)) == 0)
                    {
                        success = 1;
                        break;
                    }
                }

                if (!success)
                {
                    printf("Oops, looks like we don't have a matrix called \"%s\" here :(\n", name_mat);
                    break;
                }

                transpose_matrix( m , n , name, i );
                break;
            }
            
            case 5:
            {
                printf("You choose case 5......\n\n");

                matrix x[2];
                data y[100];
                
                for( int j = 0; j < 100; j++)
                {
                    y[j].row = 0;
                    y[j].col = 0;
                    y[j].element = 0;
                }

                printf("1st matrix:\n\n");
                enter_matrix( stdin, y, x, 0 );

                printf("2nd matrix:\n\n");
                enter_matrix(stdin, y,x , 1);
                add_matrix(x[0], x[1], y); // 145

                break;
            }

            case 6:
                printf( "You choose case6:\n");
                
                break;
            
            case 7:
            {
                printf( "You choose case 7......\n\n");
                printf( "Good bye! See you next time :)\n\n" );
                break;
            }
            default:
                break;
        }

        printf("\n");
    }

    return 0;
}