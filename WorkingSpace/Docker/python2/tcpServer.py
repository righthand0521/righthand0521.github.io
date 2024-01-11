import sys
import logging
import socket
import threading


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
                # logging.info("%s: %s", self.address, data.encode('hex'))
                self.socket.sendto(str(self.address[1]), self.address)
            except socket.timeout:
                break
        self.socket.close()


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

        sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
        sock.bind(('', int(sys.argv[1])))
        sock.listen(5)
        while True:
            (client, adr) = sock.accept()
            TServer(client, adr).start()

        logging.info("================  End  ================")
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception)
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception)

    sys.exit(0)
