void bns_svy2(int dsmn_blg[], float dsmn_hiz[], int cph_blg[], float cph_hiz[], int nsn_dizi[], unsigned char *kare[])
{
 int o,p,r;
 int u, v, e, f;

 /* dalgalar icin renk dizisi */
 int rnk[] = { 16, 24, 80, 88,120, 17, 25, 81,
               89,121, 18, 26, 82, 90,122, 19,
               27, 83, 91,123, 20, 28, 84, 92,
              124, 21, 29, 85, 93,125, 22, 30,
               86, 94,126, 23, 31, 87, 95,127};

/* bu seviyede hareket dizilerine gerek yok */
/* saldiri dalgalari arasindaki bekleme suresini tutan dizi */
 int dlg_ara[] = {12000,-2};

/* saldiri dalgalarini olusturan arac tiplerini ve ilk y koordinatlarini tutan dizi */
/* herbir dalga icin arac sayisi limitsizdir */
                   /*  t/  y/ t/  y/...      *//* dalgalar */
 int dsmn_dlg[] = {-2};

/* her dusman icin dikey hareket sayisi, hiz kat sayisi (1/k) ve uzakligini tutan dizi */
/* herbir dusman icin dikey hareket sayisi limitsizdir *//* (+) asagi, (-) yukari */
               /* harsay/ k/uzk/ k/uzk/...          *//* no */
 int dsmn_dky[] = {-10,0};

 /* yildizlari tepeleri ve dalgalari olustur */
 yldzlr(8);
 tepeler(0, 0);
 for(o = 0; o < 5; o++) dalgalar(o);

 /* yildizlari tepeleri ve dalgalari ekrana bas */
 for(o = 0; o < 320; o++)
 {
  SNL[o + (yldz.dizi[o] << 6) + (yldz.dizi[o] << 8)] = yldz.renk[o];

  if(tplr[0].dizi[o] < dlglr[0].dizi[o])
  {
   SNL[o + (tplr[0].dizi[o] << 6) + (tplr[0].dizi[o] << 8)] = 50;
   for(p = tplr[0].dizi[o] + 1, r = 50; p < dlglr[1].dizi[o] && r > 36; p++, r--) SNL[o + (p << 6) + (p << 8)] = r;
   for(p = p; p < dlglr[1].dizi[o]; p++) SNL[o + (p << 6) + (p << 8)] = r;
  }
  if(dlglr[0].dizi[o] < dlglr[1].dizi[o])
  {
   for(r = 0, p = dlglr[0].dizi[o]; p < dlglr[1].dizi[o] && r < 8; p++, r++) SNL[o + (p << 6) + (p << 8)] = rnk[r];
   for(p = p; p < dlglr[1].dizi[o]; p++) SNL[o + (p << 6) + (p << 8)] = rnk[r - 1];
  }
  if(dlglr[1].dizi[o] < dlglr[2].dizi[o])
  {
   for(r = 8, p = dlglr[1].dizi[o]; p < dlglr[2].dizi[o] && r < 16; p++, r++) SNL[o + (p << 6) + (p << 8)] = rnk[r];
   for(p = p; p < dlglr[2].dizi[o]; p++) SNL[o + (p << 6) + (p << 8)] = rnk[r - 1];
  }
  if(dlglr[2].dizi[o] < dlglr[3].dizi[o])
  {
   for(r = 16, p = dlglr[2].dizi[o]; p < dlglr[3].dizi[o] && r < 24; p++, r++) SNL[o + (p << 6) + (p << 8)] = rnk[r];
   for(p = p; p < dlglr[3].dizi[o]; p++) SNL[o + (p << 6) + (p << 8)] = rnk[r - 1];
  }
  if(dlglr[3].dizi[o] < dlglr[4].dizi[o])
  {
   for(r = 24, p = dlglr[3].dizi[o]; p < dlglr[4].dizi[o] && r < 32; p++, r++) SNL[o + (p << 6) + (p << 8)] = rnk[r];
   for(p = p; p < dlglr[4].dizi[o]; p++) SNL[o + (p << 6) + (p << 8)] = rnk[r - 1];
  }
 }

 oyuncu.asvy = 2; /* oyuncu ates seviyesi surekli 2de kalsin */
 oyuncu_hareket();

 nesne_ekle(dlg_ara, dsmn_dlg, 1,12000); /* seviyenin bitimini saðlamak icin */

 if(dsmn_blg[544] < 3) /* ekrandaki yilan sayisi 3ten az ise */
 {
  if(!dsmn_blg[571] && !svy.bitti)
  { /* seviye bitmedigi surece sayac her sifirlandiginda bir koza ekle */
   dsmn_blg[571] = 500 + (rand() % 5) * 100; /* rastgele maksimum sayac degeri belirle */
   yeni_dsmn_dugum(21, ex1 + rand() % 306, ey1 - 9, ++svy.dsmn_no);
  }
  else dsmn_blg[571]--;
 }

 if(dsmn_blg[545] && !svy.bitti) /* seviye bitmedigi surece */
 { /* yilan ekle degiskeni != 0 ise */
  dsmn_blg[545] = 0; /* degiskeni sifirla */

  /* dsmn_blg[570] son dusen kozanin x degerini tutar */
  yeni_dsmn_dugum(20, dsmn_blg[570], ey2, ++svy.dsmn_no); /* yilan basini ekle */
  /* rasgele hedef koordinatini tutan degiskenlere ilk degerlerini ata */
  dsmn_sonuncu->d2 = dsmn_blg[570];
  dsmn_sonuncu->d3 = ey2;
  /* yilanin parcalarini ekle */
  for(o = 0; o < 21; o++) yeni_dsmn_dugum(19, dsmn_blg[570], ey2, ++svy.dsmn_no);

  dsmn_blg[544]++; /* ekrandaki yilan sayisini yenile */
 }

 dsmn_zincir_oku(kare, dsmn_blg, dsmn_hiz, dsmn_dky, cph_blg, dsmn_ani);

 dcph_zincir_oku(kare, cph_blg, cph_hiz, dcph_ani);

 ocph_zincir_oku(kare, cph_hiz, cph_blg, dsmn_blg, ocph_ani);

 nsn_zincir_oku(kare, nsn_dizi, nsn_ani);

 for(o = 0; o < 320; o++) /* on cephede kalan ve zemin olusturan dalgalari ekrana bas */
 {
  for(r = 32, p = dlglr[4].dizi[o]; p < 200 && r < 40; p++, r++) SNL[o + (p << 6) + (p << 8)] = rnk[r];
  for(p = p; p < 200; p++) SNL[o + (p << 6) + (p << 8)] = rnk[r - 1];
 }
}