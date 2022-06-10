int grv1(void)
{
 int o, p, r = 0;

 int dsmn_blg[] = {/* dusman tiplerinin bilgilerini tutan dizi */
           /* en/ boy/ kilk/ ksay/ kbek/ pa/  ha/ tnr/ guc/ sna1/snas/sabk *//* bonuslar icin gecerli bilgi satiri */
 /* pr/mxhsr/ en/ boy/ kilk/ ksay/ kbek/ ns/  mh/ adt/ bkl/ ctip/ n1x/ n1y/ ctip/ n2x/ n2y/ ctip/ n3x/ n3y/ ctip/ n4x/ n4y/ ctip/ n5x/ n5y *//* tip */
     0,    0,  8,   8,   77,    8,   10,  5,   0,   0,   0,    0,   0,   0,    0,   0,   0,    0,   0,   0,    0,   0,   0,    0,   0,   0,  /*  0  *//* bonus 0 */
     0,    0, 20,  10,   65,    4,   10,  0, 200,   0,   0,   69,   8,   5,    0,   0,   0,    0,   0,   0,    0,   0,   0,    0,   0,   0,  /*  1  *//* bonus 1 */
     0,    0, 23,  23,   99,    8,    5,  0,   0,2500,   0,  104,   6,  10,    0,   0,   0,    0,   0,   0,    0,   0,   0,    0,   0,   0,  /*  2  *//* bonus 2 */
     0,    0, 13,  17,   89,    4,   10,  0,   0,   0,2500,   90,   6,   5,    0,   0,   0,    0,   0,   0,    0,   0,   0,    0,   0,   0,  /*  3  *//* bonus 3 */
     0,   20, 11,  11,   12,    6,    5,  0,   0,   0,   0,    0,   0,   0,    0,   0,   0,    0,   0,   0,    0,   0,   0,    0,   0,   0,  /*  4  *//* kor mayin */
     0,   10, 30,  15,   47,    4,    5,  0,   0,   0,   0,    0,   0,   0,    0,   0,   0,    0,   0,   0,    0,   0,   0,    0,   0,   0,  /*  5  *//* kamikaze  */
     1,  750, 30,  18,   57,    1,    0,  1,  25,   2, 100,   20,  14,  10,    0,   0,   0,    0,   0,   0,    0,   0,   0,    0,   0,   0,  /*  6  *//* mayinci   */
     1,    5, 23,  15,   58,    1,    0,  1,   0,   1, 200,   10,   1,   5,    0,   0,   0,    0,   0,   0,    0,   0,   0,    0,   0,   0,  /*  7  *//* 1 nml n 1 */
     1,   10, 38,  15,   59,    1,    0,  1,  50,   2,  50,   10,   6,   9,    0,   0,   0,    0,   0,   0,    0,   0,   0,    0,   0,   0,  /*  8  *//* 1 nml n 2 */
     1,   15, 38,  14,   56,    1,    0,  1,  25,   3, 150,   10,   4,   7,    0,   0,   0,    0,   0,   0,    0,   0,   0,    0,   0,   0,  /*  9  *//* 1 nml n 3 */
     1,   10, 30,  21,   53,    1,    0,  2,  25,   2, 100,   10,   6,   2,   10,   6,  14,    0,   0,   0,    0,   0,   0,    0,   0,   0,  /* 10  *//* 2 nml n 1 */
     1,   15, 29,  20,   55,    1,    0,  2,  25,   2,  50,   11,   8,  15,   12,   8,   0,    0,   0,   0,    0,   0,   0,    0,   0,   0,  /* 11  *//* 2 nml n 2 */
     1,   30, 27,  24,   51,    1,    0,  2,  25,   2, 100,   10,  10,   4,   10,   6,  16,    0,   0,   0,    0,   0,   0,    0,   0,   0,  /* 12  *//* 2 nml n 3 */
     1,   20, 37,  22,   52,    1,    0,  3,  15,   3, 100,   10,  16,   9,   13,  20,  20,   14,  20,  -2,    0,   0,   0,    0,   0,   0,  /* 13  *//* 3 nml n 1 */
     1,   15, 32,  21,   54,    1,    0,  3,  50,   2,  50,   21,  15,   8,   11,  10,  17,   12,  10,  -1,    0,   0,   0,    0,   0,   0,  /* 14  *//* 3 nml n 2 */
     1,  750, 68,  19,   60,    1,    0,  5,  50,   2, 150,   11,  21,  15,   12,  21,  -1,   15,  39,  15,   16,  39,  -1,   19,  30,   7,  /* 15  *//* 5 nml n 1 */
     0,   30, 15,  15,   85,    4,   10,  1,   0,   1, 100,   19,   6,   6,    0,   0,   0,    0,   0,   0,    0,   0,   0,    0,   0,   0,  /* 16  *//* 1 nml hdf */
/* burdan sonrakiler bonus seviyeler icin rastgele sirada yaratilan birimler *//* hiz dizisinde bulunmazlar */                    /* /oyuna ekleme sayaci */
     1,  100, 45,  34,  115,    1,    0,  1,   0,   1, 100,   19,  31,  -2,    0,   0,   0,    0,   0,   0,    0,   0,   0,    0,   0, 500,  /* 17  *//* balina */
     0,   10, 13,  12,  116,    4,    5,  1,   0,   1, 100,   17,   4,   0,    0,   0,   0,    0,   0,   0,    0,   0,   0,    0,   0,   0,  /* 18  *//* bocek */
     0,    0, 10,  10,  120,    1,    0,  0,   0,   0,   0,    0,   0,   0,    0,   0,   0,    0,   0,   0,    0,   0,   0,    0,   0,   0,  /* 19  *//* yilan parcasi */
                                                                                                                      /* yilan sayisi/yilan ekle/ */
     0,  150, 15,  15,  121,    8,   10,  0,   0,   0,   0,    0,   0,   0,    0,   0,   0,    0,   0,   0,    0,   0,   0,    0,   0,   0,  /* 20  *//* yilan basi */
                                                                                                          /* kozanin son x koordinati/oyuna ekleme sayaci */
     0,   50, 10,  10,  120,    1,    0,  0,   0,   0,   0,    0,   0,   0,    0,   0,   0,    0,   0,   0,    0,   0,   0,    0,   0, 500}; /* 21  *//* koza */

 /* dusman tiplerinin hizlarini tutan dizi *//* (-) yonde */
      /* dusman tip :   0/    1/    2/    3/    4/    5/    6/    7/    8/    9/   10/   11/   12/   13/   14/   15/   16/ */
 float dsmn_hiz[] = {0.10, 0.50, 0.50, 0.50, 0.25, 1.00, 0.05, 0.50, 0.50, 0.40, 0.50, 1.00, 0.30, 0.50, 1.00, 0.05, 0.50};

 int cph_blg[] = {/* cephane tiplerinin bilgilerini tutan dizi */
 /*  htip/ hsrgc/ en/ boy/ kilk/ ksay/ kbek/ sna1/ snas/ sabk/ samx/ samy *//* tip */
        0,     1,  2,   2,   30,    2,   10,   31,    4,    1,   -1,   -1,  /*  0  *//* mrm +1+0 */
        0,     1,  2,   2,   30,    2,   10,   31,    4,    1,    0,    0,  /*  1  *//* mrm +1+1 */
        0,     1,  2,   2,   30,    2,   10,   31,    4,    1,    0,    0,  /*  2  *//* mrm +1-1 */
        0,     1,  2,   2,   30,    2,   10,   31,    4,    1,    0,    0,  /*  3  *//* mrm +0+1 */
        0,     1,  2,   2,   30,    2,   10,   31,    4,    1,    0,    0,  /*  4  *//* mrm +0-1 */
        0,     2,  7,   4,   44,    3,    5,   22,    4,    5,   -4,   -4,  /*  5  *//* rkt +1+0 */
        0,     2,  7,   4,   44,    3,    5,   22,    4,    5,   -4,   -4,  /*  6  *//* rkt +1+1 */
        0,     2,  7,   4,   44,    3,    5,   22,    4,    5,   -4,   -4,  /*  7  *//* rkt +1-1 */
        0,     2,  7,   4,   44,    3,    5,   22,    4,    5,   -4,   -4,  /*  8  *//* rkt +0+1 */
        0,     2,  7,   4,   44,    3,    5,   22,    4,    5,   -4,   -4,  /*  9  *//* rkt +0-1 */
        0,    10,  5,   5,   40,    4,    5,   22,    4,    5,   -4,   -4,  /* 10  *//* atp -1+0 */
        0,    10,  5,   5,   40,    4,    5,   22,    4,    5,   -4,   -4,  /* 11  *//* atp -1-1 */
        0,    10,  5,   5,   40,    4,    5,   22,    4,    5,   -4,   -4,  /* 12  *//* atp -1+1 */
        0,    10,  5,   5,   40,    4,    5,   22,    4,    5,   -4,   -4,  /* 13  *//* atp -0-1 */
        0,    10,  5,   5,   40,    4,    5,   22,    4,    5,   -4,   -4,  /* 14  *//* atp -0+1 */
        0,    10,  5,   5,   40,    4,    5,   22,    4,    5,   -4,   -4,  /* 15  *//* atp +1-1 */
        0,    10,  5,   5,   40,    4,    5,   22,    4,    5,   -4,   -4,  /* 16  *//* atp +1+1 */
        1,    10,  5,   5,   40,    4,    5,   22,    4,    5,   -4,   -4,  /* 17  *//* atp hdfl */
        0,    20,  5,   5,   36,    4,    3,   18,    4,    5,   -4,   -4,  /* 18  *//* krmz smsk -1+0 *//*hic kullanmadim*/
        1,    20,  5,   5,   36,    4,    3,   18,    4,    5,   -4,   -4,  /* 19  *//* krmz smsk hdfl */
        2,   100,  8,   8,   26,    4,   10,    0,   12,    5,  -13,  -12,  /* 20  *//* gdml myn */
        0,    10,  5,   5,   40,    4,    5,   22,    4,    5,   -4,   -4,  /* 21  *//* hzl atp -1+0 */
        0,    25, 30,  15,   47,    4,    5,    0,   12,    5,   -5,   -7}; /* 22  *//* byk rkt -1+0 */

 /* cephane tiplerinin hizlarini tutan dizi *//* isaret yon belirtir */
                  /*    x/    y/ *//* tip *//* htip 1 (hedefli) ve 2 (gudumlu) icin x adim buyuklugudur y kullanilmamistir */
 float cph_hiz[] = {+2.00,+0.00,   /*  0  */
                    +1.40,+1.40,   /*  1  */
                    +1.40,-1.40,   /*  2  */
                    +0.00,+2.00,   /*  3  */
                    +0.00,-2.00,   /*  4  */
                    +1.75,+0.00,   /*  5  */
                    +1.24,+1.24,   /*  6  */
                    +1.24,-1.24,   /*  7  */
                    +0.00,+1.75,   /*  8  */
                    +0.00,-1.75,   /*  9  */
                    -1.00,+0.00,   /* 10  */
                    -1.70,+0.70,   /* 11  */
                    -1.70,-0.70,   /* 12  */
                    -0.50,+1.00,   /* 13  */
                    -0.50,-1.00,   /* 14  */
                    +0.70,+0.70,   /* 15  */
                    +0.70,-0.70,   /* 16  */
                    +2.00,+0.00,   /* 17  */
                    -1.00,+0.00,   /* 18  */
                    +2.00,+0.00,   /* 19  */
                    +0.50,+0.00,   /* 20  */
                    -2.00,+0.00,   /* 21  */
                    -1.50,+0.00};  /* 22  */

 int nsn_dizi[] = {/* nesne tiplerinin bilgilerini tutan dizi */
 /*  yineli/ en/ boy/ kilk/ ksay/ kbek *//* tip *//* en ve boy ekrandan cikma kontrolu icin kullanilmistir */
          0,  3,   5,    0,   50,    0,  /*  0  *//* puan anm icin*/
          0,  9,   9,   22,    4,   10,  /*  1  *//* kucuk patlama */
          0, 31,  29,    0,   12,   10,  /*  2  *//* buyuk patlama */
          0, 25,  25,   61,    4,   10,  /*  3  *//* toz */
          1,  1,   1,  129,    1,    0}; /*  4  *//* kan damlasi */

 unsigned char *kare[130];

 gorev1_grafikler(kare);

 oyuncu.pbrj = 100;
 oyuncu.hbrj = 50;
 svy.bsck = 0; /* bolum sonu canavari yok */
 aciklama(81, 87, "kaynak03.xcp", 1, 1, 158, 27, 10000);
 arkaplan_ilk_degerler(1, 16, 32, 0, 0, 0, 0, 0, 0, 0);
 if(seviye(dsmn_blg, dsmn_hiz, cph_blg, cph_hiz, nsn_dizi, kare, grv1svy1, 0, 0))
 {
  aciklama(88, 73, "kaynak03.xcp", 1, 29, 144, 81, 10000);
  arkaplan_ilk_degerler(1, 16, 32, 1, 3, 100, 199, 0, 0, 0);
  tplr[0].alt = 199, tplr[0].ust = 179;
  tplr[1].alt = 184, tplr[1].ust = 164;
  tplr[2].alt = 169, tplr[2].ust = 139;
  for(p = 0; p < 3; p++)
  {
   tplr[p].b = tplr[p].ust + rand() % (tplr[p].alt - tplr[p].ust);
   for(o = 0; o < 320; o++) tepeler(p, 1);
  }
  svy.tkr_syc = 0;
  if(seviye(dsmn_blg, dsmn_hiz, cph_blg, cph_hiz, nsn_dizi, kare, bns_svy1, 1, 0))
  {
   oyuncu.pbrj = 150;
   dsmn_blg[6 * 26 + 1] = 30; /* mayinci mxhsr degisiklik */
   dsmn_blg[6 * 26 + 8] = 50; /* mayinci mh degisiklik */
   dsmn_hiz[6] = 0.25; /* mayinci hiz degisiklik */
   cph_blg[20 * 12 + 1] = 30; /* gdml myn hsrgc degisiklik */
   cph_hiz[20 * 2 + 0] = 1; /* gdml myn hiz degisiklik */
   aciklama(80, 82, "kaynak03.xcp", 1, 83, 160, 117, 10000);
   arkaplan_ilk_degerler(1, 16, 32, 0, 0, 0, 0, 0, 0, 0);
   if(seviye(dsmn_blg, dsmn_hiz, cph_blg, cph_hiz, nsn_dizi, kare, grv1svy2, 0, 0))
   {
    aciklama(84, 82, "kaynak03.xcp", 1, 119, 151, 153, 10000);
    arkaplan_ilk_degerler(1, 32, 8, 1, 1, 100, 199, 1, 5, 175);
    tplr[0].periyot = 4;
    tplr[0].alt = 199, tplr[0].ust = 149;
    tplr[0].b = tplr[0].ust + rand() % (tplr[0].alt - tplr[0].ust);
    for(o = 0; o < 320; o++) tepeler(0, 1);
    svy.tkr_syc = 0;
    if(seviye(dsmn_blg, dsmn_hiz, cph_blg, cph_hiz, nsn_dizi, kare, bns_svy2, 1, 8))
    {
     oyuncu.pbrj = 100;
     dsmn_blg[15 * 26 + 1] = 50; /* 5 nml n 1 mxhsr degisiklik */
     dsmn_hiz[15] = 0.30; /* 5 nml n 1 hiz degisiklik */
     svy.bsck = 1; /* bolum sonu canavari var */
     bsc.x = ex2;
     bsc.y = ey1 + 75;
     bsc.hsyc = 0;
     bsc.asyc = 0;
     bsc.tsyc = 0;
     bsc.ih = 1;
     bsc.hasar = 0;
     bsc.ilk_syc = 1000;
     bsc.son_syc = 500;
     bsc.son_anm = 0;
     aciklama(71, 79, "kaynak03.xcp", 1, 155, 178, 196, 10000);
     arkaplan_ilk_degerler(1, 16, 32, 0, 0, 0, 0, 0, 0, 0);
     if(seviye(dsmn_blg, dsmn_hiz, cph_blg, cph_hiz, nsn_dizi, kare, grv1svy3, 0, 0)) r = 1;
    }
   }
  }
 }

 grafikleri_sil(kare, 130);
 return r;
}