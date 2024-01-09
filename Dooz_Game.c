//start
#include <stdio.h>
#include <stdlib.h>



//array of game status 3*3
char game_table[9] = {0,0,0, 0,0,0, 0,0,0,};

//array of output table 5*12
char output_table[60] = "|---------|\n"   //0 => 13, 1 => 17
                        "|         |\n"
                        "|         |\n"
                        "|         |\n"
                        "|---------|";


//declare sign of A and B
char A,B;



int validate_action(int location){
    if (game_table[--location] == 0)return 1;
    return 0; //else
}


int print_game(char sign, int location){
    /*save game table into format table
    and print it
    */

    location--;
    game_table[location] = sign;
    location = 13 + 4*location;
    output_table[location] = sign;
    printf("\n%s\n", output_table);
    return 0;
}


int is_winner(char player_sign){
    /*take player_sign like # or $
    check the arrows and columns of arr
    if there was three [player_id] return 1
    else return 0
    */
    int sum = player_sign*3;

    if(
            (game_table[0]+game_table[1]+game_table[2] == sum) ||
            (game_table[3]+game_table[4]+game_table[5] == sum) ||
            (game_table[6]+game_table[7]+game_table[8] == sum) ||

            (game_table[0]+game_table[3]+game_table[6] == sum) ||
            (game_table[1]+game_table[4]+game_table[7] == sum) ||
            (game_table[2]+game_table[5]+game_table[8] == sum) ||

            (game_table[1]+game_table[4]+game_table[8] == sum) ||
            (game_table[2]+game_table[4]+game_table[6] == sum)
            ) {
        return 1;
    }
    return 0;

}


void winner_party(char winner){
    printf("\nOh yes! %c you won!\n", winner);
    if (winner=='#'){
        printf("%s",   "#####\n"
                            "#####\n"
                            "#####\n"
        );
    }else{
        printf("%s","$$$$$\n"
                            "$$$$$\n"
                            "$$$$$\n"
        );
    }

}

void reset_tables(){
    for (int i = 0; i<9; i++){
        game_table[i] = 0;
        int j = 13 + 4*i;
    }
}


int main() {

    //introduction with players

    printf("%s\n", "=======================================");
    printf("%s\n", "-----<<< WELCOME TO DOOZ GAME! >>>-----");
    printf("%s\n", "[its a two player game. choose # and $]");
    printf("%s", "this is the guide table.\n"
                 "which bock that you want to sing\n"
                 "just type its number\n"
                 "|---------|\n"
                 "|1   2   3|\n"
                 "|4   5   6|\n"
                 "|7   8   9|\n"
                 "|---------|\n");
    //unit test
    //winner_party('#');

    //main loop of the game
    while (1) {



        printf("\ngame started!\n");
        //randomly assign them
        if ((rand() % 2) == 1) {
            A = '#';
            B = '$';
        } else {
            A = '$';
            B = '#';
        }

        //loop of placing signs

        int A_choice;   //these store that with block is chosen to singn
        int B_choice;

	int someone_won_flag = 0;
	
        for (int i = 0; i < 9; i++) {

            //its for player A
            do {
                printf("\nplayer [%c] where do you wanna place? ", A);
                scanf("%d", &A_choice);

            } while (!validate_action(A_choice));
            
            print_game(A, A_choice);
            
            if (is_winner(A)){
                winner_party(A);
                someone_won_flag = 1;
                break;
            }

		if(i == 4) break;
		
            //its for player B
            do {
                printf("player [%c] where do you wanna place? ", B);
                scanf("%d", &B_choice);

            } while (!validate_action(B_choice));
            
            print_game(B, B_choice);
            
            if (is_winner(B)){
                winner_party(B);
                someone_won_flag = 1;
                break;
            }

        }
        
        if (someone_won_flag == 0){
        	printf("\nNo body won!\n");
        }



    }
    return 0;
}
