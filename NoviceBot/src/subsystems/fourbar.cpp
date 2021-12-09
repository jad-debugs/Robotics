#include "subsystems/fourbar.h"

// change ports !!!

const int8_t liftPortLeft = 7;
const int8_t liftPortRight = 69;

okapi::Motor liftLeft = okapi::Motor(liftPortLeft);
okapi::Motor liftRight = okapi::Motor(liftPortRight);
