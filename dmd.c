
 /*******************************************************************
 * sertacsaka@hotmail.com       - DeMoDe V1.02 -          2001-2002 *
 *******************************************************************/
 /*******************************************************************
 * Bu ve bu dosyaya include komutuyla eklenmis dosyalardan standart *
 * kutuphaneler disinda kalan C kodlari SERTAC SAKA'ya aittir.      *
 * Kisisel amaclar disinda kullanilmamalari rica olunur.            *
 * Kodlarin hepsi Turbo C 2.01 derleyicisinde denenmistir.          *
 * Diger derleyicilerde de gerekirse bir kac kucuk duzeltmeyle      *
 * derlenebilirler.        NOT: LARGE modda derleyiniz.             *
 *******************************************************************/

#include<dos.h>
#include<mem.h>
#include<alloc.h>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#include"dmd\klavye.c"
#include"dmd\zaman.c"
#include"dmd\grafik.c"

struct /* oyuncu degiskenleri */
{
 int ats, ilr, gri, sag, sol, tnr_syc, guc_syc, guc, bitti, kzn_syc;
 int x, y, xa, ya, krsyc, i, s, a1, a2, psyc, hsyc, asvy, pbrj, hbrj;
 int maxhsr, hasar, puan, son_anm, son_syc, kacan, iska, son_puan;
 unsigned char *kare[20];
}
oyuncu;
oyuncu_krdz[20] = {0,0,0,0,1,1,1,1,2,2,2,2,3,3,3,3};

struct /* seviyeler icin ortak degiskenler */
{
 int sayac, syc, ind, dsmn_no, bitti, tamam, bsck, son_syc, tkr_syc, zemin;
}
svy;

struct /* bolum sonu canavari icin degiskenler */
{
 float x, y;
 int hsyc, ih, tsyc, asyc, hasar, son_syc, son_anm, ilk_syc;
}
bsc;

unsigned char *rakam[10];
unsigned char *pnl[6];

#include"dmd\sincos.c"   /* hazir sinus ve cosinus degerleri */
#include"dmd\dgmfonks.c" /* dugum (bagli liste) fonksiyonlari */
#include"dmd\arkaplan.c" /* arka plan animasyonu fonksiyonlari */
#include"dmd\anifonks.c" /* cesitli oyun nesneleri icin animasyon fonksiyonlari */
#include"dmd\svyfonks.c" /* seviyeler icin ortak olan fonksiyonlar */
#include"dmd\svyler.c"   /* seviyeler icin ekleme dosyasi */
#include"dmd\grvgrfk.c"  /* gorevler icin ortak grafikler */
#include"dmd\grvler.c"   /* gorevler icin ekleme dosyasi */
#include"dmd\basveson.c" /* oyunun ilk ve son ekranlari */

unsigned _stklen = 150000; /* Turbo C 2.01 derleyicisi stack boyutunu bu sekilde ve byte cinsinden ayarliyor */

main()
{
 int o = 0;

 FILE *dosya;

 dosya = fopen("kaynak01.xcp","rb");
 if(dosya == NULL) { o = 1; printf("dosya yok: \"kaynak01.xcp\""); }
 fclose(dosya);
 dosya = fopen("kaynak02.xcp","rb");
 if(dosya == NULL) { o = 1; printf("dosya yok: \"kaynak02.xcp\""); }
 fclose(dosya);
 dosya = fopen("kaynak03.xcp","rb");
 if(dosya == NULL) { o = 1; printf("dosya yok: \"kaynak03.xcp\""); }
 fclose(dosya);

 if(!o)
 {
  srand((unsigned)time(NULL));

  gorunen_alan(320, 200, 319, 199);

  SNL_ve_RGB_bellekte();

  for(o = 0; o < 20; o++) oyuncu.kare[o] = (unsigned char *) calloc(365, 1);
  for(o = 0; o < 10; o++) rakam[o] = (unsigned char *) calloc(17, 1);

  pnl[0] = (unsigned char *) calloc(154, 1);
  pnl[1] = (unsigned char *) calloc(98, 1);
  pnl[2] = (unsigned char *) calloc(80, 1);
  pnl[3] = (unsigned char *) calloc(914, 1);
  pnl[4] = (unsigned char *) calloc(134, 1);
  pnl[5] = (unsigned char *) calloc(50, 1);

  XCPyi_bellege_oku("kaynak01.xcp", RGB, SNL);

  kare_oku(233,13,251,20,SNL,pnl[0]); /* kacan */
  kare_oku(233,22,248,27,SNL,pnl[1]); /* puan */
  kare_oku(233,30,245,34,SNL,pnl[2]); /* iska */
  kare_oku(1,181,114,188,SNL,pnl[3]); /* enter */
  kare_oku(247,29,268,34,SNL,pnl[4]); /* onceki */
  kare_oku(253,13,264,16,SNL,pnl[5]); /* son */

  kare_oku(193,33,195,37,SNL,rakam[0]);
  kare_oku(197,33,199,37,SNL,rakam[1]);
  kare_oku(201,33,203,37,SNL,rakam[2]);
  kare_oku(205,33,207,37,SNL,rakam[3]);
  kare_oku(209,33,211,37,SNL,rakam[4]);
  kare_oku(213,33,215,37,SNL,rakam[5]);
  kare_oku(217,33,219,37,SNL,rakam[6]);
  kare_oku(221,33,223,37,SNL,rakam[7]);
  kare_oku(225,33,227,37,SNL,rakam[8]);
  kare_oku(229,33,231,37,SNL,rakam[9]);

  kare_oku(1,121,33,131,SNL,oyuncu.kare[0]);
  kare_oku(35,121,67,131,SNL,oyuncu.kare[1]);
  kare_oku(69,121,101,131,SNL,oyuncu.kare[2]);
  kare_oku(103,121,135,131,SNL,oyuncu.kare[3]);
  kare_oku(1,133,33,143,SNL,oyuncu.kare[4]);
  kare_oku(35,133,67,143,SNL,oyuncu.kare[5]);
  kare_oku(69,133,101,143,SNL,oyuncu.kare[6]);
  kare_oku(103,133,135,143,SNL,oyuncu.kare[7]);
  kare_oku(1,145,33,155,SNL,oyuncu.kare[8]);
  kare_oku(35,145,67,155,SNL,oyuncu.kare[9]);
  kare_oku(69,145,101,155,SNL,oyuncu.kare[10]);
  kare_oku(103,145,135,155,SNL,oyuncu.kare[11]);
  kare_oku(1,157,33,167,SNL,oyuncu.kare[12]);
  kare_oku(35,157,67,167,SNL,oyuncu.kare[13]);
  kare_oku(69,157,101,167,SNL,oyuncu.kare[14]);
  kare_oku(103,157,135,167,SNL,oyuncu.kare[15]);
  kare_oku(1,169,33,179,SNL,oyuncu.kare[16]);
  kare_oku(35,169,67,179,SNL,oyuncu.kare[17]);
  kare_oku(69,169,101,179,SNL,oyuncu.kare[18]);
  kare_oku(103,169,135,179,SNL,oyuncu.kare[19]);

  saati_yeniden_programla();
  klavyeyi_yeniden_programla();
  ekran_modu(0x13);

  renk_paletini_kur(RGB);

  oyuncu.son_puan = 0;

  bas();
  if(grv1()) kznd(); else kybtt();
  rekor();
  son();

  ekran_modu(0x03);
  klavyeyi_eski_haline_getir();
  saati_eski_haline_getir();

  SNL_ve_RGB_serbest();

  for(o = 0; o < 20; o++) free(oyuncu.kare[o]);
  for(o = 0; o < 10; o++) free(rakam[o]);
  for(o = 0; o < 4; o++) free(pnl[o]);
 }
}