#include <stdio.h>
#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdlib.h>

#define OUT_OF_SCREEN_SCALE 2
#define CELL_SIZE 5

int SCREEN_WIDTH, SCREEN_HEIGHT, GRID_WIDTH, GRID_HEIGHT, VIEW_WIDTH, VIEW_HEIGHT, i, j;

bool **CurrentGrid;
bool **NewGrid;

// Set Global Values According To System Specifications
void SetGlobalValues()
{
    // Get Screen Resolution
    SDL_DisplayMode dm;
    SDL_GetCurrentDisplayMode(0, &dm);

    SCREEN_WIDTH = (dm.w * OUT_OF_SCREEN_SCALE);
    SCREEN_HEIGHT = (dm.h * OUT_OF_SCREEN_SCALE);

    GRID_WIDTH = (SCREEN_WIDTH / CELL_SIZE);
    GRID_HEIGHT = (SCREEN_HEIGHT / CELL_SIZE);

    VIEW_WIDTH = (SCREEN_WIDTH / OUT_OF_SCREEN_SCALE);
    VIEW_HEIGHT = (SCREEN_HEIGHT / OUT_OF_SCREEN_SCALE);

    // Dynamically Initalising Array
    CurrentGrid = malloc(GRID_WIDTH * sizeof(bool *));
    NewGrid = malloc(GRID_WIDTH * sizeof(bool *));

    for (i = 0; i < GRID_WIDTH; i++)
    {
        CurrentGrid[i] = malloc(GRID_HEIGHT * sizeof(bool));
        NewGrid[i] = malloc(GRID_HEIGHT * sizeof(bool));
    }
}

// Generate A Map With Random Boolean Values For Each Cell
void RandInitGrid()
{
    for (i = 0; i < GRID_WIDTH; i++)
    {
        for (j = 0; j < GRID_HEIGHT; j++)
        {
            CurrentGrid[i][j] = rand() % 2;
        }
    }
}

// Check For Rules In The Map and Generate a New Map
void RuleCheckGrid()
{
    // Visit Each Cell
    for (i = 0; i < GRID_WIDTH; i++)
    {
        for (j = 0; j < GRID_HEIGHT; j++)
        {
            int neighbour = 0;

            // Check Neighbours
            for (int y = -1; y <= 1; y++)
            {
                for (int x = -1; x <= 1; x++)
                {
                    // Center Cell Exclusion
                    if (!(x == 0 && y == 0))
                    {
                        int newX = i + x;
                        int newY = j + y;

                        // Check Neighbour Cell Are Within Grid Bounds
                        if (newX >= 0 && newX < GRID_WIDTH && newY >= 0 && newY < GRID_HEIGHT)
                        {
                            // Check Neigbour Cell Alive or Not
                            if (CurrentGrid[newX][newY] == 1)
                            {
                                neighbour++;
                            }
                        }
                    }
                }
            }

            // Apply Conways Game of Life Rules Onto a New Map
            if (CurrentGrid[i][j] == 1)
            {
                if (neighbour < 2 || neighbour > 3)
                {
                    NewGrid[i][j] = 0;
                }
            }
            else if (neighbour == 3)
            {
                NewGrid[i][j] = 1;
            }
        }
    }
}

// Apply New Map to Current Map
void UpdateGrid()
{
    // Copy NewGrid to CurrentGrid
    for (int i = 0; i < GRID_WIDTH; i++)
    {
        for (int j = 0; j < GRID_HEIGHT; j++)
        {
            CurrentGrid[i][j] = NewGrid[i][j];
        }
    }
}

void FreeMemory(bool **arr)
{
    for (i = 0; i < GRID_WIDTH; i++)
    {
        free(arr[i]);
    }
    free(arr);
}

// Rendering, Game Loop, Event Handling, Audio
int main()
{
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);

    SetGlobalValues();

    bool Wrun = true;
    bool Lrun = true;
    bool Astate = false;
    int mX = 0;
    int mY = 0;
    int Speed = 150;

    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Event event;

    SDL_AudioSpec wavspec;
    Uint32 wavL;
    Uint8 *wavB;
    SDL_LoadWAV("./retro.wav", &wavspec, &wavB, &wavL);
    SDL_AudioDeviceID speaker = SDL_OpenAudioDevice(NULL, 0, &wavspec, NULL, 0);

    SDL_CreateWindowAndRenderer(VIEW_WIDTH, VIEW_HEIGHT, 0, &window, &renderer);
    SDL_SetWindowResizable(window, SDL_TRUE);

    // Initalize a Starting Map
    RandInitGrid();

    // Main Loop
    while (Wrun)
    {
        // Event Loop
        while (SDL_PollEvent(&event))
        {
            // Mouse Event
            if (event.type == SDL_QUIT)
            {
                Wrun = false;
            }
            if (event.type == SDL_MOUSEBUTTONDOWN)
            {
                SDL_GetMouseState(&mX, &mY);
                NewGrid[(mX / CELL_SIZE)][(mY / CELL_SIZE)] = 1;
            }

            // Keyboard Key Down Event
            if (event.type == SDL_KEYDOWN)
            {
                switch (event.key.keysym.sym)
                {
                case SDLK_q:
                    Wrun = false;
                    break;
                case SDLK_SPACE:
                    (Lrun == true) ? (Lrun = false) : (Lrun = true);
                    (Astate == false) ? (Astate = true) : (Astate = false);
                    break;
                case SDLK_UP:
                    (Speed > 0) ? (Speed -= 10) : (Speed = 10);
                    break;
                case SDLK_DOWN:
                    Speed += 10;
                    break;
                }
            }
        }

        // Clear Render
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);

        // Drawing Cell
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

        for (int i = 0; i < GRID_WIDTH; i++)
        {
            for (int j = 0; j < GRID_HEIGHT; j++)
            {

                if (CurrentGrid[i][j] == 1)
                {
                    SDL_Rect cell = {i * CELL_SIZE, j * CELL_SIZE, CELL_SIZE, CELL_SIZE};
                    SDL_RenderFillRect(renderer, &cell);
                }
            }
        }
        SDL_RenderPresent(renderer);

        // Music Control
        SDL_PauseAudioDevice(speaker, Astate);
        if (SDL_GetQueuedAudioSize(speaker) == 0)
        {
            SDL_QueueAudio(speaker, wavB, wavL);
        }

        // Call New Map
        if (Lrun)
        {
            RuleCheckGrid();
        }

        // Apply New Map
        UpdateGrid();

        // Control Speed of Game
        SDL_Delay(Speed);
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_FreeWAV(wavB);
    SDL_CloseAudioDevice(speaker);
    SDL_Quit();
    FreeMemory(CurrentGrid);
    FreeMemory(NewGrid);
    return 0;
}
