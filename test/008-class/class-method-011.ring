
package main

import {
	fmt;
	debug;
}


typedef class Job {
    var bool    Running;
    var int     JobID;
    var double  Score;

    fn Action() {
        var int  local_int_value_0    = 0;
	var int  local_int_value_1    = 1;
	var int  local_int_value_2    = 2;
	var int  local_int_value_3    = 3;
	var int  local_int_value_4    = 4;
	var int  local_int_value_5    = 5;
	var int  local_int_value_6    = 6;
	var int  local_int_value_7    = 7;
	var int  local_int_value_8    = 8;
	var int  local_int_value_9    = 9;
	var int  local_int_value_10   = 10;
	var int  local_int_value_11   = 11;
	var int  local_int_value_12   = 12;
	var int  local_int_value_13   = 13;
	var int  local_int_value_14   = 14;
	var int  local_int_value_15   = 15;
	var int  local_int_value_16   = 16;
	var int  local_int_value_17   = 17;
	var int  local_int_value_18   = 18;
	var int  local_int_value_19   = 19;
	var int  local_int_value_20   = 20;
	var int  local_int_value_21   = 21;
	var int  local_int_value_22   = 22;
	var int  local_int_value_23   = 23;
	var int  local_int_value_24   = 24;
	var int  local_int_value_25   = 25;
	var int  local_int_value_26   = 26;
	var int  local_int_value_27   = 27;
	var int  local_int_value_28   = 28;
	var int  local_int_value_29   = 29;
	var int  local_int_value_30   = 30;
	var int  local_int_value_31   = 31;
	var int  local_int_value_32   = 32;
	var int  local_int_value_33   = 33;
	var int  local_int_value_34   = 34;
	var int  local_int_value_35   = 35;
	var int  local_int_value_36   = 36;
	var int  local_int_value_37   = 37;
	var int  local_int_value_38   = 38;
	var int  local_int_value_39   = 39;
	var int  local_int_value_40   = 40;
	var int  local_int_value_41   = 41;
	var int  local_int_value_42   = 42;
	var int  local_int_value_43   = 43;
	var int  local_int_value_44   = 44;
	var int  local_int_value_45   = 45;
	var int  local_int_value_46   = 46;
	var int  local_int_value_47   = 47;
	var int  local_int_value_48   = 48;
	var int  local_int_value_49   = 49;
	var int  local_int_value_50   = 50;
	var int  local_int_value_51   = 51;
	var int  local_int_value_52   = 52;
	var int  local_int_value_53   = 53;
	var int  local_int_value_54   = 54;
	var int  local_int_value_55   = 55;
	var int  local_int_value_56   = 56;
	var int  local_int_value_57   = 57;
	var int  local_int_value_58   = 58;
	var int  local_int_value_59   = 59;
	var int  local_int_value_60   = 60;
	var int  local_int_value_61   = 61;
	var int  local_int_value_62   = 62;
	var int  local_int_value_63   = 63;
	var int  local_int_value_64   = 64;
	var int  local_int_value_65   = 65;
	var int  local_int_value_66   = 66;
	var int  local_int_value_67   = 67;
	var int  local_int_value_68   = 68;
	var int  local_int_value_69   = 69;
	var int  local_int_value_70   = 70;
	var int  local_int_value_71   = 71;
	var int  local_int_value_72   = 72;
	var int  local_int_value_73   = 73;
	var int  local_int_value_74   = 74;
	var int  local_int_value_75   = 75;
	var int  local_int_value_76   = 76;
	var int  local_int_value_77   = 77;
	var int  local_int_value_78   = 78;
	var int  local_int_value_79   = 79;
	var int  local_int_value_80   = 80;
	var int  local_int_value_81   = 81;
	var int  local_int_value_82   = 82;
	var int  local_int_value_83   = 83;
	var int  local_int_value_84   = 84;
	var int  local_int_value_85   = 85;
	var int  local_int_value_86   = 86;
	var int  local_int_value_87   = 87;
	var int  local_int_value_88   = 88;
	var int  local_int_value_89   = 89;
	var int  local_int_value_90   = 90;
	var int  local_int_value_91   = 91;
	var int  local_int_value_92   = 92;
	var int  local_int_value_93   = 93;
	var int  local_int_value_94   = 94;
	var int  local_int_value_95   = 95;
	var int  local_int_value_96   = 96;
	var int  local_int_value_97   = 97;
	var int  local_int_value_98   = 98;
	var int  local_int_value_99   = 99;
	var int  local_int_value_100  = 100;
	var int  local_int_value_101  = 101;
	var int  local_int_value_102  = 102;
	var int  local_int_value_103  = 103;
	var int  local_int_value_104  = 104;
	var int  local_int_value_105  = 105;
	var int  local_int_value_106  = 106;
	var int  local_int_value_107  = 107;
	var int  local_int_value_108  = 108;
	var int  local_int_value_109  = 109;
	var int  local_int_value_110  = 110;
	var int  local_int_value_111  = 111;
	var int  local_int_value_112  = 112;
	var int  local_int_value_113  = 113;
	var int  local_int_value_114  = 114;
	var int  local_int_value_115  = 115;
	var int  local_int_value_116  = 116;
	var int  local_int_value_117  = 117;
	var int  local_int_value_118  = 118;
	var int  local_int_value_119  = 119;
	var int  local_int_value_120  = 120;
	var int  local_int_value_121  = 121;
	var int  local_int_value_122  = 122;
	var int  local_int_value_123  = 123;
	var int  local_int_value_124  = 124;
	var int  local_int_value_125  = 125;
	var int  local_int_value_126  = 126;
	var int  local_int_value_127  = 127;
	var int  local_int_value_128  = 128;
	var int  local_int_value_129  = 129;
	var int  local_int_value_130  = 130;
	var int  local_int_value_131  = 131;
	var int  local_int_value_132  = 132;
	var int  local_int_value_133  = 133;
	var int  local_int_value_134  = 134;
	var int  local_int_value_135  = 135;
	var int  local_int_value_136  = 136;
	var int  local_int_value_137  = 137;
	var int  local_int_value_138  = 138;
	var int  local_int_value_139  = 139;
	var int  local_int_value_140  = 140;
	var int  local_int_value_141  = 141;
	var int  local_int_value_142  = 142;
	var int  local_int_value_143  = 143;
	var int  local_int_value_144  = 144;
	var int  local_int_value_145  = 145;
	var int  local_int_value_146  = 146;
	var int  local_int_value_147  = 147;
	var int  local_int_value_148  = 148;
	var int  local_int_value_149  = 149;
	var int  local_int_value_150  = 150;
	var int  local_int_value_151  = 151;
	var int  local_int_value_152  = 152;
	var int  local_int_value_153  = 153;
	var int  local_int_value_154  = 154;
	var int  local_int_value_155  = 155;
	var int  local_int_value_156  = 156;
	var int  local_int_value_157  = 157;
	var int  local_int_value_158  = 158;
	var int  local_int_value_159  = 159;
	var int  local_int_value_160  = 160;
	var int  local_int_value_161  = 161;
	var int  local_int_value_162  = 162;
	var int  local_int_value_163  = 163;
	var int  local_int_value_164  = 164;
	var int  local_int_value_165  = 165;
	var int  local_int_value_166  = 166;
	var int  local_int_value_167  = 167;
	var int  local_int_value_168  = 168;
	var int  local_int_value_169  = 169;
	var int  local_int_value_170  = 170;
	var int  local_int_value_171  = 171;
	var int  local_int_value_172  = 172;
	var int  local_int_value_173  = 173;
	var int  local_int_value_174  = 174;
	var int  local_int_value_175  = 175;
	var int  local_int_value_176  = 176;
	var int  local_int_value_177  = 177;
	var int  local_int_value_178  = 178;
	var int  local_int_value_179  = 179;
	var int  local_int_value_180  = 180;
	var int  local_int_value_181  = 181;
	var int  local_int_value_182  = 182;
	var int  local_int_value_183  = 183;
	var int  local_int_value_184  = 184;
	var int  local_int_value_185  = 185;
	var int  local_int_value_186  = 186;
	var int  local_int_value_187  = 187;
	var int  local_int_value_188  = 188;
	var int  local_int_value_189  = 189;
	var int  local_int_value_190  = 190;
	var int  local_int_value_191  = 191;
	var int  local_int_value_192  = 192;
	var int  local_int_value_193  = 193;
	var int  local_int_value_194  = 194;
	var int  local_int_value_195  = 195;
	var int  local_int_value_196  = 196;
	var int  local_int_value_197  = 197;
	var int  local_int_value_198  = 198;
	var int  local_int_value_199  = 199;
	var int  local_int_value_200  = 200;
	var int  local_int_value_201  = 201;
	var int  local_int_value_202  = 202;
	var int  local_int_value_203  = 203;
	var int  local_int_value_204  = 204;
	var int  local_int_value_205  = 205;
	var int  local_int_value_206  = 206;
	var int  local_int_value_207  = 207;
	var int  local_int_value_208  = 208;
	var int  local_int_value_209  = 209;
	var int  local_int_value_210  = 210;
	var int  local_int_value_211  = 211;
	var int  local_int_value_212  = 212;
	var int  local_int_value_213  = 213;
	var int  local_int_value_214  = 214;
	var int  local_int_value_215  = 215;
	var int  local_int_value_216  = 216;
	var int  local_int_value_217  = 217;
	var int  local_int_value_218  = 218;
	var int  local_int_value_219  = 219;
	var int  local_int_value_220  = 220;
	var int  local_int_value_221  = 221;
	var int  local_int_value_222  = 222;
	var int  local_int_value_223  = 223;
	var int  local_int_value_224  = 224;
	var int  local_int_value_225  = 225;
	var int  local_int_value_226  = 226;
	var int  local_int_value_227  = 227;
	var int  local_int_value_228  = 228;
	var int  local_int_value_229  = 229;
	var int  local_int_value_230  = 230;
	var int  local_int_value_231  = 231;
	var int  local_int_value_232  = 232;
	var int  local_int_value_233  = 233;
	var int  local_int_value_234  = 234;
	var int  local_int_value_235  = 235;
	var int  local_int_value_236  = 236;
	var int  local_int_value_237  = 237;
	var int  local_int_value_238  = 238;
	var int  local_int_value_239  = 239;
	var int  local_int_value_240  = 240;
	var int  local_int_value_241  = 241;
	var int  local_int_value_242  = 242;
	var int  local_int_value_243  = 243;
	var int  local_int_value_244  = 244;
	var int  local_int_value_245  = 245;
	var int  local_int_value_246  = 246;
	var int  local_int_value_247  = 247;
	var int  local_int_value_248  = 248;
	var int  local_int_value_249  = 249;
	var int  local_int_value_250  = 250;
	var int  local_int_value_251  = 251;
	var int  local_int_value_252  = 252;
	var int  local_int_value_253  = 253;


	debug::assert(local_int_value_0   == 0);
	debug::assert(local_int_value_1   == 1);
	debug::assert(local_int_value_2   == 2);
	debug::assert(local_int_value_3   == 3);
	debug::assert(local_int_value_4   == 4);
	debug::assert(local_int_value_5   == 5);
	debug::assert(local_int_value_6   == 6);
	debug::assert(local_int_value_7   == 7);
	debug::assert(local_int_value_8   == 8);
	debug::assert(local_int_value_9   == 9);
	debug::assert(local_int_value_10  == 10);
	debug::assert(local_int_value_11  == 11);
	debug::assert(local_int_value_12  == 12);
	debug::assert(local_int_value_13  == 13);
	debug::assert(local_int_value_14  == 14);
	debug::assert(local_int_value_15  == 15);
	debug::assert(local_int_value_16  == 16);
	debug::assert(local_int_value_17  == 17);
	debug::assert(local_int_value_18  == 18);
	debug::assert(local_int_value_19  == 19);
	debug::assert(local_int_value_20  == 20);
	debug::assert(local_int_value_21  == 21);
	debug::assert(local_int_value_22  == 22);
	debug::assert(local_int_value_23  == 23);
	debug::assert(local_int_value_24  == 24);
	debug::assert(local_int_value_25  == 25);
	debug::assert(local_int_value_26  == 26);
	debug::assert(local_int_value_27  == 27);
	debug::assert(local_int_value_28  == 28);
	debug::assert(local_int_value_29  == 29);
	debug::assert(local_int_value_30  == 30);
	debug::assert(local_int_value_31  == 31);
	debug::assert(local_int_value_32  == 32);
	debug::assert(local_int_value_33  == 33);
	debug::assert(local_int_value_34  == 34);
	debug::assert(local_int_value_35  == 35);
	debug::assert(local_int_value_36  == 36);
	debug::assert(local_int_value_37  == 37);
	debug::assert(local_int_value_38  == 38);
	debug::assert(local_int_value_39  == 39);
	debug::assert(local_int_value_40  == 40);
	debug::assert(local_int_value_41  == 41);
	debug::assert(local_int_value_42  == 42);
	debug::assert(local_int_value_43  == 43);
	debug::assert(local_int_value_44  == 44);
	debug::assert(local_int_value_45  == 45);
	debug::assert(local_int_value_46  == 46);
	debug::assert(local_int_value_47  == 47);
	debug::assert(local_int_value_48  == 48);
	debug::assert(local_int_value_49  == 49);
	debug::assert(local_int_value_50  == 50);
	debug::assert(local_int_value_51  == 51);
	debug::assert(local_int_value_52  == 52);
	debug::assert(local_int_value_53  == 53);
	debug::assert(local_int_value_54  == 54);
	debug::assert(local_int_value_55  == 55);
	debug::assert(local_int_value_56  == 56);
	debug::assert(local_int_value_57  == 57);
	debug::assert(local_int_value_58  == 58);
	debug::assert(local_int_value_59  == 59);
	debug::assert(local_int_value_60  == 60);
	debug::assert(local_int_value_61  == 61);
	debug::assert(local_int_value_62  == 62);
	debug::assert(local_int_value_63  == 63);
	debug::assert(local_int_value_64  == 64);
	debug::assert(local_int_value_65  == 65);
	debug::assert(local_int_value_66  == 66);
	debug::assert(local_int_value_67  == 67);
	debug::assert(local_int_value_68  == 68);
	debug::assert(local_int_value_69  == 69);
	debug::assert(local_int_value_70  == 70);
	debug::assert(local_int_value_71  == 71);
	debug::assert(local_int_value_72  == 72);
	debug::assert(local_int_value_73  == 73);
	debug::assert(local_int_value_74  == 74);
	debug::assert(local_int_value_75  == 75);
	debug::assert(local_int_value_76  == 76);
	debug::assert(local_int_value_77  == 77);
	debug::assert(local_int_value_78  == 78);
	debug::assert(local_int_value_79  == 79);
	debug::assert(local_int_value_80  == 80);
	debug::assert(local_int_value_81  == 81);
	debug::assert(local_int_value_82  == 82);
	debug::assert(local_int_value_83  == 83);
	debug::assert(local_int_value_84  == 84);
	debug::assert(local_int_value_85  == 85);
	debug::assert(local_int_value_86  == 86);
	debug::assert(local_int_value_87  == 87);
	debug::assert(local_int_value_88  == 88);
	debug::assert(local_int_value_89  == 89);
	debug::assert(local_int_value_90  == 90);
	debug::assert(local_int_value_91  == 91);
	debug::assert(local_int_value_92  == 92);
	debug::assert(local_int_value_93  == 93);
	debug::assert(local_int_value_94  == 94);
	debug::assert(local_int_value_95  == 95);
	debug::assert(local_int_value_96  == 96);
	debug::assert(local_int_value_97  == 97);
	debug::assert(local_int_value_98  == 98);
	debug::assert(local_int_value_99  == 99);
	debug::assert(local_int_value_100 == 100);
	debug::assert(local_int_value_101 == 101);
	debug::assert(local_int_value_102 == 102);
	debug::assert(local_int_value_103 == 103);
	debug::assert(local_int_value_104 == 104);
	debug::assert(local_int_value_105 == 105);
	debug::assert(local_int_value_106 == 106);
	debug::assert(local_int_value_107 == 107);
	debug::assert(local_int_value_108 == 108);
	debug::assert(local_int_value_109 == 109);
	debug::assert(local_int_value_110 == 110);
	debug::assert(local_int_value_111 == 111);
	debug::assert(local_int_value_112 == 112);
	debug::assert(local_int_value_113 == 113);
	debug::assert(local_int_value_114 == 114);
	debug::assert(local_int_value_115 == 115);
	debug::assert(local_int_value_116 == 116);
	debug::assert(local_int_value_117 == 117);
	debug::assert(local_int_value_118 == 118);
	debug::assert(local_int_value_119 == 119);
	debug::assert(local_int_value_120 == 120);
	debug::assert(local_int_value_121 == 121);
	debug::assert(local_int_value_122 == 122);
	debug::assert(local_int_value_123 == 123);
	debug::assert(local_int_value_124 == 124);
	debug::assert(local_int_value_125 == 125);
	debug::assert(local_int_value_126 == 126);
	debug::assert(local_int_value_127 == 127);
	debug::assert(local_int_value_128 == 128);
	debug::assert(local_int_value_129 == 129);
	debug::assert(local_int_value_130 == 130);
	debug::assert(local_int_value_131 == 131);
	debug::assert(local_int_value_132 == 132);
	debug::assert(local_int_value_133 == 133);
	debug::assert(local_int_value_134 == 134);
	debug::assert(local_int_value_135 == 135);
	debug::assert(local_int_value_136 == 136);
	debug::assert(local_int_value_137 == 137);
	debug::assert(local_int_value_138 == 138);
	debug::assert(local_int_value_139 == 139);
	debug::assert(local_int_value_140 == 140);
	debug::assert(local_int_value_141 == 141);
	debug::assert(local_int_value_142 == 142);
	debug::assert(local_int_value_143 == 143);
	debug::assert(local_int_value_144 == 144);
	debug::assert(local_int_value_145 == 145);
	debug::assert(local_int_value_146 == 146);
	debug::assert(local_int_value_147 == 147);
	debug::assert(local_int_value_148 == 148);
	debug::assert(local_int_value_149 == 149);
	debug::assert(local_int_value_150 == 150);
	debug::assert(local_int_value_151 == 151);
	debug::assert(local_int_value_152 == 152);
	debug::assert(local_int_value_153 == 153);
	debug::assert(local_int_value_154 == 154);
	debug::assert(local_int_value_155 == 155);
	debug::assert(local_int_value_156 == 156);
	debug::assert(local_int_value_157 == 157);
	debug::assert(local_int_value_158 == 158);
	debug::assert(local_int_value_159 == 159);
	debug::assert(local_int_value_160 == 160);
	debug::assert(local_int_value_161 == 161);
	debug::assert(local_int_value_162 == 162);
	debug::assert(local_int_value_163 == 163);
	debug::assert(local_int_value_164 == 164);
	debug::assert(local_int_value_165 == 165);
	debug::assert(local_int_value_166 == 166);
	debug::assert(local_int_value_167 == 167);
	debug::assert(local_int_value_168 == 168);
	debug::assert(local_int_value_169 == 169);
	debug::assert(local_int_value_170 == 170);
	debug::assert(local_int_value_171 == 171);
	debug::assert(local_int_value_172 == 172);
	debug::assert(local_int_value_173 == 173);
	debug::assert(local_int_value_174 == 174);
	debug::assert(local_int_value_175 == 175);
	debug::assert(local_int_value_176 == 176);
	debug::assert(local_int_value_177 == 177);
	debug::assert(local_int_value_178 == 178);
	debug::assert(local_int_value_179 == 179);
	debug::assert(local_int_value_180 == 180);
	debug::assert(local_int_value_181 == 181);
	debug::assert(local_int_value_182 == 182);
	debug::assert(local_int_value_183 == 183);
	debug::assert(local_int_value_184 == 184);
	debug::assert(local_int_value_185 == 185);
	debug::assert(local_int_value_186 == 186);
	debug::assert(local_int_value_187 == 187);
	debug::assert(local_int_value_188 == 188);
	debug::assert(local_int_value_189 == 189);
	debug::assert(local_int_value_190 == 190);
	debug::assert(local_int_value_191 == 191);
	debug::assert(local_int_value_192 == 192);
	debug::assert(local_int_value_193 == 193);
	debug::assert(local_int_value_194 == 194);
	debug::assert(local_int_value_195 == 195);
	debug::assert(local_int_value_196 == 196);
	debug::assert(local_int_value_197 == 197);
	debug::assert(local_int_value_198 == 198);
	debug::assert(local_int_value_199 == 199);
	debug::assert(local_int_value_200 == 200);
	debug::assert(local_int_value_201 == 201);
	debug::assert(local_int_value_202 == 202);
	debug::assert(local_int_value_203 == 203);
	debug::assert(local_int_value_204 == 204);
	debug::assert(local_int_value_205 == 205);
	debug::assert(local_int_value_206 == 206);
	debug::assert(local_int_value_207 == 207);
	debug::assert(local_int_value_208 == 208);
	debug::assert(local_int_value_209 == 209);
	debug::assert(local_int_value_210 == 210);
	debug::assert(local_int_value_211 == 211);
	debug::assert(local_int_value_212 == 212);
	debug::assert(local_int_value_213 == 213);
	debug::assert(local_int_value_214 == 214);
	debug::assert(local_int_value_215 == 215);
	debug::assert(local_int_value_216 == 216);
	debug::assert(local_int_value_217 == 217);
	debug::assert(local_int_value_218 == 218);
	debug::assert(local_int_value_219 == 219);
	debug::assert(local_int_value_220 == 220);
	debug::assert(local_int_value_221 == 221);
	debug::assert(local_int_value_222 == 222);
	debug::assert(local_int_value_223 == 223);
	debug::assert(local_int_value_224 == 224);
	debug::assert(local_int_value_225 == 225);
	debug::assert(local_int_value_226 == 226);
	debug::assert(local_int_value_227 == 227);
	debug::assert(local_int_value_228 == 228);
	debug::assert(local_int_value_229 == 229);
	debug::assert(local_int_value_230 == 230);
	debug::assert(local_int_value_231 == 231);
	debug::assert(local_int_value_232 == 232);
	debug::assert(local_int_value_233 == 233);
	debug::assert(local_int_value_234 == 234);
	debug::assert(local_int_value_235 == 235);
	debug::assert(local_int_value_236 == 236);
	debug::assert(local_int_value_237 == 237);
	debug::assert(local_int_value_238 == 238);
	debug::assert(local_int_value_239 == 239);
	debug::assert(local_int_value_240 == 240);
	debug::assert(local_int_value_241 == 241);
	debug::assert(local_int_value_242 == 242);
	debug::assert(local_int_value_243 == 243);
	debug::assert(local_int_value_244 == 244);
	debug::assert(local_int_value_245 == 245);
	debug::assert(local_int_value_246 == 246);
	debug::assert(local_int_value_247 == 247);
	debug::assert(local_int_value_248 == 248);
	debug::assert(local_int_value_249 == 249);
	debug::assert(local_int_value_250 == 250);
	debug::assert(local_int_value_251 == 251);
	debug::assert(local_int_value_252 == 252);
	debug::assert(local_int_value_253 == 253);

    }
}

global {
    var Job job_0;
}

// TestDetail: 测试method中的局部变量为255

fn main() {
    job_0.Action();
}