#ifndef TETRIS_H
#define TETRIS_H

#include <SDL3/SDL.h>
#include <stdbool.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// Constantes
#define SCREEN_WIDTH 500
#define SCREEN_HEIGHT 620
#define GRID_WIDTH 10
#define GRID_HEIGHT 20
#define BLOCK_SIZE 30

// Couleurs
typedef struct {
    Uint8 r, g, b, a;
} Color;

extern Color COLORS[8];
extern Color BG_COLOR;
extern Color GRID_COLOR;
extern Color TEXT_COLOR;
extern Color DARK_GREY;

// Les 7 formes de Tetrominos
extern const int TETROMINO_SHAPES[7][4][4];
extern const int FONT_5X7[95][7];

// Structure pour les Tetrominos
typedef struct {
    int shape[4][4];
    int x, y;
    int color;
    int rotation;
} Tetromino;

// Structure du jeu
typedef struct {
    int grid[GRID_HEIGHT][GRID_WIDTH];
    Tetromino current;
    Tetromino next;
    int score;
    int lines;
    int level;
    bool gameOver;
    Uint64 lastFallTime;
    int fallSpeed;
    int scoreMultiplier;
    int baseFallSpeed;
    bool isDifficult;
} GameState;

// Prototypes des fonctions
void initSDL();
void closeSDL();
Tetromino getRandomTetromino();
void initGame(GameState* game);
void resetGame(GameState* game);
bool checkCollision(GameState* game, Tetromino* tetro, int newX, int newY, int rotation);
void lockTetromino(GameState* game);
void clearLines(GameState* game);
void rotateTetromino(GameState* game);
void moveTetromino(GameState* game, int dx);
void dropTetromino(GameState* game);
void updateGame(GameState* game);
void drawGame(GameState* game);
void drawPixelText(const char* text, int x, int y, Color color, int scale);
void drawChar(char c, int x, int y, Color color, int scale);
void drawTetromino(Tetromino* tetro, int offsetX, int offsetY);
void drawGrid(GameState* game);
void handleInput(SDL_Event* event, GameState* game, bool* running);
void drawMenu(void);
int randomInt(int min, int max);

#endif
