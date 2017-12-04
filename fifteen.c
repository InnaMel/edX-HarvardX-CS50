/**
 * fifteen.c
 *
 * Implements Game of Fifteen (generalized to d x d).
 *
 * Usage: fifteen d
 *
 * whereby the board's dimensions are to be d x d,
 * where d must be in [DIM_MIN,DIM_MAX]
 *
 * Note that usleep is obsolete, but it offers more granularity than
 * sleep and is simpler to use than nanosleep; `man usleep` for more.
 */

#define _XOPEN_SOURCE 500

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// constants
#define DIM_MIN 3
#define DIM_MAX 9

// board
int board[DIM_MAX][DIM_MAX];

// dimensions
int d;

// current coordinates for 0
int rowZero = 0;
int columnZero = 0;

// coordinates for current tile
int rowTile = 0;
int columnTile = 0;


// prototypes
void clear(void);
void greet(void);
void init(void);
void draw(void);
bool move(int tile);
bool won(void);
void swap(int *A, int *B);
void search(int value, int values[][DIM_MAX], int diment);

int main(int argc, string argv[])
{
    // ensure proper usage
    if (argc != 2)
    {
        printf("Usage: fifteen d\n");
        return 1;
    }

    // ensure valid dimensions
    d = atoi(argv[1]);
    if (d < DIM_MIN || d > DIM_MAX)
    {
        printf("Board must be between %i x %i and %i x %i, inclusive.\n",
            DIM_MIN, DIM_MIN, DIM_MAX, DIM_MAX);
        return 2;
    }
    rowZero = d - 1;
    columnZero = d - 1;


    // open log
    FILE *file = fopen("log.txt", "w");
    if (file == NULL)
    {
        return 3;
    }

    // greet user with instructions
    greet();

    // initialize the board
    init();

    // accept moves until game is won
    while (true)
    {
        // clear the screen
        clear();

        // draw the current state of the board
        draw();

/*        // log the current state of the board (for testing)
        for (int i = 0; i < d; i++)
        {
            for (int j = 0; j < d; j++)
            {
                fprintf(file, "%i", board[i][j]);
                if (j < d - 1)
                {
                    fprintf(file, "|");
                }
            }
            fprintf(file, "\n");
        }
        fflush(file);*/

        // check for win
        if (won())
        {
            printf("ftw!\n");
            break;
        }

        // prompt for move
        printf("Tile to move: ");
        int tile = get_int();

        // quit if user inputs 0 (for testing)
        if (tile == 0)
        {
            break;
        }

        // log move (for testing)
        fprintf(file, "%i\n", tile);
        fflush(file);

        // move if possible, else report illegality
        if (!move(tile))
        {
            printf("\nIllegal move.\n");
            usleep(500000);
        }

        // sleep thread for animation's sake
        usleep(500000);
    }

    // close log
    fclose(file);

    // success
    return 0;
}

/**
 * Clears screen using ANSI escape sequences.
 */
void clear(void)
{
    printf("\033[2J");
    printf("\033[%d;%dH", 0, 0);
}

/**
 * Greets player.
 */
void greet(void)
{
    clear();
    printf("WELCOME TO GAME OF FIFTEEN\n");
    usleep(2000000);
}

/**
 * Initializes the game's board with tiles numbered 1 through d*d - 1
 * (i.e., fills 2D array with values but does not actually print them).
 */
void init(void)
{
    int quantityNum = d * d;
    quantityNum--;
    for(int i = 0; i < d; i++)
    {
        for(int j = 0; j < d; j++)
        {
            if(quantityNum == 0)
            {
                board[i][j] = 95;
                break;
            }
            board[i][j] = quantityNum;
            quantityNum--;
        }
    }
    if(d % 2 == 0)
    {
        swap(&board[d - 1][d - 2], &board[d - 1][d - 3]);
    }
}

/**
 * Prints the board in its current state.
 */
void draw(void)
{
    for(int i = 0; i < d; i++)
    {
        for(int j = 0; j < d; j++)
        {
            if(board[i][j] == 95)
            {
                printf(" %c", board[i][j]);
            }
            else
            printf("%2i  ", board[i][j]);
        }
        printf("\n");
    }
}

/**
 * If tile borders empty space, moves tile and returns true, else
 * returns false.
 */
bool move(int tile)
{
    bool legal = false;
    search(tile, board, d);
    if( ((rowTile == rowZero) && (columnTile - columnZero == 1)) || ((rowTile == rowZero) && (columnZero - columnTile == 1))
    ||  ((columnTile == columnZero) && (rowTile - rowZero == 1)) || ((columnTile == columnZero) && (rowZero - rowTile == 1)) )
    {
        legal = true;
        swap(&board[rowTile][columnTile], &board[rowZero][columnZero]);
        rowZero = rowTile;
        columnZero = columnTile;
    }
    return legal;
}

/**
 * Returns true if game is won (i.e., board is in winning configuration),
 * else false.
 */
bool won(void)
{
    int count = 0;
    bool done = true;
    for (int i = 0; i < d; i++)
    {
        for (int j = 0; j < d; j++)
        {
            count++;
            if(board[i][j] != count)
            {
                done = false;
                i = d;
                break;
            }
            else
            {
                if((count == d*d - 1) && ((board[d - 1][d - 1] == 95)))
                {
                    done = true;
                    i = d;
                    j = d;
                }
            }
        }
    }
    return done;
}

// swap function
void swap(int *A, int *B)
{
    int temp = *A;
    *A = *B;
    *B = temp;
}

//**************************************************************************************search O(log(n))

void search(int value, int values[][DIM_MAX], int diment)
{
    for (int i = 0; i < diment; i++)
    {
        for (int j = 0; j < diment; j++)
        {
            if (value == values[i][j])
            {
                rowTile = i;
                columnTile = j;
                i = diment;
                break;
            }
        }
    }
}
