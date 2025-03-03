#include <iostream>
#include <time.h>
#include <vector>
#include "search.cpp"
using namespace std;

int main(){

  int m,n,player_id,time;	//for input
	//int turn;	//0 or 1
  cin >> player_id >> m >> n >> time;	//first line input##s
  //player_id=1;m=8;n=8;time=90;
	PLAYER_ID = player_id;
  char a,b;
  lld x,y,p,q,i,j,k;

  intialize_board();
  State *st = new State(Board);
//  st->getBoardS();

  if(player_id == 1){
  //BLACK
  while(1){

/*---SEARCH---*/
//	printBoard()
  	st->getBoardS();
    int MyMove = MiniMax(st,DEPTH);
//	st->selectMove(MyMove);	//select move given by minimax
	tuple <char,pair <lld,lld>,pair <lld,lld > >  moveToPlay = st->play(MyMove);

/*------------*/

    // k is the index of the soldier selected ;
     // here 1 is the player number.
    // cuurent location of the selected player
    x = get<1>(moveToPlay).first;	//SHAYAN reverse order
    y = get<1>(moveToPlay).second;	//SAHAYAN reverse order
   	p = get<2>(moveToPlay).first;	//SHAYAN reverse order
    q = get<2>(moveToPlay).second;  //SHAYAN reverse order
  /*  cout << "S " <<  << " " << x << " " << y << " B " << p << " " << q  ;
      Depends on the search what to select p,q and type of move ;
    cout << "S " <<  << " " << x << " " << y << " M " << p << " " << q  ;*/
    
    //Before our moveT
//    cerr<<"Before\n";
//    st->printBoard(Board);
//    cerr<<st->utility()<<endl;
    
    bool if_move_soldier; //depends on search part.
    if(get<0>(moveToPlay)=='M')
    {
    	if_move_soldier = true;
    	cout << "S " << y << " " << x << " M " << q << " " << p << endl;
    }
    else{
    if_move_soldier = false;
    	cout << "S " << y << " " << x << " B " << q << " " << p << endl;

    }

    for(i=0;i<12;i++)
    {
      if(curr_posB[i].first == x && curr_posB[i].second == y && soldierB[i] == 1)
      {

        break;
      }
    }
    k = i;

    if(if_move_soldier){ // if we move the soldier
      Board[x][y] = 0;
      curr_posB[k].first = p;
      curr_posB[k].second = q;
      for(i=0;i<12;i++)
      {
        if(curr_posA[i].first == p && curr_posA[i].second == q && soldierA[i] == 1)
        {
          soldierA[i] = 0;
          break;
        }
      }
      for(i=0;i<4;i++)
      {
        if(curr_tA[i].first == p && curr_tA[i].second == q && townhallsA[i]==1)
        {
          townhallsA[i] = 0;
          break;
        }
      }
      Board[p][q] = -1;

    }
    else{ // if we use cannon
        for(i=0;i<12;i++)
        {
          if(curr_posA[i].first == p && curr_posA[i].second == q && soldierA[i] == 1)
          {
            soldierA[i] = 0;
            Board[p][q] = 0;
            break;
          }
        }

        for(i=0;i<4;i++)
        {
          if(curr_tA[i].first == p && curr_tA[i].second == q && townhallsA[i] == 1)
          {
            townhallsA[i] = 0;
            Board[p][q] = 0;
            break;
          }
        }

    }
    //Before oppo moveT
//    cerr<<"Before opp\n";
//    st->printBoard(Board);
//    cerr<<st->utility()<<endl;
    
    cin >> a >> y >> x ;	//SHAYAN order reversed
    cin >> b >> q >> p;		//SHAYAN order reversed

    if(b == 'M')
    {
      for(i=0;i<12;i++)
      {
        if(curr_posB[i].first==p&&curr_posB[i].second==q  && soldierB[i] == 1)
        {
          soldierB[i] = 0;
          break;
        }
      }

      for(i=0;i<4;i++)
      {
        if(curr_tB[i].first == p && curr_tB[i].second ==q && townhallsB[i] == 1)
        {
          townhallsB[i] = 0;
          break;
        }
      }

      Board[x][y] = 0 ;

      for(i=0;i<12;i++)
      {
        if(curr_posA[i].first==x&&curr_posA[i].second==y && soldierA[i] == 1)
        {
          break;
        }
      }

      Board[p][q] = 1;
      curr_posA[i].first = p;
      curr_posA[i].second = q;
    }
    else{

      for(i=0;i<12;i++)
      {
        if(curr_posB[i].first==p&&curr_posB[i].second==q && soldierB[i] == 1)
        {
          soldierB[i] = 0;
          break;
        }
      }

      if(i!=12){
      Board[p][q] = 0;
    }
    else{
      for(i=0;i<4;i++)
      {
        if(curr_tB[i].first == p && curr_tB[i].second==q && townhallsB[i] == 1)
        {
          townhallsB[i] = 0;
          break;
        }
      }

      if(i!=4)
      {
        Board[p][q] = 0;
      }
    }

    }


  }

}
else{	//other player first our white
  while(1)
  {

    cin >> a >> y >> x ;	//SHAYAN reverse order
    cin >> b >> q >> p;		//SHAYAN reverse order

    if(b == 'M')
    {
      for(i=0;i<12;i++)
      {
        if(curr_posA[i].first==p&&curr_posA[i].second==q && soldierA[i] == 1)
        {
          soldierA[i] = 0;
          break;
        }
      }

      for(i=0;i<4;i++)
      {
        if(curr_tA[i].first == p && curr_tA[i].second ==q && townhallsA[i] ==1)
        {
          townhallsA[i] = 0;
          break;
        }
      }

      Board[x][y] = 0 ;

      for(i=0;i<12;i++)
      {
        if(curr_posB[i].first==x&&curr_posB[i].second==y  && soldierB[i] == 1)
        {
          break;
        }
      }

      Board[p][q] = -1;
      curr_posB[i].first = p;
      curr_posB[i].second = q;
    }
    else{

      for(i=0;i<12;i++)
      {
        if(curr_posA[i].first==p&&curr_posA[i].second==q && soldierA[i] ==1)
        {
          soldierA[i] = 0;
          break;
        }
      }
      if(i!=12){
      Board[p][q] = 0;
    }
    else{
      for(i=0;i<4;i++)
      {
        if(curr_tA[i].first == p && curr_tA[i].second==q && townhallsA[i] ==1)
        {
          townhallsA[i] = 0;
          break;
        }
      }

      if(i!=4)
      {
        Board[p][q] = 0;
      }
    }

    }


/*---SEARCH---*/

  	st->getBoardS();
    int MyMove = MiniMax(st,DEPTH);
//	st->selectMove(MyMove);	//select move given by minimax
	tuple <char,pair <lld,lld>,pair <lld,lld > >  moveToPlay = st->play(MyMove);

/*------------*/

    // k is the index of the soldier selected ;
     // here 1 is the player number.
    // cuurent location of the selected player
    x = get<1>(moveToPlay).first;
    y = get<1>(moveToPlay).second;

   	 p = get<2>(moveToPlay).first;
    q = get<2>(moveToPlay).second;
  /*  cout << "S " <<  << " " << x << " " << y << " B " << p << " " << q  ;
      Depends on the search what to select p,q and type of move ;
    cout << "S " <<  << " " << x << " " << y << " M " << p << " " << q  ;*/

    bool if_move_soldier; //depends on search part.
    if(get<0>(moveToPlay)=='M')
    {
    	if_move_soldier = true;
    	cout << "S " << y << " " << x << " M " << q << " " << p << endl;
    }
    else{
    if_move_soldier = false;
    	cout << "S " << y << " " << x << " B " << q << " " << p << endl;

    }

    for(i=0;i<12;i++)
    {
      if(curr_posA[i].first == x && curr_posA[i].second == y && soldierA[i] == 1)
      {

        break;
      }
    }
    k = i;

    if(if_move_soldier){ // if we move the soldier
      Board[x][y] = 0;
      curr_posA[k].first = p;
      curr_posA[k].second = q;
      for(i=0;i<12;i++)
      {
        if(curr_posB[i].first == p && curr_posB[i].second == q &&  soldierB[i] == 1 )
        {
          soldierB[i] = 0;
          break;
        }
      }

      for(i=0;i<12;i++)
      {
        if(curr_tB[i].first == p && curr_tB[i].second == q &&  townhallsB[i] == 1 )
        {
          townhallsB[i] = 0;
          break;
        }
      }



      Board[p][q] = 1;

    }
    else{ // if we use cannon
        for(i=0;i<12;i++)
        {
          if(curr_posB[i].first == p && curr_posB[i].second == q  && soldierB[i] ==1)
          {
            soldierB[i] = 0;
            Board[p][q] = 0;
            break;
          }
        }

        if(i!=12){
        Board[p][q] = 0;
      }
      else{
        for(i=0;i<4;i++)
        {
          if(curr_tB[i].first == p && curr_tB[i].second==q && townhallsB[i] ==1)
          {
            townhallsB[i] = 0;
            break;
          }
        }

        if(i!=4)
        {
          Board[p][q] = 0;
        }
      }

    }




  }


}




}
