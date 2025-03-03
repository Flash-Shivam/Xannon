/*Ideas22222222222
⭐  -1. Still giving INVALID MOVE(wrong in game.py). 
	0. Doesn,t know townhall dead
	1. GAME: Improve Endgame Heuristics (If less stealth attack)
	2. GAME: Similar to above, Try adding heuristics for stealth attack
	0. Work on 10x10 rather than samller
XXX	3. TIME: Instead of calling Function directly see value of 'score'
XXX	4. TIME: Introduce sort at lower levels then instead of calling utility(after introduction of (3) TOO EXPENSIVE slower
	
	5. GAME: Stangnant Game?
	6. TEST: Match with TA Bots
	
	7. TIME: MutliThreading calculate best move for every next opponent move then play
	8. GAME: Better huristic and evaluation functions
	9. LEARN: Update weights after computation of utility form lower depths
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#include <string>
#include <climits>
#include"player2.cpp"

using namespace std;

//--Manual Options and Developer Options
int RED =1;	//Developer Option: check by reducing number of branches
bool LEARN = false;			//learn mode
bool DYNAMIC_DEPTH = true;	//Depth static or Dynamic
bool SORT = true;			//sort for better pruning
bool CLEAN = true;			//clean for utility calculation?
int DEPTH=2;
int ENDGAME = 4;		//4 bansal 5 sondhi ?
//vector<vector<int> > RealBoard;
//const int m=8,n=8;
int PLAYER_ID;		//1 ->black and 2 -> white	: Fixed for a game
//int RATE = 1;		//Learning rate
int DOWN = 0;		//opponent townhall down?
bool LESS = false;
/*Weights*/
int w_townhall_w =200;		//200~300
int w_townhall_b =-200;		//-200~300
int w_soldier_w  =90;		//90
int w_soldier_b  =-90;		//-90
int w_cannon_w	 =1;		//1
int w_cannon_b	 =-1;		//-1

int w_TcountW 	 =-20;		//-10
int w_TcountB 	 =20;		//10
int w_ScountW 	 =-10;		//-10
int w_ScountB 	 =10;		//10

int w_vicinityW		 =1;		//weight
int w_vicinityB		 =-1;		// weight

//Learned Values
//int l_townhall_w =923;		//200
//int l_townhall_b =-923;		//-200
//int l_soldier_w  =713;		//90
//int l_soldier_b  =-713;		//-90
//int l_cannon_w	 =1;		//1
//int l_cannon_b	 =-1;		//-1

//int l_TcountW 	 =-613;		//-10
//int l_TcountB 	 =613;		//10
//int l_ScountW 	 =-613;		//-10
//int l_ScountB 	 =613;		//10

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


/*----------------------CLASS BEGIN----------------------*/
class State{
	int m=8,n=8;				//	2-Black-Negative // 1-White-Positive

	vector<vector<int> > board;
	vector <tuple <char,pair <lld,lld>,pair <lld,lld > > > Moves;
	int moveToPlay =0;
	public: int moveIndex = 0;
			int score=0;				//	score of board /if no search done then equal to utility
//	int whosMoves = 1; 				//	1 get white move and 2 to get black move
	
	/*
		PLAYER_ID == whosMoves  Opponent
		PLAYER_ID !- whosMoves  your moves
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
	
	//Vicinity Count
	int vicinityB =0;
	int vicinityW =0;

	/*--END Statistics for evaluation function*/
	
	//Constructor
	public: State(vector<vector<int> > bored){
		m=getM();
		n=getN();
		board.resize(n);
		for(int i=0;i<n;i++)	board[i].resize(m);
		board = bored;
		//getBoardS();

	}

	//copy constructor
	public: void copy(State* st){
		m=getM();
		n=getN();
		board.resize(n);
		for(int i=0;i<n;i++)	board[i].resize(m);
		board = st->board;
//		whosMoves = 3-st->whosMoves;	//invert whose move
	}
	/*--Utility calculating functions--*/
	//Think how to layout the board and different sides in numbers##
	//writing code based on enemy -ve and black mostly

	//townhall and soldier count and vicinity count
	void setBasicCount(){
	
	//set to zero
		townhall_w =0;
		townhall_b =0;
		soldier_w = 0;
		soldier_b =0;

		for(int i=0;i<n;i++){
			for(int j=0;j<m;j++){
				if(board[i][j]==1){
					soldier_w++;
					vicinityW+=i;
				}
				else if(board[i][j]==-1){
					soldier_b++;
					vicinityB+=(n-i);
				}
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
	//To print outside board
	void printBoard(vector<vector<int> > board){
		for(int i=0;i<n;i++){
			for(int j=0;j<m;j++)
				cerr<<representation(board[i][j],i,j)<<"	";
			cerr<<endl<<endl;
		}
	}
	
	void printMove(int index){
		tuple<char,pair <int,int> ,pair <int,int> > move = Moves[index];
		cerr<<get<0>(move)<<" "<<get<1>(move).first<<" "<<get<1>(move).second<<" => "<<get<2>(move).first<<" "<<get<2>(move).second<<endl;
	}
	/*END Printing and Visualizatin Functions*/
	
	//cannon count
	int getCannonCount(){
		cannon_b=0;
		cannon_w=0;
		//Horizontal cannons
		for(int i=0;i<n;i++){
			for(int j=0;j<m-2;j++){
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
	//###Might Over write !!!!
		vector <tuple <char,pair <lld,lld>,pair <lld,lld > > > Moves;
		Moves =validMovesR(2);	//moves of white
		TcountB=0;
		ScountB=0;
		for(int i=0;i<Moves.size();i++){
			if(board[get<2>(Moves[i]).first][get<2>(Moves[i]).second]==-1)	//black soldier present
				ScountB++;
			if(board[get<2>(Moves[i]).first][get<2>(Moves[i]).second]==-2)	//black soldier present
				TcountB++;
		}
	}
	//no of white soliders in attacking range
	void whiteUnderAttack(){
	
		vector <tuple <char,pair <lld,lld>,pair <lld,lld > > > Moves;
		Moves =validMovesR(1);	//moves of black
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

	public: int utility(){	//high desired for US
		int util=0;
		setBasicCount();
		getCannonCount();
		blackUnderAttack();
		whiteUnderAttack();
		//setVicinity();
		
	//⭐END GAME Heuristics⭐//
		if(soldier_w < ENDGAME &&PLAYER_ID==2){
//			cerr<<"We are in the ENDGAME now!\n";
			//when less soldiers then save your soldiers
			w_soldier_w=130;		//120
			//stay out of attacking zones
			w_ScountW = -70;		//-60
			//Don't Try to attack soldiers
			w_ScountB = 5;			//-5
		
		}
		
		else if(soldier_b < ENDGAME &&PLAYER_ID==1){
//			cerr<<"We are in the ENDGAME now!\n";
			//when less soldiers then save your soldiers
			w_soldier_b=-130;		//-120
			//stay out of attacking zones
			w_ScountB = 70;		//60
			//Don't Try to attack soldiers
			w_ScountW = -5;			//-5
		
		}
	//END ENDGAME Heuristics//

		util += (w_townhall_w*townhall_w + w_townhall_b*townhall_b);
//		cerr<<"Util TC: "<<util<<endl;
		util += (w_soldier_w*soldier_w	 + w_soldier_b*soldier_b);
//		cerr<<"Util BC: "<<util<<endl;
		util += (w_cannon_w*cannon_w	 + w_cannon_b*cannon_b);
//		cerr<<"Util CC: "<<util<<endl;
		util += (w_TcountW*TcountW		 + w_TcountB*TcountB);
		util += (w_ScountW*ScountW		 + w_ScountB*ScountB);
//		cerr<<"TcountW: "<<TcountW<<" TcountB: "<<TcountB<<endl;
//		cerr<<"ScountW: "<<ScountW<<" ScountB: "<<ScountB<<endl;
//		cerr<<"Util AC: "<<util<<endl;

		//closeness to other townhalls
		util += (w_vicinityW*vicinityW	+	w_vicinityB*vicinityB)/10;

 		if(PLAYER_ID==1)
 			util = -util;
		score = util;
		return util;
	}
	/*----END Utility Calculating functions*/

	/*---Functions to communicate with player module---*/

	//Just gives board position if current move played
	void move(tuple<char,pair <int,int> ,pair <int,int> > move,int turn){
		//printBoard();
		//cerr<<"PLAYER_ID fiven: "<<turn<<endl;
		board = update(board,move,3-turn);	//in player.cpp
	}
	
	//Primary method to get validMoves
	void validMoves(int turn){
		Moves= getValidMoves(board,3-turn);	//in player.cpp
		//removeBlank();	//remove blank cannon shots
		clean(Moves);		//remove repetitive bomb shots/
	}
	
	//Secondary method to get validMoves for utility calculation
	 vector <tuple <char,pair <lld,lld>,pair <lld,lld > > > validMovesR(int turn){
		vector <tuple <char,pair <lld,lld>,pair <lld,lld > > > Moves= getValidMoves(board,3-turn);	//in player.cpp
		//removeBlank();	//remove blank cannon shots
		if(CLEAN)
			clean(Moves);		//remove repetitive bomb shots/
		return Moves;
	}
	
	//removes duplicate cannon shot moves and ARRANGES bomb shots before
	void clean(vector <tuple <char,pair <lld,lld>,pair <lld,lld > > > &Moves){
		for(int i=0;i<Moves.size();i++){
			if(get<0>(Moves[i])=='M')
				continue;

			for(int j=i+1;j<Moves.size();j++){
				if(get<0>(Moves[j])=='M')
					continue;
				if(get<2>(Moves[i])==get<2>(Moves[j])){	//same target
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
	tuple <char,pair <lld,lld>,pair <lld,lld > >  play(int i){
		moveToPlay=i;
		return Moves[moveToPlay];	//update in player.cpp
	}
	
	//return all the board positions after one ply
	vector<State*> Successors(int turn){

		validMoves(turn);

		vector<State*> children(Moves.size());

		for(int i=0;i<Moves.size();i++){
			children[i] = new State(board);	//#check once: copy constructor working?
			children[i]->copy(this);//problem in copy
			//printBoard();
			children[i]->move(Moves[i],turn);
			children[i]->moveIndex=i;

//		 	children[i]->printBoard();
		 	
		 	//Move and Utility
//			cerr<<"Utility of "<<i<<"th move is "<<children[i]->utility()<<endl;
//			printMove(i);
			//printBoard();
		//	cerr<<"-------------------------------------------"<<endl;
		}
		
		return children;
	}
	
};

/*--------------------------------------------------END Class Def; BEGIN MINIMAX--------------------------------------------------*/

//Learning
//void learn(int o , int n){
//	int loss = n-o;
//	int delta = RATE*loss;
//	delta/=8;
//	if(PLAYER_ID==1)
//		delta=-delta;
//		
//	l_townhall_w+=delta;
//	l_townhall_b-=delta;
//	l_soldier_w	+=delta;
//	l_soldier_b	-=delta;
//	
//	l_ScountW	+=delta;
//	l_ScountB	-=delta;
//	l_TcountW	+=delta;
//	l_TcountB	-=delta;
//	
//	cerr<<"int l_townhall_w = "<<l_townhall_w<<";"<<endl;
//	cerr<<"int l_townhall_b = "<<l_townhall_b<<";"<<endl;
//	cerr<<"int l_soldier_w =  "<<l_soldier_w<<";"<<endl;
//	cerr<<"int l_soldier_b = "<<l_soldier_b<<";"<<endl;

//	cerr<<"int l_ScountW: "<<l_ScountW<<";"<<endl;
//	cerr<<"int l_ScountB: "<<l_ScountB<<";"<<endl;	
//	cerr<<"int l_TcountW: "<<l_TcountW<<";"<<endl;
//	cerr<<"int l_TcountB: "<<l_TcountB<<";"<<endl;
//}


/*---------------Helper Functions---------------*/

// Put higher utility state prior
bool compareStates(State* left, State* right){
	int l = left->score;
	int r = right->score;
	return l > r;
}
	
/*--------------END-Helper Functions-END--------*/


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
	int alpha = INT_MIN;
	int beta = INT_MAX;

	
	vector<State*> children = state->Successors(PLAYER_ID);	//own moves
	int BranchF = children.size();
	
	if(BranchF<=0){
		cerr<<"No Moves to Play!\n";
		return 0;
	}
	
	//Compute and store utilities of all children for sorting
	for(int i=0;i<BranchF;i++)
		int temp=children[i]->utility();
		
	//Sort according to utility for better pruning
	if(SORT)
		sort(children.begin(),children.end(),compareStates);
	
	//set depth based on number of moves
	
	if(DYNAMIC_DEPTH& (!LESS)){
		if(children.size()>30) depth = 3;
		else if(children.size()>20) depth = 4;
		else if(children.size()>10) depth = 5;
		if(children.size()<=10) depth = 6;
		if(children.size()<3)  depth = 7;	//8 is too much
	}
	
//	cerr<<"\nBranch Factor: "<<children.size()<<endl;
//	cerr<<"Depth: "<<depth<<endl;

	if(depth <=0){	//Random Player
		srand(time(NULL));
		return rand()%(children.size());
	}

	max_value = MinVal(children[0],alpha,beta,depth-1);	//put first value in max_value

	
//	cerr<<"Max Initial"<<max_value<<" Index: "<<max_index<<"Utility: "<<children[0]->utility()<<endl;
//	children[0]->printBoard();

	for(int i=0;i<children.size();i++){
		
		v=MinVal(children[i],alpha,beta,depth-1);

//		v=MinVal(children[i],alpha,beta,depth-1);		
//		alpha = max(alpha,v);
//		if (alpha<v){
//			alpha = v;
//			max_index=i;
//		}
		
//		cerr<<"Trying value "<<v<<" Index: "<<i<<"\n "<<endl;
//		state->printMove(children[i]->moveIndex);
//		cerr<<"Uitlity: "<<children[i]->utility()<<endl;
//		children[i]->printBoard();
//		cerr<<"v: "<<v<<endl;
//		
		if(v>max_value){
			max_value=v;
			max_index=i;
			
//			cerr<<"Max value "<<max_value<<" Index: "<<max_index<<"Utility: "<<children[i]->utility()<<endl;
//			children[i]->printBoard();
		}
	}
	
	//## Can Update weights here
//	cerr<<"Max update "<<max_value<<" Index: "<<max_index<<"Utility: "<<children[max]->utility()<<endl;

//	cerr<<"Uitlity: "<<children[max_index]->utility()<<endl;
//	children[max_index]->printBoard();
		
		
//	cerr<<"Utility: "<<max_value<<endl;
//	state->printMove(children[max_index]->moveIndex);
//	cerr<<"(Index, Pre): ("<<max_index<<", "<<children[max_index]->moveIndex<<")\n\n";
	
	return children[max_index]->moveIndex;
}

/*
	returns minimum utility value
*/
int MinVal(State *state,int alpha,int beta,int depth){
	int child;
//	cerr<<"Utility of this state: "<<state->utility()<<endl;
	if (/*state->terminal()*/depth <=0)	//## can we so with cutoff or need to have different checks for terminal and cutoff nodes??
		return state->utility();
		
	vector<State*> children = state->Successors(3-PLAYER_ID);	//3 minus; to get other persons move

	if(children.size()<=0)	//NO Moves left for opponent
		return state->utility();

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
	
	if(children.size()<=0)	//NO Moves left
		return state->utility();
	
	for (int i=0;i<children.size();i++){
		child = MinVal(children[i],alpha,beta,depth-1);
		alpha = max(alpha,child);
		if (alpha>=beta)
			return child;
	}
	return alpha;
}
