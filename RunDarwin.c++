// -----------------------------
// projects/darwin/RunDarwin.c++
// Copyright (C) 2013
// Glenn P. Downing
// -----------------------------

/*
To run the program:
% g++ -pedantic -std=c++0x -Wall RunCollatz.c++ -o RunCollatz.c++.app
% valgrind RunDarwin.c++.app > RunDarwin.out

To configure Doxygen:
doxygen -g
That creates the file Doxyfile.
Make the following edits:
EXTRACT_ALL = YES
EXTRACT_PRIVATE = YES
EXTRACT_STATIC = YES
GENERATE_LATEX = NO

To document the program:
doxygen Doxyfile
*/

// --------
// includes
// --------

#include <cassert> // assert
#include <cstdlib> // rand, srand
#include <iostream> // cout, endl
#include <stdexcept> // invalid_argument, out_of_range

#include "Darwin.c++"

// ----
// main
// ----

int main () {
    using namespace std;
    ios_base::sync_with_stdio(false); // turn off synchronization with C I/O

    // ----
    // food
    // ----

    /*
0: left
1: go 0
*/

    // ------
    // hopper
    // ------

    /*
0: hop
1: go 0
*/

    // -----
    // rover
    // -----

    /*
0: if_enemy 9
1: if_empty 7
2: if_random 5
3: left
4: go 0
5: right
6: go 0
7: hop
8: go 0
9: infect
10: go 0
*/

    // ----
    // trap
    // ----

    /*
0: if_enemy 3
1: left
2: go 0
3: infect
4: go 0
*/

    // ----------
    // darwin 8x8
    // ----------

    try {
        cout << "*** Darwin 8x8 ***" << endl;

        World w = World(8, 8);
        w.addCreature("Food", 2, 0, 0);
        w.addCreature("Hopper", 1, 3, 3);
        w.addCreature("Hopper", 2, 3, 4);
        w.addCreature("Hopper", 3, 4, 4);
        w.addCreature("Hopper", 0, 4, 3);
        w.addCreature("Food", 1, 7, 7);
        
        cout << "Turn = 0." << endl;
        w.print();
        w.takeTurn();
        cout << "Turn = 1." << endl;
        w.print();
        w.takeTurn(); 
        cout << "Turn = 2." << endl;
        w.print();
        w.takeTurn();
        cout << "Turn = 3." << endl;
        w.print();
        w.takeTurn();
        cout << "Turn = 4." << endl;
        w.print();
        w.takeTurn();
        cout << "Turn = 5." << endl;
        w.print();
        /*
8x8 Darwin
Food, facing east, at (0, 0)
Hopper, facing north, at (3, 3)
Hopper, facing east, at (3, 4)
Hopper, facing south, at (4, 4)
Hopper, facing west, at (4, 3)
Food, facing north, at (7, 7)
Simulate 5 moves.
Print every grid.
*/
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}


    // ----------
    // darwin 7x9
    // ----------

    try {
        cout << "*** Darwin 7x9 ***" << endl;
        srand(0);

        World w2 = World(7, 9);
        w2.addCreature("Trap", 3, 0, 0);
        w2.addCreature("Hopper", 2, 3, 2);
        w2.addCreature("Rover", 1, 5, 4);
        w2.addCreature("Trap", 0, 6, 8);
       
        cout << "Turn = 0." << endl;
        w2.print();
        w2.takeTurn();
        cout << "Turn = 1." << endl;
        w2.print();
        w2.takeTurn();
        cout << "Turn = 2." << endl;
        w2.print();
        w2.takeTurn();
        cout << "Turn = 3." << endl;
        w2.print();
        w2.takeTurn();
        cout << "Turn = 4." << endl;
        w2.print();
        w2.takeTurn();
        cout << "Turn = 5." << endl;
        w2.print();


        /*
7x9 Darwin
Trap, facing south, at (0, 0)
Hopper, facing east, at (3, 2)
Rover, facing north, at (5, 4)
Trap, facing west, at (6, 8)
Simulate 5 moves.
Print every grid.
*/
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}
/*
     World w = World(3, 3);
     w.addCreature("Rover", 0, 2, 0);
     for(int y = 0; y < 10; ++y) {
        cout << "Turn " << y+1 <<endl;
        w.takeTurn();}
     w.print();
*/




    // ------------
    // darwin 72x72
    // without best
    // ------------

    try {
        cout << "*** Darwin 72x72 without Best ***" << endl;
        srand(0);
        World w3 = World(72, 72);
        int i, d, r, c;
        for(int y = 0; y < 10; ++y) {
          i = rand() % 5184;
          d = rand() % 4;
          r = i / 72;
          c = i % 72;
          w3.addCreature("Food", d, r, c);
        }
        for(int y = 0; y < 10; ++y) {
          i = rand() % 5184;
          d = rand() % 4;
          r = i / 72;
          c = i % 72;
          w3.addCreature("Hopper", d, r, c);
        }
        for(int y = 0; y < 10; ++y) {
          i = rand() % 5184;
          d = rand() % 4;
          r = i / 72;
          c = i % 72;
          w3.addCreature("Rover", d, r, c);
        }
        for(int y = 0; y < 10; ++y) {
          i = rand() % 5184;
          d = rand() % 4;
          r = i / 72;
          c = i % 72;
          w3.addCreature("Trap", d, r, c);
        }
        cout << "Turn = 0." << endl;
        w3.print();
        for(int x = 1; x < 1001; ++x) {
          w3.takeTurn();
          if(x % 100 == 0) {
            cout << "Turn = " << x << "." << endl;
            w3.print();
          }
        }


        /*
Randomly place the following creatures facing randomly.
Call rand(), mod it with 5184 (72x72), and use that for the position
in a row-major order grid.
Call rand() again, mod it with 4 and use that for it's direction with
the ordering: west, north, east, south.
Do that for each kind of creature.
10 Food
10 Hopper
10 Rover
10 Trap
Simulate 1000 moves.
Print every 100th grid.
*/

        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    // ------------
    // darwin 72x72
    // with best
    // ------------

    try {
        cout << "*** Darwin 72x72 with Best ***" << endl;
        srand(0);
        World w4 = World(72, 72);
        int i, d, r, c;
        for(int y = 0; y < 10; ++y) {
          i = rand() % 5184;
          d = rand() % 4;
          r = i / 72;
          c = i % 72;
          w4.addCreature("Food", d, r, c);
        }
        for(int y = 0; y < 10; ++y) {
          i = rand() % 5184;
          d = rand() % 4;
          r = i / 72;
          c = i % 72;
          w4.addCreature("Hopper", d, r, c);
        }
        for(int y = 0; y < 10; ++y) {
          i = rand() % 5184;
          d = rand() % 4;
          r = i / 72;
          c = i % 72;
          w4.addCreature("Rover", d, r, c);
        }
        for(int y = 0; y < 10; ++y) {
          i = rand() % 5184;
          d = rand() % 4;
          r = i / 72;
          c = i % 72;
          w4.addCreature("Trap", d, r, c);
        }
        for(int y = 0; y < 10; ++y) {
          i = rand() % 5184;
          d = rand() % 4;
          r = i / 72;
          c = i % 72;
          w4.addCreature("Best", d, r, c);
        }
        cout << "Turn = 0." << endl;
        w4.print();
        for(int x = 1; x < 1001; ++x) {
          w4.takeTurn();
          if(x % 100 == 0) {
            cout << "Turn = " << x << "." << endl;
            w4.print();
          }
        }

        /*
Randomly place the following creatures facing randomly.
Call rand(), mod it with 5184 (72x72), and use that for the position
in a row-major order grid.
Call rand() again, mod it with 4 and use that for it's direction with
the ordering: 0:west, 1:north, 2:east, 3:south.
Do that for each kind of creature.
10 Food
10 Hopper
10 Rover
10 Trap
10 Best
Simulate 1000 moves.
Best MUST outnumber ALL other species for the bonus pts.
Print every 100th grid.
*/
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    return 0;}
