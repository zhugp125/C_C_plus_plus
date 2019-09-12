#include <stdio.h>
#include <time.h>
#include "qrcode.h"

int main()
{
    clock_t start = clock();
    QRCode qrcode;
    uint8_t qrcodeData[qrcode_getBufferSize(3)];
    qrcode_initText(&qrcode, qrcodeData, 3, 0, "HELLO WORLD");
    clock_t end = clock();

    printf("QR Code Generation Time: %d\n\n", (int)(end - start));

    for (uint8_t y = 0; y < qrcode.size; ++y)
    {
        for (uint8_t x = 0; x < qrcode.size; ++x)
        {
            printf(qrcode_getModule(&qrcode, x, y) ? "\u2588\u2588" : "  ");
        }
        printf("\n");
    }

    printf("Hello World!\n");
    return 0;
}
