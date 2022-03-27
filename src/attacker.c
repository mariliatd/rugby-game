// Standard headers
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Internal headers
#include "direction.h"
#include "position.h"
#include "spy.h"

// Main header
#include "attacker.h"

// Macros
#define UNUSED(x) (void)(x) // Auxiliary to avoid error of unused parameter

/*----------------------------------------------------------------------------*/
/*                          PRIVATE FUNCTIONS HEADERS                         */
/*----------------------------------------------------------------------------*/

bool test_direction_attacker(position_t attacker_position, direction_t direction);

/*----------------------------------------------------------------------------*/
/*                              PUBLIC FUNCTIONS                              */
/*----------------------------------------------------------------------------*/

direction_t execute_attacker_strategy(
    position_t attacker_position, Spy defender_spy) {
  
  UNUSED(defender_spy);

  direction_t prefered_directions[] = {DIR_UP_RIGHT, DIR_RIGHT, DIR_DOWN_RIGHT};
  int directions_amount = 3;
  int tested_directions[] = {0, 0, 0};
  int count_tested_directions = 0;
  int random_direction_index = rand() % directions_amount;

  while (count_tested_directions < directions_amount 
         && !test_direction_attacker(attacker_position, prefered_directions[random_direction_index])) {
    if (tested_directions[random_direction_index] == 0) {
      count_tested_directions++;
      tested_directions[random_direction_index] = 1;
    }
    random_direction_index = rand() % directions_amount;
  }

  if (count_tested_directions < directions_amount) {
    return prefered_directions[random_direction_index];
  }
  
  direction_t spare_directions[] = {DIR_UP_LEFT, DIR_LEFT, DIR_DOWN_LEFT, DIR_UP, DIR_DOWN};
  random_direction_index = rand() % 5;
  while (!test_direction_attacker(attacker_position, spare_directions[random_direction_index])) {
    random_direction_index = rand() % 5;
  }
  return spare_directions[random_direction_index];
}

/*----------------------------------------------------------------------------*/
/*                              PRIVATE FUNCTIONS                              */
/*----------------------------------------------------------------------------*/

bool test_direction_attacker(position_t attacker_position, direction_t attacker_direction) {
  position_t new_position = move_position(attacker_position, attacker_direction);
  return (!equal_positions(attacker_position, new_position));
}
