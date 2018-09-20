//Author: Sundar Sampath
//CS 449: Project 4
//Craps 

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <fcntl.h>

//Utilizies the dice driver to generate a random die value (1-6)
int roll_dice() {
	unsigned int dieval;
	int i = open("/dev/dice", O_RDONLY);
	read(i, &dieval, sizeof(int));
	return dieval + 1;
}

//Plays the game of craps
int main() {
	printf("Welcome to Sundar's Casino!\nPlease enter your name: ");
	char username[100];
	char action[15];
	char action2[15];
	int point = 0;
	scanf("%s", username);
	printf("%s, would you like to Play or Quit? ", username);
	scanf("%s", action);
	if (!(strcasecmp(action, "play"))) {
		while(strcasecmp(action2,"no")) {
			int die1 = roll_dice();
			int die2 = roll_dice();
			int sum = die1 + die2;
			printf("\nYou have rolled %d + %d = %d\n", die1, die2, sum);
			if (sum == 2 || sum == 3 || sum == 12) {
				printf("You lose!\n");
			}
			else if (sum == 7) {
				printf("You Win!\n");
			}
			else {
				point = sum;
				printf("The point is %d\n", point);
				sum = 0;
				while (sum != point) {
					die1 = roll_dice();
					die2 = roll_dice();
					sum = die1 + die2;
					printf("You rolled a %d + %d = %d\n", die1, die2, sum);
					if (sum == 7) {
						printf("You lose!\n");
						break;
					}
					if (sum == point) {
						printf("You win!\n");
						break;
					}
					sum = 0;
				}
			}
		printf("Would you like to play again? ");
		scanf("%s", action2);
		}
	}
	printf("Goodbye, %s\n", username);
	return 1;
}
