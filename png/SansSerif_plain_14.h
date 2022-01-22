// Created by http://oleddisplay.squix.ch/ Consider a donation
// In case of problems make sure that you are using the font file with the correct version!
const char SansSerif_plain_14[] PROGMEM = {
	0x0E, // Width: 14
	0x11, // Height: 17
	0x20, // First Char: 32
	0xE0, // Numbers of Chars: 224

	// Jump Table:
	0xFF, 0xFF, 0x00, 0x04,  // 32:65535
	0x00, 0x00, 0x08, 0x05,  // 33:0
	0x00, 0x08, 0x0A, 0x05,  // 34:8
	0x00, 0x12, 0x1F, 0x0C,  // 35:18
	0x00, 0x31, 0x17, 0x09,  // 36:49
	0x00, 0x48, 0x23, 0x0D,  // 37:72
	0x00, 0x6B, 0x20, 0x0C,  // 38:107
	0x00, 0x8B, 0x04, 0x03,  // 39:139
	0x00, 0x8F, 0x0B, 0x05,  // 40:143
	0x00, 0x9A, 0x0B, 0x05,  // 41:154
	0x00, 0xA5, 0x13, 0x07,  // 42:165
	0x00, 0xB8, 0x1D, 0x0C,  // 43:184
	0x00, 0xD5, 0x08, 0x04,  // 44:213
	0x00, 0xDD, 0x0E, 0x05,  // 45:221
	0x00, 0xEB, 0x08, 0x04,  // 46:235
	0x00, 0xF3, 0x0D, 0x05,  // 47:243
	0x01, 0x00, 0x17, 0x09,  // 48:256
	0x01, 0x17, 0x14, 0x09,  // 49:279
	0x01, 0x2B, 0x14, 0x09,  // 50:299
	0x01, 0x3F, 0x17, 0x09,  // 51:319
	0x01, 0x56, 0x17, 0x09,  // 52:342
	0x01, 0x6D, 0x17, 0x09,  // 53:365
	0x01, 0x84, 0x17, 0x09,  // 54:388
	0x01, 0x9B, 0x16, 0x09,  // 55:411
	0x01, 0xB1, 0x17, 0x09,  // 56:433
	0x01, 0xC8, 0x17, 0x09,  // 57:456
	0x01, 0xDF, 0x08, 0x05,  // 58:479
	0x01, 0xE7, 0x08, 0x05,  // 59:487
	0x01, 0xEF, 0x1D, 0x0C,  // 60:495
	0x02, 0x0C, 0x1D, 0x0C,  // 61:524
	0x02, 0x29, 0x1D, 0x0C,  // 62:553
	0x02, 0x46, 0x10, 0x07,  // 63:582
	0x02, 0x56, 0x26, 0x0E,  // 64:598
	0x02, 0x7C, 0x1A, 0x09,  // 65:636
	0x02, 0x96, 0x1A, 0x0A,  // 66:662
	0x02, 0xB0, 0x1A, 0x0A,  // 67:688
	0x02, 0xCA, 0x1D, 0x0B,  // 68:714
	0x02, 0xE7, 0x17, 0x09,  // 69:743
	0x02, 0xFE, 0x13, 0x08,  // 70:766
	0x03, 0x11, 0x1D, 0x0B,  // 71:785
	0x03, 0x2E, 0x1A, 0x0A,  // 72:814
	0x03, 0x48, 0x05, 0x03,  // 73:840
	0x03, 0x4D, 0x05, 0x03,  // 74:845
	0x03, 0x52, 0x17, 0x09,  // 75:850
	0x03, 0x69, 0x14, 0x07,  // 76:873
	0x03, 0x7D, 0x20, 0x0C,  // 77:893
	0x03, 0x9D, 0x1A, 0x0A,  // 78:925
	0x03, 0xB7, 0x1D, 0x0B,  // 79:951
	0x03, 0xD4, 0x16, 0x09,  // 80:980
	0x03, 0xEA, 0x1D, 0x0B,  // 81:1002
	0x04, 0x07, 0x1A, 0x0A,  // 82:1031
	0x04, 0x21, 0x17, 0x09,  // 83:1057
	0x04, 0x38, 0x19, 0x09,  // 84:1080
	0x04, 0x51, 0x1A, 0x0A,  // 85:1105
	0x04, 0x6B, 0x19, 0x09,  // 86:1131
	0x04, 0x84, 0x25, 0x0D,  // 87:1156
	0x04, 0xA9, 0x1A, 0x09,  // 88:1193
	0x04, 0xC3, 0x19, 0x09,  // 89:1219
	0x04, 0xDC, 0x1A, 0x0A,  // 90:1244
	0x04, 0xF6, 0x0B, 0x05,  // 91:1270
	0x05, 0x01, 0x0E, 0x05,  // 92:1281
	0x05, 0x0F, 0x0B, 0x05,  // 93:1295
	0x05, 0x1A, 0x1C, 0x0C,  // 94:1306
	0x05, 0x36, 0x14, 0x07,  // 95:1334
	0x05, 0x4A, 0x0A, 0x07,  // 96:1354
	0x05, 0x54, 0x14, 0x08,  // 97:1364
	0x05, 0x68, 0x17, 0x09,  // 98:1384
	0x05, 0x7F, 0x14, 0x08,  // 99:1407
	0x05, 0x93, 0x17, 0x09,  // 100:1427
	0x05, 0xAA, 0x17, 0x09,  // 101:1450
	0x05, 0xC1, 0x0A, 0x04,  // 102:1473
	0x05, 0xCB, 0x17, 0x09,  // 103:1483
	0x05, 0xE2, 0x17, 0x09,  // 104:1506
	0x05, 0xF9, 0x05, 0x03,  // 105:1529
	0x05, 0xFE, 0x05, 0x03,  // 106:1534
	0x06, 0x03, 0x14, 0x08,  // 107:1539
	0x06, 0x17, 0x05, 0x03,  // 108:1559
	0x06, 0x1C, 0x23, 0x0D,  // 109:1564
	0x06, 0x3F, 0x17, 0x09,  // 110:1599
	0x06, 0x56, 0x17, 0x09,  // 111:1622
	0x06, 0x6D, 0x17, 0x09,  // 112:1645
	0x06, 0x84, 0x17, 0x09,  // 113:1668
	0x06, 0x9B, 0x0D, 0x05,  // 114:1691
	0x06, 0xA8, 0x14, 0x08,  // 115:1704
	0x06, 0xBC, 0x0E, 0x05,  // 116:1724
	0x06, 0xCA, 0x17, 0x09,  // 117:1738
	0x06, 0xE1, 0x13, 0x07,  // 118:1761
	0x06, 0xF4, 0x1C, 0x0B,  // 119:1780
	0x07, 0x10, 0x14, 0x07,  // 120:1808
	0x07, 0x24, 0x13, 0x07,  // 121:1828
	0x07, 0x37, 0x14, 0x08,  // 122:1847
	0x07, 0x4B, 0x14, 0x09,  // 123:1867
	0x07, 0x5F, 0x08, 0x05,  // 124:1887
	0x07, 0x67, 0x17, 0x09,  // 125:1895
	0x07, 0x7E, 0x1D, 0x0C,  // 126:1918
	0x07, 0x9B, 0x17, 0x08,  // 127:1947
	0x07, 0xB2, 0x17, 0x08,  // 128:1970
	0x07, 0xC9, 0x17, 0x08,  // 129:1993
	0x07, 0xE0, 0x17, 0x08,  // 130:2016
	0x07, 0xF7, 0x17, 0x08,  // 131:2039
	0x08, 0x0E, 0x17, 0x08,  // 132:2062
	0x08, 0x25, 0x17, 0x08,  // 133:2085
	0x08, 0x3C, 0x17, 0x08,  // 134:2108
	0x08, 0x53, 0x17, 0x08,  // 135:2131
	0x08, 0x6A, 0x17, 0x08,  // 136:2154
	0x08, 0x81, 0x17, 0x08,  // 137:2177
	0x08, 0x98, 0x17, 0x08,  // 138:2200
	0x08, 0xAF, 0x17, 0x08,  // 139:2223
	0x08, 0xC6, 0x17, 0x08,  // 140:2246
	0x08, 0xDD, 0x17, 0x08,  // 141:2269
	0x08, 0xF4, 0x17, 0x08,  // 142:2292
	0x09, 0x0B, 0x17, 0x08,  // 143:2315
	0x09, 0x22, 0x17, 0x08,  // 144:2338
	0x09, 0x39, 0x17, 0x08,  // 145:2361
	0x09, 0x50, 0x17, 0x08,  // 146:2384
	0x09, 0x67, 0x17, 0x08,  // 147:2407
	0x09, 0x7E, 0x17, 0x08,  // 148:2430
	0x09, 0x95, 0x17, 0x08,  // 149:2453
	0x09, 0xAC, 0x17, 0x08,  // 150:2476
	0x09, 0xC3, 0x17, 0x08,  // 151:2499
	0x09, 0xDA, 0x17, 0x08,  // 152:2522
	0x09, 0xF1, 0x17, 0x08,  // 153:2545
	0x0A, 0x08, 0x17, 0x08,  // 154:2568
	0x0A, 0x1F, 0x17, 0x08,  // 155:2591
	0x0A, 0x36, 0x17, 0x08,  // 156:2614
	0x0A, 0x4D, 0x17, 0x08,  // 157:2637
	0x0A, 0x64, 0x17, 0x08,  // 158:2660
	0x0A, 0x7B, 0x17, 0x08,  // 159:2683
	0xFF, 0xFF, 0x00, 0x04,  // 160:65535
	0x0A, 0x92, 0x08, 0x05,  // 161:2706
	0x0A, 0x9A, 0x14, 0x09,  // 162:2714
	0x0A, 0xAE, 0x17, 0x09,  // 163:2734
	0x0A, 0xC5, 0x1A, 0x09,  // 164:2757
	0x0A, 0xDF, 0x17, 0x09,  // 165:2783
	0x0A, 0xF6, 0x08, 0x05,  // 166:2806
	0x0A, 0xFE, 0x11, 0x07,  // 167:2814
	0x0B, 0x0F, 0x0D, 0x07,  // 168:2831
	0x0B, 0x1C, 0x23, 0x0E,  // 169:2844
	0x0B, 0x3F, 0x11, 0x07,  // 170:2879
	0x0B, 0x50, 0x14, 0x09,  // 171:2896
	0x0B, 0x64, 0x1D, 0x0C,  // 172:2916
	0x0B, 0x81, 0x0E, 0x05,  // 173:2945
	0x0B, 0x8F, 0x23, 0x0E,  // 174:2959
	0x0B, 0xB2, 0x0D, 0x07,  // 175:2994
	0x0B, 0xBF, 0x0D, 0x07,  // 176:3007
	0x0B, 0xCC, 0x1D, 0x0C,  // 177:3020
	0x0B, 0xE9, 0x0E, 0x06,  // 178:3049
	0x0B, 0xF7, 0x0D, 0x06,  // 179:3063
	0x0C, 0x04, 0x10, 0x07,  // 180:3076
	0x0C, 0x14, 0x1A, 0x09,  // 181:3092
	0x0C, 0x2E, 0x14, 0x09,  // 182:3118
	0x0C, 0x42, 0x08, 0x04,  // 183:3138
	0x0C, 0x4A, 0x0E, 0x07,  // 184:3146
	0x0C, 0x58, 0x0B, 0x06,  // 185:3160
	0x0C, 0x63, 0x11, 0x07,  // 186:3171
	0x0C, 0x74, 0x14, 0x09,  // 187:3188
	0x0C, 0x88, 0x26, 0x0E,  // 188:3208
	0x0C, 0xAE, 0x26, 0x0E,  // 189:3246
	0x0C, 0xD4, 0x26, 0x0E,  // 190:3284
	0x0C, 0xFA, 0x11, 0x07,  // 191:3322
	0x0D, 0x0B, 0x1A, 0x09,  // 192:3339
	0x0D, 0x25, 0x1A, 0x09,  // 193:3365
	0x0D, 0x3F, 0x1A, 0x09,  // 194:3391
	0x0D, 0x59, 0x1A, 0x09,  // 195:3417
	0x0D, 0x73, 0x1A, 0x09,  // 196:3443
	0x0D, 0x8D, 0x1A, 0x09,  // 197:3469
	0x0D, 0xA7, 0x26, 0x0E,  // 198:3495
	0x0D, 0xCD, 0x1A, 0x0A,  // 199:3533
	0x0D, 0xE7, 0x17, 0x09,  // 200:3559
	0x0D, 0xFE, 0x17, 0x09,  // 201:3582
	0x0E, 0x15, 0x17, 0x09,  // 202:3605
	0x0E, 0x2C, 0x17, 0x09,  // 203:3628
	0x0E, 0x43, 0x07, 0x03,  // 204:3651
	0x0E, 0x4A, 0x07, 0x03,  // 205:3658
	0x0E, 0x51, 0x07, 0x03,  // 206:3665
	0x0E, 0x58, 0x07, 0x03,  // 207:3672
	0x0E, 0x5F, 0x1D, 0x0B,  // 208:3679
	0x0E, 0x7C, 0x1A, 0x0A,  // 209:3708
	0x0E, 0x96, 0x1D, 0x0B,  // 210:3734
	0x0E, 0xB3, 0x1D, 0x0B,  // 211:3763
	0x0E, 0xD0, 0x1D, 0x0B,  // 212:3792
	0x0E, 0xED, 0x1D, 0x0B,  // 213:3821
	0x0F, 0x0A, 0x1D, 0x0B,  // 214:3850
	0x0F, 0x27, 0x1D, 0x0C,  // 215:3879
	0x0F, 0x44, 0x1D, 0x0B,  // 216:3908
	0x0F, 0x61, 0x1A, 0x0A,  // 217:3937
	0x0F, 0x7B, 0x1A, 0x0A,  // 218:3963
	0x0F, 0x95, 0x1A, 0x0A,  // 219:3989
	0x0F, 0xAF, 0x1A, 0x0A,  // 220:4015
	0x0F, 0xC9, 0x19, 0x09,  // 221:4041
	0x0F, 0xE2, 0x17, 0x09,  // 222:4066
	0x0F, 0xF9, 0x17, 0x09,  // 223:4089
	0x10, 0x10, 0x14, 0x08,  // 224:4112
	0x10, 0x24, 0x14, 0x08,  // 225:4132
	0x10, 0x38, 0x14, 0x08,  // 226:4152
	0x10, 0x4C, 0x14, 0x08,  // 227:4172
	0x10, 0x60, 0x14, 0x08,  // 228:4192
	0x10, 0x74, 0x14, 0x08,  // 229:4212
	0x10, 0x88, 0x26, 0x0E,  // 230:4232
	0x10, 0xAE, 0x14, 0x08,  // 231:4270
	0x10, 0xC2, 0x17, 0x09,  // 232:4290
	0x10, 0xD9, 0x17, 0x09,  // 233:4313
	0x10, 0xF0, 0x17, 0x09,  // 234:4336
	0x11, 0x07, 0x17, 0x09,  // 235:4359
	0x11, 0x1E, 0x05, 0x03,  // 236:4382
	0x11, 0x23, 0x07, 0x03,  // 237:4387
	0x11, 0x2A, 0x07, 0x03,  // 238:4394
	0x11, 0x31, 0x07, 0x03,  // 239:4401
	0x11, 0x38, 0x17, 0x09,  // 240:4408
	0x11, 0x4F, 0x17, 0x09,  // 241:4431
	0x11, 0x66, 0x17, 0x09,  // 242:4454
	0x11, 0x7D, 0x17, 0x09,  // 243:4477
	0x11, 0x94, 0x17, 0x09,  // 244:4500
	0x11, 0xAB, 0x17, 0x09,  // 245:4523
	0x11, 0xC2, 0x17, 0x09,  // 246:4546
	0x11, 0xD9, 0x20, 0x0C,  // 247:4569
	0x11, 0xF9, 0x17, 0x09,  // 248:4601
	0x12, 0x10, 0x17, 0x09,  // 249:4624
	0x12, 0x27, 0x17, 0x09,  // 250:4647
	0x12, 0x3E, 0x17, 0x09,  // 251:4670
	0x12, 0x55, 0x17, 0x09,  // 252:4693
	0x12, 0x6C, 0x13, 0x07,  // 253:4716
	0x12, 0x7F, 0x17, 0x09,  // 254:4735
	0x12, 0x96, 0x13, 0x07,  // 255:4758

	// Font Data:
	0x00,0x00,0x00,0x00,0x00,0x00,0xF8,0x19,	// 33
	0x00,0x00,0x00,0x78,0x00,0x00,0x00,0x00,0x00,0x78,	// 34
	0x00,0x00,0x00,0x00,0x02,0x00,0x40,0x02,0x00,0x40,0x1E,0x00,0xC0,0x03,0x00,0x78,0x02,0x00,0x40,0x1E,0x00,0xC0,0x07,0x00,0x78,0x02,0x00,0x40,0x02,0x00,0x40,	// 35
	0x00,0x00,0x00,0xE0,0x08,0x00,0x90,0x11,0x00,0x10,0x11,0x00,0xFC,0x7F,0x00,0x10,0x11,0x00,0x10,0x13,0x00,0x20,0x0E,	// 36
	0xF0,0x00,0x00,0x08,0x01,0x00,0x08,0x01,0x00,0x08,0x19,0x00,0xF0,0x06,0x00,0x00,0x03,0x00,0xC0,0x00,0x00,0x60,0x0F,0x00,0x98,0x10,0x00,0x80,0x10,0x00,0x80,0x10,0x00,0x00,0x0F,	// 37
	0x00,0x00,0x00,0x00,0x07,0x00,0xB0,0x08,0x00,0x48,0x10,0x00,0x88,0x10,0x00,0x08,0x11,0x00,0x10,0x12,0x00,0x00,0x0C,0x00,0x00,0x08,0x00,0x00,0x14,0x00,0x00,0x13,	// 38
	0x00,0x00,0x00,0x78,	// 39
	0x00,0x00,0x00,0xE0,0x07,0x00,0x1C,0x18,0x00,0x04,0x20,	// 40
	0x00,0x00,0x00,0x04,0x20,0x00,0x18,0x18,0x00,0xE0,0x07,	// 41
	0x90,0x00,0x00,0xA0,0x00,0x00,0x60,0x00,0x00,0xF8,0x01,0x00,0x60,0x00,0x00,0xA0,0x00,0x00,0x90,	// 42
	0x00,0x00,0x00,0x00,0x01,0x00,0x00,0x01,0x00,0x00,0x01,0x00,0x00,0x01,0x00,0xF0,0x1F,0x00,0x00,0x01,0x00,0x00,0x01,0x00,0x00,0x01,0x00,0x00,0x01,	// 43
	0x00,0x00,0x00,0x00,0x20,0x00,0x00,0x18,	// 44
	0x00,0x00,0x00,0x00,0x02,0x00,0x00,0x02,0x00,0x00,0x02,0x00,0x00,0x02,	// 45
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x18,	// 46
	0x00,0x60,0x00,0x00,0x3C,0x00,0x80,0x07,0x00,0xF0,0x00,0x00,0x18,	// 47
	0x00,0x00,0x00,0xE0,0x07,0x00,0x10,0x08,0x00,0x08,0x10,0x00,0x08,0x10,0x00,0x08,0x10,0x00,0x10,0x08,0x00,0xE0,0x07,	// 48
	0x00,0x00,0x00,0x00,0x00,0x00,0x10,0x10,0x00,0x08,0x10,0x00,0xF8,0x1F,0x00,0x00,0x10,0x00,0x00,0x10,	// 49
	0x00,0x00,0x00,0x10,0x10,0x00,0x08,0x18,0x00,0x08,0x14,0x00,0x08,0x12,0x00,0x98,0x11,0x00,0xF0,0x10,	// 50
	0x00,0x00,0x00,0x10,0x08,0x00,0x08,0x10,0x00,0x88,0x10,0x00,0x88,0x10,0x00,0x88,0x10,0x00,0x98,0x09,0x00,0x70,0x0F,	// 51
	0x00,0x00,0x00,0x00,0x03,0x00,0x80,0x02,0x00,0x60,0x02,0x00,0x10,0x02,0x00,0x08,0x02,0x00,0xF8,0x1F,0x00,0x00,0x02,	// 52
	0x00,0x00,0x00,0xF8,0x08,0x00,0x48,0x10,0x00,0x48,0x10,0x00,0x48,0x10,0x00,0x48,0x10,0x00,0x88,0x08,0x00,0x00,0x07,	// 53
	0x00,0x00,0x00,0xE0,0x07,0x00,0x30,0x09,0x00,0x98,0x10,0x00,0x88,0x10,0x00,0x88,0x10,0x00,0x88,0x19,0x00,0x10,0x0F,	// 54
	0x00,0x00,0x00,0x08,0x00,0x00,0x08,0x10,0x00,0x08,0x0C,0x00,0x08,0x03,0x00,0xC8,0x00,0x00,0x38,0x00,0x00,0x08,	// 55
	0x00,0x00,0x00,0x70,0x0F,0x00,0x58,0x19,0x00,0x88,0x10,0x00,0x88,0x10,0x00,0x88,0x10,0x00,0x58,0x19,0x00,0x70,0x0F,	// 56
	0x00,0x00,0x00,0xF0,0x08,0x00,0x98,0x11,0x00,0x08,0x11,0x00,0x08,0x11,0x00,0x08,0x19,0x00,0x90,0x0C,0x00,0xE0,0x07,	// 57
	0x00,0x00,0x00,0x00,0x00,0x00,0xC0,0x18,	// 58
	0x00,0x00,0x00,0x00,0x20,0x00,0xC0,0x18,	// 59
	0x00,0x00,0x00,0x00,0x03,0x00,0x00,0x03,0x00,0x80,0x07,0x00,0x80,0x04,0x00,0x80,0x04,0x00,0x40,0x08,0x00,0x40,0x08,0x00,0x40,0x08,0x00,0x20,0x10,	// 60
	0x00,0x00,0x00,0x40,0x02,0x00,0x40,0x02,0x00,0x40,0x02,0x00,0x40,0x02,0x00,0x40,0x02,0x00,0x40,0x02,0x00,0x40,0x02,0x00,0x40,0x02,0x00,0x40,0x02,	// 61
	0x00,0x00,0x00,0x20,0x10,0x00,0x40,0x08,0x00,0x40,0x08,0x00,0x40,0x08,0x00,0x80,0x04,0x00,0x80,0x04,0x00,0x80,0x07,0x00,0x00,0x03,0x00,0x00,0x03,	// 62
	0x00,0x00,0x00,0x10,0x00,0x00,0x08,0x00,0x00,0x88,0x1B,0x00,0xC8,0x00,0x00,0x70,	// 63
	0x00,0x00,0x00,0x80,0x07,0x00,0x60,0x18,0x00,0x10,0x20,0x00,0x90,0x27,0x00,0xC8,0x4C,0x00,0x48,0x48,0x00,0x48,0x48,0x00,0x88,0x44,0x00,0xC8,0x4F,0x00,0x10,0x28,0x00,0x20,0x04,0x00,0xC0,0x03,	// 64
	0x00,0x10,0x00,0x00,0x0E,0x00,0xC0,0x03,0x00,0x30,0x02,0x00,0x08,0x02,0x00,0x30,0x02,0x00,0xC0,0x03,0x00,0x00,0x0E,0x00,0x00,0x10,	// 65
	0x00,0x00,0x00,0xF8,0x1F,0x00,0x88,0x10,0x00,0x88,0x10,0x00,0x88,0x10,0x00,0x88,0x10,0x00,0x88,0x10,0x00,0xD8,0x19,0x00,0x70,0x0F,	// 66
	0x00,0x00,0x00,0xE0,0x07,0x00,0x30,0x0C,0x00,0x18,0x18,0x00,0x08,0x10,0x00,0x08,0x10,0x00,0x08,0x10,0x00,0x08,0x10,0x00,0x10,0x08,	// 67
	0x00,0x00,0x00,0xF8,0x1F,0x00,0x08,0x10,0x00,0x08,0x10,0x00,0x08,0x10,0x00,0x08,0x10,0x00,0x08,0x10,0x00,0x10,0x08,0x00,0x30,0x0C,0x00,0xE0,0x07,	// 68
	0x00,0x00,0x00,0xF8,0x1F,0x00,0x88,0x10,0x00,0x88,0x10,0x00,0x88,0x10,0x00,0x88,0x10,0x00,0x88,0x10,0x00,0x88,0x10,	// 69
	0x00,0x00,0x00,0xF8,0x1F,0x00,0x88,0x00,0x00,0x88,0x00,0x00,0x88,0x00,0x00,0x88,0x00,0x00,0x88,	// 70
	0x00,0x00,0x00,0xC0,0x03,0x00,0x30,0x0C,0x00,0x10,0x08,0x00,0x08,0x10,0x00,0x08,0x10,0x00,0x08,0x10,0x00,0x08,0x11,0x00,0x08,0x11,0x00,0x10,0x0F,	// 71
	0x00,0x00,0x00,0xF8,0x1F,0x00,0x80,0x00,0x00,0x80,0x00,0x00,0x80,0x00,0x00,0x80,0x00,0x00,0x80,0x00,0x00,0x80,0x00,0x00,0xF8,0x1F,	// 72
	0x00,0x00,0x00,0xF8,0x1F,	// 73
	0x00,0x80,0x00,0xF8,0x7F,	// 74
	0x00,0x00,0x00,0xF8,0x1F,0x00,0x80,0x00,0x00,0x80,0x01,0x00,0x40,0x02,0x00,0x20,0x04,0x00,0x10,0x08,0x00,0x08,0x10,	// 75
	0x00,0x00,0x00,0xF8,0x1F,0x00,0x00,0x10,0x00,0x00,0x10,0x00,0x00,0x10,0x00,0x00,0x10,0x00,0x00,0x10,	// 76
	0x00,0x00,0x00,0xF8,0x1F,0x00,0x18,0x00,0x00,0x60,0x00,0x00,0x80,0x01,0x00,0x00,0x06,0x00,0x00,0x06,0x00,0x80,0x01,0x00,0x60,0x00,0x00,0x18,0x00,0x00,0xF8,0x1F,	// 77
	0x00,0x00,0x00,0xF8,0x1F,0x00,0x18,0x00,0x00,0x20,0x00,0x00,0xC0,0x00,0x00,0x00,0x03,0x00,0x00,0x04,0x00,0x00,0x18,0x00,0xF8,0x1F,	// 78
	0x00,0x00,0x00,0xE0,0x07,0x00,0x30,0x0C,0x00,0x18,0x18,0x00,0x08,0x10,0x00,0x08,0x10,0x00,0x08,0x10,0x00,0x18,0x18,0x00,0x30,0x0C,0x00,0xE0,0x07,	// 79
	0x00,0x00,0x00,0xF8,0x1F,0x00,0x08,0x01,0x00,0x08,0x01,0x00,0x08,0x01,0x00,0x08,0x01,0x00,0x98,0x01,0x00,0xF0,	// 80
	0x00,0x00,0x00,0xE0,0x07,0x00,0x30,0x0C,0x00,0x18,0x18,0x00,0x08,0x10,0x00,0x08,0x10,0x00,0x08,0x10,0x00,0x18,0x38,0x00,0x30,0x4C,0x00,0xE0,0x07,	// 81
	0x00,0x00,0x00,0xF8,0x1F,0x00,0x08,0x01,0x00,0x08,0x01,0x00,0x08,0x01,0x00,0x08,0x01,0x00,0x98,0x03,0x00,0xF0,0x0E,0x00,0x00,0x10,	// 82
	0x00,0x00,0x00,0x70,0x08,0x00,0x98,0x10,0x00,0x88,0x10,0x00,0x08,0x11,0x00,0x08,0x11,0x00,0x08,0x19,0x00,0x10,0x0E,	// 83
	0x08,0x00,0x00,0x08,0x00,0x00,0x08,0x00,0x00,0x08,0x00,0x00,0xF8,0x1F,0x00,0x08,0x00,0x00,0x08,0x00,0x00,0x08,0x00,0x00,0x08,	// 84
	0x00,0x00,0x00,0xF8,0x07,0x00,0x00,0x08,0x00,0x00,0x10,0x00,0x00,0x10,0x00,0x00,0x10,0x00,0x00,0x10,0x00,0x00,0x08,0x00,0xF8,0x07,	// 85
	0x08,0x00,0x00,0x70,0x00,0x00,0x80,0x01,0x00,0x00,0x0E,0x00,0x00,0x10,0x00,0x00,0x0E,0x00,0x80,0x01,0x00,0x70,0x00,0x00,0x08,	// 86
	0x18,0x00,0x00,0xE0,0x00,0x00,0x00,0x0F,0x00,0x00,0x10,0x00,0x00,0x0F,0x00,0xF0,0x00,0x00,0x08,0x00,0x00,0xF0,0x00,0x00,0x00,0x0F,0x00,0x00,0x10,0x00,0x00,0x0F,0x00,0xE0,0x00,0x00,0x18,	// 87
	0x08,0x10,0x00,0x18,0x18,0x00,0x20,0x04,0x00,0x40,0x03,0x00,0x80,0x01,0x00,0x40,0x02,0x00,0x20,0x04,0x00,0x18,0x18,0x00,0x08,0x10,	// 88
	0x08,0x00,0x00,0x18,0x00,0x00,0x60,0x00,0x00,0x80,0x00,0x00,0x00,0x1F,0x00,0x80,0x00,0x00,0x60,0x00,0x00,0x18,0x00,0x00,0x08,	// 89
	0x00,0x00,0x00,0x08,0x18,0x00,0x08,0x14,0x00,0x08,0x12,0x00,0x08,0x11,0x00,0x88,0x10,0x00,0x48,0x10,0x00,0x28,0x10,0x00,0x18,0x10,	// 90
	0x00,0x00,0x00,0xFC,0x3F,0x00,0x04,0x20,0x00,0x04,0x20,	// 91
	0x18,0x00,0x00,0xF0,0x00,0x00,0x80,0x07,0x00,0x00,0x3C,0x00,0x00,0x60,	// 92
	0x00,0x00,0x00,0x04,0x20,0x00,0x04,0x20,0x00,0xFC,0x3F,	// 93
	0x00,0x00,0x00,0x40,0x00,0x00,0x60,0x00,0x00,0x30,0x00,0x00,0x18,0x00,0x00,0x08,0x00,0x00,0x18,0x00,0x00,0x30,0x00,0x00,0x60,0x00,0x00,0x40,	// 94
	0x00,0x80,0x00,0x00,0x80,0x00,0x00,0x80,0x00,0x00,0x80,0x00,0x00,0x80,0x00,0x00,0x80,0x00,0x00,0x80,	// 95
	0x00,0x00,0x00,0x02,0x00,0x00,0x06,0x00,0x00,0x08,	// 96
	0x00,0x00,0x00,0x40,0x0E,0x00,0x20,0x11,0x00,0x20,0x11,0x00,0x20,0x11,0x00,0x20,0x09,0x00,0xC0,0x1F,	// 97
	0x00,0x00,0x00,0xFC,0x1F,0x00,0x40,0x08,0x00,0x20,0x10,0x00,0x20,0x10,0x00,0x20,0x10,0x00,0x40,0x08,0x00,0x80,0x07,	// 98
	0x00,0x00,0x00,0x80,0x07,0x00,0x40,0x08,0x00,0x20,0x10,0x00,0x20,0x10,0x00,0x20,0x10,0x00,0x40,0x08,	// 99
	0x00,0x00,0x00,0x80,0x07,0x00,0x40,0x08,0x00,0x20,0x10,0x00,0x20,0x10,0x00,0x20,0x10,0x00,0x40,0x08,0x00,0xFC,0x1F,	// 100
	0x00,0x00,0x00,0x80,0x07,0x00,0x40,0x09,0x00,0x20,0x11,0x00,0x20,0x11,0x00,0x20,0x11,0x00,0x60,0x11,0x00,0xC0,0x09,	// 101
	0x20,0x00,0x00,0xF8,0x1F,0x00,0x24,0x00,0x00,0x24,	// 102
	0x00,0x00,0x00,0x80,0x07,0x00,0x40,0x48,0x00,0x20,0x90,0x00,0x20,0x90,0x00,0x20,0x90,0x00,0x40,0xC8,0x00,0xE0,0x7F,	// 103
	0x00,0x00,0x00,0xFC,0x1F,0x00,0x40,0x00,0x00,0x20,0x00,0x00,0x20,0x00,0x00,0x20,0x00,0x00,0x60,0x00,0x00,0xC0,0x1F,	// 104
	0x00,0x00,0x00,0xEC,0x1F,	// 105
	0x00,0x80,0x00,0xEC,0x7F,	// 106
	0x00,0x00,0x00,0xFC,0x1F,0x00,0x00,0x01,0x00,0x00,0x03,0x00,0x80,0x04,0x00,0x40,0x08,0x00,0x20,0x10,	// 107
	0x00,0x00,0x00,0xFC,0x1F,	// 108
	0x00,0x00,0x00,0xE0,0x1F,0x00,0x40,0x00,0x00,0x20,0x00,0x00,0x20,0x00,0x00,0x20,0x00,0x00,0xC0,0x1F,0x00,0x40,0x00,0x00,0x20,0x00,0x00,0x20,0x00,0x00,0x20,0x00,0x00,0xC0,0x1F,	// 109
	0x00,0x00,0x00,0xE0,0x1F,0x00,0x40,0x00,0x00,0x20,0x00,0x00,0x20,0x00,0x00,0x20,0x00,0x00,0x60,0x00,0x00,0xC0,0x1F,	// 110
	0x00,0x00,0x00,0x80,0x07,0x00,0x40,0x08,0x00,0x20,0x10,0x00,0x20,0x10,0x00,0x20,0x10,0x00,0x40,0x08,0x00,0x80,0x07,	// 111
	0x00,0x00,0x00,0xE0,0xFF,0x00,0x40,0x08,0x00,0x20,0x10,0x00,0x20,0x10,0x00,0x20,0x10,0x00,0x40,0x08,0x00,0x80,0x07,	// 112
	0x00,0x00,0x00,0x80,0x07,0x00,0x40,0x08,0x00,0x20,0x10,0x00,0x20,0x10,0x00,0x20,0x10,0x00,0x40,0x08,0x00,0xE0,0xFF,	// 113
	0x00,0x00,0x00,0xE0,0x1F,0x00,0x40,0x00,0x00,0x20,0x00,0x00,0x20,	// 114
	0x00,0x00,0x00,0xC0,0x09,0x00,0x20,0x11,0x00,0x20,0x11,0x00,0x20,0x12,0x00,0x20,0x12,0x00,0x40,0x0E,	// 115
	0x20,0x00,0x00,0xF8,0x0F,0x00,0x20,0x10,0x00,0x20,0x10,0x00,0x20,0x10,	// 116
	0x00,0x00,0x00,0xE0,0x0F,0x00,0x00,0x18,0x00,0x00,0x10,0x00,0x00,0x10,0x00,0x00,0x10,0x00,0x00,0x08,0x00,0xE0,0x1F,	// 117
	0x60,0x00,0x00,0x80,0x03,0x00,0x00,0x0C,0x00,0x00,0x10,0x00,0x00,0x0C,0x00,0x80,0x03,0x00,0x60,	// 118
	0x00,0x00,0x00,0xE0,0x00,0x00,0x00,0x07,0x00,0x00,0x18,0x00,0x00,0x07,0x00,0xE0,0x00,0x00,0x00,0x07,0x00,0x00,0x18,0x00,0x00,0x07,0x00,0xE0,	// 119
	0x20,0x10,0x00,0x40,0x08,0x00,0x80,0x04,0x00,0x00,0x03,0x00,0x80,0x04,0x00,0x40,0x08,0x00,0x20,0x10,	// 120
	0x60,0x80,0x00,0x80,0x81,0x00,0x00,0x46,0x00,0x00,0x38,0x00,0x00,0x06,0x00,0x80,0x01,0x00,0x60,	// 121
	0x00,0x00,0x00,0x20,0x18,0x00,0x20,0x14,0x00,0x20,0x12,0x00,0x20,0x11,0x00,0xA0,0x10,0x00,0x60,0x10,	// 122
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x00,0x00,0x01,0x00,0xF8,0x3E,0x00,0x04,0x40,0x00,0x04,0x40,	// 123
	0x00,0x00,0x00,0x00,0x00,0x00,0xFC,0xFF,	// 124
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x04,0x40,0x00,0x04,0x40,0x00,0xF8,0x3E,0x00,0x00,0x01,0x00,0x00,0x01,	// 125
	0x00,0x00,0x00,0x00,0x02,0x00,0x00,0x01,0x00,0x00,0x01,0x00,0x00,0x01,0x00,0x00,0x03,0x00,0x00,0x02,0x00,0x00,0x02,0x00,0x00,0x02,0x00,0x00,0x01,	// 126
	0x00,0x00,0x00,0xF8,0x7F,0x00,0x08,0x40,0x00,0x08,0x40,0x00,0x08,0x40,0x00,0x08,0x40,0x00,0x08,0x40,0x00,0xF8,0x7F,	// 127
	0x00,0x00,0x00,0xF8,0x7F,0x00,0x08,0x40,0x00,0x08,0x40,0x00,0x08,0x40,0x00,0x08,0x40,0x00,0x08,0x40,0x00,0xF8,0x7F,	// 128
	0x00,0x00,0x00,0xF8,0x7F,0x00,0x08,0x40,0x00,0x08,0x40,0x00,0x08,0x40,0x00,0x08,0x40,0x00,0x08,0x40,0x00,0xF8,0x7F,	// 129
	0x00,0x00,0x00,0xF8,0x7F,0x00,0x08,0x40,0x00,0x08,0x40,0x00,0x08,0x40,0x00,0x08,0x40,0x00,0x08,0x40,0x00,0xF8,0x7F,	// 130
	0x00,0x00,0x00,0xF8,0x7F,0x00,0x08,0x40,0x00,0x08,0x40,0x00,0x08,0x40,0x00,0x08,0x40,0x00,0x08,0x40,0x00,0xF8,0x7F,	// 131
	0x00,0x00,0x00,0xF8,0x7F,0x00,0x08,0x40,0x00,0x08,0x40,0x00,0x08,0x40,0x00,0x08,0x40,0x00,0x08,0x40,0x00,0xF8,0x7F,	// 132
	0x00,0x00,0x00,0xF8,0x7F,0x00,0x08,0x40,0x00,0x08,0x40,0x00,0x08,0x40,0x00,0x08,0x40,0x00,0x08,0x40,0x00,0xF8,0x7F,	// 133
	0x00,0x00,0x00,0xF8,0x7F,0x00,0x08,0x40,0x00,0x08,0x40,0x00,0x08,0x40,0x00,0x08,0x40,0x00,0x08,0x40,0x00,0xF8,0x7F,	// 134
	0x00,0x00,0x00,0xF8,0x7F,0x00,0x08,0x40,0x00,0x08,0x40,0x00,0x08,0x40,0x00,0x08,0x40,0x00,0x08,0x40,0x00,0xF8,0x7F,	// 135
	0x00,0x00,0x00,0xF8,0x7F,0x00,0x08,0x40,0x00,0x08,0x40,0x00,0x08,0x40,0x00,0x08,0x40,0x00,0x08,0x40,0x00,0xF8,0x7F,	// 136
	0x00,0x00,0x00,0xF8,0x7F,0x00,0x08,0x40,0x00,0x08,0x40,0x00,0x08,0x40,0x00,0x08,0x40,0x00,0x08,0x40,0x00,0xF8,0x7F,	// 137
	0x00,0x00,0x00,0xF8,0x7F,0x00,0x08,0x40,0x00,0x08,0x40,0x00,0x08,0x40,0x00,0x08,0x40,0x00,0x08,0x40,0x00,0xF8,0x7F,	// 138
	0x00,0x00,0x00,0xF8,0x7F,0x00,0x08,0x40,0x00,0x08,0x40,0x00,0x08,0x40,0x00,0x08,0x40,0x00,0x08,0x40,0x00,0xF8,0x7F,	// 139
	0x00,0x00,0x00,0xF8,0x7F,0x00,0x08,0x40,0x00,0x08,0x40,0x00,0x08,0x40,0x00,0x08,0x40,0x00,0x08,0x40,0x00,0xF8,0x7F,	// 140
	0x00,0x00,0x00,0xF8,0x7F,0x00,0x08,0x40,0x00,0x08,0x40,0x00,0x08,0x40,0x00,0x08,0x40,0x00,0x08,0x40,0x00,0xF8,0x7F,	// 141
	0x00,0x00,0x00,0xF8,0x7F,0x00,0x08,0x40,0x00,0x08,0x40,0x00,0x08,0x40,0x00,0x08,0x40,0x00,0x08,0x40,0x00,0xF8,0x7F,	// 142
	0x00,0x00,0x00,0xF8,0x7F,0x00,0x08,0x40,0x00,0x08,0x40,0x00,0x08,0x40,0x00,0x08,0x40,0x00,0x08,0x40,0x00,0xF8,0x7F,	// 143
	0x00,0x00,0x00,0xF8,0x7F,0x00,0x08,0x40,0x00,0x08,0x40,0x00,0x08,0x40,0x00,0x08,0x40,0x00,0x08,0x40,0x00,0xF8,0x7F,	// 144
	0x00,0x00,0x00,0xF8,0x7F,0x00,0x08,0x40,0x00,0x08,0x40,0x00,0x08,0x40,0x00,0x08,0x40,0x00,0x08,0x40,0x00,0xF8,0x7F,	// 145
	0x00,0x00,0x00,0xF8,0x7F,0x00,0x08,0x40,0x00,0x08,0x40,0x00,0x08,0x40,0x00,0x08,0x40,0x00,0x08,0x40,0x00,0xF8,0x7F,	// 146
	0x00,0x00,0x00,0xF8,0x7F,0x00,0x08,0x40,0x00,0x08,0x40,0x00,0x08,0x40,0x00,0x08,0x40,0x00,0x08,0x40,0x00,0xF8,0x7F,	// 147
	0x00,0x00,0x00,0xF8,0x7F,0x00,0x08,0x40,0x00,0x08,0x40,0x00,0x08,0x40,0x00,0x08,0x40,0x00,0x08,0x40,0x00,0xF8,0x7F,	// 148
	0x00,0x00,0x00,0xF8,0x7F,0x00,0x08,0x40,0x00,0x08,0x40,0x00,0x08,0x40,0x00,0x08,0x40,0x00,0x08,0x40,0x00,0xF8,0x7F,	// 149
	0x00,0x00,0x00,0xF8,0x7F,0x00,0x08,0x40,0x00,0x08,0x40,0x00,0x08,0x40,0x00,0x08,0x40,0x00,0x08,0x40,0x00,0xF8,0x7F,	// 150
	0x00,0x00,0x00,0xF8,0x7F,0x00,0x08,0x40,0x00,0x08,0x40,0x00,0x08,0x40,0x00,0x08,0x40,0x00,0x08,0x40,0x00,0xF8,0x7F,	// 151
	0x00,0x00,0x00,0xF8,0x7F,0x00,0x08,0x40,0x00,0x08,0x40,0x00,0x08,0x40,0x00,0x08,0x40,0x00,0x08,0x40,0x00,0xF8,0x7F,	// 152
	0x00,0x00,0x00,0xF8,0x7F,0x00,0x08,0x40,0x00,0x08,0x40,0x00,0x08,0x40,0x00,0x08,0x40,0x00,0x08,0x40,0x00,0xF8,0x7F,	// 153
	0x00,0x00,0x00,0xF8,0x7F,0x00,0x08,0x40,0x00,0x08,0x40,0x00,0x08,0x40,0x00,0x08,0x40,0x00,0x08,0x40,0x00,0xF8,0x7F,	// 154
	0x00,0x00,0x00,0xF8,0x7F,0x00,0x08,0x40,0x00,0x08,0x40,0x00,0x08,0x40,0x00,0x08,0x40,0x00,0x08,0x40,0x00,0xF8,0x7F,	// 155
	0x00,0x00,0x00,0xF8,0x7F,0x00,0x08,0x40,0x00,0x08,0x40,0x00,0x08,0x40,0x00,0x08,0x40,0x00,0x08,0x40,0x00,0xF8,0x7F,	// 156
	0x00,0x00,0x00,0xF8,0x7F,0x00,0x08,0x40,0x00,0x08,0x40,0x00,0x08,0x40,0x00,0x08,0x40,0x00,0x08,0x40,0x00,0xF8,0x7F,	// 157
	0x00,0x00,0x00,0xF8,0x7F,0x00,0x08,0x40,0x00,0x08,0x40,0x00,0x08,0x40,0x00,0x08,0x40,0x00,0x08,0x40,0x00,0xF8,0x7F,	// 158
	0x00,0x00,0x00,0xF8,0x7F,0x00,0x08,0x40,0x00,0x08,0x40,0x00,0x08,0x40,0x00,0x08,0x40,0x00,0x08,0x40,0x00,0xF8,0x7F,	// 159
	0x00,0x00,0x00,0x00,0x00,0x00,0x60,0x7E,	// 161
	0x00,0x00,0x00,0x80,0x07,0x00,0x40,0x08,0x00,0x20,0x10,0x00,0xF8,0x7F,0x00,0x20,0x10,0x00,0x40,0x08,	// 162
	0x00,0x00,0x00,0x00,0x10,0x00,0x00,0x11,0x00,0xF0,0x1F,0x00,0x08,0x11,0x00,0x08,0x11,0x00,0x08,0x11,0x00,0x10,0x10,	// 163
	0x00,0x00,0x00,0x20,0x10,0x00,0xC0,0x0F,0x00,0xC0,0x0C,0x00,0x40,0x08,0x00,0x40,0x08,0x00,0xC0,0x0C,0x00,0xC0,0x0F,0x00,0x20,0x10,	// 164
	0x00,0x00,0x00,0x88,0x02,0x00,0xB0,0x02,0x00,0xC0,0x02,0x00,0x00,0x1F,0x00,0xC0,0x02,0x00,0xB0,0x02,0x00,0x88,0x02,	// 165
	0x00,0x00,0x00,0x00,0x00,0x00,0xF8,0x7C,	// 166
	0xB0,0x21,0x00,0x68,0x22,0x00,0x48,0x26,0x00,0x48,0x24,0x00,0x88,0x2C,0x00,0x88,0x1B,	// 167
	0x00,0x00,0x00,0x00,0x00,0x00,0x04,0x00,0x00,0x00,0x00,0x00,0x04,	// 168
	0x00,0x00,0x00,0x00,0x00,0x00,0xC0,0x03,0x00,0x30,0x0C,0x00,0xD0,0x0B,0x00,0x68,0x16,0x00,0x28,0x14,0x00,0x28,0x14,0x00,0x28,0x14,0x00,0x10,0x08,0x00,0x30,0x0C,0x00,0xC0,0x03,	// 169
	0x00,0x00,0x00,0xC0,0x04,0x00,0x28,0x05,0x00,0x28,0x05,0x00,0x28,0x05,0x00,0xF0,0x05,	// 170
	0x00,0x00,0x00,0x00,0x03,0x00,0x80,0x07,0x00,0xC0,0x0C,0x00,0x00,0x03,0x00,0x80,0x07,0x00,0xC0,0x0C,	// 171
	0x00,0x00,0x00,0x80,0x00,0x00,0x80,0x00,0x00,0x80,0x00,0x00,0x80,0x00,0x00,0x80,0x00,0x00,0x80,0x00,0x00,0x80,0x00,0x00,0x80,0x00,0x00,0x80,0x07,	// 172
	0x00,0x00,0x00,0x00,0x02,0x00,0x00,0x02,0x00,0x00,0x02,0x00,0x00,0x02,	// 173
	0x00,0x00,0x00,0x00,0x00,0x00,0xC0,0x03,0x00,0x30,0x0C,0x00,0x10,0x08,0x00,0xE8,0x17,0x00,0xA8,0x10,0x00,0xA8,0x11,0x00,0x68,0x16,0x00,0x10,0x0C,0x00,0x30,0x0C,0x00,0xC0,0x03,	// 174
	0x00,0x00,0x00,0x04,0x00,0x00,0x04,0x00,0x00,0x04,0x00,0x00,0x04,	// 175
	0x00,0x00,0x00,0x30,0x00,0x00,0x48,0x00,0x00,0x48,0x00,0x00,0x30,	// 176
	0x00,0x00,0x00,0x80,0x10,0x00,0x80,0x10,0x00,0x80,0x10,0x00,0x80,0x10,0x00,0xF0,0x17,0x00,0x80,0x10,0x00,0x80,0x10,0x00,0x80,0x10,0x00,0x80,0x10,	// 177
	0x00,0x00,0x00,0x08,0x01,0x00,0x88,0x01,0x00,0x48,0x01,0x00,0x30,0x01,	// 178
	0x00,0x00,0x00,0x08,0x01,0x00,0x28,0x01,0x00,0x28,0x01,0x00,0xD8,	// 179
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x08,0x00,0x00,0x06,0x00,0x00,0x02,	// 180
	0x00,0x00,0x00,0xE0,0xFF,0x00,0x00,0x18,0x00,0x00,0x10,0x00,0x00,0x10,0x00,0x00,0x10,0x00,0x00,0x08,0x00,0xE0,0x1F,0x00,0x00,0x10,	// 181
	0x00,0x00,0x00,0x70,0x00,0x00,0xF8,0x00,0x00,0xF8,0x01,0x00,0xF8,0x3F,0x00,0x08,0x00,0x00,0xF8,0x3F,	// 182
	0x00,0x00,0x00,0x00,0x00,0x00,0x80,0x01,	// 183
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0x00,0x00,0xA0,0x00,0x00,0xC0,	// 184
	0x00,0x00,0x00,0x08,0x01,0x00,0xF8,0x01,0x00,0x00,0x01,	// 185
	0x00,0x00,0x00,0xF0,0x04,0x00,0x08,0x05,0x00,0x08,0x05,0x00,0x08,0x05,0x00,0xF0,0x04,	// 186
	0x00,0x00,0x00,0xC0,0x0C,0x00,0x80,0x07,0x00,0x00,0x03,0x00,0xC0,0x0C,0x00,0x80,0x07,0x00,0x00,0x03,	// 187
	0x00,0x00,0x00,0x08,0x01,0x00,0xF8,0x01,0x00,0x00,0x11,0x00,0x00,0x0C,0x00,0x00,0x06,0x00,0x80,0x01,0x00,0x60,0x00,0x00,0x30,0x0C,0x00,0x08,0x0A,0x00,0x00,0x09,0x00,0x80,0x1F,0x00,0x00,0x08,	// 188
	0x00,0x00,0x00,0x08,0x01,0x00,0xF8,0x01,0x00,0x00,0x11,0x00,0x00,0x0C,0x00,0x00,0x06,0x00,0x80,0x01,0x00,0x60,0x00,0x00,0x30,0x00,0x00,0x08,0x21,0x00,0x00,0x31,0x00,0x00,0x29,0x00,0x00,0x26,	// 189
	0x00,0x00,0x00,0x08,0x01,0x00,0x28,0x01,0x00,0x28,0x11,0x00,0xD8,0x0C,0x00,0x00,0x06,0x00,0x80,0x01,0x00,0x60,0x00,0x00,0x30,0x0C,0x00,0x08,0x0A,0x00,0x00,0x09,0x00,0x80,0x1F,0x00,0x00,0x08,	// 190
	0x00,0x00,0x00,0x00,0x70,0x00,0x00,0x88,0x00,0x60,0x87,0x00,0x00,0x80,0x00,0x00,0x40,	// 191
	0x00,0x10,0x00,0x00,0x0E,0x00,0xC0,0x03,0x00,0x31,0x02,0x00,0x0A,0x02,0x00,0x30,0x02,0x00,0xC0,0x03,0x00,0x00,0x0E,0x00,0x00,0x10,	// 192
	0x00,0x10,0x00,0x00,0x0E,0x00,0xC0,0x03,0x00,0x30,0x02,0x00,0x0A,0x02,0x00,0x31,0x02,0x00,0xC0,0x03,0x00,0x00,0x0E,0x00,0x00,0x10,	// 193
	0x00,0x10,0x00,0x00,0x0E,0x00,0xC0,0x03,0x00,0x32,0x02,0x00,0x09,0x02,0x00,0x32,0x02,0x00,0xC0,0x03,0x00,0x00,0x0E,0x00,0x00,0x10,	// 194
	0x00,0x10,0x00,0x00,0x0E,0x00,0xC3,0x03,0x00,0x31,0x02,0x00,0x0B,0x02,0x00,0x32,0x02,0x00,0xC3,0x03,0x00,0x00,0x0E,0x00,0x00,0x10,	// 195
	0x00,0x10,0x00,0x00,0x0E,0x00,0xC0,0x03,0x00,0x32,0x02,0x00,0x08,0x02,0x00,0x32,0x02,0x00,0xC0,0x03,0x00,0x00,0x0E,0x00,0x00,0x10,	// 196
	0x00,0x10,0x00,0x00,0x0E,0x00,0x80,0x03,0x00,0x67,0x02,0x00,0x19,0x02,0x00,0x67,0x02,0x00,0x80,0x03,0x00,0x00,0x0E,0x00,0x00,0x10,	// 197
	0x00,0x10,0x00,0x00,0x0E,0x00,0x80,0x03,0x00,0x60,0x02,0x00,0x18,0x02,0x00,0x08,0x02,0x00,0xF8,0x1F,0x00,0x88,0x10,0x00,0x88,0x10,0x00,0x88,0x10,0x00,0x88,0x10,0x00,0x88,0x10,0x00,0x88,0x10,	// 198
	0x00,0x00,0x00,0xE0,0x07,0x00,0x30,0x0C,0x00,0x18,0x18,0x00,0x08,0x90,0x00,0x08,0xB0,0x00,0x08,0xD0,0x00,0x08,0x10,0x00,0x10,0x08,	// 199
	0x00,0x00,0x00,0xF8,0x1F,0x00,0x88,0x10,0x00,0x89,0x10,0x00,0x8A,0x10,0x00,0x88,0x10,0x00,0x88,0x10,0x00,0x88,0x10,	// 200
	0x00,0x00,0x00,0xF8,0x1F,0x00,0x88,0x10,0x00,0x88,0x10,0x00,0x8A,0x10,0x00,0x89,0x10,0x00,0x88,0x10,0x00,0x88,0x10,	// 201
	0x00,0x00,0x00,0xF8,0x1F,0x00,0x88,0x10,0x00,0x8A,0x10,0x00,0x89,0x10,0x00,0x89,0x10,0x00,0x8A,0x10,0x00,0x88,0x10,	// 202
	0x00,0x00,0x00,0xF8,0x1F,0x00,0x88,0x10,0x00,0x8A,0x10,0x00,0x88,0x10,0x00,0x8A,0x10,0x00,0x88,0x10,0x00,0x88,0x10,	// 203
	0x00,0x00,0x00,0xF9,0x1F,0x00,0x02,	// 204
	0x00,0x00,0x00,0xF8,0x1F,0x00,0x02,	// 205
	0x03,0x00,0x00,0xF9,0x1F,0x00,0x03,	// 206
	0x02,0x00,0x00,0xF8,0x1F,0x00,0x02,	// 207
	0x80,0x00,0x00,0xF8,0x1F,0x00,0x88,0x10,0x00,0x88,0x10,0x00,0x08,0x10,0x00,0x08,0x10,0x00,0x08,0x10,0x00,0x10,0x08,0x00,0x30,0x0C,0x00,0xC0,0x03,	// 208
	0x00,0x00,0x00,0xF8,0x1F,0x00,0x18,0x00,0x00,0x23,0x00,0x00,0xC1,0x00,0x00,0x02,0x03,0x00,0x03,0x04,0x00,0x00,0x18,0x00,0xF8,0x1F,	// 209
	0x00,0x00,0x00,0xE0,0x07,0x00,0x30,0x0C,0x00,0x18,0x18,0x00,0x09,0x10,0x00,0x0A,0x10,0x00,0x08,0x10,0x00,0x18,0x18,0x00,0x30,0x0C,0x00,0xE0,0x07,	// 210
	0x00,0x00,0x00,0xE0,0x07,0x00,0x30,0x0C,0x00,0x18,0x18,0x00,0x08,0x10,0x00,0x0A,0x10,0x00,0x09,0x10,0x00,0x18,0x18,0x00,0x30,0x0C,0x00,0xE0,0x07,	// 211
	0x00,0x00,0x00,0xE0,0x07,0x00,0x30,0x0C,0x00,0x18,0x18,0x00,0x0A,0x10,0x00,0x09,0x10,0x00,0x0A,0x10,0x00,0x18,0x18,0x00,0x30,0x0C,0x00,0xE0,0x07,	// 212
	0x00,0x00,0x00,0xE0,0x07,0x00,0x30,0x0C,0x00,0x1B,0x18,0x00,0x09,0x10,0x00,0x0B,0x10,0x00,0x0A,0x10,0x00,0x1B,0x18,0x00,0x30,0x0C,0x00,0xE0,0x07,	// 213
	0x00,0x00,0x00,0xE0,0x07,0x00,0x30,0x0C,0x00,0x18,0x18,0x00,0x0A,0x10,0x00,0x08,0x10,0x00,0x0A,0x10,0x00,0x18,0x18,0x00,0x30,0x0C,0x00,0xE0,0x07,	// 214
	0x00,0x00,0x00,0x00,0x00,0x00,0x20,0x10,0x00,0x40,0x08,0x00,0x80,0x04,0x00,0x00,0x03,0x00,0x00,0x03,0x00,0x80,0x04,0x00,0x40,0x08,0x00,0x20,0x10,	// 215
	0x00,0x00,0x00,0xE0,0x13,0x00,0x30,0x0C,0x00,0x18,0x1C,0x00,0x08,0x12,0x00,0x88,0x11,0x00,0x48,0x10,0x00,0x38,0x18,0x00,0x30,0x0C,0x00,0xC8,0x03,	// 216
	0x00,0x00,0x00,0xF8,0x07,0x00,0x00,0x08,0x00,0x00,0x10,0x00,0x01,0x10,0x00,0x02,0x10,0x00,0x00,0x10,0x00,0x00,0x08,0x00,0xF8,0x07,	// 217
	0x00,0x00,0x00,0xF8,0x07,0x00,0x00,0x08,0x00,0x00,0x10,0x00,0x00,0x10,0x00,0x02,0x10,0x00,0x01,0x10,0x00,0x00,0x08,0x00,0xF8,0x07,	// 218
	0x00,0x00,0x00,0xF8,0x07,0x00,0x00,0x08,0x00,0x02,0x10,0x00,0x01,0x10,0x00,0x01,0x10,0x00,0x02,0x10,0x00,0x00,0x08,0x00,0xF8,0x07,	// 219
	0x00,0x00,0x00,0xF8,0x07,0x00,0x00,0x08,0x00,0x02,0x10,0x00,0x00,0x10,0x00,0x00,0x10,0x00,0x02,0x10,0x00,0x00,0x08,0x00,0xF8,0x07,	// 220
	0x08,0x00,0x00,0x18,0x00,0x00,0x60,0x00,0x00,0x80,0x00,0x00,0x02,0x1F,0x00,0x81,0x00,0x00,0x60,0x00,0x00,0x18,0x00,0x00,0x08,	// 221
	0x00,0x00,0x00,0xF8,0x1F,0x00,0x10,0x02,0x00,0x10,0x02,0x00,0x10,0x02,0x00,0x10,0x02,0x00,0x30,0x03,0x00,0xE0,0x01,	// 222
	0x00,0x00,0x00,0xF8,0x1F,0x00,0x0C,0x00,0x00,0x04,0x10,0x00,0xE4,0x11,0x00,0x24,0x11,0x00,0x18,0x13,0x00,0x00,0x0E,	// 223
	0x00,0x00,0x00,0x40,0x0E,0x00,0x22,0x11,0x00,0x26,0x11,0x00,0x28,0x11,0x00,0x20,0x09,0x00,0xC0,0x1F,	// 224
	0x00,0x00,0x00,0x40,0x0E,0x00,0x20,0x11,0x00,0x20,0x11,0x00,0x28,0x11,0x00,0x26,0x09,0x00,0xC2,0x1F,	// 225
	0x00,0x00,0x00,0x40,0x0E,0x00,0x28,0x11,0x00,0x26,0x11,0x00,0x26,0x11,0x00,0x28,0x09,0x00,0xC0,0x1F,	// 226
	0x00,0x00,0x00,0x40,0x0E,0x00,0x2C,0x11,0x00,0x24,0x11,0x00,0x28,0x11,0x00,0x2C,0x09,0x00,0xC0,0x1F,	// 227
	0x00,0x00,0x00,0x40,0x0E,0x00,0x24,0x11,0x00,0x20,0x11,0x00,0x20,0x11,0x00,0x24,0x09,0x00,0xC0,0x1F,	// 228
	0x00,0x00,0x00,0x40,0x0E,0x00,0x26,0x11,0x00,0x29,0x11,0x00,0x29,0x11,0x00,0x26,0x09,0x00,0xC0,0x1F,	// 229
	0x00,0x00,0x00,0x40,0x0E,0x00,0x20,0x11,0x00,0x20,0x11,0x00,0x20,0x11,0x00,0x20,0x09,0x00,0xC0,0x07,0x00,0x60,0x09,0x00,0x20,0x11,0x00,0x20,0x11,0x00,0x20,0x11,0x00,0x60,0x11,0x00,0x80,0x09,	// 230
	0x00,0x00,0x00,0x80,0x07,0x00,0x40,0x08,0x00,0x20,0x90,0x00,0x20,0xB0,0x00,0x20,0xD0,0x00,0x40,0x08,	// 231
	0x00,0x00,0x00,0x80,0x07,0x00,0x42,0x09,0x00,0x26,0x11,0x00,0x28,0x11,0x00,0x20,0x11,0x00,0x60,0x11,0x00,0xC0,0x09,	// 232
	0x00,0x00,0x00,0x80,0x07,0x00,0x40,0x09,0x00,0x20,0x11,0x00,0x28,0x11,0x00,0x26,0x11,0x00,0x62,0x11,0x00,0xC0,0x09,	// 233
	0x00,0x00,0x00,0x80,0x07,0x00,0x48,0x09,0x00,0x24,0x11,0x00,0x22,0x11,0x00,0x24,0x11,0x00,0x68,0x11,0x00,0xC0,0x09,	// 234
	0x00,0x00,0x00,0x80,0x07,0x00,0x40,0x09,0x00,0x24,0x11,0x00,0x20,0x11,0x00,0x24,0x11,0x00,0x60,0x11,0x00,0xC0,0x09,	// 235
	0x06,0x00,0x00,0xE8,0x1F,	// 236
	0x00,0x00,0x00,0xE8,0x1F,0x00,0x06,	// 237
	0x04,0x00,0x00,0xE2,0x1F,0x00,0x04,	// 238
	0x04,0x00,0x00,0xE0,0x1F,0x00,0x04,	// 239
	0x00,0x00,0x00,0x80,0x07,0x00,0x48,0x08,0x00,0x2C,0x10,0x00,0x28,0x10,0x00,0x34,0x10,0x00,0x64,0x08,0x00,0xC0,0x07,	// 240
	0x00,0x00,0x00,0xE0,0x1F,0x00,0x4C,0x00,0x00,0x24,0x00,0x00,0x2C,0x00,0x00,0x28,0x00,0x00,0x6C,0x00,0x00,0xC0,0x1F,	// 241
	0x00,0x00,0x00,0x80,0x07,0x00,0x42,0x08,0x00,0x26,0x10,0x00,0x28,0x10,0x00,0x20,0x10,0x00,0x40,0x08,0x00,0x80,0x07,	// 242
	0x00,0x00,0x00,0x80,0x07,0x00,0x40,0x08,0x00,0x20,0x10,0x00,0x28,0x10,0x00,0x26,0x10,0x00,0x42,0x08,0x00,0x80,0x07,	// 243
	0x00,0x00,0x00,0x80,0x07,0x00,0x40,0x08,0x00,0x2C,0x10,0x00,0x26,0x10,0x00,0x28,0x10,0x00,0x40,0x08,0x00,0x80,0x07,	// 244
	0x00,0x00,0x00,0x80,0x07,0x00,0x4C,0x08,0x00,0x24,0x10,0x00,0x2C,0x10,0x00,0x28,0x10,0x00,0x4C,0x08,0x00,0x80,0x07,	// 245
	0x00,0x00,0x00,0x80,0x07,0x00,0x40,0x08,0x00,0x24,0x10,0x00,0x20,0x10,0x00,0x24,0x10,0x00,0x40,0x08,0x00,0x80,0x07,	// 246
	0x00,0x00,0x00,0x00,0x01,0x00,0x00,0x01,0x00,0x00,0x01,0x00,0x00,0x01,0x00,0x60,0x0D,0x00,0x60,0x0D,0x00,0x00,0x01,0x00,0x00,0x01,0x00,0x00,0x01,0x00,0x00,0x01,	// 247
	0x00,0x00,0x00,0x80,0x17,0x00,0x40,0x08,0x00,0x20,0x14,0x00,0x20,0x13,0x00,0xA0,0x10,0x00,0x40,0x08,0x00,0xA0,0x07,	// 248
	0x00,0x00,0x00,0xE0,0x0F,0x00,0x02,0x18,0x00,0x06,0x10,0x00,0x08,0x10,0x00,0x00,0x10,0x00,0x00,0x08,0x00,0xE0,0x1F,	// 249
	0x00,0x00,0x00,0xE0,0x0F,0x00,0x00,0x18,0x00,0x00,0x10,0x00,0x08,0x10,0x00,0x06,0x10,0x00,0x02,0x08,0x00,0xE0,0x1F,	// 250
	0x00,0x00,0x00,0xE0,0x0F,0x00,0x00,0x18,0x00,0x0C,0x10,0x00,0x06,0x10,0x00,0x08,0x10,0x00,0x00,0x08,0x00,0xE0,0x1F,	// 251
	0x00,0x00,0x00,0xE0,0x0F,0x00,0x00,0x18,0x00,0x04,0x10,0x00,0x00,0x10,0x00,0x04,0x10,0x00,0x00,0x08,0x00,0xE0,0x1F,	// 252
	0x60,0x80,0x00,0x80,0x81,0x00,0x00,0x46,0x00,0x00,0x38,0x00,0x08,0x06,0x00,0x86,0x01,0x00,0x62,	// 253
	0x00,0x00,0x00,0xFC,0xFF,0x00,0x40,0x08,0x00,0x20,0x10,0x00,0x20,0x10,0x00,0x20,0x10,0x00,0x40,0x08,0x00,0x80,0x07,	// 254
	0x60,0x80,0x00,0x80,0x81,0x00,0x04,0x46,0x00,0x00,0x38,0x00,0x04,0x06,0x00,0x80,0x01,0x00,0x60	// 255
};
