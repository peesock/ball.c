#!/bin/tcc -run
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <inttypes.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <errno.h>
#include <error.h>
#include <unistd.h>
#include <stddef.h>
#include <math.h>
#define bool char

// newlines/second
int speed = 0;
// newlines/second/second
int gravity = 1;
// spaces/second
int scroll = 4;
// how far the drop is
int drop = 20;
// bouncosity of ball
float bounce = 0.6;
// iterations
int it = 50;

struct position {
	int x;
	int y;
};

int main(){
	// make a text ball (o) that bounces as it scrolls to the right, like a height/time graph
	char ball = 'o';
	struct position pos[it];

	// first, map out all possible points.
	// then map out where to place theme all, line by line.
	// putchar(ball);
	pos[0].x = pos[0].y = 0;
	for (int i=1; i < it; i++){

		// printf("speed: %d", speed);
		speed += gravity;
		if (pos[i-1].y >= drop) {
			speed = -speed * bounce;
			printf("speed: %d\n", speed);
		}
		pos[i].y = pos[i-1].y + speed;
		pos[i].x = pos[i-1].x + scroll;
		// printf("bye");
		printf("pos x: %d\npos y: %d\n\n", pos[i].x, pos[i].y);
		// mapping complete.
	}
	int lineW;
	for (int y=0; y < drop; y++){
		lineW = 0;
		for (int i=0; i < it; i++){
			if (pos[i].y == y) {
				for (int n=0; n < (pos[i].x - lineW) - 1; n++){
					putchar(' ');
				}
				putchar(ball);
				lineW = pos[i].x;
			}
		}
		putchar('\n');
	}

	return 0;
}
