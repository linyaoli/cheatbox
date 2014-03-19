#include "client.h"
#include "log.h"

int create_client() {

    struct sockaddr_un address;
    int socket_fd, nbytes;
    char buffer[256];

    socket_fd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (socket_fd < 0) {
        init_log("create socket failed");
        return 1;
    }

    memset(&address, 0, sizeof(struct sockaddr_un));
    address.sun_family = AF_UNIX;
//    snprintf(address.sun_path, UNIX_PATH_MAX, "./demo_socket");
    strcpy(address.sun_path, "./demo_socket");

    if (connect(socket_fd, (struct sockaddr*) &address,
            sizeof(struct sockaddr_un)) != 0) {
        init_log("connect failed");
        return 1;
    }

    nbytes = snprintf(buffer, 256, "hello server");
    write(socket_fd, buffer, nbytes);

    return 0;
}
