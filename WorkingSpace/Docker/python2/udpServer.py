import sys
import logging
import socket


class UServer():
    def __init__(self, socket):
        self.socket = socket
        self.bufferSize = 1024

    def run(self):
        while True:
            bytesAddressPair = self.socket.recvfrom(self.bufferSize)
            message = bytesAddressPair[0]
            address = bytesAddressPair[1]
            response = message.encode('hex')[0:2] + "{0:02x}".format(0x02) + message.encode('hex')[4:]
            self.socket.sendto(str(address[1]), address)
            logging.info("%s: %s", address, message.encode('hex')[136:138])


def logging_setting():
    loglevel = logging.INFO    # DEBUG, INFO, WARNING, ERROR, CRITICAL
    if __debug__:
        loglevel = logging.DEBUG

    logging.basicConfig(
        stream=sys.stdout,
        level=loglevel,
        format="%(levelname)-6s %(asctime)s %(module)s:%(funcName)s:%(lineno)-4s  %(message)s",
        datefmt="%Y/%m/%d %H:%M:%S")


if __name__ == "__main__":
    logging_setting()

    if len(sys.argv) != 2:
        logging.error("Usage: python %s <port>", sys.argv[0])
        sys.exit(1)

    try:
        logging.info("================ Start ================")
        logging.info("sys.version: %s", sys.version.replace('\n', '\t'))

        sock = socket.socket(family=socket.AF_INET, type=socket.SOCK_DGRAM)
        sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
        sock.bind(('', int(sys.argv[1])))
        UServer(sock).run()

        logging.info("================  End  ================")
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception)
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception)

    sys.exit(0)
