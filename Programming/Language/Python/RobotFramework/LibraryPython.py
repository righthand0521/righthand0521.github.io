import subprocess
import sys

import logging


def logging_setting():
    LOG_LEVEL = logging.INFO    # DEBUG, INFO, WARNING, ERROR, CRITICAL
    if __debug__:
        LOG_LEVEL = logging.DEBUG

    logging.basicConfig(
        stream=sys.stdout,
        level=LOG_LEVEL,
        format="%(levelname)-6s %(asctime)s %(module)s:%(funcName)s:%(lineno)-4s %(message)s",
        datefmt='%Y/%m/%d %H:%M:%S')


def test_subprocess():
    subprocess.run(["lsb_release", "-a"])


# main
if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("================ Start ================")
        logging.info("sys.version: %s", sys.version)

        test_subprocess()

        logging.info("================  End  ================")
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception)
        pass

    sys.exit(0)
