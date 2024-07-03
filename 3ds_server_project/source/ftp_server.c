#include <3ds.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <dirent.h>

#define FTP_PORT 5000
#define FTP_ROOT "/3ds/data/http_ftp/public_htmk"

static Thread ftp_thread;
static volatile bool ftp_running = false;

void* ftp_server_thread(void* arg) {
    printf("FTP server thread started.\n");

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
    address.sin_port = htons(FTP_PORT);

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

    ftp_running = true;

    while (ftp_running) {
        // Accept incoming connection
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
            perror("accept");
            continue;
        }

        // Handle FTP commands
        while (1) {
            int valread = read(new_socket, buffer, BUFFER_SIZE);
            if (valread <= 0) {
                break;
            }

            // Parse FTP command
            char command[16], argument[BUFFER_SIZE];
            sscanf(buffer, "%s %s", command, argument);

            if (strcmp(command, "GET") == 0) {
                send_file(new_socket, argument);
            } else if (strcmp(command, "PUT") == 0) {
                receive_file(new_socket, argument);
            } else if (strcmp(command, "LIST") == 0) {
                list_files(new_socket);
            } else if (strcmp(command, "QUIT") == 0) {
                break;
            } else {
                send(new_socket, "Invalid command\n", 16, 0);
            }
        }

        // Close socket
        close(new_socket);
    }

    close(server_fd);
    printf("FTP server thread stopping.\n");
    return NULL;
}

void start_ftp_server() {
    printf("Starting FTP server on port %d...\n", FTP_PORT);
    ftp_thread = threadCreate(ftp_server_thread, NULL, 16 * 1024, 0x3F, -2, false);
    if (!ftp_thread) {
        printf("Failed to create FTP server thread!\n");
    }
}

void stop_ftp_server() {
    printf("Stopping FTP server...\n");
    ftp_running = false;
    threadJoin(ftp_thread, U64_MAX);
    threadFree(ftp_thread);
}

void send_file(int client_fd, const char *filename) {
    char full_path[BUFFER_SIZE];
    sprintf(full_path, "%s/%s", FTP_ROOT, filename);

    FILE *fp = fopen(full_path, "rb");
    if (fp == NULL) {
        send(client_fd, "File not found\n", 15, 0);
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

    // Send file content
    send(client_fd, file_content, file_size, 0);

    free(file_content);
}

void receive_file(int client_fd, const char *filename) {
    char full_path[BUFFER_SIZE];
    sprintf(full_path, "%s/%s", FTP_ROOT, filename);

    FILE *fp = fopen(full_path, "wb");
    if (fp == NULL) {
        send(client_fd, "Failed to create file\n", 22, 0);
        return;
    }

    char buffer[BUFFER_SIZE];
    int bytes_received;
    while ((bytes_received = recv(client_fd, buffer, BUFFER_SIZE, 0)) > 0) {
        fwrite(buffer, 1, bytes_received, fp);
    }

    fclose(fp);
}

void list_files(int client_fd) {
    DIR *dir;
    struct dirent *ent;
    char list_buffer[BUFFER_SIZE] = {0};
    char filename[BUFFER_SIZE];

    if ((dir = opendir(FTP_ROOT)) != NULL) {
        while ((ent = readdir(dir)) != NULL) {
            sprintf(filename, "%s\n", ent->d_name);
            strcat(list_buffer, filename);
        }
        closedir(dir);
    } else {
        perror("Failed to open directory");
    }

    send(client_fd, list_buffer, strlen(list_buffer), 0);
}
