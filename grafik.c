
 /*************************************************
 * Eklenecegi dosyaya kendisinden once            *
 * <dos.h> , <alloc.h> ve <stdio.h> eklenmelidir. *
 *************************************************/

#define SAYDAM 248 /* ekrana basilmayacak olan renk */

unsigned char *VGA = (unsigned char *) 0xA0000000L; /* VGA grafik belleginin baslangic adresi */
unsigned char *SNL = NULL; /* animasyonlar icin kullanilacak yedek ekrani gosterir */
unsigned char *RGB = NULL; /* renk paletini tutar */

unsigned int ex1, ey1, ex2, ey2; /* gorunen alanin sinir koordinatlari */

void gorunen_alan(int x, int y, int en, int boy)
{
 ex1 = x, ex2 = ex1 + en;
 ey1 = y, ey2 = ey1 + boy;
}

void SNL_ve_RGB_bellekte(void)
{
 SNL = (unsigned char *) calloc(64000, 1);
 RGB = (unsigned char *) calloc(768, 1);
}

void PCXden_byte_oku(unsigned char *byte, unsigned int *tekrar, FILE *dosya)
{/* PCX formatindan 1 byte okur ve siradaki rengin tekrar sayisini belirler */
 unsigned char i;
 *tekrar = 1;
 i = getc(dosya);
 if((i & 0xC0) == 0xC0) /* ilk 2 bit 1 ise sonraki 6 tanesi tekrar sayisini verir */
 {
  *tekrar = (i & 0x3F);
  i = getc(dosya);
 }
 *byte = i;
}

/*
char PCXi_bellege_oku(char *adres, unsigned char *palet, unsigned char *hedef)
{ /* PCX formatindaki resim dosyasini hedef alana okur */
 FILE *dosya;
 unsigned char byte;
 unsigned int Alan, tekrar, i = 0;
 int Xmin, Ymin, Xmax, Ymax, En, Boy, j = 0;

 dosya = fopen(adres, "rb");
 if(dosya == NULL) return 0;

/* ilk 128 byte baslik kismidir */
 fseek(dosya, 4, SEEK_SET); /* 4.den sonraki ilk 4 word (2byte) cerceve korrdinatlarini verir */
 Xmin = getw(dosya);
 Ymin = getw(dosya);
 Xmax = getw(dosya);
 Ymax = getw(dosya);
 En = Xmax - Xmin + 1;
 Boy = Ymax - Ymin + 1;
 Alan = (unsigned int) En * Boy; /* resmin toplam pixel sayisi */

/* en dipteki 768 byte renk paletini saklar */
 fseek(dosya, -768, SEEK_END);
/* VGA paleti 0-255 degil 0-63 arasi degerlere gereksinim duydugundan */
/* okunan degerler 4e bolunur */
 while (!feof(dosya))
 {
  palet[j++] = getc(dosya)/4;
  palet[j++] = getc(dosya)/4;
  palet[j++] = getc(dosya)/4;
 }

 fseek(dosya, 128, SEEK_SET); /* artik resmimizi hedef ekrana acabiliriz */
 while(i < Alan)
 {
  PCXden_byte_oku(&byte, &tekrar, dosya);
  while(tekrar)
  {
   hedef[i] = byte;
   tekrar--;
   i++;
  }
 }
 fclose(dosya);
 return 1;
}
*/

char XCPyi_bellege_oku(char *adres, unsigned char *palet, unsigned char *hedef)
{ /* XCP formatindaki resim dosyasini hedef alana okur */
  /* XCP, PCX formatinin baslik ve palet kisimlarinin yer degistirmis seklidir */

 FILE *dosya;
 unsigned char byte;
 unsigned int Alan, tekrar, i = 0;
 int Xmin, Ymin, Xmax, Ymax, En, Boy, j = 0;

 dosya = fopen(adres, "rb");
 if(dosya == NULL) return 0;

/* son 128 byte baslik kismidir */
 fseek(dosya, -128+4, SEEK_END); /* 4.den sonraki ilk 4 word (2byte) cerceve korrdinatlarini verir */
 Xmin = getw(dosya);
 Ymin = getw(dosya);
 Xmax = getw(dosya);
 Ymax = getw(dosya);
 En = Xmax - Xmin + 1;
 Boy = Ymax - Ymin + 1;
 Alan = (unsigned int) En * Boy; /* resmin toplam pixel sayisi */

/* en bastaki 768 byte renk paletini saklar */
 fseek(dosya, 0, SEEK_SET);
/* VGA paleti 0-255 degil 0-63 arasi degerlere gereksinim duydugundan */
/* okunan degerler 4e bolunur */
 while (j < 768)
 {
  palet[j++] = getc(dosya)/4;
  palet[j++] = getc(dosya)/4;
  palet[j++] = getc(dosya)/4;
 }

 fseek(dosya, 768, SEEK_SET); /* artik resmimizi hedef ekrana acabiliriz */
 while(i < Alan)
 {
  PCXden_byte_oku(&byte, &tekrar, dosya);
  while(tekrar)
  {
   hedef[i] = byte;
   tekrar--;
   i++;
  }
 }
 fclose(dosya);
 return 1;
}

void kare_oku(int x1, int y1, int x2, int y2, unsigned char *kaynak, unsigned char *hedef)
{ /* kaynak alandan hedefe bir resim karesi okur. ilk 2 bayta en ve boy degerini yazar */
 int i, j, h = 2;
 hedef[0] = x2 - x1 + 1;
 hedef[1] = y2 - y1 + 1;
 for(j = y1; j <= y2; j++)
  for(i = x1; i <= x2; i++)
   hedef[h++] = kaynak[i + j * 320];
}

void ekran_modu(unsigned char mod)
{ /* ekran modunu mod degerine getirir */
 union REGS regs;

 regs.h.ah = 0x0;
 regs.h.al = mod;

 int86(0x10, &regs, &regs);
}

void renk(unsigned char no, unsigned char R, unsigned char G, unsigned char B)
{ /* no ile verilen numarali rengin kirmizi yesil mavi yogunlugunu ayarlar */
 outp(0x03C8,no);
 outp(0x03C9,R);
 outp(0x03C9,G);
 outp(0x03C9,B);
}

void renk_paletini_kur(unsigned char *kaynak)
{ /* renk paletini kaynakta verilen degerlere ayarlar */
 int i = 0;
 unsigned char R, G, B, no;
 for(no = 0; no < 255; no++)
 {
  R = kaynak[i++];
  G = kaynak[i++];
  B = kaynak[i++];
  renk(no, R, G, B);
 }
}

void kare_koy(int nx1, int ny1, unsigned char *kaynak, unsigned char *hedef)
{ /* kaynak resim karesinin verilen koordinatlarda */
  /* gorunen alan icinde kalan kismini hedef alana kopyalar */

 int nx2, ny2;
 int x1, x2, y1, y2;
 int ix, sx, iy, sy;
 int x, y, k = 2;

 nx2 = nx1 + kaynak[0] - 1;
 ny2 = ny1 + kaynak[1] - 1;

 x1 = max(ex1, nx1);
 x2 = min(ex2, nx2);
 y1 = max(ey1, ny1);
 y2 = min(ey2, ny2);

 ix = x1 - nx1;
 sx = ix + (x2 - x1);
 iy = y1 - ny1;
 sy = iy + (y2 - y1);

 for(y = iy; y <= sy; y++)
  for(x = ix; x <= sx; x++)
  {
   k = 2 + (x + y * kaynak[0]);
   if(kaynak[k] != SAYDAM) hedef[(nx1 - ex1 + x) + (ny1 - ey1 + y) * 320] = kaynak[k];
  }
}

void hzl_kare_koy(int x, int y, unsigned char *kaynak, unsigned char *hedef)
{ /* kaynakta verilen resim karesini hedef alanin istenen koordinatina kopyalar */
 int a, b, k = 2;
 int c = kaynak[0] - 1;
 int d = kaynak[1] - 1;

 for(b = 0; b <= d; b++)
  for(a = 0; a <= c; a++)
   { if(kaynak[k] != SAYDAM) hedef[(x + a) + (y + b) * 320] = kaynak[k]; k++; }
}

void SNL_ve_RGB_serbest(void)
{
 free(SNL);
 free(RGB);
}