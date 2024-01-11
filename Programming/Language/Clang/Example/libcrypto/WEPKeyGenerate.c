#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// On-Line WEP Key Generate: http://www.wepkey.com
#define WEP_KEY                 4
#define WEP_KEY_SIZE_64         5
#define WEP_KEY_SIZE_128        13

// https://sourcecodebrowser.com/linux-wlan-ng/0.2.3/lwepgen_8c_source.html
#ifndef REF_1
#define REF_1                   1

#include <unistd.h>
#include <sys/types.h>
#include <openssl/md5.h>

#define WEP_KEY_STORE_64        WEP_KEY * WEP_KEY_SIZE_64
#define WEP_KEY_STORE_128       WEP_KEY * WEP_KEY_SIZE_128

void wep_keyGenerate_64(char *pPassphrase, u_char *pWepKey)
{
    int i;

    int seed = 0;
    for (i=0; pPassphrase[i]; ++i)
    {
        seed ^= pPassphrase[i] << ((i&0x3) * 8);
    }

    for (i=0; i<WEP_KEY_STORE_64; ++i)
    {
        seed *= 0x343fd;
        seed += 0x269ec3;
        pWepKey[i] = seed >> 16;
    }
}

void wep_keyPrint_64(u_char *pWepKey)
{
    printf("WEP64\n");

    int i;
    for (i=0; i<WEP_KEY_STORE_64; ++i)
    {
        if (i%WEP_KEY_SIZE_64 == 0)
        {
            printf("\t");
        }

        printf("%02X", pWepKey[i]);

        if (i%WEP_KEY_SIZE_64 == 4)
        {
            printf("\n");
        }
    }
}

void wep_keyGenerate_128(char *pPassphrase, u_char *pWepKey)
{
    int j = 0;
    u_char buf[64];
    memset(buf, 0, sizeof(buf));
    int i;
    for (i=0; i<sizeof(buf); i++)
    {
        if (pPassphrase[j] == 0)
        {
            j = 0;
        }
        buf[i] = pPassphrase[j++];
    }

    MD5_CTX ctx;
    MD5_Init(&ctx);
    MD5_Update(&ctx, buf, sizeof(buf));
    MD5_Final(buf, &ctx);
    memcpy(pWepKey, buf, WEP_KEY_STORE_128);
}

void wep_keyPrint_128(u_char *pWepKey)
{
    printf("WEP128\n");
    printf("\t");

    int i;
    for (i=0; i<WEP_KEY_SIZE_128; ++i)
    {
        printf("%02X", pWepKey[i]);
    }
    printf("\n");
}
#endif

// http://stackoverflow.com/questions/16459257/standard-algorithm-for-wep-key-generator-64-bit
#ifndef REF_2
#define REF_2                   1

void generate_wep_key_64(char *pPassphrase, unsigned char pWepKey[WEP_KEY][WEP_KEY_SIZE_64])
{
    int i, j;

    unsigned char seed[4] = {0};
    for (i=0; i<strlen(pPassphrase); ++i)
    {
        seed[i%4] ^= (unsigned char)pPassphrase[i];
    }
    unsigned int randNumber = (seed[0]) | (seed[1]<<8) | (seed[2]<<16) | (seed[3]<<24);

    for (i=0; i<WEP_KEY; ++i)
    {
        for (j=0; j<WEP_KEY_SIZE_64; ++j)
        {
            randNumber = (randNumber * 0x343fd + 0x269ec3) & 0xffffffff;
            pWepKey[i][j] = (unsigned char)((randNumber>>16) & 0xff);
        }
    }
}

void print_wep_key_64(unsigned char pWepKey[WEP_KEY][WEP_KEY_SIZE_64])
{
    int i, j;

    printf("WEP64\n");
    for (i=0; i<WEP_KEY; ++i)
    {
        printf("\tkey%d: ", i+1);
        for (j=0; j<WEP_KEY_SIZE_64; ++j)
        {
            printf("%02X", pWepKey[i][j]);
        }
        printf("\n");
    }
}
#endif


int main(int argc, char **argv)
{
    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <Passphrase>\n", argv[0]);
        return EXIT_FAILURE;
    }


#if (REF_1)
    u_char wepKey64_1[WEP_KEY_STORE_64];
    memset(wepKey64_1, 0, sizeof(wepKey64_1));
    wep_keyGenerate_64(argv[1], wepKey64_1);
    wep_keyPrint_64(wepKey64_1);

    u_char wepKey128[WEP_KEY_STORE_128];
    memset(wepKey128, 0, sizeof(wepKey128));
    wep_keyGenerate_128(argv[1], wepKey128);
    wep_keyPrint_128(wepKey128);
#endif
#if (REF_2)
    unsigned char wepKey64_2[WEP_KEY][WEP_KEY_SIZE_64];
    memset(wepKey64_2, 3, sizeof(wepKey64_2));
    generate_wep_key_64(argv[1], wepKey64_2);
    print_wep_key_64(wepKey64_2);
#endif


    return EXIT_SUCCESS;
}

