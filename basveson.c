void bas()
{ /* oyuna giris ekrani */
 int o, p, syc = 0, DMD_y = 0, bitti = 0, m = 0, n = 0, a = 2, uck_x = ex1 - 33, k = 0;
 float l = 0;

 unsigned char *rsm[5];

 rsm[0] = (unsigned char *) calloc(3551, 1);
 rsm[1] = (unsigned char *) calloc(698, 1);
 rsm[2] = (unsigned char *) calloc(380, 1);
 rsm[3] = (unsigned char *) calloc(134, 1);
 rsm[4] = (unsigned char *) calloc(66, 1);

 XCPyi_bellege_oku("kaynak02.xcp", RGB, SNL);

 kare_oku(1,1,91,39,SNL,rsm[0]); /* DMD */
 kare_oku(1,41,87,48,SNL,rsm[1]); /* TvP */
 kare_oku(1,50,54,56,SNL,rsm[2]); /* SS */
 kare_oku(56,50,88,53,SNL,rsm[3]); /* tarih */
 kare_oku(71,118,86,121,SNL,rsm[4]); /* versiyon */

 T.Esc = 0;
 T.Enter = 0;

 while(!T.Esc && !T.Enter && syc < 750)
 {
  kronometre = 0;

  memset(SNL, 0, 64000);

  if(syc > 100) DMD_y += 5; /* oyunun ismi ekranin ustunden inmeye baslasin */
  if(DMD_y >= ey1 + 61) /* inme tamamlandiysa */
  {
   DMD_y = ey1 + 61; /* seviyeyi sabitle */

   kare_koy(ex2 - 16, ey2 - 4, rsm[4], SNL); /* oyunun versiyonunu ekrana bas */

   if(!bitti) /* cizgi animasyonu bitmediyse devam etsin */
   {
    for(o = 0; o < n / 2; o++)
    {
     SNL[159 + m - o + 100 * 320] = 58;
     SNL[159 - m + o + 100 * 320] = 58;
    }

    if(m <= 158)
    {
     n += a;
     if(m >= 79) a = -2;
     m += 2;
    } /* cizgiler ekranin kenarlarina ulastiginda cizgi animasyonu biter */
    else bitti = 1;
   }
  } /* cizgi animasyonu bittiyse ucak soldan ekrana girsin */
  if(bitti) { if(uck_x <= ex2) uck_x += 2; }

  kare_koy(ex1 + 114, DMD_y, rsm[0], SNL); /* oyunun ismini ekrana bas */

  /* ucak ustunden gectigi yaziyi tamamen acmissa */
  /* acilan yazinin altindan benim ismim inmeye baslasin =) */
  if(k >= 87) { if(l < 20) l += 0.2; }

  if(syc >= 500) /* zamani geldiginde oyunun yapim tarih araligini ekrana bas */
  {
   kare_koy(ex1 + 143, ey1 + 150, rsm[3], SNL);
  }

  kare_koy(ex1 + 132, ey1 + 120 + l, rsm[2], SNL); /* ismimi ekrana bas =P */
  /* ve ucagin actigi yazinin altinda kalan kismini sil */
  for(o = 0; o < 54; o++)
   for(p = 0; p < 7; p++)
    SNL[132 + o + (120 + p) * 320] = 0;

  /* acacagi yazinin ustundeyken ucagin yazinin basina uzakligini bul */
  if(uck_x >= ex1 + 116 && uck_x <= ex1 + 205) k = uck_x - ex1 - 116;

  kare_koy(ex1 + 116, ey1 + 120, rsm[1], SNL); /* ucagin acacagi yaziyi ekrana bas */
  /* ucagin acmadigi kadarini sil */
  for(o = k; o < 87; o++)
   for(p = 0; p < 8; p++)
    SNL[116 + o + (120 + p) * 320] = 0;

  kare_koy(uck_x, ey1 + 120, oyuncu.kare[9], SNL); /* ucagi ekrana bas */

  memcpy(VGA, SNL, 64000);

  syc++;

  while(kronometre < 10);
 }

 for(o = 0; o < 5; o++) free(rsm[o]);
}

rekor() /* varsa yeni rekoru kaydeden ve son rekoru gosteren ekranlar */
{
 /* bellek taksimini kolaylastirma amacli siralama dizisi */
 int sr[] = {10,11, 12,14, 3,5,6,9,13,19,21,22,28, 0,1,2,4,7,8,16,17,18,20,23,24,25,26,27, 15};
 FILE *dosya;
 int o, puan = 0, pf = 1, h = 0, p[] = {0,0,0,0}, ys[] = {0,0};
 int eisim[45], yisim[45], i = 0, j = 0, eboy = 0, yboy = 0, exblok = 0, yxblok = 0;
 unsigned char *harf[30], *czg, *cmllr[6];

 for(o = 0; o < 2; o++) harf[sr[o]] = (unsigned char *) calloc(12, 1);
 for(o = o; o < 4; o++) harf[sr[o]] = (unsigned char *) calloc(32, 1);
 for(o = o; o < 13; o++) harf[sr[o]] = (unsigned char *) calloc(42, 1);
 for(o = o; o < 28; o++) harf[sr[o]] = (unsigned char *) calloc(52, 1);
 for(o = o; o < 29; o++) harf[sr[o]] = (unsigned char *) calloc(72, 1);

 harf[29] = (unsigned char *) calloc(42, 1);
 czg = (unsigned char *) calloc(12, 1);
 cmllr[0] = (unsigned char *) calloc(4410, 1);
 cmllr[1] = (unsigned char *) calloc(506, 1);
 cmllr[2] = (unsigned char *) calloc(698, 1);
 cmllr[3] = (unsigned char *) calloc(418, 1);
 cmllr[4] = (unsigned char *) calloc(1170, 1);
 cmllr[5] = (unsigned char *) calloc(578, 1);

 XCPyi_bellege_oku("kaynak02.xcp", RGB, SNL);

 kare_oku(108,78,112,87,SNL,harf[0]);
 kare_oku(114,78,118,87,SNL,harf[1]);
 kare_oku(120,78,124,87,SNL,harf[2]);
 kare_oku(126,78,129,87,SNL,harf[3]);
 kare_oku(131,78,135,87,SNL,harf[4]);
 kare_oku(137,78,140,87,SNL,harf[5]);
 kare_oku(142,78,145,87,SNL,harf[6]);
 kare_oku(147,78,151,87,SNL,harf[7]);
 kare_oku(153,78,157,87,SNL,harf[8]);
 kare_oku(159,78,162,87,SNL,harf[9]);
 kare_oku(164,78,164,87,SNL,harf[10]);
 kare_oku(166,78,166,87,SNL,harf[11]);
 kare_oku(168,78,170,87,SNL,harf[12]);
 kare_oku(172,78,175,87,SNL,harf[13]);
 kare_oku(177,78,179,87,SNL,harf[14]);
 kare_oku(181,78,187,87,SNL,harf[15]);
 kare_oku(189,78,193,87,SNL,harf[16]);
 kare_oku(195,78,199,87,SNL,harf[17]);
 kare_oku(201,78,205,87,SNL,harf[18]);
 kare_oku(207,78,210,87,SNL,harf[19]);
 kare_oku(212,78,216,87,SNL,harf[20]);
 kare_oku(218,78,221,87,SNL,harf[21]);
 kare_oku(223,78,226,87,SNL,harf[22]);
 kare_oku(228,78,232,87,SNL,harf[23]);
 kare_oku(234,78,238,87,SNL,harf[24]);
 kare_oku(240,78,244,87,SNL,harf[25]);
 kare_oku(246,78,250,87,SNL,harf[26]);
 kare_oku(252,78,256,87,SNL,harf[27]);
 kare_oku(258,78,261,87,SNL,harf[28]);
 kare_oku(263,78,266,87,SNL,harf[29]);

 kare_oku(90,41,90,50,SNL,czg);

 kare_oku(119,117,270,145,SNL,cmllr[0]); /* tebrikler */
 kare_oku(108,89,163,97,SNL,cmllr[1]); /* isimli oyuncunun */
 kare_oku(108,99,194,106,SNL,cmllr[2]); /* puanlik rekorunu kirdiniz */
 kare_oku(196,99,247,106,SNL,cmllr[3]); /* en yuksek puan */
 kare_oku(108,108,253,115,SNL,cmllr[4]); /* ok tuslariyla isminizi yazip entera basiniz */
 kare_oku(196,99,267,106,SNL,cmllr[5]); /* en yuksek puan sizin */

 /* varsa eski rekor bilgilerini oku */
 dosya = fopen("rekor.kyt", "rb");
 if(dosya != NULL)
 {
  puan = getw(dosya);
  while(!feof(dosya)) eisim[i++] = getc(dosya);
  i--;
 }
 fclose(dosya);

 /* yeni bir rekor kirilmissa */
 if(oyuncu.son_puan > puan)
 {/* eski rekor sahibinin isminin uzunlugunu hesapla (harf arasi bosluklar dahil) */
  for(o = 0; o < i; o++) eboy += (harf[eisim[o]])[0] + 1;
  /* uzunlugu tutan degisken burda ekrana ortalamayi saglama amacli kullanilmistir */
  eboy = (320 - eboy) / 2;

  /* eski rekorun kac haneli oldugunu bul */
  while(puan / pf) { pf *= 10; ++h; }
  /* rekorun sayi olarak ekrana yatay ortalanmasini saglamak uzere kullanmak icin */
  /* ekranin solundan uzakligini hesapla */
  pf = (320 - h * 4) / 2 + h * 4;
  h = 29;

  T.art = 0;

  while(!T.Enter || (j == 0 && h == 29))
  {
   kronometre = 0;

   memset(SNL, 0, 64000);

   hzl_kare_koy(87, 5, cmllr[0], SNL); /* "tebrikler" */

   if(dosya != NULL)
   {
    exblok = 0; /* herbir harfin kelimenin basindan uzakligini tutar */
    for(o = 0; o < i; o++) /* ismin herbir harfini ekrana bas */
    {
     hzl_kare_koy(eboy + exblok, 78, harf[eisim[o]], SNL);
     exblok += (harf[eisim[o]])[0] + 1;
    }

    hzl_kare_koy(132, 90, cmllr[1], SNL); /* "isimli oyuncunun" */
    sayi_yaz(ex1 + pf, ey1 + 106, puan, rakam, SNL);
    hzl_kare_koy(116, 111, cmllr[2], SNL); /* "puanlik rekorunu kirdiniz" */
   }

   hzl_kare_koy(124, 60, cmllr[5], SNL); /* "en yuksek puan sizin" */
   hzl_kare_koy(85, 135, cmllr[4], SNL); /* "yon tuslariyla isminizi yazip entera basiniz" */

   /* yeni isim dizisinin eleman sayisini 1 azaltir */
   if(T.sol) { if(!p[0]) { p[0] = 5; j--; if(j < 0) j = 0; h = 29; } else p[0]--; }
   /* yeni isim dizisinin eleman sayisini 1 arttirir */
   if(T.sag) { if(!p[1]) { p[1] = 5; j++; if(j > 44) j = 44; h = 29; } else p[1]--; }
   /* dizinin secili elemaninin degerini 1 arttirir */
   if(T.ilr) { if(!p[2]) { p[2] = 5; h++; if(h > 29) h = 0; } else p[2]--; }
   /* dizinin secili elemaninin degerini 1 azaltir */
   if(T.gri) { if(!p[3]) { p[3] = 5; h--; if(h < 0) h = 29; } else p[3]--; }
   yisim[j] = h; /* secili son dizi elemanini belirlenen degere getirir */

   /* yeni rekor sahibinin isminin uzunlugunu hesapla (harf arasi bosluklar dahil) */
   yboy = 0;
   for(o = 0; o <= j; o++) yboy += (harf[yisim[o]])[0] + 1;
   /* uzunlugu tutan degisken burda ekrana ortalamayi saglama amacli kullanilmistir */
   yboy = (320 - yboy) / 2;
   yxblok = 0; /* herbir harfin kelimenin basindan uzakligini tutar */
   for(o = 0; o <= j; o++) /* ismin herbir harfini ekrana bas */
   {
    hzl_kare_koy(yboy + yxblok, 150, harf[yisim[o]], SNL);
    yxblok += (harf[yisim[o]])[0] + 1;
   }
   /* secili (ayni zamanda son) harfin nereye basilacagini gosteren cizgi */
   yan_son(yboy + yxblok - (harf[yisim[j]])[0] - 2, 150, ys, 25, 25, czg);

   memcpy(VGA, SNL, 64000);

   while(kronometre < 10);
  }

  /* yeni rekoru eskisini silip ustune yaz */
  dosya = fopen("rekor.kyt", "wb");
  if(dosya != NULL)
  {
   putw(oyuncu.son_puan, dosya);
   i = 0;
   while(i <= j) putc(yisim[i++], dosya);
  }
  fclose(dosya);
 }

 /* son rekor kaydini oku */
 i = 0;
 dosya = fopen("rekor.kyt", "rb");
 if(dosya != NULL)
 {
  puan = getw(dosya);
  while(!feof(dosya)) eisim[i++] = getc(dosya);
  i--;

  /* son rekor sahibinin isminin uzunlugunu hesapla (harf arasi bosluklar dahil) */
  eboy = 0;
  for(o = 0; o < i; o++) eboy += (harf[eisim[o]])[0] + 1;
  /* uzunlugu tutan degisken burda ekrana ortalamayi saglama amacli kullanilmistir */
  eboy = (320 - eboy) / 2;

  /* eski rekorun kac haneli oldugunu bul */
  h = 0;
  pf = 1;
  while(puan / pf) { pf *= 10; ++h; }
  /* rekorun sayi olarak ekrana yatay ortalanmasini saglayacak olan */
  /* ekranin solundan uzakligini hesapla */
  pf = (320 - h * 4) / 2 + h * 4;

  memset(VGA, 0, 64000);

  hzl_kare_koy(134, 90, cmllr[3], VGA); /* "en yuksek puan" */

  sayi_yaz(ex1 + pf, ey1 + 105, puan, rakam, VGA);

  exblok = 0;
  for(o = 0; o < i; o++) /* ismin herbir harfini ekrana bas */
  { hzl_kare_koy(eboy + exblok, 110, harf[eisim[o]], VGA); exblok += (harf[eisim[o]])[0] + 1; }

  hzl_kare_koy(132, 120, cmllr[1], VGA); /* "isimli oyuncunun" */

  kronometre = 0;
  T.Esc = 0;
  T.Enter = 0;
  while(kronometre < 10000 && !T.Esc && !T.Enter);
 }
 fclose(dosya);

 for(o = 0; o < 30; o++) free(harf[o]);
 for(o = 0; o < 6; o++) free(cmllr[o]);
 free(czg);
}

void son() /* oyundan cikis ekrani */
{
 unsigned char *rsm = (unsigned char *) calloc(4666, 1);

 XCPyi_bellege_oku("kaynak02.xcp", RGB, SNL);

 kare_oku(1,58,106,101,SNL,rsm);

 memset(VGA, 0, 64000);

 kare_koy(ex1 + 106, ey1 + 78, rsm, VGA);

 kronometre = 0;

 T.Esc = 0;
 T.Enter = 0;

 while(!T.Esc && !T.Enter && kronometre < 10000);

 free(rsm);
}

void kznd() /* kazanma ekrani */
{
 int o, p, uzyl_x = ex1 - 13, syc = 0, krsyc = 1, kr = 0, uck_x = ex1 - 33;
 int k = 0, l = 0, m = 33, n = 36, krlr[] = {3,2,1,0,1,2,3,4};
 float e = 0, f = 0;

 unsigned char *uzyl[5];
 unsigned char *szlr[2];

 for(o = 0; o < 5; o++) uzyl[o] = (unsigned char *) calloc(288, 1);
 szlr[0] = (unsigned char *) calloc(167, 1);
 szlr[1] = (unsigned char *) calloc(290, 1);

 XCPyi_bellege_oku("kaynak02.xcp", RGB, SNL);

 kare_oku(71,103,103,107,SNL,szlr[0]); /* uzaylinin soyledigi */
 kare_oku(71,109,106,116,SNL,szlr[1]); /* ucagin soyledigi =) */

 kare_oku(1,103,13,124,SNL,uzyl[0]);
 kare_oku(15,103,27,124,SNL,uzyl[1]);
 kare_oku(29,103,41,124,SNL,uzyl[2]);
 kare_oku(43,103,55,124,SNL,uzyl[3]);
 kare_oku(57,103,69,124,SNL,uzyl[4]);

 T.Esc = 0;
 T.Enter = 0;

 while(!T.Esc && !T.Enter && syc < 750)
 {
  kronometre = 0;

  memset(SNL, 0, 64000);

  if(syc > 100) uzyl_x++; /* zamani gelince uzayli saga dogru kosmaya baslasin */
  if(syc > 350) uck_x += 2; /* zamani gelince ucak uzayliyi kovalamaya baslasin */

  if(uzyl_x >= ex1 + 75 && uzyl_x < ex1 + 108) k++; /* uzaylinin sozu acilmaya baslasin */
  if(uzyl_x == ex1 + 141) { k = 0; m = 0; }
  if(uzyl_x > ex1 + 141) m++; /* uzaylinin sozu kapanmaya baslasin */
  if(uck_x >= ex1 + 150 && uck_x < ex1 + 186) l += 2; /* ucagin sozu acilmaya baslasin */
  if(uck_x == ex1 + 186) { l = 0; n = 0; }
  if(uck_x > ex1 + 186) n += 2; /* ucagin sozu kapanmaya baslasin */

  kare_koy(ex1 + 75 + e, ey1 + 70, szlr[0], SNL); /* uzaylinin sozunu ekrana bas */
  for(o = k; o < m; o++) /* gerektigi kadarini sil */
   for(p = 0; p < 5; p++)
    SNL[75 + o + e + (70 + p) * 320] = 0;

  kare_koy(ex1 + 150 + f, ey1 + 70, szlr[1], SNL); /* ucagin sozunu ekrana bas */
  for(o = l; o < n; o++) /* gerektigi kadarini sil */
   for(p = 0; p < 9; p++)
    SNL[150 + o + f + (69 + p) * 320] = 0;

  if(uzyl_x >= ex1 + 75) e += 0.3; /* uzaylinin sozu saga kaymaya baslasin */
  if(uck_x >= ex1 + 150) f += 0.5; /* ucagin sozu saga kaymaya baslasin */

  kare_koy(uck_x, ey1 + 85, oyuncu.kare[9], SNL); /* ucagi ekrana bas */

  kare_koy(uzyl_x, ey1 + 80, uzyl[krlr[kr]], SNL); /* uzaylinin sirasi gelen karesini ekrana bas */

  /* uzaylinin bir sonraki resim karesini belirle */
  krsyc++;
  if(krsyc == 8) krsyc = 1;
  if(!(krsyc % 7)) kr++;
  if(kr == 8) kr = 0;

  memcpy(VGA, SNL, 64000);

  syc++;

  while(kronometre < 10);
 }

 aciklama(81, 77, "kaynak02.xcp", 108, 31, 257, 76, 5000);

 for(o = 0; o < 5; o++) free(uzyl[o]);
}

void kybtt() /* kaybetme ekrani */
{
 int o, p, syc = 0;
 float k = 0;

 unsigned char *ob;

 ob = (unsigned char *) calloc(5512, 1);

 XCPyi_bellege_oku("kaynak02.xcp", RGB, SNL);

 kare_oku(93,1,282,29,SNL,ob);

 aciklama(103, 91, "kaynak02.xcp", 1, 126, 117, 142, 2500);

 T.Esc = 0;
 T.Enter = 0;

 while(!T.Esc && !T.Enter && syc < 250)
 {
  kronometre = 0;

  memset(SNL, 0, 64000);

  kare_koy(ex1 + 65, ey1 + 85, ob, SNL); /* "oyun bitti" yazisini ekrana bas */
  /* "oyun bitti" yazisini ust ve alt kenarindan esit uzakliga kadar kapat */
  for(o = 0; o < 190; o++) /* ust yari */
   for(p = 0; p < 14 - k; p++)
    SNL[65 + o + (85 + p) * 320] = 0;
  for(o = 0; o < 190; o++) /* alt yari */
   for(p = 15; p >= k; p--)
    SNL[65 + o + (99 + p) * 320] = 0;

  if(syc > 50 && k < 15) k += 0.25; /* kapatma miktarini azaltmaya basla */

  syc++;

  memcpy(VGA, SNL, 64000);

  while(kronometre < 10);
 }

 free(ob);
}