void sayi_yaz(int x, int y, int sayi, unsigned char *rkm[], unsigned char *yer)
{ /* rkm isimli isretci dizisinde tutulan rakam resimleriyle sayi ile verilen sayiyi yazar */
 int blm, yz, n = 1, eksi = 0;
 unsigned char *czg = (unsigned char *) calloc(5, 1);
 czg[0] = 3, czg[1] = 1, czg[2] = 63, czg[3] = 63, czg[4] = 63;

 y -= 4;

 if(sayi < 0) { sayi = -sayi; eksi = 1; }

 do /* sayinin hanelerine ulas */
 {
  blm = sayi / (n * 10);
  yz = sayi / n - blm * 10;
  n *= 10;
  x -= 4;
  kare_koy(x, y, rkm[yz], yer);
 }
 while(blm);

 if(eksi) kare_koy(x - 5, y + 2, czg, yer);
 free(czg);
}

void hedefli(float adim)
{ /* verilen koordinatlari, onceden belli koordinatlara gore ayarlanmis */
  /* sabit bir dogrultuda ilerletir */

 if(dcph_adres->asyc >= 1)
 { /* Bresenham'in cizgi algoritmasindan uyarlanmistir */
  dcph_adres->asyc = 0;

  dcph_adres->s += dcph_adres->n;

  if(dcph_adres->s >= dcph_adres->m)
  {
   dcph_adres->s -= dcph_adres->m;
   dcph_adres->x += dcph_adres->d1x;
   dcph_adres->y += dcph_adres->d1y;
  }
  else
  {
   dcph_adres->x += dcph_adres->d2x;
   dcph_adres->y += dcph_adres->d2y;
  }
 }
 dcph_adres->asyc += adim;
}

void gudumlu(int cb[], float adim, int uzk)
{ /* verilen koordinatlari, degisken koordinatlara gore ayarlanan */
  /* sabit olmayan bir dogrultuda ilerletir */
  /* Bresenham'in cizgi algoritmasindan uyarlanmistir */

 int u, v, e, f, blok = dcph_adres->tip * 12;

 if(dcph_adres->h1 < uzk)
 { /* ilk hareket namludan ekranin alt ve ust kenarindan uzak olana dogru olsun */
  if(!dcph_adres->h1) dcph_adres->asyc = (abs(dcph_adres->y - ey1) < abs(ey2 - dcph_adres->y + cb[blok + 3])) ? +1 : -1;
  dcph_adres->h1++;
  dcph_adres->x++;
  dcph_adres->y += dcph_adres->asyc;
 }
 else /* ilk hareket tamamlanmissa */
 {
  if(dcph_adres->asyc >= 1)
  {
   dcph_adres->asyc = 0;

   u = (oyuncu.x + 17) - (dcph_adres->x + cb[blok + 2]);
   v = (oyuncu.y + 6) - (dcph_adres->y + cb[blok + 3]);

   dcph_adres->d1x = sgn(u);
   dcph_adres->d1y = sgn(v);

   e = abs(u);
   f = abs(v);

   if (e <= f)
   {
    dcph_adres->d2x = 0;
    dcph_adres->d2y = dcph_adres->d1y;
    dcph_adres->m = f;
    dcph_adres->n = e;
   }
   else
   {
    dcph_adres->d2x = dcph_adres->d1x;
    dcph_adres->d2y = 0;
    dcph_adres->m = e;
    dcph_adres->n = f;
   }

   dcph_adres->s = dcph_adres->m >> 1;

   dcph_adres->s += dcph_adres->n;

   if(dcph_adres->s >= dcph_adres->m)
   {
    dcph_adres->s -= dcph_adres->m;
    dcph_adres->x += dcph_adres->d1x;
    dcph_adres->y += dcph_adres->d1y;
   }
   else
   {
    dcph_adres->x += dcph_adres->d2x;
    dcph_adres->y += dcph_adres->d2y;
   }
  }
  dcph_adres->asyc += adim;
 }
}

void ocph_ani(int cb[], float ch[], unsigned char *kr[])
{ /* oyuncu cephanelerinin animasyonu */
 int blok = ocph_adres->tip * 12, a, i, mx, my, o, k;

 if(!ocph_adres->son_anm) /* son animasyon degilse */
 {
  if(!ocph_adres->krbksyc) /* bekleme sayaci sifirlanmissa */
  {
   ocph_adres->krbksyc = cb[blok + 6]; /* bekleme sayaci max degerini alsin */
   ocph_adres->krsyc++; /* kare sayaci bir sonraki kareyi gostersin */
   if(ocph_adres->krsyc == cb[blok + 5]) ocph_adres->krsyc = 0; /* son kareye ulasmissa ilk kareye don */
  }
  else ocph_adres->krbksyc--; /* bekleme sayacini 1 azalt */

  kare_koy(ocph_adres->x, ocph_adres->y, kr[cb[blok + 4] + ocph_adres->krsyc], SNL);

  ocph_adres->x += ch[ocph_adres->tip * 2];
  ocph_adres->y += ch[ocph_adres->tip * 2 + 1];
 }
 else /* son animasyon ise */
 {
  kare_koy(ocph_adres->x + cb[blok + 10], ocph_adres->y + cb[blok + 11], kr[cb[blok + 7] + ocph_adres->krsyc], SNL);

  if(!ocph_adres->krbksyc) /* bekleme sayaci sifirlanmissa */
  {
   ocph_adres->krsyc++; /* kare sayaci bir sonraki kareyi gostersin */
   ocph_adres->krbksyc = cb[blok + 9]; /* bekleme sayaci max degerini alsin */
   if(ocph_adres->krsyc == cb[blok + 8]) ocph_adres->sil = 1; /* son kareye ulasmissa dugumu sil */
  }
  else ocph_adres->krbksyc--; /* bekleme sayacini 1 azalt */

  /* guc arttirici bonus aktifse beyaz patlama animasyonu icin gerekli degiskenleri hazirla */
  if(oyuncu.guc_syc)
  {
   mx = ocph_adres->x + cb[blok + 2] / 2;
   my = ocph_adres->y + cb[blok + 3] / 2;
   o = max(cb[blok + 2], cb[blok + 3]);

   /* beyaz patlama animasyonu */
   for(k = 1; k <= o; k++)
   {
    a = rand() % 360;
    yeni_nsn_dugum(3,-1, mx + tama(k * cos[a]), my + tama(k * sin[a]));
   }
  }
 }
}

void bns_svy_dsmn_ani(int c[], int d[], dsmn *onceki)
{ /* bonus seviye dusmanlarinin animasyonu */
 int a = 0, b = 0, k, ocph_blok = ocph_adres->tip * 12, dsmn_blok = dsmn_adres->tip * 26;
 int u, v, e, f;

 cph *ocph_sonraki = NULL; /* sonraki oyuncu cephanesi dugumunu gosterir */

 if(dsmn_adres->tip == 17) /* balina */
 {/* yhr burada ilk hareketin bitip bitmediðini belirlemekte kullanildi */
  if(!dsmn_adres->yhr) /* ilk hareket bitmemisse */
  {
   dsmn_adres->ya = 0.3;
   dsmn_adres->y += dsmn_adres->ya;
   /* ilk hareketin bitis noktasina ulasilmissa ilk hareket biter */
   if(dsmn_adres->y > ey1 + dsmn_adres->d2) dsmn_adres->yhr = 1;
  }
  else /* ilk hareket bitmisse */
  { /* yhr ayni zamanda kac bocek birakildigini tutmak icin de kullanildi */
    /* max sayida bocek birakilmissa ekrani terket */
   if(dsmn_adres->yhr > 3) dsmn_adres->ya = -0.3, dsmn_adres->y += dsmn_adres->ya;
   else /* boceklerin hepsi birakilmadiysa */
   {
    if(!dsmn_adres->abksyc && !dsmn_adres->asyc && !(rand() % 3) && dsmn_adres->son_anm < 2)
    { /* bitis animasyonu aktif degilse ve ates ediyorsa 3te 1 olasilikla bocek birakacaktir */
     yeni_dsmn_dugum(18, dsmn_adres->x + 15, dsmn_adres->y + 18, ++svy.dsmn_no);
     dsmn_adres->yhr++;
    }
   }

   /* d1 ekstra degiskeni ekran kenarina sikismayi kontrolde kullanildi */
   if(dsmn_adres->d1 == 0) /* alt veya ust sinirda sikismamissa */
   { /* ekrandaki oyuncu cephanelerini tara */
    if(ocph_birinci != NULL) /* zincir mevcutsa */
    {
     ocph_adres = ocph_birinci; /* sayac saymaya birinci dugumden baslasin */

     a = d[dsmn_blok + 3];
     b = d[dsmn_blok + 3];

     do
     {
      ocph_sonraki = ocph_adres->sonraki;

      if(ocph_adres->y + c[ocph_blok + 3] + 5 >= dsmn_adres->y && ocph_adres->y <= dsmn_adres->y + d[dsmn_blok + 3] && ocph_adres->x + c[ocph_blok + 2] >= dsmn_adres->x - 30)
      { /* bir oyuncu cephanesi 30 piksellik on menzile girmisse */
       k = ocph_adres->y - dsmn_adres->y;
       if(a > k) a = k; /* cephanelerin on cephede ust sinira minimum uzakligi */
       k = dsmn_adres->y + d[dsmn_blok + 3] - (ocph_adres->y + c[ocph_blok + 3]);
       if(b > k) b = k; /* cephanelerin on cephede alt sinira minimum uzakligi */
      }

      ocph_adres = ocph_sonraki; /* sayac sonraki dugumu gostersin */
     } while(ocph_sonraki != NULL);
    }
    /* ekrandaki oyuncu cephanelerinin taranmasi burada bitmistir */

    if(dsmn_adres->yhr < 4) /* balina butun bocekleri birakmadiysa */
    {
     if(a > b) /* ust bosluk buyukse */
     { /* ekranin disina cikmamak sartiyla yukari kac */
      dsmn_adres->ya = -1;
      dsmn_adres->y += dsmn_adres->ya;
      if(dsmn_adres->y < ey1) dsmn_adres->d1 = 50;
     }
     else if(a < b) /* alt bosluk buyukse */
     { /* ekranin disina cikmamak sartiyla asagi kac */
      dsmn_adres->ya = +1;
      dsmn_adres->y += dsmn_adres->ya;
      if(dsmn_adres->y > ey1 + 100) dsmn_adres->d1 = -50;
     }
     else if(a == b) /* bosluklar esitse ilk hareketin hedefi olan seviyeye in */
     {
      if(dsmn_adres->y < ey1 + dsmn_adres->d2) dsmn_adres->ya = 0.5, dsmn_adres->y += dsmn_adres->ya;
      else if(dsmn_adres->y > ey1 + dsmn_adres->d2 + 1) dsmn_adres->ya = -0.5, dsmn_adres->y += dsmn_adres->ya;
     }
    }
   }
   else /* alt veya ust sinirda sikismissa */
   {
    if(dsmn_adres->d1 > 0) /* ust sinirda sikismissa asagi kac */
    {
     dsmn_adres->d1 += -1;
     dsmn_adres->y = ey1 + (50 - dsmn_adres->d1);
     dsmn_adres->ya = +1;
    }
    else /* alt sinirda sikismissa yukari kac */
    {
     dsmn_adres->d1 += +1;
     dsmn_adres->y = ey1 + 100 - (50 + dsmn_adres->d1);
     dsmn_adres->ya = -1;
    }
   }
  }

  /* eninin 2 kati kadar ekrana girene kadar x koordinati -0.5 artsin */
  if(dsmn_adres->x < ex1 + 231)
  { /* eninin 2 kati icerdeyse *//* ysyc, x eksenindeki hareketin bitimini belirlemek icin kullanildi */
   if(!dsmn_adres->ysyc) /* hareket bitmisse */
   {
    a = (int) dsmn_adres->x - (ex1 + 75); /* sola iki oyuncu eni kadar icerden uzaklik */
    b = (ex1 + 231) - (int) (dsmn_adres->x + 44); /* saga iki balina eni kadar icerden uzaklik */

    if(a > b) /* sola uzaklik buyukse */
    {
     dsmn_adres->xa = -0.3;
     dsmn_adres->ysyc = ((20 + rand() % (a - 20)) * 10) / 3; /* menzil belirle */
    }
    else /* saga uzaklik buyukse */
    {
     dsmn_adres->xa = +0.3;
     dsmn_adres->ysyc = ((20 + rand() % (b - 20)) * 10) / 3; /* menzil belirle */
    }
   }
   else dsmn_adres->ysyc--;
  }
  else dsmn_adres->xa = -0.5;

  dsmn_adres->x += dsmn_adres->xa;
 }
 else if(dsmn_adres->tip == 18) /* bocek */
 {
  if(!tplr[1].sayac) dsmn_adres->x--;

  /* ekranin sol kenarinin bocegin sag kenarina uzakligi */
  b = (dsmn_adres->x >= ex1) ? 0 : ex1 - dsmn_adres->x;

  if(!dsmn_adres->yhr) /* dusme hareketi bitmediyse */
  {
   dsmn_adres->y++;
   for(k = b; k < 13; k++) if(ey1 + tplr[1].dizi[dsmn_adres->x - ex1 + k] > dsmn_adres->y + 12) a = 1;
   /* bocegin alt siniri tamamen tepenin ust sinirinin altina indiyse dusme hareketi biter */
   if(!a) dsmn_adres->yhr = 1; else dsmn_adres->y += 0.5;
  }
  else /* bocek yere inmisse */
  { /* ysyc, bocek sola yakin duserse ekranin sagina gectikten sonra */
    /* yavaslamasini saglamak icin kullanildi */
   if(dsmn_adres->x < ex1 + 160 && !dsmn_adres->ysyc)
   { /* ekranin soluna yakinsa ve saga dusmemisse saga hizli hareket etsin */
    dsmn_adres->x += 0.6;
    if(dsmn_adres->x >= ex1 + 160) dsmn_adres->ysyc = 1;
   }
   else dsmn_adres->x += 0.1;

   for(k = b; k < 13; k++) if(ey1 + tplr[1].dizi[dsmn_adres->x - ex1 + k] > dsmn_adres->y + 12) a = 1;
   if(a) dsmn_adres->y++; /* bocegin tabani tepe zeminini ustunde kaliyorsa 1 asagi insin */
   else /* aksi halde */
   {
    a = 0;
    for(k = b; k < 13; k++) if(ey1 + tplr[1].dizi[dsmn_adres->x - ex1 + k] >= dsmn_adres->y + 12) a = 1;
    if(!a) dsmn_adres->y--; /* bocegin tabani tepe zeminini altinda kaliyorsa 1 yukari ciksin */
   }
  }
 }
 else if(dsmn_adres->tip == 19) /* yilan parcasi */
 {
  dsmn_adres->y += 0.5; /* yercekimi etkisi */

  /* ysyc yilan parcasinin hareket etmis olup olmadigini belirlemek icin kullanildi */
  if(onceki->ysyc) /* onceki parca hareket etmisse */
  { /* onceki parcanin tipine gore hareket ve sinir kontrolu */
   if(onceki->tip == 19) /* onceki yilan parcasi ise */
   {
    if(dsmn_adres->y < onceki->y) dsmn_adres->y += 0.5;
    if(dsmn_adres->y > onceki->y) dsmn_adres->y -= 0.5;
    if(dsmn_adres->x < onceki->x) dsmn_adres->x += 0.5;
    if(dsmn_adres->x > onceki->x) dsmn_adres->x -= 0.5;
   }
   else if(onceki->tip == 20) /* onceki yilan basi ise */
   {
    if(dsmn_adres->y < onceki->y + 2) dsmn_adres->y += 0.5;
    if(dsmn_adres->y > onceki->y + 2) dsmn_adres->y -= 0.5;
    if(dsmn_adres->x < onceki->x + 2) dsmn_adres->x += 0.5;
    if(dsmn_adres->x > onceki->x + 2) dsmn_adres->x -= 0.5;
   }
  }

  dsmn_adres->ysyc = 0;
  /* sonraki parcanin tipine gore sinir kontrolu */
  if(onceki->tip == 19) /* onceki yilan parcasi ise */
  {
   while(dsmn_adres->y < onceki->y - 6) dsmn_adres->y += 1, dsmn_adres->ysyc = 1;
   while(dsmn_adres->x < onceki->x - 6) dsmn_adres->x += 1, dsmn_adres->ysyc = 1;
   while(dsmn_adres->y > onceki->y + 6) dsmn_adres->y -= 1, dsmn_adres->ysyc = 1;
   while(dsmn_adres->x > onceki->x + 6) dsmn_adres->x -= 1, dsmn_adres->ysyc = 1;
  }
  else if(onceki->tip == 20) /* onceki yilan basi ise */
  {
   while(dsmn_adres->y < onceki->y - 6) dsmn_adres->y += 1, dsmn_adres->ysyc = 1;
   while(dsmn_adres->x < onceki->x - 6) dsmn_adres->x += 1, dsmn_adres->ysyc = 1;
   while(dsmn_adres->y > onceki->y + 11) dsmn_adres->y -= 1, dsmn_adres->ysyc = 1;
   while(dsmn_adres->x > onceki->x + 11) dsmn_adres->x -= 1, dsmn_adres->ysyc = 1;
  }

  if(dsmn_adres->y > ey2) dsmn_adres->y = ey2; /* asagidan ekranin disina cikmasin */

  if(dsmn_adres->y == ey2 && dsmn_adres->yhr)
  { /* ekranin dibine inmisse ve yilanin basi icin bitis animasyonu aktifse */
    /* sonraki parcayi haberdar et */
   if((dsmn_adres->sonraki)->tip == 19) (dsmn_adres->sonraki)->yhr = 1;
   dsmn_adres->sil = 1; /* parcayi sil */
  }

  /* yilan parcasi dalga seviyesine inmisse sicrayan dalga animasyonu yarat */
  a = rand() % 10;
  b = ey1 + dlglr[4].dizi[dsmn_adres->x - ex1 + a];
  if(b >= dsmn_adres->y && b <= dsmn_adres->y)
  {
   yeni_nsn_dugum(3, -4, dsmn_adres->x + a, b);
   nsn_sonuncu->k = (10 + rand() % 10) / 10;
   nsn_sonuncu->xa = -1;
  }

 }
 else if(dsmn_adres->tip == 20) /* yilan basi */
 {
  dsmn_adres->x += dsmn_adres->xa;
  dsmn_adres->y += dsmn_adres->ya;

  /* d2 ve d3 degiskenleri rasgele hedef korrdinatlarini tutmak icin kullanildi */
  if(dsmn_adres->x >= dsmn_adres->d2 - 3 && dsmn_adres->x <= dsmn_adres->d2 + 3)
  { /* x eksenindeki hedef koordinata vardiysa */
   dsmn_adres->d2 = ex1 + rand() % 306; /* rastgele yeni x menzili belirle */
   /* hedef koordinatin sagda veya solda olmasina gore artis degeri belirle */
   dsmn_adres->xa = (dsmn_adres->d2 < dsmn_adres->x) ? -0.5 : +0.5;
  }

  if(dsmn_adres->y >= dsmn_adres->d3 - 3 && dsmn_adres->y <= dsmn_adres->d3 + 3)
  { /* y eksenindeki hedef koordinata vardiysa */
   dsmn_adres->d3 = ey1 + 50 + rand() % 150; /* rastgele yeni y menzili belirle */
   /* hedef koordinatin ustte veya altta olmasina gore artis degeri belirle */
   dsmn_adres->ya = (dsmn_adres->d3 < dsmn_adres->y) ? -1 : +2;
  }

  if(dsmn_adres->son_anm == 2) /* bitis animasyonu aktif ise */
  {
   dsmn_adres->ya = +1;
   dsmn_adres->xa = 0;
   (dsmn_adres->sonraki)->yhr = 1; /* sonrakini haberdar et */
  }

  if(dsmn_adres->y > ey2) dsmn_adres->y = ey2; /* asagidan ekranin disina cikmasin */
 }
 else if(dsmn_adres->tip == 21) /* koza */
 {
  if(dsmn_adres->y >= ey1 + 196) /* yere inmisse */
  {
   d[545] = 1; /* yilan ekle */
   d[570] = dsmn_adres->x; /* yilan basi icin ilk x koordinati */
   dsmn_adres->sil = 1; /* kozayi sil */
  } /* yere inmemisse insin */
  else dsmn_adres->y += 1, dsmn_adres->xa = 0, dsmn_adres->ya = 1;

  /* dusme efekti */
  b = rand() % 360;
  yeni_nsn_dugum(3,-1, dsmn_adres->x + 5 + cos[b] * 5, dsmn_adres->y + 4 + sin[b] * 5);
 }
}

void dsmn_ani(int d[], float dh[], int dd[], unsigned char *kr[], int cb[], int rstglnsn, dsmn *onceki)
{ /* dusmanlarin animasyonu */
 int a = 0, dsmn_blok = dsmn_adres->tip * 26, hr_blok, ns = d[dsmn_blok + 7], no;

 if(dsmn_adres->tip > 3 || (dsmn_adres->tip < 4 && !dsmn_adres->son_anm))
 { /* bonus ise bitis animasyonu normal animasyonun ustunde olmasin */
  if(!dsmn_adres->krbksyc) /* bekleme sayaci sifirlanmissa */
  {
   dsmn_adres->krbksyc = d[dsmn_blok + 6]; /* bekleme sayaci max degerini alsin */
   dsmn_adres->krsyc++; /* kare sayaci bir sonraki kareyi gostersin */
   if(dsmn_adres->krsyc == d[dsmn_blok + 5]) dsmn_adres->krsyc = 0; /* kare sayaci max degere ulastiysa sifirlansin */
  }
  else dsmn_adres->krbksyc--;

  kare_koy(dsmn_adres->x, dsmn_adres->y, kr[d[dsmn_blok + 4] + dsmn_adres->krsyc], SNL);
 }

 if(dsmn_adres->tip < rstglnsn || (dsmn_adres->tip >= rstglnsn && dsmn_adres->yhr))
 {/* rstglnsn ise aktif oldugunda gerekli islemleri yap degilse farketmez */
  if(!dsmn_adres->abksyc && dsmn_adres->tip > 3) /* ates etme icin bekleme bittiyse ve bonus degilse */
  {
   if(dsmn_adres->asyc < d[dsmn_blok + 9]) /* atis sayisi tamamlanmadiysa */
   {
    if(!dsmn_adres->msyc) /* iki atis arasi bekleme bittiyse */
    {
     dsmn_adres->msyc = d[dsmn_blok + 8];
     while(ns) /* ns (namlu sayisi) sifirsa cephane nesnesi yaratilmaz */
     {
      yeni_dcph_dugum(d[dsmn_blok + 11 + a], dsmn_adres->x + d[dsmn_blok + 12 + a], dsmn_adres->y + d[dsmn_blok + 13 + a], cb);
      ns--, a += 3;
     }
     dsmn_adres->asyc++;
    }
    else dsmn_adres->msyc--;
   }
   else dsmn_adres->asyc = 0, dsmn_adres->abksyc = d[dsmn_blok + 10];
  }
  else dsmn_adres->abksyc--;
 }

 if(dsmn_adres->tip < rstglnsn) /* rastgele nesne degilse */
 {
  if(dsmn_adres->tip) /* tip = 0 degilse */
  {
   if(dsmn_adres->tip > 3 || (dsmn_adres->tip < 4 && !dsmn_adres->son_anm))
   {
    /* bonus nesne degilse veya son animasyonu aktif olmayan bonus nesnesi ise */
    /* bonus ise bitis animasyonunda koordinat degismesin diye boyle bir sart koyuldu */
    dsmn_adres->xa = -dh[dsmn_adres->tip];
    dsmn_adres->x += dsmn_adres->xa;

/* buradan itibaren sirasi gelen dikey hareket islenecek */
    hr_blok = 0, no = 1;

    while(no != dsmn_adres->no) /* arac noya gore dikey hareket satirini bul */
    {
     if(dd[++hr_blok] == -10) no++;
    }

    if(dsmn_adres->yhr <= dd[hr_blok + 1]) /* dikey hareketler bitmediyse */
    {
     if(dsmn_adres->ysyc <= 0) /* islenen dikey hareket bittiyse sonrakine gec */
     {
      dsmn_adres->ysyc = dd[hr_blok + 3 + dsmn_adres->yhr * 2]; /* menzil sayaci yeni degerini alsin */
      dsmn_adres->yhr++; /* hareket sayaci bir sonrakini gostersin */
     }
     else /* islenen dikey hareket bitmediyse */
     {
      a = hr_blok + 2 + (dsmn_adres->yhr - 1) * 2; /* adim hanesini bul */
      if(dd[a]) /* adim sifir degilse */
      {
       dsmn_adres->ya = 2 * (dh[dsmn_adres->tip] / dd[a]); /* adim buyuklugunu hesapla */
       dsmn_adres->ysyc += (dd[a] > 0) ? -dsmn_adres->ya : dsmn_adres->ya; /* menzili azalt */
       dsmn_adres->y += dsmn_adres->ya;
      }
      else /* adim sifirsa */
      {
       dsmn_adres->ysyc--;
       dsmn_adres->ya = 0;
      }
     }
    }
    else dsmn_adres->ya = 0; /* dikey hareketler bittiyse dikey artisi sifirla */
/* dikey hareket isleme burada bitmistir */
   }
  }
  else /* 0. tip yani bns 0 (puan animasyonu) ise */
  { /* msyc menzil sayaci olarak kullanilmistir */
   dsmn_adres->x -= dh[dsmn_adres->tip];
   if(dsmn_adres->msyc)
   {
    dsmn_adres->x += dsmn_adres->xa;
    dsmn_adres->y += dsmn_adres->ya;
    dsmn_adres->msyc--;
   }
  }
 }
 else bns_svy_dsmn_ani(cb, d, onceki); /* bonus seviye nesnesi ise */

 if(dsmn_adres->son_anm) /* patlama efekti */
 {
  if(dsmn_adres->tip == 20) /* yilan basi ise */
  {
   if(dsmn_adres->son_anm == 1) /* kan akma animasyonu */
   {
    yeni_nsn_dugum(4,-4,dsmn_adres->x + 7,dsmn_adres->y + 7);
    nsn_sonuncu->k = 5 + rand() % 5;
    nsn_sonuncu->xa = (rand() % 2) ? -0.1 : +0.1;
   }
   if(dsmn_adres->son_anm == 2) /* kan fiskirma animasyonu */
   {
    if(dsmn_adres->son_syc)
    {
     for(a = 0; a < 5; a++)
     {
      yeni_nsn_dugum(4,-4,dsmn_adres->x + 7,dsmn_adres->y + 7);
      nsn_sonuncu->k = 1 + rand() % 5;
      nsn_sonuncu->xa = (rand() % 2) ? -0.1 * nsn_sonuncu->k : +0.1 * nsn_sonuncu->k;
     }
     dsmn_adres->son_syc--;
    } /* yilan basi dibe inmisse max yilan sayacini 1 azalt ve yilan basini sil */
    else if(dsmn_adres->y >= ey2) { if(d[544]) d[544]--; dsmn_adres->sil = 1; }
   }
  }
  else if(dsmn_adres->tip > 3) /* bonus degilse */
  {
   if(dsmn_adres->son_anm == 2) /* son patlama animasyonu */
   {
    if(dsmn_adres->son_syc)
    {
     if(dsmn_adres->son_syc == 50)
      yeni_nsn_dugum(2, dsmn_adres->no, (int) dsmn_adres->x + d[dsmn_blok + 2] / 2 - 14, (int) dsmn_adres->y + d[dsmn_blok + 3] / 2 - 14);
     if(dsmn_adres->tip != 0 && !(dsmn_adres->son_syc % 2))
      yeni_nsn_dugum(1, -1, dsmn_adres->x + (rand() % d[dsmn_blok + 2]), dsmn_adres->y + (rand() % d[dsmn_blok + 3]));
     dsmn_adres->son_syc--;
    }
    else dsmn_adres->sil = 1;
   }
   else if(dsmn_adres->son_anm == 1) /* yanma animasyonu */
   {
    if(dsmn_adres->tip != 0 && !(dsmn_adres->ilk_syc % 10))
     yeni_nsn_dugum(1, -1, dsmn_adres->x + (rand() % d[dsmn_blok + 2]), dsmn_adres->y + (rand() % d[dsmn_blok + 3]));
    dsmn_adres->ilk_syc--;
    if(!dsmn_adres->ilk_syc) dsmn_adres->ilk_syc = 1000;
   }
  }
  else if(dsmn_adres->tip < 4) /* bonus ise */
  {
   if(d[dsmn_blok + 12]) /* kare sayisi > 0 ise */
   {
    kare_koy(dsmn_adres->x, dsmn_adres->y, kr[d[dsmn_blok + 11] + dsmn_adres->krsyc], SNL);

    if(!dsmn_adres->krbksyc)
    {
     dsmn_adres->krsyc++;
     dsmn_adres->krbksyc = d[dsmn_blok + 13];
     if(dsmn_adres->krsyc == d[dsmn_blok + 12]) dsmn_adres->sil = 1;
    }
    else dsmn_adres->krbksyc--;
   }
   else dsmn_adres->sil = 1;
  }
 }

 if(dsmn_adres->sil && !dsmn_adres->crplrk && d[dsmn_blok + 0]) /* para animasyonu */
 { /* dsmn dugumu oyuncu tarafindan carpilarak yokedilmemisse ve pr = 1 ise */
  no = d[dsmn_blok + 1] / 5;
  while(no) /* gereken miktarda para nesnesi yarat */
  {
   yeni_dsmn_dugum(0,dsmn_adres->x + d[dsmn_blok + 2] / 2,dsmn_adres->y + d[dsmn_blok + 3] / 2,0);
   a = rand() % 360; /* yayilma yonunu belirle */
   dsmn_sonuncu->xa = cos[a] / 10;
   dsmn_sonuncu->ya = sin[a] / 10;
   dsmn_sonuncu->msyc = 50 + rand() % 100; /* yayilma menzili */
   no--;
  }
 }
}

void dcph_ani(int cb[], float ch[], unsigned char *kr[])
{ /* dusman cephanelerinin animasyonu */
 int blok = dcph_adres->tip * 12;

 if(!dcph_adres->son_anm) /* bitis animasyonu aktif degilse */
 {
  if(!dcph_adres->krbksyc) /* bekleme sayaci sifirlanmissa */
  {
   dcph_adres->krbksyc = cb[blok + 6]; /* bekleme sayaci max degerini alsin */
   dcph_adres->krsyc++; /* kare sayaci bir sonraki kareyi gostersin */
   if(dcph_adres->krsyc == cb[blok + 5]) dcph_adres->krsyc = 0; /* kare sayaci max degere ulastiysa sifirlansin */
  }
  else dcph_adres->krbksyc--;

  kare_koy(dcph_adres->x, dcph_adres->y, kr[cb[blok + 4] + dcph_adres->krsyc], SNL);

  if(!cb[blok + 0]) /* hareket tipi 0 yani sabit hareket ise */
  {
   dcph_adres->x += ch[dcph_adres->tip * 2];
   dcph_adres->y += ch[dcph_adres->tip * 2 + 1];
  }
  else /* hareket tipi sabitten baska bir seyse */
  {
   switch(cb[blok + 0])
   {
    case 1: hedefli(ch[dcph_adres->tip * 2]); break;
    case 2: gudumlu(cb, ch[dcph_adres->tip * 2], 20); break;
   }
  }
 }
 else /* bitis animasyonu aktifse */
 {
  kare_koy(dcph_adres->x + cb[blok + 10], dcph_adres->y + cb[blok + 11], kr[cb[blok + 7] + dcph_adres->krsyc], SNL);

  if(!dcph_adres->krbksyc) /* bekleme sayaci sifirlanmissa */
  {
   dcph_adres->krbksyc = cb[blok + 9]; /* bekleme sayaci max degerini alsin */
   dcph_adres->krsyc++; /* kare sayaci bir sonraki kareyi gostersin */
   if(dcph_adres->krsyc == cb[blok + 8]) dcph_adres->sil = 1; /* kare sayaci max degere ulastiysa cephaneyi sil */
  }
  else dcph_adres->krbksyc--;
 }
}

void nsn_ani(int nsn_dizi[], unsigned char *kr[])
{ /* nesne animasyonu */
 float artma;
 int blok = nsn_adres->tip * 6;

 if(!nsn_adres->tip) /* puan anm ise */
 { /* krsyc bir cesit menzil sayaci gibi kullanilmistir */
  artma = nsn_adres->krsyc / 5;
  /* krbksyc puan tutmak icin kullanilmistir */
  sayi_yaz(nsn_adres->x + artma, nsn_adres->y - artma, nsn_adres->krbksyc, rakam, SNL);
  nsn_adres->krsyc++;
  if(nsn_adres->krsyc == nsn_dizi[blok + 4]) nsn_adres->sil = 1;
 }
 else /* puan animasyonundan farkliysa */
 {
  kare_koy(nsn_adres->x, nsn_adres->y, kr[nsn_dizi[blok + 3] + nsn_adres->krsyc], SNL);

  if(!nsn_adres->krbksyc) /* bekleme sayaci sifirlanmissa */
  {
   nsn_adres->krsyc++; /* kare sayaci bir sonraki kareyi gostersin */
   nsn_adres->krbksyc = nsn_dizi[blok + 5]; /* bekleme sayaci max degerini alsin */
   if(nsn_adres->krsyc == nsn_dizi[blok + 4]) /* kare sayaci max degere ulastiysa */
   { /* yineli ise kare sayacini sifirla aksi halde sil */
    if(nsn_dizi[blok + 0]) nsn_adres->krsyc = 0; else nsn_adres->sil = 1;
   }
  }
  else nsn_adres->krbksyc--;
 }
}

void b1sc_ani(int cph_blg[], unsigned char *kr[])
{ /* bolum sonu canavari animasyonu */
/* bsc icin hareket dizileri (hareket suresi/hizin x bileseni/hizin y bileseni) */
 int dt[18] = {100,100,100,100,100,100,100,100,100,200,150,100, 50,200,150,250,300,300};
 int vx[18] = {  0, +4, +2, -2, -4,  0,  0, +4, +2, -3, -2, -2, -2,  0, +3, +5, +4, +5};
 int vy[18] = { -5, -5, -5, +5, +5, +5, +5, +5, +5, -3, -3, -9, +2, +3, +4,  0, -6, -4};

 if(bsc.son_anm < 2) /* bitis animasyonu aktif degilse */
 {
  if(!bsc.ih) /* ilk hareket bittiyse */
  {
   if(bsc.tsyc == dt[bsc.hsyc]) /* islenen hareketin zaman sayaci o hareketin suresine esitlendiyse */
   {
    if(bsc.hsyc == 18) /* son hareket de islendiyse */
    {
     if(bsc.tsyc) /* zaman sayaci sifirlanmamissa */
     {
      bsc.x = ex1 + 243; /* x ve y degerlerini */
      bsc.y = ey1 + 12;  /* son haline getir */
      bsc.tsyc = 0; /* zaman sayacini sifirla */
     }
     if(bsc.x > ex1 + 150) bsc.x -= 0.25; /* x ve y degerlerini */
     if(bsc.y < ey1 + 75) bsc.y += 0.20;  /* ilk haline yaklastir */
     if(bsc.x <= ex1 + 150 && bsc.y >= ey1 + 75) /* ilk koordinatlara ulasilmissa */
     {
      bsc.hsyc = 0; /* hareket sayaci ilk hareketi gostersin */
      bsc.x = ex1 + 150; /* x ve y degerlerini */
      bsc.y = ey1 + 75;  /* ilk haline getir */
     }
    }
    else /* daha son harekete gelinmediyse */
    {
     bsc.tsyc = 0; /* zaman sayacini sifirla */
     bsc.hsyc++; /* hareket sayaci bir sonraki hareketi gostersin */
    }
   }
   else bsc.tsyc++;

   if(bsc.hsyc < 18) /* son harekete kadar birim hareket miktarlari asagidaki gibi hesaplanacak */
   {
    bsc.x += (vx[bsc.hsyc]) ? (float) 1 / vx[bsc.hsyc] : 0;
    bsc.y += (vy[bsc.hsyc]) ? (float) 1 / vy[bsc.hsyc] : 0;
   }
  } /* ilk hareket bitmediyse tamamla */
  else { bsc.x -= 0.3; if(bsc.x <= ex1 + 150) { bsc.x = ex1 + 150;  bsc.ih = 0; } }

  /* hareket araliklarina gore degisik cephane nesneleri olustur */
  if(bsc.hsyc >= 0 && bsc.hsyc <= 8)
  {
   if(!bsc.asyc)
   {
    bsc.asyc = 40;

    yeni_dcph_dugum(10, bsc.x + 38, bsc.y + 15, cph_blg);
    yeni_dcph_dugum(10, bsc.x + 40, bsc.y + 21, cph_blg);
    yeni_dcph_dugum(10, bsc.x + 40, bsc.y + 27, cph_blg);
    yeni_dcph_dugum(10, bsc.x + 38, bsc.y + 33, cph_blg);
   }
   else bsc.asyc--;
  }
  if(bsc.hsyc >= 9 && bsc.hsyc <= 11)
  {
   if(!bsc.asyc)
   {
    bsc.asyc = 50;

    yeni_dcph_dugum(17, bsc.x + 8, bsc.y - 2, cph_blg);

    yeni_dcph_dugum(22, bsc.x + 18, bsc.y + 40, cph_blg);
   }
   else bsc.asyc--;
  }
  if(bsc.hsyc >= 12 && bsc.hsyc <= 15)
  {
   if(!bsc.asyc)
   {
    bsc.asyc = 15;

    yeni_dcph_dugum(19, bsc.x + 8, bsc.y - 2, cph_blg);
    yeni_dcph_dugum(19, bsc.x + 8, bsc.y + 5, cph_blg);
    yeni_dcph_dugum(19, bsc.x + 10, bsc.y + 10, cph_blg);
    yeni_dcph_dugum(19, bsc.x + 13, bsc.y + 14, cph_blg);
   }
   else bsc.asyc--;
  }
  if(bsc.hsyc >= 16)
  {
   if(!bsc.asyc)
   {
    bsc.asyc = 50;

    yeni_dcph_dugum(17, bsc.x + 8, bsc.y - 2, cph_blg);

    yeni_dcph_dugum(22, bsc.x + 18, bsc.y + 40, cph_blg);
   }
   else bsc.asyc--;
  }
 }

 /* bsc mevcutsa ve seviye sona ermediyse ve son sayac sifirlanmadiysa ve son animasyon aktif degilse */
 if(svy.bsck && svy.bitti && !svy.son_syc && bsc.son_anm < 2)
  if(oyuncu.x + 32 >= bsc.x + 25 && oyuncu.x <= bsc.x + 61 && oyuncu.y + 9 >= bsc.y + 21 && oyuncu.y <= bsc.y + 46)
  { /* oyuncuyla kesisme durumu kontrolu */
   bsc.hasar += oyuncu.hasar;
   oyuncu.hasar = oyuncu.maxhsr;
   oyuncu.son_anm = 1;
  }

 if(bsc.hasar > 10000) bsc.son_anm = 1;
 if(bsc.hasar > 15000) bsc.son_anm = 2;

 if(bsc.son_anm == 2) /* son patlama animasyonu aktifse */
 {
  if(bsc.son_syc) /* animasyon bitmediyse */
  {
   bsc.son_syc--;
   if(bsc.son_syc <= 200 && !(bsc.son_syc % 20))
    yeni_nsn_dugum(2, -1, bsc.x + 15 + (rand() % 45) - 15, bsc.y + 15 + (rand() % 35) - 15);
   if(!(bsc.son_syc % 5))
    yeni_nsn_dugum(2, -1, bsc.x + 15 + (rand() % 45) - 15, bsc.y + 15 + (rand() % 35) - 15);
   if(!(bsc.son_syc % 2))
    yeni_nsn_dugum(1, -1, bsc.x + 15 + (rand() % 45) - 3, bsc.y + 15 + (rand() % 35) - 3);
  }
  else svy.bsck = 0; /* animasyon bittiyse bsc yokedilsin */
 }
 else if(bsc.son_anm == 1) /* yanma animasyonu aktifse */
 {
  if(!(bsc.ilk_syc % 10))
   yeni_nsn_dugum(1, -1, bsc.x + 15 + (rand() % 45) - 3, bsc.y + 15 + (rand() % 35) - 3);
  bsc.ilk_syc--;
  if(!dsmn_adres->ilk_syc) bsc.ilk_syc = 1000;
 }

 /* bolum sonu canavari mevcutsa resim karesini ekrana bas */
 if(svy.bsck) kare_koy(bsc.x, bsc.y, kr[114], SNL);
}