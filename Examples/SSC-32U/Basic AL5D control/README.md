Created on 2018-03-15 for RobotShop by scharette.
This examples uses a BotBoarduino to control a Lynxmotion AL5D robotic arm [using a SSC-32U] using direct serial connection (UART TTL) between the BotBoardiuno and SSC-32U. It controls it by sending group moves. See below for more details.

The code does a few things:
1) Initialize all interfaces and set all the servomotor channels to 1500 (center position).
2) Move the channels #0/#1/#2#3 from 1500 > 1800. When reached, they reverse direction and move from 1800 > 1200. Then, it reverses again from 1200 > 1800. This repeats infinitely. Make sure to not let the arm unnatented and prevent the servomotors from overheating.
3) It also reads the analog value present at SSC-32U input H at ever loop (delay = 100 ms).

You can find out more about these products here:

BotBoarduino: http://www.robotshop.com/en/lynxmotion-botboarduino-robot-controller.html
> [Useful links](http://www.robotshop.com/en/lynxmotion-botboarduino-robot-controller.html#Useful Links)

SSC-32U: http://www.robotshop.com/en/lynxmotion-ssc-32u-usb-servo-controller.html
> [Useful links](http://www.robotshop.com/en/lynxmotion-ssc-32u-usb-servo-controller.html#Useful Links)

> Especially helpful in this example is a list of the commands for the SSC-32U. These can be found in the [user manual on pages 24-26](http://www.lynxmotion.com/images/data/lynxmotion_ssc-32u_usb_user_guide.pdf#page=24) and [pages 32-35](http://www.lynxmotion.com/images/data/lynxmotion_ssc-32u_usb_user_guide.pdf#page=32).

> You may also want to check out an example of the wiring for the GND/RX/TX between the BotBoarduino and SSC-32U. This is available in the [user manual on page 21, option 2](http://www.lynxmotion.com/images/data/lynxmotion_ssc-32u_usb_user_guide.pdf#page=21).

License GNU GPL v3: http://www.gnu.org/licenses/gpl-3.0.en.html
