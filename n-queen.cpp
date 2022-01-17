#include<bits/stdc++.h>
using namespace std;
#include <stdlib.h>


int N=12;//Size of the Board




// Class board that contains info about the one state of the board which are position of queens and  state evaluation
class board{
    // in_line function returns 1 if two queens atteck each other and 0 
    int in_line(int x1,int y1,int x2,int y2){
            if (x1==x2 && y1==y2){
                return 0;
            }
        else if(x1==x2 || y1==y2){
            return 1;
        }
        else if(abs((float)(x1-x2))/abs((float)(y1-y2))==1){
            return 1;
        }
        else return 0;
        }
    public:
        
        vector <pair<int,int>> positions;//stores coordinates of queens
        int eval; //stores number of pairs of queens attacking each other
        

        //this function calculates the number of queens attacking each other
        void evaluate(){
        int num=0;
        for(int i =0;i<N;i++){
            int x1,y1;
            x1=positions[i].first;
            y1=positions[i].second;
            for(int j=0;j<N;j++){
                if(i==j)continue;
                int x2,y2;
                x2=positions[j].first;
                y2=positions[j].second;
                num += in_line(x1,y1,x2,y2);
            }
        }
        eval=num;
        }

        //this function prints the coordinates of the queens in present state and the number of pairs attacking each other
        void print_state(){
            for(int i=0;i<N;i++){
                cout<<positions[i].first<<" "<<positions[i].second<<"\n";
            }
            cout<<eval<<"\n";
        }

        // this function generates a random position of queens for this state. One constraint on this random generation is that one row(called a 'rank' in chess) can have only one queen 
        void randomize(){
            positions.clear();
            for (int i=0;i<N;i++){
                int pos=rand()%N;

                positions.push_back({i,pos});
            }
        }


        //this function prints the board in a nice NxN grid , just like a chess board, with 1 on the coordinates where there is a queen and 0 everywhere else.
        void print_board(){
            int board[N][N];
            for(int i=0;i<N;i++){
                for(int j=0;j<N;j++){
                    board[i][j]=0;
                }
            }
            for(int i=0;i<N;i++){
                board[positions[i].first][positions[i].second]=1;
            }
            for(int i=0;i<N;i++){
                for(int j=0;j<N;j++){
                    cout<<board[i][j]<<" ";
                }
                cout<<"\n";
            }
        }
};


board state;//initializing object of class board , which at every iteration will store the info about the state on which we are currently present


vector <board> neighbouring_states;
//vector arrray of objects of class board which will , at every iteration , store all the neighbouring states to our current state. Two states are considered
//neighbouring states if they differ in  position of only one queen.Thus for a state having N queens total number of neighbours is N*(N-1)



//this function generates all the neighbours of our current state and stores them in the neighbouring_states vector
void neighbours(vector<board>& neighbouring_states, int N,board state){
    int posi = rand()%N;
    for(int a =0;a<N;a++){
        int k=(posi+a)%N;
        int old_y=state.positions[k].second;
        for(int j=1;j<N;j++){
            int new_y =(old_y+j)%N;
            board new_state = state;
            
            new_state.positions[k].second=new_y;
            new_state.evaluate();
            
            
            neighbouring_states.push_back(new_state);
            
        }
        
    }
}


int main(){

    srand(time(0));//seeding the random function with current time
    
    state.randomize();//generating a random initial state
    state.evaluate();//evaluating number of pairs attacking each other and storing it in the object variable eval
    
    int counter=0;//intitializing a counter which will keep track of the number of iteration of while loop. After each iteration of the while loop we take the 
    //If the while loop runs more than N*N number of times then then the current state again gets randomized and the counter is set to zero. With this approch we can easily escape local minima 
    
    while(state.eval!=0){
       
       neighbouring_states.clear();

       if(counter>N*N){

           state.randomize();
           state.evaluate();
           
           counter=0;
       }
       counter++;
       neighbours(neighbouring_states,N,state);
       int siz=neighbouring_states.size();
       for(int i=0;i<siz;i++){
           if(neighbouring_states[i].eval<state.eval){
               state=neighbouring_states[i];
           }
       }
        
    }
    state.print_board();//prints the answer board
}





