#include <stdio.h>
#include <stdlib.h>

struct sPerson
{
    int age;
    struct sPerson *nextInLine;
    struct sPerson *prevInLine;
};

struct sPerson *getNewPerson(const int age)
{
    struct sPerson *newPerson = NULL;
    newPerson = malloc(sizeof(struct sPerson));
    if (newPerson!=NULL){
        newPerson->nextInLine = NULL;
        newPerson->prevInLine = NULL;
        newPerson->age = age; //accessing the value at the address (kind of like dereferencing)
        printf("created new person at %p\n", newPerson);
    } else {
        printf("Memory Allocation failure \n");
    }
    return newPerson;
};

void printPerson(const struct sPerson *person, const char *comment)
{
    if (person == NULL)
    {
        printf("%s is NULL\n", comment);
    } else {
        printf("%s: age: %d address: %p nextInLine: %p prevInLine: %p\n", comment, person->age, person, person->nextInLine, person->prevInLine);
    }

}

int main()
{
    printf("start program...\n\n");

    //Creating the pointer to a struct
    struct sPerson *first = NULL;
    struct sPerson *second = NULL;
    struct sPerson *third = NULL;
    struct sPerson *fourth = NULL;

    //just showing that it's null (not really needed).
    printPerson(first, "first");
    printPerson(second, "second");

    //Initializing a person (giving them a place in memory)
    first = getNewPerson(40);
    second = getNewPerson(20);
    third = getNewPerson(14);
    fourth = getNewPerson(19);

    //Linking structs
    first->nextInLine = second;
    second->prevInLine = first;
    second->nextInLine = third;
    third->prevInLine = second;
    third->nextInLine = fourth;
    fourth->prevInLine = third;

    printPerson(first, "first");
    printPerson(second, "second");
    printPerson(third, "third");
    printPerson(fourth, "fourth");

    //My interface
    struct sPerson *focus = first;
    char input[4];
    printf("\n\nHere is your first person \n");
    printPerson(focus, "focus");
    printf("\nType <next> <prev> or <done> to control list\n");

    while(1){
        scanf("%s",&input);

        if(strcmp(input, "next") == 0){
            if(focus->nextInLine == NULL){
                printf("Sorry, next is null. maybe the other way?\n");
            } else {
                focus = focus->nextInLine;
                printPerson(focus, "focus");
            }
        } else if(strcmp(input, "prev") == 0) {
            if(focus->prevInLine == NULL){
                printf("Sorry, prev is null. maybe the other way?\n");
            } else {
                focus = focus->prevInLine;
                printPerson(focus, "focus");
            }
        } else if(strcmp(input, "done") == 0){
            printf("Ending program...\n");
            break;
        } else { //if none of these, throw an error
            printf("You didn't type in a command in the proper syntax, try again...\n");
        }
    }

    //Cleaning up
    free(first);
    free(second);
    free(third);
    free(fourth);
    first = NULL;
    second = NULL;
    third = NULL;
    fourth = NULL;

    return 0;
}
