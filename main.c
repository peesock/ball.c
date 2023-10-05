// #!/bin/tcc -run
#include <stdio.h>
#include <math.h>

// newlines/second/second
float gravity = 2;

//newlines/second
float speed = 0;
float speedPrev;

// spaces/second
float scroll = 3;

// how far the drop is
int drop = 50;

// bouncosity of ball
float bounce = 0.80;

// iterations
int it = 80;

struct position {
	float x;
	float y;
};

int main(){
	// make a text ball (o) that bounces as it scrolls to the right, like a height/time graph
	char ball = 'o';
	struct position pos[it + 1];

	// first, map out all possible points.
	// then find where to place them all, line by line.
	pos[0].x = pos[0].y = 0;
	for (int i=0; i < it; i++){

		// when it detects that it should've bounced at y=drop, but is currently sloping past that point, move backwards in time so that x, y, and speed are at a lower num and y = drop.
		if (pos[i].y >= drop) {
			float diffY = pos[i].y - drop;
			float diffTime = diffY / speedPrev;
			// printf("diffY: %f\n", diffY);
			// printf("diffTime: %f\n", diffTime);
			// printf("speed: %f\n", speed);

			speed -= (gravity + (diffTime * gravity));
			speed = -speed * bounce;
			pos[i].x -= (diffTime * scroll);
			pos[i].y = drop;
		}

		speedPrev = speed;
		// set values
		pos[i+1].y = pos[i].y + speed;
		speed = speed + gravity;
		pos[i+1].x = pos[i].x + scroll;
		fprintf(stderr, "%d (%f,%f)\n", i, (pos[i].x), (pos[i].y));
		// fprintf(stderr, "(%f,%f)\n", round(pos[i].x), round(pos[i].y));
	}

	int lineW;
	int x;
	for (int y=0; y <= drop; y++){
		lineW = 0;
		for (int i=0; i < it; i++){
			if (round(pos[i].y) == y) {

				x = round(pos[i].x) + 1; // offset
				if (x >= (lineW + 1)){
					while (lineW < x - 1) {
						putchar(' ');
						lineW++;
					}
					putchar(ball);
					lineW++;
				}

			}
		}
		putchar('\n');

	}

	return 0;
}
