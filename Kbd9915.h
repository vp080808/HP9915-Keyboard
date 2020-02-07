
typedef unsigned char uchar;
typedef unsigned short ushort;
typedef unsigned int uint;

/*
 * Conversion table -- maps ASCII code to ROW/COL
 * on the HP-85 keyboard
 */
struct ascii2hp85tblent {
        uchar   a2h_sc;     // format is 0cccrrrr 
        ushort  a2h_cc;     // ASCII char or extended code
        uchar   a2h_ctrl;   // CTRL key flag
        uchar   a2h_shift;  // Shift Key flag
};

#define HP_KDB_DOWN         0x0100
#define HP_KBD_AUTO         0x0101
#define HP_KDB_LEFT         0x0102
#define HP_KDB_UP           0x0104
#define HP_KDB_HOME         0x0105
#define HP_KDB_RIGHT        0x0106
#define HP_KDB_COPY         0x0107
#define HP_KDB_K4           0x0108
#define HP_KDB_K8           0x0109
#define HP_KDB_INS_RPL      0x0110
#define HP_KDB_K7           0x0113
#define HP_KDB_PAUSE        0x0114
#define HP_KDB_STEP         0x0115
#define HP_KDB_ENDLINE      0x0116
#define HP_KDB_CHAR         0x0117
#define HP_KDB_DEL          0x0118
#define HP_KDB_K2           0x0119
#define HP_KDB_K6           0x0120
#define HP_KDB_RUN          0x0121
#define HP_KDB_LIST         0x0122
#define HP_KDB_PLST         0x0123
#define HP_KDB_CONT         0x0124
#define HP_KDB_SCRATCH      0x0125
#define HP_KDB_ROLLDN       0x0126
#define HP_KDB_ROLLUP       0x0127
#define HP_KDB_K1           0x0128
#define HP_KDB_K5           0x0129
#define HP_KDB_LINE         0x0130
#define HP_KDB_CLEAR        0x0131
#define HP_KDB_BS           0x0132
#define HP_KDB_LOAD         0x0133
#define HP_KDB_REW          0x0134
#define HP_KDB_KEYLBL       0x0135
#define HP_KDB_INIT         0x0136
#define HP_KDB_RESET        0x0137
#define HP_KDB_STORE        0x0138
#define HP_KDB_TEST         0x0139
#define HP_KDB_RESLT        0x0140
#define HP_KDB_PAPADV       0x0141
#define HP_KDB_K3           0x0142
#define HP_KDB_GRAPH        0x0143
#define HP_KBD_KPD_PLUS     0x0144
#define HP_KBD_KPD_MINUS    0x0145
#define HP_KBD_KPD_MUL      0x0146
#define HP_KBD_KPD_DIV      0x0147
#define HP_KBD_KPD_LBRA     0x0148
#define HP_KBD_KPD_RBRA     0x0149
#define HP_KBD_KPD_CART     0x014A

// Control Codes
#define HP_KDB_CNULL        0x0200
#define HP_KDB_CA           0x0201
#define HP_KDB_CB           0x0202
#define HP_KDB_CC           0x0203
#define HP_KDB_CD           0x0204
#define HP_KDB_CE           0x0205
#define HP_KDB_CF           0x0206
#define HP_KDB_CG           0x0207
#define HP_KDB_CH           0x0208
#define HP_KDB_CI           0x0209
#define HP_KDB_CJ           0x020A
#define HP_KDB_CK           0x020B
#define HP_KDB_CL           0x020C
#define HP_KDB_CM           0x020D
#define HP_KDB_CN           0x020E
#define HP_KDB_CO           0x020F
#define HP_KDB_CP           0x0210
#define HP_KDB_CQ           0x0211
#define HP_KDB_CR           0x0212
#define HP_KDB_CS           0x0213
#define HP_KDB_CT           0x0214
#define HP_KDB_CU           0x0215
#define HP_KDB_CV           0x0216
#define HP_KDB_CW           0x0217
#define HP_KDB_CX           0x0218
#define HP_KDB_CY           0x0219
#define HP_KDB_CZ           0x021A
#define HP_KDB_CLBRA        0x021B
#define HP_KDB_CBSL         0x021C
#define HP_KDB_CRBRA        0x021D
#define HP_KDB_CCART        0x021E
#define HP_KDB_CUSCOR       0x021F

#define HP_KDB_CDEL         0x027F

#define HP_KDB_UNKNOWN      0x0FFF

/*
 * The following table may be confusing because 
 * the search is on the 2nd entry, e.g. in the
 * case of, say, the down-arrow key, the lookup
 * code has the HP_KDB_DOWN code and will look into
 * the table to find the grid lines to cross
 * the cccrrrr code in the 1st entry and to
 * find whether Shift and/or Ctrl need to be
 * pressed as well (entries 3 and 4 respectively).
 */
static struct ascii2hp85tblent conv_tbl[] = {

    // format is 0cccrrrr 
    // cccrrrr   ascii          ctrl  shift
    { 0x00,   HP_KDB_DOWN,        0,  0 },
    { 0x00,   HP_KBD_AUTO,        0,  1 },
    { 0x01,   '8',                0,  0 },
    { 0x01,   '*',                0,  1 },
    { 0x02,   'I',                0,  0 },
    { 0x02,   'i',                0,  1 },
    { 0x02,   HP_KDB_CI,          1,  0 },
    { 0x03,   'K',                0,  0 },
    { 0x03,   'k',                0,  1 },
    { 0x03,   HP_KDB_CK,          1,  0 },
    { 0x04,   'M',                0,  0 },
    { 0x04,   'm',                0,  1 },
    { 0x04,   HP_KDB_CM,          1,  0 },
    { 0x05,   ',',                0,  0 },
    { 0x05,   '<',                0,  1 },
    { 0x06,   'L',                0,  0 },   
    { 0x06,   'l',                0,  1 },
    { 0x06,   HP_KDB_CL,          1,  0 },
    { 0x07,   'O',                0,  0 },
    { 0x07,   'o',                0,  1 },
    { 0x07,   HP_KDB_CO,          1,  0 },
    { 0x08,   '9',                0,  0 },
    { 0x08,   '(',                0,  1 },
    { 0x09,   HP_KDB_LEFT,        0,  0 },
    { 0x09,   HP_KDB_GRAPH,       0,  1 },
  
    { 0x10,   HP_KDB_UP,          0,  0 },
    { 0x10,   HP_KDB_HOME,        0,  1 },
    { 0x11,   '7',                0,  0 },
    { 0x11,   '&',                0,  1 },
    { 0x12,   'U',                0,  0 },
    { 0x12,   'u',                0,  1 },
    { 0x12,   HP_KDB_CU,          1,  0 },
    { 0x13,   'J',                0,  0 },
    { 0x13,   'j',                0,  1 },
    { 0x13,   HP_KDB_CJ,          1,  0 },
    { 0x14,   'N',                0,  0 },
    { 0x14,   'n',                0,  1 },
    { 0x14,   HP_KDB_CN,          1,  0 },
    { 0x15,   '.',                0,  0 },
    { 0x15,   '>',                0,  1 },
    { 0x16,   ';',                0,  0 },
    { 0x16,   ':',                0,  1 },
    { 0x17,   'P',                0,  0 },
    { 0x17,   'p',                0,  1 },
    { 0x17,   HP_KDB_CP,          1,  0 },
    { 0x18,   '0',                0,  0 },
    { 0x18,   ')',                0,  1 },
    { 0x19,   HP_KDB_RIGHT,       0,  0 },
    { 0x19,   HP_KDB_COPY,        0,  1 },
    
    { 0x20,   HP_KDB_K4,          0,  0 },
    { 0x20,   HP_KDB_K8,          0,  1 },
    { 0x21,   '6',                0,  0 },
    { 0x21,   '^',                0,  1 },
    { 0x22,   'Y',                0,  0 },
    { 0x22,   'y',                0,  1 },
    { 0x22,   HP_KDB_CY,          1,  0 },
    { 0x23,   'H',                0,  0 },
    { 0x23,   'h',                0,  1 },
    { 0x23,   HP_KDB_CH,          1,  0 },
    { 0x24,   'B',                0,  0 },
    { 0x24,   'b',                0,  1 },
    { 0x24,   HP_KDB_CB,          1,  0 },
    { 0x25,   '/',                0,  0 },
    { 0x25,   '?',                0,  1 },
    { 0x26,   '\'',               0,  0 },
    { 0x26,   '"',                0,  1 },
    { 0x27,   '(',                0,  0 },
    { 0x27,   '[',                0,  1 },
    { 0x27,   HP_KDB_CLBRA,       1,  1 },
    { 0x28,   '-',                0,  0 },
    { 0x28,   '_',                0,  1 },
    { 0x28,   HP_KDB_CUSCOR,      1,  1 },
    
    
    { 0x29,   HP_KDB_INS_RPL,     0,  0 },
    { 0x29,   HP_KDB_INS_RPL,     0,  1 },
    
    { 0x30,   HP_KDB_K3,          0,  0 },
    { 0x30,   HP_KDB_K7,          0,  1 },
    { 0x31,   '5',                0,  0 },
    { 0x31,   '%',                0,  1 },
    { 0x32,   'T',                0,  0 },
    { 0x32,   't',                0,  1 },
    { 0x32,   HP_KDB_CT,          1,  0 },
    { 0x33,   'G',                0,  0 },
    { 0x33,   'g',                0,  1 },
    { 0x33,   HP_KDB_CG,          1,  0 },
    { 0x34,   'V',                0,  0 },
    { 0x34,   'v',                0,  1 },
    { 0x34,   HP_KDB_CV,          1,  0 },
    { 0x35,   HP_KDB_PAUSE,       0,  0 },
    { 0x35,   HP_KDB_STEP,        0,  1 },
    { 0x36,   HP_KDB_ENDLINE,     0,  0 },
    //36,
    { 0x37,   ')',                0,  0 },
    { 0x37,   ']',                0,  1 },
    { 0x37,   HP_KDB_CRBRA,       1,  1 },
    { 0x38,   '=',                0,  0 },
    { 0x38,   '+',                0,  1 },
    { 0x39,   HP_KDB_CHAR,        0,  0 },
    { 0x39,   HP_KDB_DEL,         0,  1 },
    
    { 0x40,   HP_KDB_K2,          0,  0 },
    { 0x40,   HP_KDB_K6,          0,  1 },
    { 0x41,   '4',                0,  0 },
    { 0x41,   '$',                0,  1 },
    { 0x42,   'R',                0,  0 },
    { 0x42,   'r',                0,  1 },
    { 0x42,   HP_KDB_CR,          1,  0 },
    { 0x43,   'F',                0,  0 },
    { 0x43,   'f',                0,  1 },
    { 0x43,   HP_KDB_CF,          1,  0 },
    { 0x44,   'C',                0,  0 },
    { 0x44,   'c',                0,  1 },
    { 0x44,   HP_KDB_CC,          1,  0 },
    { 0x45,   HP_KDB_RUN,         0,  0 },
    //45,
    { 0x46,   HP_KDB_LIST,        0,  0 },
    { 0x46,   HP_KDB_PLST,        0,  1 },
    { 0x47,   HP_KDB_CONT,        0,  0 },
    { 0x47,   HP_KDB_SCRATCH,     0,  1 },
    { 0x48,   '\\',               0,  0 },
    { 0x48,   HP_KDB_CBSL,        1,  0 },
    { 0x48,   '|',                0,  1 },
    { 0x49,   HP_KDB_ROLLDN,      0,  0 },
    { 0x49,   HP_KDB_ROLLUP,      0,  1 },
   
    { 0x50,   HP_KDB_K1,          0,  0 },
    { 0x50,   HP_KDB_K5,          0,  1 },
    { 0x51,   '3',                0,  0 },
    { 0x51,   '#',                0,  1 },
    { 0x52,   'E',                0,  0 },
    { 0x52,   'e',                0,  1 },
    { 0x52,   HP_KDB_CE,          1,  0 },
    { 0x53,   'D',                0,  0 },
    { 0x53,   'd',                0,  1 },
    { 0x53,   HP_KDB_CD,          1,  0 },
    { 0x54,   'X',                0,  0 },
    { 0x54,   'x',                0,  1 },
    { 0x54,   HP_KDB_CX,          1,  0 },
    { 0x55,   HP_KBD_KPD_PLUS,    0,  0 },
    { 0x55,   HP_KDB_CDEL,        0,  1 },
    //56,   
    //56,
    { 0x57,   HP_KDB_LINE,        0,  0 },
    { 0x57,   HP_KDB_CLEAR,       0,  1 },
    { 0x58,   HP_KDB_BS,          0,  0 },
    //58,
    { 0x59,   HP_KDB_LOAD,        0,  0 },
    { 0x59,   HP_KDB_REW,         0,  1 },
    
    { 0x60,   HP_KDB_KEYLBL,      0,  0 },
    { 0x60,   '`',                0,  1 },
    { 0x61,   '2',                0,  0 },
    { 0x61,   '@',                0,  1 },
    { 0x61,   HP_KDB_CNULL,       1,  1 },
    { 0x62,   'W',                0,  0 },
    { 0x62,   'w',                0,  1 },
    { 0x62,   HP_KDB_CW,          1,  0 },
    { 0x63,   'S',                0,  0 },
    { 0x63,   's',                0,  1 },
    { 0x63,   HP_KDB_CS,          1,  0 },
    { 0x64,   'Z',                0,  0 },
    { 0x64,   'z',                0,  1 },
    { 0x64,   HP_KDB_CZ,          1,  0 },
    { 0x65,   HP_KBD_KPD_MINUS,   0,  0 },
    { 0x65,   '}',                0,  1 },
    //65
    { 0x66,   HP_KBD_KPD_MUL,     0,  0 },
    //66,
    { 0x66,   '~',                0,  1 },
    { 0x67,   HP_KBD_KPD_RBRA,    0,  0 },
    { 0x67,   HP_KDB_INIT,        0,  1 },
    { 0x68,   HP_KBD_KPD_LBRA,    0,  0 },
    { 0x68,   HP_KDB_RESET,       0,  1 },
    { 0x69,   HP_KDB_STORE,       0,  0 },
    { 0x69,   HP_KDB_TEST,        0,  1 },
    
    //70
    //70
    { 0x71,   '1',                0,  0 },
    { 0x71,   '!',                0,  1 },
    { 0x72,   'Q',                0,  0 },
    { 0x72,   'q',                0,  1 },
    { 0x72,   HP_KDB_CQ,          1,  0 },
    { 0x73,   'A',                0,  0 },
    { 0x73,   'a',                0,  1 },
    { 0x73,   HP_KDB_CA,          1,  0 },
    { 0x74,   ' ',                0,  0 },
    //74,
    //75,   
    //75,
    { 0x76,   HP_KBD_KPD_DIV,     0,  0 },
    { 0x76,   '{',                0,  1 },
    //76,
    //77,
    //77,
    { 0x78,   HP_KBD_KPD_CART,    0,  0 },
    { 0x78,   HP_KDB_RESLT,       0,  1 },
    { 0x78,   HP_KDB_CCART,       1,  0 },
    { 0x79,   HP_KDB_PAPADV,      0,  0 },
    //79,
    { 0x79,   HP_KDB_UNKNOWN,     0,  0 }  // Paper Adv (on the 9915 is No Op)
};


/*
 * PS/2 EUR Keyboard map (converts PS/2 scancodes to 9915 keys
 *    This map is for the EURO keyboard (with the extra key
 *    between the left shift and the 'Z'.
 *    The US Keyboard will prob need a slightly different map
 *
 *    This table deals ONLY with one byte keys. Extended keys
 *    are dealt by code.
 */

#define PS2_9915_NF  0  // key not found in table
                        // by returning zero the key will be ignored

struct ps2_9915_map {
  ushort ps2keycode;
  ushort hp9915_normal;
  ushort hp9915_shifted;
} hp9915_ps2mapEU[] = {
// Row 1
  { 0x76,  HP_KDB_KEYLBL,  HP_KDB_KEYLBL    },  // ESC
  { 0x05,  HP_KDB_K1,      HP_KDB_K5        },  // F1
  { 0x06,  HP_KDB_K2,      HP_KDB_K6        },  // F2
  { 0x04,  HP_KDB_K3,      HP_KDB_K7        },  // F3
  { 0x0C,  HP_KDB_K4,      HP_KDB_K8        },  // F4

  { 0x03, HP_KDB_LOAD,    HP_KDB_REW        },  // F5
  { 0x0B, HP_KDB_STORE,   HP_KDB_STORE      },  // F6
  { 0x83, HP_KBD_KPD_LBRA, HP_KDB_RESET     },  // F7
  { 0x0A, HP_KBD_KPD_RBRA, HP_KDB_INIT      },  // F8
  
  { 0x01, HP_KBD_AUTO,    HP_KBD_AUTO       },  // F9
  { 0x09, HP_KDB_GRAPH,   HP_KDB_GRAPH      },  // F10
  { 0x78, HP_KDB_COPY,    HP_KDB_DEL        },  // F11
  { 0x07, HP_KDB_LIST,    HP_KDB_PLST       },  // F12

  { 0x7E, PS2_9915_NF,    HP_KDB_TEST       },  // Scroll Lock

// Row 2
  { 0x0E,  HP_KDB_PAUSE,   HP_KDB_STEP      },  // `
  { 0x16,  '1',  '!'  },
  { 0x1E,  '2',  '@'  },
  { 0x26,  '3',  '#'  },
  { 0x25,  '4',  '$'  },
  { 0x2E,  '5',  '%'  },
  { 0x36,  '6',  '^'  },
  { 0x3D,  '7',  '&'  },
  { 0x3E,  '8',  '*'  },
  { 0x46,  '9',  '('  },
  { 0x45,  '0',  ')'  },
  { 0x4E,  '-',  '_'  },
  { 0x55,  '=',  '+'  },
  { 0x66,  HP_KDB_BS,      HP_KDB_BS        },  // Backspace
// Row 3
  { 0x0D,  HP_KDB_CONT,    HP_KDB_SCRATCH   },  // Tab
  { 0x15,  'Q',  'q'  },
  { 0x1D,  'W',  'w'  },
  { 0x24,  'E',  'e'  },
  { 0x2D,  'R',  'r'  },
  { 0x2C,  'T',  't'  },
  { 0x35,  'Y',  'y'  },
  { 0x3C,  'U',  'u'  },
  { 0x43,  'I',  'i'  },
  { 0x44,  'O',  'o'  },
  { 0x4D,  'P',  'p'  },
  { 0x54,  '(',  '['  },
  { 0x5B,  ')',  ']'  },
  { 0x5D,  '\\',  '|' },
// Row 4
  // 0x5 Caps_Lock
  { 0x1C,  'A',  'a'  },
  { 0x1B,  'S',  's'  },
  { 0x23,  'D',  'd'  },
  { 0x2B,  'F',  'f'  },
  { 0x34,  'G',  'g'  },
  { 0x33,  'H',  'h'  },
  { 0x3B,  'J',  'j'  },
  { 0x42,  'K',  'k'  },
  { 0x4B,  'L',  'l'  },
  { 0x4C,  ';',  ':'  },
  { 0x52,  '\'',  '"' },
  { 0x5A,  HP_KDB_ENDLINE,    HP_KDB_ENDLINE  },  // Enter
// Row 5
  // 0x12 Shift_L
  { 0x1A,  'Z',  'z'  },
  { 0x22,  'X',  'x'  },
  { 0x21,  'C',  'c'  },
  { 0x2A,  'V',  'v'  },
  { 0x32,  'B',  'b'  },
  { 0x31,  'N',  'n'  },
  { 0x3A,  'M',  'm'  },
  { 0x41,  ',',  '<'  },
  { 0x49,  '.',  '>'  },
  { 0x4A,  '/',  '?'  },
  // 0x59   Shift_R
// Row 6
  // 0x14    Ctrl_L
  // 0x11    Alt
  { 0xE01F, PS2_9915_NF,      PS2_9915_NF       },  // left win key
  { 0x11,   PS2_9915_NF,      PS2_9915_NF       },  // Alt 
  { 0x29,   ' ',              ' '               },  // SPACE
  { 0xE011, HP_KDB_RUN,       HP_KDB_RUN        },  // Alt GR   
  { 0xE027, HP_KDB_PAUSE,     HP_KDB_STEP       },  // right Win Key
  { 0xE02F, HP_KDB_CONT,      HP_KDB_SCRATCH    },  // Menus
  { 0xE014, PS2_9915_NF,      PS2_9915_NF       },  // Right Ctrl -- does not work ??

// Keypad
  { 0x77,   HP_KDB_RESLT,     HP_KDB_CLEAR      }, // Num_Lock
  { 0xE04A, HP_KBD_KPD_DIV,   HP_KBD_KPD_LBRA   }, // Keypad Divide
  { 0x7C,   HP_KBD_KPD_MUL,   HP_KBD_KPD_RBRA   }, // Keypad *
  { 0x7B,   HP_KBD_KPD_MINUS, HP_KBD_KPD_CART   }, // Keypad -
  { 0x79,   HP_KBD_KPD_PLUS,  HP_KBD_KPD_PLUS   }, // Keypad +
  { 0x70,   '0',  '0'  },
  { 0x69,   '1',  '1'  },
  { 0x72,   '2',  '2'  },
  { 0x7A,   '3',  '3'  },
  { 0x6B,   '4',  '4'  },
  { 0x73,   '5',  '5'  },
  { 0x74,   '6',  '6'  },
  { 0x6C,   '7',  '7'  },
  { 0x75,   '8',  '8'  },
  { 0x7D,   '9',  '9'  },
  { 0x71,   '.',  ','  },
  { 0xE05A, HP_KDB_ENDLINE, HP_KDB_ENDLINE  }, // Keypad Enter

// cursor group
  { 0xE075, HP_KDB_UP,      HP_KDB_UP       }, // Up Arrow
  { 0xE06B, HP_KDB_LEFT,    HP_KDB_LEFT     }, // Left Arrow
  { 0xE072, HP_KDB_DOWN,    HP_KDB_DOWN     }, // Down Arrow
  { 0xE074, HP_KDB_RIGHT,   HP_KDB_RIGHT    }, // Right Arrow

// editing group
  { 0xE070, HP_KDB_INS_RPL, HP_KDB_INS_RPL  }, // Insert
  { 0xE06C, HP_KDB_HOME,    HP_KDB_HOME     }, // Home
  { 0xE07D, HP_KDB_ROLLUP,  HP_KDB_ROLLUP   }, // Page Up
  { 0xE071, HP_KDB_CHAR,    HP_KDB_DEL      }, // Delete
  { 0xE069, HP_KDB_LINE,    HP_KDB_CLEAR    }, // End
  { 0xE07A, HP_KDB_ROLLDN,  HP_KDB_ROLLDN   }, // Page Down

  { 0xFF,    PS2_9915_NF,    PS2_9915_NF  }    // end of table
};


/**
 * PS/2 Keyboard 
 * Original Author:  Christian Weichel
 * Adapted to the HP-9915A/B by Vassilis Prevelakis
 */
class PS2_9915_Keyboard {
  public:
        /**
         * This constructor does basically nothing. Please call the begin(int,int)
         * method before using any other method of this class.
         */
    PS2_9915_Keyboard();

    /**
     * Starts the keyboard "service" by registering the external interrupt.
     * setting the pin modes correctly and driving those needed to high.
     * The propably best place to call this method is in the setup routine.
     */
    static void begin(uint8_t dataPin, uint8_t irq_pin, const struct ps2_9915_map *keymap_tbl = hp9915_ps2mapEU);

    /**
     * Returns true if there is a char to be read, false if not.
     */
    static bool available();

    /**
     * Returns the char last read from the keyboard.
     * If there is no char availble, -1 is returned.
     */
    static int read();
};
