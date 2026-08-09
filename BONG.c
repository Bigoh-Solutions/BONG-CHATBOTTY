#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include "raylib.h"
#include "raymath.h"
#include "rlgl.h"

#define MAX_INPUT_LENGTH 256
#define MAX_MESSAGES 50
#define MESSAGE_BUFFER_SIZE 1024

typedef struct {
    char text[MESSAGE_BUFFER_SIZE];
    int isAI;  // 1 if AI, 0 if user
} Message;

typedef struct {
    Message messages[MAX_MESSAGES];
    int count;
    char input[MAX_INPUT_LENGTH];
    int inputLength;
} ChatState;

// Simple AI response generator
const char* getAIResponse(const char* userInput) {
    static char response[MESSAGE_BUFFER_SIZE];
    
    // Simple pattern matching for basic responses
    if (strstr(userInput, "hello") || strstr(userInput, "hi")) {
        snprintf(response, sizeof(response), "Hey there! ;.;");
    } else if (strstr(userInput, "how are you")) {
        snprintf(response, sizeof(response), "I'm doing great! Thanks for asking ;.;");
    } else if (strstr(userInput, "what is your name")) {
        snprintf(response, sizeof(response), "I'm BONG! Your friendly AI buddy ;.;");
    } else if (strstr(userInput, "bye") || strstr(userInput, "goodbye")) {
        snprintf(response, sizeof(response), "See you soon! Take care ;.;");
    } else if (strstr(userInput, "joke")) {
        snprintf(response, sizeof(response), "Why did the AI go to school? To improve its learning model! ;.;");
    } else if (strstr(userInput, "help")) {
        snprintf(response, sizeof(response), "I can chat with you! Try asking me about myself ;.;");
    } else {
        snprintf(response, sizeof(response), "That's interesting! Tell me more ;.;");
    }
    
    return response;
}

void drawAIFace(Vector2 pos, float scale) {
    // Draw the face ;.;
    float faceSize = 100 * scale;
    
    // Draw background circle
    DrawCircle(pos.x, pos.y, faceSize * 0.6f, (Color){100, 150, 200, 255});
    DrawCircleLines(pos.x, pos.y, faceSize * 0.6f, (Color){50, 100, 150, 255});
    
    // Draw left eye ;
    float eyeDistance = faceSize * 0.2f;
    DrawCircle(pos.x - eyeDistance, pos.y - faceSize * 0.15f, faceSize * 0.08f, BLACK);
    DrawCircle(pos.x - eyeDistance - faceSize * 0.05f, pos.y - faceSize * 0.15f, faceSize * 0.04f, WHITE);
    
    // Draw right eye .
    DrawCircle(pos.x + eyeDistance, pos.y - faceSize * 0.15f, faceSize * 0.06f, BLACK);
    DrawCircle(pos.x + eyeDistance, pos.y - faceSize * 0.15f, faceSize * 0.03f, WHITE);
    
    // Draw mouth (;)
    DrawText(";", pos.x - 8, pos.y + faceSize * 0.2f, 20, BLACK);
}

void drawChatUI(ChatState* chat, int screenWidth, int screenHeight) {
    // Clear background
    DrawRectangle(0, 0, screenWidth, screenHeight, (Color){240, 240, 245, 255});
    
    // Draw AI face at the top
    drawAIFace((Vector2){screenWidth / 2, 80}, 1.5f);
    
    // Draw "BONG AI" title
    DrawText("BONG AI", screenWidth / 2 - 40, 20, 20, (Color){50, 100, 150, 255});
    
    // Draw chat messages area
    DrawRectangle(20, 160, screenWidth - 40, screenHeight - 240, WHITE);
    DrawRectangleLines(20, 160, screenWidth - 40, screenHeight - 240, (Color){100, 100, 100, 255});
    
    // Draw messages
    int msgY = 170;
    for (int i = 0; i < chat->count; i++) {
        if (msgY > screenHeight - 100) break;
        
        Color msgColor = chat->messages[i].isAI ? (Color){200, 220, 255, 255} : (Color){220, 220, 220, 255};
        const char* sender = chat->messages[i].isAI ? "BONG: " : "You: ";
        
        DrawRectangle(30, msgY - 5, screenWidth - 60, 30, msgColor);
        DrawText(sender, 40, msgY, 14, BLACK);
        DrawText(chat->messages[i].text, 120, msgY, 14, (Color){50, 50, 50, 255});
        
        msgY += 40;
    }
    
    // Draw input area
    DrawRectangle(20, screenHeight - 70, screenWidth - 40, 50, (Color){230, 230, 235, 255});
    DrawRectangleLines(20, screenHeight - 70, screenWidth - 40, 50, (Color){100, 100, 100, 255});
    DrawText("Input:", 30, screenHeight - 60, 14, BLACK);
    DrawText(chat->input, 100, screenHeight - 60, 14, BLACK);
    
    // Draw cursor
    if (((int)(GetTime() * 2) % 2) == 0) {
        DrawText("|", 100 + MeasureText(chat->input, 14), screenHeight - 60, 14, BLACK);
    }
    
    // Draw instructions
    DrawText("Press ENTER to send | ESC to quit", 30, screenHeight - 25, 12, (Color){100, 100, 100, 255});
}

void handleInput(ChatState* chat) {
    int key = GetCharPressed();
    
    while (key > 0) {
        if ((key >= 32) && (key <= 125) && (chat->inputLength < MAX_INPUT_LENGTH - 1)) {
            chat->input[chat->inputLength] = (char)key;
            chat->inputLength++;
            chat->input[chat->inputLength] = '\0';
        }
        key = GetCharPressed();
    }
    
    if (IsKeyPressed(KEY_BACKSPACE)) {
        if (chat->inputLength > 0) {
            chat->inputLength--;
            chat->input[chat->inputLength] = '\0';
        }
    }
    
    if (IsKeyPressed(KEY_ENTER)) {
        if (chat->inputLength > 0) {
            // Add user message
            if (chat->count < MAX_MESSAGES) {
                strncpy(chat->messages[chat->count].text, chat->input, MESSAGE_BUFFER_SIZE - 1);
                chat->messages[chat->count].isAI = 0;
                chat->count++;
            }
            
            // Get AI response
            if (chat->count < MAX_MESSAGES) {
                const char* aiResponse = getAIResponse(chat->input);
                strncpy(chat->messages[chat->count].text, aiResponse, MESSAGE_BUFFER_SIZE - 1);
                chat->messages[chat->count].isAI = 1;
                chat->count++;
            }
            
            // Clear input
            chat->inputLength = 0;
            chat->input[0] = '\0';
        }
    }
}

int main(void) {
    const int screenWidth = 800;
    const int screenHeight = 600;
    
    InitWindow(screenWidth, screenHeight, "BONG AI - ;.;");
    SetTargetFPS(60);
    
    ChatState chat = {0};
    
    // Initial greeting
    const char* greeting = "Hi! I'm BONG AI! ;.; What would you like to talk about?";
    strncpy(chat.messages[0].text, greeting, MESSAGE_BUFFER_SIZE - 1);
    chat.messages[0].isAI = 1;
    chat.count = 1;
    
    while (!WindowShouldClose() && !IsKeyPressed(KEY_ESCAPE)) {
        handleInput(&chat);
        
        BeginDrawing();
        drawChatUI(&chat, screenWidth, screenHeight);
        EndDrawing();
    }
    
    CloseWindow();
    return 0;
}
