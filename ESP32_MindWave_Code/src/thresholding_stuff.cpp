#include <iostream>
#include <stdio.h>

#define SAMPLE_COUNT 10
#define ARRAY_SIZE 5
using namespace std;

int main()
{

    int incoming_value;
    int value_array[ARRAY_SIZE];
    int old_value = 0;
    bool sample_flag = false;
    int sample_count = 0;
    int running_sum = 0;

    printf("Enter a value : ");

    // for(int i = 0; i < 5; i++)
    while (sample_flag == false)
    {
        printf("Enter a value : ");
        scanf("%d", &incoming_value);

        if (incoming_value != old_value && incoming_value > 0)
        {
            // Store the values here
            // printf("Not the same\r\n");

            if (sample_count == 5)
            {
                printf("\r\nMAX REACHED \r\n");
                sample_flag = true;
                // break;
            }
            else
            {
                value_array[sample_count] = incoming_value;
                // running_sum += value_array[sample_count];

                // printf("Value inserted : %d || Count : %d ", value_array[sample_count], sample_count);

                sample_count++;
            }
            // value_array[i] = incoming_value;
        }
        else
        {
            // Ignore the values here
            int ignore_value = incoming_value;
            printf("VALUE NOT SAVED\r\n");
        }

        // Store previous value here
        old_value = incoming_value;
    }

    cout << "-----------------" << endl;

    printf("Sum : ", running_sum);

    int array_size = sizeof(value_array) / sizeof(value_array[0]);

    for (int i = 0; i < array_size; i++)
    {
        running_sum += value_array[i];

        printf("Value inserted : %d || Count : %d  || Running sum : %d \r\n", value_array[i], i, running_sum);

        //printf("%d \r\n", value_array[i]);
    }

    printf("Average : %d \r\n",running_sum/array_size);

    return 0;
}
