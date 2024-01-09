#include <stdio.h> 
#include <stdlib.h> 
#include <time.h>
#include <string.h>

#define MAX_LOOP 10


void greet(){
    //introduce to game
    printf(
        "\n==========================================================\n"
        "|  Welcom to \"ROCK PAPER SCISSOR\" game!\n\n"
        "|  you can press [ROCK:1 , PAPER:2 , SCISSOR:3] to choos!\n"
        "|  and press 'R' to restart game.\n\n"
        "|  lets start!\n"
        "==========================================================\n\n"
        );

}

void write_status(int user, int pc){
    //print current game counts in [ vs ] format
    printf("\n[ YOU: %d vs PC: %d ]\n", user, pc);
}

char* three_rand(int seed){
    //return a random from set: {rock, paper, scissor}

    srand(time(NULL) + seed);

    char r = (rand() % 3);

    switch (r)
    {
    case 0:
        return "rock";

    case 1:
        return "paper";

    case 2:
        return "scissor";
        
    default:
        break;
    }
}

char* who_won(const char* user_choice, const char* pc_choice){
    //returns on of strings {pc, user, equal}
    //and prints notation in output
    
    if (user_choice == pc_choice){
        printf("|   Oh. we are same!\n");

        return "equal";
    }
    else if (user_choice == "rock")
    {
        switch (pc_choice[0])
        {
        case 'p':
            printf("|   I eat you!\n");
            return "pc";
        case 's':
            printf("|   You crack me!\n");
            return "user";
        default:
            break;
        }

    } 
    else if (user_choice == "paper")
    {
        switch (pc_choice[0])
        {
        case 'r':
            printf("|   You eat me!\n");
            return "user";
        case 's':
            printf("|   I cut you!\n");
            return "pc";
        default:
            break;
        }

    } 
    else if (user_choice == "scissor")
    {
        switch (pc_choice[0])
        {
        case 'r':
            printf("|   I crack you!\n");
            return "pc";
        case 'p':
            printf("|   You cut me!\n");
            return "user";
        default:
            break;
        }
    }
    
}

char* convert_digit_to_str(int d){
    //convert {1, 2, 3} to names

    switch (d)
        {
        case 1:
            return "rock";
        
        case 2:
            return "paper";

        case 3:
            return "scissor";
        
        default:
            break;
        }

}

char* game_loop(){
    //make a loop and every time show the status and take user choice

    //initializ counters
    int user = 0, pc = 0;

    for (int i = 0; i < MAX_LOOP; i++)
    {
        char* pc_choice = three_rand(i);

        write_status(user, pc);

        int user_digit;

        printf("|   Choose: ");
        scanf("%d", &user_digit);

        //store who had won, pc user equal
        char* result = who_won(convert_digit_to_str(user_digit), pc_choice);

        if (result == "pc") pc++ ;
        else if (result == "user") user++ ;
        else if (result == "equal");
        else printf("ERROR: who_won function doesnt work!"); //error handler
        

    }
    
    //return preparing
    if (user > pc) return "user";
    else if (user < pc) return "pc";
    else return "equal";

}

int main(){

   
    greet();
    
    char replay = 'n';

    do{
        char* game_result = game_loop();

        printf("\n|   Game winner: '%s'\n", game_result);
        printf("|   Do you wanna play again? (y/n) ");
        scanf(" %c", &replay);

    }while (replay == 'y' || replay == 'Y');
    
       
    
    
    return 0;
}