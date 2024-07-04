#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char* argv[])
{

    // init k, and check if iter was given
    int k = atoi(argv[1]);
    int iter;

    if (argc == 3)
    {
        iter = atoi(argv[2]);
    }
    else
    {
        iter = 200; // default value for iter if not given
    }

    // delete later
    printf("k = %d, iter = %d\n", k, iter);
    
    // ch will be our temporary character
    // vec dim will define the number of entries in each vector
    char ch;
    int vecdim = 0;

    // allocate memory for curr_dbl
    size_t curr_dbl_size = 10; 
    char *curr_dbl = malloc(curr_dbl_size * sizeof(char));
    size_t curr_dbl_index = 0;

    // make sure memory was allocated
    if (curr_dbl == NULL)
    {
        printf("Failed to allocate memory");
        return 1;
    }

    // first vector will be a dynamic array of doubles
    double *first_vec = malloc(sizeof(double));
    char is_first = 1; // boolean to check if we are on the first vector

    ch = getchar();
    
    // iterating over the first vector to find its dimension
    while (ch != '\n')
    {
        if (ch == ',')
        {
            curr_dbl[curr_dbl_index] = '\0'; // terminate our string

            // cast our entry into a double
            double entry = atof(curr_dbl);
            
            // we need to reallocate memory for one more double in our first vector
            first_vec = realloc(first_vec, (vecdim+1) * sizeof(double));
            if (first_vec == NULL)
            {
                printf("Failed to reallocate memory");
                return 1;
            }

            // add the current double to our first vector
            first_vec[vecdim] = entry;
            
            vecdim++; // increment the number of entries in the vector
            curr_dbl_index = 0; // reset the index
        }
        else // we need to append chars to curr_dbl
        {
            // we need to reallocate memory
            if (curr_dbl_index+1 >= curr_dbl_size) // +1 for the null terminator
            {
                curr_dbl_size *= 2; // double buffer size
                curr_dbl = realloc(curr_dbl, curr_dbl_size * sizeof(char)); // reallocate the memory

                // make sure memory was reallocated
                if (curr_dbl == NULL)
                {
                    printf("Failed to reallocate memory");
                    return 1;
                }
            }

            // else, no need to reallocate memory
            curr_dbl[curr_dbl_index] = ch;
            curr_dbl_index++;
        }
        // move on to next character
        ch = getchar();
    }
    
    // ------ add the last entry to vector ---------
    curr_dbl[curr_dbl_index] = '\0'; // terminate our string

    // cast our entry into a double
    double entry = atof(curr_dbl);
    
    // we need to reallocate memory for one more double in our first vector
    first_vec = realloc(first_vec, (vecdim+1) * sizeof(double));
    if (first_vec == NULL)
    {
        printf("Failed to reallocate memory");
        return 1;
    }

    // add the current double to our first vector
    first_vec[vecdim] = entry;
    
    vecdim++; // increment the number of entries in the vector
    curr_dbl_index = 0; // reset the index

    //-------------done with first vector----------------

    // init vector array of arrays
    double **vec_arr = malloc(sizeof(first_vec));
    vec_arr[0] = first_vec;
    ch = getchar();
    
    while (ch != EOF) 
    {
        double curr_vec[vecdim];
        for (int i=0;i<vecdim;i++)
        {
            while (ch != ',' && ch != '\n')
            {
                // we need to reallocate memory
                if (curr_dbl_index+1 >= curr_dbl_size) // +1 for the null terminator
                {
                    curr_dbl_size *= 2; // double buffer size
                    curr_dbl = realloc(curr_dbl, curr_dbl_size * sizeof(char)); // reallocate the memory

                    // make sure memory was reallocated
                    if (curr_dbl == NULL)
                    {
                        printf("Failed to reallocate memory");
                        return 1;
                    }

                }
                // else, no need to reallocate memory
                curr_dbl[curr_dbl_index] = ch;
                curr_dbl_index++;

                // move on to next character
                ch = getchar();
            }

            //we reached the end of a float
            curr_dbl[curr_dbl_index] = '\0'; // terminate our string

            // cast our entry into a double
            double entry = atof(curr_dbl);

            // add the current double to our first vector
            curr_vec[i] = entry;
            
            curr_dbl_index = 0; // reset the index

            ch = getchar(); // move on to next character
        }

        //print curr_vec
        for (int i=0;i<vecdim;i++)
        {
            printf("%f\n", curr_vec[i]);
        }
        break;
    }
    return 0;
}
