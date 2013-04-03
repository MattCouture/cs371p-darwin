#include <cassert> // assert
#include <cstdlib> // rand, srand
#include <iostream> // cout, endl
#include <vector>
#include <string>
#include <stdexcept> // invalid_argument, out_of_range


using namespace std;


class Creature {    
 public:
   string species;
   int direction, programCounter;
   bool turnEnd;
  
   string foodProgram[2];
   string hopperProgram[2];
   string roverProgram[11];
   string trapProgram[5];
   string bestProgram[13];

   // West = 0, North = 1, East = 2, South = 4

   Creature() {species = "null";}

   Creature(int direc, string type) {
     programCounter = 0;
     species = type;
     direction = direc;
    
//     foodProgram
       foodProgram[0] = "left"; foodProgram[1] = "go 0";
//     hopperProgram
       hopperProgram[0] = "hop"; hopperProgram[1] = "go 0";
//     roverProgram
       roverProgram[0] = "if_enemy 9"; roverProgram[1] = "if_empty 7"; roverProgram[2] = "if_random 5"; roverProgram[3] = "left"; roverProgram[4] = "go 0";
       roverProgram[5] = "right"; roverProgram[6] = "go 0"; roverProgram[7] = "hop"; roverProgram[8] = "go 0"; roverProgram[9] = "infect"; roverProgram[10] = "go 0";
//     trapProgram
       trapProgram[0] = "if_enemy 3"; trapProgram[1] = "left"; trapProgram[2] = "go 0"; trapProgram[3] = "infect"; trapProgram[4] = "go 0";
//     bestProgram
//       bestProgram[0] = "if_enemy 3"; bestProgram[1] = "left"; bestProgram[2] = "go 0"; bestProgram[3] = "infect"; bestProgram[4] = "go 0";
       bestProgram[0] = "if_enemy 11"; bestProgram[1] = "if_wall 4"; bestProgram[2] = "if_empty 9"; bestProgram[3] = "go 7"; bestProgram[4] = "if_random 7"; 
       bestProgram[5] = "left"; bestProgram[6] = "go 0"; bestProgram[7] = "right"; bestProgram[8] = "go 0"; bestProgram[9] = "hop"; bestProgram[10] = "go 0";
       bestProgram[11] = "infect"; bestProgram[12] = "go 0";

     }

   string turn() {
     string instruction;
     if(species.compare("Food") == 0) {
       instruction = foodProgram[programCounter];
     }
     else if(species.compare("Hopper") == 0) {
       instruction = hopperProgram[programCounter];
     }
     else if(species.compare("Rover") == 0) {
       instruction = roverProgram[programCounter];
     } 
     else if(species.compare("Trap") == 0) {
       instruction = trapProgram[programCounter];
     }
     else if(species.compare("Best") == 0) {
       instruction = bestProgram[programCounter];
     }
     return instruction;
   }

};


class World {
  vector<Creature> cols;
  vector<vector<Creature> > grid;


  public:
  World(int row, int col) {
    cols.resize(col);
    vector<vector<Creature> > g(row, cols);
    grid = g;
  }

  void addCreature(string type, int d, int r, int c) {
    Creature cr = Creature(d, type);
    grid[r][c] = cr;
  }

  bool isWall(int r, int c, int d) {
    if((d == 0 && c == 0) || (d == 1 && r == 0) || (d == 2 && c == (int)grid[0].size() - 1) || (d == 3 && r == (int)grid.size() - 1)) {
      return true;}
    return false;
  }

  bool isEmpty(int r, int c, int d) {
    if(isWall(r, c, d)) {
      return false;}
    if((d == 0 && grid[r][c - 1].species.compare("null") == 0) || (d == 1 && grid[r - 1][c].species.compare("null") == 0) || (d == 2 && grid[r][c + 1].species.compare("null") == 0) || (d == 3 && grid[r + 1][c].species.compare("null") == 0)) {
      return true;}
    return false;
  }

  bool isEnemy(int r, int c, int d) {
    string str = grid[r][c].species;
    if(isWall(r, c, d) || isEmpty(r, c, d)) {
      return false;}
    if((d == 0 && grid[r][c - 1].species.compare(str) == 0) || (d == 1 && grid[r - 1][c].species.compare(str) == 0) || (d == 2 && grid[r][c + 1].species.compare(str) == 0) || (d == 3 && grid[r + 1][c].species.compare(str) == 0)) {
      return false;}
    return true;
  }

  bool creatureExists(int col, int row) {
    if(grid[row][col].species.compare("null") == 0) {
      return false;}
    return true;
  }

  void takeTurn() {
    string ins;
    for(int y = 0; y < (int)grid.size(); ++y) {
      for(int x = 0; x < (int)grid[0].size(); ++x) {
        grid[y][x].turnEnd = false;}}
    for(int y = 0; y < (int)grid[0].size(); ++y) {
      for(int x = 0; x < (int)grid.size(); ++x) {
        if(creatureExists(y, x)) {
          while(grid[x][y].turnEnd == false){
          ins = grid[x][y].turn();
          
          if(ins.compare("hop") == 0) {
            if(isEmpty(x, y, grid[x][y].direction)) {
              
              if(grid[x][y].direction == 0) {
                grid[x][y - 1] = grid[x][y];
                grid[x][y].species = "null";
                ++grid[x][y - 1].programCounter;
                grid[x][y - 1].turnEnd = true;
              }
              else if(grid[x][y].direction == 1) {
                grid[x - 1][y] = grid[x][y];
                grid[x][y].species = "null";
                ++grid[x - 1][y].programCounter;
                grid[x - 1][y].turnEnd = true;
              }
              else if(grid[x][y].direction == 2) {
                grid[x][y + 1] = grid[x][y];
                grid[x][y].species = "null";
                ++grid[x][y + 1].programCounter;
                grid[x][y + 1].turnEnd = true;
              }

              else if(grid[x][y].direction == 3) {
                grid[x + 1][y] = grid[x][y];
                grid[x][y].species = "null";
                ++grid[x + 1][y].programCounter;
                grid[x + 1][y].turnEnd = true;
              }
             }

              ++grid[x][y].programCounter;
              grid[x][y].turnEnd = true;
               
          }

          else if(ins.compare("left") == 0) {
            if(grid[x][y].direction == 0) {
              grid[x][y].direction = 3;}
            else if(grid[x][y].direction == 1) {
              grid[x][y].direction = 0;}
            else if(grid[x][y].direction == 2) {
              grid[x][y].direction = 1;}
            else if(grid[x][y].direction == 3) {
              grid[x][y].direction = 2;}
            ++grid[x][y].programCounter;
            grid[x][y].turnEnd = true;
          }

         else if(ins.compare("right") == 0) {
            if(grid[x][y].direction == 0) {
              grid[x][y].direction = 1;}
            else if(grid[x][y].direction == 1) {
              grid[x][y].direction = 2;}
            else if(grid[x][y].direction == 2) {
              grid[x][y].direction = 3;}
            else if(grid[x][y].direction == 3) {
              grid[x][y].direction = 0;}
            ++grid[x][y].programCounter;
            grid[x][y].turnEnd = true;
          }

        else if(ins.compare("infect") == 0) {
          if(isEnemy(x, y, grid[x][y].direction)) {
              if(grid[x][y].direction == 0) {
                grid[x][y - 1].species = grid[x][y].species;
                grid[x][y - 1].programCounter = 0;
              }
              else if(grid[x][y].direction == 1) {
                grid[x - 1][y].species = grid[x][y].species;
                grid[x - 1][y].programCounter = 0;
              }
              else if(grid[x][y].direction == 2) {
                grid[x][y + 1].species = grid[x][y].species;
                grid[x][y + 1].programCounter = 0;
              }
              else if(grid[x][y].direction == 3) {
                grid[x + 1][y].species = grid[x][y].species;
                grid[x + 1][y].programCounter = 0;
              }  
          }
          ++grid[x][y].programCounter;
          grid[x][y].turnEnd = true;
        }

        else if(ins.substr(0, 8).compare("if_empty") == 0) {
          if(isEmpty(x, y, grid[x][y].direction)) {
            int line = std::stoi(ins.substr(9));
            grid[x][y].programCounter = line;
          }  
          else{ ++grid[x][y].programCounter; }
        }        


        else if(ins.substr(0, 7).compare("if_wall") == 0) {
          if(isWall(x, y, grid[x][y].direction)) {
            int line = std::stoi(ins.substr(8));
            grid[x][y].programCounter = line;
          }
          else{ ++grid[x][y].programCounter; }
        }
      
        else if(ins.substr(0, 9).compare("if_random") == 0) {
          if(rand() % 2 != 0) {
            int line = std::stoi(ins.substr(10));
            grid[x][y].programCounter = line;
          }
          else{ ++grid[x][y].programCounter; }
        }


         else if(ins.substr(0, 8).compare("if_enemy") == 0) {
          if(isEnemy(x, y, grid[x][y].direction)) {
            int line = std::stoi(ins.substr(9));
            grid[x][y].programCounter = line;
         }
          else{ ++grid[x][y].programCounter; }
         }

        else if(ins.substr(0, 2).compare("go") == 0) {
          int line = std::stoi(ins.substr(3));
          grid[x][y].programCounter = line;
        }


        }
      }
    }
  }
}

  void print() {
     int count = 0;
     cout << "  ";
     for(int x = 0; x < (int)grid[0].size(); ++x) {
       if(count > 9) {
         count = 0;}
       cout << count;
       ++count;
     } 
     cout << "\n";
     count = 0;

     for(int y = 0; y < (int)grid.size(); ++y) {
       if(count > 9) {
         count = 0;}
       cout << count << " ";
       ++count;
       for(int x = 0; x < (int)grid[0].size(); ++x) {
         if(grid[y][x].species.compare("Food") == 0)
		cout << "f";
         else if(grid[y][x].species.compare("Hopper") == 0)
                cout << "h";
	 else if(grid[y][x].species.compare("Rover") == 0)
                cout << "r";
	 else if(grid[y][x].species.compare("Trap") == 0)
                cout << "t";
         else if(grid[y][x].species.compare("Best") == 0)
		cout << "b";
         else
		cout << ".";
       }
       cout << "\n";
     }

  }

};
