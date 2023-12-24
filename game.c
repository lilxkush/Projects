#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
int numguess;
int numrand;
char c;

int GetGuess() {
	
	if (numguess > numrand) {
		printf("too high, guess again: \n");
		scanf_s("%d", &numguess);
	}
	
	else if (numguess < numrand) {
		printf("too low, guess again: \n");
		scanf_s("%d", &numguess);
	}
	return 0;
}

int PlayGuessingGame() {

	while (c != 'q') {
		srand(time(NULL));
		numrand = (rand() % (100 - 10 + 1)) + 10;
		
		double sqrtnum = sqrt((double)numrand);
		
		printf("%lf is the square root of what number? \n", sqrtnum);
		scanf_s("%d", &numguess);
		
		while (numguess != numrand) {
			GetGuess();
		}
		
		printf("you got it baby!\n");
		
		int ch;
		while ((ch = getchar()) != '\n' && ch != EOF);
		
		printf("Press 'q' to quit or any key to continue: ");
		c = getchar();
	}
	return 0;
}

int main() {

	printf("Welcome! Press q to quit or any key to continue: \n");
	c = getchar();
	
	while (c != 'q') {
		PlayGuessingGame();
	}
	
	printf("Bye Bye !\n");
}
	