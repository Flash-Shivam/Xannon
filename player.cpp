#include <iostream>
#include <time.h>
#include <vector>
#include<tuple>
using namespace std;
#define lld int

vector<vector<int> > Board;
lld soldierA[12],soldierB[12],townhallsA[4],townhallsB[4]; // value is 0 if dead else 1.
pair <lld,lld> curr_posA[12],curr_posB[12],curr_tA[4],curr_tB[4];  //stores location of the soldiers
lld p = 0;
/* Function Prototypes */
vector <pair <lld,lld> >  cannon_movement(lld player_number,lld soldier_selected,pair <lld,lld> curr_posB[],pair <lld,lld> curr_posA[],lld soldierB[],lld soldierA[]);
/*END Funciton prototypes*/
void intialize_board(){
  lld i,j,k;
	Board.resize(8);
	for(int i=0;i<8;i++)
		Board[i].resize(8);

  for(k=0;k<4;k++)
  {

    townhallsA[k] = 1;
    townhallsB[k] = 1;
  }

  for(k=0;k<12;k++)
  {

    soldierA[k] =1;
    soldierB[k] = 1;
  }

  lld x=0,y=0;

  for(i=0;i<8;i++)
  {
    if(i%2==0)
    {
      Board[0][i] = 2;  // represents townhall A
      curr_tA[x].first = 0;
      curr_tA[x].second = i;
      x++;
    }
    else{
      Board[0][i] = 1;  // represents soldier A
      curr_posA[y].first = 0;
      curr_posA[y].second = i;
      y++;
    }
  }

  for(j=1;j<=2;j++)
  {
    for(i=0;i<8;i++)
    {
      if(i%2==1)
      {
        Board[j][i] = 1;  // represents soldier A
        curr_posA[y].first = j;
        curr_posA[y].second = i;
        y++;
      }
      else{
        Board[j][i] = 0;
      }
    }
  }
x=0;
y=0;
  for(i=0;i<8;i++)
  {
    if(i%2==0)
    {
      Board[7][i] = -1;  // represents soldier B
      curr_posB[y].first = 7;
      curr_posB[y].second = i;
      y++;
    }
    else{
      Board[7][i] = -2;  // represents townhall B
      curr_tB[x].first = 7;
      curr_tB[x].second = i;
      x++;
    }
  }

  for(j=5;j<=6;j++)
  {
    for(i=0;i<8;i++)
    {
      if(i%2==1)
      {
        Board[j][i] = 0;
      }
      else{
        Board[j][i] = -1;  // represents soldier B
        curr_posB[y].first = j;
        curr_posB[y].second = i;
        y++;
      }
    }
  }


}

vector<vector<int> > getBoard(){
	return Board;
}

int getM(){
	return 8;
}
int getN(){
	return 8;
}
// player_number = 1 if A player
// selects a random player among all the valid soldiers
lld selectSoldier(lld player_number, lld soldierA[],lld soldierB[])
{
  vector <lld> valid_soldier;
  if(player_number == 1)
  {
    lld i,j,k;
    for(i=0;i<12;i++)
    {
        if(soldierA[i]==1)
        {
          valid_soldier.push_back(i);
        }

    }
    srand(time(0));
    j = rand();
     k = valid_soldier.size();
     j = j % k;

     return j;

  }
  else{

    lld i,j,k;
    for(i=0;i<12;i++)
    {
        if(soldierB[i]==1)
        {
          valid_soldier.push_back(i);
        }

    }
    srand(time(0));
    j = rand();
     k = valid_soldier.size();
     j = j % k;

     return j;


  }


}

// takes input of which player's turn and which soldier is selected.
// returns the targets which can be attacked by the soldier selected.
vector <pair<lld ,lld >> can_player_be_killed(lld player_number,lld soldier_selected, pair <lld,lld> curr_posA[],pair <lld,lld> curr_posB[],lld soldierB[],lld soldierA[],lld townhallsB[],lld townhallsA[]){
  vector <pair <lld,lld>> loc_can_kill;
  if(player_number==1)
  {
    if(soldierA[soldier_selected]==1){
    lld x = curr_posA[soldier_selected].first;
    lld y = curr_posA[soldier_selected].second;

  //  //        cerr << "player coordinates\n";
  //  //        cerr << x <<  " " << y << endl;
  //  //        cerr << "Other target coordinates\n";
      lld i,j,k;
      for(i=0;i<12;i++)
      {
         if(soldierB[i]==1)
         {
           pair <lld,lld> xx;
            xx.first = curr_posB[i].first;
            j = xx.first;

            xx.second = curr_posB[i].second;
            k = xx.second;
            if((j==x&&k==y-1)||(j==x&&k==y+1)||(j==x+1&&k==y-1)||(j==x+1&&k==y)||(j==x+1&&k==y+1)){
              loc_can_kill.push_back(xx);
            //  //        cerr << xx.first << " " << xx.second << endl;
            }

         }
      }
    //  //        cerr <<"Other target townhallB coordinates\n";
      for(i=0;i<4;i++)
      {
        if(townhallsB[i]==1){
          pair <lld,lld> xx;
          xx.first = curr_tB[i].first;
          j = xx.first;
          xx.second = curr_tB[i].second;
          k = xx.second;

          if((j==x&&k==y-1)||(j==x&&k==y+1)||(j==x+1&&k==y-1)||(j==x+1&&k==y)||(j==x+1&&k==y+1)){
            loc_can_kill.push_back(xx);
      //      //        cerr << xx.first << " " << xx.second << "... " <<endl;
          }

        }
      }
    //  //        cerr << "done" << endl;
    }
  }
  else{
    if(soldierB[soldier_selected]==1){


    lld x = curr_posB[soldier_selected].first;
    lld y = curr_posB[soldier_selected].second;

//    //        cerr << "playerA attack coordinates\n";
    //        cerr << x <<  " " << y << endl;
  //  //        cerr << "Other target coordinates\n";
      lld i,j,k;
      for(i=0;i<12;i++)
      {
         if(soldierA[i]==1)
         {
      //     //        cerr << i << " " ;
           pair <lld,lld> xx;
            xx.first = curr_posA[i].first;
            j = xx.first;

            xx.second = curr_posA[i].second;
            k = xx.second;
            if((j==x&&k==y-1)||(j==x&&k==y+1)||(j==x-1&&k==y-1)||(j==x-1&&k==y)||(j==x-1&&k==y+1)){
              loc_can_kill.push_back(xx);
   //          //        cerr << xx.first << " " << xx.second << endl;
            }

         }
      }
    //  //        cerr << "Other target townhallA coordinates\n";
      for(i=0;i<4;i++)
      {
        if(townhallsA[i]==1){
          pair <lld,lld> xx;
          xx.first = curr_tA[i].first;
          j = xx.first;
          xx.second = curr_tA[i].second;
          k = xx.second;

          if((j==x&&k==y-1)||(j==x&&k==y+1)||(j==x-1&&k==y-1)||(j==x-1&&k==y)||(j==x-1&&k==y+1)){
            loc_can_kill.push_back(xx);
           //        cerr << xx.first << " " << xx.second <<" ;;;;;" << endl;
          }

        }
      }
    //  //        cerr << "done" << endl;
    }

  }

  return loc_can_kill;

}

bool check_kills_ownplayer2(lld x,lld y,lld player_number,pair <lld,lld> curr_posB[],pair<lld,lld> curr_posA[],lld soldierB[],lld soldierA[],pair <lld,lld> curr_tA[],pair <lld,lld> curr_tB[],lld townhallsA[],lld townhallsB[]){
  lld i,j=0,k=0;
  for(i=0;i<12;i++)
  {
    if(curr_posA[i].first == x&& curr_posA[i].second == y && soldierA[i] ==1)
    {
      k=1;
    }
  }

  for(i=0;i<12;i++)
  {
    if(curr_posB[i].first == x&& curr_posB[i].second == y && soldierB[i] ==1)
    {
      k=1;
    }
  }

  for(i=0;i<4;i++)
  {
    if(curr_tA[i].first == x&& curr_tA[i].second == y && townhallsA[i] ==1)
    {
      k=1;
    }
  }

  for(i=0;i<4;i++)
  {
    if(curr_tB[i].first == x&& curr_tB[i].second == y && townhallsB[i] ==1)
    {
      k=1;
    }
  }

  if(k==0)
  {
    return true;
  }

  return false;

}


bool check_kills_townhall(lld x,lld y,lld player_number,pair <lld,lld> curr_posB[],pair<lld,lld> curr_posA[],lld soldierB[],lld soldierA[],pair <lld,lld> curr_tA[],pair <lld,lld> curr_tB[],lld townhallsA[],lld townhallsB[]){
  lld i,j,k;
  if(player_number==1){
  for(i=0;i<4;i++)
  {
    if(curr_tA[i].first == x&& curr_tA[i].second == y && townhallsA[i] ==1)
    {
      break;
    }
  }

  if(i==4)
  {
    return true;
  }
  else{
    return false;
  }
}
else{
  for(i=0;i<4;i++)
  {
    if(curr_tB[i].first == x&& curr_tB[i].second == y && townhallsB[i] ==1)
    {
      break;
    }
  }

  if(i==4)
  {
    return true;
  }
  else{
    return false;
  }

}


}

bool check_kills_ownplayer1(lld x,lld y,lld player_number,pair <lld,lld> curr_posB[],pair<lld,lld> curr_posA[],lld soldierB[],lld soldierA[],pair <lld,lld> curr_tA[],pair <lld,lld> curr_tB[],lld townhallsA[],lld townhallsB[]){
  lld i,j,k;
  if(player_number==1){
  for(i=0;i<12;i++)
  {
    if(curr_posA[i].first == x&& curr_posA[i].second == y && soldierA[i] ==1)
    {
      break;
    }
  }

  if(i==12)
  {
    return true;
  }
  else{
    return false;
  }
}
else{
  for(i=0;i<12;i++)
  {
    if(curr_posB[i].first == x&& curr_posB[i].second == y && soldierB[i] ==1)
    {
      break;
    }
  }

  if(i==12)
  {
    return true;
  }
  else{
    return false;
  }

}


}

//return true if cant be killed by it's own player
bool check_kills_ownplayer(lld x,lld y,lld player_number,pair <lld,lld> curr_posB[],pair<lld,lld> curr_posA[],lld soldierB[],lld soldierA[],pair <lld,lld> curr_tA[],pair <lld,lld> curr_tB[],lld townhallsA[],lld townhallsB[])
{
  lld i,j,k;
  if(player_number==1){
  for(i=0;i<12;i++)
  {
    if(curr_posA[i].first == x&& curr_posA[i].second == y && soldierA[i] ==1)
    {
      break;
    }
  }

  if(i==12)
  {
    for(j=0;j<4;j++)
    {
      if(curr_tA[j].first == x&& curr_tA[j].second == y && townhallsA[j] ==1)
      {
        break;
      }
    }
    if(j==4){
      return true;
    }
    return false;
  }
  else{
    return false;
  }
}
else{
  for(i=0;i<12;i++)
  {
    if(curr_posB[i].first == x&& curr_posB[i].second == y && soldierB[i] ==1)
    {
      break;
    }
  }

  if(i==12)
  {
    for(j=0;j<4;j++)
    {
      if(curr_tB[j].first == x&& curr_tB[j].second == y && townhallsB[j] ==1)
      {
        break;
      }
    }
    if(j==4){
      return true;
    }
    return false;
  }
  else{
    return false;
  }

}

}

// takes input of which player's turn and which soldier is selected
// returns the targets which can be attacked by all the possible cannons which has the selected soldier as a member
vector <pair <lld,lld> > is_Cannon_formed(lld player_number,lld soldier_selected,pair <lld,lld> curr_posB[],pair <lld,lld> curr_posA[],lld soldierB[],lld soldierA[])
{
  vector <pair <lld,lld>> can_be_killed;
  if(player_number==1)
  {
    if(soldierA[soldier_selected]==1){
    lld x = curr_posA[soldier_selected].first;
    lld y = curr_posA[soldier_selected].second;
    lld i,j,k,p,q,e,f,a,b;
    j = x-2;
    k = y;
    p = x-1;
    q = y;
    if(0<=j&&j<8&&0<=p&&p<8&&0<=q&&q<8&&k<8&&0<=k&&!check_kills_ownplayer1(j,k,1,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB)&&!check_kills_ownplayer1(p,q,1,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB)){

          j = x-5; k = y;
          p = x-4; q = y;
          e = x+2; f = y;
          a = x+3; b = y;



          if(0<=j&&j<8&&k<8&&0<=k&&check_kills_ownplayer2(x-3,y,1,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB)&&check_kills_ownplayer(j,k,1,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB))
          {
            pair <lld,lld> xx ;
            xx.first = j;
            xx.second = k;
            can_be_killed.push_back(xx);
          }
          if(0<=e&&e<8&&f<8&&0<=f&&check_kills_ownplayer2(x+1,y,1,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB)&&check_kills_ownplayer(e,f,1,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB))
          {
            pair <lld,lld> xx ;
            xx.first = e;
            xx.second = f;
            can_be_killed.push_back(xx);
          }
          if(0<=p&&p<8&&q<8&&0<=q&&check_kills_ownplayer2(x-3,y,1,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB)&&check_kills_ownplayer(p,q,1,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB))
          {
            pair <lld,lld> xx ;
            xx.first = p;
            xx.second = q;
            can_be_killed.push_back(xx);
          }
          if(0<=a&&a<8&&b<8&&0<=b&&check_kills_ownplayer2(x+1,y,1,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB)&&check_kills_ownplayer(a,b,1,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB))
          {
            pair <lld,lld> xx ;
            xx.first = a;
            xx.second = b;
            can_be_killed.push_back(xx);
          }

    }

      j = x-1;
      k = y;
      p = x+1;
      q = y;
      if(0<=j&&j<8&&0<=p&&p<8&&0<=q&&q<8&&k<8&&0<=k&&!check_kills_ownplayer1(j,k,1,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB)&&!check_kills_ownplayer1(p,q,1,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB)){

            j = x-3; k = y;
            p = x-4; q = y;
            e = x+4; f = y;
            a = x+3; b = y;
            if(0<=j&&j<8&&k<8&&0<=k&&check_kills_ownplayer2(x-2,y,1,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB)&&check_kills_ownplayer(j,k,1,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB))
            {
              pair <lld,lld> xx ;
              xx.first = j;
              xx.second = k;
              can_be_killed.push_back(xx);
            }
            if(0<=e&&e<8&&f<8&&0<=f&&check_kills_ownplayer2(x+2,y,1,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB)&&check_kills_ownplayer(e,f,1,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB))
            {
              pair <lld,lld> xx ;
              xx.first = e;
              xx.second = f;
              can_be_killed.push_back(xx);
            }
            if(0<=p&&p<8&&q<8&&0<=q&&check_kills_ownplayer2(x-2,y,1,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB)&&check_kills_ownplayer(p,q,1,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB))
            {
              pair <lld,lld> xx ;
              xx.first = p;
              xx.second = q;
              can_be_killed.push_back(xx);
            }
            if(0<=a&&a<8&&b<8&&0<=b&&check_kills_ownplayer2(x+2,y,1,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB)&&check_kills_ownplayer(a,b,1,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB))
            {
              pair <lld,lld> xx ;
              xx.first = a;
              xx.second = b;
              can_be_killed.push_back(xx);
            }



    }

    j = x+2;
    k = y;
    p = x+1;
    q = y;
    if(0<=j&&j<8&&0<=p&&p<8&&0<=q&&q<8&&k<8&&0<=k&&!check_kills_ownplayer1(j,k,1,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB)&&!check_kills_ownplayer1(p,q,1,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB)){

          j = x-3; k = y;
          p = x-2; q = y;
          e = x+4; f = y;
          a = x+5; b = y;
          if(0<=j&&j<8&&k<8&&0<=k&&check_kills_ownplayer2(x-1,y,1,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB)&&check_kills_ownplayer(j,k,1,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB))
          {
            pair <lld,lld> xx ;
            xx.first = j;
            xx.second = k;
            can_be_killed.push_back(xx);
          }
          if(0<=e&&e<8&&f<8&&0<=f&&check_kills_ownplayer2(x+3,y,1,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB)&&check_kills_ownplayer(e,f,1,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB))
          {
            pair <lld,lld> xx ;
            xx.first = e;
            xx.second = f;
            can_be_killed.push_back(xx);
          }
          if(0<=p&&p<8&&q<8&&0<=q&&check_kills_ownplayer2(x-1,y,1,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB)&&check_kills_ownplayer(p,q,1,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB))
          {
            pair <lld,lld> xx ;
            xx.first = p;
            xx.second = q;
            can_be_killed.push_back(xx);
          }
          if(0<=a&&a<8&&b<8&&0<=b&&check_kills_ownplayer2(x+3,y,1,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB)&&check_kills_ownplayer(a,b,1,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB))
          {
            pair <lld,lld> xx ;
            xx.first = a;
            xx.second = b;
            can_be_killed.push_back(xx);
          }



  }

  j = x;
  k = y-1;
  p = x;
  q = y+1;
  if(0<=j&&j<8&&0<=p&&p<8&&0<=q&&q<8&&k<8&&0<=k&&!check_kills_ownplayer1(j,k,1,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB)&&!check_kills_ownplayer1(p,q,1,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB)){

        j = x; k = y-4;
        p = x; q = y-3;
        e = x; f = y+4;
        a = x; b = y+3;
        if(0<=j&&j<8&&k<8&&0<=k&&check_kills_ownplayer2(x,y-2,1,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB)&&check_kills_ownplayer(j,k,1,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB))
        {
          pair <lld,lld> xx ;
          xx.first = j;
          xx.second = k;
          can_be_killed.push_back(xx);
        }
        if(0<=e&&e<8&&f<8&&0<=f&&check_kills_ownplayer2(x,y+2,1,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB)&&check_kills_ownplayer(e,f,1,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB))
        {
          pair <lld,lld> xx ;
          xx.first = e;
          xx.second = f;
          can_be_killed.push_back(xx);
        }
        if(0<=p&&p<8&&q<8&&0<=q&&check_kills_ownplayer2(x,y-2,1,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB)&&check_kills_ownplayer(p,q,1,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB))
        {
          pair <lld,lld> xx ;
          xx.first = p;
          xx.second = q;
          can_be_killed.push_back(xx);
        }
        if(0<=a&&a<8&&b<8&&0<=b&&check_kills_ownplayer2(x,y+2,1,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB)&&check_kills_ownplayer(a,b,1,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB))
        {
          pair <lld,lld> xx ;
          xx.first = a;
          xx.second = b;
          can_be_killed.push_back(xx);
        }


}

j = x;
k = y-1;
p = x;
q = y-2;
if(0<=j&&j<8&&0<=p&&p<8&&0<=q&&q<8&&k<8&&0<=k&&!check_kills_ownplayer1(j,k,1,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB)&&!check_kills_ownplayer1(p,q,1,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB)){

      j = x; k = y-4;
      p = x; q = y-5;
      e = x; f = y+2;
      a = x; b = y+3;
      if(0<=j&&j<8&&k<8&&0<=k&&check_kills_ownplayer2(x,y-3,1,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB)&&check_kills_ownplayer(j,k,1,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB))
      {
        pair <lld,lld> xx ;
        xx.first = j;
        xx.second = k;
        can_be_killed.push_back(xx);
      }
      if(0<=e&&e<8&&f<8&&0<=f&&check_kills_ownplayer2(x,y+1,1,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB)&&check_kills_ownplayer(e,f,1,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB))
      {
        pair <lld,lld> xx ;
        xx.first = e;
        xx.second = f;
        can_be_killed.push_back(xx);
      }
      if(0<=p&&p<8&&q<8&&0<=q&&check_kills_ownplayer2(x,y-3,1,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB)&&check_kills_ownplayer(p,q,1,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB))
      {
        pair <lld,lld> xx ;
        xx.first = p;
        xx.second = q;
        can_be_killed.push_back(xx);
      }
      if(0<=a&&a<8&&b<8&&0<=b&&check_kills_ownplayer2(x,y+1,1,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB)&&check_kills_ownplayer(a,b,1,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB))
      {
        pair <lld,lld> xx ;
        xx.first = a;
        xx.second = b;
        can_be_killed.push_back(xx);
      }


}

j = x;
k = y+1;
p = x;
q = y+2;
if(0<=j&&j<8&&0<=p&&p<8&&0<=q&&q<8&&k<8&&0<=k&&!check_kills_ownplayer1(j,k,1,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB)&&!check_kills_ownplayer1(p,q,1,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB)){

      j = x; k = y-3;
      p = x; q = y-2;
      e = x; f = y+4;
      a = x; b = y+5;
      if(0<=j&&j<8&&k<8&&0<=k&&check_kills_ownplayer2(x,y-1,1,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB)&&check_kills_ownplayer(j,k,1,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB))
      {
        pair <lld,lld> xx ;
        xx.first = j;
        xx.second = k;
        can_be_killed.push_back(xx);
      }
      if(0<=e&&e<8&&f<8&&0<=f&&check_kills_ownplayer2(x,y+3,1,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB)&&check_kills_ownplayer(e,f,1,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB))
      {
        pair <lld,lld> xx ;
        xx.first = e;
        xx.second = f;
        can_be_killed.push_back(xx);
      }
      if(0<=p&&p<8&&q<8&&0<=q&&check_kills_ownplayer2(x,y-1,1,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB)&&check_kills_ownplayer(p,q,1,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB))
      {
        pair <lld,lld> xx ;
        xx.first = p;
        xx.second = q;
        can_be_killed.push_back(xx);
      }
      if(0<=a&&a<8&&b<8&&0<=b&&check_kills_ownplayer2(x,y+3,1,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB)&&check_kills_ownplayer(a,b,1,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB))
      {
        pair <lld,lld> xx ;
        xx.first = a;
        xx.second = b;
        can_be_killed.push_back(xx);
      }


}

j = x-1;
k = y+1;
p = x+1;
q = y-1;
if(0<=j&&j<8&&0<=p&&p<8&&0<=q&&q<8&&k<8&&0<=k&&!check_kills_ownplayer1(j,k,1,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB)&&!check_kills_ownplayer1(p,q,1,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB)){

      j = x-3; k = y+3;
      p = x-4; q = y+4;
      e = x+3; f = y-3;
      a = x+4; b = y-4;
      if(0<=j&&j<8&&k<8&&0<=k&&check_kills_ownplayer2(x-2,y+2,1,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB)&&check_kills_ownplayer(j,k,1,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB))
      {
        pair <lld,lld> xx ;
        xx.first = j;
        xx.second = k;
        can_be_killed.push_back(xx);
      }
      if(0<=e&&e<8&&f<8&&0<=f&&check_kills_ownplayer2(x+2,y-2,1,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB)&&check_kills_ownplayer(e,f,1,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB))
      {
        pair <lld,lld> xx ;
        xx.first = e;
        xx.second = f;
        can_be_killed.push_back(xx);
      }
      if(0<=p&&p<8&&q<8&&0<=q&&check_kills_ownplayer2(x-2,y+2,1,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB)&&check_kills_ownplayer(p,q,1,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB))
      {
        pair <lld,lld> xx ;
        xx.first = p;
        xx.second = q;
        can_be_killed.push_back(xx);
      }
      if(0<=a&&a<8&&b<8&&0<=b&&check_kills_ownplayer2(x+2,y-2,1,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB)&&check_kills_ownplayer(a,b,1,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB))
      {
        pair <lld,lld> xx ;
        xx.first = a;
        xx.second = b;
        can_be_killed.push_back(xx);
      }


}

j = x+1;
k = y-1;
p = x+2;
q = y-2;
if(0<=j&&j<8&&0<=p&&p<8&&0<=q&&q<8&&k<8&&0<=k&&!check_kills_ownplayer1(j,k,1,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB)&&!check_kills_ownplayer1(p,q,1,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB)){

      j = x-3; k = y+3;
      p = x-2; q = y+2;
      e = x+4; f = y-4;
      a = x+5; b = y-5;
      if(0<=j&&j<8&&k<8&&0<=k&&check_kills_ownplayer2(x-1,y+1,1,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB)&&check_kills_ownplayer(j,k,1,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB))
      {
        pair <lld,lld> xx ;
        xx.first = j;
        xx.second = k;
        can_be_killed.push_back(xx);
      }
      if(0<=e&&e<8&&f<8&&0<=f&&check_kills_ownplayer2(x+3,y-3,1,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB)&&check_kills_ownplayer(e,f,1,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB))
      {
        pair <lld,lld> xx ;
        xx.first = e;
        xx.second = f;
        can_be_killed.push_back(xx);
      }
      if(0<=p&&p<8&&q<8&&0<=q&&check_kills_ownplayer2(x-1,y+1,1,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB)&&check_kills_ownplayer(p,q,1,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB))
      {
        pair <lld,lld> xx ;
        xx.first = p;
        xx.second = q;
        can_be_killed.push_back(xx);
      }
      if(0<=a&&a<8&&b<8&&0<=b&&check_kills_ownplayer2(x+3,y-3,1,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB)&&check_kills_ownplayer(a,b,1,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB))
      {
        pair <lld,lld> xx ;
        xx.first = a;
        xx.second = b;
        can_be_killed.push_back(xx);
      }


}

j = x-2;
k = y+2;
p = x-1;
q = y+1;
if(0<=j&&j<8&&0<=p&&p<8&&0<=q&&q<8&&k<8&&0<=k&&!check_kills_ownplayer1(j,k,1,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB)&&!check_kills_ownplayer1(p,q,1,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB)){

      j = x+2; k = y-2;
      p = x+3; q = y-3;
      e = x-4; f = y+4;
      a = x-5; b = y+5;
      if(0<=j&&j<8&&k<8&&0<=k&&check_kills_ownplayer2(x+1,y-1,1,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB)&&check_kills_ownplayer(j,k,1,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB))
      {
        pair <lld,lld> xx ;
        xx.first = j;
        xx.second = k;
        can_be_killed.push_back(xx);
      }
      if(0<=e&&e<8&&f<8&&0<=f&&check_kills_ownplayer2(x-3,y+3,1,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB)&&check_kills_ownplayer(e,f,1,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB))
      {
        pair <lld,lld> xx ;
        xx.first = e;
        xx.second = f;
        can_be_killed.push_back(xx);
      }
      if(0<=p&&p<8&&q<8&&0<=q&&check_kills_ownplayer2(x+1,y-1,1,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB)&&check_kills_ownplayer(p,q,1,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB))
      {
        pair <lld,lld> xx ;
        xx.first = p;
        xx.second = q;
        can_be_killed.push_back(xx);
      }
      if(0<=a&&a<8&&b<8&&0<=b&&check_kills_ownplayer2(x-3,y+3,1,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB)&&check_kills_ownplayer(a,b,1,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB))
      {
        pair <lld,lld> xx ;
        xx.first = a;
        xx.second = b;
        can_be_killed.push_back(xx);
      }


}

j = x+1;
k = y+1;
p = x+2;
q = y+2;
if(0<=j&&j<8&&0<=p&&p<8&&0<=q&&q<8&&k<8&&0<=k&&!check_kills_ownplayer1(j,k,1,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB)&&!check_kills_ownplayer1(p,q,1,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB)){

      j = x-2; k = y-2;
      p = x-3; q = y-3;
      e = x+4; f = y+4;
      a = x+5; b = y+5;
      if(0<=j&&j<8&&k<8&&0<=k&&check_kills_ownplayer2(x-1,y-1,1,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB)&&check_kills_ownplayer(j,k,1,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB))
      {
        pair <lld,lld> xx ;
        xx.first = j;
        xx.second = k;
        can_be_killed.push_back(xx);
      }
      if(0<=e&&e<8&&f<8&&0<=f&&check_kills_ownplayer2(x+3,y+3,1,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB)&&check_kills_ownplayer(e,f,1,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB))
      {
        pair <lld,lld> xx ;
        xx.first = e;
        xx.second = f;
        can_be_killed.push_back(xx);
      }
      if(0<=p&&p<8&&q<8&&0<=q&&check_kills_ownplayer2(x-1,y-1,1,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB)&&check_kills_ownplayer(p,q,1,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB))
      {
        pair <lld,lld> xx ;
        xx.first = p;
        xx.second = q;
        can_be_killed.push_back(xx);
      }
      if(0<=a&&a<8&&b<8&&0<=b&&check_kills_ownplayer2(x+3,y+3,1,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB)&&check_kills_ownplayer(a,b,1,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB))
      {
        pair <lld,lld> xx ;
        xx.first = a;
        xx.second = b;
        can_be_killed.push_back(xx);
      }


}

j = x+1;
k = y+1;
p = x-1;
q = y-1;
if(0<=j&&j<8&&0<=p&&p<8&&0<=q&&q<8&&k<8&&0<=k&&!check_kills_ownplayer1(j,k,1,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB)&&!check_kills_ownplayer1(p,q,1,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB)){

      j = x+3; k = y+3;
      p = x+4; q = y+4;
      e = x-3; f = y-3;
      a = x-4; b = y-4;
      if(0<=j&&j<8&&k<8&&0<=k&&check_kills_ownplayer2(x+2,y+2,1,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB)&&check_kills_ownplayer(j,k,1,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB))
      {
        pair <lld,lld> xx ;
        xx.first = j;
        xx.second = k;
        can_be_killed.push_back(xx);
      }
      if(0<=e&&e<8&&f<8&&0<=f&&check_kills_ownplayer2(x-2,y-2,1,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB)&&check_kills_ownplayer(e,f,1,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB))
      {
        pair <lld,lld> xx ;
        xx.first = e;
        xx.second = f;
        can_be_killed.push_back(xx);
      }
      if(0<=p&&p<8&&q<8&&0<=q&&check_kills_ownplayer2(x+2,y+2,1,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB)&&check_kills_ownplayer(p,q,1,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB))
      {
        pair <lld,lld> xx ;
        xx.first = p;
        xx.second = q;
        can_be_killed.push_back(xx);
      }
      if(0<=a&&a<8&&b<8&&0<=b&&check_kills_ownplayer2(x-2,y-2,1,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB)&&check_kills_ownplayer(a,b,1,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB))
      {
        pair <lld,lld> xx ;
        xx.first = a;
        xx.second = b;
        can_be_killed.push_back(xx);
      }


}

j = x-2;
k = y-2;
p = x-1;
q = y-1;
if(0<=j&&j<8&&0<=p&&p<8&&0<=q&&q<8&&k<8&&0<=k&&!check_kills_ownplayer1(j,k,1,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB)&&!check_kills_ownplayer1(p,q,1,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB)){

      j = x-4; k = y-4;
      p = x-5; q = y-5;
      e = x+2; f = y+2;
      a = x+3; b = y+3;
      if(0<=j&&j<8&&k<8&&0<=k&&check_kills_ownplayer2(x-3,y-3,1,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB)&&check_kills_ownplayer(j,k,1,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB))
      {
        pair <lld,lld> xx ;
        xx.first = j;
        xx.second = k;
        can_be_killed.push_back(xx);
      }
      if(0<=e&&e<8&&f<8&&0<=f&&check_kills_ownplayer2(x+1,y+1,1,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB)&&check_kills_ownplayer(e,f,1,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB))
      {
        pair <lld,lld> xx ;
        xx.first = e;
        xx.second = f;
        can_be_killed.push_back(xx);
      }
      if(0<=p&&p<8&&q<8&&0<=q&&check_kills_ownplayer2(x-3,y-3,1,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB)&&check_kills_ownplayer(p,q,1,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB))
      {
        pair <lld,lld> xx ;
        xx.first = p;
        xx.second = q;
        can_be_killed.push_back(xx);
      }
      if(0<=a&&a<8&&b<8&&0<=b&&check_kills_ownplayer2(x+1,y+1,1,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB)&&check_kills_ownplayer(a,b,1,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB))
      {
        pair <lld,lld> xx ;
        xx.first = a;
        xx.second = b;
        can_be_killed.push_back(xx);
      }


}

}


  }
  else{
if(soldierB[soldier_selected]==1){
              //----
              lld x = curr_posB[soldier_selected].first;
              lld y = curr_posB[soldier_selected].second;
              lld i,j,k,p,q,e,f,a,b;
              j = x-2;
              k = y;
              p = x-1;
              q = y;
              if(0<=j&&j<8&&0<=p&&p<8&&0<=q&&q<8&&k<8&&0<=k&&!check_kills_ownplayer1(j,k,2,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB)&&!check_kills_ownplayer1(p,q,2,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB)){

                    j = x-5; k = y;
                    p = x-4; q = y;
                    e = x+2; f = y;
                    a = x+3; b = y;



                    if(0<=j&&j<8&&k<8&&0<=k&&check_kills_ownplayer2(x-3,y,2,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB)&&check_kills_ownplayer(j,k,2,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB))
                    {
                      pair <lld,lld> xx ;
                      xx.first = j;
                      xx.second = k;
                      can_be_killed.push_back(xx);
                    }
                    if(0<=e&&e<8&&f<8&&0<=f&&check_kills_ownplayer2(x+1,y,2,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB)&&check_kills_ownplayer(e,f,2,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB))
                    {
                      pair <lld,lld> xx ;
                      xx.first = e;
                      xx.second = f;
                      can_be_killed.push_back(xx);
                    }
                    if(0<=p&&p<8&&q<8&&0<=q&&check_kills_ownplayer2(x-3,y,2,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB)&&check_kills_ownplayer(p,q,2,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB))
                    {
                      pair <lld,lld> xx ;
                      xx.first = p;
                      xx.second = q;
                      can_be_killed.push_back(xx);
                    }
                    if(0<=a&&a<8&&b<8&&0<=b&&check_kills_ownplayer2(x+1,y,2,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB)&&check_kills_ownplayer(a,b,2,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB))
                    {
                      pair <lld,lld> xx ;
                      xx.first = a;
                      xx.second = b;
                      can_be_killed.push_back(xx);
                    }

              }

                j = x-1;
                k = y;
                p = x+1;
                q = y;
                if(0<=j&&j<8&&0<=p&&p<8&&0<=q&&q<8&&k<8&&0<=k&&!check_kills_ownplayer1(j,k,2,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB)&&!check_kills_ownplayer1(p,q,2,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB)){

                      j = x-3; k = y;
                      p = x-4; q = y;
                      e = x+4; f = y;
                      a = x+3; b = y;
                      if(0<=j&&j<8&&k<8&&0<=k&&check_kills_ownplayer2(x-2,y,2,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB)&&check_kills_ownplayer(j,k,2,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB))
                      {
                        pair <lld,lld> xx ;
                        xx.first = j;
                        xx.second = k;
                        can_be_killed.push_back(xx);
                      }
                      if(0<=e&&e<8&&f<8&&0<=f&&check_kills_ownplayer2(x+2,y,2,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB)&&check_kills_ownplayer(e,f,2,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB))
                      {
                        pair <lld,lld> xx ;
                        xx.first = e;
                        xx.second = f;
                        can_be_killed.push_back(xx);
                      }
                      if(0<=p&&p<8&&q<8&&0<=q&&check_kills_ownplayer2(x-2,y,2,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB)&&check_kills_ownplayer(p,q,2,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB))
                      {
                        pair <lld,lld> xx ;
                        xx.first = p;
                        xx.second = q;
                        can_be_killed.push_back(xx);
                      }
                      if(0<=a&&a<8&&b<8&&0<=b&&check_kills_ownplayer2(x+2,y,2,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB)&&check_kills_ownplayer(a,b,2,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB))
                      {
                        pair <lld,lld> xx ;
                        xx.first = a;
                        xx.second = b;
                        can_be_killed.push_back(xx);
                      }



              }

              j = x+2;
              k = y;
              p = x+1;
              q = y;
              if(0<=j&&j<8&&0<=p&&p<8&&0<=q&&q<8&&k<8&&0<=k&&!check_kills_ownplayer1(j,k,2,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB)&&!check_kills_ownplayer1(p,q,2,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB)){

                    j = x-3; k = y;
                    p = x-2; q = y;
                    e = x+4; f = y;
                    a = x+5; b = y;
                    if(0<=j&&j<8&&k<8&&0<=k&&check_kills_ownplayer2(x-1,y,2,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB)&&check_kills_ownplayer(j,k,2,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB))
                    {
                      pair <lld,lld> xx ;
                      xx.first = j;
                      xx.second = k;
                      can_be_killed.push_back(xx);
                    }
                    if(0<=e&&e<8&&f<8&&0<=f&&check_kills_ownplayer2(x+3,y,2,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB)&&check_kills_ownplayer(e,f,2,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB))
                    {
                      pair <lld,lld> xx ;
                      xx.first = e;
                      xx.second = f;
                      can_be_killed.push_back(xx);
                    }
                    if(0<=p&&p<8&&q<8&&0<=q&&check_kills_ownplayer2(x-1,y,2,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB)&&check_kills_ownplayer(p,q,2,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB))
                    {
                      pair <lld,lld> xx ;
                      xx.first = p;
                      xx.second = q;
                      can_be_killed.push_back(xx);
                    }
                    if(0<=a&&a<8&&b<8&&0<=b&&check_kills_ownplayer2(x+3,y,2,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB)&&check_kills_ownplayer(a,b,2,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB))
                    {
                      pair <lld,lld> xx ;
                      xx.first = a;
                      xx.second = b;
                      can_be_killed.push_back(xx);
                    }



            }

            j = x;
            k = y-1;
            p = x;
            q = y+1;
            if(0<=j&&j<8&&0<=p&&p<8&&0<=q&&q<8&&k<8&&0<=k&&!check_kills_ownplayer1(j,k,2,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB)&&!check_kills_ownplayer1(p,q,2,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB)){

                  j = x; k = y-4;
                  p = x; q = y-3;
                  e = x; f = y+4;
                  a = x; b = y+3;
                  if(0<=j&&j<8&&k<8&&0<=k&&check_kills_ownplayer2(x,y-2,2,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB)&&check_kills_ownplayer(j,k,2,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB))
                  {
                    pair <lld,lld> xx ;
                    xx.first = j;
                    xx.second = k;
                    can_be_killed.push_back(xx);
                  }
                  if(0<=e&&e<8&&f<8&&0<=f&&check_kills_ownplayer2(x,y+2,2,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB)&&check_kills_ownplayer(e,f,2,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB))
                  {
                    pair <lld,lld> xx ;
                    xx.first = e;
                    xx.second = f;
                    can_be_killed.push_back(xx);
                  }
                  if(0<=p&&p<8&&q<8&&0<=q&&check_kills_ownplayer2(x,y-2,2,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB)&&check_kills_ownplayer(p,q,2,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB))
                  {
                    pair <lld,lld> xx ;
                    xx.first = p;
                    xx.second = q;
                    can_be_killed.push_back(xx);
                  }
                  if(0<=a&&a<8&&b<8&&0<=b&&check_kills_ownplayer2(x,y+2,2,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB)&&check_kills_ownplayer(a,b,2,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB))
                  {
                    pair <lld,lld> xx ;
                    xx.first = a;
                    xx.second = b;
                    can_be_killed.push_back(xx);
                  }


          }

          j = x;
          k = y-1;
          p = x;
          q = y-2;
          if(0<=j&&j<8&&0<=p&&p<8&&0<=q&&q<8&&k<8&&0<=k&&!check_kills_ownplayer1(j,k,2,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB)&&!check_kills_ownplayer1(p,q,2,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB)){

                j = x; k = y-4;
                p = x; q = y-5;
                e = x; f = y+2;
                a = x; b = y+3;
                if(0<=j&&j<8&&k<8&&0<=k&&check_kills_ownplayer2(x,y-3,2,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB)&&check_kills_ownplayer(j,k,2,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB))
                {
                  pair <lld,lld> xx ;
                  xx.first = j;
                  xx.second = k;
                  can_be_killed.push_back(xx);
                }
                if(0<=e&&e<8&&f<8&&0<=f&&check_kills_ownplayer2(x,y+1,2,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB)&&check_kills_ownplayer(e,f,2,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB))
                {
                  pair <lld,lld> xx ;
                  xx.first = e;
                  xx.second = f;
                  can_be_killed.push_back(xx);
                }
                if(0<=p&&p<8&&q<8&&0<=q&&check_kills_ownplayer2(x,y-3,2,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB)&&check_kills_ownplayer(p,q,2,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB))
                {
                  pair <lld,lld> xx ;
                  xx.first = p;
                  xx.second = q;
                  can_be_killed.push_back(xx);
                }
                if(0<=a&&a<8&&b<8&&0<=b&&check_kills_ownplayer2(x,y+1,2,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB)&&check_kills_ownplayer(a,b,2,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB))
                {
                  pair <lld,lld> xx ;
                  xx.first = a;
                  xx.second = b;
                  can_be_killed.push_back(xx);
                }


          }

          j = x;
          k = y+1;
          p = x;
          q = y+2;
          if(0<=j&&j<8&&0<=p&&p<8&&0<=q&&q<8&&k<8&&0<=k&&!check_kills_ownplayer1(j,k,2,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB)&&!check_kills_ownplayer1(p,q,2,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB)){

                j = x; k = y-3;
                p = x; q = y-2;
                e = x; f = y+4;
                a = x; b = y+5;
                if(0<=j&&j<8&&k<8&&0<=k&&check_kills_ownplayer2(x,y-1,2,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB)&&check_kills_ownplayer(j,k,2,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB))
                {
                  pair <lld,lld> xx ;
                  xx.first = j;
                  xx.second = k;
                  can_be_killed.push_back(xx);
                }
                if(0<=e&&e<8&&f<8&&0<=f&&check_kills_ownplayer2(x,y+3,2,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB)&&check_kills_ownplayer(e,f,2,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB))
                {
                  pair <lld,lld> xx ;
                  xx.first = e;
                  xx.second = f;
                  can_be_killed.push_back(xx);
                }
                if(0<=p&&p<8&&q<8&&0<=q&&check_kills_ownplayer2(x,y-1,2,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB)&&check_kills_ownplayer(p,q,2,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB))
                {
                  pair <lld,lld> xx ;
                  xx.first = p;
                  xx.second = q;
                  can_be_killed.push_back(xx);
                }
                if(0<=a&&a<8&&b<8&&0<=b&&check_kills_ownplayer2(x,y+3,2,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB)&&check_kills_ownplayer(a,b,2,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB))
                {
                  pair <lld,lld> xx ;
                  xx.first = a;
                  xx.second = b;
                  can_be_killed.push_back(xx);
                }


          }

          j = x-1;
          k = y+1;
          p = x+1;
          q = y-1;
          if(0<=j&&j<8&&0<=p&&p<8&&0<=q&&q<8&&k<8&&0<=k&&!check_kills_ownplayer1(j,k,2,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB)&&!check_kills_ownplayer1(p,q,2,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB)){

                j = x-3; k = y+3;
                p = x-4; q = y+4;
                e = x+3; f = y-3;
                a = x+4; b = y-4;
                if(0<=j&&j<8&&k<8&&0<=k&&check_kills_ownplayer2(x-2,y+2,2,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB)&&check_kills_ownplayer(j,k,2,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB))
                {
                  pair <lld,lld> xx ;
                  xx.first = j;
                  xx.second = k;
                  can_be_killed.push_back(xx);
                }
                if(0<=e&&e<8&&f<8&&0<=f&&check_kills_ownplayer2(x+2,y-2,2,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB)&&check_kills_ownplayer(e,f,2,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB))
                {
                  pair <lld,lld> xx ;
                  xx.first = e;
                  xx.second = f;
                  can_be_killed.push_back(xx);
                }
                if(0<=p&&p<8&&q<8&&0<=q&&check_kills_ownplayer2(x-2,y+2,2,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB)&&check_kills_ownplayer(p,q,2,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB))
                {
                  pair <lld,lld> xx ;
                  xx.first = p;
                  xx.second = q;
                  can_be_killed.push_back(xx);
                }
                if(0<=a&&a<8&&b<8&&0<=b&&check_kills_ownplayer2(x+2,y-2,2,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB)&&check_kills_ownplayer(a,b,2,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB))
                {
                  pair <lld,lld> xx ;
                  xx.first = a;
                  xx.second = b;
                  can_be_killed.push_back(xx);
                }


          }

          j = x+1;
          k = y-1;
          p = x+2;
          q = y-2;
          if(0<=j&&j<8&&0<=p&&p<8&&0<=q&&q<8&&k<8&&0<=k&&!check_kills_ownplayer1(j,k,2,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB)&&!check_kills_ownplayer1(p,q,2,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB)){

                j = x-3; k = y+3;
                p = x-2; q = y+2;
                e = x+4; f = y-4;
                a = x+5; b = y-5;
                if(0<=j&&j<8&&k<8&&0<=k&&check_kills_ownplayer2(x-1,y+1,2,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB)&&check_kills_ownplayer(j,k,2,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB))
                {
                  pair <lld,lld> xx ;
                  xx.first = j;
                  xx.second = k;
                  can_be_killed.push_back(xx);
                }
                if(0<=e&&e<8&&f<8&&0<=f&&check_kills_ownplayer2(x+3,y-3,2,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB)&&check_kills_ownplayer(e,f,2,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB))
                {
                  pair <lld,lld> xx ;
                  xx.first = e;
                  xx.second = f;
                  can_be_killed.push_back(xx);
                }
                if(0<=p&&p<8&&q<8&&0<=q&&check_kills_ownplayer2(x-1,y+1,2,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB)&&check_kills_ownplayer(p,q,2,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB))
                {
                  pair <lld,lld> xx ;
                  xx.first = p;
                  xx.second = q;
                  can_be_killed.push_back(xx);
                }
                if(0<=a&&a<8&&b<8&&0<=b&&check_kills_ownplayer2(x+3,y-3,2,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB)&&check_kills_ownplayer(a,b,2,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB))
                {
                  pair <lld,lld> xx ;
                  xx.first = a;
                  xx.second = b;
                  can_be_killed.push_back(xx);
                }


          }

          j = x-2;
          k = y+2;
          p = x-1;
          q = y+1;
          if(0<=j&&j<8&&0<=p&&p<8&&0<=q&&q<8&&k<8&&0<=k&&!check_kills_ownplayer1(j,k,2,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB)&&!check_kills_ownplayer1(p,q,2,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB)){

                j = x+2; k = y-2;
                p = x+3; q = y-3;
                e = x-4; f = y+4;
                a = x-5; b = y+5;
                if(0<=j&&j<8&&k<8&&0<=k&&check_kills_ownplayer2(x+1,y-1,2,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB)&&check_kills_ownplayer(j,k,2,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB))
                {
                  pair <lld,lld> xx ;
                  xx.first = j;
                  xx.second = k;
                  can_be_killed.push_back(xx);
                }
                if(0<=e&&e<8&&f<8&&0<=f&&check_kills_ownplayer2(x-3,y+3,2,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB)&&check_kills_ownplayer(e,f,2,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB))
                {
                  pair <lld,lld> xx ;
                  xx.first = e;
                  xx.second = f;
                  can_be_killed.push_back(xx);
                }
                if(0<=p&&p<8&&q<8&&0<=q&&check_kills_ownplayer2(x+1,y-1,2,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB)&&check_kills_ownplayer(p,q,2,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB))
                {
                  pair <lld,lld> xx ;
                  xx.first = p;
                  xx.second = q;
                  can_be_killed.push_back(xx);
                }
                if(0<=a&&a<8&&b<8&&0<=b&&check_kills_ownplayer2(x-3,y+3,2,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB)&&check_kills_ownplayer(a,b,2,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB))
                {
                  pair <lld,lld> xx ;
                  xx.first = a;
                  xx.second = b;
                  can_be_killed.push_back(xx);
                }


          }

          j = x+1;
          k = y+1;
          p = x+2;
          q = y+2;
          if(0<=j&&j<8&&0<=p&&p<8&&0<=q&&q<8&&k<8&&0<=k&&!check_kills_ownplayer1(j,k,2,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB)&&!check_kills_ownplayer1(p,q,2,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB)){

                j = x-2; k = y-2;
                p = x-3; q = y-3;
                e = x+4; f = y+4;
                a = x+5; b = y+5;
                if(0<=j&&j<8&&k<8&&0<=k&&check_kills_ownplayer2(x-1,y-1,2,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB)&&check_kills_ownplayer(j,k,2,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB))
                {
                  pair <lld,lld> xx ;
                  xx.first = j;
                  xx.second = k;
                  can_be_killed.push_back(xx);
                }
                if(0<=e&&e<8&&f<8&&0<=f&&check_kills_ownplayer2(x+3,y+3,2,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB)&&check_kills_ownplayer(e,f,2,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB))
                {
                  pair <lld,lld> xx ;
                  xx.first = e;
                  xx.second = f;
                  can_be_killed.push_back(xx);
                }
                if(0<=p&&p<8&&q<8&&0<=q&&check_kills_ownplayer2(x-1,y-1,2,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB)&&check_kills_ownplayer(p,q,2,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB))
                {
                  pair <lld,lld> xx ;
                  xx.first = p;
                  xx.second = q;
                  can_be_killed.push_back(xx);
                }
                if(0<=a&&a<8&&b<8&&0<=b&&check_kills_ownplayer2(x+3,y+3,2,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB)&&check_kills_ownplayer(a,b,2,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB))
                {
                  pair <lld,lld> xx ;
                  xx.first = a;
                  xx.second = b;
                  can_be_killed.push_back(xx);
                }


          }

          j = x+1;
          k = y+1;
          p = x-1;
          q = y-1;
          if(0<=j&&j<8&&0<=p&&p<8&&0<=q&&q<8&&k<8&&0<=k&&!check_kills_ownplayer1(j,k,2,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB)&&!check_kills_ownplayer1(p,q,2,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB)){

                j = x+3; k = y+3;
                p = x+4; q = y+4;
                e = x-3; f = y-3;
                a = x-4; b = y-4;
                if(0<=j&&j<8&&k<8&&0<=k&&check_kills_ownplayer2(x+2,y+2,2,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB)&&check_kills_ownplayer(j,k,2,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB))
                {
                  pair <lld,lld> xx ;
                  xx.first = j;
                  xx.second = k;
                  can_be_killed.push_back(xx);
                }
                if(0<=e&&e<8&&f<8&&0<=f&&check_kills_ownplayer2(x-2,y-2,2,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB)&&check_kills_ownplayer(e,f,2,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB))
                {
                  pair <lld,lld> xx ;
                  xx.first = e;
                  xx.second = f;
                  can_be_killed.push_back(xx);
                }
                if(0<=p&&p<8&&q<8&&0<=q&&check_kills_ownplayer2(x+2,y+2,2,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB)&&check_kills_ownplayer(p,q,2,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB))
                {
                  pair <lld,lld> xx ;
                  xx.first = p;
                  xx.second = q;
                  can_be_killed.push_back(xx);
                }
                if(0<=a&&a<8&&b<8&&0<=b&&check_kills_ownplayer2(x-2,y-2,2,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB)&&check_kills_ownplayer(a,b,2,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB))
                {
                  pair <lld,lld> xx ;
                  xx.first = a;
                  xx.second = b;
                  can_be_killed.push_back(xx);
                }


          }

          j = x-2;
          k = y-2;
          p = x-1;
          q = y-1;
          if(0<=j&&j<8&&0<=p&&p<8&&0<=q&&q<8&&k<8&&0<=k&&!check_kills_ownplayer1(j,k,2,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB)&&!check_kills_ownplayer1(p,q,2,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB)){

                j = x-4; k = y-4;
                p = x-5; q = y-5;
                e = x+2; f = y+2;
                a = x+3; b = y+3;
                if(0<=j&&j<8&&k<8&&0<=k&&check_kills_ownplayer2(x-3,y-3,2,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB)&&check_kills_ownplayer(j,k,2,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB))
                {
                  pair <lld,lld> xx ;
                  xx.first = j;
                  xx.second = k;
                  can_be_killed.push_back(xx);
                }
                if(0<=e&&e<8&&f<8&&0<=f&&check_kills_ownplayer2(x+1,y+1,2,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB)&&check_kills_ownplayer(e,f,2,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB))
                {
                  pair <lld,lld> xx ;
                  xx.first = e;
                  xx.second = f;
                  can_be_killed.push_back(xx);
                }
                if(0<=p&&p<8&&q<8&&0<=q&&check_kills_ownplayer2(x-3,y-3,2,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB)&&check_kills_ownplayer(p,q,2,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB))
                {
                  pair <lld,lld> xx ;
                  xx.first = p;
                  xx.second = q;
                  can_be_killed.push_back(xx);
                }
                if(0<=a&&a<8&&b<8&&0<=b&&check_kills_ownplayer2(x+1,y+1,2,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB)&&check_kills_ownplayer(a,b,2,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB))
                {
                  pair <lld,lld> xx ;
                  xx.first = a;
                  xx.second = b;
                  can_be_killed.push_back(xx);
                }


          }
              //---
}
  }

  return can_be_killed;
}

// checks whether (x,y) is valid point on the board
bool check_valid_move(lld x,lld y)
{
  if(0<=x&&x<8&&y<8&&0<=y)
  {
    return true;
  }

  return false;

}

// for a selected soldier gives the points where a soldier can move.
vector <pair <lld,lld>> movesoldier(lld player_number,lld soldier_selected,pair <lld,lld> curr_posA[], pair <lld,lld> curr_posB[],lld soldierB[],lld soldierA[],lld townhallsB[],lld townhallsA[]){
  vector <pair <lld,lld>> target = can_player_be_killed(player_number,soldier_selected,curr_posA,curr_posB,soldierB,soldierA,townhallsB,townhallsA);
  lld r = target.size(),j,k,p,q;
//  //        cerr << "start\n";
  if(player_number==1){
    if(soldierA[soldier_selected]==1){

          j = curr_posA[soldier_selected].first +1 ;
          k = curr_posA[soldier_selected].second  ;
          p = curr_posA[soldier_selected].second -1;
          q = curr_posA[soldier_selected].second + 1;
        //  //        cerr << j << " " << k << " " << p << " " << q << endl;
          if(check_valid_move(j,k)&&check_kills_ownplayer(j,k,1,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB))
          {
            if(!check_kills_townhall(j,k,2,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB))
            {
              r=0;
            }
            pair <lld,lld> xx;
            xx.first = j;
            xx.second = k;
            target.push_back(xx);
      //      //        cerr << j << " " << k << endl;
          }

          if(check_valid_move(j,p)&&check_kills_ownplayer(j,p,1,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB))
          {
            if(!check_kills_townhall(j,p,2,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB))
            {
              r=0;
            }
            pair <lld,lld> xx;
            xx.first = j;
            xx.second = p;
            target.push_back(xx);
      //      //        cerr << j << " " << p << endl;
          }
          if(check_valid_move(j,q)&&check_kills_ownplayer(j,q,1,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB))
          {
            if(!check_kills_townhall(j,q,2,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB))
            {
              r=0;
            }
            pair <lld,lld> xx;
            xx.first = j;
            xx.second = q;
            target.push_back(xx);
      //      //        cerr << j << " " << q << endl;
          }


          if(r!=0)
    {
      j = curr_posA[soldier_selected].first - 2 ;
      k = curr_posA[soldier_selected].second  ;
      p = curr_posA[soldier_selected].second -2;
      q = curr_posA[soldier_selected].second + 2;

      if(check_valid_move(j,k)&&check_kills_ownplayer(j,k,1,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB))
      {
        pair <lld,lld> xx;
        xx.first = j;
        xx.second = k;
        target.push_back(xx);
      //  //        cerr << j << " " << k << endl;
      }
      if(check_valid_move(j,p)&&check_kills_ownplayer(j,p,1,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB))
      {
        pair <lld,lld> xx;
        xx.first = j;
        xx.second = p;
        target.push_back(xx);
      //  //        cerr << j << " " << p << endl;
      }
      if(check_valid_move(j,q)&&check_kills_ownplayer(j,q,1,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB))
      {
        pair <lld,lld> xx;
        xx.first = j;
        xx.second = q;
        target.push_back(xx);
    //    //        cerr << j << " " << q << endl;
      }
    }
  }

  }
  else{
  //  //        cerr << r << endl;
    //----
    if(soldierB[soldier_selected]==1){


          j = curr_posB[soldier_selected].first -1 ;
          k = curr_posB[soldier_selected].second  ;
          p = curr_posB[soldier_selected].second -1;
          q = curr_posB[soldier_selected].second + 1;
   //       //        cerr << j << " " << k << " " << p << " " << q << " " << check_kills_ownplayer(j,k,2,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB) << endl ;
          if(check_valid_move(j,k)&&check_kills_ownplayer(j,k,2,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB))
          {
            if(!check_kills_townhall(j,k,1,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB))
            {
              r=0;
            }
            pair <lld,lld> xx;
            xx.first = j;
            xx.second = k;
            target.push_back(xx);
//            //        cerr << j << " " << k << endl;
          }

          if(check_valid_move(j,p)&&check_kills_ownplayer(j,p,2,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB))
          {
            if(!check_kills_townhall(j,p,1,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB))
            {
              r=0;
            }
            pair <lld,lld> xx;
            xx.first = j;
            xx.second = p;
            target.push_back(xx);
//            //        cerr << j << " " << p << endl;
          }
          if(check_valid_move(j,q)&&check_kills_ownplayer(j,q,2,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB))
          {
            if(!check_kills_townhall(j,q,1,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB))
            {
              r=0;
            }
            pair <lld,lld> xx;
            xx.first = j;
            xx.second = q;
            target.push_back(xx);
//            //        cerr << j << " " << q << endl;
          }


          if(r!=0)
    {
      j = curr_posB[soldier_selected].first + 2 ;
      k = curr_posB[soldier_selected].second  ;
      p = curr_posB[soldier_selected].second -2;
      q = curr_posB[soldier_selected].second + 2;
      if(check_valid_move(j,k)&&check_kills_ownplayer(j,k,2,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB))
      {
        pair <lld,lld> xx;
        xx.first = j;
        xx.second = k;
        target.push_back(xx);
    //    //        cerr << j << " " << k << endl;
      }

      if(check_valid_move(j,p)&&check_kills_ownplayer(j,p,2,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB))
      {
        pair <lld,lld> xx;
        xx.first = j;
        xx.second = p;
        target.push_back(xx);
    //    //        cerr << j << " " << p << endl;
      }
      if(check_valid_move(j,q)&&check_kills_ownplayer(j,q,2,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB))
      {
        pair <lld,lld> xx;
        xx.first = j;
        xx.second = q;
        target.push_back(xx);
    //    //        cerr << j << " " << q << endl;
      }
    }

    //---
  }

  }
//  //        cerr << "----" << endl;
return target;
}

// genrates all moves valid on board (for given playerID).
vector <tuple <char,pair <lld,lld>,pair <lld,lld > > > all_valid_moves_on_board(pair <lld,lld> curr_posA[], pair <lld,lld> curr_posB[],lld soldierB[],lld soldierA[],lld townhallsB[],lld townhallsA[], int player_id){
	vector <tuple <char,pair <lld,lld>,pair <lld,lld > > > all_moves ;
	lld i,j,k;
//	cerr<<"PLAYER ID IS IN: "<<player_id<<endl;
	if(player_id==1){

  		for(i=0;i<12;i++){
//        //        cerr << "bombA  moves" << endl;
    		vector <pair <lld,lld> > bomb = is_Cannon_formed(1,i,curr_posB,curr_posA,soldierB,soldierA);
    		for(j=0;j<bomb.size();j++){
      			tuple <char,pair <lld,lld>, pair <lld,lld> > xx;
      			xx = make_tuple('B',curr_posA[i],bomb[j]);
        //    //        cerr << curr_posA[i].second << " " << curr_posA[i].first << " " << bomb[j].second << " " << bomb[j].first << endl;
      			all_moves.push_back(xx);
    		}
        //        cerr << "soldierA  moves" << endl;
			vector <pair <lld,lld> > move = movesoldier(1,i,curr_posA,curr_posB,soldierB,soldierA,townhallsB,townhallsA);
    		for(j=0;j<move.size();j++){
    			tuple <char,pair <lld,lld>, pair <lld,lld> > xx;
      			xx = make_tuple('M',curr_posA[i],move[j]);	//## pushing 0 0 always
      	//		//        cerr << curr_posA[i].second << " " << curr_posA[i].first << " " << move[j].second << " " << move[j].first << endl;
      			all_moves.push_back(xx);
    		}

        vector <pair <lld,lld>> movement_can = cannon_movement(1,i,curr_posB,curr_posA,soldierB,soldierA);
        for(j=0;j<movement_can.size();j++){
      			tuple <char,pair <lld,lld>, pair <lld,lld> > xx;
      			xx = make_tuple('M',curr_posA[i],movement_can[j]);
          //  //        cerr << curr_posA[i].second << " " << curr_posA[i].first << " " << bomb[j].second << " " << bomb[j].first << endl;
      			all_moves.push_back(xx);
    		}
  		}
	}
	else{
  		for(i=0;i<12;i++){
//        //        cerr << "bombB  moves" << endl;
    		vector <pair <lld,lld> > bomb = is_Cannon_formed(2,i,curr_posB,curr_posA,soldierB,soldierA);
    		for(j=0;j<bomb.size();j++){
      			tuple <char,pair <lld,lld>, pair <lld,lld> > xx;
      			xx = make_tuple('B',curr_posB[i],bomb[j]);
//            //        cerr << curr_posB[i].second << " " << curr_posB[i].first << " " << bomb[j].second << " " << bomb[j].first << endl;
      			all_moves.push_back(xx);
    		}
        //        cerr << "soldierB  moves" << endl;
    		vector <pair <lld,lld> > move = movesoldier(2,i,curr_posA,curr_posB,soldierB,soldierA,townhallsB,townhallsA);
    		for(j=0;j<move.size();j++){
     			tuple <char,pair <lld,lld>, pair <lld,lld> > xx;
      			xx = make_tuple('M',curr_posB[i],move[j]);
            //        cerr << curr_posB[i].second << " " << curr_posB[i].first << " " << move[j].second << " " << move[j].first << endl;
      			all_moves.push_back(xx);
    		}

        vector <pair <lld,lld>> movement_can = cannon_movement(2,i,curr_posB,curr_posA,soldierB,soldierA);
        for(j=0;j<movement_can.size();j++){
      			tuple <char,pair <lld,lld>, pair <lld,lld> > xx;
      			xx = make_tuple('M',curr_posB[i],movement_can[j]);
          //  //        cerr << curr_posA[i].second << " " << curr_posA[i].first << " " << bomb[j].second << " " << bomb[j].first << endl;
      			all_moves.push_back(xx);
    		}
        //        cerr << "ok\n";
  		}
	}
  	return all_moves;
}/*END ALL VALI*/


// this function gives all moves on the temporary board.
vector < tuple<char,pair <lld,lld>,pair <lld,lld> > > getValidMoves(vector<vector<int> > temp_board,int playID)
{
  lld i,j,k=0,e=0,q=0,p=0;
  lld sA[12],sB[12],tA[4],tB[4];
  pair <lld,lld> cpA[12],cpB[12],cptA[4],cptB[4];

	for(i=0;i<temp_board.size();i++){
		for(j=0;j<temp_board[i].size();j++){
      		if(temp_board[i][j] == 1){
        		sA[k] = 1;
        		cpA[k].first = i;
        		cpA[k].second = j;
        		k++;
      		}
      		else if(temp_board[i][j] ==2){
        		tA[p] = 1;
        		cptA[p].first = i;
        		cptA[p].second = j;
        		p++;
      		}
      		else if(temp_board[i][j] == -1){
        		sB[e] = 1;
        		cpB[e].first = i;
        		cpB[e].second = j;
        		e++;
      		}
      		else if(temp_board[i][j] ==-2){
        		tB[q] = 1;
        		cptB[q].first = i;
        		cptB[q].second = j;
        		q++;
      		}

    	}
	}

	for(i=q;i<4;i++){
    	tB[i] = 0;
    	cptB[i].first = -1;
    	cptB[i].second = -1;
  	}
  	for(i=p;i<4;i++){
    	tA[i] = 0;
    	cptA[i].first = -1;
    	cptA[i].second = -1;
  	}
  	for(i=k;i<12;i++){
    	sA[i] =0;
    	cpA[i].first = -1;
    	cpA[i].second = -1;
  	}
  	for(i=e;i<12;i++){
    	sB[i] =0;
    	cpB[i].first = -1;
    	cpB[i].second = -1;
  	}

    //debug
  /*  //        cerr << "Soldier A" << endl;
    for(i=0;i<k;i++)
    {
        //        cerr << cpA[i].first << " " << cpA[i].second << endl;
    }
    //        cerr << "Townhall A" << endl;
    for(i=0;i<p;i++)
    {
        //        cerr << cptA[i].first << " " << cptA[i].second << endl;
    }
    //        cerr << "Soldier B" << endl;
    for(i=0;i<e;i++)
    {
        //        cerr << cpB[i].first << " " << cpB[i].second << endl;
    }
    //        cerr << "Townhall B" << endl;
    for(i=0;i<q;i++)
    {
        //        cerr << cptB[i].first << " " << cptB[i].second << endl;
    }



	//        cerr <<"MOVE PRINT: "<< k << " " << p << " " << e << " " << q << endl;*/




  return all_valid_moves_on_board(cpA,cpB,sB,sA,tB,tA,playID);

}



vector <vector <int> > update(vector <vector <int> > temp_board , tuple <char, pair <int,int> , pair <int,int> > move , int player_id){
          char a = get<0>(move);
          int x = get<1>(move).first;
          int y = get<1>(move).second;
          int p = get<2>(move).first;
          int q = get<2>(move).second;

     //            cerr<<"Try Move: S "<<y<<" "<<x<<" "<<a<<" "<<q<<" "<<p<<endl;

	//	//        cerr<<"ID TO MOVE "<<player_id;
          if(player_id == 1){
          if(a == 'M')
          {
         // 	if(temp_board[x][y]==0||temp_board[x][y]==2||temp_board[x][y]==-2||temp_board[x][y]==-1)         cerr<<"Invalid Move: White solider not present here"<<endl;
            temp_board[x][y] = 0;
    //        if(temp_board[p][q]==1||temp_board[p][q]==2)         cerr<<"Invalid Move our player present there"<<endl;
            temp_board[p][q]  = 1;
          }
          else{	//take cannon shot
            temp_board[p][q]  = 0;
          }

        }
        else{
          if(a == 'M')
          {
            temp_board[x][y] = 0;
     //       if(temp_board[p][q]==-1||temp_board[p][q]==-2)         cerr<<"Invalid Move our player present there"<<endl;
            temp_board[p][q]  = -1;
          }
          else{
            temp_board[p][q]  = 0;
          }
        }
//		for(int i=0;i<8;i++){
//			for(int j=0;j<8;j++)
//				cerr<<temp_board[i][j]<<" ";
//			cerr<<endl;
//		}
        return temp_board;
}



vector <pair <lld,lld> >  cannon_movement(lld player_number,lld soldier_selected,pair <lld,lld> curr_posB[],pair <lld,lld> curr_posA[],lld soldierB[],lld soldierA[]){
  vector <pair <lld,lld>> can_be_killed;
  if(player_number==1){
    if(soldierA[soldier_selected]==1){
    lld x = curr_posA[soldier_selected].first;
    lld y = curr_posA[soldier_selected].second;
    lld i,j,k,p,q,e,f,a,b;
    j = x-2;
    k = y;
    p = x-1;
    q = y;
    if(0<=j&&j<8&&0<=p&&p<8&&0<=q&&q<8&&k<8&&0<=k&&!check_kills_ownplayer1(j,k,1,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB)&&!check_kills_ownplayer1(p,q,1,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB)){
          a = x-3; b = y;

          if(0<=a&&a<8&&b<8&&0<=b&&check_kills_ownplayer(a,b,1,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB)&&check_kills_ownplayer(a,b,2,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB))
          {
            pair <lld,lld> xx ;
            xx.first = a;
            xx.second = b;
            can_be_killed.push_back(xx);
          }

    }


    j = x+2;
    k = y;
    p = x+1;
    q = y;
    if(0<=j&&j<8&&0<=p&&p<8&&0<=q&&q<8&&k<8&&0<=k&&!check_kills_ownplayer1(j,k,1,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB)&&!check_kills_ownplayer1(p,q,1,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB)){


          a = x+3; b = y;
          if(0<=a&&a<8&&b<8&&0<=b&&check_kills_ownplayer(a,b,1,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB)&&check_kills_ownplayer(a,b,2,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB))
          {
            pair <lld,lld> xx ;
            xx.first = a;
            xx.second = b;
            can_be_killed.push_back(xx);
          }
  }
j = x;
k = y-1;
p = x;
q = y-2;
if(0<=j&&j<8&&0<=p&&p<8&&0<=q&&q<8&&k<8&&0<=k&&!check_kills_ownplayer1(j,k,1,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB)&&!check_kills_ownplayer1(p,q,1,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB)){


      a = x; b = y-3;
      if(0<=a&&a<8&&b<8&&0<=b&&check_kills_ownplayer(a,b,1,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB)&&check_kills_ownplayer(a,b,2,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB))
      {
        pair <lld,lld> xx ;
        xx.first = a;
        xx.second = b;
        can_be_killed.push_back(xx);
      }
}

j = x;
k = y+1;
p = x;
q = y+2;
if(0<=j&&j<8&&0<=p&&p<8&&0<=q&&q<8&&k<8&&0<=k&&!check_kills_ownplayer1(j,k,1,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB)&&!check_kills_ownplayer1(p,q,1,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB)){


      a = x; b = y+3;
      if(0<=a&&a<8&&b<8&&0<=b&&check_kills_ownplayer(a,b,1,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB)&&check_kills_ownplayer(a,b,2,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB))
      {
        pair <lld,lld> xx ;
        xx.first = a;
        xx.second = b;
        can_be_killed.push_back(xx);
      }


}


j = x+1;
k = y-1;
p = x+2;
q = y-2;
if(0<=j&&j<8&&0<=p&&p<8&&0<=q&&q<8&&k<8&&0<=k&&!check_kills_ownplayer1(j,k,1,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB)&&!check_kills_ownplayer1(p,q,1,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB)){

      a = x+3; b = y-3;
      if(0<=a&&a<8&&b<8&&0<=b&&check_kills_ownplayer(a,b,1,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB)&&check_kills_ownplayer(a,b,2,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB))
      {
        pair <lld,lld> xx ;
        xx.first = a;
        xx.second = b;
        can_be_killed.push_back(xx);
      }


}

j = x-2;
k = y+2;
p = x-1;
q = y+1;
if(0<=j&&j<8&&0<=p&&p<8&&0<=q&&q<8&&k<8&&0<=k&&!check_kills_ownplayer1(j,k,1,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB)&&!check_kills_ownplayer1(p,q,1,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB)){


      a = x-3; b = y+3;
      if(0<=a&&a<8&&b<8&&0<=b&&check_kills_ownplayer(a,b,1,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB)&&check_kills_ownplayer(a,b,2,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB))
      {
        pair <lld,lld> xx ;
        xx.first = a;
        xx.second = b;
        can_be_killed.push_back(xx);
      }


}

j = x+1;
k = y+1;
p = x+2;
q = y+2;
if(0<=j&&j<8&&0<=p&&p<8&&0<=q&&q<8&&k<8&&0<=k&&!check_kills_ownplayer1(j,k,1,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB)&&!check_kills_ownplayer1(p,q,1,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB)){


      a = x+3; b = y+3;
      if(0<=a&&a<8&&b<8&&0<=b&&check_kills_ownplayer(a,b,1,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB)&&check_kills_ownplayer(a,b,2,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB))
      {
        pair <lld,lld> xx ;
        xx.first = a;
        xx.second = b;
        can_be_killed.push_back(xx);
      }

}


j = x-2;
k = y-2;
p = x-1;
q = y-1;
if(0<=j&&j<8&&0<=p&&p<8&&0<=q&&q<8&&k<8&&0<=k&&!check_kills_ownplayer1(j,k,1,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB)&&!check_kills_ownplayer1(p,q,1,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB)){


      a = x-3; b = y-3;
      if(0<=a&&a<8&&b<8&&0<=b&&check_kills_ownplayer(a,b,1,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB)&&check_kills_ownplayer(a,b,2,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB))
      {
        pair <lld,lld> xx ;
        xx.first = a;
        xx.second = b;
        can_be_killed.push_back(xx);
      }


}

}


  }
  else{
if(soldierB[soldier_selected]==1){
              //----
              lld x = curr_posB[soldier_selected].first;
lld y = curr_posB[soldier_selected].second;
lld i,j,k,p,q,e,f,a,b;
j = x-2;
k = y;
p = x-1;
q = y;
if(0<=j&&j<8&&0<=p&&p<8&&0<=q&&q<8&&k<8&&0<=k&&!check_kills_ownplayer1(j,k,2,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB)&&!check_kills_ownplayer1(p,q,2,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB)){

      a = x-3; b = y;

      if(0<=a&&a<8&&b<8&&0<=b&&check_kills_ownplayer(a,b,1,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB)&&check_kills_ownplayer(a,b,2,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB))
      {
        pair <lld,lld> xx ;
        xx.first = a;
        xx.second = b;
        can_be_killed.push_back(xx);
      }

}


j = x+2;
k = y;
p = x+1;
q = y;
if(0<=j&&j<8&&0<=p&&p<8&&0<=q&&q<8&&k<8&&0<=k&&!check_kills_ownplayer1(j,k,2,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB)&&!check_kills_ownplayer1(p,q,2,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB)){


      a = x+3; b = y;
      if(0<=a&&a<8&&b<8&&0<=b&&check_kills_ownplayer(a,b,1,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB)&&check_kills_ownplayer(a,b,2,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB))
      {
        pair <lld,lld> xx ;
        xx.first = a;
        xx.second = b;
        can_be_killed.push_back(xx);
      }



}



j = x;
k = y-1;
p = x;
q = y-2;
if(0<=j&&j<8&&0<=p&&p<8&&0<=q&&q<8&&k<8&&0<=k&&!check_kills_ownplayer1(j,k,2,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB)&&!check_kills_ownplayer1(p,q,2,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB)){


  a = x; b = y-3;
  if(0<=a&&a<8&&b<8&&0<=b&&check_kills_ownplayer(a,b,1,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB)&&check_kills_ownplayer(a,b,2,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB))
  {
    pair <lld,lld> xx ;
    xx.first = a;
    xx.second = b;
    can_be_killed.push_back(xx);
  }


}

j = x;
k = y+1;
p = x;
q = y+2;
if(0<=j&&j<8&&0<=p&&p<8&&0<=q&&q<8&&k<8&&0<=k&&!check_kills_ownplayer1(j,k,2,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB)&&!check_kills_ownplayer1(p,q,2,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB)){


  a = x; b = y+3;
  if(0<=a&&a<8&&b<8&&0<=b&&check_kills_ownplayer(a,b,1,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB)&&check_kills_ownplayer(a,b,2,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB))
  {
    pair <lld,lld> xx ;
    xx.first = a;
    xx.second = b;
    can_be_killed.push_back(xx);
  }


}


j = x+1;
k = y-1;
p = x+2;
q = y-2;
if(0<=j&&j<8&&0<=p&&p<8&&0<=q&&q<8&&k<8&&0<=k&&!check_kills_ownplayer1(j,k,2,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB)&&!check_kills_ownplayer1(p,q,2,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB)){

  a = x+3; b = y-3;
  if(0<=a&&a<8&&b<8&&0<=b&&check_kills_ownplayer(a,b,1,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB)&&check_kills_ownplayer(a,b,2,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB))
  {
    pair <lld,lld> xx ;
    xx.first = a;
    xx.second = b;
    can_be_killed.push_back(xx);
  }


}

j = x-2;
k = y+2;
p = x-1;
q = y+1;
if(0<=j&&j<8&&0<=p&&p<8&&0<=q&&q<8&&k<8&&0<=k&&!check_kills_ownplayer1(j,k,2,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB)&&!check_kills_ownplayer1(p,q,2,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB)){


  a = x-3; b = y+3;
  if(0<=a&&a<8&&b<8&&0<=b&&check_kills_ownplayer(a,b,1,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB)&&check_kills_ownplayer(a,b,2,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB))
  {
    pair <lld,lld> xx ;
    xx.first = a;
    xx.second = b;
    can_be_killed.push_back(xx);
  }


}

j = x+1;
k = y+1;
p = x+2;
q = y+2;
if(0<=j&&j<8&&0<=p&&p<8&&0<=q&&q<8&&k<8&&0<=k&&!check_kills_ownplayer1(j,k,2,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB)&&!check_kills_ownplayer1(p,q,2,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB)){


  a = x+3; b = y+3;
  if(0<=a&&a<8&&b<8&&0<=b&&check_kills_ownplayer(a,b,1,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB)&&check_kills_ownplayer(a,b,2,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB))
  {
    pair <lld,lld> xx ;
    xx.first = a;
    xx.second = b;
    can_be_killed.push_back(xx);
  }

}


j = x-2;
k = y-2;
p = x-1;
q = y-1;
if(0<=j&&j<8&&0<=p&&p<8&&0<=q&&q<8&&k<8&&0<=k&&!check_kills_ownplayer1(j,k,2,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB)&&!check_kills_ownplayer1(p,q,2,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB)){


  a = x-3; b = y-3;
  if(0<=a&&a<8&&b<8&&0<=b&&check_kills_ownplayer(a,b,1,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB)&&check_kills_ownplayer(a,b,2,curr_posB,curr_posA,soldierB,soldierA,curr_tA,curr_tB,townhallsA,townhallsB))
  {
    pair <lld,lld> xx ;
    xx.first = a;
    xx.second = b;
    can_be_killed.push_back(xx);
  }
              //---
}
  }
}
  return can_be_killed;
}

lld soldierattacking(lld player_number,lld soldier_selected,pair <lld,lld> curr_posA[], pair <lld,lld> curr_posB[],lld soldierB[],lld soldierA[],lld townhallsB[],lld townhallsA[]){
      vector <pair <lld,lld>> target = can_player_be_killed(player_number,soldier_selected,curr_posA,curr_posB,soldierB,soldierA,townhallsB,townhallsA);

      return target.size();
}


lld cannonattacking(lld player_number,lld soldier_selected,pair <lld,lld> curr_posA[], pair <lld,lld> curr_posB[],lld soldierB[],lld soldierA[],lld townhallsB[],lld townhallsA[]){

  lld i,j,k=0;
  if(player_number==1){
    vector <pair <lld,lld> > bomb = is_Cannon_formed(1,i,curr_posB,curr_posA,soldierB,soldierA);
    for(i=0;i<12;i++){
      for(j=0;j<bomb.size();j++){
        if(bomb[j].first == curr_posA[i].first && bomb[j].second == curr_posA[i].second){
          k++;
          break;
        }
      }
    }
    return k;
  }
  else{
    vector <pair <lld,lld> > bomb = is_Cannon_formed(2,i,curr_posB,curr_posA,soldierB,soldierA);
    for(i=0;i<12;i++){
      for(j=0;j<bomb.size();j++){
        if(bomb[j].first == curr_posB[i].first && bomb[j].second == curr_posB[i].second){
          k++;
          break;
        }
      }
    }
    return k;
  }
}
