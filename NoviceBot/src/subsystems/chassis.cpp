#include "main.h"
#include "subsystems/chassis.h"

using namespace okapi::literals;

// change port numbers after once team puts them in

const int8_t lf = -1;
const int8_t lb = -2;
const int8_t rf = 10;
const int8_t rb = 9;

std::shared_ptr<okapi::ChassisController> chassis = okapi::ChassisControllerBuilder().withMotors({lf, lb},{rf, rb}).withDimensions(okapi::AbstractMotor::gearset::green, {{4_in, 11.5_in}, okapi::imev5GreenTPR}).build();
