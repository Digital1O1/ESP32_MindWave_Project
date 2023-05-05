/******************************************************************************

                              Online C++ Compiler.
               Code, Compile, Run and Debug C++ program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <iostream>
#include <stdio.h>  /* printf, scanf, puts, NULL */
#include <stdlib.h> /* srand, rand */
#include <time.h>   /* time */

using namespace std;

int main()
{
    int storage[10];
    float sum = 0;
    float random_number = 0;

    srand(time(NULL));

    for (int i = 0; i < 10; i++)
    {
        // storage[i] = rand() %10 +1;
        // printf("%d \r\n", storage[i]);
        random_number = rand() % 10 + 1;
        storage[i] = random_number;
        // printf("numbers being added : %d \r\n",random_number);
        // sum += random_number;
        sum += storage[i];
    }

    // for(int i = 0; i < sizeof(storage)/sizeof(int); i++)
    // {
    //     printf("%d ", storage[i]);
    // }

    float average = 0.0;

    int storage_array_size = sizeof(storage) / sizeof(storage[0]);
    average = sum / storage_array_size;
    // average = sum / sizeof(storage)/sizeof(storage[0]);
    printf("sum : %f\r\n", sum);
    printf("array size : %ld \r\n", sizeof(storage) / sizeof(int));
    cout << "Average : " << average << endl;
    // printf("average : %d\r\n",average);

    // printf("%d",sum);

    return 0;
}
