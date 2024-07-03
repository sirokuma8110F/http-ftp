#include <3ds.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <errno.h>
#include <dirent.h>

#define HTTP_PORT 8000
#define BUFFER_SIZE 1024
#define DOCUMENT_ROOT "/3ds/data/http_ftp/public_html"

static Thread http_thread;
static volatile bool http_running = false;

void* http_server_thread(void* arg) {
    printf("HTTP server thread started.\n");

    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[BUFFER_SIZE] = {0};

    // Create socket
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        return NULL;
    }

    // Set socket options
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("setsockopt");
        return NULL;
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(HTTP_PORT);

    // Bind socket to port
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        return NULL;
    }

    // Start listening
    if (listen(server_fd, 3) < 0) {
        perror("listen");
        return NULL;
    }

    http_running = true;

    while (http_running) {
        // Accept incoming connection
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
            perror("accept");
            continue;
        }

        // Read request
        int valread = read(new_socket, buffer, BUFFER_SIZE);

        if (valread > 0) {
            // Parse request
            char method[16], path[BUFFER_SIZE], protocol[16];
            sscanf(buffer, "%s %s %s", method, path, protocol);

            // Handle PHP request
            if (strstr(path, ".php") != NULL) {
                // Execute PHP script
                char php_command[BUFFER_SIZE];
                sprintf(php_command, "php-cgi -f %s%s", DOCUMENT_ROOT, path);

                FILE *fp = popen(php_command, "r");
                if (fp == NULL) {
                    perror("Failed to execute PHP script");
                    close(new_socket);
                    continue;
                }

                // Send PHP output to client
                char php_output[BUFFER_SIZE];
                while (fgets(php_output, BUFFER_SIZE, fp) != NULL) {
                    send(new_socket, php_output, strlen(php_output), 0);
                }

                pclose(fp);
            } else {
                // Serve static files
                serve_file(new_socket, path);
            }
        }

        // Close socket
        close(new_socket);
    }

    close(server_fd);
    printf("HTTP server thread stopping.\n");
    return NULL;
}

void start_http_server() {
    printf("Starting HTTP server on port %d...\n", HTTP_PORT);
    http_thread = threadCreate(http_server_thread, NULL, 16 * 1024, 0x3F, -2, false);
    if (!http_thread) {
        printf("Failed to create HTTP server thread!\n");
    }
}

void stop_http_server() {
    printf("Stopping HTTP server...\n");
    http_running = false;
    threadJoin(http_thread, U64_MAX);
    threadFree(http_thread);
}

void serve_file(int client_fd, const char *path) {
    char full_path[BUFFER_SIZE];
    sprintf(full_path, "%s%s", DOCUMENT_ROOT, path);

    FILE *fp = fopen(full_path, "rb");
    if (fp == NULL) {
        perror("Failed to open file");
        return;
    }

    // Get file size
    fseek(fp, 0, SEEK_END);
    long file_size = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    // Read file content
    char *file_content = (char *)malloc(file_size);
    fread(file_content, 1, file_size, fp);
    fclose(fp);

    // Send HTTP headers
    char headers[BUFFER_SIZE];
    sprintf(headers, "HTTP/1.1 200 OK\r\nContent-Length: %ld\r\n\r\n", file_size);
    send(client_fd, headers, strlen(headers), 0);

    // Send file content
    send(client_fd, file_content, file_size, 0);

    free(file_content);
}
