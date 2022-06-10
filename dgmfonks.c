typedef struct cph_dugum /* cephane dugumu */
{
 float x, y, asyc;
 int tip, son_anm, sil, krsyc, krbksyc, sabksyc;
 int s, m, n, d1x, d1y, d2x, d2y, h1;
 struct cph_dugum *sonraki;
} cph;

typedef struct dsmn_dugum /* dusman dugumu */
{
 float x, y, xa, ya, ysyc;
 int tip, yhr, no, hasar, son_anm, son_syc, ilk_syc;
 int sil, krsyc, krbksyc, msyc, asyc, abksyc, crplrk, d1, d2, d3;
 struct dsmn_dugum *sonraki;
} dsmn;

typedef struct nsn_dugum /* nesne dugumu */
{
 float x, y, xa, ya;
 int tip, sil, no, krsyc, krbksyc, k, ksyc;
 struct nsn_dugum *sonraki;
} nsn;

/* oyuncu cephanesi dugum gostergeleri */

cph *ocph_birinci = NULL, /* zincirin ilk dugumunu gosterir */
    *ocph_sonuncu = NULL, /* daima en son eklenen dugumu gosterir */
    *ocph_adres = NULL;   /* sayac vazifesi gorur islenen dugumu gosterir */

/* dusman cephanesi dugum gostergeleri */

cph *dcph_birinci = NULL, /* zincirin ilk dugumunu gosterir */
    *dcph_sonuncu = NULL, /* daima en son eklenen dugumu gosterir */
    *dcph_adres = NULL;   /* sayac vazifesi gorur islenen dugumu gosterir */

/* dusman araci dugum gostergeleri */

dsmn *dsmn_birinci = NULL, /* zincirin ilk dugumunu gosterir */
     *dsmn_sonuncu = NULL, /* daima en son eklenen dugumu gosterir */
     *dsmn_adres = NULL;   /* sayac vazifesi gorur islenen dugumu gosterir */

/* nesne dugum gostergeleri */

nsn *nsn_birinci = NULL, /* zincirin ilk dugumunu gosterir */
    *nsn_sonuncu = NULL, /* daima en son eklenen dugumu gosterir */
    *nsn_adres = NULL;   /* sayac vazifesi gorur islenen dugumu gosterir */

void yeni_ocph_dugum(int tip, int x, int y)
{ /* yeni oyuncu cephanesi dugumu yaratir ve varsa zincire ekler */
 cph *ocph_yeni = NULL;    /* gecici bilgi alani */

 ocph_yeni = (cph *) malloc(sizeof(cph));

 if(ocph_yeni != NULL) /* hafizada yeterli yer varsa */
 {
  ocph_yeni->x = x;
  ocph_yeni->y = y;
  ocph_yeni->sil = 0;
  ocph_yeni->tip = tip;
  ocph_yeni->krsyc = 0;
  ocph_yeni->krbksyc = 0;
  ocph_yeni->sabksyc = 0;
  ocph_yeni->son_anm = 0;
  ocph_yeni->sonraki = NULL;

  if(ocph_birinci == NULL) ocph_birinci = ocph_yeni; /* birinci mevcut degilse yaratilan birinci dugum olsun */
  else ocph_sonuncu->sonraki = ocph_yeni; /* birinci mevcutsa yeniyi sona ekle */

  ocph_sonuncu = ocph_yeni; /* bundan sonra yeni dugum sonuncu olsun */
 }
}

void yeni_dcph_dugum(int tip, int x, int y, int cb[])
{ /* yeni dusman cephanesi dugumu yaratir ve varsa zincire ekler */
 cph *dcph_yeni = NULL;    /* gecici bilgi alani */

 int u, v, e, f, blok = tip * 12;

 dcph_yeni = (cph *) malloc(sizeof(cph));

 if(dcph_yeni != NULL) /* hafizada yeterli yer varsa */
 {
  dcph_yeni->x = x;
  dcph_yeni->y = y;
  dcph_yeni->h1 = 0;
  dcph_yeni->sil = 0;
  dcph_yeni->asyc = 0;
  dcph_yeni->tip = tip;
  dcph_yeni->krsyc = 0;
  dcph_yeni->krbksyc = 0;
  dcph_yeni->sabksyc = 0;
  dcph_yeni->son_anm = 0;
  dcph_yeni->sonraki = NULL;

  if(cb[blok] == 1) /* hareket tipi hedefli ise yol parametrelerini belirle */
  { /* Bresenham'in cizgi algoritmasindan uyarlanmistir */
   u = (oyuncu.x + 17) - (dcph_yeni->x + cb[blok + 2]);
   v = (oyuncu.y + 6) - (dcph_yeni->y + cb[blok + 3]);

   dcph_yeni->d1x = sgn(u);
   dcph_yeni->d1y = sgn(v);

   e = abs(u);
   f = abs(v);

   if (e <= f)
   {
    dcph_yeni->d2x = 0;
    dcph_yeni->d2y = dcph_yeni->d1y;
    dcph_yeni->m = f;
    dcph_yeni->n = e;
   }
   else
   {
    dcph_yeni->d2x = dcph_yeni->d1x;
    dcph_yeni->d2y = 0;
    dcph_yeni->m = e;
    dcph_yeni->n = f;
   }

   dcph_yeni->s = dcph_yeni->m >> 1;
  }

  if(dcph_birinci == NULL) dcph_birinci = dcph_yeni; /* birinci mevcut degilse yaratilan birinci dugum olsun */
  else dcph_sonuncu->sonraki = dcph_yeni;       /* birinci mevcutsa yeniyi sona ekle */

  dcph_sonuncu = dcph_yeni; /* bundan sonra yeni dugum sonuncu olsun */
 }
}

void yeni_dsmn_dugum(int tip, int x, int y, int no)
{ /* yeni dusman araci dugumu yaratir ve varsa zincire ekler */
 dsmn *dsmn_yeni = NULL;    /* gecici bilgi alani */

 dsmn_yeni = (dsmn *) malloc(sizeof(dsmn));

 if(dsmn_yeni != NULL) /* hafizada yeterli yer varsa */
 {
  dsmn_yeni->x = x;
  dsmn_yeni->y = y;
  dsmn_yeni->xa = 0;
  dsmn_yeni->ya = 0;
  dsmn_yeni->d1 = 0;
  dsmn_yeni->d2 = 0;
  dsmn_yeni->d3 = 0;
  dsmn_yeni->yhr = 0;
  dsmn_yeni->no = no;
  dsmn_yeni->sil = 0;
  dsmn_yeni->msyc = 0;
  dsmn_yeni->ysyc = 0;
  dsmn_yeni->asyc = 0;
  dsmn_yeni->abksyc = 0;
  dsmn_yeni->tip = tip;
  dsmn_yeni->hasar = 0;
  dsmn_yeni->krsyc = 0;
  dsmn_yeni->crplrk = 0;
  dsmn_yeni->krbksyc = 0;
  dsmn_yeni->ilk_syc = 1000;
  dsmn_yeni->son_syc = 50;
  dsmn_yeni->son_anm = 0;
  dsmn_yeni->sonraki = NULL;

  if(dsmn_birinci == NULL) dsmn_birinci = dsmn_yeni; /* birinci mevcut degilse yaratilan birinci dugum olsun */
  else dsmn_sonuncu->sonraki = dsmn_yeni;       /* birinci mevcutsa yeniyi sona ekle */

  dsmn_sonuncu = dsmn_yeni; /* bundan sonra yeni dugum sonuncu olsun */
 }
}

void yeni_nsn_dugum(int tip, int no, int x, int y)
{ /* yeni nesne dugumu yaratir ve varsa zincire ekler */
 nsn *nsn_yeni = NULL;    /* gecici bilgi alani */

 nsn_yeni = (nsn *) malloc(sizeof(nsn));

 if(nsn_yeni != NULL) /* hafizada yeterli yer varsa */
 {
  nsn_yeni->x = x;
  nsn_yeni->y = y;
  nsn_yeni->xa = 0;
  nsn_yeni->ya = 0;
  nsn_yeni->k = 1 + rand() % 10;
  nsn_yeni->no = no;
  nsn_yeni->sil = 0;
  nsn_yeni->tip = tip;
  nsn_yeni->ksyc = 0;
  nsn_yeni->krsyc = 0;
  nsn_yeni->krbksyc = 0;
  nsn_yeni->sonraki = NULL;

  if(nsn_birinci == NULL) nsn_birinci = nsn_yeni; /* birinci mevcut degilse yaratilan birinci dugum olsun */
  else nsn_sonuncu->sonraki = nsn_yeni; /* birinci mevcutsa yeniyi sona ekle */

  nsn_sonuncu = nsn_yeni; /* bundan sonra yeni dugum sonuncu olsun */
 }
}

void ocph_zincir_sil(void)
{ /* oyuncu cephanesi zincirinin hafizada kapladigi alani serbest birakir */
 cph *ocph_sonraki = NULL; /* bastan sona okumada bir sonraki dugumu gosterir */

 if(ocph_birinci != NULL) /* zincir mevcutsa */
 {
  ocph_adres = ocph_birinci;
  ocph_birinci = NULL;

  do
  {
   ocph_sonraki = ocph_adres->sonraki;
   free(ocph_adres);
   ocph_adres = ocph_sonraki;
  } while(ocph_sonraki != NULL);
 }
}

void dcph_zincir_sil(void)
{ /* dusman cephanesi zincirinin hafizada kapladigi alani serbest birakir */
 cph *dcph_sonraki = NULL; /* bastan sona okumada bir sonraki dugumu gosterir */

 if(dcph_birinci != NULL) /* zincir mevcutsa */
 {
  dcph_adres = dcph_birinci;
  dcph_birinci = NULL;

  do
  {
   dcph_sonraki = dcph_adres->sonraki;
   free(dcph_adres);
   dcph_adres = dcph_sonraki;
  } while(dcph_sonraki != NULL);
 }
}

void dsmn_zincir_sil(void)
{ /* dusman dugumu zincirinin hafizada kapladigi alani serbest birakir */
 dsmn *dsmn_sonraki = NULL; /* bastan sona okumada bir sonraki dugumu gosterir */

 if(dsmn_birinci != NULL) /* zincir mevcutsa */
 {
  dsmn_adres = dsmn_birinci;
  dsmn_birinci = NULL;

  do
  {
   dsmn_sonraki = dsmn_adres->sonraki;
   free(dsmn_adres);
   dsmn_adres = dsmn_sonraki;
  } while(dsmn_sonraki != NULL);
 }
}

void nsn_zincir_sil(void)
{ /* nesne zincirinin hafizada kapladigi alani serbest birakir */
 nsn *nsn_sonraki = NULL; /* bastan sona okumada bir sonraki dugumu gosterir */

 if(nsn_birinci != NULL) /* zincir mevcutsa */
 {
  nsn_adres = nsn_birinci;
  nsn_birinci = NULL;

  do
  {
   nsn_sonraki = nsn_adres->sonraki;
   free(nsn_adres);
   nsn_adres = nsn_sonraki;
  } while(nsn_sonraki != NULL);
 }
}

void ocph_zincir_oku(unsigned char *kr[], float cph_hiz[], int cph_dizi[], int dsmn_dizi[], void ocph_anm(int[], float[], unsigned char *[]))
{ /* oyuncu cephane zincirinin dugumlerini dusman zinciri dugumleri ile karsilastirir */
 cph *ocph_sonraki = NULL, /* sonraki oyuncu cephanesi dugumunu gosterir */
     *ocph_onceki = NULL;  /* onceki oyuncu cephanesi dugumunu gosterir */

 dsmn *dsmn_sonraki = NULL; /* sonraki dusman dugumunu gosterir */
 cph *dcph_sonraki = NULL; /* sonraki dusman cephanesi dugumunu gosterir */

 int x1, y1, x2, y2, ocph_blok, blok, ocph_en, ocph_boy, en, boy, cikti;

 if(ocph_birinci != NULL) /* zincir mevcutsa */
 {
  ocph_adres = ocph_birinci; /* sayac saymaya birinci dugumden baslasin */

  do
  {
   ocph_sonraki = ocph_adres->sonraki;

   ocph_blok = ocph_adres->tip * 12;
   ocph_en = cph_dizi[ocph_blok + 2];
   ocph_boy = cph_dizi[ocph_blok + 3];

   x1 = ocph_adres->x, y1 = ocph_adres->y;
   x2 = x1 + ocph_en, y2 = y1 + ocph_boy;

/* dusman zinciri okuma baslangici */
    if(dsmn_birinci != NULL && !ocph_adres->son_anm) /* zincir mevcutsa ve okunan cephane aktifse */
    {
     dsmn_adres = dsmn_birinci; /* sayac saymaya birinci dugumden baslasin */

     do
     {
      dsmn_sonraki = dsmn_adres->sonraki;

      if(dsmn_adres->son_anm < 2 && dsmn_adres->tip > 3) /* siradaki dusman aktifse ve bonus degilse */
      {
       blok = dsmn_adres->tip * 26;

       en = dsmn_dizi[blok + 2] - 1;
       boy = dsmn_dizi[blok + 3] - 1;

       if(dsmn_dizi[blok + 1]) /* maxhsr != 0 ise */
       {
        if(x1 >= dsmn_adres->x - ocph_en && x2 <= dsmn_adres->x + en + ocph_en && y1 >= dsmn_adres->y - ocph_boy && y2 <= dsmn_adres->y + boy + ocph_boy)
        { /* kesisme durumu */
         ocph_adres->son_anm = 1; /* cephane bitis animasyonu aktive edilir */
         ocph_adres->krsyc = 0; /* bitis animasyonu icin kare sayaci sifirlanir */
         ocph_adres->krbksyc = cph_dizi[ocph_blok + 9]; /* kare bekleme sayaci yeni degerini alir */
         dsmn_adres->hasar += cph_dizi[ocph_blok + 1] * oyuncu.guc; /* dusman hasar sayisini arttir */
         if(dsmn_adres->hasar >= dsmn_dizi[blok + 1])
         { /* dusman maksimum hasardan fazlasini almissa */
          yeni_nsn_dugum(0,-1, dsmn_adres->x, dsmn_adres->y); /* puan animasyonu */
          /* kac puan olacagini belirlemek icin mxhsr degerini */
          /* kendi gorevi disinda kullanarak krbksyc ile nsn dugumune gecir */
          nsn_sonuncu->krbksyc = dsmn_dizi[blok + 1];

          dsmn_adres->son_anm = 2; /* hasar max olursa dugumu pasif hale getir  */
          oyuncu.puan += dsmn_dizi[blok + 1] * oyuncu.guc;
          oyuncu.psyc += dsmn_dizi[blok + 1] * oyuncu.guc;
          if(oyuncu.psyc > oyuncu.asvy * oyuncu.pbrj) oyuncu.asvy++, oyuncu.psyc = 0;
          if(oyuncu.asvy > 6) oyuncu.asvy = 6;
         }
         else /* dusman maksimum hasari asmamissa */
         {
          oyuncu.puan += cph_dizi[ocph_blok + 1] * oyuncu.guc;
          /* dusman maksimum hasarinin yarisini asarsa yanma animasyonunu aktive et */
          if(dsmn_adres->hasar >= dsmn_dizi[blok + 1] / 2) dsmn_adres->son_anm = 1;
         }
        }
       }
      }

      dsmn_adres = dsmn_sonraki; /* sayac sonraki dugumu gostersin */
     } while(dsmn_sonraki != NULL);
    }
/* dusman zinciri okuma sonu */

/* gudumlu (vurulabilir) cephane icin dusman cephane zinciri okuma baslangici */
    if(dcph_birinci != NULL && !ocph_adres->son_anm) /* zincir mevcutsa ve okunan cephane aktifse */
    {
     dcph_adres = dcph_birinci; /* sayac saymaya birinci dugumden baslasin */

     do
     {
      dcph_sonraki = dcph_adres->sonraki;

      blok = dcph_adres->tip * 12;

      if(cph_dizi[blok + 0] == 2 && !dcph_adres->son_anm) /* siradaki gudumlu ve aktifse */
      {
       en = cph_dizi[blok + 2] - 1;
       boy = cph_dizi[blok + 3] - 1;

       if(x1 >= dcph_adres->x - ocph_en && x2 <= dcph_adres->x + en + ocph_en && y1 >= dcph_adres->y - ocph_boy && y2 <= dcph_adres->y + boy + ocph_boy)
       { /* kesisme durumu */
        ocph_adres->sil = 1; /* oyuncu cephanesini sil */
        dcph_adres->son_anm = 1, /* cephane bitis animasyonu aktive edilir */
        dcph_adres->krsyc = 0, /* bitis animasyonu icin kare sayaci sifirlanir */
        dcph_adres->krbksyc = cph_dizi[blok + 9]; /* hasar max olursa dugumu pasif hale getir  */
       }
      }

      dcph_adres = dcph_sonraki; /* sayac sonraki dugumu gostersin */
     } while(dcph_sonraki != NULL);
    }
/* dusman cephane zinciri okuma sonu */

/* bolum sonu canavari kontrolu */
   if(svy.bsck && svy.bitti && !svy.son_syc) /* bsc varsa, seviye sonu geldiyse, son sayac sifirlandiysa */
    if(x2 >= bsc.x + 25 && x1 <= bsc.x + 61 && y2 >= bsc.y + 21 && y1 <= bsc.y + 46)
    { /* kesisme durumu */
     bsc.hasar += cph_dizi[ocph_blok + 1] * oyuncu.guc;
     ocph_adres->son_anm = 1;
    }

/* cephane gorunen alanin disina ciktiysa */
   if(x2 < ex1 || y2 < ey1 || x1 > ex2 || y1 > ey2) cikti = 1, oyuncu.iska++; else cikti = 0;

   if(cikti || ocph_adres->sil) /* dugum silme sarti */
   {
    if(ocph_adres == ocph_birinci) ocph_birinci = ocph_sonraki; /* birinci silinecekse ikinci birinci olsun */
    else /* silinecek birinci degilse sonrakini oncekine ekle */
    {
     ocph_onceki->sonraki = ocph_sonraki;
     if(ocph_adres == ocph_sonuncu) ocph_sonuncu = ocph_onceki; /* son dugum silindiyse sonuncu öncekini gostersin */
    }
    free(ocph_adres);
   }
   else
   {
    ocph_anm(cph_dizi, cph_hiz, kr);

    ocph_onceki = ocph_adres; /* islemi biten dugum onceki olsun */
   }

   ocph_adres = ocph_sonraki; /* sayac sonraki dugumu gostersin */
  } while(ocph_sonraki != NULL);
 }
}

void dsmn_zincir_oku(unsigned char *kr[], int dsmn_dizi[], float dsmn_hiz[], int dsmn_dky[], int cph_blg[], void dsmn_anm(int[], float[], int[], unsigned char *[], int[], int, dsmn*))
{ /* oyuncuyu dusman zinciri dugumleri ile karsilastirir */
 dsmn *dsmn_sonraki = NULL, /* sonraki dusman dugumunu gsterir */
      *dsmn_onceki = NULL;  /* onceki dusman dugumunu gosterir */

 int x1, x2, y1, y2, blok, cikti;

 if(dsmn_birinci != NULL) /* zincir mevcutsa */
 {
  dsmn_adres = dsmn_birinci; /* sayac saymaya birinci dugumden baslasin */

  do
  {
   dsmn_sonraki = dsmn_adres->sonraki;

   blok = dsmn_adres->tip * 26;

   x1 = dsmn_adres->x, y1 = dsmn_adres->y;
   x2 = x1 + dsmn_dizi[blok + 2], y2 = y1 + dsmn_dizi[blok + 3];

   if(dsmn_adres->son_anm < 2) /* siradaki dusman aktifse */
   {
    if(!oyuncu.son_anm && oyuncu.x >= x1 - 32 && oyuncu.x + 33 <= x2 + 32 && oyuncu.y >= y1 - 10 && oyuncu.y + 11 <= y2 + 10)
    { /* kesisme durumu */
     if(dsmn_adres->tip < 4) /* bonus ise */
     {
      if(dsmn_dizi[blok + 7]) /* puan arttirici */
      {
       yeni_nsn_dugum(0,-1, dsmn_adres->x, dsmn_adres->y); /* puan animasyonu */
       /* kac puan olacagini belirlemek icin mxhsr degerini */
       /* kendi gorevi disinda kullanarak krbksyc ile nsn dugumune gecir */
       nsn_sonuncu->krbksyc = dsmn_dizi[blok + 7];
       oyuncu.puan += dsmn_dizi[blok + 7];
      }
      /* hasar azaltici */
      if(dsmn_dizi[blok + 8]) { oyuncu.hasar -= dsmn_dizi[blok + 8]; if(oyuncu.hasar < 0) oyuncu.hasar = 0; }
      /* kalkan */
      if(dsmn_dizi[blok + 9]) oyuncu.tnr_syc = dsmn_dizi[blok + 9];
      /* guc arttirici */
      if(dsmn_dizi[blok + 10]) oyuncu.guc_syc = dsmn_dizi[blok + 10];

      dsmn_adres->son_anm = 2; /* bitis animasyonunu aktive et */
      dsmn_adres->krsyc = 0; /* bitis animasyonu icin kare sayacini ve */
      dsmn_adres->krbksyc = 0; /* kare bekleme sayacini sifirla */
     }
     else /* bonus degilse */
     {
      oyuncu.hasar += dsmn_dizi[blok + 1]; /* oyuncu hasar sayisini arttir */

      oyuncu.hsyc += dsmn_dizi[blok + 1];
      if(oyuncu.hsyc > oyuncu.asvy * oyuncu.hbrj) oyuncu.asvy--, oyuncu.hsyc = 0;
      if(oyuncu.asvy < 1) oyuncu.asvy = 1;

      /* hasar max olursa oyuncuyu pasif hale getir */
      if(oyuncu.hasar >= oyuncu.maxhsr) oyuncu.son_anm = 1;

      dsmn_adres->hasar += oyuncu.maxhsr * oyuncu.guc;
      if(dsmn_dizi[blok + 1]) /* dusmanin maksimum hasari 0dan buyukse */
      {
       if(dsmn_adres->hasar >= dsmn_dizi[blok + 1]) /* hasar max olursa dugumu pasif hale getir */
       {
        dsmn_adres->son_anm = 2;
        dsmn_adres->crplrk = 1;
       } /* yok eger sadece yariyi asarsa yanma animasyonunu aktive et */
       else if(dsmn_adres->hasar >= dsmn_dizi[blok + 1] / 2) dsmn_adres->son_anm = 1;
      }
     }
    }
   }

   if(x2 < ex1 || y2 < ey1 || y1 > ey2)
   { /* dusman gorunen alanin disina cikarsa */
    cikti = 1;
    if(!oyuncu.son_anm && dsmn_adres->tip > 3) oyuncu.kacan++;
   }
   else cikti = 0;

   if(cikti || dsmn_adres->sil) /* dugum silme sarti */
   {
    if(dsmn_adres == dsmn_birinci) dsmn_birinci = dsmn_sonraki; /* birinci silinecekse ikinci birinci olsun */
    else /* silinecek birinci degilse sonrakini oncekine ekle */
    {
     dsmn_onceki->sonraki = dsmn_sonraki;
     if(dsmn_adres == dsmn_sonuncu) dsmn_sonuncu = dsmn_onceki; /* son dugum silindiyse sonuncu öncekini gostersin */
    }
    free(dsmn_adres);
   }
   else
   {
    dsmn_anm(dsmn_dizi, dsmn_hiz, dsmn_dky, kr, cph_blg, 17, dsmn_onceki);

    dsmn_onceki = dsmn_adres; /* islemi biten dugum onceki olsun */
   }

   dsmn_adres = dsmn_sonraki; /* sayac sonraki dugumu gostersin */
  } while(dsmn_sonraki != NULL);
 }
}

void dcph_zincir_oku(unsigned char *kr[], int cph_dizi[], float cph_hiz[], void dcph_anm(int[], float[], unsigned char *[]))
{ /* oyuncuyu dusman cephanesi dugumleri ile karsilastirir */
 cph *dcph_sonraki = NULL, /* sonraki dusman cephanesi dugumunu gsterir */
     *dcph_onceki = NULL;  /* onceki dusman cephanesi dugumunu gosterir */

 int x1, x2, y1, y2, blok, cikti;

 if(dcph_birinci != NULL) /* zincir mevcutsa */
 {
  dcph_adres = dcph_birinci; /* sayac saymaya birinci dugumden baslasin */

  do
  {
   dcph_sonraki = dcph_adres->sonraki;

   blok = dcph_adres->tip * 12;

   x1 = dcph_adres->x, y1 = dcph_adres->y;
   x2 = x1 + cph_dizi[blok + 2], y2 = y1 + cph_dizi[blok + 3];

   if(!dcph_adres->son_anm) /* siradaki dusman cephanesi aktifse */
   {
    if(!oyuncu.son_anm && oyuncu.x >= x1 - 32 && oyuncu.x + 33 <= x2 + 32 && oyuncu.y >= y1 - 10 && oyuncu.y + 11 <= y2 + 10)
    { /* kesisme durumu */
     dcph_adres->son_anm = 1, /* cephane son animasyonunu aktive et */
     dcph_adres->krsyc = 0, /* son animasyon icin kare sayacini sifirla */
     dcph_adres->krbksyc = cph_dizi[blok + 9]; /* kare bekleme sayaci yeni degerini alir */
     /* kalkan bonusu yoksa oyuncu hasar sayisini arttir */
     if(!oyuncu.tnr_syc) oyuncu.hasar += cph_dizi[blok + 1];
     if(oyuncu.hasar >= oyuncu.maxhsr) oyuncu.son_anm = 1; /* hasar max olursa oyuncuyu pasif hale getir */
    }
   }

   if(x2 < ex1 || y2 < ey1 || x1 > ex2 + 50 || y1 > ey2) /* cephane gorunen alan disina cikarsa */
    cikti = 1; else cikti = 0;

   if(cikti || dcph_adres->sil) /* dugum silme sarti */
   {
    if(dcph_adres == dcph_birinci) dcph_birinci = dcph_sonraki; /* birinci silinecekse ikinci birinci olsun */
    else /* silinecek birinci degilse sonrakini oncekine ekle */
    {
     dcph_onceki->sonraki = dcph_sonraki;
     if(dcph_adres == dcph_sonuncu) dcph_sonuncu = dcph_onceki; /* son dugum silindiyse sonuncu öncekini gostersin */
    }
    free(dcph_adres);
   }
   else
   {
    dcph_anm(cph_dizi, cph_hiz, kr);

    dcph_onceki = dcph_adres; /* islemi biten dugum onceki olsun */
   }

   dcph_adres = dcph_sonraki; /* sayac sonraki dugumu gostersin */
  } while(dcph_sonraki != NULL);
 }
}

void nsn_zincir_oku(unsigned char *kr[], int nsn_dizi[], void nsn_anm(int [], unsigned char *[]))
{ /* nesne dugumlerini isler */
 nsn *nsn_sonraki = NULL, /* sonraki nesne dugumunu gsterir */
     *nsn_onceki = NULL;  /* onceki nesne dugumunu gosterir */

 dsmn *dsmn_sonraki; /* sonraki dusman dugumunu gsterir */

 int cikti, blok, o;

 if(nsn_birinci != NULL) /* zincir mevcutsa */
 {
  nsn_adres = nsn_birinci; /* sayac saymaya birinci dugumden baslasin */

  do
  {
   nsn_sonraki = nsn_adres->sonraki;

   blok = nsn_adres->tip * 6;

   if(nsn_adres->no >= 0) /* okunan nsn koordinat olarak kime bagliysa bul */
   {
    if(nsn_adres->no == 0) /* oyuncuya bagliysa */
    {
     nsn_adres->x += oyuncu.xa;
     nsn_adres->y += oyuncu.ya;
    }
    else /* dusmanlardan birine bagliysa */
    { /* bulana kadar dsmn zincirini bastan sona oku */
     if(dsmn_birinci != NULL) /* zincir mevcutsa */
     {
      dsmn_adres = dsmn_birinci; /* sayac saymaya birinci dugumden baslasin */

      do
      {
       dsmn_sonraki = dsmn_adres->sonraki;

       if(nsn_adres->no == dsmn_adres->no) /* bulunca gerekli islemleri yap ve cik */
       {
        nsn_adres->x += dsmn_adres->xa; /* koordinat eslemesini yap */
        nsn_adres->y += dsmn_adres->ya; /* xa ve ya artis miktaridir */
        break;
       }

       dsmn_adres = dsmn_sonraki; /* sayac sonraki dugumu gostersin */
      } while(dsmn_sonraki != NULL);
     }
    }
   }
   else /* okunan nsn koordinat olarak kimseye bagli degilse ve */
   { /* no degiskeni burdan sonraki degerlerden birini alimissa degisik efektler elde edilir */
    if(nsn_adres->no == -2) /* -1 ise koordinat degismez */
    { /* -2 ise x koordinatinda sola kayar */
     nsn_adres->x--;
    }
    if(nsn_adres->no == -3) /* -3 ise -2ye ek olarak y ekseninde oyuncuya bagimli hareket eder */
    {
     nsn_adres->x--;
     nsn_adres->y += oyuncu.ya;
    }
    if(nsn_adres->no == -4) /* sicrama efekti */
    {
     nsn_adres->x += nsn_adres->xa;
     nsn_adres->ksyc += nsn_adres->k * 5;
     if(nsn_adres->ksyc >= 360) { nsn_adres->ksyc = 0; if(nsn_dizi[blok + 0]) nsn_adres->ya = 1; }
     nsn_adres->y += (nsn_adres->ya) ? 2 : -sin[nsn_adres->ksyc];
    }
   }

   /* gorunen alanin disina ciktiysa */
   if(nsn_adres->x < ex1 - nsn_dizi[blok + 1] || nsn_adres->y < ey1 - nsn_dizi[blok + 2] || nsn_adres->x > ex2 || nsn_adres->y > ey2)
    cikti = 1; else cikti = 0;

   if(cikti || nsn_adres->sil)
   {/* silme sarti */
    if(nsn_adres == nsn_birinci) nsn_birinci = nsn_sonraki; /* birinci silinecekse ikinci birinci olsun */
    else /* silinecek birinci degilse sonrakini oncekine ekle */
    {
     nsn_onceki->sonraki = nsn_sonraki;
     if(nsn_adres == nsn_sonuncu) nsn_sonuncu = nsn_onceki; /* son dugum silindiyse sonuncu öncekini gostersin */
    }
    free(nsn_adres);
   }
   else
   {
    nsn_anm(nsn_dizi, kr);

    nsn_onceki = nsn_adres; /* islemi biten dugum onceki olsun */
   }

   nsn_adres = nsn_sonraki; /* sayac sonraki dugumu gostersin */
  } while(nsn_sonraki != NULL);
 }
}