//
// Created by xoselolo on 01/01/2021.
//

#ifndef CHAT_SCREEN_SCREEN_H
#define CHAT_SCREEN_SCREEN_H

#include <ncurses.h>
#include <string.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#define SUCCESS 0
#define FAILURE 1

#define USERNAME_MAXCHAR 30
#define MESSAGE_MAXCHAR 1000

typedef struct{
    int hores;
    int minuts;
    int segons;
}Hora;

typedef struct {
    int id_missatge;
    char content[MESSAGE_MAXCHAR];
    char sender[USERNAME_MAXCHAR];
    Hora hora;
}Missatge;

typedef struct{
    int num_missatges;
    Missatge* missatges;
}Screen;

//static char SCREEN_input[MESSAGE_MAXCHAR];

int SCREEN_init();
int SCREEN_waitMsg(char** in);
int SCREEN_newMsg(char* in);
int SCREEN_writeMsgInLine(Missatge missatge, int line);
void SCREEN_paintNewMessageZone();
int SCREEN_close();
void SCREEN_free();

#endif //CHAT_SCREEN_SCREEN_H
