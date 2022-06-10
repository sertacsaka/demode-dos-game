struct /* yildizli kayan fon icin kullanilacak degiskenler */
{
 int yogunluk,dizi[320],renk[320],sayac,periyot;
}
yldz;

struct /* kayan tepe animasyonlari icin kullanilacak degiskenler */
{
 int a,b,c,d,i,s,d1x,d1y,d2x,d2y,u,v,m,n,e,f,ust,alt,dizi[320],sayac,periyot;
}
tplr[3];

struct /* kayan dalga animasyonlari icin kullanilacak degiskenler */
{
 int a,ailk,dizi[320],y,da,genlik,dgenlik,sgenlik,dalgaboyu,sayac,periyot;
}
dlglr[5];

void yldz_yap(int d, unsigned char fon) /* yildizli kayan fon icin baslangic degerleri */
{
 int o;

 yldz.yogunluk = d; /* yildizin dizinin belli bir yerinde olma olasiligi */
 yldz.periyot = 4;
 yldz.sayac = 0;

 for(o = 0; o < 320; o++) /* ilk ekran icin yildiz dizisini doldur */
 {
  yldz.dizi[o] = rand() % 199;
  yldz.renk[o] = (!(rand() % yldz.yogunluk)) ? 40 + (rand() % 23) : fon;
 }
}

void tepe_yap(int k, int ust, int alt) /* kayan tepe animasyonlari icin baslangic degerleri */
{
 int o;

 for(o = 0; o < k; o++)
 {
  tplr[o].i = 0;
  tplr[o].a = 319; /* kayan tepenin kaymaya */
  tplr[o].b = 199; /* baslangic noktasi */
  tplr[o].ust = ust + (k - o) * 10; /* tepe ust siniri */
  tplr[o].alt = alt; /* tepe alt siniri */
  tplr[o].sayac = 0;
  tplr[o].periyot = o * 2;
 }

 /* dizinin butun degerlerini minimum degere getir */
 for(o = 0; o < 320; o++)
 {
  tplr[0].dizi[o] = alt;
  tplr[1].dizi[o] = alt;
  tplr[2].dizi[o] = alt;
 }
}

void dalga_yap(int k, int ust) /* kayan dalga animasyonlari icin baslangic degerleri */
{
 int o;

 for(o = 0; o < k; o++)
 {
  dlglr[o].y = ust + o * 3;
  dlglr[o].da = o + 3; /* acinin artma miktari */
  dlglr[o].dalgaboyu = k - o;
  dlglr[o].ailk = 0; /* acinin baslangic degeri */
  dlglr[o].genlik = k - o; /* genligin anlik degeri */
  dlglr[o].sgenlik = 3 + o * 3; /* max genlik */
  dlglr[o].dgenlik = -1; /* genligin degisim miktari */
  dlglr[o].sayac = 0;
  dlglr[o].periyot = k - o;
 }
}

void arkaplan_ilk_degerler(int yldz, int y, unsigned char fon, int tp, int t, int ust, int alt, int dlg, int d, int dust)
{ /* baslangic degeri fonksiyonlarinin tek fonksiyonda birlestirilmis hali */
 if(yldz) yldz_yap(y, fon);
 if(tp) { tepe_yap(t,ust,alt); svy.zemin = 1; }
 if(dlg) { dalga_yap(d, dust); svy.zemin = 2; }
 if(!tp && !dlg) svy.zemin = 0;
}

void yldzlr(unsigned char fon)
{  /* yildizli fonu kaydirir yeni yildiz ekler ve olanlarin rengini degistirir */
 int o;

 if(!yldz.sayac)
 {
  yldz.sayac = yldz.periyot;

  /* dizinin elemanlarini bir sola kaydir */
  for(o = 1; o < 320; o++) { yldz.dizi[o - 1] = yldz.dizi[o]; yldz.renk[o - 1] = yldz.renk[o]; }

  /* en sagdaki dizi elemanini yarat */
  yldz.dizi[319] = rand() % 199;
  yldz.renk[319] = (!(rand() % yldz.yogunluk)) ? 40 + (rand() % 23) : fon;

  /* diziyi bastan sona tara ve yildiz olan elemanlarin renk kaydirmasini yap */
  if(oyuncu.x <= ex2)
   for(o = 0; o < 320; o++) { if(yldz.renk[o] > 40) yldz.renk[o]--; if(yldz.renk[o] == 40) yldz.renk[o] = 63; }
 } else yldz.sayac--;
}

int sgn(int say) /* isaret fonksiyonu */
{
 if(say < 0) return -1;
 else if(say > 0) return 1;
 else return 0;
}

void tepeler(int t, int bas) /* kayan tepeler yaratir */
{ /* Bresenham'in cizgi algoritmasindan uyarlanmistir */
 int o;

 if(!tplr[t].sayac)
 {
  /* bas != 0 ise beklemeden ilk ekran degerleri icin diziyi doldur */
  tplr[t].sayac = (bas) ? 0 : tplr[t].periyot;

  for(o = 1; o < 320; o++) tplr[t].dizi[o - 1] = tplr[t].dizi[o];

  if(!tplr[t].i)
  {
   tplr[t].c = 319 + (rand() % 10);

   tplr[t].d = (rand() % 2) ? tplr[t].b - ((rand() % 10) + 1) : tplr[t].b + ((rand() % 10) + 1);

   if(tplr[t].d < tplr[t].ust) tplr[t].d = tplr[t].ust + ((rand() % 10) + 1);
   if(tplr[t].d > tplr[t].alt) tplr[t].d = tplr[t].alt - ((rand() % 10) + 1);

   tplr[t].u = tplr[t].c - tplr[t].a;
   tplr[t].v = tplr[t].d - tplr[t].b;

   tplr[t].d1x = sgn(tplr[t].u);
   tplr[t].d1y = sgn(tplr[t].v);

   tplr[t].e = abs(tplr[t].u);
   tplr[t].f = abs(tplr[t].v);

   if (tplr[t].e <= tplr[t].f)
   {
    tplr[t].d2x = 0;
    tplr[t].d2y = tplr[t].d1y;
    tplr[t].m = tplr[t].f;
    tplr[t].n = tplr[t].e;
   }
   else
   {
    tplr[t].d2x = tplr[t].d1x;
    tplr[t].d2y = 0;
    tplr[t].m = tplr[t].e;
    tplr[t].n = tplr[t].f;
   }

   tplr[t].s = tplr[t].m >> 1;
  }

  if(tplr[t].i <= tplr[t].m)
  {
   tplr[t].dizi[319] = tplr[t].b;
   tplr[t].s += tplr[t].n;
   if (tplr[t].s >= tplr[t].m)
   {
    tplr[t].s -= tplr[t].m;
    tplr[t].a += tplr[t].d1x;
    tplr[t].b += tplr[t].d1y;
   }
   else
   {
    tplr[t].a += tplr[t].d2x;
    tplr[t].b += tplr[t].d2y;
   }

   tplr[t].i++;
  }
  else tplr[t].i = 0;
 }
 else tplr[t].sayac--;
}

void dalgalar(int d) /* genligi azalip artan sabit boyda dalgalar yaratir */
{
 int o;

 if(!dlglr[d].sayac)
 {
  dlglr[d].sayac = dlglr[d].periyot;

  /* dizinin ilk elemaninin aci degerini belirle */
  dlglr[d].a = dlglr[d].ailk += dlglr[d].da;
  if(dlglr[d].ailk >= 360) dlglr[d].ailk = 0;

  dlglr[d].genlik += dlglr[d].dgenlik;

  /* dalga dibe ulastiysa cikmaya tepeye ulastiysa inmeye baslasin */
  if(dlglr[d].genlik == -dlglr[d].sgenlik) dlglr[d].dgenlik = 1;
  else if(dlglr[d].genlik == dlglr[d].sgenlik) dlglr[d].dgenlik = -1;

  /* belirlenen degerlere gore dalga dizisini bastan sona doldur */
  for(o = 0; o < 320; o++)
   dlglr[d].dizi[o] = dlglr[d].y + dlglr[d].genlik * sin[(dlglr[d].a++ * dlglr[d].dalgaboyu) % 360];
 }
 else dlglr[d].sayac--;
}