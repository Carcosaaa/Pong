#include <ncurses/ncurses.h>

// Constants
#define WIDTH 80
#define HEIGHT 24
#define PADDLE_SIZE 5
#define BALL_CHAR '*'
#define PADDLE_CHAR '|'

// Global variables
int ball_x, ball_y;
int ball_dx, ball_dy;
int player1_y, player2_y;

// Initialize the game
void init() {
    // Set up ncurses
    initscr();
    cbreak();
    noecho();
    clear();
    refresh();

    // Initialize variables
    ball_x = WIDTH / 2;
    ball_y = HEIGHT / 2;
    ball_dx = 1;
    ball_dy = 1;
    player1_y = HEIGHT / 2;
    player2_y = HEIGHT / 2;
}

// Draw the game board
void draw() {
    // Clear the screen
    clear();

    // Draw the ball
    mvaddch(ball_y, ball_x, BALL_CHAR);

    // Draw the paddles
    for (int i = 0; i < PADDLE_SIZE; i++) {
        mvaddch(player1_y + i, 1, PADDLE_CHAR);
        mvaddch(player2_y + i, WIDTH - 2, PADDLE_CHAR);
    }

    // Refresh the screen
    refresh();
}

// Update the game state
void update() {
    // Move the ball
    ball_x += ball_dx;
    ball_y += ball_dy;

    // Check for collisions with walls
    if (ball_y == 0 || ball_y == HEIGHT - 1) {
        ball_dy *= -1;
    }
    if (ball_x == 1) {
        if (ball_y >= player1_y && ball_y <= player1_y + PADDLE_SIZE - 1) {
            ball_dx *= -1;
        }
        else {
            // Player 2 scores
            ball_x = WIDTH / 2;
            ball_y = HEIGHT / 2;
            ball_dx *= -1;
        }
    }
    if (ball_x == WIDTH - 2) {
        if (ball_y >= player2_y && ball_y <= player2_y + PADDLE_SIZE - 1) {
            ball_dx *= -1;
        }
        else {
            // Player 1 scores
            ball_x = WIDTH / 2;
            ball_y = HEIGHT / 2;
            ball_dx *= -1;
        }
    }

    // Move the paddles
    int key = getch();
    switch (key) {
        case 'w':
            if (player1_y > 0) {
                player1_y--;
            }
            break;
        case 's':
            if (player1_y + PADDLE_SIZE < HEIGHT) {
                player1_y++;
            }
            break;
        case KEY_UP:
            if (player2_y > 0) {
                player2_y--;
            }
            break;
        case KEY_DOWN:
            if (player2_y + PADDLE_SIZE < HEIGHT) {
                player2_y++;
            }
            break;
    }
}

// Main game loop
int main() {
    // Initialize the game
    init();

    // Game loop
    while (1) {
        // Draw the game
        draw();

        // Update the game
        update();
    }

    // Clean up ncurses
    endwin();

    return 0;
}