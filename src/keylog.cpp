#include <stdio.h>
#include <iostream>
#include <vector>
#include <ctime>

/* See https://manpages.ubuntu.com/manpages/impish/man3/timeval.3bsd.html */
/* https://github.com/torvalds/linux/blob/master/include/uapi/linux/input-event-codes.h */

/*
struct input_event {
	struct timeval time;
	unsigned short type;
	unsigned short code;
	unsigned int value;
};
*/

#include <linux/input.h>

using namespace std;

#define FILENAME "/dev/input/event6"

vector<unsigned short> syns;		/* It stores signals */

bool
is_in_syns(unsigned short code)
{
	/*
	 * This function goes through the array
	 * and finds out if the `code` has
	 * already been stored.
	 */

	for (unsigned short _code : syns) {
		if (code == _code)
			return true;
	}

	return false;
}

void
push_syn(unsigned short code)
{
	/* 
	 * It stores the signal indicating that
	 * it's being pressed.
	 */

	if (!is_in_syns(code))
		syns.push_back(code);
}

char
get_typed_letter(unsigned short code)
{
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

void
delete_syn(unsigned short code)
{
	for (register int i = 0; i < syns.size(); i++)
		if (code == syns.at(i))
			syns.at(i) = 0;
}

int
main(int argc, char *argv[])
{
	FILE  *fp;
	struct input_event event;
	char   ch;

	fp = fopen(FILENAME, "rb");

	if (fp == nullptr) {
		cout << "There was an error: Cannot open the file " << FILENAME << endl;
		exit(1);
	}

	for (;;) { /* loop */

		/* Puts the file pointer to the last sizeof(KEYBOARD) bytes */

		fseek(fp, -sizeof(struct input_event), SEEK_END);

		if (fread(&event, sizeof(struct input_event), 1, fp) != 1) {
			if (!feof(fp))
				cout << "File read error" << endl;
		}

		if (event.type == EV_KEY) /* Key Event */
			switch (event.value) {
				case EV_SYN:
					push_syn(event.code);
					break;
				case EV_KEY:
					ch = get_typed_letter(event.code);
					if (ch != '\0')
						cout << ch << endl;
					break;
				case EV_REL:
					delete_syn(event.code);
					break;
			}
/*
		if (keyboard.type == EV_KEY && keyboard.value == EV_KEY) {

			switch (keyboard.code) {
				case KEY_A:
					cout << "a" << endl;
					break;
				case KEY_B:
					cout << "b" << endl;
					break;
			}
		}*/
		/*
		cout << "Time: "   << keyboard.time.tv_sec << endl;
		cout << "Type: "   << keyboard.type << endl;
		cout << "Event: "  << keyboard.code << endl;
		printf("Event: %x\n", keyboard.code);
		cout << "Letter: " << keyboard.value << endl;
		*/
	}

	fclose(fp);

	return 0;
}
