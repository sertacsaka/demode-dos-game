void nesne_ekle(int bklm[], int nsns[], int tkr, int lmt)
{ /* zamaný gelince yeni dusman nesnesi dugumlerini ekler */
 int o, p;

 if(!svy.sayac) /* dusman dalgalari arasindaki beklemeyi sayan sayac sifirlanmissa */
 { /* bekleme dizisinin sonuna ulasilmamissa bekleme sayaci yeni degerini alsin */
   /* ve dusman dalgalarini sayan sayac bir sonraki dalgayi gostersin */
  if(bklm[svy.syc] != -2) svy.sayac = bklm[svy.syc++];

  if(nsns[svy.ind] != -2) /* eklenecek nesneleri tutan dizinin sonuna gelinmemisse */
  {
   svy.ind++; /* nesne sayaci yeni nesneyi gostersin */
   while(nsns[svy.ind] != -1 && nsns[svy.ind] != -2)
   { /* sayac dalga satirinin basini ya da dizi sonunu gostermiyorsa */
    o = svy.ind; /* eklenecek nesnenin tipi */
    p = o + 1; /* ve ilk y degeri belirlensin */
    yeni_dsmn_dugum(nsns[o], 640, nsns[p], ++svy.dsmn_no); /* nesne eklensin */
    svy.ind = p + 1; /* sayac bir sonraki dalga satirinin basini gostersin */
   }
  }
  else /* nesne dizisinin sonuna gelinmisse */
  {
   if(!tkr) svy.bitti = 1; /* eger tekrarli bir seviye degilse seviyeyi bitir */
   /* aksi halde sure limiti asilmamissa seviye degiskenlerini sifirla limit asilmissa seviyeyi bitir */
   else { if(svy.tkr_syc < lmt) svy.syc = 0, svy.ind = 0; else svy.bitti = 1; }
  }
 }
 else { svy.sayac--; svy.tkr_syc++; }
}

int kare_parca(int x, int y, unsigned char *kare, int k, int kareler, int enk, int kln[], unsigned char *kr)
{ /* karekare_olustur fonksiyonu icin verilen resim karesinden istenen buyuklukte */
  /* rastgele yerlesimli bir kare belirleyip ekrana basar */
 int o, p, r, a, b, i, j, m, n;

 kronometre = 0;

 if(!kln[0]) return 1; /* acilacak kare kalmadiysa cik */

 o = rand() % kln[0]; /* acilacak kareyi belirle (acilmamis kareler icindeki sira numarasi) */

 p = 0;

 while(p < kareler) /* butun kareleri bastan sona tara */
 {
  if(!kr[p]) /* siradaki kare acilmamissa */
  {
   if(!o) /* acilacak karenin sira numarasina ulasilmissa */
   {
    kr[p] = 1; /* karenin acildigini ustune yaz */
    kln[0]--; /* acilmayan kare sayisini 1 azalt */
    i = (p % enk) * k; /* acilacak karenin sutun */
    j = (p / enk) * k; /* ve satirini bul */
    /* kareyi ana resim alaninin disina cikmayacak sekilde ekrana bas */
    for(a = 0; a < k; a++)
    {
     m = i + a;
     if(m < kare[0])
     {
      for(b = 0; b < k; b++)
      {
       n = j + b;
       if(n < kare[1])
       {
        r = 2 + m + n * kare[0];
        if(kare[r] != SAYDAM) SNL[(x + m) + (y + n) * 320] = kare[r];
       }
      }
     }
    }
    break; /* karenin ekrana basilmasi bittiginde cik */
   }
   o--; /* acilacak kareye ulasilmamissa */
  }
  p++; /* acilmamis kareleri taramaya devam et */
 }

 memcpy(VGA, SNL, 64000);
 while(kronometre < 10);

 return 0;
}

int karekare_olustur(int x, int y, unsigned char *kare, int k)
{ /* kare_parca fonksiyonunu acilacak kare kalmayincaya kadar isletir */
 int enk = kare[0] / k + 1;
 /* istenen boyuttaki kucuk karelerin verilen resim alanini dolduracak maksimum sayisi */
 int kareler = enk * (kare[1] / k + 1);
 int kln[1], o = 0;
 unsigned char *kr = (unsigned char *) calloc(kareler, 1);

 kln[0] = kareler;

 T.Esc = 0;
 T.Enter = 0;

 while(!T.Esc && !T.Enter && !o) o = kare_parca(x, y, kare, k, kareler, enk, kln, kr);

 free(kr);

 if(kln[0]) return 1; else return 0; /* butun karelerin acilip acilmadigini bildir */
}

void aciklama(int x, int y, char *adres, int x1, int y1, int x2, int y2, int bekleme)
{ /* seviye oncesi aciklama ekrani */
 int o;

 unsigned char *kare = (unsigned char *) calloc((x2 - x1 + 1) * (y2 - y1 + 1) + 2 , 1);

 XCPyi_bellege_oku(adres, RGB, SNL);

 kare_oku(x1,y1,x2,y2,SNL,kare);

 memset(SNL, 0, 64000);

 kronometre = 0;
 o = karekare_olustur(x, y, kare, 5);
 T.Esc = 0;
 T.Enter = 0;
 while(!o && !T.Esc && !T.Enter && kronometre < bekleme);

 free(kare);
}

void yan_son(int x, int y, int o[], int son, int yan, unsigned char *kare)
{ /* verilen resim karesini ekrana belli zaman araliginda belli sure basar */
 if(o[0] == son)
  { if(o[1] == yan) o[0] = 0, o[1] = 0; else { o[1]++; hzl_kare_koy(x, y, kare, SNL); } }
 else o[0]++;
}

void panel(void) /* oyun ekranindaki puan ve hasar gostergesi */
{
 float oran;
 int x, y, hasar;

 oran = (float) oyuncu.hasar / oyuncu.maxhsr;
 hasar = 310 - (float) 310 * oran;

 for(x = 9; x < hasar; x += 2)
  for(y = 5; y < 8; y++)
   SNL[x + y * 320] = 100;

 hzl_kare_koy(302, 186, pnl[1], SNL);
 sayi_yaz(ex1 + 319, ey1 + 197, oyuncu.puan, rakam, SNL);
}

int puanlama(int bns) /* seviye sonundaki puanlama ekrani */
{
 int o[] = {0,0},
     syc = 0,
     esc = 0,
     tisyc = 100,
     enter = 0,
     kacan = 0,
     iska = 0, 
     puan = oyuncu.puan,
     puansyc = 0,
     son_puan = oyuncu.son_puan,
     sayac[7] = {0,0,0,0,0,0,0},
     czg1[110],
     czg2[110],
     czg3[110],
     czg4[110],
     czg5[110],
     czg6[110];
 float ti = 0;

 while(1)
 {
  kronometre = 0;

  memset(SNL, 0, 64000);

  if(T.Enter) enter = 1;

  if(T.Esc) { esc = 1; break; }

  if(!enter)
  {
   if(syc > 100)
   {
    hzl_kare_koy(103, 40, pnl[4], SNL);
    hzl_kare_koy(130, 42, pnl[1], SNL);
    sayi_yaz(ex1 + 218, ey1 + 45, oyuncu.son_puan, rakam, SNL);
   }
   if(!bns)
   {
    if(syc > 150)
    {
     hzl_kare_koy(103, 60, pnl[0], SNL);
     sayi_yaz(ex1 + 218, ey1 + 65, kacan, rakam, SNL);
    }
    if(syc > 200)
    {
     hzl_kare_koy(103, 80, pnl[2], SNL);
     sayi_yaz(ex1 + 218, ey1 + 84, iska, rakam, SNL);
    }
   }
   if(syc > 250)
   {
    hzl_kare_koy(103, 100, pnl[1], SNL);
    sayi_yaz(ex1 + 218, ey1 + 103, puan, rakam, SNL);
   }
   if(syc > 300)
   {
    if(!bns)
    {
     if(kacan < oyuncu.kacan) { kacan++; puan -= 1; }
     if(iska < oyuncu.iska) { tisyc = 100; while(tisyc && iska < oyuncu.iska) { ti += 0.1; if(ti >= 1) { ti = 0; puan--; }; iska++; tisyc--; } }
    }
    if((!bns && kacan >= oyuncu.kacan && iska >= oyuncu.iska) || bns)
    {
     hzl_kare_koy(103, 120, pnl[5], SNL);
     hzl_kare_koy(120, 120, pnl[1], SNL);
     if(puansyc < abs(puan)) { tisyc = 10; while(tisyc && puansyc < abs(puan)) { son_puan += (puan > 0) ? +1 : -1; puansyc++; tisyc--; } }
     sayi_yaz(ex1 + 218, ey1 + 123, son_puan, rakam, SNL);
    }
   }
   if(syc > 350)
   {
    if(!oyuncu.son_syc) { esc = 1; yan_son(103, 150, o, 50, 50, pnl[3]); }
    else yan_son(103, 150, o, 50, 50, pnl[3]);
   }
   syc++;
  }
  else /* entera basilmissa direkt hesapla */
  {
   if(!bns) oyuncu.puan -= oyuncu.kacan * 1 + oyuncu.iska * 0.1;

   hzl_kare_koy(103, 40, pnl[4], SNL);
   hzl_kare_koy(130, 42, pnl[1], SNL);
   sayi_yaz(ex1 + 218, ey1 + 45, oyuncu.son_puan, rakam, SNL);
   if(!bns)
   {
    hzl_kare_koy(103, 60, pnl[0], SNL);
    sayi_yaz(ex1 + 218, ey1 + 65, oyuncu.kacan, rakam, SNL);
    hzl_kare_koy(103, 80, pnl[2], SNL);
    sayi_yaz(ex1 + 218, ey1 + 84, oyuncu.iska, rakam, SNL);
   }
   hzl_kare_koy(103, 100, pnl[1], SNL);
   sayi_yaz(ex1 + 218, ey1 + 103, oyuncu.puan, rakam, SNL);
   hzl_kare_koy(103, 120, pnl[5], SNL);
   hzl_kare_koy(120, 120, pnl[1], SNL);
   sayi_yaz(ex1 + 218, ey1 + 123, oyuncu.son_puan + puan, rakam, SNL);

   while(kronometre < 250);
  }

/* kayan nokta animasyonu baslangici */
  for(sayac[0] = 0; sayac[0] < 110; sayac[0]++)
  {
   czg1[sayac[0]] = 0;
   czg2[sayac[0]] = 0;
   czg3[sayac[0]] = 0;
   czg4[sayac[0]] = 0;
   czg5[sayac[0]] = 0;
   czg6[sayac[0]] = 0;
  }

  if(sayac[1] == 22) sayac[2] = 0;
  if(sayac[1] == 44) sayac[3] = 0;
  if(sayac[1] == 66) sayac[4] = 0;
  if(sayac[1] == 88) sayac[5] = 0;
  if(sayac[1] == 110) { sayac[6] = 0; sayac[1] = 0; }

  czg1[sayac[1]] = 32 + (sayac[1] % 33);
  czg2[sayac[2]] = 32 + (sayac[2] % 33);
  czg3[sayac[3]] = 32 + (sayac[3] % 33);
  czg4[sayac[4]] = 32 + (sayac[4] % 33);
  czg5[sayac[5]] = 32 + (sayac[5] % 33);
  czg6[sayac[6]] = 32 + (sayac[6] % 33);

  for(sayac[0] = 0; sayac[0] < 110; sayac[0]++)
  {
   SNL[100 + (sayac[0] + 30) * 320] = czg1[sayac[0]];
   SNL[100 + sayac[0] + 50 * 320] = czg2[sayac[0]];
   if(!bns)
   {
    SNL[100 + sayac[0] + 70 * 320] = czg3[sayac[0]];
    SNL[100 + sayac[0] + 90 * 320] = czg4[sayac[0]];
   }
   SNL[100 + sayac[0] + 110 * 320] = czg5[sayac[0]];
   SNL[100 + sayac[0] + 130 * 320] = czg6[sayac[0]];
  }

  sayac[1]++;
  sayac[2]++;
  sayac[3]++;
  sayac[4]++;
  sayac[5]++;
  sayac[6]++;
/* kayan nokta animasyonu bitisi */

  memcpy(VGA, SNL, 64000);

  if(enter) break;

  while(kronometre < 10);
 }

 oyuncu.son_puan += puan;

 return !esc;
}

void oyuncu_hareket() /* oyuncunun kontrol ettigi ucagin animasyonu */
{
 int o, r, a, xa = 0, ya = 0, i = 0;
 /* i degiskeni guc_syc > 0 iken sinirlarda konum sabitlemek icin kullanildi */
 /* konum sabitlemesi yapilmadiginda guc arttirici bonus animasyonu sinirlarda kayma yapiyor */

 /* oyuncu hasar maksimum hasari asamaz */
 if(oyuncu.hasar >= oyuncu.maxhsr) oyuncu.hasar = oyuncu.maxhsr;

 if(oyuncu.son_syc) /* oyuncu yokolmadigi surece hareketini isle */
 {
  oyuncu.ilr = T.ilr,
  oyuncu.gri = T.gri,
  oyuncu.sag = T.sag,
  oyuncu.sol = T.sol,
  oyuncu.ats = T.Ctrl;

  if(oyuncu.ilr) oyuncu.y--, ya = -1;
  else if(oyuncu.gri) oyuncu.y++, ya = +1;
  if(oyuncu.sag) oyuncu.x++, xa = +1;
  else if(oyuncu.sol && oyuncu.i) oyuncu.x--, xa = -1;

  if(!oyuncu.i) oyuncu.i = 1; else oyuncu.i = 0;

  if(svy.tamam) oyuncu.x += 2; /* seviye biterse ucak ekrani terk eder */
  else
  if(oyuncu.x + 32 > ex2) oyuncu.x = ex2 - 32, xa = 0;
  if(oyuncu.x < ex1 + 0) oyuncu.x = ex1 + 0, xa = 0;
  if(oyuncu.y < ey1 + 0) oyuncu.y = ey1 + 0, ya = 0, i = 1;
  /* zemin animasyonu yoksa ucak ekranin alt sinirini gecemesin */
  if(!svy.zemin) { if(oyuncu.y + 10 > ey2) oyuncu.y = ey2 - 10, ya = 0, i = 1; }
  else if(oyuncu.x + 32 <= ex2) /* zemin animasyonu varsa ve ucak ekrani terk etmemisse */
  {
   if(svy.zemin == 1) /* zemin tepeler ise */
    for(o = oyuncu.x; o <= oyuncu.x + 31; o++)
    {
     if(oyuncu.y + 8 >= ey1 + tplr[0].dizi[o - ex1])
     { /* zeminle kesisme durumu */
      oyuncu.y -= 5; oyuncu.hasar += 10;
      yeni_nsn_dugum(1, -1, o, oyuncu.y + 8);
      if(oyuncu.hasar >= oyuncu.maxhsr) oyuncu.son_anm = 1;
     }
    }
   else
   if(svy.zemin == 2) /* zemin dalgalar ise */
    for(o = oyuncu.x; o <= oyuncu.x + 31; o++)
    {
     if(oyuncu.y + 6 >= ey1 + dlglr[4].dizi[o - ex1])
     { /* zeminle kesisme durumu */
      oyuncu.y--; oyuncu.hasar++;
      for(r = 0; r < 10; r++)
      {
       yeni_nsn_dugum(3, -4, o, oyuncu.y + 6);
       nsn_sonuncu->k = 1 + rand() % 10;
       nsn_sonuncu->xa = -1;
      }
      if(oyuncu.hasar >= oyuncu.maxhsr) oyuncu.son_anm = 1;
     }
    }
  }

  oyuncu.xa = xa, oyuncu.ya = ya; /* ilgili nesneler icin gerekli artma miktarlari */

  if(!oyuncu.son_anm) /* son patlama efekti aktif degilse */
  {
   if(oyuncu.ats) /* ates tusu basiliysa */
   {
    if(!oyuncu.a1) /* mermi icin ates bekleme sayaci sifirlanmissa */
    {
     yeni_ocph_dugum(0, oyuncu.x + 32, oyuncu.y + 6);
     if(oyuncu.asvy > 2)
      yeni_ocph_dugum(1, oyuncu.x + 22, oyuncu.y + 6),
      yeni_ocph_dugum(2, oyuncu.x + 22, oyuncu.y + 6);
     if(oyuncu.asvy > 4)
      yeni_ocph_dugum(3, oyuncu.x + 22, oyuncu.y + 6),
      yeni_ocph_dugum(4, oyuncu.x + 22, oyuncu.y + 6);
     oyuncu.a1 = 5;
    }
    else oyuncu.a1--;
    if(!oyuncu.a2) /* roket icin ates bekleme sayaci sifirlanmissa */
    {
     if(oyuncu.asvy > 1) yeni_ocph_dugum(5, oyuncu.x + 23, oyuncu.y + 8);
     if(oyuncu.asvy > 3)
      yeni_ocph_dugum(6, oyuncu.x + 23, oyuncu.y + 8),
      yeni_ocph_dugum(7, oyuncu.x + 23, oyuncu.y + 8);
     if(oyuncu.asvy > 5)
      yeni_ocph_dugum(8, oyuncu.x + 23, oyuncu.y + 8),
      yeni_ocph_dugum(9, oyuncu.x + 23, oyuncu.y + 8);
     oyuncu.a2 = 30;
    }
    else oyuncu.a2--;
   }
  }

  /* ucak hareketine gore yana yatma animasyonu sayaci */
  if(oyuncu.ilr) { if(oyuncu.s > 1) oyuncu.s--; }
  else if(oyuncu.gri) { if(oyuncu.s < 40) oyuncu.s++; }
  /* yatma pozisyonunda kalacak bir hareket yaptirilmiyorsa normal haline dogru duzelsin */
  else { if(oyuncu.s < 20) oyuncu.s++; else if(oyuncu.s > 20) oyuncu.s--; }

  /* guc arttirici bonus animasyonu icin gerekli degiskenler */
  if(oyuncu.guc_syc) { r = rand() % 3; a = rand() % 360; }

  /* dogru yatma acisindaki sirasi gelen ucak karesini ekrana bas */
  /* ve aktifse uzerine guc arttirici bonusun animasyonunu da ekle */
  if(oyuncu.s == 1)
  {
   kare_koy(oyuncu.x, oyuncu.y, oyuncu.kare[oyuncu_krdz[oyuncu.krsyc++]], SNL);
   if(oyuncu.guc_syc) yeni_nsn_dugum(3, -3, oyuncu.x + 12 + tama(r * cos[a]), oyuncu.y + 10 - i + tama(r * sin [a])),
                      yeni_nsn_dugum(3, -3, oyuncu.x + 12 + tama(r * cos[a]), oyuncu.y +  0 - i + tama(r * sin [a]));
  }
  else if(oyuncu.s > 1 && oyuncu.s < 18)
  {
   kare_koy(oyuncu.x, oyuncu.y, oyuncu.kare[4 + oyuncu_krdz[oyuncu.krsyc++]], SNL);
   if(oyuncu.guc_syc) yeni_nsn_dugum(3, -3, oyuncu.x + 12 + tama(r * cos[a]), oyuncu.y + 7 + tama(r * sin [a])),
                      yeni_nsn_dugum(3, -3, oyuncu.x + 12 + tama(r * cos[a]), oyuncu.y + 1 + tama(r * sin [a]));
  }
  else if(oyuncu.s > 17 && oyuncu.s < 23)
  {
   kare_koy(oyuncu.x, oyuncu.y, oyuncu.kare[8 + oyuncu_krdz[oyuncu.krsyc++]], SNL);
   if(oyuncu.guc_syc) yeni_nsn_dugum(3, -3, oyuncu.x + 12 + tama(r * cos[a]), oyuncu.y + 5 + tama(r * sin [a]));
  }
  else if(oyuncu.s > 22 && oyuncu.s < 39)
  {
   kare_koy(oyuncu.x, oyuncu.y, oyuncu.kare[12 + oyuncu_krdz[oyuncu.krsyc++]], SNL);
   if(oyuncu.guc_syc) yeni_nsn_dugum(3, -3, oyuncu.x + 12 + tama(r * cos[a]), oyuncu.y + 2 + tama(r * sin [a])),
                      yeni_nsn_dugum(3, -3, oyuncu.x + 12 + tama(r * cos[a]), oyuncu.y + 7 + tama(r * sin [a]));
  }
  else
  {
   kare_koy(oyuncu.x, oyuncu.y, oyuncu.kare[16 + oyuncu_krdz[oyuncu.krsyc++]], SNL);
   if(oyuncu.guc_syc) yeni_nsn_dugum(3, -3, oyuncu.x + 12 + tama(r * cos[a]), oyuncu.y - 2 + i + tama(r * sin [a])),
                      yeni_nsn_dugum(3, -3, oyuncu.x + 12 + tama(r * cos[a]), oyuncu.y + 8 + i + tama(r * sin [a]));
  }

  if(oyuncu.krsyc == 20) oyuncu.krsyc = 0; /* kare sayaci max degerine ulastiginda sifirlansin */

  if(oyuncu.hasar >= oyuncu.maxhsr / 2 && oyuncu.i) /* yanma efekti */
   yeni_nsn_dugum(1, -2, oyuncu.x + (rand() % 16), oyuncu.y + (rand() % 8));

  /* bitis animasyonu aktif ise kalkan ve guc arttirici bonus animasyonlarini pasif hale getir */
  if(oyuncu.son_anm) oyuncu.tnr_syc = 0, oyuncu.guc_syc = 0;
 }

 if(oyuncu.tnr_syc) /* eger aktifse kalkan animasyonunu gerceklestir */
 {
  oyuncu.tnr_syc--; /* kalkan bonusunun pasiflestirilmesi icin geri sayim */
  r = 20 + rand() % 2;
  a = rand() % 360;
  yeni_nsn_dugum(3, 0, oyuncu.x + 16 + tama(r * cos[a]), oyuncu.y + 4 + tama(r * sin [a]));
 }
 if(oyuncu.guc_syc) /* guc arttirici bonusun pasiflestirilmesi icin geri sayim */
 {
  oyuncu.guc_syc--;
  oyuncu.guc = 2;
 }
 else oyuncu.guc = 1;

 if(oyuncu.son_anm) /* son patlama efekti */
 {
  if(oyuncu.son_syc)
  {
   oyuncu.son_syc--;
   if(oyuncu.son_syc <= 200 && !(oyuncu.son_syc % 20))
    yeni_nsn_dugum(2,  0, oyuncu.x - 16 + rand() % 32, oyuncu.y - 15 + rand() % 10);
   if(!(oyuncu.son_syc % 5))
    yeni_nsn_dugum(2, -2, oyuncu.x - 16 + rand() % 32, oyuncu.y - 15 + rand() % 10);
   if(!(oyuncu.son_syc % 2))
    yeni_nsn_dugum(1, -2, oyuncu.x - 3 + rand() % 32, oyuncu.y - 3 + rand() % 10);
  }
  else oyuncu.xa = 0, oyuncu.ya = 0;
 }
}

void seviye_ilk_degerler(void)
{ /* her seviye icin ortak ilk degerler */
 oyuncu.x = ex1 + 145;
 oyuncu.y = ey1 + 95;
 oyuncu.krsyc = 0;
 oyuncu.puan = 0;
 oyuncu.hasar = 0;
 oyuncu.iska = 0;
 oyuncu.kacan = 0;
 oyuncu.maxhsr = 500;
 oyuncu.son_anm = 0;
 oyuncu.kzn_syc = 100;
 oyuncu.son_syc = 1000;
 oyuncu.tnr_syc = 0;
 oyuncu.guc_syc = 0;
 oyuncu.guc = 1;
 oyuncu.i = 0;
 oyuncu.s = 20;
 oyuncu.a1 = 0;
 oyuncu.a2 = 0;
 oyuncu.hsyc = 0;
 oyuncu.psyc = 0;
 oyuncu.asvy = 1;

 svy.ind = 0;
 svy.syc = 0;
 svy.sayac = 500;
 svy.dsmn_no = 0;
 svy.son_syc = 500;
 svy.bitti = 0;
 svy.tamam = 0;
}

int seviye(int dsmn_blg[], float dsmn_hiz[], int cph_blg[], float cph_hiz[], int nsn_dizi[], unsigned char *kare[], void svyx(int [], float [], int [], float [], int [], unsigned char *[]), int bns, unsigned char fr)
{
 unsigned char tus, otus = 0, /* sifre kontrolu icin */
               kalkan[] = {1,65,64,62,65,62,64},
               guc[] =    {1,67,59,61,68,61,67},
               maxcan[] = {1,60,68,63,60,66,63},
               blmbtr[] = {1,64,59,66,61,68,63};/*Esc F6 F1 F8 F3 F10 F5*/

 int mola,art,oart,o;

 seviye_ilk_degerler();

 art = 0; /* durdurma tusuna basilmamis */
 mola = 0; /* oyun durmamis */

 T.Esc = 0;

 while(1)
 {
  if(T.Esc) { o = 0; break; }

  kronometre = 0;

  /* oart durdurma tusunun bir onceki durumunu tutar */
  oart = art, art = T.art;

  /* durudurma tusunun basilma durumu degismisse ve su an basiliysa oyunu durdur */
  /* aksi halde oyunu devam ettir */
  if(oart != art && art) mola = (!mola) ? 1 : 0;

  if(!mola) /* oyun durdurulmamissa */
  { /* oyuncu yokedilmisse cik */
   if(oyuncu.son_anm && !oyuncu.son_syc) { o = 2; break; }

   /* sifre kontrol baslangici */

   tus = kod;

   if(tus != otus && tus < 129)
   {
    if(tus == kalkan[kalkan[0]]) kalkan[0]++; else kalkan[0] = 1;
      if(kalkan[0] == 7) { if(!oyuncu.tnr_syc) oyuncu.tnr_syc = 2500; kalkan[0] = 1; }
    if(tus == guc[guc[0]]) guc[0]++; else guc[0] = 1;
      if(guc[0] == 7) { if(!oyuncu.guc_syc) oyuncu.guc_syc= 2500; guc[0] = 1; }
    if(tus == maxcan[maxcan[0]]) maxcan[0]++; else maxcan[0] = 1;
      if(maxcan[0] == 7) { oyuncu.hasar = 0; maxcan[0] = 1; }
    if(tus == blmbtr[blmbtr[0]]) blmbtr[0]++; else blmbtr[0] = 1;
      if(blmbtr[0] == 7) { o = 1; break; }

    otus = tus;
   }

   /* sifre kontrol sonu */

   if(!bns) /* bonus seviye degilse */
   { /* oyuncu ekrani terk etmisse ve ekranda nsn turunden nesne kalmamissa bir sure bekle ve cik */
    if(oyuncu.x > ex2 && nsn_birinci == NULL) { oyuncu.kzn_syc--; if(!oyuncu.kzn_syc) { o = 1; break; } }
    else memset(SNL, fr, 64000); /* aksi halde ekrani temizle */
   }
   else /* bonus seviye ise */
   { /* oyuncu ekrani terk etmisse bir sure bekle ve cik */
    if(oyuncu.x > ex2) { oyuncu.kzn_syc--; if(!oyuncu.kzn_syc) { o = 1; break; } }
    memset(SNL, fr, 64000); /* ekrani ne olursa olsun temizle */
   }

   /* bsc yoksa, oyuncu yokedilmemisse, seviye tamamlanmissa ve ekranda nsn tipi disinda hicbir nesne kalmamissa */
   if(!svy.bsck && !oyuncu.son_anm && svy.bitti && dsmn_birinci == NULL && dcph_birinci == NULL && ocph_birinci == NULL)
    svy.tamam = 1; /* seviye basariyla tamamlanmistir */

   svyx(dsmn_blg, dsmn_hiz, cph_blg, cph_hiz, nsn_dizi, kare);

   panel();

   memcpy(VGA, SNL, 64000);
  }

  while(kronometre < 10);
 }

 /* butun oyun nesnelerinin hafizada kapladigi yeri serbest birak */
 dsmn_zincir_sil();
 ocph_zincir_sil();
 dcph_zincir_sil();
 nsn_zincir_sil();

 if(o)
 {
  if(o == 1) return puanlama(bns); /* puanlama ekranini goster ve devam et */
  else if(o == 2) { puanlama(bns); return 0; } /* puanlama ekranini goster ve cik */
 }
 else /* oyundan cik */
 {
  if(!bns) oyuncu.puan -= oyuncu.kacan * 1 + oyuncu.iska * 0.1;
  oyuncu.son_puan += oyuncu.puan;
  return 0;
 }
}
