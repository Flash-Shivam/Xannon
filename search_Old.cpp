#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#include<string>
#include"player.cpp"

int RED =1;	//Developer Option: check by reducing number of branches
using namespace std;

//const int m=8,n=8;
//vector<vector<int> > RealBoard;
int DEPTH=3;
int PLAYER_ID;		//1 ->black and 2 -> white
/*Weights*/
int w_townhall_w =500;
int w_townhall_b =-500;
int w_soldier_w  =90;
int w_soldier_b  =-95;
int w_cannon_w	 =15;
int w_cannon_b	 =-15;

int w_TcountW 	 =-1;
int w_TcountB 	 =1;
int w_ScountW 	 =-1;
int w_ScountB 	 =1;

/*
	  -------(m)------>
	| 🔳🔲🔳🔲🔳🔲🔳🔲
	| 🔳🔲🔳🔲🔳🔲🔳🔲
	| 🔳🔲🔳🔲🔳🔲🔳🔲
   (n)🔳🔲🔳🔲🔳🔲🔳🔲
	| 🔳🔲🔳🔲🔳🔲🔳🔲
	| 🔳🔲🔳🔲🔳🔲🔳🔲
	| 🔳🔲🔳🔲🔳🔲🔳🔲
	V 🔳🔲🔳🔲🔳🔲🔳🔲
*/
/*Ideas
	MutliThreading calculate best move for every next opponent move then play
	Better huristic and evaluation functions
	more depth
*/

/*---------------Helper Functions---------------*/
//struct CustomLessThan
//{
//    bool operator()(tuple<T1, T2, T3> const &lhs, tuple<T1, T2, T3> const &rhs) const
//    {
//    	get<0>(lhs)<get<0>(rhs)	//bomb shots arranges before
//};
/*--------------END-Helper Functions-END--------*/

/**/
class State{
	int m=8,n=8;					//	2-Black-Negative // 1-White-Positive
	int score=0,id=1;				//	score of board /if no search done then equal to utility
	vector<vector<int> > board;
	vector <tuple <char,pair <lld,lld>,pair <lld,lld > > > Moves;
	int moveToPlay =0;
	int whosMoves = 1; 				//	1 get white move and 2 to get black move
	
	/*
		id == whosMoves  Opponent
		id !- whosMoves  your moves
	*/
	
	/*Statistics for evaluation function*/
	
	//Basic count
	int townhall_w  = 4;
	int soldier_w   = 16;
	int cannon_w	= 4;

	int townhall_b 	= 4;
	int soldier_b  	= 16;
	int cannon_b	= 4;
	
	//Attack count
	int TcountB =0;
	int TcountW =0;
	int ScountB =0;
	int ScountW =0;

	/*--END Statistics for evaluation function*/
	
	//Constructor
	public: State(int ID,vector<vector<int> > bored){
		m=getM();
		n=getN();
		board.resize(n);
		for(int i=0;i<n;i++)	board[i].resize(m);
		board = bored;
		//getBoardS();
		id= ID;

	}

	//copy constructor
	public: void copy(State* st){
		m=getM();
		n=getN();
		board.resize(n);
		for(int i=0;i<n;i++)	board[i].resize(m);
		board = st->board;
		id = st->id;
		whosMoves = 3-st->whosMoves;	//invert whose move
	}
	/*--Utility calculating functions--*/
	//Think how to layout the board and different sides in numbers##
	//writing code based on enemy -ve and black mostly

	//townhall and soldier count
	void setBasicCount(){
	
	//set to zero
		townhall_w =0;
		townhall_b =0;
		soldier_w = 0;
		soldier_b =0;

		for(int i=0;i<n;i++){
			for(int j=0;j<m;j++){
				if(board[i][j]==1)			soldier_w++;
				else if(board[i][j]==-1)	soldier_b++;
				else if(board[i][j]==2)		townhall_w++;
				else if(board[i][j]==-2)	townhall_b++;
			}
		}
	}
	
	/*
		DevOpt:Printing visual functions
	*/
	string representation(int i, int x, int y){
		switch (i){
			case 1 : return "⚪";
			case -1: return "⚫";
			case 2 : return "🔲";
			case -2 : return "🔳";
			default: if(x%2==y%2) return "  "; else return "  ";

//			default: if(x%2==y%2) return "⬛"; else return "⬜";
		}
		return "X";
	}
	
	void printBoard(){
		for(int i=0;i<n;i++){
			for(int j=0;j<m;j++)
				cerr<<representation(board[i][j],i,j)<<"	";
			cerr<<endl<<endl;
		}
	}
	/*END Printing and Visualizatin Functions*/
	
	//cannon count
	int getCannonCount(){
		cannon_b=0;
		cannon_w=0;
		//Horizontal cannons
		for(int i=0;i<n;i++){
			for(int j=0;i<j-2;j++){
				if(board[i][j]==1&&board[i][j+1]==1&&board[i][j+2]==1)	//horizontal cannon found
					cannon_w++;
				else if(board[i][j]==-1&&board[i][j+1]==-1&&board[i][j+2]==-1)
					cannon_b++;
			}
		}
		//vertical cannons
		for(int j=0;j<m;j++){
			for(int i=0;i<m-2;i++){
				if(board[i][j]==1&&board[i+1][j]==1&&board[i+2][j]==1)
					cannon_w++;
				else if(board[i][j]==-1&&board[i+1][j]==-1&&board[i+2][j]==-1)
					cannon_b++;
			}
		}
		//bottom right diagonal cannons
		for(int i=0;i<n-2;i++){
			for(int j=0;j<m-2;j++){
				if(board[i][j]==1&&board[i+1][j+1]==1&&board[i+2][j+2]==1)
					cannon_w++;
				else if(board[i][j]==-1&&board[i+1][j+1]==-1&&board[i+2][j+2]==-1)
					cannon_b++;
			}
		}
		//bottom left diagonal cannons
		for(int i=0;i<n-2;i++){
			for(int j=2;j<m;j++){
				if(board[i][j]==1&&board[i+1][j-1]==1&&board[i+2][j-2]==1)
					cannon_w++;
				else if(board[i][j]==-1&&board[i+1][j-1]==-1&&board[i+2][j-2]==-1)
					cannon_b++;
			}
		}

	}

	//no of black soliders in attacking range
	void blackUnderAttack(){
		validMoves(1);	//moves of white
		TcountB=0;
		ScountB=0;
		for(int i=0;i<Moves.size();i++){
			if(board[get<2>(Moves[i]).first][get<2>(Moves[i]).second]==-1)	//black soldier present
				ScountB++;
			if(board[get<2>(Moves[i]).first][get<2>(Moves[i]).second]==-2)	//black soldier present
				TcountB++;
		}
	}
	//no of black soliders in attacking range
	void whiteUnderAttack(){
		validMoves(2);	//moves of black
		TcountW=0;
		ScountW=0;
		for(int i=0;i<Moves.size();i++){
			if(board[get<2>(Moves[i]).first][get<2>(Moves[i]).second]==1)	//white soldier present
				ScountW++;
			if(board[get<2>(Moves[i]).first][get<2>(Moves[i]).second]==2)	//white soldier present
				TcountW++;
		}
	}
	//soldiers under attacki
	//number of cannons
	//enemy cannons
	//attacking cannos
	//under attack form cannons
	//townhalls under attack
	//townhall in attacking range
	//Sum of coordinates of our soldiers
	int sum(){
		int sumJ=0;
		for(int i=0;i<n;i++){
			for(int j=0;j<m;j++){
				if(board[i][j]==1)
					sumJ+=i;
			}
		}
		return sumJ;
	}



	public: int utility(){	//high desired for US
		int util=0;
		setBasicCount();
		getCannonCount();
		blackUnderAttack();
		whiteUnderAttack();

		util += w_townhall_w*townhall_w	+ 	w_townhall_b*townhall_b;
		util += w_soldier_w*soldier_w	+	w_soldier_b*soldier_b;
		util += w_cannon_w*cannon_w		+	w_cannon_b*cannon_b;
		util += w_TcountW*TcountW		+	w_TcountB*TcountB;
		util += w_ScountW*ScountW		+	w_ScountB*ScountB;
		//closeness to other townhalls
	//	util += sum()/10;	//to get closeness to other townhalls
 		if(id=1)
 			util = -util;
		score = util;
		return util;
	}
	/*----END Utility Calculating functions*/

	/*---Functions to communicate with player module---*/

	//Just gives board position if current move played
	void move(tuple<char,pair <int,int> ,pair <int,int> > move,int turn){
		//printBoard();
		//cerr<<"id fiven: "<<turn<<endl;
		board = update(board,move,turn);
	}
	void validMoves(int turn){
		Moves= getValidMoves(board,turn);	//in player.cpp
		//removeBlank();	//remove blank cannon shots
		clean();		//remove repetitive bomb shots/
	}
	//removes duplicate cannon shot moves and arranges bomb shots before
	void clean(){
		for(int i=0;i<Moves.size();i++){
			if(get<0>(Moves[i])=='M')
				continue;

			for(int j=i+1;j<Moves.size();j++){
				if(get<0>(Moves[j])=='M')
					continue;
				if(get<2>(Moves[i])==get<2>(Moves[j])){	//same target
	//			 	it= find(Moves.begin(), Moves.end(), 5);
					swap(Moves[j],Moves[Moves.size()-1]);
					Moves.pop_back();
					j--;
				}
			}
		}
	}
	
	//Removes duplicate bomb shots of same cannon
	void removeBlank(){
		for(int i=0;i<Moves.size();i++){
			if(get<0>(Moves[i])=='M')
				continue;
			if(board[get<2>(Moves[i]).first][get<2>(Moves[i]).second]==0)
			swap(Moves[i],Moves[Moves.size()-1]);
					Moves.pop_back();
					i--;

		}
	}

	void getBoardS(){
		board=getBoard();	//in player.cpp
	}
	
	//Play function: Actually plays the move and updates board
	tuple <char,pair <lld,lld>,pair <lld,lld > >  play(){
		return Moves[moveToPlay];	//update in player.cpp
	}

	//return all the board positions after one ply
	vector<State*> Successors(int turn){
		turn = 3-turn;
		validMoves(turn);
		//cerr<<"turhin: "<<turn<<endl;
		vector<State*> children(Moves.size());
//		cerr<<"MoveSize: "<<Moves.size()<<endl;
		for(int i=0;i<Moves.size();i++){
			children[i] = new State(id,board);	//#check once: copy constructor working?
			children[i]->copy(this);//problem in copy
			//printBoard();
			children[i]->move(Moves[i],turn);
//			cerr<<"a\n";
//		 	children[i]->printBoard();
//			cerr<<"Utility of "<<i<<" move "<<children[i]->utility()<<endl;
	//		cerr<<"Cannon counts Black"<<children[i]->cannon_b<<" White "<<children[i]->cannon_w<<endl;
			//printBoard();
		//	cerr<<"-------------------------------------------"<<endl;
		}
		return children;
	}

	void selectMove(int i){	//gives INDEX of what move to play
		moveToPlay=i;
	}
};

/*----------END Class Def; BEGIN MINIMAX----------*/


/*--Function Prototypes--*/
int MiniMax(State *state, int depth);
int MinVal(State *state,int alpha,int beta,int depth);
int MaxVal(State *state,int alpha,int beta,int depth);
/*--Function Prototypes*/

//returns an index for best action // depth =0 means random player
int MiniMax(State *state, int depth){

	int max_value=0;
	int max_index=0;
	int v;
	//cerr<<"IN MINMAX\n";
	vector<State*> children = state->Successors(PLAYER_ID);	//own moves

	//set depth based on number of moves

	if(children.size()>50) DEPTH = 3;
	else if(children.size()>10) DEPTH = 4;
	if(children.size()<=10) DEPTH = 5;
	if(children.size()<3)  DEPTH = 6;

	if(depth <=0){	//Random Player
		srand(time(NULL));
		return rand()%(children.size());
	}

	max_value = MinVal(children[0],INT8_MIN,INT8_MAX,depth-1);	//put first value in max_value
	
//	cerr<<"Max Initial"<<max_value<<" Index: "<<max_index<<"Utility: "<<children[0]->utility()<<endl;
//	children[0]->printBoard();

	for(int i=1;i<children.size();i++){
		v=MinVal(children[i],INT8_MIN,INT8_MAX,depth-1);
		
//		cerr<<"Trying value "<<v<<" Index: "<<i<<"\n Utility: "<<children[i]->utility()<<"\n "<<endl;
//		children[i]->printBoard();
//		cerr<<"v: "<<v<<endl;
//		
		if(v>max_value){
			max_value=v;
			max_index=i;
			
	//		cerr<<"Max updatej value "<<max_value<<" Index: "<<max_index<<"Utility: "<<children[i]->utility()<<endl;
	//		children[i]->printBoard();
		}
	}
	
	//## Can Update weights here
//	cerr<<"Max update"<<max_value<<" Index: "<<max_index<<"Utility: "<<children[max]->utility()<<endl;/
//	chilren[]printBoard();

	return max_index;
}

/*
	returns minimum utility value
*/
int MinVal(State *state,int alpha,int beta,int depth){
	int child;
//	cerr<<"Utility of this state: "<<state->utility()<<endl;
	if (/*state->terminal()*/depth <=0)	//## can we so with cutoff or need to have different checks for terminal and cutoff nodes??
		return state->utility();
	vector<State*> children = state->Successors(3-PLAYER_ID);	//to get other persons move

	for (int i=0;i<children.size();i++){
		child = MaxVal(children[i],alpha,beta,depth-1);
		beta = min(beta,child);
		if(alpha>=beta)
			return child;
	}
	return beta;	//beta
}
/*END MinVal*/

//alpha = the highest value for MAX along the path
//beta = the lowest value for MIN along the path

/*
	returns maximum utility value
*/
int MaxVal(State *state, int alpha, int beta,int depth){
	int child;
//		cerr<<"Utility of this state: "<<state->utility()<<endl;
	if (/*state->terminal()*/depth <=0)
		return state->utility();
	vector<State*> children = state->Successors(PLAYER_ID);
	for (int i=0;i<children.size();i++){
		child = MinVal(children[i],alpha,beta,depth-1);
		alpha = max(alpha,child);
		if (alpha>=beta)
			return child;
	}
	return alpha;
}
