#include "numbers_input.hpp"
extern "C"
{
    #include "game/game.h"
    #include "game/print.h"
}

// Numbers Count X Digits

#define DIGIT_COUNT 4
#define ANSWER_COUNT 4

namespace NumbersInput
{
    static int Inputs[ANSWER_COUNT][DIGIT_COUNT];
    static int CursorPosition;

    static short PreviousInputs;

    static bool isButtonPressed(short button)
    {
        if (!(gPlayer1Controller->buttonPressed & button))
            return false;

        return (gPlayer1Controller->buttonPressed ^ PreviousInputs) & button;
    }

    static void Draw()
    {
        for (int i = 0; i < ANSWER_COUNT; i++)
        {
            char symText[] = "A";
            symText[0] += i;

            char numText[DIGIT_COUNT + 1];
            for (int j = 0; j < DIGIT_COUNT; j++)
                numText[j] = '0' + Inputs[i][j];
            numText[DIGIT_COUNT] = '\0';
        
            print_text_centered(40 + i * 80, 180, symText);
            print_text_centered(40 + i * 80, 160, numText);

            if (CursorPosition / DIGIT_COUNT == i)
            {
                char cursorText[DIGIT_COUNT + 1];
                for (int i = 0; i < DIGIT_COUNT; i++)
                    cursorText[i] = ' ';
                cursorText[DIGIT_COUNT] = '\0';

                cursorText[CursorPosition % DIGIT_COUNT] = '+';
                print_text_centered(40 + i * 80, 140, cursorText);
            }
        }
    }

    static void MoveCursor()
    {
        if (isButtonPressed(R_JPAD))
            CursorPosition++;
        if (isButtonPressed(D_JPAD))
            CursorPosition--;
        
        CursorPosition += (DIGIT_COUNT * ANSWER_COUNT);
        CursorPosition %= (DIGIT_COUNT * ANSWER_COUNT);
    }

    static void ChangeNumber()
    {
        int answer = CursorPosition / DIGIT_COUNT;
        int digit  = CursorPosition % DIGIT_COUNT;

        if (isButtonPressed(U_JPAD))
            Inputs[answer][digit]++;
        if (isButtonPressed(D_JPAD))
            Inputs[answer][digit]--;

        Inputs[answer][digit] += 10;
        Inputs[answer][digit] %= 10;
    }

    void Init()
    {
        for (int i = 0; i < DIGIT_COUNT; i++)
            for (int j = 0; j < ANSWER_COUNT; j++)
                Inputs[i][j] = 0;
    }

    void Step()
    {
        Draw();
        MoveCursor();
        ChangeNumber();

        PreviousInputs = gPlayer1Controller->buttonPressed;
    }
    
    void GetResults(s32 res[4])
    {
        for (int answer = 0; answer < ANSWER_COUNT; answer++)
        {
            res[answer] = 0;
            for (int digit = 0; digit < DIGIT_COUNT; digit++)
            {
                res[answer] *= 10;
                res[answer] += Inputs[answer][digit];
            }
        }
    }
}
