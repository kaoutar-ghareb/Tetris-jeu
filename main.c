#include "tetris.h"

// Définitions des constantes de police et couleurs
Color COLORS[8] = {
    {26, 31, 40, 255},  // Gris foncé (vide)
    {0, 240, 240, 255},  // Cyan (I)
    {240, 240, 0, 255},  // Jaune (O)
    {160, 0, 240, 255},  // Violet (T)
    {0, 240, 0, 255},    // Vert (S)
    {240, 0, 0, 255},    // Rouge (Z)
    {0, 0, 240, 255},    // Bleu (J)
    {240, 160, 0, 255}   // Orange (L)
};

Color BG_COLOR    = {44, 44, 127, 255};
Color GRID_COLOR  = {59, 85, 162, 255};
Color TEXT_COLOR  = {255, 255, 255, 255};
Color DARK_GREY   = {26, 31, 40, 255};

const int TETROMINO_SHAPES[7][4][4] = {
    {{0,0,0,0},{1,1,1,1},{0,0,0,0},{0,0,0,0}}, // I
    {{0,0,0,0},{0,1,1,0},{0,1,1,0},{0,0,0,0}}, // O
    {{0,0,0,0},{0,1,0,0},{1,1,1,0},{0,0,0,0}}, // T
    {{0,0,0,0},{0,1,1,0},{1,1,0,0},{0,0,0,0}}, // S
    {{0,0,0,0},{1,1,0,0},{0,1,1,0},{0,0,0,0}}, // Z
    {{0,0,0,0},{1,0,0,0},{1,1,1,0},{0,0,0,0}}, // J
    {{0,0,0,0},{0,0,1,0},{1,1,1,0},{0,0,0,0}}  // L
};

const int FONT_5X7[95][7] = {
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    {0x04, 0x04, 0x04, 0x04, 0x00, 0x04, 0x00},
    {0x0A, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00},
    {0x0A, 0x1F, 0x0A, 0x1F, 0x0A, 0x00, 0x00},
    {0x04, 0x0F, 0x14, 0x0E, 0x05, 0x1E, 0x04},
    {0x18, 0x19, 0x02, 0x04, 0x08, 0x13, 0x03},
    {0x0C, 0x12, 0x14, 0x08, 0x15, 0x12, 0x0D},
    {0x04, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00},
    {0x02, 0x04, 0x08, 0x08, 0x08, 0x04, 0x02},
    {0x08, 0x04, 0x02, 0x02, 0x02, 0x04, 0x08},
    {0x00, 0x0A, 0x04, 0x1F, 0x04, 0x0A, 0x00},
    {0x00, 0x04, 0x04, 0x1F, 0x04, 0x04, 0x00},
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x08},
    {0x00, 0x00, 0x00, 0x1F, 0x00, 0x00, 0x00},
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00},
    {0x00, 0x01, 0x02, 0x04, 0x08, 0x10, 0x00},
    {0x0E, 0x11, 0x13, 0x15, 0x19, 0x11, 0x0E},
    {0x04, 0x0C, 0x04, 0x04, 0x04, 0x04, 0x0E},
    {0x0E, 0x11, 0x01, 0x02, 0x04, 0x08, 0x1F},
    {0x1F, 0x02, 0x04, 0x02, 0x01, 0x11, 0x0E},
    {0x02, 0x06, 0x0A, 0x12, 0x1F, 0x02, 0x02},
    {0x1F, 0x10, 0x1E, 0x01, 0x01, 0x11, 0x0E},
    {0x06, 0x08, 0x10, 0x1E, 0x11, 0x11, 0x0E},
    {0x1F, 0x01, 0x02, 0x04, 0x08, 0x08, 0x08},
    {0x0E, 0x11, 0x11, 0x0E, 0x11, 0x11, 0x0E},
    {0x0E, 0x11, 0x11, 0x0F, 0x01, 0x02, 0x0C},
    {0x00, 0x00, 0x04, 0x00, 0x00, 0x04, 0x00},
    {0x00, 0x00, 0x04, 0x00, 0x00, 0x04, 0x08},
    {0x02, 0x04, 0x08, 0x10, 0x08, 0x04, 0x02},
    {0x00, 0x00, 0x1F, 0x00, 0x1F, 0x00, 0x00},
    {0x08, 0x04, 0x02, 0x01, 0x02, 0x04, 0x08},
    {0x0E, 0x11, 0x01, 0x02, 0x04, 0x00, 0x04},
    {0x0E, 0x11, 0x01, 0x0D, 0x15, 0x15, 0x0E},
    {0x0E, 0x11, 0x11, 0x11, 0x1F, 0x11, 0x11},
    {0x1E, 0x11, 0x11, 0x1E, 0x11, 0x11, 0x1E},
    {0x0E, 0x11, 0x10, 0x10, 0x10, 0x11, 0x0E},
    {0x1C, 0x12, 0x11, 0x11, 0x11, 0x12, 0x1C},
    {0x1F, 0x10, 0x10, 0x1E, 0x10, 0x10, 0x1F},
    {0x1F, 0x10, 0x10, 0x1E, 0x10, 0x10, 0x10},
    {0x0E, 0x11, 0x10, 0x17, 0x11, 0x11, 0x0F},
    {0x11, 0x11, 0x11, 0x1F, 0x11, 0x11, 0x11},
    {0x0E, 0x04, 0x04, 0x04, 0x04, 0x04, 0x0E},
    {0x07, 0x02, 0x02, 0x02, 0x02, 0x12, 0x0C},
    {0x11, 0x12, 0x14, 0x18, 0x14, 0x12, 0x11},
    {0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x1F},
    {0x11, 0x1B, 0x15, 0x15, 0x11, 0x11, 0x11},
    {0x11, 0x11, 0x19, 0x15, 0x13, 0x11, 0x11},
    {0x0E, 0x11, 0x11, 0x11, 0x11, 0x11, 0x0E},
    {0x1E, 0x11, 0x11, 0x1E, 0x10, 0x10, 0x10},
    {0x0E, 0x11, 0x11, 0x11, 0x15, 0x12, 0x0D},
    {0x1E, 0x11, 0x11, 0x1E, 0x14, 0x12, 0x11},
    {0x0F, 0x10, 0x10, 0x0E, 0x01, 0x01, 0x1E},
    {0x1F, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04},
    {0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x0E},
    {0x11, 0x11, 0x11, 0x11, 0x11, 0x0A, 0x04},
    {0x11, 0x11, 0x11, 0x15, 0x15, 0x15, 0x0A},
    {0x11, 0x11, 0x0A, 0x04, 0x0A, 0x11, 0x11},
    {0x11, 0x11, 0x11, 0x0A, 0x04, 0x04, 0x04},
    {0x1F, 0x01, 0x02, 0x04, 0x08, 0x10, 0x1F}
};

// Variables globales SDL
SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

// --- Implémentations des fonctions ---

int randomInt(int min, int max) {
    return min + rand() % (max - min + 1);
}

void initSDL() {
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        printf("SDL Error: %s\n", SDL_GetError());
        exit(1);
    }
    window = SDL_CreateWindow("Tetris Game", SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    if (!window) {
        printf("Window Error: %s\n", SDL_GetError());
        exit(1);
    }
    renderer = SDL_CreateRenderer(window, NULL);
    if (!renderer) {
        printf("Renderer Error: %s\n", SDL_GetError());
        exit(1);
    }
}

void closeSDL() {
    if (renderer) SDL_DestroyRenderer(renderer);
    if (window) SDL_DestroyWindow(window);
    SDL_Quit();
}

void drawChar(char c, int x, int y, Color color, int scale) {
    if (c < 32 || c > 126) return;
    const int* pattern = FONT_5X7[c - 32];
    for (int row = 0; row < 7; row++) {
        for (int col = 0; col < 5; col++) {
            if (pattern[row] & (1 << (4 - col))) {
                SDL_FRect rect = { (float)x + col * scale, (float)y + row * scale, (float)scale, (float)scale };
                SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
                SDL_RenderFillRect(renderer, &rect);
            }
        }
    }
}

void drawPixelText(const char* text, int x, int y, Color color, int scale) {
    int offsetX = 0;
    for (int i = 0; text[i] != '\0'; i++) {
        drawChar(text[i], x + offsetX, y, color, scale);
        offsetX += 6 * scale;
    }
}

Tetromino getRandomTetromino() {
    Tetromino tetro;
    int type = randomInt(0, 6);
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            tetro.shape[i][j] = TETROMINO_SHAPES[type][i][j];
        }
    }
    tetro.x = GRID_WIDTH / 2 - 2;
    tetro.y = 0;
    tetro.color = type + 1;
    tetro.rotation = 0;
    return tetro;
}

void initGame(GameState* game) {
    for (int i = 0; i < GRID_HEIGHT; i++) {
        for (int j = 0; j < GRID_WIDTH; j++) {
            game->grid[i][j] = 0;
        }
    }
    game->current = getRandomTetromino();
    game->next = getRandomTetromino();
    game->score = 0;
    game->lines = 0;
    game->level = 1;
    game->gameOver = false;
    game->lastFallTime = SDL_GetTicks();
    game->fallSpeed = game->baseFallSpeed;
}

void resetGame(GameState* game) {
    initGame(game);
}

bool checkCollision(GameState* game, Tetromino* tetro, int newX, int newY, int rotation) {
    int tempShape[4][4];
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            tempShape[i][j] = tetro->shape[i][j];
        }
    }
    if (rotation != 0) {
        int rotated[4][4];
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                rotated[i][j] = tempShape[3 - j][i];
            }
        }
        memcpy(tempShape, rotated, sizeof(tempShape));
    }
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (tempShape[i][j]) {
                int gridX = newX + j;
                int gridY = newY + i;
                if (gridX < 0 || gridX >= GRID_WIDTH || gridY >= GRID_HEIGHT) {
                    return true;
                }
                if (gridY >= 0 && game->grid[gridY][gridX] != 0) {
                    return true;
                }
            }
        }
    }
    return false;
}

void lockTetromino(GameState* game) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (game->current.shape[i][j]) {
                int gridX = game->current.x + j;
                int gridY = game->current.y + i;
                if (gridY >= 0 && gridY < GRID_HEIGHT && gridX >= 0 && gridX < GRID_WIDTH) {
                    game->grid[gridY][gridX] = game->current.color;
                }
            }
        }
    }
    if (game->current.y <= 1) {
        game->gameOver = true;
        return;
    }
    clearLines(game);
    game->current = game->next;
    game->next = getRandomTetromino();
}

void clearLines(GameState* game) {
    int linesCleared = 0;
    for (int i = GRID_HEIGHT - 1; i >= 0; i--) {
        bool fullLine = true;
        for (int j = 0; j < GRID_WIDTH; j++) {
            if (game->grid[i][j] == 0) {
                fullLine = false;
                break;
            }
        }
        if (fullLine) {
            linesCleared++;
            for (int k = i; k > 0; k--) {
                for (int j = 0; j < GRID_WIDTH; j++) {
                    game->grid[k][j] = game->grid[k - 1][j];
                }
            }
            for (int j = 0; j < GRID_WIDTH; j++) {
                game->grid[0][j] = 0;
            }
            i++;
        }
    }
    if (linesCleared > 0) {
        game->lines += linesCleared;
        int points[] = {0, 100, 300, 500, 800};
        game->score += points[linesCleared] * game->level * game->scoreMultiplier;
        game->level = game->lines / 10 + 1;
        if (game->isDifficult) {
            game->fallSpeed = game->baseFallSpeed - (game->level - 1) * 20;
            if (game->fallSpeed < 50) game->fallSpeed = 50;
        } else {
            game->fallSpeed = game->baseFallSpeed - (game->level - 1) * 40;
            if (game->fallSpeed < 100) game->fallSpeed = 100;
        }
    }
}

void rotateTetromino(GameState* game) {
    if (game->gameOver) return;
    if (!checkCollision(game, &game->current, game->current.x, game->current.y, 1)) {
        int rotated[4][4];
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                rotated[i][j] = game->current.shape[3 - j][i];
            }
        }
        memcpy(game->current.shape, rotated, sizeof(game->current.shape));
    }
}

void moveTetromino(GameState* game, int dx) {
    if (game->gameOver) return;
    if (!checkCollision(game, &game->current, game->current.x + dx, game->current.y, 0)) {
        game->current.x += dx;
    }
}

void dropTetromino(GameState* game) {
    if (game->gameOver) return;
    while (!checkCollision(game, &game->current, game->current.x, game->current.y + 1, 0)) {
        game->current.y++;
        game->score += 2 * game->scoreMultiplier;
    }
    lockTetromino(game);
}

void updateGame(GameState* game) {
    if (game->gameOver) return;
    Uint64 currentTime = SDL_GetTicks();
    if (currentTime - game->lastFallTime >= (Uint64)game->fallSpeed) {
        if (!checkCollision(game, &game->current, game->current.x, game->current.y + 1, 0)) {
            game->current.y++;
        } else {
            lockTetromino(game);
        }
        game->lastFallTime = currentTime;
    }
}

void drawTetromino(Tetromino* tetro, int offsetX, int offsetY) {
    Color color = COLORS[tetro->color];
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (tetro->shape[i][j]) {
                SDL_FRect rect = {
                    (float)offsetX + (tetro->x + j) * BLOCK_SIZE,
                    (float)offsetY + (tetro->y + i) * BLOCK_SIZE,
                    (float)BLOCK_SIZE - 2, (float)BLOCK_SIZE - 2
                };
                SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
                SDL_RenderFillRect(renderer, &rect);
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 100);
                SDL_RenderRect(renderer, &rect);
            }
        }
    }
}

void drawNextTetromino(Tetromino* tetro, int startX, int startY) {
    Color color = COLORS[tetro->color];
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (tetro->shape[i][j]) {
                SDL_FRect rect = {
                    (float)startX + j * BLOCK_SIZE,
                    (float)startY + i * BLOCK_SIZE,
                    (float)BLOCK_SIZE - 2, (float)BLOCK_SIZE - 2
                };
                SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
                SDL_RenderFillRect(renderer, &rect);
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 120);
                SDL_RenderRect(renderer, &rect);
            }
        }
    }
}

void drawGrid(GameState* game) {
    int offsetX = 11;
    int offsetY = 11;
    for (int i = 0; i < GRID_HEIGHT; i++) {
        for (int j = 0; j < GRID_WIDTH; j++) {
            SDL_FRect rect = {
                (float)offsetX + j * BLOCK_SIZE,
                (float)offsetY + i * BLOCK_SIZE,
                (float)BLOCK_SIZE - 1, (float)BLOCK_SIZE - 1
            };
            if (game->grid[i][j] != 0) {
                Color color = COLORS[game->grid[i][j]];
                SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
                SDL_RenderFillRect(renderer, &rect);
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 100);
                SDL_RenderRect(renderer, &rect);
            } else {
                SDL_SetRenderDrawColor(renderer, DARK_GREY.r, DARK_GREY.g, DARK_GREY.b, DARK_GREY.a);
                SDL_RenderFillRect(renderer, &rect);
            }
        }
    }
}

void drawGame(GameState* game) {
    SDL_SetRenderDrawColor(renderer, BG_COLOR.r, BG_COLOR.g, BG_COLOR.b, BG_COLOR.a);
    SDL_RenderClear(renderer);
    
    SDL_FRect scoreRect = {320, 55, 170, 60};
    SDL_SetRenderDrawColor(renderer, GRID_COLOR.r, GRID_COLOR.g, GRID_COLOR.b, GRID_COLOR.a);
    SDL_RenderFillRect(renderer, &scoreRect);
    
    SDL_FRect nextRect = {320, 215, 170, 180};
    SDL_RenderFillRect(renderer, &nextRect);
    
    drawGrid(game);
    if (!game->gameOver) drawTetromino(&game->current, 11, 11);
    
    drawPixelText("Score", 365, 20, TEXT_COLOR, 2);
    drawPixelText("Next", 375, 180, TEXT_COLOR, 2);
    
    char buffer[50];
    sprintf(buffer, "%d", game->score);
    drawPixelText(buffer, 360, 75, TEXT_COLOR, 2);
    
    sprintf(buffer, "Niveau %d", game->level);
    drawPixelText(buffer, 330, 420, TEXT_COLOR, 2);
    
    drawNextTetromino(&game->next, 350, 260);
    
    if (game->gameOver) {
        drawPixelText("GAME OVER", 100, 280, TEXT_COLOR, 3);
        drawPixelText("Appuyez sur une touche", 60, 340, TEXT_COLOR, 2);
    }
    
    SDL_RenderPresent(renderer);
}

void handleInput(SDL_Event* event, GameState* game, bool* running) {
    if (event->type == SDL_EVENT_QUIT) *running = false;
    if (event->type == SDL_EVENT_KEY_DOWN) {
        if (game->gameOver) {
            game->gameOver = false;
            resetGame(game);
            return;
        }
        switch (event->key.key) {
            case SDLK_ESCAPE: *running = false; break;
            case SDLK_LEFT:   moveTetromino(game, -1); break;
            case SDLK_RIGHT:  moveTetromino(game, 1); break;
            case SDLK_DOWN:   
                if (!checkCollision(game, &game->current, game->current.x, game->current.y + 1, 0)) {
                    game->current.y++;
                    game->score += 1 * game->scoreMultiplier;
                }
                break;
            case SDLK_UP:     rotateTetromino(game); break;
            case SDLK_SPACE:  dropTetromino(game); break;
        }
    }
}

void drawMenu(void) {
    SDL_SetRenderDrawColor(renderer, BG_COLOR.r, BG_COLOR.g, BG_COLOR.b, BG_COLOR.a);
    SDL_RenderClear(renderer);
    drawPixelText("TETRIS", SCREEN_WIDTH / 2 - 60, 80, TEXT_COLOR, 4);
    drawPixelText("Choisissez la difficulte", SCREEN_WIDTH / 2 - 120, 180, TEXT_COLOR, 2);
    drawPixelText("F1 : FACILE", SCREEN_WIDTH / 2 - 80, 260, TEXT_COLOR, 2);
    drawPixelText("Vitesse normale", SCREEN_WIDTH / 2 - 80, 290, TEXT_COLOR, 1);
    drawPixelText("F2 : DIFFICILE", SCREEN_WIDTH / 2 - 80, 350, TEXT_COLOR, 2);
    drawPixelText("Vitesse RAPIDE !", SCREEN_WIDTH / 2 - 80, 380, TEXT_COLOR, 1);
    drawPixelText("Score x2", SCREEN_WIDTH / 2 - 80, 400, TEXT_COLOR, 1);
    drawPixelText("ESC : Quitter", SCREEN_WIDTH / 2 - 80, 500, TEXT_COLOR, 2);
    SDL_RenderPresent(renderer);
}

int main(int argc, char* argv[]) {
    srand((unsigned int)time(NULL));
    initSDL();
    
    GameState game;
    bool running = true;
    SDL_Event event;
    bool inMenu = true;
    
    while (running) {
        while (SDL_PollEvent(&event)) {
            if (inMenu) {
                if (event.type == SDL_EVENT_KEY_DOWN) {
                    switch (event.key.key) {
                        case SDLK_F1:
                            game.baseFallSpeed = 500;
                            game.fallSpeed = 500;
                            game.scoreMultiplier = 1;
                            game.isDifficult = false;
                            inMenu = false;
                            initGame(&game);
                            break;
                        case SDLK_F2:
                            game.baseFallSpeed = 200;
                            game.fallSpeed = 200;
                            game.scoreMultiplier = 2;
                            game.isDifficult = true;
                            inMenu = false;
                            initGame(&game);
                            break;
                        case SDLK_ESCAPE: running = false; break;
                    }
                }
            } else {
                handleInput(&event, &game, &running);
            }
        }
        
        if (inMenu) drawMenu();
        else {
            updateGame(&game);
            drawGame(&game);
        }
        SDL_Delay(16);
    }
    
    closeSDL();
    return 0;
}
