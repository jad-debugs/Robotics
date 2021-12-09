#include "main.h"
#include "subsystems/chassis.h"
#include "subsystems/fourbar.h"

using namespace okapi::literals;

/**
 * A callback function for LLEMU's center button.
 *
 * When this callback is fired, it will toggle line 2 of the LCD text between
 * "I was pressed!" and nothing.
 */
void on_center_button() {
	static bool pressed = false;
	pressed = !pressed;
	if (pressed) {
		pros::lcd::set_text(2, "69... lcd works yay");
	}
	else
		pros::lcd::clear_line(2);
	}

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
	pros::lcd::initialize();
	pros::lcd::set_text(1, "Hello PROS User!");

	pros::lcd::register_btn1_cb(on_center_button);
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {}

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void opcontrol() {
	double left;
	double right;
	okapi::Controller controller;
	okapi::Rate rate;

	while (true) {
		left = controller.getAnalog(okapi::ControllerAnalog::leftY);
		right = controller.getAnalog(okapi::ControllerAnalog::rightY);

		// delay 40 hz around 0.025 sec
		rate.delay(40_Hz);

		// tank drive not arcade
		chassis->getModel()->tank(left, right);

		if (controller[okapi::ControllerDigital::R1].isPressed()) {
			liftLeft.controllerSet(0.5);
			liftRight.controllerSet(0.5);
		}
		else if (controller[okapi::ControllerDigital::R2].isPressed()) {
			liftLeft.controllerSet(-0.5);
			liftRight.controllerSet(-0.5);
		}
		else {
			liftLeft.controllerSet(0);
			liftRight.controllerSet(0);
		}
	}

}
