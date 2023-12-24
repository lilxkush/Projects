#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "bst.h"
#include <string.h>
#include <stdlib.h>




int main()
{
	struct node* game_tree = create_game_tree();
	printf("Welcome! Press 'q' to quit or any other key to continue:\n");
	char c, game_over = 0;
	c = getchar();
	if (c == 'q') {
		game_over = 1;
	}
	
	struct node* current = game_tree;
    printf("You think of a fruit or vegetable and I will try to guess it:\n");
    while (!game_over) {
        printf("%s (y/n): ", current->question);
        c = getchar();
        while (getchar() != '\n'); // Clear the input buffer

        if (c == 'y' || c == 'Y') {
            current = current->left;
        }
        else if (c == 'n' || c == 'N') {
            current = current->right;
        }

        if (current->left == NULL && current->right == NULL) {
            // Leaf node reached (guess made)
            printf("%s?\n", current->guess);
            c = getchar();
            while (getchar() != '\n'); // Clear the input buffer
            if (c == 'y' || c == 'Y') {
                printf("I win!\n");
            }
            else {
                if (c == 'n' || c == 'N') {
                    printf("You win!\n");
                }
            }
            game_over = 1;
        }
    }

    return 0;
}