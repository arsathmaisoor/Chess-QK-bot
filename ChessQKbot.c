#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>
// struct to mark the positions of the pieces and check whether they are alive
struct coordinate {
  int row,column;
  bool alive;
};
struct coordinate black_king,white_king,black_queen;
int moves=0;

//function to return the column number according to the input given
int getColumn(char column){
	int col;
	switch(column){
		case 'A':col=1;break;
		case 'B':col=2;break;
		case 'C':col=3;break;
		case 'D':col=4;break;
		case 'E':col=5;break;
		case 'F':col=6;break;
		case 'G':col=7;break;
		case 'H':col=8;break;
		default:printf("Error in the column\n");
 }
 return col;
}

// function to set initial blackking position
void initialBlackKingPos(){
	int row, col;
	do{
		row =1+rand() % 8;
		col=1+rand() % 8; 
	} 
	while((row>=4 && row<=6)&& (col>=4 && col<=6));// set the black king position not in attacking zone of white
	
	black_king.row=row;
	black_king.column=col;
	black_king.alive=true;
}
// function to set initial black queen position
void initialBlackQueenPos(){
	int row, col;
	do{
		row=1+rand () % 8;
		col=1+rand () % 8; 
	} 
	while(row==5 || col==5 ||(abs(5-row)==abs(5-col))||(black_king.row==row&&black_king.column==col) );// set the black queen position not in attacking zone of white
	black_queen.row=row;
	black_queen.column=col;
	black_queen.alive=true;
}
// function to print the chessboard
void printChessBoard(){
	for(int i=9,f=65;i>0;i--){
		for (int j=0;j<=8;j++){
			if(j==0){
				if (i==9)
					printf("  ");
					
				else
					printf("%d,",i);
			}
			else{
				if(i==9){
				printf("%c,",f);f++;
			}else{
		
				if(black_queen.row==i && black_queen.column==j && black_queen.alive==true){
					printf("Q,");
				}
				else if(black_king.row==i && black_king.column==j && black_king.alive==true){
					printf("B,");
				}
				else if(white_king.row==i && white_king.column==j &&white_king.alive==true){
					printf("W,");
				}
				else{
					printf("_,");
				}
			}
			}
			
		}
		printf("\n");
	}
	printf("\n");
}
// function to check whether the input is valid
bool isValidInput(char piece,char col,int row){
	if ((piece=='B'||piece=='Q' )&& (getColumn(col)>=1&&getColumn(col)<=8 )&&(row>=1 && row<=8))
		return true;
	else 
		return false;
}
// print the coordinates of the pieces
void print(){
	printf("black king col: %d row: %d alive: %d\n",black_king.column,black_king.row,black_king.alive);
	printf("black queen col: %d row: %d alive: %d\n",black_queen.column,black_queen.row,black_queen.alive);
	printf("white king col:  %d row: %d alive: %d\n",white_king.column,white_king.row,white_king.alive);
}
// function to check whether the black king move is valid such that it takes only one step
bool isBlackKingValidMove(char col,int row){
	int colm=getColumn(col);
	if(abs(black_king.column-colm)<=1 && abs(black_king.row-row)<=1)
		return true;
	return false;
	
}
// function to check whether the black queen move is valid
bool isBlackQueenValidMove(char col,int row){
	if (black_queen.column==getColumn(col)||black_queen.row==row||(abs(black_queen.column-getColumn(col))==abs(black_queen.row-row)))
		return true;
	return false;
}
// function to check the checkmate
bool isCheckMate(char piece){
//	if either the position of black king with white king or black queen with white king coincide then it is a checkmate
	if((black_queen.column==white_king.column && black_queen.row==white_king.row )||(black_king.column==white_king.column && black_king.row==white_king.row)){
		if(piece=='W'){
			if(black_queen.column==white_king.column && black_queen.row==white_king.row ){			
				black_queen.alive=false;
				black_queen.column=-1;
				black_queen.row=-1;
				return false;
			}
			else{			
				black_king.alive=false;
				black_king.column=-1;
				black_king.row=-1;
				whiteWinner();
				return true;// if black king is dead, then checkmate
			}
		}
		else{		
			white_king.alive=false;
			white_king.column=-1;
			white_king.row=-1;
			blackWinner();
			return true;//if white king is dead, then checkmate
		}
		
	}
	return false;	
}
// function to check whether the white move is valid
bool isWhiteMoveValid(int moveRow,int moveCol ){
	int col=white_king.column+moveCol;
	int row=white_king.row+moveRow;
	if (col>=1 && col<=8)
		if (row>=1 && row<=8){
			return true;
		}			
	return false;		
}
// function to check whether the position to move is safe
bool safePosition(int row,int col){
	if (abs(black_king.column-col)<=1&&abs(black_king.row-row)<=1)
		return false;
	if (abs(black_queen.column-col)==abs(black_queen.row-row)||black_queen.column==col||black_queen.row==row)
		return false;
	return true;	
}
// function to say whether moving towars center is either by adding or substracting
char whiteSideCol(){
	int col=white_king.column;
	if (col<=4)
		return 'a';
	else 
		return 's';

}
// function to say whether moving towars center is either by adding or substracting
char whiteSideRow(){
	int row=white_king.row;
	if (row<=4)
		return 'a';
	else 
		return 's';
}
// function to check the all 8 positions that white can take
void checkAllPositions(){
		int moveRow,moveCol;
		bool valid=false;
		bool isSafe;
	for (int i=-1;i<=1&&!isSafe;i++){
		for (int j=-1;j<=1&&!isSafe;j++){
			moveRow=i;
			moveCol=j;
			valid=isWhiteMoveValid(moveRow,moveCol);//check whether the move is valid
			if (valid&&(moveRow!=0||moveCol!=0)){//omitting the 0,0 because that is not a move
				isSafe=safePosition(white_king.row+moveRow,white_king.column+moveCol);//check whether position is safe
				if(isSafe)
					{white_king.column+=moveCol;white_king.row+=moveRow;break;}
				}
		}
	}
//	if no position to move safely then stalemate and announce white as winner
	if (!isSafe){
		printf("stalemate\n");
		black_king.alive=false;
		black_king.column=-1;
		black_king.row=-1;
		whiteWinner();
	}
			
	
}
//function to take a normal move
void moveWhite1(){
	// to move towards center
	char colOperation=whiteSideCol();
	char rowOperation=whiteSideRow();
	int col,row;
	switch(colOperation){
		case 'a':col=white_king.column+1;break;
		case 's':col=white_king.column-1;break;
	}
	switch(rowOperation){
		case 'a':row=white_king.row+1;break;
		case 's':row=white_king.row-1;break;
	}
	// to move towards center it can have 3 options 
	// check moving towards center is safe
	bool isSafe=safePosition(row,col);
	bool moved=false;
	if(isSafe){
		white_king.row=row;
		white_king.column=col;
		moved=true;
	}
	if(!moved)
		isSafe=safePosition(white_king.row,col);
	if(isSafe&&!moved){
		white_king.column=col;
		moved=true;
	}
	if(!moved)
		isSafe=safePosition(row,white_king.column);
	if(isSafe&&!moved){
		white_king.row=row;
		moved=true;
	}
	if(!moved){
		printf("Moving towards center failed check all other cells\n");
		checkAllPositions();// if moving towards center is not safe, then consider other options
	}
		

}

// function to move white
void moveWhite(){
	if((abs(white_king.column-black_king.column)>1||abs(white_king.row-black_king.row)>1)){//if it cant attack black king check for black queen
		if((abs(white_king.column-black_queen.column)>1||abs(white_king.row-black_queen.row)>1)){
			moveWhite1();//if it cant attack black queen also then a normal move
		}
		else{//can attack black queen
			white_king.column=black_queen.column;
			white_king.row=black_queen.row;			
		}
	}
	else{//can attack black king
		white_king.column=black_king.column;
		white_king.row=black_king.row;		
	}
}
void whiteWinner(){
	printf("\nThe white is the winner\nEnd of Game\n");
}
void blackWinner(){
	printf("\nThe black is the winner\nEnd of Game\n");
}
int main() {
//	set initial positions of black and white
	initialBlackKingPos();
	initialBlackQueenPos();
	white_king.row=5;
	white_king.column=5;
	white_king.alive=true;
//	print the initial chessboard
	printChessBoard();
	print();
	char piece,col;
	int row;
	bool valid=false,validMove=false;
	while(moves<20&&(black_king.alive&&white_king.alive)){//run the loop for 20 moves of black and while black and white king are alive
		do {
			printf("Enter the piece and move\n");
			scanf(" %c %c %d", &piece, &col,&row);
			valid=isValidInput(piece,col,row);//check whether the input is valid
			if(!valid)
				printf("The input is not valid\nre-enter proper input\n");
			else{
				if(piece=='B'){
					validMove=isBlackKingValidMove(col,row);
//					if the black king move towards the cell of black queen make it as invalid move
					if (getColumn(col)==black_queen.column&&row==black_queen.row)
						validMove=false;

				}
				else if(piece=='Q'){
					validMove=isBlackQueenValidMove(col,row);
//					if the black queen move towards the cell of black king make it as invalid move
					if (getColumn(col)==black_king.column&&row==black_king.row)
						validMove=false;
				}
				if(!validMove)
					printf("Move is not valid\nre-enter a valid move\n");
					
				if(valid&&validMove){//if the input and move  is valid take further action
					
					bool win;
					moves+=1;
//					if the moving piece is black king
					if(piece=='B'){	
						black_king.column=getColumn(col);//change the alphabet to column number
						black_king.row=row;
					}
//					if the moving piece is black queen
					if(piece=='Q'){	
						black_queen.column=getColumn(col);//change the alphabet to column number
						black_queen.row=row;
					}
//					check whether the black checkmates the whiteking
					win=isCheckMate(piece);
//					print the chessboard after black's move
					printChessBoard();
//					print the positions of the pieces
					print();
					printf("\n");
//					if black didnt checkmate the white then move white
					if (!win){
						moveWhite();
	//					check whether white checkmates the black
						win=isCheckMate('W');
						printChessBoard();
						print();
					}
					
				}
			}
			
		}while(!valid&&!validMove);		//run the loop until valid input and valid move is given		
	}
	if(white_king.alive)//after 20 moves if still white king is alive then declare white as winner
		whiteWinner();	
  return 0;
}

