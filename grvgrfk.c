void gorev1_grafikler(unsigned char *kare[])
{ /* 1. gorev icin ortak grafiklere hafiza alani taksimi */
 int o;

 for(o = 0; o < 12; o++) kare[o] = (unsigned char *) calloc(901, 1); /* 12 */
 for(o = o; o < 18; o++) kare[o] = (unsigned char *) calloc(123, 1); /*  6 */
 for(o = o; o < 26; o++) kare[o] = (unsigned char *) calloc(83, 1);  /*  8 */
 for(o = o; o < 30; o++) kare[o] = (unsigned char *) calloc(66, 1);  /*  4 */
 for(o = o; o < 32; o++) kare[o] = (unsigned char *) calloc( 6, 1);  /*  2 */
 for(o = o; o < 44; o++) kare[o] = (unsigned char *) calloc(27, 1);  /* 12 */
 for(o = o; o < 46; o++) kare[o] = (unsigned char *) calloc(30, 1);  /*  3 */
 for(o = o; o < 51; o++) kare[o] = (unsigned char *) calloc(452, 1); /*  4 */
 kare[51] = (unsigned char *) calloc(650, 1);
 kare[52] = (unsigned char *) calloc(876, 1);
 kare[53] = (unsigned char *) calloc(632, 1);
 kare[54] = (unsigned char *) calloc(674, 1);
 kare[55] = (unsigned char *) calloc(582, 1);
 kare[56] = (unsigned char *) calloc(534, 1);
 kare[57] = (unsigned char *) calloc(542, 1);
 kare[58] = (unsigned char *) calloc(347, 1);
 kare[59] = (unsigned char *) calloc(572, 1);
 kare[60] = (unsigned char *) calloc(1294, 1);
 for(o = 61; o < 65; o++) kare[o] = (unsigned char *) calloc(3, 1);
 for(o = o; o < 77; o++) kare[o] = (unsigned char *) calloc(202, 1);
 for(o = o; o < 85; o++) kare[o] = (unsigned char *) calloc(27, 1);
 for(o = o; o < 89; o++) kare[o] = (unsigned char *) calloc(227, 1);
 for(o = o; o < 99; o++) kare[o] = (unsigned char *) calloc(223, 1);
 for(o = o; o < 114; o++) kare[o] = (unsigned char *) calloc(443, 1);
 kare[114] = (unsigned char *) calloc(4370, 1);
 kare[115] = (unsigned char *) calloc(1532, 1);
 for(o = 116; o < 120; o++) kare[o] = (unsigned char *) calloc(158, 1);
 kare[120] = (unsigned char *) calloc(102, 1);
 for(o = 121; o < 129; o++) kare[o] = (unsigned char *) calloc(227, 1);
 kare[129] = (unsigned char *) calloc(3, 1);

 XCPyi_bellege_oku("kaynak01.xcp", RGB, SNL);

/* buyuk patlama */
 kare_oku(1,1,31,29,SNL,kare[0]);
 kare_oku(33,1,63,29,SNL,kare[1]);
 kare_oku(65,1,95,29,SNL,kare[2]);
 kare_oku(97,1,127,29,SNL,kare[3]);
 kare_oku(129,1,159,29,SNL,kare[4]);
 kare_oku(161,1,191,29,SNL,kare[5]);
 kare_oku(1,31,31,59,SNL,kare[6]);
 kare_oku(33,31,63,59,SNL,kare[7]);
 kare_oku(65,31,95,59,SNL,kare[8]);
 kare_oku(97,31,127,59,SNL,kare[9]);
 kare_oku(129,31,159,59,SNL,kare[10]);
 kare_oku(161,31,191,59,SNL,kare[11]);
/* kor mayin */
 kare_oku(193,1,203,11,SNL,kare[12]);
 kare_oku(205,1,215,11,SNL,kare[13]);
 kare_oku(217,1,227,11,SNL,kare[14]);
 kare_oku(229,1,239,11,SNL,kare[15]);
 kare_oku(241,1,251,11,SNL,kare[16]);
 kare_oku(253,1,263,11,SNL,kare[17]);
/* kirmizi patlama */
 kare_oku(193,13,201,21,SNL,kare[18]);
 kare_oku(203,13,211,21,SNL,kare[19]);
 kare_oku(213,13,221,21,SNL,kare[20]);
 kare_oku(223,13,231,21,SNL,kare[21]);
/* kucuk patlama */
 kare_oku(193,23,201,31,SNL,kare[22]);
 kare_oku(203,23,211,31,SNL,kare[23]);
 kare_oku(213,23,221,31,SNL,kare[24]);
 kare_oku(223,23,231,31,SNL,kare[25]);
/* gudumlu mayin */
 kare_oku(193,51,200,58,SNL,kare[26]);
 kare_oku(202,51,209,58,SNL,kare[27]);
 kare_oku(211,51,218,58,SNL,kare[28]);
 kare_oku(220,51,227,58,SNL,kare[29]);
/* mermi */
 kare_oku(229,43,230,44,SNL,kare[30]);
 kare_oku(232,43,233,44,SNL,kare[31]);
/* mermi kivilcimi */
 kare_oku(193,39,197,43,SNL,kare[32]);
 kare_oku(193,45,197,49,SNL,kare[33]);
 kare_oku(199,45,203,49,SNL,kare[34]);
 kare_oku(199,39,203,43,SNL,kare[35]);
/* kirmizi simsek */
 kare_oku(205,39,209,43,SNL,kare[36]);
 kare_oku(211,39,215,43,SNL,kare[37]);
 kare_oku(217,39,221,43,SNL,kare[38]);
 kare_oku(223,39,227,43,SNL,kare[39]);
/* ates topu */
 kare_oku(205,45,209,49,SNL,kare[40]);
 kare_oku(211,45,215,49,SNL,kare[41]);
 kare_oku(217,45,221,49,SNL,kare[42]);
 kare_oku(223,45,227,49,SNL,kare[43]);
/* roket */
 kare_oku(229,46,235,49,SNL,kare[44]);
 kare_oku(229,51,235,54,SNL,kare[45]);
 kare_oku(229,56,235,59,SNL,kare[46]);
/* kamikaze */
 kare_oku(40,85,69,99,SNL,kare[47]);
 kare_oku(71,85,100,99,SNL,kare[48]);
 kare_oku(102,85,131,99,SNL,kare[49]);
 kare_oku(133,85,162,99,SNL,kare[50]);
/* 2 namlulu no 3 */
 kare_oku(1,61,27,84,SNL,kare[51]);
/* 3 namlulu no 1 */
 kare_oku(29,61,66,83,SNL,kare[52]);
/* 2 namlulu no 1 */
 kare_oku(68,61,97,81,SNL,kare[53]);
/* 3 namlulu no 2 */
 kare_oku(99,61,130,81,SNL,kare[54]);
/* 2 namlulu no 2 */
 kare_oku(133,62,161,81,SNL,kare[55]);
/* 1 namlulu no 3 */
 kare_oku(1,86,38,99,SNL,kare[56]);
/* mayinci */
 kare_oku(1,101,30,118,SNL,kare[57]);
/* 1 namlulu no 1 */
 kare_oku(32,103,54,117,SNL,kare[58]);
/* 1 namlulu no 2 */
 kare_oku(56,103,93,117,SNL,kare[59]);
/* 5 namlulu */
 kare_oku(95,101,162,119,SNL,kare[60]);
/* kalkan tozu */
 kare_oku(229,39,229,39,SNL,kare[61]);
 kare_oku(231,39,231,39,SNL,kare[62]);
 kare_oku(231,41,231,41,SNL,kare[63]);
 kare_oku(229,41,229,41,SNL,kare[64]);
/* bonus 1 */
 kare_oku(299,1,318,10,SNL,kare[65]);
 kare_oku(278,1,297,10,SNL,kare[66]);
 kare_oku(278,12,297,21,SNL,kare[67]);
 kare_oku(278,23,297,32,SNL,kare[68]);
/* bonus 1 bitis */
 kare_oku(299,1,318,10,SNL,kare[69]);
 kare_oku(299,12,318,21,SNL,kare[70]);
 kare_oku(299,23,318,32,SNL,kare[71]);
 kare_oku(299,34,318,43,SNL,kare[72]);
 kare_oku(299,45,318,54,SNL,kare[73]);
 kare_oku(299,56,318,65,SNL,kare[74]);
 kare_oku(299,67,318,76,SNL,kare[75]);
 kare_oku(299,78,318,87,SNL,kare[76]);
/* bonus 0 */
 kare_oku(266,1,270,5,SNL,kare[77]);
 kare_oku(266,7,270,11,SNL,kare[78]);
 kare_oku(266,13,270,17,SNL,kare[79]);
 kare_oku(266,19,270,23,SNL,kare[80]);
 kare_oku(272,1,276,5,SNL,kare[81]);
 kare_oku(272,7,276,11,SNL,kare[82]);
 kare_oku(272,13,276,17,SNL,kare[83]);
 kare_oku(272,19,276,23,SNL,kare[84]);
/* 1 namlulu hedefli */
 kare_oku(164,61,178,75,SNL,kare[85]);
 kare_oku(164,77,178,91,SNL,kare[86]);
 kare_oku(180,61,194,75,SNL,kare[87]);
 kare_oku(180,77,194,91,SNL,kare[88]);
/* bonus 3 */
 kare_oku(306,89,318,105,SNL,kare[89]);
 kare_oku(292,89,304,105,SNL,kare[90]);
 kare_oku(292,107,304,123,SNL,kare[91]);
 kare_oku(292,125,304,141,SNL,kare[92]);
/* bonus 3 bitis */
 kare_oku(306,89,318,105,SNL,kare[93]);
 kare_oku(306,107,318,123,SNL,kare[94]);
 kare_oku(306,125,318,141,SNL,kare[95]);
 kare_oku(306,143,318,159,SNL,kare[96]);
 kare_oku(306,161,318,177,SNL,kare[97]);
 kare_oku(306,179,318,195,SNL,kare[98]);
/* bonus 2 */
 kare_oku(196,156,216,176,SNL,kare[99]);
 kare_oku(218,156,238,176,SNL,kare[100]);
 kare_oku(240,156,260,176,SNL,kare[101]);
 kare_oku(262,156,282,176,SNL,kare[102]);
 kare_oku(284,156,304,176,SNL,kare[103]);
 kare_oku(262,156,282,176,SNL,kare[104]);
 kare_oku(240,156,260,176,SNL,kare[105]);
 kare_oku(218,156,238,176,SNL,kare[106]);
/* bonus 2 bitis */
 kare_oku(240,156,260,176,SNL,kare[107]);
 kare_oku(174,178,194,198,SNL,kare[108]);
 kare_oku(196,178,216,198,SNL,kare[109]);
 kare_oku(218,178,238,198,SNL,kare[110]);
 kare_oku(240,178,260,198,SNL,kare[111]);
 kare_oku(262,178,282,198,SNL,kare[112]);
 kare_oku(284,178,304,198,SNL,kare[113]);
/* bsc */
 kare_oku(196,61,273,116,SNL,kare[114]);
/* balina */
 kare_oku(246,118,290,151,SNL,kare[115]);
/* bocek */
 kare_oku(164,93,176,104,SNL,kare[116]);
 kare_oku(178,93,190,104,SNL,kare[117]);
 kare_oku(164,106,176,117,SNL,kare[118]);
 kare_oku(178,106,190,117,SNL,kare[119]);
/* yilan parcasi */
 kare_oku(294,144,303,153,SNL,kare[120]);
/* yilan basi */
 kare_oku(275,38,289,52,SNL,kare[121]);
 kare_oku(275,54,289,68,SNL,kare[122]);
 kare_oku(275,70,289,84,SNL,kare[123]);
 kare_oku(275,86,289,100,SNL,kare[124]);
 kare_oku(275,102,289,116,SNL,kare[125]);
 kare_oku(275,86,289,100,SNL,kare[126]);
 kare_oku(275,70,289,84,SNL,kare[127]);
 kare_oku(275,54,289,68,SNL,kare[128]);
/* kan damlasi */
 kare_oku(302,99,302,99,SNL,kare[129]);
}

grafikleri_sil(unsigned char *kare[], int s)
{
 int o;

 for(o = 0; o < s; o++) free(kare[o]);
}