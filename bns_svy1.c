void bns_svy1(int dsmn_blg[], float dsmn_hiz[], int cph_blg[], float cph_hiz[], int nsn_dizi[], unsigned char *kare[])
{
 int o,p,r;

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

 yldzlr(32); /* yildizli fonu olustur */
 for(o = 0; o < 3; o++) tepeler(o, 0); /* kayan tepeleri olustur */

 for(o = 0; o < 320; o++) /* yildizlari ve tepeleri ekrana bas */
 {
  SNL[o + (yldz.dizi[o] << 6) + (yldz.dizi[o] << 8)] = yldz.renk[o];

  if(tplr[2].dizi[o] < tplr[1].dizi[o] && tplr[2].dizi[o] < tplr[0].dizi[o])
  {
   SNL[o + (tplr[2].dizi[o] << 6) + (tplr[2].dizi[o] << 8)] = 50;
   for(p = tplr[2].dizi[o] + 1, r = 50; (p < tplr[0].dizi[o] && p < tplr[1].dizi[o] && r > 36); p++, r--) SNL[o + (p << 6) + (p << 8)] = r;
   for(p = p; (p < tplr[0].dizi[o] && p < tplr[1].dizi[o]); p++) SNL[o + (p << 6) + (p << 8)] = r;
  }
  if(tplr[1].dizi[o] < tplr[0].dizi[o])
  {
   SNL[o + (tplr[1].dizi[o] << 6) + (tplr[1].dizi[o] << 8)] = 50;
   for(p = tplr[1].dizi[o] + 1, r = 50; (p < tplr[0].dizi[o] && r > 36); p++, r--) SNL[o + (p << 6) + (p << 8)] = r;
   for(p = p; p < tplr[0].dizi[o]; p++) SNL[o + (p << 6) + (p << 8)] = r;
  }
 }

 oyuncu.asvy = 2; /* oyuncunun ates seviyesi surekli 2de kalsin */
 oyuncu_hareket();

 nesne_ekle(dlg_ara, dsmn_dlg, 1,12000); /* seviyenin bitimini saðlamak icin sayac vazifesi gorur */

 if(!dsmn_blg[467] && !svy.bitti)
 { /* seviye bitmedigi surece her sayac sifirlandiginda yeni balina gonder */
  dsmn_blg[467] = 1000; /* sayac maksimum degerini alsin */
  dsmn_sonuncu->d2 = rand() % 50; /* ekrana rastgele giris seviyesi belirle */
  yeni_dsmn_dugum(17, ex2, ey1 + dsmn_sonuncu->d2, ++svy.dsmn_no);
  dsmn_sonuncu->d2 = 50 + rand() % 50; /* rasgele hedef seviye belirle */
 }
 else dsmn_blg[467]--;

 dsmn_zincir_oku(kare, dsmn_blg, dsmn_hiz, dsmn_dky, cph_blg, dsmn_ani);

 dcph_zincir_oku(kare, cph_blg, cph_hiz, dcph_ani);

 ocph_zincir_oku(kare, cph_hiz, cph_blg, dsmn_blg, ocph_ani);

 nsn_zincir_oku(kare, nsn_dizi, nsn_ani);

 for(o = 0; o < 320; o++) /* on cephede kalan ve zemin olusturan tepeleri ekrana bas */
 {
  SNL[o + (tplr[0].dizi[o] << 6) + (tplr[0].dizi[o] << 8)] = 50;
  for(p = tplr[0].dizi[o] + 1, r = 50; (p < 200 && r > 36); p++, r--) SNL[o + (p << 6) + (p << 8)] = r;
  for(p = p; p < 200; p++) SNL[o + (p << 6) + (p << 8)] = r;
 }
}