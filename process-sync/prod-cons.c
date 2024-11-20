#include <stdio.h>

#define BUFFER_SIZE 10

int buffer[BUFFER_SIZE];
int in = 0, out = 0;
int count = 0;

void produce(int item)
{
    if (count == BUFFER_SIZE)
    {
        printf("Buffer is full\n");
    }
    else
    {
        buffer[in] = item;
        in = (in + 1) % BUFFER_SIZE;
        count++;
        printf("Produced value is %d\n", item);
    }
}

void consume()
{
    if (count == 0)
    {
        printf("Buffer is empty\n");
    }
    else
    {
        int item = buffer[out];
        out = (out + 1) % BUFFER_SIZE;
        count--;
        printf("Consumed value is %d\n", item);
    }
}

int main()
{
    int choice = 0;
    int item;

    while (choice != 3)
    {
        printf("\n1. Produce\n2. Consume\n3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            printf("Enter the value to produce: ");
            scanf("%d", &item);
            produce(item);
            break;

        case 2:
            consume();
            break;

        case 3:
            printf("Exiting...\n");
            break;

        default:
            printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}