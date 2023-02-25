#include <stdio.h>
#include <iostream>
#include <ctime>

#include <unistd.h>

using namespace std;

#define FILENAME "/dev/input/event6"

struct input_event {
	struct timeval time;
	unsigned short type;
	unsigned short code;
	unsigned int value;
};

typedef struct input_event KEYBOARD;

int
main(int argc, char *argv[])
{
	FILE *fp = fopen(FILENAME, "rb");
	KEYBOARD keyboard;

	keyboard.code = 0;
	keyboard.value = 0;

	if (fp == nullptr) {
		cout << "There was an error: Cannot open the file " << FILENAME << endl;
		exit(1);
	}

	for (register int i = 0; i < 30; i++) {

		/* Puts the file pointer to the last sizeof(KEYBOARD) bytes */

		fseek(fp, -sizeof(KEYBOARD), SEEK_END);

		if (fread(&keyboard, sizeof(KEYBOARD), 1, fp) != 1) {
			if (!feof(fp))
				cout << "File read error" << endl;
		}

		if (keyboard.type == 1) {

			if (keyboard.code > 1 && keyboard.code < 100)
				cout << "Code: " << keyboard.code << endl;
		}
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
