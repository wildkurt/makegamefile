#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

typedef struct Card{
    char rank;
    char suit;
    char dealt;
}Card;

char rankValueToChar(int i){
    switch(i){
        case 1 : return 'A';
        case 2 : return '2';
        case 3 : return '3';
        case 4 : return '4';
        case 5 : return '5';
        case 6 : return '6';
        case 7 : return '7';
        case 8 : return '8';
        case 9 : return '9';
        case 10 : return 'T';
        case 11 : return 'J';
        case 12 : return 'Q';
        case 13 : return 'K';
    }
}

void createDeck(Card *deck){
    for(int i = 0; i < 52; i++){
        if(i<=12){
            deck[i].rank = rankValueToChar(i+1);
            deck[i].suit = 'c';
        }
        if(i > 12 && i <= 25){
            deck[i].rank = rankValueToChar(i - 12);
            deck[i].suit = 'd';
        }
        if(i > 25 && i <= 38){
            deck[i].rank = rankValueToChar(i - 25);
            deck[i].suit = 'h';
        }
        if(i > 38 && i <= 51){
            deck[i].rank = rankValueToChar(i - 38);
            deck[i].suit = 's';
        }
    }
}

void randomizeDeck(Card *deck){
    int long randindex;
    Card randomDeck[52] = {0,0,'f'};
    srand(time(0));
    for(int i = 0; i < 52; i++){
        while(1){
            randindex = rand() % 52;
            if(deck[randindex].dealt != 't'){
                randomDeck[i] = deck[randindex];
                deck[randindex].dealt = 't';
                break;
            }
        }
    }
    for(int i = 0; i < 52; i++){
        deck[i] = randomDeck[i];
    }
}

void printRandomizedGameFile(Card *deck){
    FILE *output;
    output = fopen("randgame.txt", "w");
    fputs("RULES:\n", output);
    fputs("turn 1\n", output);
    fputs("unlimited\n", output);
    fputs("FOUNDATIONS:\n", output);
    fputs("_c _d _h _s\n", output);
    fputs("TABLEAU:\n", output);
    char string[3]={0};
    for(int i = 0; i <= 27; i++){
        memset(string, 0, 3);
        if(i == 6 || i == 12 || i == 17 || i == 21 || i== 24 || i == 26 || i == 27)
            fputs("| ", output);
        string[0] = deck[i].rank;
        string[1] = deck[i].suit;
        string[2] = ' ';
        fputs(string,output);
        if(i == 6 || i == 12 || i == 17 || i == 21 || i== 24 || i == 26 || i == 27)
            fputs("\n", output);
    }
    fputs("STOCK:\n", output);
    fputs("| ", output);
    for(int i = 28; i < 52; i++){
        memset(string,0,3);
        string[0] = deck[i].rank;
        string[1] = deck[i].suit;
        string[2] = ' ';
        fputs(string, output);
    }
    fputs("\nMOVES:\n", output);
    fclose(output);
}

int main() {
    Card deck[52]={0, 0, 'f'};
    createDeck(deck);
    randomizeDeck(deck);
    printRandomizedGameFile(deck);
    return 0;
}
