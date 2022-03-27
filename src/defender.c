// Standard headers
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Internal headers
#include "direction.h"
#include "position.h"
#include "spy.h"

// Main header
#include "defender.h"

// Macros
#define UNUSED(x) (void)(x) // Auxiliary to avoid error of unused parameter

/*----------------------------------------------------------------------------*/
/*                          PRIVATE FUNCTIONS HEADERS                         */
/*----------------------------------------------------------------------------*/

bool test_direction_defender(position_t defender_position, direction_t defender_direction);

/*----------------------------------------------------------------------------*/
/*                              PUBLIC FUNCTIONS                              */
/*----------------------------------------------------------------------------*/

direction_t execute_defender_strategy(
    position_t defender_position, Spy attacker_spy) {
  
  UNUSED(attacker_spy);

  direction_t defender_directions[] = {DIR_UP, DIR_DOWN};
  int directions_amount = 2;
  int tested_directions[] = {0, 0};
  int count_tested_directions = 0;
  int random_direction_index = rand() % directions_amount;
  
  while (count_tested_directions < directions_amount
         && !test_direction_defender(defender_position, defender_directions[random_direction_index])) {
    if (tested_directions[random_direction_index] == 0) {
      tested_directions[random_direction_index] = 1;
      count_tested_directions++;
    }
    random_direction_index = rand() % directions_amount;
    
  }
  
  if (count_tested_directions < directions_amount) {
    return defender_directions[random_direction_index];
  }
  
  return (direction_t) DIR_LEFT;
}

/*----------------------------------------------------------------------------*/
/*                              PRIVATE FUNCTIONS                             */
/*----------------------------------------------------------------------------*/

bool test_direction_defender(position_t defender_position, direction_t defender_direction) {
  position_t new_position = move_position(defender_position, defender_direction);
  return !equal_positions(defender_position, new_position);
}
