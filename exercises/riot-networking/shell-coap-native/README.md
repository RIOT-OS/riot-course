# Exchange CoAP packets

In this exercise, we propose to exchange CoAP packets between 2 RIOT native
instances on your local computer and between your local computer and a RIOT
native instance.

## Prepare the network on your Linux host (if not already done)

[Prepare the network](https://github.com/riot-os/riot-course-exercises/blob/master/riot-networking/shell-basic-native/README.md#prepare-the-network-on-your-linux-host) (if not already done)

## Start 2 native instances

3. Build the `gcoap` example application for native:

  ```sh
  $ make -C ~/riot-course/RIOT/examples/gcoap all
  ```

4. In separate terminals, start 2 native instances of RIOT on each `tap`
interface created (use `tap0` and `tap1`):

  ```sh
  $ sudo PORT=tap0 make -C ~/riot-course/RIOT/examples/gcoap term
  main(): This is RIOT! (Version: workshop-captronic)
  RIOT network stack example application
  All up, running the shell now
  > help
  ```

## Verify the setup

On each instance, display the network configuration using `ifconfig`

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

## Send CoAP request between instances

- Get the list of available resources on the instances:
```sh
> coap get -c fe80::44bc:5fff:fe34:78a6 5683 /.well-known/core
gcoap_cli: sending msg ID 7019, 23 bytes
gcoap: response Success, code 2.05, 26 bytes
</cli/stats>,</riot/board>
```

- Get the content of the `/riot/board` resource:
```sh
> coap get -c fe80::44bc:5fff:fe34:78a6 5683 /riot/board
gcoap_cli: sending msg ID 7020, 17 bytes
gcoap: response Success, code 2.05, 6 bytes
native
```

- Change the content of /cli/stats resource and verify that it changed:
```sh
> coap get fe80::44bc:5fff:fe34:78a6 5683 /cli/stats
gcoap_cli: sending msg ID 7024, 16 bytes
gcoap: response Success, code 2.05, 1 bytes
0
> coap put fe80::44bc:5fff:fe34:78a6 5683 /cli/stats 10
gcoap_cli: sending msg ID 7022, 20 bytes
gcoap: response Success, code 2.04, empty payload
> coap get fe80::44bc:5fff:fe34:78a6 5683 /cli/stats
gcoap_cli: sending msg ID 7023, 16 bytes
gcoap: response Success, code 2.05, 2 bytes
10
```

## Send CoAP request from the Linux host

It's also possible to use a CoAP client from the Linux to fetch resources of
one of the RIOT instance.

For example, use [aiocoap](https://aiocoap.readthedocs.io/en/latest/index.html)
clients (already installed on the VM):

- Get the content of `/riot/board`, from Linux:
```sh
$ aiocoap-client -m get coap://[fe80::44bc:5fff:fe34:78a6%tapbr0]/riot/board
native
```

- Change the value of `/cli/stats`:
```sh
$ aiocoap-client -m put coap://[fe80::44bc:5fff:fe34:78a6%tapbr0]/cli/stats --payload 42
$ aiocoap-client -m get coap://[fe80::44bc:5fff:fe34:78a6%tapbr0]/cli/stats
42
```

**_TIP:_** You can use Tshark to monitor CoAP requests sent on the
different `tap` interfaces while using the `coap` command. For example, to
monitor CoAP requests on interface `tap0`, use:

  $ sudo tshark -i tap0 -f "udp port 5683"

Now let's continue with the
[networking slides](https://riot-os.github.io/riot-course/slides/04-networking-in-riot/#22).
