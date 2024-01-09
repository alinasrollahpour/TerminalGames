/*
hint: code to clear console = printf("\e[1;1H\e[2J");


describtion:
    a simple hang-man game 
    your friend should enter the word and credit
    credit means how much extra characters you can guess
    then appear a ----- on console
    you can guess one by one 

functions:

    game_loop:
        args: word, credit

    clear: to clear screen

    write_table: to print current status of the game and left over attempts
        args: true_attempts array, false_attempts

    is_repeated: to check if this character already exists
        args: string for check-in, target character


*/

#include <stdio.h>
#include <string.h>


//prototypes
int game_loop();

void write_table(char* top_line, char* bottom_line, int left_over, int len);

void repeat_char(char ch, int count);

int is_repeated(char ch, char* str);


int main(){

    //write_table("a b  ts r", "", 3);
    game_loop();
    

    return 0;
}

int game_loop(){
    //word: string that should be guessed 
    //int: how many attempts after chart had been filled

    int attempt_count = 0;
    int credit;
    char word[30];
    

    printf("|   Please enter the word to guess: ");
    scanf("%s", word);

    printf("|   Please enter the credit: ");
    scanf("%d", &credit);

    char top_line[31];
    char bottom_line[31];

    //prepare those strings for printing
    for (int i = 0; i < 30; i++)
    {
        top_line[i] = ' ';
        bottom_line[i] = '\0';;
    }
    top_line[strlen(word)] = '\0';

    attempt_count = credit + strlen(word);



    int win_flag = 0;
    //loop for taking charcters and updating table 
    for (int i = 0; i < attempt_count; i++)
    {
        write_table(top_line, bottom_line, attempt_count - i, strlen(word));

        char guess;
        scanf(" %c", &guess);

        //loop to ensure avoid repeated characters
        while (is_repeated(guess, top_line) || is_repeated(guess, bottom_line))
        {
            printf("|   Already exists! try another charcter: ");
            scanf(" %c", &guess);
        }
        
        //flag stores is the chosen character truely guessed
        int is_guess_true_flag = 0; 

        for (int i = 0; i < strlen(word); i++)
        {
            if (guess == word[i])
            {
                is_guess_true_flag = 1;
                top_line[i] = guess;
            }
            
        }

        //put character in bottom_line if nessecary
        if (is_guess_true_flag == 0){
            bottom_line[strlen(bottom_line)] = guess;
        }
        else i--;
        
        if (strcmp(word, top_line) == 0)
        {   
            printf("\e[1;1H\e[2J");
        
            repeat_char('\n',2);
            repeat_char('#', 21);
            printf("\n|   Yes! you won!   |\n");
            repeat_char('#', 21);
            printf("\n\n|   The word was: %s\n\n", word); 

            return 1;
        }
        
    }//end loop of taking characters
    


    return 0;
}


void write_table(char* top_line, char* bottom_line, int left_over, int len){
    //clear console
    printf("\e[1;1H\e[2J");
    repeat_char('=', 36);
    printf("\n|   Your left over attempts:  %2d   |\n", left_over);
    repeat_char('=', 36);

    printf("\n\n");
    repeat_char(' ', 12);
    printf("\nDiscovered: %s\n", top_line);
    repeat_char(' ', 12);
    repeat_char('-', len);
    printf("\nWrong char: %s\n\n|   please choose your character: ",
        bottom_line);



}

void repeat_char(char ch, int count){

    //print ch, count times
    for (int i = 0; i < count; i++)
    {
        putchar(ch);
    }
    
}

int is_repeated(char ch, char* str){
    //chek if is the ch in str?

    for (int i = 0; i < strlen(str); i++)
    {
        if (ch == str[i]) return 1;
        
    }
    
    return 0;
}

