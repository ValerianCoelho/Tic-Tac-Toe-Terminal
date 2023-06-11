#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

unsigned char grid[3][3]={{' ',' ',' '},{' ',' ',' '},{' ',' ',' '}};

void display(int y, int x) {
    for(int i=1; i<=7; i++) {
        for(int j=1; j<=13; j++) {
            // Drawing the horizontal lines
            if((i==1 || i==3 || i==5 || i==7) && (j!=1 && j!=5 && j!=9 && j!=13))
                printf("Ä");
            
            // Drawing the vertical lines
            else if((i==2 || i==4 || i==6) && (j==1 || j==5 || j==9 || j==13))
                printf("³");

            // Drawing the intersection of horizontal and vertical lines
            else if((i==1) && (j==5 || j==9))
                printf("Â");
            else if((i==7) && (j==5 || j==9))
                printf("Á");
            else if((i==3 || i==5) && (j==1))
                printf("Ã");
            else if((i==3 || i==5) && (j==13))
                printf("´");
            else if((i==3 || i==5) && (j==5 || j==9))
                printf("Å");

            // Drawing the corners
            else if(i==1 && j==1)
                printf("Ú");
            else if(i==1 && j==13)
                printf("¿");
            else if(i==7 && j==1)
                printf("À");
            else if(i==7 && j==13)
                printf("Ù");

            // Drawing the X or O marks
            else if((i==2 || i==4 || i==6) && (j==3 || j==7 || j==11)) {
                if(i==2*(y+1) && j==4*(x+1)-1)
                    printf("\033[107m"); // Setting the background color
                printf("%c",grid[i/2-1][(j+1)/4-1]);
                if(i==2*(y+1) && j==4*(x+1)-1)
                    printf("\033[0m"); // Resetting the background color
            }
            else {
                printf(" "); // Empty space
            }
        }
        printf("\n");
    }
}

int checkwinner() {
    int empty = 0;
    for(int i=0; i<3; i++) {
        // Checking rows and columns for a win
        if((grid[i][0]=='X' && grid[i][1]=='X' && grid[i][2]=='X') || (grid[0][i]=='X' && grid[1][i]=='X' && grid[2][i]=='X'))
            return 1;
        if((grid[i][0]=='O' && grid[i][1]=='O' && grid[i][2]=='O') || (grid[0][i]=='O' && grid[1][i]=='O' && grid[2][i]=='O'))
            return 2;
        
        // Checking diagonals for a win
        if((grid[0][0]=='X' && grid[1][1]=='X' && grid[2][2]=='X') || (grid[0][2]=='X' && grid[1][1]=='X' && grid[2][0]=='X'))
            return 1;
        if((grid[0][0]=='O' && grid[1][1]=='O' && grid[2][2]=='O') || (grid[0][2]=='O' && grid[1][1]=='O' && grid[2][0]=='O'))
            return 2;
        
        // Checking if the board is full
        if(grid[i][0]==' ' || grid[i][1]==' ' || grid[i][2]==' ')
            empty = 1;
    }
    
    if(empty)
        return 0; // Game is not over, still possible moves
    else
        return -1; // Game is a draw
}

int main() {
    char ch;
    char choice = 'X';
    int y=0,x=2;
    
    // Main game loop
    while(!checkwinner()) {
        system("cls");
        display(y,x);

        printf("Enter : ");
        ch = getch();

        // Handling player movements
        if(ch==75) {
            if(!(x>0)) {
                continue;
            }
            x--;
        }
        else if(ch==77) {
            if(!(x<2)) {
                continue;
            }
            x++;
        }
        else if(ch==80) {
            if(!(y<2)) {
                continue;
            }
            y++;
        }  
        else if(ch==72) {
            if(!(y>0)) {
                continue;
            }
            y--;
        }  
        else if(ch==13) {
            if(!(grid[y][x]==' ')) {
                continue;
            }
            grid[y][x]=choice;
            
            // Switching the player's turn
            if(choice=='X') {
                choice = 'O';
            }
            else if(choice=='O') {
                choice = 'X';
            }
        }
    }
    
    system("cls");
    display(y,x);
    int result = checkwinner();
    
    // Printing the result of the game
    if(result==1) {
        printf("\nWinner : Player 1\n");
    }
    if(result==2) {
        printf("\nWinner : Player 2\n");
    }
    if(result==-1) {
        printf("\nResult : Draw\n");
    }
    system("pause");
    return 0;
}
