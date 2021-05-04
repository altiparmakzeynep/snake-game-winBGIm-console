#include <iostream>
#include <conio.h> //console input/output
#include <windows.h>
#define esc 27
using namespace std;
bool gameOver;

enum eDirection{ LEFT, RIGHT, UP, DOWN, STOP = 0 };
eDirection dir;

const int height = 20;
const int width = 20;
int x,y;
int foodX, foodY, score;
int tailX[1000], tailY[1000], tailLength;

void Drawing(int);
void initGame();

int level = 0;

int menu(){
    cout << "Easy mode for press e " << endl;
    cout << "Medium mode for press m " << endl;
    cout << "Hard mode for press h " << endl;
    cout << "Help for press 1 " << endl;
    cout << "Quit for press q " << endl;
    char decider;
    while(1){
    	scanf("%c",&decider);
		if(decider == 'e'){
			level = 1;
			initGame();
			return 1;
		}
		else if(decider == 'm'){
			level = 2;
			initGame();
			return 1;
		}	
		else if(decider == 'h'){
			level = 3;
			initGame();
			return 1;
		}
		else if(decider == '1'){
			cout << "Welcome to help part! " << endl;
		}
		else if(decider == 'q'){
			cout << "Are you sure? y/n " << endl;
		}
	    if(decider == 'y'){
			gameOver = true;
			return 0;
		}
	   if(decider == 'n'){
			menu();
		}		  
	}
}

void initGame(){
	
	gameOver = false;
	score = 0;	
	dir = STOP;
	x = width / 2;
	y = height / 2;
	
	//random co-ordinate generation for food
	foodX = rand() % width;
	foodY = rand() % height;
    Drawing(1);
}

void Drawing(int dFlag){
	
	//create wall
	system("cls");
	
	for(int i = 0; i < width + 2; i++)
		cout  << "O";
	cout << endl; 
	
	for(int i = 0; i < height; i++){
		for(int j = 0; j < width; j++){
			if(j == 0)
				cout << "O";
			
			if(i==y && j==x) //create snake
				cout << "S";
			else if(i == foodY && j == foodX) //create food
				cout << "F";
			else{
				bool print = false;
				for(int z = 0; z < tailLength; z++){
					
					if(tailX[z] == j && tailY[z] == i){
						cout << "s";
						print = true;
					}
					
				}
				if(!print){
					cout << " ";
				}
			
			}	
			if(j == width - 1)
				cout << "O";
		}
		cout << endl; 
	}
	
	for(int i = 0; i < width + 2; i++)
		cout << "O";
    cout << endl;
}

//This function for keyboard values
void Input(){
	
	if(_kbhit()){
		
		switch(_getch()){
			case 'a':
			case 'A':
				dir = LEFT;
				break;
			case 'd':
			case 'D':
				dir = RIGHT;
				break;
			case 'w':
			case 'W':
				dir = UP;
				break;
			case 's':
			case 'S':
				dir = DOWN;
				break;
			case 27:
				cout << "Are you sure? y/n " << endl;
				case 'y':
		        gameOver = 1;
				break;
			 
		}
	}
}

	
void playGame(){
	
	printf("score: %d ", score);
	int prevTailX = tailX[0];
	int prevTailY = tailY[0];
	int prevTail2X, prevTail2Y;
	tailX[0] = x;
	tailY[0] = y;
	for(int i = 1; i < tailLength; i++){
		prevTail2X = tailX[i];
		prevTail2Y = tailY[i];
		tailX[i] = prevTailX;
		tailY[i] = prevTailY;
		prevTailX = prevTail2X;
		prevTailY = prevTail2Y;
	}
	switch(dir){
		case LEFT:
			x--;
			break;
		case RIGHT:
			x++;
			break;
		case UP:
			y--;
			break;
		case DOWN:
			y++;
			break;
		default:
			break;
	}
	//if snake hits the wall
	if(x > width || x < 0 || y > height || y < 0){
		gameOver = true;	
	}
	   
	//if snake eats its own tail
	for (int i = 0; i < tailLength; i++)
        if (tailX[i] == x && tailY[i] == y)
            gameOver = true;
  
            
	//if snake eats food
	if (x == foodX && y == foodY){
			if(level != 0){
    		switch(level){
    			case 1:
    				score++;
    				break;
    			case 2:
    				score += 5;
    				break;
    			case 3:
    				score += 10;
    				break;	
			}
    				
		}
	    foodX = rand() % width;
		foodY = rand() % height;
		tailLength++;
	}
	
	
   if(gameOver == true){
   	//file op.
    FILE *file = fopen("file.txt", "a"); //append
    fprintf(file,"%d\n", score);
    fclose(file);
    
    int highScore = score;
    
    file = fopen("file.txt", "r");//read

    while(!feof(file)){
     int file_score;
     fscanf(file, "%d", &file_score);
	 if(file_score>= highScore){
	 	highScore = file_score;
	 }
	}
    fclose(file);
    printf("high score: %d ", highScore);
   }
  
  
	    
}
int main()

{
    int denemeFlag = menu();
    
    while(!gameOver){
    	Drawing(0);
    	Input();
    	playGame();
    	if(level != 0){
    		switch(level){
    			case 1:
    				Sleep(150);
    				break;
    			case 2:
    				Sleep(100);
    				break;
    			case 3:
    				Sleep(50);
    				break;	
			}
    				
		}
		
	}
	return 0;
}
