#include <stdio.h>

int tph, phil[20], status[20], howHungry, hu[20], chop;

void one()
{
    int pos = 0, x, i;
    printf("\nAllow one philosopher to eat at any time\n");
    for (i = 0; i < howHungry; i++, pos++)
    {
        printf("\nP %d is granted to eat", phil[hu[pos]]);
        for (x = pos; x < howHungry; x++)
            printf("\nP %d is waiting", phil[hu[x]]);
    }
}

void two(){
    int pos = 0, x, i;
    printf("\nAllow two philosophers to eat at any time\n");
    for (i = 0; i < howHungry; i++, pos++)
    {
        printf("\nP %d and P %d are granted to eat", phil[hu[pos]], phil[hu[pos + 1]]);
        for (x = pos + 2; x < howHungry; x++)
            printf("\nP %d is waiting", phil[hu[x]]);
    }
}
int main()
{
    printf("\n\nDINING PHILOSOPHER PROBLEM");
    printf("\nEnter the number of philosophers: ");
    scanf("%d", &tph);
    for (int i = 0; i < tph; i++)
    {
        phil[i] = i + 1;
        status[i] = 1;
    }
    printf("How many are hungry: ");
    scanf("%d", &howHungry);
    if (howHungry > tph)
    {
        printf("Hungry philosophers cannot be more than total philosophers");
        return 0;
    }
    else if (howHungry == tph)
    {
        printf("All philosophers are hungry, deadlock will occur");
        return 0;
    }
    else
    {
        for (int i = 0; i < howHungry; i++)
        {
            printf("Enter the philosopher number who is hungry: ");
            scanf("%d", &hu[i]);
            status[hu[i]] = 2;
        }
        do
        {
            printf("1.One can eat at a time\n2.Two can eat at a time\n3.Exit\n\nEnter your choice: ");
            scanf("%d", &chop);
            switch (chop)
            {
            case 1:
                one();
                break;
            case 2:
                two();
                break;
            case 3:
                return 0;
            default:
                printf("Invalid choice");
                break;
            }
        } while (1);
    }
}