#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

int ArrayAdder();
int ArrayRemover();
int main()
{

    char *arr[20] = {"first one", "second one", "third one"};

    char **temp = (char **)calloc(20, sizeof(char *));
    char something[100];

    int choice = 0;
    int index;

    while (TRUE)
    {

        printf("What do you want to do \n1. add\n2. delete\n3. exit\n");
        scanf("%d", &choice);

        if (choice == 1)
        {

            printf("\nwhat do you want to add: ");

            
            fgets(something, 99, stdin);

            ArrayAdder(arr, something, &temp);

            for (int i = 0; i < 4; i++)
            {
                printf("%d. %s\n", i + 1, temp[i]);
            }
        }
        else if (choice == 2)
        {
            printf("which data you want to alter provide with number (1 or 2 or 3): ");
            scanf("%d", &index);

            ArrayRemover(index, &temp, temp);

            for (int i = 0; i < 20; i++)
            {
                if (temp[i] != NULL)
                {
                    printf("%d. %s\n", i + 1, temp[i]);
                }
                else
                {
                    continue;
                }
            }
        }

        else if(choice == 3){
            return -1;
        }
        else{
            printf("please enter the correct value\n");
        }
            
        }
    }


int ArrayAdder(char *parr[], char *something, char ***tempers)
{

    int i;
    char **temp = (char **)calloc(20, sizeof(char *));

    for (i = 0; i < 20; i++)
    {

        if (parr[i] != NULL)
        {
            temp[i] = parr[i];
        }
        else
        {
            break;
        }
    }

    temp[i] = something;

    *tempers = temp;

    return 0;
}

// The array adder has been created now create a remove optioner now that removes the daily details

int ArrayRemover(int index, char ***triplearray, char **array)
{
    int i;

    // allocating heap because not to get any error later.
    char **temp = (char **)calloc(20, sizeof(char *));

    // if index = 1 then we have to remove the first element so
    if (index == 1)
    {
        int n = 0;
        for (i = 1; i < 20; i++)
        {
            if (array[i] != NULL)
            {

                temp[n] = array[i];

                n++;
            }
            else
            {
                printf("null hitted break\n");
                break;
            }
        }
    }

    else
    {

        // if index is greater than one we have to use index-1 because the index is startign from 1 in user point of view
        for (i = 0; i < (index - 1); i++)
        {
            if (array[i] != NULL)
            {
                temp[i] = array[i];
                // printf("%s",array[i]);
            }
            else
            {
                // printf("Null hitted break\n");
                break;
            }
        }

        // now removing the array
        for (int j = i + 1; j < 20; j++)
        {
            if (array[j] != NULL)
            {
                temp[j - 1] = array[j];
            }
            else
            {
                // printf("null hitted second \n");
                break;
            }
        }
    }
    // as we want to take the value of the array to the calle we have to use pass by refrence;
    *triplearray = temp;
}