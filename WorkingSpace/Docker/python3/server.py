import sys
import logging
import socket
import threading


def logging_setting():
    loglevel = logging.INFO    # DEBUG, INFO, WARNING, ERROR, CRITICAL
    if __debug__:
        loglevel = logging.DEBUG

    logging.basicConfig(
        stream=sys.stdout,
        level=loglevel,
        format="%(levelname)-6s %(asctime)s %(module)s:%(funcName)s:%(lineno)-4s  %(message)s",
        datefmt="%Y/%m/%d %H:%M:%S")


class TServer(threading.Thread):
    def __init__(self, socket, adr):
        threading.Thread.__init__(self)
        self.socket = socket
        self.address = adr
        self.bufferSize = 1024

    def run(self):
        while True:
            try:
                data = self.socket.recv(self.bufferSize)
                if not data:
                    break
                logging.info("%s", self.address)
                self.socket.sendto(
                    str(self.address[1]).encode('utf-8'), self.address)
            except socket.timeout:
                break
        self.socket.close()


class UServer():
    def __init__(self, socket):
        self.socket = socket
        self.bufferSize = 1024

    def run(self):
        while True:
            data = self.socket.recvfrom(self.bufferSize)
            message = data[0]
            address = data[1]
            logging.info("%s", address)
            self.socket.sendto(str(address[1]).encode('utf-8'), address)


if __name__ == "__main__":
    logging_setting()

    if len(sys.argv) != 3:
        logging.error("Usage: python %s <tcp|udp> <port>", sys.argv[0])
        sys.exit(1)

    try:
        logging.info("================ Start ================")
        logging.info("sys.version: %s", sys.version.replace('\n', '\t'))

        PROTOCOL = sys.argv[1]
        PORT = int(sys.argv[2])
        serverAddress = ('', PORT)

        if PROTOCOL == "tcp":
            if socket.has_dualstack_ipv6():
                sock = socket.create_server(
                    serverAddress, family=socket.AF_INET6, dualstack_ipv6=True)
            else:
                sock = socket.create_server(serverAddress)

            while True:
                (client, adr) = sock.accept()
                TServer(client, adr).start()
        elif PROTOCOL == "udp":
            sock = socket.socket(family=socket.AF_INET6,
                                 type=socket.SOCK_DGRAM)
            sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
            sock.bind(serverAddress)
            UServer(sock).run()
        else:
            logging.error("%s: not a valid protocol: tcp or udp", PROTOCOL)

        logging.info("================  End  ================")
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception)
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception)

    sys.exit(0)
