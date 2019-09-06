# Basic IPv6 Networking using the shell

In this exercise, we propose to discover RIOT basic networking capabilities
using the existing `gnrc_networking` example.
You will perform basic IPv6 communication between 2 native instances on
your local computer.

## Prepare the network on your Linux host

1. Configure a network bridge with 2 virtual interfaces (`tap`) with the
   following command (user password is user):

  ```sh
  $ sudo ~/riot-course/RIOT/dist/tools/tapsetup/tapsetup -c 2

  ```

2. Verify the 3 new interfaces (`tap0`, `tap1` and `tapbr0`) are created on
  your host:
  ```
  $ ifconfig
  [...]

  tap0: flags=4099<UP,BROADCAST,MULTICAST>  mtu 1500
          ether a2:46:e0:e5:74:f0  txqueuelen 1000  (Ethernet)
          RX packets 0  bytes 0 (0.0 B)
          RX errors 0  dropped 0  overruns 0  frame 0
          TX packets 0  bytes 0 (0.0 B)
          TX errors 0  dropped 0 overruns 0  carrier 0  collisions 0

  tap1: flags=4099<UP,BROADCAST,MULTICAST>  mtu 1500
          ether 46:bc:5f:34:78:a5  txqueuelen 1000  (Ethernet)
          RX packets 0  bytes 0 (0.0 B)
          RX errors 0  dropped 0  overruns 0  frame 0
          TX packets 0  bytes 0 (0.0 B)
          TX errors 0  dropped 0 overruns 0  carrier 0  collisions 0

  tapbr0: flags=4099<UP,BROADCAST,MULTICAST>  mtu 1500
          inet6 fe80::aaaa:xxxx:yyyy:zzzz  prefixlen 64  scopeid 0x20<link>
          ether 46:bc:5f:34:78:a5  txqueuelen 1000  (Ethernet)
          RX packets 0  bytes 0 (0.0 B)
          RX errors 0  dropped 0  overruns 0  frame 0
          TX packets 9  bytes 917 (917.0 B)
          TX errors 0  dropped 0 overruns 0  carrier 0  collisions 0
  ```

## Start 2 native instances

1. Build the `gnrc_networking` example application for native:

  ```sh
  $ make -C ~/riot-course/RIOT/examples/gnrc_networking all
  ```

2. In separate terminals, start 2 native instances of RIOT on each `tap`
interface created (use `tap0` and `tap1`):

  ```sh
  $ sudo PORT=tap0 make -C ~/riot-course/RIOT/examples/gnrc_networking term
  main(): This is RIOT! (Version: workshop-captronic)
  RIOT network stack example application
  All up, running the shell now
  > help
  ```

## Exchange ICMPv6 (ping) messages

1. On each instance, display the network configuration using `ifconfig`

  ```sh
  > ifconfig
  Iface  6  HWaddr: 0a:46:47:86:27:e8
            MTU:1500  HL:64  RTR  
            RTR_ADV  
            Source address length: 6
            Link type: wired
            inet6 addr: fe80::846:47ff:fe86:27e8  scope: local
            inet6 group: ff02::2
  [...]
  ```

2. Verify ping is working between each instances: use the ipv6 address with
   `scope: local`
  ```sh
  > ping6 fe80::846:47ff:fe86:27e8
  12 bytes from fe80::a046:e0ff:fee5:74f1: icmp_seq=0 ttl=64 time=0.752 ms
  12 bytes from fe80::a046:e0ff:fee5:74f1: icmp_seq=1 ttl=64 time=0.594 ms
  12 bytes from fe80::a046:e0ff:fee5:74f1: icmp_seq=2 ttl=64 time=0.586 ms

  --- fe80::a046:e0ff:fee5:74f1 PING statistics ---
  3 packets transmitted, 3 packets received, 0% packet loss
  round-trip min/avg/max = 0.586/0.644/0.752 ms
  ```

3. Verify ping is working between your host and the instances. In this case, you
  must specify the interface name to tell Linux on which interface the RIOT
  instance is reachable:
  ```sh
  $ ping6 fe80::846:47ff:fe86:27e8%tapbr0
  PING fe80::a046:e0ff:fee5:74f1%tapbr0(fe80::a046:e0ff:fee5:74f1%tapbr0) 56 data bytes
  64 bytes from fe80::a046:e0ff:fee5:74f1%tapbr0: icmp_seq=1 ttl=64 time=0.293 ms
  64 bytes from fe80::a046:e0ff:fee5:74f1%tapbr0: icmp_seq=2 ttl=64 time=0.548 ms
  ```

**_TIP:_** You can use Tshark to monitor ICMPv6 packets exchanged on the
different `tap` interfaces while using the `ping6` command. For example, to
monitor ICMPv6 echo/reply on `tap0`, use:

  $ sudo tshark -i tap0 -Y icmpv6

You can move to the
[next exercise](https://github.com/riot-os/riot-course-exercises/tree/master/riot-networking/shell-udp-native).
