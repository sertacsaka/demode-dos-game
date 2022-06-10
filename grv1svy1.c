void grv1svy1(int dsmn_blg[], float dsmn_hiz[], int cph_blg[], float cph_hiz[], int nsn_dizi[], unsigned char *kare[])
{
 int o;

/* saldiri dalgalari arasindaki bekleme surelerini tutan dizi */
 int dlg_ara[] = {300,50,350,50,350,50,350,50,50,75,350,50,50,75,350,/*500+2550*//*15*/
                  50,50,75,350,300,300,300,350,75,400,75,700,25,25,/*3075*//*29*/
                  25,400,25,25,25,400,25,25,25,200,25,25,25,350,100,100,100,100,100,100,100,100,100,500,/*3000*//*53*/
                  75,250,75,500,75,75,350,75,75,750,50,50,50,75,200,300,/*3025*//*69*/
                  50,50,50,50,50,50,50,100,100,100,500,100,100,350,100,100,350,50,50,250,50,50,300,/*3000*//*92*/
                  50,25,400,50,25,350,150,150,150,400,75,75,100,75,75,500,50,50,50,50,50,50,/*2950*//*114*/
                  400,50,50,150,50,50,50,50,50,150,50,50,50,50,50,150,50,50,50,50,50,150,50,50,150,50,50,100,50,50,150,50,50,250,50,50,/*3000*//*151*/
                  50,50,50,100,50,50,100,50,50,100,50,50,50,-2};/*800*//*168*/

/* saldiri dalgalarini olusturan arac tiplerini ve ilk y koordinatlarini tutan dizi */
/* herbir dalga icin arac sayisi limitsizdir */
                   /*  t/  y/ t/  y/...      *//* dalgalar */
 int dsmn_dlg[] = {-1, 7,245, 7,345,           /* dalga 1  */
                   -1, 7,295,                  /* dalga 2  */
                   -1, 7,280, 7,310,           /* dalga 3  */
                   -1, 7,295, 7,375,           /*    .     */
                   -1, 7,295, 7,375,           /*    .     */
                   -1, 7,225, 7,305,           /*    .     */
                   -1, 7,225, 7,305,
                   -1, 7,250,
                   -1, 7,250,
                   -1, 7,250,
                   -1,10,250,
                   -1, 7,300,
                   -1, 7,300,
                   -1, 7,300,
                   -1,10,300,
                   -1, 7,350,
                   -1, 7,350,
                   -1, 7,350,
                   -1,10,350,
                   -1, 8,250,
                   -1, 8,250,/*20*/
                   -1, 8,325,
                   -1, 8,325,
                   -1,10,225,10,265,
                   -1, 7,292, 7,332,
                   -1,10,315,10,355,
                   -1, 7,253, 7,293,
                   -1, 5,250,
                   -1, 5,250,
                   -1, 5,250,
                   -1, 5,250,
                   -1, 5,350,
                   -1, 5,350,
                   -1, 5,350,
                   -1, 5,350,
                   -1, 5,300,
                   -1, 5,300,
                   -1, 5,300,
                   -1, 5,300,
                   -1, 5,300,
                   -1, 5,300,/*40*/
                   -1, 5,300,
                   -1, 5,300,
                   -1, 4,200,
                   -1, 4,399,
                   -1, 4,200,
                   -1, 4,399,
                   -1, 4,200,
                   -1, 4,399,
                   -1, 4,200,
                   -1, 4,399,
                   -1, 4,200,
                   -1, 4,399,
                   -1, 8,250, 8,270,
                   -1, 8,250, 8,270,
                   -1, 8,350, 8,370,
                   -1, 8,350, 8,370,
                   -1,10,250,
                   -1,10,250,
                   -1,10,250,
                   -1,10,350,/*60*/
                   -1,10,350,
                   -1,10,350,
                   -1, 7,295,
                   -1, 7,280, 7,310,
                   -1, 7,265, 7,295, 7,325,
                   -1,10,230,10,360,
                   -1,10,230,10,360,
                   -1, 1,300,
                   -1, 7,303,
                   -1, 7,303,
                   -1, 7,303,
                   -1, 7,303,
                   -1, 7,303,
                   -1, 7,303,
                   -1, 7,303,
                   -1, 7,303,
                   -1,11,250,11,350,
                   -1,11,250,11,350,
                   -1,11,250,11,350,
                   -1,11,375,/*80*/
                   -1,11,375,
                   -1,11,375,
                   -1,11,225,
                   -1,11,225,
                   -1,11,225,
                   -1,11,350,
                   -1,11,350,
                   -1,11,350,
                   -1,11,225,
                   -1,11,225,
                   -1,11,225,
                   -1, 7,303,
                   -1,10,300,
                   -1,11,225,
                   -1, 7,303,
                   -1,10,300,
                   -1,11,375,
                   -1, 8,250,
                   -1, 8,250,
                   -1, 8,325,/*100*/
                   -1, 8,325,
                   -1,10,225,
                   -1,10,225,
                   -1,10,225,
                   -1,10,350,
                   -1,10,350,
                   -1,10,350,
                   -1, 4,295,
                   -1, 4,284, 4,306,
                   -1, 4,295,
                   -1, 6,291,
                   -1, 4,340,
                   -1, 4,329, 4,351,
                   -1, 4,340,
                   -1, 4,295,
                   -1, 4,284, 4,306,
                   -1, 4,295,
                   -1, 4,295,
                   -1, 4,284, 4,306,
                   -1, 4,295,
                   -1, 4,250,/*120*/
                   -1, 4,239, 4,261,
                   -1, 4,250,
                   -1, 4,340,
                   -1, 4,329, 4,351,
                   -1, 4,340,
                   -1, 4,295,
                   -1, 4,284, 4,306,
                   -1, 4,295,
                   -1, 4,295,
                   -1, 4,284, 4,306,
                   -1, 4,295,
                   -1, 4,340,
                   -1, 4,329, 4,351,
                   -1, 4,340,
                   -1, 4,340,
                   -1, 4,329, 4,351,
                   -1, 4,340,
                   -1, 4,340, 4,250,
                   -1, 4,329, 4,351, 4,239, 4,261,
                   -1, 4,340, 4,250,/*140*/
                   -1, 4,295,
                   -1, 4,284, 4,306,
                   -1, 4,295,
                   -1, 4,250, 4,340,
                   -1, 4,239, 4,261, 4,329, 4,351,
                   -1, 4,250, 4,340,
                   -1, 4,295,
                   -1, 4,284, 4,306,
                   -1, 4,295,
                   -1, 4,340,
                   -1, 4,329, 4,351,
                   -1, 4,340,
                   -1, 4,250,
                   -1, 4,239, 4,261,
                   -1, 4,250,
                   -1, 4,295,
                   -1, 4,284, 4,306,
                   -1, 4,295,
                   -1, 4,295,
                   -1, 4,284, 4,306,
                   -1, 4,295,
                   -2};

/* her dusman icin dikey hareket sayisi, hiz kat sayisi (1/k) ve uzakligini tutan dizi */
/* herbir dusman icin dikey hareket sayisi limitsizdir *//* (+) asagi, (-) yukari */
               /* harsay/ k/uzk/ k/uzk/...          *//* no */
 int dsmn_dky[] = {-10,0,                             /* 1  */
                   -10,0,                             /* 2  */
                   -10,0,                             /* 3  */
                   -10,2, 0, 50,-5, 50,               /* .  */
                   -10,2, 0, 50,+5, 50,               /* .  */
                   -10,1,+2, 25,                      /* .  */
                   -10,1,-2, 25,
                   -10,1,+2, 25,
                   -10,1,-2, 25,
                   -10,1,+2, 25,
                   -10,1,-2, 25,
                   -10,1,+2, 25,
                   -10,1,-2, 25,
                   -10,4,+6, 15,-6, 30,+6, 30,-6, 30,
                   -10,4,-6, 15,+6, 30,-6, 30,+6, 30,
                   -10,4,+4, 25,-4, 50,+4, 50,-4, 50,
                   -10,2, 0, 75,+2,100,
                   -10,4,+6, 15,-6, 30,+6, 30,-6, 30,
                   -10,4,-6, 15,+6, 30,-6, 30,+6, 30,
                   -10,4,+4, 25,-4, 50,+4, 50,-4, 50,
                   -10,3, 0, 75,-2, 50,+6,100,
                   -10,4,+6, 15,-6, 30,+6, 30,-6, 30,
                   -10,4,-6, 15,+6, 30,-6, 30,+6, 30,
                   -10,4,+4, 25,-4, 50,+4, 50,-4, 50,
                   -10,2, 0, 75,-2,100,
                   -10,6, 0, 50,+2, 50, 0, 50,+2, 50, 0, 50,+2, 50,
                   -10,6, 0, 50,+2, 50, 0, 50,+2, 50, 0, 50,+2, 50,
                   -10,6, 0, 50,-2, 50, 0, 50,-2, 50, 0, 50,-2, 50,
                   -10,6, 0, 50,-2, 50, 0, 50,-2, 50, 0, 50,-2, 50,
                   -10,0,
                   -10,0,
                   -10,2, 0, 50,-1, 65,
                   -10,2, 0, 50,-1, 65,
                   -10,0,
                   -10,0,
                   -10,2, 0, 50,+1, 65,
                   -10,2, 0, 50,+1, 65,
                   -10,3, 0, 50,-4, 25,+2,150,
                   -10,3, 0, 50,-4, 25,+2,150,
                   -10,3, 0, 50,-4, 25,+2,150,
                   -10,3, 0, 50,-4, 25,+2,150,
                   -10,3, 0, 50,+4, 25,-2,150,
                   -10,3, 0, 50,+4, 25,-2,150,
                   -10,3, 0, 50,+4, 25,-2,150,
                   -10,3, 0, 50,+4, 25,-2,150,
                   -10,4, 0, 50,+4, 25,-2, 50,+2,100,
                   -10,4, 0, 50,+4, 25,-2, 50,+2,100,
                   -10,4, 0, 50,+4, 25,-2, 50,+2,100,
                   -10,4, 0, 50,+4, 25,-2, 50,+2,100,
                   -10,4, 0, 50,-4, 25,+2, 50,-2,100,
                   -10,4, 0, 50,-4, 25,+2, 50,-2,100,
                   -10,4, 0, 50,-4, 25,+2, 50,-2,100,
                   -10,4, 0, 50,-4, 25,+2, 50,-2,100,
                   -10,2,+2,139,-4,200,
                   -10,2,-8,150,+2,189,
                   -10,2,+8,139,-2,200,
                   -10,2,-2,150,+4,189,
                   -10,2,+2,139,-4,200,
                   -10,2,-8,150,+2,189,
                   -10,2,+8,139,-2,200,
                   -10,2,-2,150,+4,189,
                   -10,2,+2,139,-4,200,
                   -10,2,-8,150,+2,189,
                   -10,6, 0, 50,+2, 50, 0, 50,+2, 50, 0, 50,+2, 50,
                   -10,6, 0, 50,+2, 50, 0, 50,+2, 50, 0, 50,+2, 50,
                   -10,6, 0, 50,+2, 50, 0, 50,+2, 50, 0, 50,+2, 50,
                   -10,6, 0, 50,+2, 50, 0, 50,+2, 50, 0, 50,+2, 50,
                   -10,6, 0, 50,-2, 50, 0, 50,-2, 50, 0, 50,-2, 50,
                   -10,6, 0, 50,-2, 50, 0, 50,-2, 50, 0, 50,-2, 50,
                   -10,6, 0, 50,-2, 50, 0, 50,-2, 50, 0, 50,-2, 50,
                   -10,6, 0, 50,-2, 50, 0, 50,-2, 50, 0, 50,-2, 50,
                   -10,8,+6, 25,-6, 50,+6, 50,-6, 50,+6, 50,-6, 50,+6, 50,-6, 50,
                   -10,8,-6, 25,+6, 50,-6, 50,+6, 50,-6, 50,+6, 50,-6, 50,+6, 50,
                   -10,8,+6, 25,-6, 50,+6, 50,-6, 50,+6, 50,-6, 50,+6, 50,-6, 50,
                   -10,8,+6, 25,-6, 50,+6, 50,-6, 50,+6, 50,-6, 50,+6, 50,-6, 50,
                   -10,8,-6, 25,+6, 50,-6, 50,+6, 50,-6, 50,+6, 50,-6, 50,+6, 50,
                   -10,8,+6, 25,-6, 50,+6, 50,-6, 50,+6, 50,-6, 50,+6, 50,-3, 50,
                   -10,0,
                   -10,0,
                   -10,0,
                   -10,0,
                   -10,0,
                   -10,0,
                   -10,1,+6, 50,
                   -10,1,-6, 50,
                   -10,1,+6, 50,
                   -10,1,-6, 50,
                   -10,0,
                   -10,0,
                   -10,0,
                   -10,0,
                   -10,0,
                   -10,0,
                   -10,0,
                   -10,0,
                   -10,0,
                   -10,10, 0, 50,+4, 25, 0, 50,-4, 25, 0, 50,+4, 25, 0, 50,-4, 25, 0, 50,+4, 25,
                   -10,10, 0, 50,-4, 25, 0, 50,+4, 25, 0, 50,-4, 25, 0, 50,+4, 25, 0, 50,-4, 25,
                   -10,10, 0, 50,+4, 25, 0, 50,-4, 25, 0, 50,+4, 25, 0, 50,-4, 25, 0, 50,+4, 25,
                   -10,10, 0, 50,-4, 25, 0, 50,+4, 25, 0, 50,-4, 25, 0, 50,+4, 25, 0, 50,-4, 25,
                   -10,10, 0, 50,+4, 25, 0, 50,-4, 25, 0, 50,+4, 25, 0, 50,-4, 25, 0, 50,+4, 25,
                   -10,10, 0, 50,-4, 25, 0, 50,+4, 25, 0, 50,-4, 25, 0, 50,+4, 25, 0, 50,-4, 25,
                   -10,8, 0, 50,-2, 50, 0, 50,-2, 50, 0, 50,-2, 50, 0, 50,-2, 50,
                   -10,8, 0, 50,-2, 50, 0, 50,-2, 50, 0, 50,-2, 50, 0, 50,-2, 50,
                   -10,8, 0, 50,-2, 50, 0, 50,-2, 50, 0, 50,-2, 50, 0, 50,-2, 50,
                   -10,8, 0, 50,+2, 50, 0, 50,+2, 50, 0, 50,+2, 50, 0, 50,+2, 50,
                   -10,8, 0, 50,+2, 50, 0, 50,+2, 50, 0, 50,+2, 50, 0, 50,+2, 50,
                   -10,8, 0, 50,+2, 50, 0, 50,+2, 50, 0, 50,+2, 50, 0, 50,+2, 50,
                   -10,6,+2, 25,-3, 50,+2, 25,-3, 50,+2, 25,-3, 50,
                   -10,6,+2, 25,-3, 50,+2, 25,-3, 50,+2, 25,-3, 50,
                   -10,6,+2, 25,-3, 50,+2, 25,-3, 50,+2, 25,-3, 50,
                   -10,6,-2, 25,+3, 50,-2, 25,+3, 50,-2, 25,+3, 50,
                   -10,6,-2, 25,+3, 50,-2, 25,+3, 50,-2, 25,+3, 50,
                   -10,6,-2, 25,+3, 50,-2, 25,+3, 50,-2, 25,+3, 50,
                   -10,0,
                   -10,2, 0, 50,-1, 75,
                   -10,0,
                   -10,0,
                   -10,2, 0, 50,+1, 75,
                   -10,0,
                   -10,6, 0, 50,+2, 50, 0, 50,+2, 50, 0, 50,+2, 50,
                   -10,6, 0, 50,+2, 50, 0, 50,+2, 50, 0, 50,+2, 50,
                   -10,6, 0, 50,-2, 50, 0, 50,-2, 50, 0, 50,-2, 50,
                   -10,6, 0, 50,-2, 50, 0, 50,-2, 50, 0, 50,-2, 50,
                   -10,6, 0, 50,+1,100,-2, 50, 0, 50,+1,100,-2, 50,
                   -10,6, 0, 50,+1,100,-2, 50, 0, 50,+1,100,-2, 50,
                   -10,6, 0, 50,+1,100,-2, 50, 0, 50,+1,100,-2, 50,
                   -10,6, 0, 50,-1,100,+2, 50, 0, 50,-1,100,+2, 50,
                   -10,6, 0, 50,-1,100,+2, 50, 0, 50,-1,100,+2, 50,
                   -10,6, 0, 50,-1,100,+2, 50, 0, 50,-1,100,+2, 50,
                   -10,0,
                   -10,0,
                   -10,0,
                   -10,0,
                   -10,7,+1, 70,-1,140,+1,70,-1,35,+1,35,-1,35,+1, 200,
                   -10,0,
                   -10,0,
                   -10,0,
                   -10,0,
                   -10,0,
                   -10,0,
                   -10,0,
                   -10,0,
                   -10,0,
                   -10,0,
                   -10,0,
                   -10,0,
                   -10,0,
                   -10,0,
                   -10,0,
                   -10,0,
                   -10,0,
                   -10,0,
                   -10,0,
                   -10,0,
                   -10,0,
                   -10,0,
                   -10,0,
                   -10,0,
                   -10,0,
                   -10,0,
                   -10,0,
                   -10,0,
                   -10,0,
                   -10,0,
                   -10,0,
                   -10,0,
                   -10,0,
                   -10,0,
                   -10,0,
                   -10,0,
                   -10,0,
                   -10,0,
                   -10,0,
                   -10,0,
                   -10,0,
                   -10,0,
                   -10,0,
                   -10,0,
                   -10,0,
                   -10,0,
                   -10,0,
                   -10,0,
                   -10,0,
                   -10,0,
                   -10,0,
                   -10,0,
                   -10,0,
                   -10,0,
                   -10,0,
                   -10,0,
                   -10,0,
                   -10,0,
                   -10,0,
                   -10,0,
                   -10,0,
                   -10,0,
                   -10,0,
                   -10,0,
                   -10,0,
                   -10,0,
                   -10,0,
                   -10,0,
                   -10,0,
                   -10,0,
                   -10,0,
                   -10,0,
                   -10,0,
                   -10,0,
                   -10,0,
                   -10,0};

 yldzlr(32); /* yildizli fonu yarat */
 /* yildizlari ekrana bas */
 for(o = 0; o < 320; o++) SNL[o + (yldz.dizi[o] << 6) + (yldz.dizi[o] << 8)] = yldz.renk[o];

 oyuncu_hareket();

 nesne_ekle(dlg_ara, dsmn_dlg, 0, 0);

 dsmn_zincir_oku(kare, dsmn_blg, dsmn_hiz, dsmn_dky, cph_blg, dsmn_ani);

 dcph_zincir_oku(kare, cph_blg, cph_hiz, dcph_ani);

 ocph_zincir_oku(kare, cph_hiz, cph_blg, dsmn_blg, ocph_ani);

 nsn_zincir_oku(kare, nsn_dizi, nsn_ani);
}