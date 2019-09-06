## UDP networking using the Sock API

### Introduction

In this exercise, we propose to implement 2 UDP applications:
- one client that periodically sends the "Hello Server" message
- one server that echoes any message received

The server listens on port 8888. The client sends its messages to the IPv6
link-local address of the server.

Both applications will run as RIOT native instances.

### Exercise

1. If not already done, configure 2 tap interfaces for to use with 2 native
  instances. The server will run on `tap0` and the client on `tap1`.

2. Implement the server application

  - Go into the `~/riot-course/exercises/riot-networking/sock-udp/server` application
    directory
  - Add the low-level driver modules dependencies to the application `Makefile`:
    ```mk
    USEMODULE += gnrc_netdev_default
    USEMODULE += auto_init_gnrc_netif
    ```
  - Add the network modules dependencies to the application `Makefile`:
    ```mk
    USEMODULE += gnrc_ipv6_default
    USEMODULE += gnrc_sock_udp
    ```
  - In the `main.c` file, create the sock UDP endpoint:
    ```c
    sock_udp_ep_t local = SOCK_IPV6_EP_ANY;
    sock_udp_t sock;
    local.port = SERVER_PORT;
    if (sock_udp_create(&sock, &local, NULL, 0) < 0) {
        puts("Error creating UDP sock");
        return 1;
    }
    ```
  - Implement the server side UDP echo:
    ```c
    sock_udp_ep_t remote;
    ssize_t res;
    if ((res = sock_udp_recv(&sock, buf, sizeof(buf), SOCK_NO_TIMEOUT,
                             &remote)) >= 0) {

        printf("Message received: %s\n", (char*)buf);
        if (sock_udp_send(&sock, buf, res, &remote) < 0) {
            puts("Error sending reply");
        }
    }
    ```

3. Implement the client application

  - Go into the `~/riot-course/exercises/riot-networking/sock-udp/client` application
    directory
  - Add the low-level driver modules dependencies to the application `Makefile`:
    ```mk
    USEMODULE += gnrc_netdev_default
    USEMODULE += auto_init_gnrc_netif
    ```
  - Add the network modules dependencies to the application `Makefile`:
    ```mk
    USEMODULE += gnrc_ipv6_default
    USEMODULE += gnrc_sock_udp
    ```
  - In the `main.c` file, create the sock UDP endpoint:
    ```c
    sock_udp_ep_t local = SOCK_IPV6_EP_ANY;
    sock_udp_t sock;
    local.port = 0xabcd;
    if (sock_udp_create(&sock, &local, NULL, 0) < 0) {
        puts("Error creating UDP sock");
        return 1;
    }
    ```
  - Convert the server address macro string to an `ipv6_addr_t`:
    ```c
    sock_udp_ep_t remote = { .family = AF_INET6  };

    /* Convert server address from string to ipv6_addr_t */
    if (ipv6_addr_from_str((ipv6_addr_t *)&remote.addr.ipv6, SERVER_ADDR) == NULL) {
        puts("Cannot convert server address");
        sock_udp_close(&sock);
        return 1;
    }
    ```
  - Implement sending CLIENT_MESSAGE to the server:
    ```c
    if (sock_udp_send(&sock, CLIENT_MESSAGE, sizeof(CLIENT_MESSAGE), &remote) < 0) {
        puts("Error sending message");
        sock_udp_close(&sock);
        return 1;
    }
    ```
  - Implement the listening of the echo sent by the server:
    ```c
    ssize_t res;
    if ((res = sock_udp_recv(&sock, buf, sizeof(buf), SOCK_NO_TIMEOUT,
                             &remote)) >= 0) {

        printf("Message received: %s\n", (char*)buf);
    }
    ```

4. Build and start the server application on `tap0`. Note the link-local address of the
  server application:
  ```sh
  $ make -C ~/riot-course/exercises/riot-networking/sock-udp/server
  $ make PORT=tap0 -C ~/riot-course/exercises/riot-networking/sock-udp/server term
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
  $ make SERVER_ADDR=fe80::f09d:f4ff:fe58:14d4 -C ~/riot-course/exercises/riot-networking/sock-udp/client
  $ make PORT=tap1 -C ~/riot-course/exercises/riot-networking/sock-udp/client term
  Timed out
  Received message: "Hello Server"
  Received message: "Hello Server"
  Received message: "Hello Server"
  Received message: "Hello Server"

  On the server terminal, you should also see the following messages:
  ```
  Message received: Hello Server
  Error sending reply
  Message received: Hello Server
  Message received: Hello Server
  Message received: Hello Server
  Message received: Hello Server
  ```

Now let's continue with the
[networking slides](https://riot-os.github.io/riot-course/slides/04-networking-in-riot/#17).
