
 /*********************************
 * Eklenecegi dosyaya kendisinden *
 * once <dos.h> eklenmelidir.     *
 *********************************/

unsigned char kod;

struct /* kullanacagimiz tuslar icin */
{
 int Esc : 1;
 int Enter : 1;
 int sol : 1;
 int sag : 1;
 int ilr : 1;
 int gri : 1;
 int art : 1;
 int Ctrl : 1;
} T;

void interrupt (*INT9)(void); /* orjinal kesmeyi bunda sakliycaz */

void kod_kontrol(void) /* kullandimiz tuslarin basildiðini ya da birakildiðini kontrol eder */
{
 if(kod == 1) T.Esc = 1;
 if(kod == 129) T.Esc = 0;
 if(kod == 28) T.Enter = 1;
 if(kod == 156) T.Enter = 0;
 if(kod == 75) T.sol = 1;
 if(kod == 203) T.sol = 0;
 if(kod == 77) T.sag = 1;
 if(kod == 205) T.sag = 0;
 if(kod == 72) T.ilr = 1;
 if(kod == 200) T.ilr = 0;
 if(kod == 80) T.gri = 1;
 if(kod == 208) T.gri = 0;
 if(kod == 78) T.art = 1;
 if(kod == 206) T.art = 0;
 if(kod == 29) T.Ctrl = 1;
 if(kod == 157) T.Ctrl = 0;
}

void interrupt yeni_INT9(void) /* kendi kesmemiz */
{
 kod = inp(0x60); /* 0x60 nolu porttan tus kodunu okur */
 outp(0x20,0x20); /* portu durumdan haberdar et */
 kod_kontrol(); /* kodu kontrol eder */
}

void klavyeyi_yeniden_programla(void)
{
 kod = 0;
 T.Esc = 0;
 T.Enter = 0;
 T.sol = 0;
 T.sag = 0;
 T.ilr = 0;
 T.gri = 0;
 T.art = 0;
 T.Ctrl = 0;

 INT9 = getvect(9); /* orjinal kesmeyi yedekle */
 setvect(9, yeni_INT9); /* kendi kesmemizi orjinalinin yerine koy */
}

void klavyeyi_eski_haline_getir(void)
{
 setvect(9, INT9); /* orjinal kesmeyi yerine koy */
}