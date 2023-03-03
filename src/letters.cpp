/**
 *
 */

#include <vector>
#include <linux/input.h>

using namespace std;

char
get_typed_letter(unsigned short code, vector<unsigned short>& syns)
{
	/**
	 * This function returns the letter typed.
	 *
	 * @param `code` receives the code in accordance
	 * 	with input_event structure in
	 * 	`<linux/input.h>`.
	 * @param `syns` contains all the signals of the
	 * 	pressed keys by the user.
	 *
	 * @return `ch`: result of the key combination.
	 */

	char ch = '\0';

	switch (code) {
                case KEY_1:
                case KEY_KP1:
                        ch = '1';
                        break;
                case KEY_2:
                case KEY_KP2:
                        ch = '2';
                        break;
                case KEY_3:
                case KEY_KP3:
                        ch = '3';
                        break;
                case KEY_4:
                case KEY_KP4:
                        ch = '4';
                        break;
                case KEY_5:
                case KEY_KP5:
                        ch = '5';
                        break;
                case KEY_6:
                case KEY_KP6:
                        ch = '6';
                        break;
                case KEY_7:
		case KEY_KP7:
                        ch = '7';
                        break;
                case KEY_8:
                case KEY_KP8:
                        ch = '8';
                        break;
                case KEY_9:
                case KEY_KP9:
                        ch = '9';
                        break;
                case KEY_0:
                case KEY_KP0:
                        ch = '0';
                        break;
	}

	return ch;
}
