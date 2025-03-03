#include <iostream>
#include <time.h>
#include <vector>
#include <cmath>
#include "search3.cpp"
using namespace std;

int time_left(float x,float y)
{
  return int(y-x/CLOCKS_PER_SEC)-1;
}

int stoii(string x)
{
  int k = x.length();

  int i , r = 0;
  for(i=k-1;i>=0;i--)
  {
  
    r = r + pow(10,i)*(x[k-i-1]-'0');
  }

  return r;
}

int main(int argc, char** argv){

  int m,n,player_id,timee;	//for input
	//int turn;	//0 or 1
//  cin >> player_id >> m >> n >> time;	//first line input##s
	player_id=stoii(argv[1]);
	m = stoii(argv[2]);
	n = stoii(argv[3]);
	timee = stoii(argv[4]);

  clock_t tStart = clock();
  //player_id=1;m=8;n=8;time=90;
	PLAYER_ID = player_id;
  char a,b;
  lld x,y,p,q,i,j,k;
  int prev_x,prev_y;
  prev_x = -1;
  prev_y = -1;
  char move_type = 'B';
  //cerr << " Ready for intialization\n";
  intialize_board();
  //cerr << "BOard Intiaized\n";
  State *st = new State(Board);
//  st->getBoardS();

  if(player_id == 1){
  //BLACK
  while(1){

/*SEARCH*/
  	st->getBoardS();
  	if(time_left(clock(),timee)<5)
  	{
  		LESS = true;
  	}
    int MyMove = MiniMax(st,DEPTH);

	// st->selectMove(MyMove);	//select move given by minimax

	tuple <char,pair <lld,lld>,pair <lld,lld > >  moveToPlay = st->play(MyMove);

  // if(prev_x == get<2>(moveToPlay).first && prev_y == get<2>(moveToPlay).second && move_type == get<0>(moveToPlay) )
  // {
  //   vector < tuple <char,pair <lld,lld>,pair <lld,lld > > >  every_move = all_valid_moves_on_board(curr_posA,curr_posB,soldierB,soldierA,townhallsB,townhallsA,2);
  //   srand(time(0));
  //   // int flag = 0;
  //   lld len = every_move.size();
  //   int random = rand()%len;
  //   int pivot = 0;
  //   moveToPlay = every_move[random];
  //   while(check_kills_ownplayer(get<2>(moveToPlay).first,get<2>(moveToPlay).second,2,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB))
  //   {
  //     random = (pivot + rand())%len;
  //     moveToPlay = every_move[random];
  //     cerr << "Checking  "  << random << endl;
  //     pivot = (pivot + 1)%len;
  //   }
  //
  // }

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
    prev_x = p;
    prev_y = q;
    move_type = get<0>(moveToPlay);

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

    for(i=0;i<15;i++)
    {
      if(curr_posB[i].first == x && curr_posB[i].second == y && soldierB[i] == 1)
      {

        break;
      }
    }
    k = i;

    // if(p==0&&q==0)
    // {
    //   vector <pair <lld,lld>> pytorch = can_player_be_killed(2,k,curr_posA,curr_posB,soldierB,soldierA,townhallsB,townhallsA);
    //   cerr << k << endl;
    //   for(int de = 0;de < pytorch.size();de++)
    //   {
    //     cerr << pytorch[de].second << "," << pytorch[de].first << endl;
    //   }
    // }

    if(if_move_soldier){ // if we move the soldier
      Board[x][y] = 0;
      curr_posB[k].first = p;
      curr_posB[k].second = q;
      for(i=0;i<15;i++)
      {
        if(curr_posA[i].first == p && curr_posA[i].second == q && soldierA[i] == 1)
        {
          soldierA[i] = 0;
          break;
        }
      }
      for(i=0;i<5;i++)
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
        for(i=0;i<15;i++)
        {
          if(curr_posA[i].first == p && curr_posA[i].second == q && soldierA[i] == 1)
          {
            soldierA[i] = 0;
            Board[p][q] = 0;
            break;
          }
        }

        for(i=0;i<5;i++)
        {
          if(curr_tA[i].first == p && curr_tA[i].second == q && townhallsA[i] == 1)
          {
            townhallsA[i] = 0;
            Board[p][q] = 0;
            break;
          }
        }

    }


    cin >> a >> y >> x ;	//SHAYAN order reversed
    cin >> b >> q >> p;		//SHAYAN order reversed

    if(b == 'M')
    {
      for(i=0;i<15;i++)
      {
        if(curr_posB[i].first==p&&curr_posB[i].second==q  && soldierB[i] == 1)
        {
          soldierB[i] = 0;
          break;
        }
      }

      for(i=0;i<5;i++)
      {
        if(curr_tB[i].first == p && curr_tB[i].second ==q && townhallsB[i] == 1)
        {
          townhallsB[i] = 0;
          break;
        }
      }

      Board[x][y] = 0 ;

      for(i=0;i<15;i++)
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

      for(i=0;i<15;i++)
      {
        if(curr_posB[i].first==p&&curr_posB[i].second==q && soldierB[i] == 1)
        {
          soldierB[i] = 0;
          break;
        }
      }

      if(i!=15){
      Board[p][q] = 0;
    }
    else{
      for(i=0;i<5;i++)
      {
        if(curr_tB[i].first == p && curr_tB[i].second==q && townhallsB[i] == 1)
        {
          townhallsB[i] = 0;
          break;
        }
      }

      if(i!=5)
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
      for(i=0;i<15;i++)
      {
        if(curr_posA[i].first==p&&curr_posA[i].second==q && soldierA[i] == 1)
        {
          soldierA[i] = 0;
          break;
        }
      }

      for(i=0;i<5;i++)
      {
        if(curr_tA[i].first == p && curr_tA[i].second ==q && townhallsA[i] ==1)
        {
          townhallsA[i] = 0;
          break;
        }
      }

      Board[x][y] = 0 ;

      for(i=0;i<15;i++)
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

      for(i=0;i<15;i++)
      {
        if(curr_posA[i].first==p&&curr_posA[i].second==q && soldierA[i] ==1)
        {
          soldierA[i] = 0;
          break;
        }
      }
      if(i!=15){
      Board[p][q] = 0;
    }
    else{
      for(i=0;i<5;i++)
      {
        if(curr_tA[i].first == p && curr_tA[i].second==q && townhallsA[i] ==1)
        {
          townhallsA[i] = 0;
          break;
        }
      }

      if(i!=5)
      {
        Board[p][q] = 0;
      }
    }

    }


/*-------Search-----*/
  	st->getBoardS();
  	if(time_left(clock(),timee)<5)
  	{
  		LESS = true;
  	}
	int MyMove = MiniMax(st,DEPTH);	//select move given by minimax
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

    for(i=0;i<15;i++)
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
      for(i=0;i<15;i++)
      {
        if(curr_posB[i].first == p && curr_posB[i].second == q &&  soldierB[i] == 1 )
        {
          soldierB[i] = 0;
          break;
        }
      }

      for(i=0;i<15;i++)
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
        for(i=0;i<15;i++)
        {
          if(curr_posB[i].first == p && curr_posB[i].second == q  && soldierB[i] ==1)
          {
            soldierB[i] = 0;
            Board[p][q] = 0;
            break;
          }
        }

        if(i!=15){
        Board[p][q] = 0;
      }
      else{
        for(i=0;i<5;i++)
        {
          if(curr_tB[i].first == p && curr_tB[i].second==q && townhallsB[i] ==1)
          {
            townhallsB[i] = 0;
            break;
          }
        }

        if(i!=5)
        {
          Board[p][q] = 0;
        }
      }

    }




  }


}




}

