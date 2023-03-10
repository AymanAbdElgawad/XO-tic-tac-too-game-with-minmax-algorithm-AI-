#include <iostream>
#include<cstdlib>
#include<time.h>

 using namespace std;
 
  struct Node{
    int data;
    Node* next;
};
class Rand {
   int size=0;
   Node* head=nullptr;
   
Node* add (int val) {
    Node* ptr=new Node;
    ptr->data=val;
    ptr->next=nullptr;
    size++;
    return ptr;
    }
    template <typename Val,typename ...Args>
Node*   add(Val val,Args ...args){
    Node* ptr=new Node;
    ptr->data=val;
    ptr->next=add(args...);
    size++;
    return ptr;
    }
    
    int    del (Node *before_del ,int i)
    {
       if (i==0){
             Node* temp;
            temp = before_del;
            head = temp->next;
        i=temp->data;
        delete temp;
        size--;
        return i;
            
           }
       else  if(i==1){
        Node* temp;
        temp = before_del->next;
        before_del->next = temp->next;
        i=temp->data;
        delete temp;
        size--;
        return i;
    }
   else return del(before_del->next,i-1);
    }
public:    
    template <typename Val,typename ...Args>
    Rand(Val val, Args ...args){
     Node* ptr=new Node;  ptr->data=val;
    ptr->next=add(args...);  size++;    
     head=ptr;
     }
     
      int range(int low,int high) {
          srand(time(NULL));
    return (rand()%((high+1)-low))+low;
    }
    
     int pop(){
            return del(head,range(0,size-1));
     }
    
    };

void printGui(int n,  string cha){
    for(int i=0; i < n ; i++ )cout<<cha;
}
 struct nod  { 
  int depth;
  int res;
  int move;
};
 
class XOboard{
   

    char board [9]={' ',' ',' ',' ',' ',' ',' ',' ',' '};
    string guichar="|";         
    int guin=26;
    int WS(char n1,char n2 , char n3);
    int min2 (int n) {return n;}
    template <typename stute,typename n1,              typename n2, typename n3,typename ...            args >
    int min2 (stute stu, n1 n11, n2 n22, n3 n33,       args... nums){
       int nstu=WS(board[n11], board[n22],                     board[n33]);
       if (nstu==2||nstu==0)return nstu;
       else if  (nstu>stu)stu=nstu;
       return min2(stu, nums...);
    }
    nod minsearch(int d);
    nod maxsearch(int d);  
  public: 
    int maxmin(int d);
    int minmax(int d);
    void print ();
    bool play(int box,char XorO);
    int stute();
   };

class XOgame
{
	XOboard board;
	int tern=2;	
    void playturn();
    void play();
    int AI(char XorO);
    bool check();
  public:	
    XOgame() {
	    printGui(7,"☆");
	    cout<<" wellcom to XO game ";
	    printGui(7,"☆");
	    cout <<"\n enter 1 to play first or 2 to play sacand : ";
	    char sel=' ';
	    cin>>sel ;
	    if (!(sel=='1'))tern++; 
	    board.print();
 	  playturn();
	 }	
};

int main()
{
  
 
  char c='y';
  while(c=='y'){
    XOgame game;
    cout<<"\n game over \n play again? y or n \n";
    cin>>c;
  }
	return 0;
}

void XOboard::print (){
   cout<<"\n";
   printGui(13+(guin*2),guichar);
   for (int i=0; i<9 ; i++){
      if (i==0){
         cout<<"\n";
         printGui(guin,guichar);
         cout<<"|";
       }
    else  if (i%3==0){
        printGui(guin,guichar);
        cout<<"\n";
        printGui(guin,guichar);
        cout<<"|---|---|---|";
        printGui(guin,guichar);
        cout<<"\n";
        printGui(guin,guichar);
        cout<<"|";
      }
   cout <<" "<<board[i]<<" |";
  }   
 printGui(guin,guichar); 
 cout<<"\n";
 printGui(13+(guin*2),guichar); 
 cout<<"\n";
}

bool XOboard::play(int box,char XorO){
      if (!(board[box]==' '))  return true;
      board[box]=XorO;
      return false;
}
      
int XOboard::WS(char n1,char n2 , char n3){
        int r=1;
        if (n1== ' ' || n2==' ' || n3==' ')r=3;
        else if (n1=='X' && n2=='X' && n3=='X')r=0;
        else if (n1=='O' && n2=='O' && n3=='O')r=2;
        return r;
}

int XOboard::stute(){
    return min2(1,    0,1,2,     3,4,5,    6,7,8,
                                   0,3,6,    1,4,7,    2,5,8,
                                    0,4,8,    2,4,6   );    
}
 
int XOboard::minmax(int d){
     nod stu;
     stu.depth=d;
     stu.res=1000;
     int move =0;
     Rand rand(0,1,2,3,4,5,6,7,8);
     cout<<"\n  ";
     for (int l=0; l<9;l++){
         int i=rand.pop();
         if (play(i,'X'))continue;
         nod temp =maxsearch(d-1);
         board[i]=' ';
        cout<<"("<<i+1<<":"<<temp.res<<":"<<d-temp.depth<<")      ";                         
         if(temp.res<stu.res){
             stu=temp;
             move=i+1;
           }
           else if (temp.res==stu.res){
             if(temp.res==0){
                      if (temp.depth>stu.depth){
                    stu=temp;
                     move=i+1;
                   }
             }
             if (temp.res==2){
               if (temp.depth<stu.depth){
                    stu=temp;
                     move=i+1;
                   }
                      else if (temp.depth==stu.depth)move=temp.move;
               }
               }
       
     }
       cout<<"\n";
   return move;
}

int XOboard::maxmin(int d){
     nod stu;
     stu.depth=d;
     stu.res=-1000;
     int move =0;
        Rand rand(0,1,2,3,4,5,6,7,8);  
        cout<<"\n  ";
     for (int l=0; l<9;l++){
         int i=rand.pop();
         if (play(i,'O'))continue;
         nod temp =minsearch(d-1);
         board[i]=' ';
        cout<<"("<<i+1<<":"<<temp.res<<":"<<d-temp.depth<<")      ";                         
         if(temp.res>stu.res){
             stu=temp;
             move=i+1;
           }
             else if (temp.res==stu.res){
             if(temp.res==0){
                      if (temp.depth<stu.depth){
                    stu=temp;
                     move=i+1;
                   }
                   else if (temp.depth==stu.depth)move=temp.move;
             }
             if (temp.res==2){
               if (temp.depth>stu.depth){
                    stu=temp;
                     move=i+1;
                   }
               }
               }
       
     }
       cout<<"\n";
   return move;
 }
 
nod XOboard::minsearch(int d ){
    nod n;
    n.depth=d;
    if(d<1){
        n.res=1;
        return n; }
    int stu=stute();
    if(!(stu==3)){
        n.res=stu;
        return n;}
    n.res=1000;
    
     Rand rand(0,1,2,3,4,5,6,7,8);
     for (int l=0; l<9;l++){
         int i=rand.pop();
         if (play(i,'X'))continue;
         nod n2=maxsearch(d-1);
          n2.move=i+1;
         board[i]=' ';
         if(n2.res==0&&n2.depth==d-1)return n2;
        if(n.res>n2.res) n=n2; 
        else if (n.res==n2.res){
 if(n.res==0){
       if(n2.depth>n.depth)n=n2;  
            }
            if(n.res==2){
       if(n2.depth<n.depth)n=n2;  
            }
         }
               }
     return n;
}
 
nod XOboard::maxsearch(int d ){
     nod n;
    n.depth=d;
    if(d==0){
        n.res=1;
        return n; }
    int stu=stute();
    if(!(stu==3)){
        n.res=stu;
        return n;}
    n.res=-1000;
    
        Rand rand(0,1,2,3,4,5,6,7,8);
     for (int l=0; l<9;l++){
         int i=rand.pop();
         if (play(i,'O'))continue;
         nod n2=minsearch(d-1);
         n2.move=i+1;
         board[i]=' ';
         if(n2.res==2&&n2.depth==d-1)return n2;
        if(n.res<n2.res) n=n2;
        else if (n.res==n2.res){
            if(n.res==0){
       if(n2.depth<n.depth)n=n2;  
            }
             if (n.res==2){
       if(n2.depth>n.depth)n=n2;  
            }
            
         }
               }
     return n;
}

void XOgame::playturn(){
    play();
    board.print();
    if (check())playturn();
}
    
bool XOgame::check(){
        int stute=8888;
    stute= board.stute();
    if (stute==3) return true;
    else {
        cout<<"\n";
        printGui(3,"☆");
        if (stute==0)cout<<" Win ";
       
        else  if (stute==2)cout<<" Lost ";
        else  if (stute==1)cout<<" Draw ";
         printGui(3,"☆");
        return false;
        }
}
    
int XOgame::AI(char XorO){
          int best;
          if(XorO=='O') best =  board.maxmin(5);
         else best=board.minmax(9);
         cout<<"\nbest move is: "<<best<<"\n";    
     	return best-1;
}

void XOgame::play(){
    if (tern%2==0){
        cout << "\n it is your tern \n enter box number to play : ";
        int box=0;
        AI('X');
   cin>>box;
        
       if (board.play(  box-1 ,'X')){
      cout<<"\n Error enter nuber of empty box:";
      play();
     }
       else tern++;
   }
    else {
        cout <<"\n it is comuter tern ples weit....";
            cout<<"\n best move is box N :";           
     if(  board.play(AI('O'),'O'))play();    
      else   tern++;     
          }
}