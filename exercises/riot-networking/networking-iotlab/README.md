## RIOT networking on real hardware

### Introduction

This exercise shows you the interoperability features of RIOT: you will
reuse the example application and same code already written in previous
exercises, but this time, remotely, on real boards provided by the FIT IoT-LAB.

### Prerequisites

Follow the riot-course [FIT IoT-LAB prerequites](https://riot-os.github.io/riot-course/slides/prerequisites/#4).

After that, you are ready to use RIOT on the FIT-IoT-LAB testbed

### Setup an experiment on FIT IoT-LAB

- Stop any running experiment you may have (use `-i` if you have multiple
  experiments already running):

      $ iotlab-experiment stop

- Book 2 iotlab-m3 boards. You can use Saclay, Paris, Lille, Strasbourg or
  Grenoble sites:

      $ iotlab-experiment submit -n riot_course -d 120 -l 2,archi=m3:at86rf231+site=paris
      {
        "id": 164500
      }
      $ iotlab-experiment wait
      "Running"

  If the `wait` subcommand takes too much time, have a look at the
  [testbed activity](https://www.iot-lab.info/testbed/drawgantt). Maybe there
  are no more boards available on the site you requested: choose M3 boards on
  another site (saclay, grenoble, lille, strasbourg)

- Verify the devices booked in your experiment (use the corresponding
  experiment identifier):

      $ iotlab-experiment get -r -i 164500
      {
        "items": [
            {
                "archi": "m3:at86rf231",
                "mobile": "0",
                "mobility_type": " ",
                "network_address": "m3-10.paris.iot-lab.info",
                "site": "paris",
                "state": "Alive",
                "uid": "b375",
                "x": "1.63",
                "y": "0",
                "z": "0.55"
            },
            {
                "archi": "m3:at86rf231",
                "mobile": "0",
                "mobility_type": " ",
                "network_address": "m3-11.paris.iot-lab.info",
                "site": "paris",
                "state": "Alive",
                "uid": "3662",
                "x": "2.28",
                "y": "0",
                "z": "1.12"
            }
        ]
      }

  In this experiment, 2 boards were booked (see **network_address** field):
  - m3-10.paris.iot-lab.info
  - m3-11.paris.iot-lab.info

- Using the RIOT build system, it's possible to specifically flash a board
remotely in FIT IoT-LAB:

  > Assign the board network_address to the `IOTLAB_NODE` variable when calling
  > the `make` command

### Testing basic networking shell commands

1. In a first terminal, build, flash and open a termining with the `gnrc_networking` example
   application for `iotlab-m3`:

  ```sh
  $ make BOARD=iotlab-m3 IOTLAB_NODE=m3-10.paris.iot-lab.info -C ~/riot-course/RIOT/examples/gnrc_networking flash term
  ```

2. In a second terminal, adapt the same command with the second board
   `network_address` (here it's `m3-11.paris.iot-lab.info`)
   Keep both terminals open.

3. You can now verify the network configuration of both boards:

  ```sh
  > ifconfig
  > ifconfig
  Iface  7  HWaddr: 29:22  Channel: 26  Page: 0  NID: 0x23
            Long HWaddr: 15:11:6B:10:65:F8:A9:22
             TX-Power: 0dBm  State: IDLE  max. Retrans.: 3  CSMA Retries: 4
            AUTOACK  ACK_REQ  CSMA  L2-PDU:102 MTU:1280  HL:64  RTR
            6LO  IPHC
            Source address length: 8
            Link type: wireless
            inet6 addr: fe80::1711:6b10:65f8:a922  scope: local  VAL
            inet6 group: ff02::2
            inet6 group: ff02::1
            inet6 group: ff02::1:fff8:a922
            inet6 group: ff02::1a

            Statistics for Layer 2
              RX packets 0  bytes 0
              TX packets 3 (Multicast: 3)  bytes 115
              TX succeeded 3 errors 0
            Statistics for IPv6
              RX packets 0  bytes 0
              TX packets 3 (Multicast: 3)  bytes 178
              TX succeeded 3 errors 0
  ```

## Exchange ICMPv6 (ping) packets

Verify ping is working between each instances: use the ipv6 address with
 `scope: local`
```sh
> ping6 fe80::1711:6b10:65f8:a922
12 bytes from fe80::1711:6b10:65f8:a922: icmp_seq=0 ttl=64 rssi=-63 dBm time=6.348 ms
12 bytes from fe80::1711:6b10:65f8:a922: icmp_seq=1 ttl=64 rssi=-63 dBm time=7.308 ms
12 bytes from fe80::1711:6b10:65f8:a922: icmp_seq=2 ttl=64 rssi=-63 dBm time=6.348 ms

--- fe80::1711:6b10:65f8:a922 PING statistics ---
3 packets transmitted, 3 packets received, 0% packet loss
round-trip min/avg/max = 6.348/6.668/7.308 ms
```

## Exchange UDP packets

1. Use the `udp` command to start an UDP server on port `8888` on the first board
(`m3-10` here):
  ```sh
  > udp server start 8888
  Success: started UDP server on port 8888
  ```

2. Send an UDP packet from the second board (`m3-11`):
  ```sh
  > udp send fe80::1711:6b10:65f8:a922 8888 "Hello Board"
  Success: sent 11 byte(s) to [fe80::1711:6b10:65f8:a922]:8888
  ```

3. Verify the packet was received on the first board, something like the
  following:
  ```sh
  PKTDUMP: data received:
  ~~ SNIP  0 - size:  11 byte, type: NETTYPE_UNDEF (0)
  00000000  48  65  6C  6C  6F  20  42  6F  61  72  64
  ~~ SNIP  1 - size:   8 byte, type: NETTYPE_UDP (4)
     src-port:  8888  dst-port:  8888
     length: 19  cksum: 0x5a02
  ~~ SNIP  2 - size:  40 byte, type: NETTYPE_IPV6 (2)
  traffic class: 0x00 (ECN: 0x0, DSCP: 0x00)
  flow label: 0x00000
  length: 19  next header: 17  hop limit: 64
  source address: fe80::1711:6b10:65fb:be26
  destination address: fe80::1711:6b10:65f8:a922
  ~~ SNIP  3 - size:  24 byte, type: NETTYPE_NETIF (-1)
  if_pid: 7  rssi: -65  lqi: 255
  flags: 0x0
  src_l2addr: 15:11:6B:10:65:FB:BE:26
  dst_l2addr: 15:11:6B:10:65:F8:A9:22
  ~~ PKT    -  4 snips, total size:  83 byte
  ```

## Test your own applications

Similar to the `gnrc_networking` application, you can test the applications
written in [sock-udp](../sock-udp), [posix-udp](../posix-udp)
and [gcoap](../gcoap) exercises on the 2 boards in your experiment.

Now let's continue with the
[networking slides](https://riot-os.github.io/riot-course/slides/04-networking-in-riot/#28).
