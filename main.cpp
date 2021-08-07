#include <iostream>
#include <string>
#include <cstdlib>
#include <vector>
#include <unistd.h>
using namespace std;



void clear(){
  cout << "\033[2J\033[1;1H"; //Clear Console
}
void sleep(int n){
  unsigned int microsecond = 1000000;
  usleep(n * microsecond);//sleeps for n second
}

class Board{
     public:
          Board(){ //Constructor
               for (int i = 0; i < size/3; i++){
                    for (int j = 0; j < size/3; j++){
                         coords[i][j] = 2; //The teams will be 0 or 1.
                    }
               }
          }
          void set_coords(string& coord, int team){
               //Coord must be as the following example: "12" 1st row, 2nd column like matrix positions.
               int nums[3] = {1, 2, 3};
               string str_nums = "123";
               int row = nums[str_nums.find(coord[0])], col = nums[str_nums.find(coord[1])];
               coords[row - 1][col - 1] = team;
          }
          bool coord_in_board(string coord){
               int nums[3] = {1, 2, 3};
               string str_nums = "123";
               int row = nums[str_nums.find(coord[0])], col = nums[str_nums.find(coord[1])];
               if(coords[row - 1][col - 1] == 0 || coords[row - 1][col - 1] == 1)
                    return true;
               return false;
          }
          bool completed_board(){
               int cond = 0;
               for (int i = 0; i < size/3; i++){
                    for (int j = 0; j < size/3; j++){
                         if(coords[i][j] == 0 || coords[i][j] == 1)
                              cond++;
                    }
               }
               if(cond == size)
                    return true;
               return false;
          }
          bool winner(int team){
               
               for (int i = 0; i < size/3; i++){
                    for (int j = 0; j < size/3; j++){
                         int r_cond = 0, c_cond = 0, d_cond = 0;
                         if(coords[i][j] == team){
                              for (int col = 0; col < size / 3; col++){
                                   if(coords[i][col] == coords[i][j])
                                        r_cond++;
                              }
                              for (int row = 0; row < size / 3; row++){
                                   if(coords[row][j] == coords[i][j])
                                        c_cond++;
                                   
                              }
                              if(j != 1 || i != 1){
                                   if(i == j){
                                        for (int row = 0; row < size / 3; row++){
                                             if(coords[i+row][j+row] == coords[i][j])
                                                  d_cond += 1;
                                        }
                                   }
                                   else{
                                        for (int row = 0; row < size / 3; row++){
                                             if(coords[i+row][j-row] == coords[i][j])
                                                  d_cond += 1;
                                        }
                                   }
                                   
                              } 
                              if(r_cond == 3 || c_cond == 3 || d_cond == 3)
                                   return true;
                              
                         }
                    }
               }
               return false;
          }
          void print_board(){
               string indexes = "XO ";
               string space = "     ";
               cout << "  TIC TAC TOE" << endl;
               
               for (int i = 0; i < size / 3; i++){
                    cout << space;
                    for (int j = 0; j < size / 3; j++){
                         if(j < size/3 - 1){
                              
                              cout << indexes[coords[i][j]] << "|";
                         }
                         else
                              cout << indexes[coords[i][j]];
                    }
                    cout << endl;
                    cout << space;
                    if(i < size/3 - 1) cout << "- - -" << endl;
               }
               cout << endl;
          }

     private:
          const int size = 9;
          int coords[3][3];
};

int main(){
     Board board;
     int team = 0;
     vector<string> teams;
     teams.push_back("X");
     teams.push_back("O");
     cout << "Starting..." << endl;
     cout << "[**........] 20%" << endl;
     sleep(1);
     cout << "[*****.....] 50%" << endl;
     sleep(1);
     cout << "[********..] 80%" << endl;
     sleep(1);
     cout << "[**********] 100%";
     sleep(1);
     clear();
     while(!board.completed_board()){
          string coord;
          cout << "You are '" + teams[team] + "', write the coord(Ex. 12): ";
          cin >> coord;
          if (stoi(coord) > 33)
               cout << "The coord isn't valid, choose again!" << endl;
          else if(!board.coord_in_board(coord)){
               board.set_coords(coord, team);
               clear();
               board.print_board();
               if(board.winner(team)){
                    cout << "TIC TAC TOE! The '" + teams[team] + "' team has won." << endl;
                    break;
               }
               team++;
               team %= 2;
          }
          else
               cout << "The coord is chose, choose again! " << endl;
          
          }
     char str;
     cout << "The game has finished, 'p' for playing again: ";
     cin >> str;
     if(str == 'p')
          main();

     return 0;
}