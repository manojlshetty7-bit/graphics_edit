#include <stdio.h>
#include <stdlib.h>

#define WIDTH 60
#define HEIGHT 20

char canvas[HEIGHT][WIDTH];

void clear_canvas() {
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            canvas[i][j] = ' ';
        }
    }
}

void display_canvas() {
    printf("\n--- Canvas ---\n");
    for (int i = 0; i < WIDTH + 2; i++) printf("-");
    printf("\n");
    
    for (int i = 0; i < HEIGHT; i++) {
        printf("|");
        for (int j = 0; j < WIDTH; j++) {
            printf("%c", canvas[i][j]);
        }
        printf("|\n");
    }

    for (int i = 0; i < WIDTH + 2; i++) printf("-");
    printf("\n");
}

int main() {
    clear_canvas();
    int choice;
    do {
        printf("\n=== 2D Graphics Editor ===\n");
        printf("1. Add Object\n");
        printf("2. Delete Object\n");
        printf("3. Modify Object\n");
        printf("4. Display Picture\n");
        printf("5. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1: printf("Add feature coming soon!\n"); break;
            case 2: printf("Delete feature coming soon!\n"); break;
            case 3: printf("Modify feature coming soon!\n"); break;
            case 4: display_canvas(); break;
            case 5: printf("Exiting...\n"); break;
            default: printf("Invalid choice.\n");
        }
    } while (choice != 5);
    
    return 0;
}