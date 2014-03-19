#include "server.h"
#include "log.h"

int connection_handler(int connection_fd) {
    int nbytes;
    char buffer[256];

    nbytes = read(connection_fd, buffer, 256);
    buffer[nbytes] = 0;

    init_log("msg from client");
    nbytes = snprintf(buffer, 256, "this is server, hi");
    write(connection_fd, buffer, nbytes);

    close(connection_fd);
    return 0;
}

/**
 *  domain = PF_UNIX
 *  type = SOCK_STREAM
 *  protocal = 0
 */
int create_server(int domain, int type, int protocol) {
    struct sockaddr_un address;
    int socket_fd, connection_fd;
    socklen_t address_length;
    pid_t child;

    socket_fd = socket(domain, type, protocol);
    if (socket_fd < 0) {
        init_log("create socket failed!");
        return 1;
    }
    unlink("./demo_socket");

    memset(&address, 0, sizeof(struct sockaddr_un));
    address.sun_family = AF_UNIX;
//    snprintf(address.sun_path, UNIX_PATH_MAX, "./demo_socket");
    strcpy(address.sun_path, "./demo_socket");

    if (bind(socket_fd, (struct sockaddr *) &address,
                sizeof(struct sockaddr_un)) != 0) {
        init_log("bind failed!");
        return 1;
    }

    if (listen(socket_fd, 5) != 0) {
        init_log("listen failed!");
        return 1;
    }
    address_length = sizeof(address);

    while ((connection_fd = accept(socket_fd, (struct sockaddr*) &address,
                    &address_length)) > -1) {
        child = fork();
        if (child == 0) {
            return connection_handler(connection_fd);
        }
        close(connection_fd);
    }

    close(socket_fd);
    unlink("./demo_socket");

    return 0;
}
