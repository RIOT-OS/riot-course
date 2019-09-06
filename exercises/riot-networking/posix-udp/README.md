## UDP networking using the Sock API

### Introduction

In this exercise, we propose to implement 2 UDP applications using the Posix
compliant API of RIOT: one client will periodically send the "Hello Server"
message, the server prints any messages received.

The server listens on port 8888. The client sends its messages to the IPv6
link-local address of the server.

Both applications will run as RIOT native instances.

### Exercise

1. If not already done, configure 2 tap interfaces for to use with 2 native
  instances. The server will run on `tap0` and the client on `tap1`.

2. Implement the server application

  - Go into the `~/riot-course/exercises/riot-networking/posix-udp/server` application
    directory
  - Add the posix sockets module dependency to the application `Makefile`:
    ```mk
    USEMODULE += posix_sockets
    ```
  - In the `main.c` file, create the server socket:
    ```c
    int server_socket = socket(AF_INET6, SOCK_DGRAM, IPPROTO_UDP);
    if (server_socket < 0) {
        puts("error initializing socket");
        server_socket = 0;
        return 1;
    }
    ```
  - Instanciate and configure the server address:
  ```c
  struct sockaddr_in6 server_addr;
  server_addr.sin6_family = AF_INET6;
  memset(&server_addr.sin6_addr, 0, sizeof(server_addr.sin6_addr));
  server_addr.sin6_port = htons(SERVER_PORT);
  ```
  - Bind the socket to the server address:
  ```
  if (bind(server_socket, (struct sockaddr *)&server_addr,
          sizeof(server_addr)) < 0) {
      server_socket = -1;
      puts("error binding socket");
      return 1;
  }
  ```
  - Start listening to incoming packets:
    ```c
    int res;
    struct sockaddr_in6 src;
    socklen_t src_len = sizeof(struct sockaddr_in6);
    if ((res = recvfrom(server_socket, server_buffer, sizeof(server_buffer), 0,
                        (struct sockaddr *)&src, &src_len)) < 0) {
        puts("Error on receive");
    }
    else if (res == 0) {
        puts("Peer did shut down");
    }
    else {
        printf("Message received: ");
        puts(server_buffer);
        sendto(server_socket, SERVER_MESSAGE, sizeof(SERVER_MESSAGE), 0,
               (struct sockaddr *)&src, sizeof(src));
    }
    ```

3. Implement the client application

  - Go into the `~/riot-course/exercises/riot-networking/posix-udp/client` application
    directory
  - Add the posix sockets module dependency to the application `Makefile`:
    ```mk
    USEMODULE += posix_sockets
    ```
  - In the `main.c` file, create the socket:
    ```c
    int s = socket(AF_INET6, SOCK_DGRAM, IPPROTO_UDP);
    if (s < 0) {
        puts("error initializing socket");
        return 1;
    }
    ```
  - Configure the destination address (based on `SERVER_ADDR` and `SERVER_PORT` macros)
    ```c
    /* configure the destination address */
    struct sockaddr_in6 dst;
    dst.sin6_family = AF_INET6;

    /* parse destination address */
    ipv6_addr_from_str((ipv6_addr_t *)&dst.sin6_addr, SERVER_ADDR);

    /* parse port */
    dst.sin6_port = htons(SERVER_PORT);
    ```
  - Sends packets to the server:
    ```c
    sendto(s, CLIENT_MESSAGE, strlen(CLIENT_MESSAGE), 0,
              (struct sockaddr *)&dst, sizeof(dst));
    ```

4. Build and start the server application on `tap0`. Note the link-local address of the
  server application:
  ```sh
  $ make -C ~/riot-course/exercises/riot-networking/posix-udp/server
  $ make PORT=tap0 -C ~/riot-course/exercises/riot-networking/posix-udp/server term
  Configured network interfaces:
  Iface  5  HWaddr: F2:9D:F4:58:14:D4
          L2-PDU:1500 MTU:1500  HL:64  Source address length: 6
          Link type: wired
          inet6 addr: fe80::f09d:f4ff:fe58:14d4  scope: local  TNT[1]
          inet6 group: ff02::1
          inet6 group: ff02::1:ff58:14d4
  ```
  Here the link-local address of the server is **fe80::f09d:f4ff:fe58:14d4**.
  Keep the terminal open and the server application running.

5. Build and start the client application on `tap1`. Use the `SERVER_ADDR` to
  specify the server address to use:
  ```sh
  $ make SERVER_ADDR=fe80::f09d:f4ff:fe58:14d4 -C ~/riot-course/exercises/riot-networking/posix-udp/client
  $ make PORT=tap1 -C ~/riot-course/exercises/riot-networking/posix-udp/client term

  On the server terminal, you should also see the following messages:
  ```
  Message received: Hello Server
  Message received: Hello Server
  Message received: Hello Server
  Message received: Hello Server
  Message received: Hello Server
  ```

Now let's continue with the
[networking slides](https://riot-os.github.io/riot-course/slides/04-networking-in-riot/#19).