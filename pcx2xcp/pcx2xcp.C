#include<stdio.h>

void pcx2xcp(char *pcxadr, char *xcpadr)
{ /* PCX formatinin baslik ve palet kismini yer degistirir */
 FILE *pcx, *xcp;
 long yer, i;

 pcx = fopen(pcxadr, "rb");
 xcp = fopen(xcpadr, "wb");

 /* paleti PCXin sonundan XCPnin basina yaz */
 fseek(pcx, -768, SEEK_END);
 yer = ftell(pcx);
 i = 0;
 while(i++ < 768) fputc(fgetc(pcx), xcp);

 /* resim kismini PCXten XCPnin palet kisminin hemen sonrasina yaz */
 fseek(pcx, 128, SEEK_SET);
 while(ftell(pcx) < yer) fputc(fgetc(pcx), xcp);

 /* basligi PCXin basindan XCPnin sonuna yaz */
 fseek(pcx, 0, SEEK_SET);
 i = 0;
 while(i++ < 128) fputc(fgetc(pcx), xcp);

 fclose(pcx);
 fclose(xcp);
}

main()
{
 pcx2xcp("kaynak01.pcx", "kaynak01.xcp");
 pcx2xcp("kaynak02.pcx", "kaynak02.xcp");
 pcx2xcp("kaynak03.pcx", "kaynak03.xcp");
}