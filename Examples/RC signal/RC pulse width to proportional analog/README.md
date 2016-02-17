Created on 2016-02-17 for RobotShop by scharette.
Allows output of an RC signal (digital pulse width) from an RC receiver to be converted to a proportional analog voltage output (PWM).
Typical RC signal is from 1000-2000 us (1500 us = center) and is therefore mapped to an output of ~0-5 V DC (2.5 V DC = center).
Note: The PWM output is not a true analog voltage. It is recommend to attach to it a simple low pass filter (single pole) to get a proper analog output from it.

License GNU GPL v3: http://www.gnu.org/licenses/gpl-3.0.en.html