# Exchange UDP packets

In this exercise, we propose to exchange UDP packets between 2 RIOT native
instances on your local computer and between your local computer and a RIOT
native instance.

## Start 2 native instances

1. [Prepare the network](https://github.com/riot-os/riot-course-exercises/blob/master/riot-networking/shell-basic-native/README.md#prepare-the-network-on-your-linux-host) (if not already done)
2. [Start the 2 instances](https://github.com/riot-os/riot-course-exercises/blob/master/riot-networking/shell-basic-native/README.md#start-2-native-instances)

## Exchange UDP packets between the RIOT instances

1. On the first instance, print the IP addresses using ifconfig:
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


2. Then use the `udp` command to start an UDP server on port `8888`:
  ```sh
  > udp server start 8888
  Success: started UDP server on port 8888
  ```

3. Send an UDP packet from the second instance:
  ```sh
  > udp send fe80::846:47ff:fe86:27e8 8888 "Hello Bro"
  ```

4. Verify the packet was received on the first instance, something like the
  following:
  ```sh
  PKTDUMP: data received:
  ~~ SNIP  0 - size:  10 byte, type: NETTYPE_UNDEF (0)
  00000000  48  65  6C  6C  6F  20  52  49  4F  54
  ~~ SNIP  1 - size:   8 byte, type: NETTYPE_UDP (3)
     src-port:  8888  dst-port:  8888
     length: 18  cksum: 0xe713
  ~~ SNIP  2 - size:  40 byte, type: NETTYPE_IPV6 (1)
  traffic class: 0x00 (ECN: 0x0, DSCP: 0x00)
  flow label: 0x00000
  length: 18  next header: 17  hop limit: 64
  source address: fe80::44bc:5fff:fe34:78a6
  destination address: fe80::a046:e0ff:fee5:74f1
  ~~ SNIP  3 - size:  20 byte, type: NETTYPE_NETIF (-1)
  if_pid: 6  rssi: 0  lqi: 0
  flags: 0x0
  src_l2addr: 46:BC:5F:34:78:A6
  dst_l2addr: A2:46:E0:E5:74:F1
  ~~ PKT    -  4 snips, total size:  78 byte
  ```

## Exchange UDP packets with your Linux host

1. Send an UDP packet from Linux to first instance of RIOT, the one running the
  UDP server. Note that you still need to specify the interface `tapbr0`.
  ```sh
  $ echo -n "Hello RIOT" >/dev/udp/fe80::846:47ff:fe86:27e8%tapbr0/8888
  ```

2. Start an UDP server on Linux using netcat:
  ```sh
  $ nc -6ul 8888
  ```

3. Check the link local address of the `tapbr0` interface on your Linux host:
  ```sh
  $ ifconfig
  [...]
  tapbr0: flags=4163<UP,BROADCAST,RUNNING,MULTICAST>  mtu 1500
        inet6 fe80::44bc:5fff:fe34:78a5  prefixlen 64  scopeid 0x20<link>
        ether 46:bc:5f:34:78:a5  txqueuelen 1000  (Ethernet)
        RX packets 183  bytes 12904 (12.9 KB)
        RX errors 0  dropped 0  overruns 0  frame 0
        TX packets 4314  bytes 235890 (235.8 KB)
        TX errors 0  dropped 0 overruns 0  carrier 0  collisions 0
  [...]
  ```

4. Send an UDP packet from RIOT to Linux:
  ```sh
  > udp send fe80::44bc:5fff:fe34:78a5 8888 "Hello Linux"
  Success: sent 11 byte(s) to [fe80::44bc:5fff:fe34:78a5]:8888
  ```
  You should see the message printed in the console running netcat on Linux!

**_TIP:_** You can use Tshark to monitor UDP packets sent on the
different `tap` interfaces while using the `udp` command. For example, to
monitor udp packet on port 8888 on interface `tap0`, use:

  $ sudo tshark -i tap0 -f "udp port 8888"

Now let's continue with the
[networking slides](https://riot-os.github.io/riot-course/slides/04-networking-in-riot/#12).
