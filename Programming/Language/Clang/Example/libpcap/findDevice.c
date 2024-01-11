#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pcap.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#ifndef __linux
#include <net/if.h>
#include <netinet/in.h>
#include <net/if_dl.h>
#include <net/ethernet.h>
#else /* if BSD */
#include <linux/if_ether.h>
#include <netpacket/packet.h>
#include <linux/if_link.h>
#include <netinet/ether.h>
#endif


int main(int argc, char **argv)
{
    pcap_if_t *deviceList = NULL;
    char errbuf[PCAP_ERRBUF_SIZE];
    memset(errbuf, 0, sizeof(errbuf));
    if (PCAP_ERROR == pcap_findalldevs(&deviceList, errbuf))
    {
        fprintf(stderr, "pcap_findalldevs(): %s\n", errbuf);
        return EXIT_FAILURE;
    }

    pcap_if_t *pDevice = NULL;
    for (pDevice=deviceList; pDevice; pDevice=pDevice->next)
    {
        printf("Device: %s\n", pDevice->name);
        if (pDevice->description)
        {
            printf("\tDescription: %s\n", pDevice->description);
        }
#ifdef PCAP_IF_UP
        printf("\tUp: %s\n", (pDevice->flags&PCAP_IF_UP)?"yes":"no");
#endif
#ifdef PCAP_IF_RUNNING
        printf("\tRunning: %s\n", (pDevice->flags&PCAP_IF_RUNNING)?"yes":"no");
#endif

        struct pcap_addr *pAddress;
        for (pAddress=pDevice->addresses; pAddress; pAddress=pAddress->next)
        {
            char ntop_buf[256];
            memset(ntop_buf, 0, sizeof(ntop_buf));

            sa_family_t family = pAddress->addr->sa_family;
            if (family == AF_INET || family == AF_INET6)
            {
                if (pAddress->addr)
                {
                    printf("\tAddress: %s\n",
                        inet_ntop(family, &((struct sockaddr_in *)pAddress->addr)->sin_addr, ntop_buf, sizeof(ntop_buf)));
                }
                if (pAddress->netmask)
                {
                    printf("\tNetmask: %s\n",
                        inet_ntop(family, &((struct sockaddr_in *)pAddress->netmask)->sin_addr, ntop_buf, sizeof(ntop_buf)));
                }
                if (pAddress->broadaddr)
                {
                    printf("\tBroadcast Address: %s\n",
                        inet_ntop(family, &((struct sockaddr_in *)pAddress->broadaddr)->sin_addr, ntop_buf, sizeof(ntop_buf)));
                }
                if (pAddress->dstaddr)
                {
                    printf("\tDestination Address: %s\n",
                        inet_ntop(family, &((struct sockaddr_in *)pAddress->dstaddr)->sin_addr, ntop_buf, sizeof(ntop_buf)));
                }
            }
#ifdef AF_LINK
            else if (family == AF_LINK && a->addr)
            {
                struct sockaddr_dl *sdl = (struct sockaddr_dl *)pAddress->addr;
                if (sdl->sdl_family == AF_LINK && sdl->sdl_alen == ETHER_ADDR_LEN)
                {
                    printf("\tLink address: %s\n", ether_ntoa((const struct ether_addr *)(sdl->sdl_data + sdl->sdl_nlen)));

                }
            }
#elif AF_PACKET
            else if (family == AF_PACKET && pAddress->addr)
            {
                struct sockaddr_ll *sll = (struct sockaddr_ll *)pAddress->addr;
                if (sll->sll_family == AF_PACKET && sll->sll_halen == ETHER_ADDR_LEN)
                {
                    printf("\tLink address: %s\n", ether_ntoa((const struct ether_addr *)sll->sll_addr));
                }
            }
#endif
        }
    }
    pcap_freealldevs(deviceList);


    return EXIT_SUCCESS;
}

