#ifndef __TW8819_H
#define __TW8819_H
#include "stm32f7xx.h"
#include "variables.h"
#define	TW8819_ADDRESS		        0x8A

#define PAGE0_GENERAL		        0x00
#define PAGE0_OUTPUT		        0x00	//0x007::0x00F & 0x01F
#define PAGE0_INPUT			0x00	//0x040::0x046
#define PAGE0_BT656			0x00	//0x047::0x04A
#define PAGE0_DTV			0x00	//0x050::0x05F
#define PAGE0_GPIO			0x00	//0x080::0x09E
#define PAGE0_MBIST			0x00	//0x0A0::0x0A4
#define PAGE0_TOUCH			0x00	//0x0B0::0x0B4
#define PAGE0_LOPOR			0x00	//0x0D4::0x0DF
#define PAGE0_LEDC			0x00	//0x0E0::0x0E6
#define PAGE0_DCDC			0x00	//0x0E8::0x0EC
#define PAGE0_VCOM			0x00	//0x0ED::0x0EE
#define PAGE0_SSPLL			0x00	//0x0F6::0x0FD
#define PAGE1_DECODER		        0x01	//0x101::0x142
#define PAGE1_VADC			0x01	//0x1C0::0x1E7	include LLPLL
#define PAGE2_SCALER		        0x02	//0x201::0x21E
#define PAGE2_TCON			0x02	//0x240::0x24E
#define PAGE2_IMAGE			0x02	//0x280::0x2BF
#define PAGE2_GAMMA			0x02	//0x2E0::0x2E3 include LCDC
#define PAGE2_DITHER		        0x02	//0x2E4::0x2E4
#define PAGE2_RGBLEVEL		        0x02	//0x2F0::0x2F5
#define PAGE2_8BITPANEL		        0x02	//0x2F8::0x2F9
#define PAGE3_FOSD			0x03	//0x300::0x354
#define PAGE4_SOSD			0x04	//0x400::0x3BE
#define PAGE3_SPI			0x04	//0x4C0::0x4DA include MCU
#define PAGE4_SPI			0x04	//0x4C0::0x4DA include MCU
#define TWBASE_SPI			0xC0	//note:Not a page. it is a offset.
#define PAGE4_CLOCK			0x04	//0x4E0::0x4EB
#define PAGE5_MEAS			0x05	//0x500::0x545

//===========================
// PAGE 0
//===========================
	#define REG000	0x00
	#define REG001	0x01
	#define REG002	0x02
	#define REG003	0x03
	#define REG004	0x04
	#define REG005	0x05
	#define REG006	0x06
	#define REG007	0x07
	#define REG008	0x08
	#define REG009	0x09
	#define REG00A	0x0A
	#define REG00B	0x0B
	#define REG00C	0x0C
	#define REG00D	0x0D
	#define REG00E	0x0E
	#define REG00F	0x0F

	#define REG010	0x10
	#define REG011	0x11
	#define REG012	0x12
	#define REG013	0x13
	#define REG014	0x14
	#define REG015	0x15
	#define REG016	0x16
	#define REG017	0x17
	#define REG018	0x18
	#define REG019	0x19
	#define REG01A	0x1A
	#define REG01B	0x1B
	#define REG01C	0x1C
	#define REG01D	0x1D
	#define REG01E	0x1E
	#define REG01F	0x1F

	#define REG020	0x20
	#define REG021	0x21
	#define REG022	0x22
	#define REG023	0x23
	#define REG024	0x24
	#define REG025	0x25
	#define REG026	0x26
	#define REG027	0x27
	#define REG028	0x28
	#define REG029	0x29
	#define REG02A	0x2A
	#define REG02B	0x2B
	#define REG02C	0x2C
	#define REG02D	0x2D
	#define REG02E	0x2E
	#define REG02F	0x2F

	#define REG030	0x30
	#define REG031	0x31
	#define REG032	0x32
	#define REG033	0x33
	#define REG034	0x34
	#define REG035	0x35
	#define REG036	0x36
	#define REG037	0x37
	#define REG038	0x38
	#define REG039	0x39
	#define REG03A	0x3A
	#define REG03B	0x3B
	#define REG03C	0x3C
	#define REG03D	0x3D
	#define REG03E	0x3E
	#define REG03F	0x3F

	#define REG040	0x40
	#define REG041	0x41
	#define REG042	0x42
	#define REG043	0x43
	#define REG044	0x44
	#define REG045	0x45
	#define REG046	0x46
	#define REG047	0x47
	#define REG048	0x48
	#define REG049	0x49
	#define REG04A	0x4A
	#define REG04B	0x4B
	#define REG04C	0x4C
	#define REG04D	0x4D
	#define REG04E	0x4E
	#define REG04F	0x4F

	#define REG050	0x50
	#define REG051	0x51
	#define REG052	0x52
	#define REG053	0x53
	#define REG054	0x54
	#define REG055	0x55
	#define REG056	0x56
	#define REG057	0x57
	#define REG058	0x58
	#define REG059	0x59
	#define REG05A	0x5A
	#define REG05B	0x5B
	#define REG05C	0x5C
	#define REG05D	0x5D
	#define REG05E	0x5E
	#define REG05F	0x5F

	#define REG060	0x60
	#define REG061	0x61
	#define REG062	0x62
	#define REG063	0x63
	#define REG064	0x64
	#define REG065	0x65
	#define REG066	0x66
	#define REG067	0x67
	#define REG068	0x68
	#define REG069	0x69
	#define REG06A	0x6A
	#define REG06B	0x6B
	#define REG06C	0x6C
	#define REG06D	0x6D
	#define REG06E	0x6E
	#define REG06F	0x6F

	#define REG070	0x70
	#define REG071	0x71
	#define REG072	0x72
	#define REG073	0x73
	#define REG074	0x74
	#define REG075	0x75
	#define REG076	0x76
	#define REG077	0x77
	#define REG078	0x78
	#define REG079	0x79
	#define REG07A	0x7A
	#define REG07B	0x7B
	#define REG07C	0x7C
	#define REG07D	0x7D
	#define REG07E	0x7E
	#define REG07F	0x7F

	#define REG080	0x80
	#define REG081	0x81
	#define REG082	0x82
	#define REG083	0x83
	#define REG084	0x84
	#define REG085	0x85
	#define REG086	0x86
	#define REG087	0x87
	#define REG088	0x88
	#define REG089	0x89
	#define REG08A	0x8A
	#define REG08B	0x8B
	#define REG08C	0x8C
	#define REG08D	0x8D
	#define REG08E	0x8E
	#define REG08F	0x8F

	#define REG090	0x90
	#define REG091	0x91
	#define REG092	0x92
	#define REG093	0x93
	#define REG094	0x94
	#define REG095	0x95
	#define REG096	0x96
	#define REG097	0x97
	#define REG098	0x98
	#define REG099	0x99
	#define REG09A	0x9A
	#define REG09B	0x9B
	#define REG09C	0x9C
	#define REG09D	0x9D
	#define REG09E	0x9E
	#define REG09F	0x9F

	#define REG0A0	0xA0
	#define REG0A1	0xA1
	#define REG0A2	0xA2
	#define REG0A3	0xA3
	#define REG0A4	0xA4
	#define REG0A5	0xA5
	#define REG0A6	0xA6
	#define REG0A7	0xA7
	#define REG0A8	0xA8
	#define REG0A9	0xA9
	#define REG0AA	0xAA
	#define REG0AB	0xAB
	#define REG0AC	0xAC
	#define REG0AD	0xAD
	#define REG0AE	0xAE
	#define REG0AF	0xAF

	#define REG0B0	0xB0
	#define REG0B1	0xB1
	#define REG0B2	0xB2
	#define REG0B3	0xB3
	#define REG0B4	0xB4
	#define REG0B5	0xB5
	#define REG0B6	0xB6
	#define REG0B7	0xB7
	#define REG0B8	0xB8
	#define REG0B9	0xB9
	#define REG0BA	0xBA
	#define REG0BB	0xBB
	#define REG0BC	0xBC
	#define REG0BD	0xBD
	#define REG0BE	0xBE
	#define REG0BF	0xBF

	#define REG0C0	0xC0
	#define REG0C1	0xC1
	#define REG0C2	0xC2
	#define REG0C3	0xC3
	#define REG0C4	0xC4
	#define REG0C5	0xC5
	#define REG0C6	0xC6
	#define REG0C7	0xC7
	#define REG0C8	0xC8
	#define REG0C9	0xC9
	#define REG0CA	0xCA
	#define REG0CB	0xCB
	#define REG0CC	0xCC
	#define REG0CD	0xCD
	#define REG0CE	0xCE
	#define REG0CF	0xCF

	#define REG0D0	0xD0
	#define REG0D1	0xD1
	#define REG0D2	0xD2
	#define REG0D3	0xD3
	#define REG0D4	0xD4
	#define REG0D5	0xD5
	#define REG0D6	0xD6
	#define REG0D7	0xD7
	#define REG0D8	0xD8
	#define REG0D9	0xD9
	#define REG0DA	0xDA
	#define REG0DB	0xDB
	#define REG0DC	0xDC
	#define REG0DD	0xDD
	#define REG0DE	0xDE
	#define REG0DF	0xDF

	#define REG0E0	0xE0
	#define REG0E1	0xE1
	#define REG0E2	0xE2
	#define REG0E3	0xE3
	#define REG0E4	0xE4
	#define REG0E5	0xE5
	#define REG0E6	0xE6
	#define REG0E7	0xE7
	#define REG0E8	0xE8
	#define REG0E9	0xE9
	#define REG0EA	0xEA
	#define REG0EB	0xEB
	#define REG0EC	0xEC
	#define REG0ED	0xED
	#define REG0EE	0xEE
	#define REG0EF	0xEF

	#define REG0F0	0xF0
	#define REG0F1	0xF1
	#define REG0F2	0xF2
	#define REG0F3	0xF3
	#define REG0F4	0xF4
	#define REG0F5	0xF5
	#define REG0F6	0xF6
	#define REG0F7	0xF7
	#define REG0F8	0xF8
	#define REG0F9	0xF9
	#define REG0FA	0xFA
	#define REG0FB	0xFB
	#define REG0FC	0xFC
	#define REG0FD	0xFD
	#define REG0FE	0xFE
	//#define REG0FF	0xFF

//===========================
// PAGE 1
//===========================
	#define REG100	0x00
	#define REG101	0x01
	#define REG102	0x02
	#define REG103	0x03
	#define REG104	0x04
	#define REG105	0x05
	#define REG106	0x06
	#define REG107	0x07
	#define REG108	0x08
	#define REG109	0x09
	#define REG10A	0x0A
	#define REG10B	0x0B
	#define REG10C	0x0C
	#define REG10D	0x0D
	#define REG10E	0x0E
	#define REG10F	0x0F

	#define REG110	0x10
	#define REG111	0x11
	#define REG112	0x12
	#define REG113	0x13
	#define REG114	0x14
	#define REG115	0x15
	#define REG116	0x16
	#define REG117	0x17
	#define REG118	0x18
	#define REG119	0x19
	#define REG11A	0x1A
	#define REG11B	0x1B
	#define REG11C	0x1C
	#define REG11D	0x1D
	#define REG11E	0x1E
	#define REG11F	0x1F

	#define REG120	0x20
	#define REG121	0x21
	#define REG122	0x22
	#define REG123	0x23
	#define REG124	0x24
	#define REG125	0x25
	#define REG126	0x26
	#define REG127	0x27
	#define REG128	0x28
	#define REG129	0x29
	#define REG12A	0x2A
	#define REG12B	0x2B
	#define REG12C	0x2C
	#define REG12D	0x2D
	#define REG12E	0x2E
	#define REG12F	0x2F

	#define REG130	0x30
	#define REG131	0x31
	#define REG132	0x32
	#define REG133	0x33
	#define REG134	0x34
	#define REG135	0x35
	#define REG136	0x36
	#define REG137	0x37
	#define REG138	0x38
	#define REG139	0x39
	#define REG13A	0x3A
	#define REG13B	0x3B
	#define REG13C	0x3C
	#define REG13D	0x3D
	#define REG13E	0x3E
	#define REG13F	0x3F

	#define REG140	0x40
	#define REG141	0x41
	#define REG142	0x42
	#define REG143	0x43
	#define REG144	0x44
	#define REG145	0x45
	#define REG146	0x46
	#define REG147	0x47
	#define REG148	0x48
	#define REG149	0x49
	#define REG14A	0x4A
	#define REG14B	0x4B
	#define REG14C	0x4C
	#define REG14D	0x4D
	#define REG14E	0x4E
	#define REG14F	0x4F

	#define REG150	0x50
	#define REG151	0x51
	#define REG152	0x52
	#define REG153	0x53
	#define REG154	0x54
	#define REG155	0x55
	#define REG156	0x56
	#define REG157	0x57
	#define REG158	0x58
	#define REG159	0x59
	#define REG15A	0x5A
	#define REG15B	0x5B
	#define REG15C	0x5C
	#define REG15D	0x5D
	#define REG15E	0x5E
	#define REG15F	0x5F

	#define REG160	0x60
	#define REG161	0x61
	#define REG162	0x62
	#define REG163	0x63
	#define REG164	0x64
	#define REG165	0x65
	#define REG166	0x66
	#define REG167	0x67
	#define REG168	0x68
	#define REG169	0x69
	#define REG16A	0x6A
	#define REG16B	0x6B
	#define REG16C	0x6C
	#define REG16D	0x6D
	#define REG16E	0x6E
	#define REG16F	0x6F

	#define REG170	0x70
	#define REG171	0x71
	#define REG172	0x72
	#define REG173	0x73
	#define REG174	0x74
	#define REG175	0x75
	#define REG176	0x76
	#define REG177	0x77
	#define REG178	0x78
	#define REG179	0x79
	#define REG17A	0x7A
	#define REG17B	0x7B
	#define REG17C	0x7C
	#define REG17D	0x7D
	#define REG17E	0x7E
	#define REG17F	0x7F

	#define REG180	0x80
	#define REG181	0x81
	#define REG182	0x82
	#define REG183	0x83
	#define REG184	0x84
	#define REG185	0x85
	#define REG186	0x86
	#define REG187	0x87
	#define REG188	0x88
	#define REG189	0x89
	#define REG18A	0x8A
	#define REG18B	0x8B
	#define REG18C	0x8C
	#define REG18D	0x8D
	#define REG18E	0x8E
	#define REG18F	0x8F

	#define REG190	0x90
	#define REG191	0x91
	#define REG192	0x92
	#define REG193	0x93
	#define REG194	0x94
	#define REG195	0x95
	#define REG196	0x96
	#define REG197	0x97
	#define REG198	0x98
	#define REG199	0x99
	#define REG19A	0x9A
	#define REG19B	0x9B
	#define REG19C	0x9C
	#define REG19D	0x9D
	#define REG19E	0x9E
	#define REG19F	0x9F

	#define REG1A0	0xA0
	#define REG1A1	0xA1
	#define REG1A2	0xA2
	#define REG1A3	0xA3
	#define REG1A4	0xA4
	#define REG1A5	0xA5
	#define REG1A6	0xA6
	#define REG1A7	0xA7
	#define REG1A8	0xA8
	#define REG1A9	0xA9
	#define REG1AA	0xAA
	#define REG1AB	0xAB
	#define REG1AC	0xAC
	#define REG1AD	0xAD
	#define REG1AE	0xAE
	#define REG1AF	0xAF

	#define REG1B0	0xB0
	#define REG1B1	0xB1
	#define REG1B2	0xB2
	#define REG1B3	0xB3
	#define REG1B4	0xB4
	#define REG1B5	0xB5
	#define REG1B6	0xB6
	#define REG1B7	0xB7
	#define REG1B8	0xB8
	#define REG1B9	0xB9
	#define REG1BA	0xBA
	#define REG1BB	0xBB
	#define REG1BC	0xBC
	#define REG1BD	0xBD
	#define REG1BE	0xBE
	#define REG1BF	0xBF

	#define REG1C0	0xC0
	#define REG1C1	0xC1
	#define REG1C2	0xC2
	#define REG1C3	0xC3
	#define REG1C4	0xC4
	#define REG1C5	0xC5
	#define REG1C6	0xC6
	#define REG1C7	0xC7
	#define REG1C8	0xC8
	#define REG1C9	0xC9
	#define REG1CA	0xCA
	#define REG1CB	0xCB
	#define REG1CC	0xCC
	#define REG1CD	0xCD
	#define REG1CE	0xCE
	#define REG1CF	0xCF

	#define REG1D0	0xD0
	#define REG1D1	0xD1
	#define REG1D2	0xD2
	#define REG1D3	0xD3
	#define REG1D4	0xD4
	#define REG1D5	0xD5
	#define REG1D6	0xD6
	#define REG1D7	0xD7
	#define REG1D8	0xD8
	#define REG1D9	0xD9
	#define REG1DA	0xDA
	#define REG1DB	0xDB
	#define REG1DC	0xDC
	#define REG1DD	0xDD
	#define REG1DE	0xDE
	#define REG1DF	0xDF

	#define REG1E0	0xE0
	#define REG1E1	0xE1
	#define REG1E2	0xE2
	#define REG1E3	0xE3
	#define REG1E4	0xE4
	#define REG1E5	0xE5
	#define REG1E6	0xE6
	#define REG1E7	0xE7
	#define REG1E8	0xE8
	#define REG1E9	0xE9
	#define REG1EA	0xEA
	#define REG1EB	0xEB
	#define REG1EC	0xEC
	#define REG1ED	0xED
	#define REG1EE	0xEE
	#define REG1EF	0xEF

	#define REG1F0	0xF0
	#define REG1F1	0xF1
	#define REG1F2	0xF2
	#define REG1F3	0xF3
	#define REG1F4	0xF4
	#define REG1F5	0xF5
	#define REG1F6	0xF6
	#define REG1F7	0xF7
	#define REG1F8	0xF8
	#define REG1F9	0xF9
	#define REG1FA	0xFA
	#define REG1FB	0xFB
	#define REG1FC	0xFC
	#define REG1FD	0xFD
	#define REG1FE	0xFE
	//#define REG1FF	0xFF
//===========================
// PAGE 2
//===========================
	#define REG200	0x00
	#define REG201	0x01
	#define REG202	0x02
	#define REG203	0x03
	#define REG204	0x04
	#define REG205	0x05
	#define REG206	0x06
	#define REG207	0x07
	#define REG208	0x08
	#define REG209	0x09
	#define REG20A	0x0A
	#define REG20B	0x0B
	#define REG20C	0x0C
	#define REG20D	0x0D
	#define REG20E	0x0E
	#define REG20F	0x0F

	#define REG210	0x10
	#define REG211	0x11
	#define REG212	0x12
	#define REG213	0x13
	#define REG214	0x14
	#define REG215	0x15
	#define REG216	0x16
	#define REG217	0x17
	#define REG218	0x18
	#define REG219	0x19
	#define REG21A	0x1A
	#define REG21B	0x1B
	#define REG21C	0x1C
	#define REG21D	0x1D
	#define REG21E	0x1E
	#define REG21F	0x1F

	#define REG220	0x20
	#define REG221	0x21
	#define REG222	0x22
	#define REG223	0x23
	#define REG224	0x24
	#define REG225	0x25
	#define REG226	0x26
	#define REG227	0x27
	#define REG228	0x28
	#define REG229	0x29
	#define REG22A	0x2A
	#define REG22B	0x2B
	#define REG22C	0x2C
	#define REG22D	0x2D
	#define REG22E	0x2E
	#define REG22F	0x2F

	#define REG230	0x30
	#define REG231	0x31
	#define REG232	0x32
	#define REG233	0x33
	#define REG234	0x34
	#define REG235	0x35
	#define REG236	0x36
	#define REG237	0x37
	#define REG238	0x38
	#define REG239	0x39
	#define REG23A	0x3A
	#define REG23B	0x3B
	#define REG23C	0x3C
	#define REG23D	0x3D
	#define REG23E	0x3E
	#define REG23F	0x3F

	#define REG240	0x40
	#define REG241	0x41
	#define REG242	0x42
	#define REG243	0x43
	#define REG244	0x44
	#define REG245	0x45
	#define REG246	0x46
	#define REG247	0x47
	#define REG248	0x48
	#define REG249	0x49
	#define REG24A	0x4A
	#define REG24B	0x4B
	#define REG24C	0x4C
	#define REG24D	0x4D
	#define REG24E	0x4E
	#define REG24F	0x4F

	#define REG250	0x50
	#define REG251	0x51
	#define REG252	0x52
	#define REG253	0x53
	#define REG254	0x54
	#define REG255	0x55
	#define REG256	0x56
	#define REG257	0x57
	#define REG258	0x58
	#define REG259	0x59
	#define REG25A	0x5A
	#define REG25B	0x5B
	#define REG25C	0x5C
	#define REG25D	0x5D
	#define REG25E	0x5E
	#define REG25F	0x5F

	#define REG260	0x60
	#define REG261	0x61
	#define REG262	0x62
	#define REG263	0x63
	#define REG264	0x64
	#define REG265	0x65
	#define REG266	0x66
	#define REG267	0x67
	#define REG268	0x68
	#define REG269	0x69
	#define REG26A	0x6A
	#define REG26B	0x6B
	#define REG26C	0x6C
	#define REG26D	0x6D
	#define REG26E	0x6E
	#define REG26F	0x6F

	#define REG270	0x70
	#define REG271	0x71
	#define REG272	0x72
	#define REG273	0x73
	#define REG274	0x74
	#define REG275	0x75
	#define REG276	0x76
	#define REG277	0x77
	#define REG278	0x78
	#define REG279	0x79
	#define REG27A	0x7A
	#define REG27B	0x7B
	#define REG27C	0x7C
	#define REG27D	0x7D
	#define REG27E	0x7E
	#define REG27F	0x7F

	#define REG280	0x80
	#define REG281	0x81
	#define REG282	0x82
	#define REG283	0x83
	#define REG284	0x84
	#define REG285	0x85
	#define REG286	0x86
	#define REG287	0x87
	#define REG288	0x88
	#define REG289	0x89
	#define REG28A	0x8A
	#define REG28B	0x8B
	#define REG28C	0x8C
	#define REG28D	0x8D
	#define REG28E	0x8E
	#define REG28F	0x8F

	#define REG290	0x90
	#define REG291	0x91
	#define REG292	0x92
	#define REG293	0x93
	#define REG294	0x94
	#define REG295	0x95
	#define REG296	0x96
	#define REG297	0x97
	#define REG298	0x98
	#define REG299	0x99
	#define REG29A	0x9A
	#define REG29B	0x9B
	#define REG29C	0x9C
	#define REG29D	0x9D
	#define REG29E	0x9E
	#define REG29F	0x9F

	#define REG2A0	0xA0
	#define REG2A1	0xA1
	#define REG2A2	0xA2
	#define REG2A3	0xA3
	#define REG2A4	0xA4
	#define REG2A5	0xA5
	#define REG2A6	0xA6
	#define REG2A7	0xA7
	#define REG2A8	0xA8
	#define REG2A9	0xA9
	#define REG2AA	0xAA
	#define REG2AB	0xAB
	#define REG2AC	0xAC
	#define REG2AD	0xAD
	#define REG2AE	0xAE
	#define REG2AF	0xAF

	#define REG2B0	0xB0
	#define REG2B1	0xB1
	#define REG2B2	0xB2
	#define REG2B3	0xB3
	#define REG2B4	0xB4
	#define REG2B5	0xB5
	#define REG2B6	0xB6
	#define REG2B7	0xB7
	#define REG2B8	0xB8
	#define REG2B9	0xB9
	#define REG2BA	0xBA
	#define REG2BB	0xBB
	#define REG2BC	0xBC
	#define REG2BD	0xBD
	#define REG2BE	0xBE
	#define REG2BF	0xBF

	#define REG2C0	0xC0
	#define REG2C1	0xC1
	#define REG2C2	0xC2
	#define REG2C3	0xC3
	#define REG2C4	0xC4
	#define REG2C5	0xC5
	#define REG2C6	0xC6
	#define REG2C7	0xC7
	#define REG2C8	0xC8
	#define REG2C9	0xC9
	#define REG2CA	0xCA
	#define REG2CB	0xCB
	#define REG2CC	0xCC
	#define REG2CD	0xCD
	#define REG2CE	0xCE
	#define REG2CF	0xCF

	#define REG2D0	0xD0
	#define REG2D1	0xD1
	#define REG2D2	0xD2
	#define REG2D3	0xD3
	#define REG2D4	0xD4
	#define REG2D5	0xD5
	#define REG2D6	0xD6
	#define REG2D7	0xD7
	#define REG2D8	0xD8
	#define REG2D9	0xD9
	#define REG2DA	0xDA
	#define REG2DB	0xDB
	#define REG2DC	0xDC
	#define REG2DD	0xDD
	#define REG2DE	0xDE
	#define REG2DF	0xDF

	#define REG2E0	0xE0
	#define REG2E1	0xE1
	#define REG2E2	0xE2
	#define REG2E3	0xE3
	#define REG2E4	0xE4
	#define REG2E5	0xE5
	#define REG2E6	0xE6
	#define REG2E7	0xE7
	#define REG2E8	0xE8
	#define REG2E9	0xE9
	#define REG2EA	0xEA
	#define REG2EB	0xEB
	#define REG2EC	0xEC
	#define REG2ED	0xED
	#define REG2EE	0xEE
	#define REG2EF	0xEF

	#define REG2F0	0xF0
	#define REG2F1	0xF1
	#define REG2F2	0xF2
	#define REG2F3	0xF3
	#define REG2F4	0xF4
	#define REG2F5	0xF5
	#define REG2F6	0xF6
	#define REG2F7	0xF7
	#define REG2F8	0xF8
	#define REG2F9	0xF9
	#define REG2FA	0xFA
	#define REG2FB	0xFB
	#define REG2FC	0xFC
	#define REG2FD	0xFD
	#define REG2FE	0xFE
	//#define REG2FF	0xFF

//===========================
// PAGE 3
//===========================
	#define REG300	0x00
	#define REG301	0x01
	#define REG302	0x02
	#define REG303	0x03
	#define REG304	0x04
	#define REG305	0x05
	#define REG306	0x06
	#define REG307	0x07
	#define REG308	0x08
	#define REG309	0x09
	#define REG30A	0x0A
	#define REG30B	0x0B
	#define REG30C	0x0C
	#define REG30D	0x0D
	#define REG30E	0x0E
	#define REG30F	0x0F

	#define REG310	0x10
	#define REG311	0x11
	#define REG312	0x12
	#define REG313	0x13
	#define REG314	0x14
	#define REG315	0x15
	#define REG316	0x16
	#define REG317	0x17
	#define REG318	0x18
	#define REG319	0x19
	#define REG31A	0x1A
	#define REG31B	0x1B
	#define REG31C	0x1C
	#define REG31D	0x1D
	#define REG31E	0x1E
	#define REG31F	0x1F

	#define REG320	0x20
	#define REG321	0x21
	#define REG322	0x22
	#define REG323	0x23
	#define REG324	0x24
	#define REG325	0x25
	#define REG326	0x26
	#define REG327	0x27
	#define REG328	0x28
	#define REG329	0x29
	#define REG32A	0x2A
	#define REG32B	0x2B
	#define REG32C	0x2C
	#define REG32D	0x2D
	#define REG32E	0x2E
	#define REG32F	0x2F

	#define REG330	0x30
	#define REG331	0x31
	#define REG332	0x32
	#define REG333	0x33
	#define REG334	0x34
	#define REG335	0x35
	#define REG336	0x36
	#define REG337	0x37
	#define REG338	0x38
	#define REG339	0x39
	#define REG33A	0x3A
	#define REG33B	0x3B
	#define REG33C	0x3C
	#define REG33D	0x3D
	#define REG33E	0x3E
	#define REG33F	0x3F

	#define REG340	0x40
	#define REG341	0x41
	#define REG342	0x42
	#define REG343	0x43
	#define REG344	0x44
	#define REG345	0x45
	#define REG346	0x46
	#define REG347	0x47
	#define REG348	0x48
	#define REG349	0x49
	#define REG34A	0x4A
	#define REG34B	0x4B
	#define REG34C	0x4C
	#define REG34D	0x4D
	#define REG34E	0x4E
	#define REG34F	0x4F

	#define REG350	0x50
	#define REG351	0x51
	#define REG352	0x52
	#define REG353	0x53
	#define REG354	0x54
	#define REG355	0x55
	#define REG356	0x56
	#define REG357	0x57
	#define REG358	0x58
	#define REG359	0x59
	#define REG35A	0x5A
	#define REG35B	0x5B
	#define REG35C	0x5C
	#define REG35D	0x5D
	#define REG35E	0x5E
	#define REG35F	0x5F

	#define REG360	0x60
	#define REG361	0x61
	#define REG362	0x62
	#define REG363	0x63
	#define REG364	0x64
	#define REG365	0x65
	#define REG366	0x66
	#define REG367	0x67
	#define REG368	0x68
	#define REG369	0x69
	#define REG36A	0x6A
	#define REG36B	0x6B
	#define REG36C	0x6C
	#define REG36D	0x6D
	#define REG36E	0x6E
	#define REG36F	0x6F

	#define REG370	0x70
	#define REG371	0x71
	#define REG372	0x72
	#define REG373	0x73
	#define REG374	0x74
	#define REG375	0x75
	#define REG376	0x76
	#define REG377	0x77
	#define REG378	0x78
	#define REG379	0x79
	#define REG37A	0x7A
	#define REG37B	0x7B
	#define REG37C	0x7C
	#define REG37D	0x7D
	#define REG37E	0x7E
	#define REG37F	0x7F

	#define REG380	0x80
	#define REG381	0x81
	#define REG382	0x82
	#define REG383	0x83
	#define REG384	0x84
	#define REG385	0x85
	#define REG386	0x86
	#define REG387	0x87
	#define REG388	0x88
	#define REG389	0x89
	#define REG38A	0x8A
	#define REG38B	0x8B
	#define REG38C	0x8C
	#define REG38D	0x8D
	#define REG38E	0x8E
	#define REG38F	0x8F

	#define REG390	0x90
	#define REG391	0x91
	#define REG392	0x92
	#define REG393	0x93
	#define REG394	0x94
	#define REG395	0x95
	#define REG396	0x96
	#define REG397	0x97
	#define REG398	0x98
	#define REG399	0x99
	#define REG39A	0x9A
	#define REG39B	0x9B
	#define REG39C	0x9C
	#define REG39D	0x9D
	#define REG39E	0x9E
	#define REG39F	0x9F

	#define REG3A0	0xA0
	#define REG3A1	0xA1
	#define REG3A2	0xA2
	#define REG3A3	0xA3
	#define REG3A4	0xA4
	#define REG3A5	0xA5
	#define REG3A6	0xA6
	#define REG3A7	0xA7
	#define REG3A8	0xA8
	#define REG3A9	0xA9
	#define REG3AA	0xAA
	#define REG3AB	0xAB
	#define REG3AC	0xAC
	#define REG3AD	0xAD
	#define REG3AE	0xAE
	#define REG3AF	0xAF

	#define REG3B0	0xB0
	#define REG3B1	0xB1
	#define REG3B2	0xB2
	#define REG3B3	0xB3
	#define REG3B4	0xB4
	#define REG3B5	0xB5
	#define REG3B6	0xB6
	#define REG3B7	0xB7
	#define REG3B8	0xB8
	#define REG3B9	0xB9
	#define REG3BA	0xBA
	#define REG3BB	0xBB
	#define REG3BC	0xBC
	#define REG3BD	0xBD
	#define REG3BE	0xBE
	#define REG3BF	0xBF

	#define REG3C0	0xC0
	#define REG3C1	0xC1
	#define REG3C2	0xC2
	#define REG3C3	0xC3
	#define REG3C4	0xC4
	#define REG3C5	0xC5
	#define REG3C6	0xC6
	#define REG3C7	0xC7
	#define REG3C8	0xC8
	#define REG3C9	0xC9
	#define REG3CA	0xCA
	#define REG3CB	0xCB
	#define REG3CC	0xCC
	#define REG3CD	0xCD
	#define REG3CE	0xCE
	#define REG3CF	0xCF

	#define REG3D0	0xD0
	#define REG3D1	0xD1
	#define REG3D2	0xD2
	#define REG3D3	0xD3
	#define REG3D4	0xD4
	#define REG3D5	0xD5
	#define REG3D6	0xD6
	#define REG3D7	0xD7
	#define REG3D8	0xD8
	#define REG3D9	0xD9
	#define REG3DA	0xDA
	#define REG3DB	0xDB
	#define REG3DC	0xDC
	#define REG3DD	0xDD
	#define REG3DE	0xDE
	#define REG3DF	0xDF

	#define REG3E0	0xE0
	#define REG3E1	0xE1
	#define REG3E2	0xE2
	#define REG3E3	0xE3
	#define REG3E4	0xE4
	#define REG3E5	0xE5
	#define REG3E6	0xE6
	#define REG3E7	0xE7
	#define REG3E8	0xE8
	#define REG3E9	0xE9
	#define REG3EA	0xEA
	#define REG3EB	0xEB
	#define REG3EC	0xEC
	#define REG3ED	0xED
	#define REG3EE	0xEE
	#define REG3EF	0xEF

	#define REG3F0	0xF0
	#define REG3F1	0xF1
	#define REG3F2	0xF2
	#define REG3F3	0xF3
	#define REG3F4	0xF4
	#define REG3F5	0xF5
	#define REG3F6	0xF6
	#define REG3F7	0xF7
	#define REG3F8	0xF8
	#define REG3F9	0xF9
	#define REG3FA	0xFA
	#define REG3FB	0xFB
	#define REG3FC	0xFC
	#define REG3FD	0xFD
	#define REG3FE	0xFE
//#define REG3FF	0xFF

//#define	ReadTW88(a, b)		I2C_BufferRead( TW8819_ADDRESS, a, b, 1, 0)
//#define	WriteTW88(a, b)		I2C_BufferWrite(TW8819_ADDRESS, a, b, 1, 0) // I2C_BufferWrite(uint8_t dev,uint16_t addr, uint8_t *buf, uint16_t len,uint8_t mode16)
//#define WriteTW88Page(a)	HAL_I2C_Master_Transmit(&hi2c2, TW8819_ADDRESS, a, 2, 1000);//I2C_BufferWrite(TW8819_ADDRESS, 0xff, a, 1, 0) uint8_t I2C_BufferWrite(uint8_t dev,uint16_t addr, uint8_t *buf, uint16_t len,uint8_t mode16)

uint16_t SetYCbCrContrast(uint16_t val);
uint16_t ReadYCbCrContrast(void);
uint16_t SetYCbCrBright(uint16_t val);
uint16_t ReadYCbCrBright(void);
uint16_t SetYCbCrSaturation(uint16_t val);
uint16_t ReadYCbCrSaturation(void);
uint16_t SetYCbCrHUE(uint16_t val);
uint16_t ReadYCbCrHUE(void);
uint16_t SetYCbCrSharp(uint16_t val);
uint16_t ReadYCbCrSharp(void);


////////////
uint8_t ReadTW88(uint8_t addr, uint8_t* buf ); 
uint8_t WriteTW88(uint8_t addr, uint8_t* buf);
uint8_t WriteTW88Page(uint8_t* buf);
//


void BD_Init_TW8819();
void ReadTW8819ID(void);
void Switch_Camera(uint8_t cam);
uint8_t ChangeCVBS(void);
void LCD_Video_GPIO_Deinit(void);
void LCD_Video_GPIO_Init(void);

#endif