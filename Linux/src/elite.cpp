#include<iostream>
#include<termios.h>
#include<unistd.h>
#include<cstdio>
#include<cctype>

struct termios og_termios;

void rawMode(bool state);


char c;
bool debug = true;

int main(void)
{
	rawMode(true);
	
	while(read(STDIN_FILENO, &c, 1) == 1 && c != '0')
	{
		if (iscntrl(c)) {
			printf("%d\r\n", c);
		} 
		else {
			printf("%d ('%c')\r\n", c, c);

		}

	}

	rawMode(false);
	return 0;
}

void rawMode(bool state)
{
	if(state)
	{
		
		tcgetattr(STDIN_FILENO, &og_termios);
		struct termios raw = og_termios;
		raw.c_iflag &= ~(ISTRIP | INPCK  | ICRNL  | BRKINT | ICRNL | IXON);
		raw.c_lflag &= ~(ECHO   | ICANON | IEXTEN | ISIG);
		raw.c_oflag &= ~(OPOST);
		raw.c_cflag |=  (CS8);
		tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
		if(debug)
			std::cout << "RawMode Engaged." << std::endl;
	}
		
	else
	{
		tcsetattr(STDIN_FILENO, TCSAFLUSH, &og_termios);
		if(debug)
			std::cout << "RawMode Disengaged." << std::endl;
	}
}
