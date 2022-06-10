
 /*********************************
 * Eklenecegi dosyaya kendisinden *
 * once <dos.h> eklenmelidir.     *
 *********************************/

unsigned long int kronometre; /* saniyenin 1000de 1inde 1 artar */

void interrupt (*INT8)(void); /* orjinal kesmeyi bunda sakliycaz */

void interrupt yeni_INT8(void) /* kendi kesmemiz */
{
 static unsigned long int say = 0;

 kronometre++;
 say += 1193; /* programlanabilir icsel zamanlayicinin frekansinin (1193181) 1000de 1i */
/* normalde 65536 vurusta bir 8 nolu kesme olusturulur (yaklasik saniyede 18.2 vurus) */
 if(say >= 65536)
 {
  say -= 65536;
  INT8();
 }
 else outp(0x20, 0x20); /* aksi halde portu durumdan haberdar et */
}

void saati_yeniden_programla(void)
{
 kronometre = 0;

 INT8 = getvect(8); /* orjinal kesmeyi yedekle */
 setvect(8, yeni_INT8); /* kendi kesmemizi orjinalinin yerine koy */

 outp(0x43, 52); /* zamanlayicinin 0. kanalini ayarla */
 outp(0x40, 1193 % 256); /* kanal sayacina once vurus araliginin dusuk baytini */
 outp(0x40, 1193 / 256); /* sonra yuksek baytini yaz */
}

void saati_eski_haline_getir(void)
{
 outp(0x43, 52);
 outp(0x40, 0);
 outp(0x40, 0);

 setvect(8, INT8); /* orjinal kesmeyi yerine koy */
}