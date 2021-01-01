//
// Created by xoselolo on 01/01/2021.
//

#include "SCREEN.h"

static int nextLine = 1;
static int nextId = 1;
static char* username = "xoselolo";
static int filas = 0, columnas = 0;
static Screen screen;

// ---------- AUXILIARY ----------------
Hora getHoraActual();

Missatge createMsg(char sender[USERNAME_MAXCHAR], char content[MESSAGE_MAXCHAR], int id){
    Missatge msg;

    msg.id_missatge = id;
    strcpy(msg.sender, sender);
    strcpy(msg.content, content);
    msg.hora = getHoraActual();

    return msg;
}

Hora getHoraActual() {
    Hora result;
    time_t rawtime;
    struct tm * timeinfo;

    time(&rawtime);
    timeinfo = localtime(&rawtime);

    result.hores = timeinfo->tm_hour;
    result.minuts = timeinfo->tm_min;
    result.segons = timeinfo->tm_sec;

    return result;
}

void cleanLine(int line){
    move(line, 1);
    clrtoeol();
    move(line, 1);
}

void repaint() {
    for (int i = 0; i < screen.num_missatges; i++) {
        SCREEN_writeMsgInLine(screen.missatges[i], i);
    }
    refresh();
}

void reorder(){
    for (int i = 0; i < screen.num_missatges - 1; i++) {
        screen.missatges[i].hora = screen.missatges[i+1].hora;
        screen.missatges[i].id_missatge = screen.missatges[i+1].id_missatge;
        strcpy(screen.missatges[i].sender, screen.missatges[i+1].sender);
        strcpy(screen.missatges[i].content, screen.missatges[i+1].content);
    }
}

// ---------- END AUXILIARY ---------------

// ------------ MODULE FUNCTIONS AND METHODS -------------
int SCREEN_init(){
    initscr();
    start_color();
    init_pair(1, COLOR_RED, COLOR_BLACK);
    init_pair(2, COLOR_WHITE, COLOR_BLACK);
    init_pair(3, COLOR_BLUE, COLOR_BLACK);
    init_pair(4, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(5, COLOR_GREEN, COLOR_BLACK);
    init_pair(6, COLOR_CYAN, COLOR_BLACK);
    init_pair(7, COLOR_YELLOW, COLOR_BLACK);
    bkgd(COLOR_PAIR(2));
    attron(COLOR_PAIR(2));
    mvprintw(0, 1, "........ Welcome %s\n", username);
    attroff(COLOR_PAIR(2));
    refresh();

    // Obtener filas y columunas de la ventana
    getmaxyx(stdscr, filas, columnas);

    // Initialize filas
    screen.num_missatges = 1;
    screen.missatges = (Missatge*)malloc(sizeof(Missatge) * (filas - 3));

    return SUCCESS;
}

int SCREEN_waitMsg(char** in){
    getstr(*in);
    return SUCCESS;
}

int SCREEN_newMsg(char* in){
    if (nextLine == filas - 3){
        reorder();
        screen.missatges[screen.num_missatges - 1] = createMsg(username, in, nextId);
        repaint();
    }else{
        screen.missatges[nextLine] = createMsg(username, in, nextId);
        SCREEN_writeMsgInLine(screen.missatges[nextLine], nextLine);
        nextLine++;
        screen.num_missatges++;
    }
    nextId++;
    return SUCCESS;
}

int SCREEN_writeMsgInLine(Missatge missatge, int line) {
    //move(line, 1);
    cleanLine(line);
    attron(COLOR_PAIR(2)); // blanco
    char text[MESSAGE_MAXCHAR + USERNAME_MAXCHAR + 20];
    sprintf(text, " %d:%d:%d - %s : %s", missatge.hora.hores, missatge.hora.minuts,
            missatge.hora.segons, missatge.sender, missatge.content);
    printw(text);
    attroff(COLOR_PAIR(2));
    refresh();
    return SUCCESS;
}

void SCREEN_paintNewMessageZone(){
    attron(COLOR_PAIR(2));

    cleanLine(filas - 3);
    cleanLine(filas - 2);
    cleanLine(filas - 1);
    move(filas - 3, 0);
    for (int i = 0; i < columnas; i++) {
        printw("_");
    }
    mvprintw(filas - 1, 0, "Escribe tu mensaje: ");

    attroff(COLOR_PAIR(2));
    refresh();
}

int SCREEN_close(){
    endwin();
    return SUCCESS;
}

void SCREEN_free(){
    free(screen.missatges);
}
// ------------ MODULE AUXILIARY FUNCTIONS AND METHODS -------------
