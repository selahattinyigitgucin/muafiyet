#include "raylib.h"
#include <stdlib.h>
#include <math.h>

typedef struct Circle {
    struct Circle *previous;
    struct Circle *next;
    Vector2 position;
    float angular_v;
    float angle;
    float orbit_radius;
    float radius;
    Color color;
    bool is_dynamic;
} Circle;

Color RandomColor(void)
{
    Color c = {
        rand() % 256,
        rand() % 256,
        rand() % 256,
        255
    };
    return c;
}

int main(void)
{
    const int screenWidth = 800;
    const int screenHeight = 450;
    InitWindow(screenWidth, screenHeight, "muafiyet");
    SetTargetFPS(60);
    Circle *head = (Circle*)malloc(sizeof(Circle));
    head->previous = NULL;
    head->next = NULL;
    head->position = (Vector2){screenWidth/2, screenHeight/2};
    head->radius = 15;
    head->color = BLACK;
    head->is_dynamic = false;
    head->angle = 0;
    head->angular_v = 0;
    head->orbit_radius = 0;
    Circle *tail = head;
    float zoom = 1.0f;
    while (!WindowShouldClose())
    {
        float dt = GetFrameTime();
        float wheel = GetMouseWheelMove();
        zoom += wheel * 0.05f;
        if (zoom < 0.1f) zoom = 0.1f;
        if (zoom > 3.0f) zoom = 3.0f;
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            Circle *newCircle = (Circle*)malloc(sizeof(Circle));
            newCircle->previous = tail;
            newCircle->next = NULL;
            Vector2 mouse = GetMousePosition();
            newCircle->orbit_radius = sqrt((mouse.x - tail->position.x)* (mouse.x - tail->position.x)+((mouse.y - tail->position.y)* (mouse.y - tail->position.y)));;
            newCircle->radius = 8 + (rand() / (float)RAND_MAX) * 10;
            newCircle->angular_v = ((rand() / (float)RAND_MAX) * 2.0f + 1.0f) * (rand() % 2 ? 1 : -1);
            newCircle->angle = 0.0f;
            newCircle->is_dynamic = true;
            newCircle->color = RandomColor();
            newCircle->position = mouse;

            tail->next = newCircle;
            tail = newCircle;
        }
        if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT))
        {
            Circle *newCircle = (Circle*)malloc(sizeof(Circle));
            newCircle->previous = tail;
            newCircle->next = NULL;
            newCircle->radius = 15;
            newCircle->is_dynamic = false;
            newCircle->color = BLACK;
            newCircle->position = GetMousePosition();
            tail->next = newCircle;
            tail = newCircle;
        }
        if (IsMouseButtonPressed(MOUSE_BUTTON_MIDDLE) && tail->previous != NULL)
        {
            Circle *prev = tail->previous;  
            prev->next = NULL;             
            free(tail);                     
            tail = prev; 
        }
        

        BeginDrawing();
        ClearBackground(RAYWHITE);
        Circle *current = head;
        while (current != NULL)
        {
            if (current->is_dynamic && current->previous != NULL)
            {
                current->angle += current->angular_v * dt;
                current->position.x = current->previous->position.x + current->orbit_radius * cosf(current->angle) * zoom;
                current->position.y = current->previous->position.y + current->orbit_radius * sinf(current->angle) * zoom;
                DrawLineV(current->position, current->previous->position, LIGHTGRAY);
            }

            DrawCircleV(current->position, current->radius * zoom, current->color);
                    if (IsKeyDown(KEY_RIGHT)) current->position.x += 2.0f;
        if (IsKeyDown(KEY_LEFT)) current->position.x -= 2.0f;
        if (IsKeyDown(KEY_UP)) current->position.y -= 2.0f;
        if (IsKeyDown(KEY_DOWN)) current->position.y += 2.0f;
            current = current->next;
        }
        DrawText("sol tik yeni doner daire , sag tik yeni stabil daire , mouse tekerlegi zoom icin , orta buton son cemberi silmek icin", 10, 10, 10, DARKGRAY);
        EndDrawing();
       
    }


    CloseWindow();
    return 0;
}
