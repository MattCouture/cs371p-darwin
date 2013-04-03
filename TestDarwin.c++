
// --------
// includes
// --------

#include <algorithm> // count
#include <iostream> // ios_base
#include <memory> // allocator
#include <string>

#include "cppunit/extensions/HelperMacros.h" // CPPUNIT_TEST, CPPUNIT_TEST_SUITE, CPPUNIT_TEST_SUITE_END
#include "cppunit/TestFixture.h" // TestFixture
#include "cppunit/TextTestRunner.h" // TestRunner

#define private public
#define protected public
#define class struct

#include "Darwin.c++"

// -------------
// TestAllocator
// -------------

struct TestDarwin : CppUnit::TestFixture {

    // --------
    // test Creature Constructor
    // --------

    void test_creatureConstruct() {
      Creature c = Creature();
      assert (c.species.compare("null") == 0);
    }
    
    // --------
    // test Creature Constructor 2
    // --------

    void test_creatureConstruct1() {
      Creature c = Creature(0, "Trap");
      assert(c.species.compare("Trap") == 0);
      assert(c.direction == 0);
      assert(c.programCounter == 0);
    }  
    void test_creatureConstruct2() {
      Creature c = Creature(1, "Rover");
      assert(c.species.compare("Rover") == 0);
      assert(c.direction == 1);
      assert(c.programCounter == 0);
    }
    void test_creatureConstruct3() {
      Creature c = Creature(3, "Hopper");
      assert(c.species.compare("Hopper") == 0);
      assert(c.direction == 3);
      assert(c.programCounter == 0);
    }
    void test_creatureConstruct4() {
      Creature c = Creature(2, "Food");
      assert(c.species.compare("Food") == 0);
      assert(c.direction == 2);
      assert(c.programCounter == 0);
    }

    // -------
    // test turn
    // -------
    
    void test_turn1() {
      Creature c = Creature(1, "Hopper");
      string ins = c.turn();
      assert(ins.compare("hop") == 0);
    }     
    void test_turn2() {
      Creature c = Creature(1, "Rover");
      string ins = c.turn();
      assert(ins.compare("if_enemy 9") == 0);
    }
    void test_turn3() {
      Creature c = Creature(1, "Trap");
      c.programCounter = 2;
      string ins = c.turn();
      assert(ins.compare("go 0") == 0);
    }

    // --------
    // test World Constructor
    // --------
 
    void test_worldConstruct1() {
      World w = World(8, 8);
      assert(w.cols.size() == 8);
      assert(w.grid[0].size() == 8); 
    }
    void test_worldConstruct2() {
      World w = World(7, 9);
      assert(w.cols.size() == 9);
      assert(w.grid[0].size() == 9);
    }
    void test_worldConstruct3() {
      World w = World(72, 72);
      assert(w.cols.size() == 72);
      assert(w.grid[0].size() == 72);
    }
    

    // --------
    // test_addCreature
    // --------

    void test_addCreature1() {
      World  w = World(8, 8);
      w.addCreature("Hopper", 0, 3, 3);
      assert(w.grid[3][3].species.compare("Hopper") == 0);
      assert(w.grid[3][3].direction == 0);
    } 
    void test_addCreature2() {
      World  w = World(8, 8);
      w.addCreature("Rover", 3, 7, 7);
      assert(w.grid[7][7].species.compare("Rover") == 0);
      assert(w.grid[7][7].direction == 3);
    }
    void test_addCreature3() {
      World  w = World(8, 8);
      w.addCreature("Trap", 1, 2, 4);
      assert(w.grid[2][4].species.compare("Trap") == 0);
      assert(w.grid[2][4].direction == 1);
    }
 
    // -------
    // test isWall
    // -------

    void test_isWall1() {
      World w = World(8, 8);
      bool b = w.isWall(0, 0, 0);
      assert(b == true);
    }     
    void test_isWall2() {
      World w = World(8, 8);
      bool b = w.isWall(0, 7, 2);
      assert(b == true);
    }
    void test_isWall3() {
      World w = World(8, 8);
      bool b = w.isWall(4, 4, 1);
      assert(b == false);
    }

    // --------
    // test isEmpty
    // --------
    
    void test_isEmpty1() {
      World w = World(8, 8);
      bool b = w.isEmpty(0, 0, 0);
      assert(b == false);
    }
    void test_isEmpty2() {
      World w = World(8, 8);
      bool b = w.isEmpty(4, 0, 1);
      assert(b == true);
    }
    void test_isEmpty3() {
      World w = World(8, 8);
      w.addCreature("Food", 0, 0, 1);
      bool b = w.isEmpty(1, 1, 1);
      assert(b == false);
    }

    // ---------
    // test isEnemy
    // ---------
    
    void test_isEnemy1() {
      World w = World(8, 8);
      bool b = w.isEnemy(0, 0, 0);
      assert(b == false);
    }
    void test_isEnemy2() {
      World w = World(8, 8);
      w.addCreature("Hopper", 0, 0, 1);
      w.addCreature("Food", 1, 1, 1);
      bool b = w.isEnemy(1, 1, 1);
      assert(b == true);
    }
    void test_isEnemy3() {
      World w = World(8, 8);
      w.addCreature("Food", 0, 0, 1);
      w.addCreature("Food", 1, 1, 1);
      bool b = w.isEnemy(1, 1, 1);
      assert(b == false);
    }


    // ---------
    // test creatureExists
    // ---------
   
    void test_creatureExists1() {
      World w = World(8, 8);
      bool b = w.creatureExists(0, 0);
      assert(b == false);
    }
    void test_creatureExists2() {
      World w = World(8, 8); 
      w.addCreature("Food", 0, 0, 0);
      bool b = w.creatureExists(0, 0);
      assert(b == true);
    }
    void test_creatureExists3() {
      World w = World(8, 8);
      w.addCreature("Food", 0, 3, 4);
      bool b = w.creatureExists(4, 3);
      assert(b == true);
    }

    // ---------
    // test takeTurn
    // ---------

    void test_takeTurn1() {
      World w = World(8, 8);
      w.addCreature("Food", 0, 1, 1);
      w.takeTurn();
      assert(w.grid[1][1].direction == 3);
      assert(w.grid[1][1].programCounter == 1);
      assert(w.grid[1][1].turnEnd == true);
    }
    void test_takeTurn2() {
      World w = World(8, 8);
      w.addCreature("Hopper", 0, 1, 1);
      w.takeTurn();
      assert(w.grid[1][1].species.compare("null") == 0);
      assert(w.grid[1][0].species.compare("Hopper") == 0);
      assert(w.grid[1][0].turnEnd == true);
      assert(w.grid[1][0].programCounter == 1);
      assert(w.grid[1][0].direction == 0);
    }
    void test_takeTurn3() {
      World w = World(8, 8);
      w.addCreature("Rover", 0, 1, 1);
      w.takeTurn();
      assert(w.grid[1][1].species.compare("null") == 0);
      assert(w.grid[1][0].species.compare("Rover") == 0);
      assert(w.grid[1][0].turnEnd == true);
      assert(w.grid[1][0].programCounter == 8);
      assert(w.grid[1][0].direction == 0);
    }


    CPPUNIT_TEST_SUITE(TestDarwin);

    CPPUNIT_TEST(test_creatureConstruct);
    CPPUNIT_TEST(test_creatureConstruct1);
    CPPUNIT_TEST(test_creatureConstruct2);
    CPPUNIT_TEST(test_creatureConstruct3);
    CPPUNIT_TEST(test_creatureConstruct4);
    CPPUNIT_TEST(test_turn1);
    CPPUNIT_TEST(test_turn2);
    CPPUNIT_TEST(test_turn3);
    CPPUNIT_TEST(test_worldConstruct1);
    CPPUNIT_TEST(test_worldConstruct2);
    CPPUNIT_TEST(test_worldConstruct3);
    CPPUNIT_TEST(test_addCreature1);
    CPPUNIT_TEST(test_addCreature2);
    CPPUNIT_TEST(test_addCreature3);
    CPPUNIT_TEST(test_isWall1);
    CPPUNIT_TEST(test_isWall2);
    CPPUNIT_TEST(test_isWall3);
    CPPUNIT_TEST(test_isEmpty1);
    CPPUNIT_TEST(test_isEmpty2);
    CPPUNIT_TEST(test_isEmpty3);
    CPPUNIT_TEST(test_isEnemy1);
    CPPUNIT_TEST(test_isEnemy2);
    CPPUNIT_TEST(test_isEnemy3);
    CPPUNIT_TEST(test_creatureExists1);
    CPPUNIT_TEST(test_creatureExists2);
    CPPUNIT_TEST(test_creatureExists3);
    CPPUNIT_TEST(test_takeTurn1); 
    CPPUNIT_TEST(test_takeTurn2);
    CPPUNIT_TEST(test_takeTurn3);

    CPPUNIT_TEST_SUITE_END();};

// ----
// main
// ----

int main () {
    using namespace std;
    ios_base::sync_with_stdio(false); // turn off synchronization with C I/O
    cout << "TestDarwin.c++" << endl;

    CppUnit::TextTestRunner tr;

    tr.addTest(TestDarwin::suite());

    tr.run();

    cout << "Done." << endl;
    return 0;}
