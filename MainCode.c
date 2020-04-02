#include<stdio.h>
#include<string.h>

// ****** Run the code in Interactive Console for Best Experience ****** //

void inBodyComp (float *a);
void penalize (float *a);
void attack (float *attacker, float *attacked, int attackerPart, int attackedPart);
float score (float *a);
void printStatus (char x, float *a);

int main(){
    int streak[3] = {0, 0, 0};
    PlayAgain:
    //Printing the Game Instructions
    printf("****Welcome to Virtual Battle Game!****\n");
    printf("~~Following are the rules for the game~~\n");
    printf("1) There are two contestants A and B in the game, each with an initial strength of 500 points.\n");
    printf("2) Every contestant has four body parts: head, arms, legs and abdomen.\n");
    printf("3) Each participant can either make his/her own body constitution (i.e. distribute the total strength to different body parts) or can continue with the default constitution.\n");
    printf("4) Strength of any of the body parts can not be zero from very beginning.\n");
    printf("5) Attack can be made by only arms and legs, however any of the four body parts of opponent can be attacked.\n");
    printf("6) Turns are provided to A and B in alternate manner. However, the game always starts with turn of A.\n");
    printf("7) If the strength of attacking body part is more than of the attacked body part, then the strength of attacking body part increases by 25%% and attacked body part decreases by 50%%.\n");
    printf("8) If the strength of attacking body part is less than of the attacked body part, then the strength of attacking body part decreases by 50%% and attacked body part decreases by 5%%.\n");
    printf("9) If the strength of both attacked and attacking body part is same, then strength of attacked part decreases by 20%% and the strength of attacking part remains same.\n");
    printf("10) If any player makes any illegal move then he/she is penalized by reducing the strength of every body part by 50%% for every illegal move. Moreover, only 2 spare chances are given to the culprit.\n");
    printf("11) The first person whose strength reaches 50 points or below first, loses the game. However, if upon completion of 10 turns (5 turns of each A and B), strength of none of them is 50\n");
    printf("   points or below then the one with lower strength loses. The game also terminates as soon as the strength for both arms as well as legs nullifies for any player.\n");
    printf("12) Here are some handy notations that we'll use ahead for inputs:\n");
    printf("--> '1' for Yes! and '0' for No!\n");
    printf("--> '0' for Arms, '1' for Legs, '2' for Head and '3' for Abdomen\n");
    float playerA[4] = {125.0, 125.0, 125.0, 125.0};
    float playerB[4] = {125.0, 125.0, 125.0, 125.0};
    int token;
    // Game Settings
    printf("\nDoes Player A want to change his/her composition?\n");
    scanf("%d", &token);
    if (token) inBodyComp (playerA);
    printf("\nDoes Player B want to change his/her composition?\n");
    scanf("%d", &token);
    if (token) inBodyComp (playerB);
    // Actual Gameplay
    int attackingPart, attackedPart, n=0;
    printf("\nGame Begins!! Please provide moves in following format: \"Attacking Body Part, Attacked Body Part\"\n");
    do {
        // Chance of Player A
        printf("\nTurn of Player A! Please, provide input:\n");
        int penal=0;
        PlayA:
        scanf("%d, %d", &attackingPart, &attackedPart);
        if ((attackingPart<0)||(attackingPart>1)||(attackedPart<0)||(attackedPart>3))
        {
            printf("\nInvalid Move of Player A!! Player A is being Penalized!!");
            penalize (playerA);
            penal++;
            if (penal < 2)
            {
                printf("\nPlayer A, Please Make a Valid Move!!\n");
                goto PlayA;
            }
            else
            {
                printf("\nChance of Player A is skipped!!\n");
                goto SkipA;
            }
        }
        attack(playerA, playerB, attackingPart, attackedPart);
        SkipA:
        printf("\nCurrent status of game is:\n");
        printStatus('A', playerA);
        printStatus('B', playerB);
        n++;
        // Chance of Player B
        if ((score(playerB) > 50)&&(score(playerA) > 50))
        {
            printf("\nTurn of Player B! Please, provide input:\n");
            int penal=0;
            PlayB:
            scanf("%d, %d", &attackingPart, &attackedPart);
            if ((attackingPart<0)||(attackingPart>1)||(attackedPart<0)||(attackedPart>3))
            {
                printf("\nInvalid Move of Player B!! Player B is being Penalized!!");
                penalize (playerB);
                penal++;
                if (penal < 2)
                {
                    printf("\nPlayer B, Please Make a Valid Move!!\n");
                    goto PlayB;
                }
                else
                {
                    printf("\nChance of Player B is skipped!!\n");
                    goto SkipB;
                }
                penal++;
            }
            attack(playerB, playerA, attackingPart, attackedPart);
            SkipB:
            printf("\nCurrent status of game is:\n");
            printStatus('A', playerA);
            printStatus('B', playerB);
            n++;
        }
    } while ((score(playerA) > 50)&&(score(playerB) > 50)&&(n<10)&&((playerA[0]+playerA[1])!=0)&&((playerB[0]+playerB[1])!=0));
    // Declaration of Result
    if (score(playerA) > score(playerB))
    {
        printf("\nCongratulations! Player A is the winner of this round of Virtual Battle!!");
        streak[0]++;
    }
    else if (score(playerB) > score(playerA))
    {
        printf("\nCongratulations! Player B is the winner of this round of Virtual Battle!!");
        streak[1]++;
    }
    else 
    {
        printf("The game is a Tie!!");
        streak[2];
    }
    // Printing of Leaderboard
    printf("\n\n****LeaderBoard Statistics****\n");
    printf("\nThe no. of matches played till now:%d", (streak[0]+streak[1]+streak[2]));
    printf("\nMatches won by Player A: %d", streak[0]);
    printf("\nMatches won by Player B: %d", streak[1]);
    printf("\nMatches tied between Player A & Player B: %d", streak[2]);
    printf("\nNo. of moves for which the last match lasted: %d", n);
    //Ask to play again
    printf("\n\nDo you wish to play again?\n");
    scanf("%d", &token);
    if (token) goto PlayAgain;
    // Printing the final results
    if (streak[0]>streak[1])
    {
        printf("\n\nThe overall winner of this gaming session is Player A!! CONGRATULATIONS!!");
    }
    else if (streak[0]<streak[1])
    {
        printf("\n\nThe overall winner of this gaming session is Player B!! CONGRATULATIONS!!");
    }
    else printf("\n\nThe overall result of this gaming session is a tie!! Both players played well!!");
    printf("\n\nEnter any number to shut this game... Hope that you had a nice playtime...\n");
    scanf("%d", &token);
    return 0;
}

float score (float *a){
    float score = *a + *(a+1) + *(a+2) + *(a+3);
    return score;
}

void attack (float *attacker, float *attacked, int attackerPart, int attackedPart){
    if ((*(attacker + attackerPart))>(*(attacked + attackedPart))&&((*(attacked + attackedPart))!=0))
    {
        *(attacker + attackerPart) *= (1.25);
        *(attacked + attackedPart) *= (.50);
    }
    else if ((*(attacker + attackerPart))<(*(attacked + attackedPart))&&((*(attacker + attackerPart))!=0))
    {
        *(attacker + attackerPart) *= (.50);
        *(attacked + attackedPart) *= (.95);
    }
    else if ((*(attacker + attackerPart))==(*(attacked + attackedPart)))
    {
        *(attacker + attackerPart) *= (1.00);
        *(attacked + attackedPart) *= (.80);
    }
    return;
}

void printStatus (char x, float *a){
    printf("\nTotal strength of %c is: %.2f", x, *a + *(a+1) + *(a+2) + *(a+3));
    printf("\nStrength of Arms: %.2f, Legs: %.2f, Head: %.2f, Abdomen: %.2f\n", *a, *(a+1), *(a+2), *(a+3));
    return;
}

void inBodyComp (float *a){
    int a1, a2, a3, a4;
    correction:
    printf("\nEnter percentage strength of Arms(in integers):\n");
    scanf("%d", &a1);
    printf("\nEnter percentage strength of Legs(in integers):\n");
    scanf("%d", &a2);
    printf("\nEnter percentage strength of Head(in integers):\n");
    scanf("%d", &a3);
    printf("\nEnter percentage strength of Abdomen(in integers):\n");
    scanf("%d", &a4);
    if ((a1<=0)||(a2<=0)||(a3<=0)||(a4<=0)||((a1 + a2 + a3 + a4)!=100)){
        printf("Entered composition is invalid!!! Insert correction composition!!");
        goto correction;
    }
    *(a) = a1*5;
    *(a+1) = a2*5;
    *(a+2) = a3*5;
    *(a+3) = a4*5;
    return;
}

void penalize (float *a){
    for (int i=0; i<4; i++)
    {
        *(a+i) *= (.50);
    }
}