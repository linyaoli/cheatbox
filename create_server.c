#include "server.h"

int main(void) {
    create_server(AF_UNIX, SOCK_STREAM, 0);
    return 1;
}
