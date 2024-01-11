import sys
import logging
import socket


def logging_setting():
    loglevel = logging.INFO    # DEBUG, INFO, WARNING, ERROR, CRITICAL
    if __debug__:
        loglevel = logging.DEBUG

    logging.basicConfig(
        stream=sys.stdout,
        level=loglevel,
        format="%(levelname)-6s %(asctime)s %(module)s:%(funcName)s:%(lineno)-4s  %(message)s",
        datefmt="%Y/%m/%d %H:%M:%S")


class Client:
    def is_valid_ipv4_address(self, address) -> bool:
        try:
            socket.inet_pton(socket.AF_INET, address)
        except AttributeError:  # no inet_pton here, sorry
            try:
                socket.inet_aton(address)
            except socket.error:
                return False
            return address.count('.') == 3
        except socket.error:  # not a valid address
            return False

        return True

    def is_valid_ipv6_address(self, address) -> bool:
        try:
            socket.inet_pton(socket.AF_INET6, address)
        except socket.error:  # not a valid address
            return False

        return True

    def run(self, protocol, ip, port) -> None:
        logging.info("%s, %s, %s.", protocol, ip, port)

        if self.is_valid_ipv4_address(ip) == True:
            family = socket.AF_INET
            severAddr = (ip, port)
        else:
            splitList = ip.split('%')
            if self.is_valid_ipv6_address(splitList[0]) == True:
                family = socket.AF_INET6
                for res in socket.getaddrinfo(ip, port, family, socket.SOCK_STREAM, socket.SOL_TCP):
                    af, socktype, proto, canonname, severAddr = res
            else:
                logging.error("%s: not a valid ip address", ip)
                return

        message = "Hello"
        if protocol == "tcp":
            sock = socket.socket(family, socket.SOCK_STREAM)
            sock.connect(severAddr)
        elif protocol == "udp":
            sock = socket.socket(family, socket.SOCK_DGRAM)
        else:
            logging.error("%s: not a valid protocol: tcp or udp", protocol)
            return
        sock.sendto(message.encode('utf-8'), severAddr)
        sock.close()


if __name__ == "__main__":
    logging_setting()

    if len(sys.argv) != 4:
        logging.error("Usage: python %s <tcp|udp> <ip> <port>", sys.argv[0])
        sys.exit(1)

    try:
        logging.info("================ Start ================")
        logging.info("sys.version: %s", sys.version.replace('\n', '\t'))

        PROTOCOL = sys.argv[1]
        IP = sys.argv[2]
        PORT = int(sys.argv[3])
        pClient = Client()
        pClient.run(PROTOCOL, IP, PORT)

        logging.info("================  End  ================")
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception)
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception)

    sys.exit(0)
