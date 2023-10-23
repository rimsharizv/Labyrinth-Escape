#include <utility>
#include <random>
#include <set>
#include "grid.h"
#include "maze.h"
using namespace std;

/* Change this constant to contain your full first and last name (middle is ok too).
 *
 * WARNING: Once you've set set this constant and started exploring your maze,
 * do NOT edit the value of kYourName. Changing kYourName will change which
 * maze you get back, which might invalidate all your hard work!
 */
const string kYourName = "Rimsha Rizvi";

/* Change these constants to contain the paths out of your mazes. */
const string kPathOutOfRegularMaze = "EWSSSEENNNSEN";  // EWSSSEENNENSWN
const string kPathOutOfTwistyMaze = "SEWSEWWWWE";  // SEWSEWWWEE


bool isPathToFreedom(MazeCell *start, const string& moves) {
  /* TO DO: Delete this comment and the next few lines, then implement
   * this function.
   */
  bool valid = false;
  int validSpell = 0, validPotion = 0, validWand = 0;

  // found at initial?
  if (start->whatsHere == "Potion"){
    validPotion = 1;
  } else if (start->whatsHere == "Spellbook"){
    validSpell = 1;
  } else if (start->whatsHere == "Wand"){
    validWand = 1;
  }
  if (!start) {
    validSpell = 0;
    validPotion = 0;
    validWand = 0;
    return false;
  }
  int size = moves.length();
  for (int i = 0; i < size; i++) {
    if (moves[i] != 'N' && moves[i] != 'E' && moves[i] != 'W' &&
       moves[i] != 'S') {
      return false;
    }
    if (start == nullptr) {
      validSpell = 0;
      validPotion = 0;
      validWand = 0;
      return false;
    } else if (moves[i] == 'N') {
      start = start->north;
    } else if (moves[i] == 'E') {
      start = start->east;
    } else if (moves[i] == 'W') {
      start = start->west;
    } else if (moves[i] == 'S') {
      start = start->south;
    }

    if (!start) {
      return false;
    }

    // found at position?
    if (start->whatsHere == "Potion"){
      validPotion = 1;
    } else if (start->whatsHere == "Spellbook"){
      validSpell = 1;
    } else if (start->whatsHere == "Wand"){
      validWand = 1;
    }

    // are all items picked up?
    if (validPotion == 1 && validSpell == 1 && validWand == 1) {
      valid = true;
    } else {
      valid = false;
    }
  }
  return valid;
}
