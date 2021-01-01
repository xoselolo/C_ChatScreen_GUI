#include "SCREEN.h"
#include <signal.h>

// ----------- MAIN -----------

static char* msg;

static void sigint() {
    // tanquem la finestra
    SCREEN_close();
    // Alliberem memoria
    free(msg);
    SCREEN_free();
    // ens matem
    raise(SIGKILL);
}

int main() {
    SCREEN_init();

    signal(SIGINT, sigint);

    msg = (char*) malloc(sizeof(char) * MESSAGE_MAXCHAR);
    while (1){
        SCREEN_paintNewMessageZone();

        // wait until the user writes a message
        SCREEN_waitMsg(&msg);
        SCREEN_newMsg(msg);
    }

    // Cerrar ventana
    SCREEN_close();
    return 1;
}
// ----------- END MAIN -------------
