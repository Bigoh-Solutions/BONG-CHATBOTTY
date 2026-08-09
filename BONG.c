#include <stdio.h>
#include <string.h>
#include "raylib.h"

#define MAX_INPUT_CHARS 32

// Tell the compiler our external network function exists
extern void FetchBongData(const char *payload, char *outputBuffer, int maxLen);

int main() {
    InitWindow(1000, 1000, "BONG CHATBOTTY v3 - SOLE COMMAND");
    SetTargetFPS(60);

    char input_buffer[MAX_INPUT_CHARS + 1] = "\0";
    int letter_count = 0;
    char formatted_prompt[256] = "Awaiting input parameter vectors...";
    char display_response[512] = "Engine Status: Ready.";

    while (!WindowShouldClose()) {
        int key = GetCharPressed();
        while (key > 0) {
            if ((key >= 32) && (key <= 125) && (letter_count < MAX_INPUT_CHARS)) {
                input_buffer[letter_count] = (char)key;
                input_buffer[letter_count + 1] = '\0';
                letter_count++;
            }
            key = GetCharPressed();
        }

        if (IsKeyPressed(KEY_BACKSPACE)) {
            letter_count--;
            if (letter_count < 0) letter_count = 0;
            input_buffer[letter_count] = '\0';
        }

        if (IsKeyPressed(KEY_ENTER) && letter_count > 0) {
            snprintf(formatted_prompt, sizeof(formatted_prompt),
                     "what should i say when someone says %s? ai can you say it in one sentence? without giving out details and no more stuff",
                     input_buffer);

            strcpy(display_response, "Diving into data matrix streams...");
            
            // Call our clean isolated connection function
            FetchBongData(formatted_prompt, display_response, sizeof(display_response));
        }

        BeginDrawing();
        ClearBackground((Color){ 8, 8, 12, 255 });

        DrawRectangleLines(40, 40, 920, 920, PURPLE);
        DrawText("⚡ AI BONG CORE RENDERING SYSTEM (C / Libcurl / Raylib)", 60, 60, 22, VIOLET);
        DrawText("Authority: DHUBU / BIGOHSOLUTIONS (Sole Command)", 60, 95, 14, GRAY);

        DrawText("ENTER TRIGGER KEYWORD:", 60, 180, 16, RAYWHITE);
        DrawRectangle(60, 210, 450, 50, (Color){ 20, 20, 30, 255 });
        DrawRectangleLines(60, 210, 450, 50, DARKPURPLE);
        
        if (letter_count == 0) {
            DrawText("Type keyword & hit ENTER...", 75, 225, 16, DARKGRAY);
        } else {
            DrawText(input_buffer, 75, 225, 18, BLUE);
        }

        DrawText("Evaluated Prompt Query Vector Sent to API String:", 60, 310, 14, DARKPURPLE);
        DrawText(formatted_prompt, 60, 340, 13, RAYWHITE);

        DrawText("--- SINGLE SENTENCE ENGINE RESPONSE ---", 60, 450, 18, LIME);
        DrawRectangle(60, 490, 880, 120, (Color){ 12, 12, 18, 255 });
        DrawRectangleLines(60, 490, 880, 120, (Color){ 30, 30, 45, 255 });
        
        DrawText(display_response, 80, 530, 16, BLUE);
        DrawText("Lineage: [2025-2026 Phase] | Status: Online", 60, 920, 13, GRAY);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
