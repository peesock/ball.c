// #!/bin/tcc -run
#include <stdio.h>
#include <stdarg.h>
#include <math.h>

// newlines/second/second
float gravity = 2;

//newlines/second
float speed = 0;

// spaces/second
float scroll = 3;

// how far the drop is
int drop = 50;

// bouncosity of ball
float bounce = 0.90;

// iterations
int it = 50;

struct position {
	float x;
	float y;
};

int main(){
	// make a text ball (o) that bounces as it scrolls to the right, like a height/time graph
	char ball = 'o';
	struct position pos[it];

	// first, map out all possible points.
	// then map out where to place theme all, line by line.
	pos[0].x = pos[0].y = 0;
	for (int i=0; i < it; i++){

		if (pos[i].y == drop) {
			speed = -speed * bounce;
		}
		// when it detects that it should've bounced at y=drop, but is currently sloping past that point, move backwards in time so that x, y, and speed are at a lower num and y = drop.
		else if (pos[i].y > drop) {
			float diffY = pos[i].y - drop;
			// printf("diffY: %f\n", diffY);
			float diffTime = diffY / (speed - gravity); // note speedPrev
			// printf("diffTime: %f\n", diffTime);
			// printf("speed: %f\n", speed);

			speed -= (gravity + (diffTime * gravity));
			speed = -speed * bounce;
			pos[i].x -= (diffTime * scroll);
			pos[i].y = drop;
		}
		// printf("speed: %f\n", speed);

		// set values
		pos[i+1].y = pos[i].y + speed;
		speed = speed + gravity;
		pos[i+1].x = pos[i].x + scroll;
		fprintf(stderr, "(%f,%f)\n", (pos[i].x), (pos[i].y));
		// fprintf(stderr, "(%f,%f)\n", round(pos[i].x), round(pos[i].y));
		// printf("pos x: %f\npos y: %f\n\n", pos[i].x, pos[i].y);
		// mapping complete.
	}

	int lineW;
	for (int y=0; y <= drop; y++){
		lineW = 0;
		for (int i=0; i < it; i++){
			if (round(pos[i].y) == y) {
				for (int n=0; n < (round(pos[i].x) - lineW - 1); n++){
					putchar(' ');
				}
				putchar(ball);
				lineW = pos[i].x + 1;
			}
		}
		putchar('\n');
	}

	// printf("complete\n");
	return 0;
}
