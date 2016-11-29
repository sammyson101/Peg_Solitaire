/*

	THE BOARD
	  0
	 1 2
       3  4  5
     6  7  8  9
   10 11 12 13 14

       ROW/COLUMN SET UP       PEG NUMBER
	0,0 0,1 0,2 0,3 0,4     0, 2, 5, 9, 14
	1,0 1,1 1,2 1,3         1, 4, 8, 13
	2,0 2,1 2,2 	 	3, 7, 12,
	3,0 3,1			6, 11
	4,0	                10

	Anytime a direction is referenced in comments, it is in terms of the above sideways boards

	Directions you can jump  
	N S 
	E W
	NE SW

	Directions you cannot jump
	NW SE

	When jumping the peg one away in a valid direction must be full
				&&
	The peg two away in the same valid direction must be empty
*/	


#include <vector>
#include <iostream>
#include <cstdio>
#include <stdlib.h>
#include <string>

using namespace std;


/*Structure for pegs*/ 
struct Peg {
	int value;
	int status;
	
};


/*Flip a spot on the board from empty to full or vice versa*/
void switchPeg(struct Peg &peg){
	if(peg.status == 0){
		peg.status = 1;
	}

	else{
		peg.status = 0;
	}
}


	/*Switch statement checking playerStart variable that gets passed during program call. playerStart represents the peg number that will be empty to start the game*/
void startGame(vector<vector<struct Peg> > &game, int playerStart){
	switch(playerStart){
		case 0:
			switchPeg(game[0][0]);
			break;
		case 1:
			switchPeg(game[1][0]);
			break;
		case 2:
			switchPeg(game[0][1]);
			break;
		case 3:
			switchPeg(game[2][0]);
			break;
		case 4:
			switchPeg(game[1][1]);
			break;
		case 5:
			switchPeg(game[0][2]);
			break;
		case 6:
			switchPeg(game[3][0]);
			break;
		case 7:
			switchPeg(game[2][1]);
			break;
		case 8:
			switchPeg(game[1][2]);
			break;
		case 9:
			switchPeg(game[0][3]);
			break;
		case 10:
			switchPeg(game[4][0]);
			break;
		case 11:
			switchPeg(game[3][1]);
			break;
		case 12:
			switchPeg(game[2][2]);
			break;
		case 13:
			switchPeg(game[1][3]);
			break;
		case 14:
			switchPeg(game[0][4]);
			break;
		default:
			printf("How'd you even get here. You done borked it!\n");
			exit(1);
	}//end switch
}



/*Print the current state of the board with 1's and 0's to represent peg placements*/
void printBoard(vector<vector<struct Peg> > game){
	printf("         %d\n", game[0][0].status);
	printf("       %d   %d\n", game[1][0].status, game[0][1].status);	
	printf("     %d   %d   %d\n", game[2][0].status, game[1][1].status, game[0][2].status);
	printf("   %d   %d   %d   %d\n", game[3][0].status, game[2][1].status, game[1][2].status
								   , game[0][3].status);
	printf(" %d   %d   %d   %d   %d\n",game[4][0].status,game[3][1].status, game[2][2].status
									  , game[1][3].status, game[0][4].status);
printf("----------------------\n");
}

/*Count and return the number of pegs(1's) in the board*/
int countPegs(vector<vector<struct Peg> > game){	
	int i = 0;
	int j = 0;
	int pegs = 0;
	while(i < game.size()){
		while(j < game[i].size()){
			if(game[i][j].status == 1){
				pegs++;	
			}	
			j++;
		}
		i++;
		j = 0;
	}
	return pegs;
}


/*Recursive function to solve game*/
/*Cases in this function represent what column/row the peg movement is starting from */

void solveGame(vector<vector<struct Peg> > game,  vector<vector<vector<struct Peg> > > &boardList, bool &success)
{
	int i = 0;
	int j = 0;

	//push current board onto the moveList
	boardList.push_back(game);
	
	//if (pegs == 1) end game by setting success to true
	//success being true will break through all recursive calls of solveGame as unwind happens
	if(countPegs(game) == 1){
		success = true;
				
		while(i < boardList.size()){
			printBoard(boardList[i]);
			i++;
		}
	}


	vector<vector<struct Peg> > newOne;
	i = 0;
	j = 0;
	//loop thourgh game while success == false
//	while(success == false){
		while(i < game.size() && success == false){
			while(j < game[i].size() && success == false){
				//until we find a "peg"
				if(game[i][j].status == 1 && success == false){
				
					
					//BEGIN JUMP TESTS

					//TEST NORTH
					if(success == false){		
			//check spot furthest away in jump exists				
						if(i - 2 >= 0){
							//if it exists check legal peg placement
							if(game[i-1][j].status == 1 && game[i-2][j].status == 0){
								//if move is legal -> make the move, call recursively
								newOne = game;
								switchPeg(newOne[i][j]);	
								switchPeg(newOne[i-1][j]);
								switchPeg(newOne[i-2][j]);
								
								solveGame(newOne, boardList, success);
							}//end if(pegPlacement)
						}//end if(i-2 >= 0)	
					}//end TEST NORTH
				
					//TEST SOUTH
					//switch on j since it determines how far i can go
					//Steps in switch: //check that pegs in jump are in a vaild arragement
											 //if they are make the move in a new board
											 //call recursively on new board
					if(success == false){			
						switch(j){
							//column 0
							case 0: 
								if(i + 2 <= 4){
									if(game[i+1][j].status == 1 && game[i+2][j].status == 0){
										newOne = game;
										switchPeg(newOne[i][j]);
										switchPeg(newOne[i+1][j]);
										switchPeg(newOne[i+2][j]);
										solveGame(newOne, boardList, success);
									}
								}
								break;
								
							//column 1
							case 1:
								if(i + 2 <= 3){
									if(game[i+1][j].status == 1 && game[i+2][j].status == 0){
										newOne = game;
										switchPeg(newOne[i][j]);
										switchPeg(newOne[i+1][j]);
										switchPeg(newOne[i+2][j]);
										solveGame(newOne, boardList, success);
									}
								}
								break;
							
							//column 2
							case 2:
								if (i + 2 <= 2){
									if(game[i+1][j].status == 1 && game[i+2][j].status == 0){
										newOne = game;
										switchPeg(newOne[i][j]);
										switchPeg(newOne[i+1][j]);
										switchPeg(newOne[i+2][j]);
										solveGame(newOne, boardList, success);
									}
								}
								break;
							
							//column 3 and 4 can't move south							
							default:
								break;	
				
						}//end switch	
					}//end TEST SOUTH

					
					//TEST EAST
					if(success == false){
						//switch on i since its value determines how far j can go
						//Steps in switch: //check that pegs in jump are in a vaild arragement
						  						 //if they are make the move in a new board
												 //call recursively on new board
						switch(i){
							//row 0
							case 0: 
								if(j + 2 <= 4){
									if(game[i][j+1].status == 1 && game[i][j+2].status == 0){
										newOne = game;
										switchPeg(newOne[i][j]);
										switchPeg(newOne[i][j+1]);
										switchPeg(newOne[i][j+2]);
										solveGame(newOne, boardList, success);
									}
								}
								break;
								
							//row 1
							case 1:
								if(j + 2 <= 3){
									if(game[i][j+1].status == 1 && game[i][j+2].status == 0){
										newOne = game;
										switchPeg(newOne[i][j]);
										switchPeg(newOne[i][j+1]);
										switchPeg(newOne[i][j+2]);
										solveGame(newOne, boardList, success);
									}
								}
								break;
							
							//row 2
							case 2:
								if (j + 2 <= 2){
									if(game[i][j+1].status == 1 && game[i][j+2].status == 0){
										newOne = game;
										switchPeg(newOne[i][j]);
										switchPeg(newOne[i][j+1]);
										switchPeg(newOne[i][j+2]);
										solveGame(newOne, boardList, success);
									}
								}
								break;
							
							//column 3 and 4 can't move east							
							default:
								break;	
				
						}//end switch			
					}//end TEST SOUTH		


					//TEST WEST
					if(success == false){		
			//check spot furthest away in jump exists				
						if(j - 2 >= 0){
							//if it exists check legal peg placement
							if(game[i][j-1].status == 1 && game[i][j-2].status == 0){
								//if move is legal -> make the move, call recursively
								newOne = game;
								switchPeg(newOne[i][j]);	
								switchPeg(newOne[i][j-1]);
								switchPeg(newOne[i][j-2]);
								solveGame(newOne, boardList, success);
							}//end if(pegPlacement)
						}//end if(j-2 >= 0)	
					}//end TEST WEST 
									

					//TEST NORTH EAST
					//switch on peg.value
					//concept: only a few pegs(3, 6, 7, 10, 11, 12) can make this jump legally.
					//since checking boudaries is a litte more complex than other moves....
					//hardcode the switchPeg() calls based on the case
					//YAY MAGIC NUMBERS!!!!!!
						
					if(success == false){				
						switch(game[i][j].value){
							case 3:
							case 6:
							case 7:
							case 10:
							case 11:
							case 12:
								if(game[i-1][j+1].status == 1 && game[i-2][j+2].status == 0){
									newOne = game;
									switchPeg(newOne[i][j]);
									switchPeg(newOne[i-1][j+1]);
									switchPeg(newOne[i-2][j+2]);
									solveGame(newOne, boardList, success);
									break;
								} 
							
							default:
								break;		
						}//end switch
					}//end TEST NORTH EAST

					//TEST SOUTH WEST
					//same sort of switch as the NE move
					if(success == false){
						switch(game[i][j].value){
							case 5:
							case 8:
							case 9:
							case 12:
							case 13:
							case 14:
								if(game[i+1][j-1].status == 1 && game[i+2][j-2].status ==0){
									newOne = game;
									switchPeg(newOne[i][j]);
									switchPeg(newOne[i+1][j-1]);
									switchPeg(newOne[i+2][j-2]);
									solveGame(newOne, boardList, success);
									break;
								}

							default:
								break;
						}//end switch
					}//end TEST SOUTH WEST
					
					
				}//end if(game[i][j].status == 1)
				

				j++;
			}//end while(j<game[i].size())
			i++;
			j = 0;
		}//end while(i<game.size())
		
		//If we reach this spot that means we didn't find a peg that could move
		//since we have reached a dead end we will unwind
		//pop current board off of boardList since it isn't apart of the final solution
		boardList.pop_back();
	
//	}//end while(success == false)


}//end function


	
int main(int argc, char** argv){
	/*error checks for proper arguements*/
	if(argc < 1 || argc > 3){
		printf("Inproper number of arguements. Argc must = 2 or 3\n");
		exit(1);				
	}

	//read argv[1] into an int	
	int playerStart;
	sscanf(argv[1], "%d", &playerStart);
		
	if(playerStart < 0 || playerStart > 14){
		printf("Improper use of argv[1]. ");
		printf("Argv[1] must be between 0 and 14 inclusively\n");
		exit(1);
	}

	//boardlist to be printed at the end showing winning path	
	vector<vector<vector<struct Peg> > > boardList;

	/*Create game board and populate it with "pegs"*/
	vector<vector<struct Peg> > game(5);
	
	int i = 0;
	int j = 0;
	struct Peg temp;
	temp.status = 1;

	//row 0
	temp.value = 0;
	game[0].push_back(temp);	
	temp.value = 2;
	game[0].push_back(temp);	
	temp.value = 5;
	game[0].push_back(temp);	
	temp.value = 9;
	game[0].push_back(temp);	
	temp.value = 14;
	game[0].push_back(temp);	
	
	//row 1
	temp.value = 1;
	game[1].push_back(temp);	
	temp.value = 4;
	game[1].push_back(temp);	
	temp.value = 8;
	game[1].push_back(temp);	
	temp.value = 13;
	game[1].push_back(temp);	

	//row 2
	temp.value = 3;
	game[2].push_back(temp);	
	temp.value = 7;
	game[2].push_back(temp);	
	temp.value = 12;
	game[2].push_back(temp);	
	
	//row 3
	temp.value = 6;
	game[3].push_back(temp);	
	temp.value = 11;
	game[3].push_back(temp);	
	
	//row 4
	temp.value = 10;
	game[4].push_back(temp);
	
		
	bool success = false;

	startGame(game,playerStart);
	
		

	solveGame(game,boardList,success);


	return 0;
}
