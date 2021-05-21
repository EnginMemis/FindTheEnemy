#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<time.h>
#include<stdbool.h>
#include<unistd.h>

void preparePlacementMatrix(char placementMatrix[20][30],int treeCount,int enemyCount);
void prepareDisplayMatrix(char displayMatrix[20][30]);
void prepareTheGame(char displayMatrix[20][30] , char placementMatrix[20][30],int treeCount,int enemyCount);
void display(char displayMatrix[20][30]);
void updateDisplayMatrix(char displayMatrix[20][30] , char placementMatrix[20][30],int playerPosition[2],char input,int *gameOver);
void update(char displayMatrix[20][30] , char placementMatrix[20][30] , int playerPosition[2],int remainingEnemy);
int fightWithEnemy(char displayMatrix[20][30] , char placementMatrix[20][30],int playerPosition[2],int remainingEnemy,char input);
void displayGodMode(char displayMatrix[20][30],char placementMatrix[20][30]);
int score(char displayMatrix[20][30]);


int main(){
	
	char displayMatrix[20][30],placementMatrix[20][30];
	int playerPosition[2]={0};
	int treeCount,enemyCount,remainingEnemy;
	int i,j;
	int choice;
	
	srand(time(NULL));
	printf("***********FIND THE ENEMY***********\n");
	printf("1.Play\n2.How to Play\n");
	scanf("%d",&choice);
	switch(choice)
	{	
		case 1:
			system("cls");
			do{
				printf("Please enter the tree and enemy count:");
				scanf("%d %d",&treeCount,&enemyCount);
			}while(treeCount+enemyCount>=596);
			
			remainingEnemy=enemyCount;
			prepareTheGame(displayMatrix , placementMatrix,treeCount,enemyCount);
			update(displayMatrix, placementMatrix,playerPosition,remainingEnemy);
			break;
					
		case 2:
			system("cls");
			printf("Use w,a,s,d.\n");
			printf("You can go to enemies and kill them by pressing the h key.\n");
			printf("you can end the game by pressing the q key.\n");
			printf("You can turn godmode on and off by pressing the c key.\n");
			printf("you will die if you step on the enemy.\n\n");
			printf("1.Play\n");
			scanf("%d",&choice);
			if(choice==1){
				system("cls");
				do{
					printf("Please enter the tree and enemy count:");
					scanf("%d %d",&treeCount,&enemyCount);
				}while(treeCount+enemyCount>=596);
				
				remainingEnemy=enemyCount;
				prepareTheGame(displayMatrix , placementMatrix,treeCount,enemyCount);
				update(displayMatrix, placementMatrix,playerPosition,remainingEnemy);
			}
			else{
				break;
			}
			break;
	}
	
	return 0;
}

void prepareDisplayMatrix(char displayMatrix[20][30]){
	
	int i,j;
	for(i=0;i<20;i++){
		for(j=0;j<30;j++){
			displayMatrix[i][j] = -78;
		}
	}
	displayMatrix[0][0] = 'P';	
	displayMatrix[0][1] = -80;	
	displayMatrix[1][0] = -80;	
	displayMatrix[1][1] = -80;	
}

void preparePlacementMatrix(char placementMatrix[20][30],int treeCount,int enemyCount){
	
	int i,j,x,y;
	
	for(i=0;i<20;i++){
		for(j=0;j<30;j++){
			placementMatrix[i][j]=' ';
		}
	}
	
	for(i=0;i<treeCount;i++){                
		do{
			x=rand()%20;
			y=rand()%30;
			
		}while( (x==0 && y==0) || (x==0 && y==1) || (x==1 && y==0) || (x==1 && y==1) || (placementMatrix[x][y] !=' '));
		
		placementMatrix[x][y] = 'T';
	}
	
	for(i=0;i<enemyCount;i++){
		do{
			x=rand()%20;
			y=rand()%30;
			
		}while( (x==0 && y==0) || (x==0 && y==1) || (x==1 && y==0) || (x==1 && y==1) || (placementMatrix[x][y] !=' '));
		
		placementMatrix[x][y] = 'E';
	}
	
}

void prepareTheGame(char displayMatrix[20][30] , char placementMatrix[20][30],int treeCount,int enemyCount){
	prepareDisplayMatrix(displayMatrix);
	preparePlacementMatrix(placementMatrix,treeCount,enemyCount);
	
}

void update(char displayMatrix[20][30] , char placementMatrix[20][30] , int playerPosition[2],int remainingEnemy){
	char input='b';
	bool isGodMode = false;
	int diff;
	int gameOver = 0;
	int currentScore;
	
	display(displayMatrix);
	
		while(remainingEnemy!=0 && input !='q' && gameOver==0){
				currentScore=score(displayMatrix);
				input = getch();
				if(input=='q'){
					gameOver=2;
				}
				remainingEnemy = fightWithEnemy(displayMatrix, placementMatrix, playerPosition, remainingEnemy,input);
				updateDisplayMatrix(displayMatrix ,placementMatrix,playerPosition,input,&gameOver);
				if(input =='c'){
					
					if(isGodMode==false){
						displayGodMode(displayMatrix,placementMatrix);
						isGodMode=true;
					}
					else{
						display(displayMatrix);
						isGodMode=false;
					}
				}
				else{
					if(isGodMode==true){
						displayGodMode(displayMatrix,placementMatrix);
						
					}
					else{
						display(displayMatrix);
					}
				}
			}
			if(gameOver==1){
				printf("\n\nGAMEOVER !! Score: 0");	
			}
			else if(gameOver==0){
				printf("\n\nCONGRATULATIONS !! Score: %d",currentScore);
			}
			else if(gameOver==2){
				printf("\n\nTHE END !!");
			}
				
}

int fightWithEnemy(char displayMatrix[20][30] , char placementMatrix[20][30],int playerPosition[2],int remainingEnemy,char input){
	
	int i=0,j=0;
	bool isKilled=true;
	
	if(input == 'h'){
		
		i=playerPosition[0]-1;
		j=playerPosition[1]-1;
		while(i<=playerPosition[0]+1 && isKilled){
			while(j<=playerPosition[1]+1 && isKilled){
				if(placementMatrix[i][j] == 'E'){	
					if((i>=0 && j>=0) && (i<20 && j<30)){
						placementMatrix[i][j] = ' ';
						displayMatrix[i][j]= -80;
						isKilled=false;
						remainingEnemy--;	
					}
				}
				j++;	
			}
			i++;
			j=playerPosition[1]-1;
		}
	}
	return remainingEnemy;
}

void updateDisplayMatrix(char displayMatrix[20][30] , char placementMatrix[20][30],int playerPosition[2],char input, int *gameOver){
	
	int i,j;
	switch(input){
		
		case 'w':
			
			if(playerPosition[0] > 0  && placementMatrix[ playerPosition[0]-1 ][playerPosition[1] ] != 'T' && placementMatrix[ playerPosition[0]-1 ][playerPosition[1] ] != 'E' ){
				
				displayMatrix[ playerPosition[0] ][ playerPosition[1] ] = -80;
				playerPosition[0] = playerPosition[0]-1;
				
				for(i=playerPosition[0]-1;i<=playerPosition[0]+1;i++){
					for(j=playerPosition[1]-1;j<=playerPosition[1]+1;j++){
						if((i>=0 && j>=0) && (i<20 && j<30)){
						
							if(placementMatrix[i][j] == ' '){
								displayMatrix[i][j] = -80;
							}
							else{
								displayMatrix[i][j] = placementMatrix[i][j];
							}
						}
						
					}
				}
				
				displayMatrix[ playerPosition[0] ][ playerPosition[1] ] = 'P';
				
			}	
			
			else if(placementMatrix[ playerPosition[0]-1 ][playerPosition[1] ] == 'E'){
				*gameOver=1;
			}	
			
			break;
		case 'a':
			
			if(playerPosition[1] > 0 && placementMatrix[ playerPosition[0] ][playerPosition[1]-1 ] != 'T' && placementMatrix[ playerPosition[0] ][playerPosition[1]-1 ] != 'E'){
				displayMatrix[ playerPosition[0] ][ playerPosition[1] ] = -80;
				playerPosition[1] = playerPosition[1]-1;
				
				for(i=playerPosition[0]-1;i<=playerPosition[0]+1;i++){
					for(j=playerPosition[1]-1;j<=playerPosition[1]+1;j++){
						if((i>=0 && j>=0) && (i<20 && j<30)){
						
							if(placementMatrix[i][j] == ' '){
								displayMatrix[i][j] = -80;
							}
							else{
								displayMatrix[i][j] = placementMatrix[i][j];
							}
						}
					}
				}
				displayMatrix[ playerPosition[0] ][ playerPosition[1] ] = 'P';	
			}
			else if(placementMatrix[ playerPosition[0] ][playerPosition[1]-1 ] =='E'){
				*gameOver = 1;
			}
			break;
		case 's':
			
			if(playerPosition[0] < 19 && placementMatrix[ playerPosition[0]+1 ][playerPosition[1] ] != 'T' && placementMatrix[ playerPosition[0]+1 ][playerPosition[1] ] != 'E'){
				displayMatrix[ playerPosition[0] ][ playerPosition[1] ] = -80;
				playerPosition[0] = playerPosition[0]+1;
				
				for(i=playerPosition[0]-1;i<=playerPosition[0]+1;i++){
					for(j=playerPosition[1]-1;j<=playerPosition[1]+1;j++){
						if((i>=0 && j>=0) && (i<20 && j<30)){
						
							if(placementMatrix[i][j] == ' '){
								displayMatrix[i][j] = -80;
							}
							else{
								displayMatrix[i][j] = placementMatrix[i][j];
							}
						}
					}
				}
				displayMatrix[ playerPosition[0] ][ playerPosition[1] ] = 'P';	
			}
			else if( placementMatrix[ playerPosition[0]+1 ][playerPosition[1] ] == 'E'){
				*gameOver=1;
			}
			
			break;
		case 'd':
			
			if(playerPosition[1] < 29 && placementMatrix[ playerPosition[0] ][playerPosition[1]+1 ] != 'T' && placementMatrix[ playerPosition[0] ][playerPosition[1]+1 ] != 'E'){
				displayMatrix[ playerPosition[0] ][ playerPosition[1] ] = -80;
				playerPosition[1] = playerPosition[1]+1;
				
				for(i=playerPosition[0]-1;i<=playerPosition[0]+1;i++){
					for(j=playerPosition[1]-1;j<=playerPosition[1]+1;j++){
						if((i>=0 && j>=0) && (i<20 && j<30)){
						
							if(placementMatrix[i][j] == ' '){
								displayMatrix[i][j] = -80;
							}
							else{
								displayMatrix[i][j] = placementMatrix[i][j];
							}
						}
					}
				}
				displayMatrix[ playerPosition[0] ][ playerPosition[1] ] = 'P';	
			}
			else if(placementMatrix[ playerPosition[0] ][playerPosition[1]+1 ] == 'E'){
				*gameOver = 1;
			}
			break;
	}
	
}

void displayGodMode(char displayMatrix[20][30],char placementMatrix[20][30]){
	int i,j;
	system("cls");
	
	for(i=0;i<20;i++){
		for(j=0;j<30;j++){
			if(placementMatrix[i][j] == ' '){
				if(displayMatrix[i][j] == 'P'){
					printf("%c",displayMatrix[i][j]);
				}
				else{
					printf("%c",-80);
				}	
			}
			else{
				printf("%c",placementMatrix[i][j]);
			}
		
	}
	printf("\n");
	}
	
	
}

void display(char displayMatrix[20][30]){
	int i,j;
	system("cls");
	
	for(i=0;i<20;i++){
		for(j=0;j<30;j++){
		printf("%c",displayMatrix[i][j]);
	}
	printf("\n");
	}
	
	
}

int score(char displayMatrix[20][30]){
	
	int i,j;
	int currentScore=0;
	int count;
	count=0;
	
	for(i=0;i<20;i++){
		for(j=0;j<30;j++){
			if(displayMatrix[i][j]==-78){
				count++;
			}
		}
	}
	currentScore=count*10+40;
	printf("******************************\nScore: %d ",currentScore);
	return currentScore;
}






