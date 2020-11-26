#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "safeinput.h"
#include <stdbool.h>
#include <time.h>
#include <string.h>


typedef struct
{
    int number;
    bool access;
    time_t time;
}CARDS;

typedef struct
{
    CARDS* allCards;
    int numberOfCards;

}LISTOFCARDS;

char* timestamp(time_t tiktok)
{
    char* timeString = (char*)malloc(sizeof(char) * 30);
    struct tm* tm;
    tm = localtime(&tiktok);
    strftime(timeString, 30, "%c", tm);
    return timeString;
}


void fakeOpenDoor()
{
    printf("CURRENTLY LAMP IS: Green. The door is open for 3 seconds. RUN!\n");
}

void listOfAllCards(LISTOFCARDS* state)
{

    for (int i = 0; i < state->numberOfCards; i++)
    {
        CARDS c = state->allCards[i];
        char* access = c.access == 1 ? "Has Access." : "Does not have access.";
        printf("%d %s %s \n", c.number, access, timestamp(c.time));
    }
}

void NewCard(LISTOFCARDS* state)
{
    printf("ADD NEW CARD\n");

    int indexForTheNewOne;
    if (state->numberOfCards == 0)
    {
        state->allCards = malloc(sizeof(CARDS));
        state->numberOfCards = 1;
        indexForTheNewOne = 0;

    }
    else
    {
        state->allCards = realloc(state->allCards,
            sizeof(CARDS) * (state->numberOfCards + 1));
        indexForTheNewOne = state->numberOfCards;
        state->numberOfCards++;
    }
    int cardNumber;
    char gotAccess;
    GetInputInt("Enter Card Number: ", &cardNumber);
    printf("Grant access? y/n: \n");
    scanf("%c", &gotAccess);
    bool access = false;
    if (gotAccess == 'y')
    {
        access = true;
    }
    else if (gotAccess == 'n')
    {
        access = false;
    }
    CARDS cardHolder = { cardNumber, access, time(0) };
    state->allCards[indexForTheNewOne].number = cardHolder.number;
    state->allCards[indexForTheNewOne].access = cardHolder.access;
    state->allCards[indexForTheNewOne].time = cardHolder.time;
    printf("Card #%d was successfully added:\n%s\n", cardNumber, timestamp(time(0)));

}

void ChangeAccess(LISTOFCARDS* state, int lookFor)
{
    char choice;
    for (int i = 0; i < state->numberOfCards; i++)
    {
        if (state->allCards[i].number == lookFor)
        {
            printf("Change access? y/n: \n");
            scanf("%c", &choice);
            if (choice == 'y')
            {
                state->allCards[i].access = true ? false : true;
                CARDS c = state->allCards[i];
                char* access = c.access == 1 ? "Access." : "No Access.";
                printf("Access changed to: \"%s\".\n", access);
            }
            else {
                break;
            }

        }
        else
        {
            printf("This card does not exist.\n");
            NewCard(state);
        }
    }

}

void addRemoveMenu(LISTOFCARDS* state)
{
    while (true)
    {
        printf("REGISTER NEW ACCES CARD\n");
        printf("1. Add Card\n2. Exit\n");
        int selection;
        if (GetInputInt("Select option: ", &selection) == false)
            continue;
        switch (selection)
        {
        case 1:
            NewCard(state);
            break;
        case 2:
            break;
        }
        break;
    }
}

void remoteAccess(LISTOFCARDS* state, int lookfor)
{
    CARDS card;
    for (int i = 0; i < state->numberOfCards; i++)
    {
        if (state->allCards[i].number == lookfor)
        {
            card = state->allCards[i];
        }
    }

    const char* out = card.access == true ? "GREEN LIGHT: door is open\n" : "RED LIGHT: door is closed\n";
    printf("%s", out);

}

int FakeTest(LISTOFCARDS* state)
{
    /*int testcard;
    printf("Please scan card to enter or x to go back to admin mode\n");
    printf("CURRENTLY LAMP IS: off\n");
    printf("Scan card ");
    scanf("%s", &testcard);
    if (card has access)
        printf("CURRENLTY LAMP IS: Green\n");
    else
        printf("CURRENTLY LAMP IS: Red");
    return 0;*/
}


void Huvudmeny(LISTOFCARDS* state)
{
    while (true)
    {
        printf("MAIN MENU\n");
        printf("1. List all cards.\n2. Add Card.\n3. Remote Access.\n4. Remote open door.\n5. Change Access\n9. Fake test scan card\n");
        int choice;
        int selection;
        int lookFor;
        if (GetInputInt("Select option: ", &selection) == false)
            continue;
        switch (selection)
        {
        case 1:
            listOfAllCards(state);
            break;

        case 2:
            addRemoveMenu(state);
            break;

        case 3:

            GetInputInt("Enter Card Number: \n", &lookFor);
            remoteAccess(state, lookFor);
            break;

        case 4:
            fakeOpenDoor();
            break;
        case 5:
            GetInputInt("Enter card to change access: ->\n", &choice);
            ChangeAccess(state, choice);
            printf("Acces has been changed for #%d %s", choice, timestamp(time(0)));
        case 9:
            FakeTest(state);


        }
    }
}

int main()
{
    LISTOFCARDS state;
    state.allCards = NULL;
    state.numberOfCards = 0;
    Huvudmeny(&state);
    return 0;
}



