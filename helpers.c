// Helper functions for music

#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <stdlib.h>

#include "helpers.h"
#define A4 4
#define Hz 440

// find Hz nearest note of A
int findNeededA(float octave, bool ifA)
{
    int Azero = 0;
    int deltaOctave = 0;
    int corrective = 0;

    if (ifA == false)
    {
        corrective = 1;
    }

    deltaOctave = A4 - octave;
    if (deltaOctave < 0)
    {
        Azero = Hz * pow(2, (abs(deltaOctave) - corrective));
    }
    else if (deltaOctave > 0)
    {
        Azero = Hz / (pow(2, deltaOctave + corrective));
    }
    else if (ifA == false)
    {
        Azero = Hz / 2;
    }
    else
    {
        Azero = Hz;
    }
    return Azero;
}



// Converts a fraction formatted as X/Y to eighths
int duration(string fraction)
{
    // for calculation use ASCII code
    int numerator = (int)fraction[0] - 48;
    int denomenator = (int)fraction[2] - 48;

    // multiply both parts
    while (denomenator != 8)
    {
        numerator *= 2;
        denomenator *= 2;
    }
    return numerator;
}

// Calculates frequency (in Hz) of a note
int frequency(string note)
{
    char letter = note[0];
    char middleElement = '*';
    int octave = 0;
    float extent = letter - 'A';
    int AHz = 0;
    float frequency = 0;
    bool ifA = false;


    // parse note to letter, #, b, octave
    if (strlen(note) == 2)
    {
        octave = (int)note[1] - 48;
    }
    else
    {
        middleElement = note[1];
        octave = (int)note[2] - 48;
    }

    if (letter == 'B')
    {
        octave += 1;
    }

    if (letter == 'A')
    {
        ifA = true;
    }

    // find near A
    AHz = findNeededA(octave, ifA);

    // find out which note
    switch (letter)
    {
        case 'B':
        case 'C':
            extent += 1;
            break;
        case 'D':
            extent += 2;
            break;
        case 'E':
        case 'F':
            extent += 3;
            break;
        case 'G':
            extent += 4;
            break;
    }

    // correction extend of note in case of semitone
    switch (middleElement)
    {
        case '#':
            extent += 1;
            break;
        case 'b':
            extent -= 1;
            break;
    }

    // calculate the result
    frequency = AHz * pow(2.0, extent / 12);
    return round(frequency);
}

// Determines whether a string represents a rest
bool is_rest(string s)
{
    // also we can use in this case sush check:
    // if (strlen(s) == 0)
    if (s[0] == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}
