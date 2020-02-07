
#include "Kbd9915.h"

/*
 * STM32-based Keyboard adapter for the HP-9915A/B embedded computer
 * 20200207 -- Vassilis Prevelakis <vp2020 .at. aegisresearch.eu>
 * 
 * To compile this program using the Arduino IDE,
 *    a)  Tools->Board->"Generic STM32F103C series"
 *    b)  Tools->Variant->"Generic STM32F103C8"
 *    c)  Tools->Upload Method-> Serial
 *    
 *  You will also need to make sure that the STM32 (BluePill) helper files
 *  are loaded in ~/Desktop/Arduino
 */
 
/*
 * ascii2hp85tblent -- extended ascii code to 9915 keyboard map
 */

struct ascii2hp85tblent *ascii2hp85(short c)
{
    int i;
    
    for (i=0; conv_tbl[i].a2h_cc != HP_KDB_UNKNOWN; i++) {
            if (conv_tbl[i].a2h_cc == c)
                return(&conv_tbl[i]);
    }
    return(&conv_tbl[i]);   // return Unknown char (same as "Paper Advance", which on the 9915 does nothing)
}

#define ZAR_STROBE	PA8
#define ZAR_RESET	PB12
// The following ZAR_DATA pin is not really needed,
// we use ZAR_RESET to clear all the pins in one go.
// so ZAR_DATA is always TRUE so we can pull the 
// the line HIGH and be done with.
#define ZAR_DATA	PA1


#define ZAR_AX0	    PB6
#define ZAR_AX1	    PB7
#define ZAR_AX2	    PB8
#define ZAR_AX3	    PB9

#define ZAR_AY0	    PB13
#define ZAR_AY1	    PB14
#define ZAR_AY2	    PB15

#define K9915_SHIFT	PA11
#define K9915_CTRL	PA12
#define K9915_CAPS	PA15

#define SETBIT(V)	( ((V & 0x01) == 0) ? LOW : HIGH )

void pulse_line(int lid)
{
  digitalWrite(lid, HIGH);
  delay(1);
  digitalWrite(lid, LOW);
}

/*
 * set_sw__addr -- set MT093 address line
 *    Our addresses are cccrrrr where ccc is the column and rrrr is the row
 *    However the MT093 has a quirk whereby rows 0 to 5 are mapped to 0 to 5 (as expected)
 *    but rows 6 to B are mapped to addresses 8 to D respectively
 *    
 *    So we need to translate between the cccrrrr to cccRRRR where RRRR are the MT093
 *    compatible addresses and then set the MT093 lines.
 */
int set_sw__addr(int cr)
{
  // this only works if rrrr < 14
  if ((cr & 0xF) >= 6)
    cr += 2;

  // format of cr is 0cccRRRR, so we set the line
  // correspong to the LSBit and shift right till
  // we set all the bits.
  digitalWrite(ZAR_AX0, SETBIT(cr));  cr >>= 1;
  digitalWrite(ZAR_AX1, SETBIT(cr));  cr >>= 1;
  digitalWrite(ZAR_AX2, SETBIT(cr));  cr >>= 1;
  digitalWrite(ZAR_AX3, SETBIT(cr));  cr >>= 1;
  digitalWrite(ZAR_AY0, SETBIT(cr));  cr >>= 1;
  digitalWrite(ZAR_AY1, SETBIT(cr));  cr >>= 1;
  digitalWrite(ZAR_AY2, SETBIT(cr));

  // set DATA to HIGH
  digitalWrite(ZAR_DATA, HIGH);
}

void reset_switch()
{
  pulse_line(ZAR_RESET);   // pulse reset to clear the switches
  /* 
   *  normally resetting the switch should be all that's needed. BUT, it does not
   *  work in all the cases. Specifically, it works if you press a different key (e.g. A and then S)
   *  but not is you press the same key (e.g. A and then A again).
   *  I came up with the kludge that sends a "PAPER ADVANCE" key after each character,
   *  so when you press A, the 9915 gets an A followed by [PAPER ADVANCE], so that repeated characters
   *  are no longer repeated as far as the 9915 is concerned. In this way, they register OK. 
   *  Of course if you try this on an HP-85 you will be getting paper
   *  advances for each character pressed. Sorry!
   */
  set_sw__addr(0x79); // set PAPER ADVANCE switch address
  pulse_line(ZAR_STROBE);
  delay(30);
  pulse_line(ZAR_RESET);  // pulse reset to clear all the switches
}


void sendKey9915(short cc)
{
  struct ascii2hp85tblent *kcp;  // keyboard code

  kcp = ascii2hp85(cc);

  // load switch address
  set_sw__addr(kcp->a2h_sc);
  
  // deal with  modifier keys
  if (kcp->a2h_ctrl == 1)  // if control set control
    digitalWrite(K9915_CTRL, LOW);
  if (kcp->a2h_shift == 1) // if shift set shift
    digitalWrite(K9915_SHIFT, LOW);
   
  delay(1); // allow data to settle
  
  // pulse STROBE
  pulse_line(ZAR_STROBE);

  // wait for key press to register
  delay(40);

  // clear switch config
  reset_switch();                  // open all switches
  digitalWrite(K9915_CTRL,  HIGH); // clear control
  digitalWrite(K9915_SHIFT, HIGH); // clear shift
}

/*
 * PS/2 Keyboard variables -- see later on for details
 */

const int PS2_DataPin = PB11;
const int PS2_IRQpin =  PB10;

PS2_9915_Keyboard keyboard;

/*
 * ============================================================
 *       Setup 
 * ============================================================
 */
void setup() {
  digitalWrite(ZAR_AX0, LOW);
  digitalWrite(ZAR_AX1, LOW);
  digitalWrite(ZAR_AX2, LOW);
  digitalWrite(ZAR_AX3, LOW);
  digitalWrite(ZAR_AY0, LOW);
  digitalWrite(ZAR_AY1, LOW);
  digitalWrite(ZAR_AY2, LOW);
  digitalWrite(ZAR_STROBE, LOW);
  digitalWrite(ZAR_RESET, LOW);
  digitalWrite(ZAR_DATA, LOW);
  digitalWrite(K9915_SHIFT, HIGH); // negative logic
  digitalWrite(K9915_CTRL, HIGH);  // negative logic
  digitalWrite(K9915_CAPS, HIGH);  // negative logic
  
  pinMode(ZAR_AX0, OUTPUT);
  pinMode(ZAR_AX1, OUTPUT);
  pinMode(ZAR_AX2, OUTPUT);
  pinMode(ZAR_AX3, OUTPUT);
  pinMode(ZAR_AY0, OUTPUT);
  pinMode(ZAR_AY1, OUTPUT);
  pinMode(ZAR_AY2, OUTPUT);
  pinMode(ZAR_STROBE, OUTPUT);
  pinMode(ZAR_RESET, OUTPUT);
  pinMode(ZAR_DATA, OUTPUT);
  pinMode(K9915_SHIFT, OUTPUT);
  pinMode(K9915_CTRL, OUTPUT);
  pinMode(K9915_CAPS, OUTPUT);

  reset_switch();
  
  delay(1000);
  keyboard.begin(PS2_DataPin, PS2_IRQpin);
  // Serial.begin(115200);
  // Serial.println("Keyboard Ctrl+Enter Test:");
}

/*
 * ============================================================
 *       Main loop 
 * ============================================================
 */
void loop() {
  /*
   * Here we need to read a key from the PS/2 keyboard and determine
   * which row and which column to short in the 9915 keyboard connector
   * In addition we need to find out if we also need to tell the 9915 that
   * the Shift and/or the Ctrl key(s) need to be pressed as well.
   * For example to send 2 to the 9915 we need to connect column 6 with row 1.
   * If we want to send @ to the 9915, we need to also drive low the Shift line
   * Finally if we want to send NULL (Ctrl @ on the normal 9915 keyboard), 
   * we need to drive low the Ctrl line as well.
   * 
   * The keyboard.read routine converts the PS/2 keyboard scancodes to 
   * our internal 0015 representation which the sendKey9915 will convert
   * to the appropriate lines for row, column, Shift and Ctrl that must 
   * be driven to 'press' the key.
   */
  if (keyboard.available()) {
    
   ushort c = keyboard.read();
    
    if (c == -1)
      return;
    sendKey9915(c);
  }
}




/*
 * The code below is derived from the PS2Keyboard library.
 *
 * Initially I wanted to leave the original code intact, but it soon
 * bacame a mess, so the code below is specific to the HP9915 keyboard adapter.
 * I added comments and (hopefully) restructured the code to make it
 * easier to read. The copyright remains:
 *
 * Copyright (c) 2007 Free Software Foundation.  All right reserved.
 * Written by Christian Weichel <info@32leaves.net>
 *
 * ** Mostly rewritten Paul Stoffregen <paul@pjrc.com> 2010, 2011
 * ** Modified for use beginning with Arduino 13 by L. Abraham Smith, <n3bah@microcompdesign.com> * 
 * ** Modified for easy interrup pin assignement on method begin(datapin,irq_pin). Cuningan <cuninganreset@gmail.com> **
 *
 * ** Adapted for the 9915 keyboard converter by Vassilis Prevelakis
 *    vp2020 .at. aegisresearch.eu
*/


#define BUFFER_SIZE 45
static volatile uint8_t buffer[BUFFER_SIZE];
static volatile uint8_t head, tail;
static uint8_t DataPin;
static ushort PrevChar=0;

// The ISR for the external interrupt
void ps2interrupt(void)
{
  static uint8_t bitcount=0;
  static uint8_t incoming=0;
  static uint32_t prev_ms=0;
  uint32_t now_ms;
  uint8_t n, val;

  val = digitalRead(DataPin);
  now_ms = millis();
  if (now_ms - prev_ms > 250) {
    bitcount = 0;
    incoming = 0;
  }
  prev_ms = now_ms;
  n = bitcount - 1;
  if (n <= 7) {
    incoming |= (val << n);
  }
  bitcount++;
  if (bitcount == 11) {
    uint8_t i = head + 1;
    if (i >= BUFFER_SIZE) i = 0;
    if (i != tail) {
      buffer[i] = incoming;
      head = i;
    }
    bitcount = 0;
    incoming = 0;
  }
}

static inline uint8_t get_scan_code(void)
{
  uint8_t c, i;

  i = tail;
  if (i == head)
    return 0;
  i++;
  if (i >= BUFFER_SIZE)
    i = 0;
  c = buffer[i];
  tail = i;
  return c;
}

const struct ps2_9915_map *mymap;

ushort map_keycode(int s, int shifted)
{
  const struct ps2_9915_map *rp;

  for (rp = mymap; rp->ps2keycode != 0xFF; rp++) {
    if (rp->ps2keycode == s) {
      if (shifted)
          return(rp->hp9915_shifted);
        else
          return(rp->hp9915_normal);
    }
  }
  return(0);
}

ushort map_ctrl(ushort c)
{
  switch (c) {
        case '@': return(HP_KDB_CNULL);
        case 'A':
        case 'a': return(HP_KDB_CA);
        case 'B':
        case 'b': return(HP_KDB_CB);
        case 'C':
        case 'c': return(HP_KDB_CC);
        case 'D':
        case 'd': return(HP_KDB_CD);
        case 'E':
        case 'e': return(HP_KDB_CE);
        case 'F':
        case 'f': return(HP_KDB_CF);
        case 'G':
        case 'g': return(HP_KDB_CG);
        case 'H':
        case 'h': return(HP_KDB_CH);
        case 'I':
        case 'i': return(HP_KDB_CI);
        case 'J':
        case 'j': return(HP_KDB_CJ);
        case 'K':
        case 'k': return(HP_KDB_CK);
        case 'L':
        case 'l': return(HP_KDB_CL);
        case 'M':
        case 'm': return(HP_KDB_CM);
        case 'N':
        case 'n': return(HP_KDB_CN);
        case 'O':
        case 'o': return(HP_KDB_CO);
        case 'P':
        case 'p': return(HP_KDB_CP);
        case 'Q':
        case 'q': return(HP_KDB_CQ);
        case 'R':
        case 'r': return(HP_KDB_CR);
        case 'S':
        case 's': return(HP_KDB_CS);
        case 'T':
        case 't': return(HP_KDB_CT);
        case 'U':
        case 'u': return(HP_KDB_CU);
        case 'V':
        case 'v': return(HP_KDB_CV);
        case 'W':
        case 'w': return(HP_KDB_CW);
        case 'X':
        case 'x': return(HP_KDB_CX);
        case 'Y':
        case 'y': return(HP_KDB_CY);
        case 'Z':
        case 'z': return(HP_KDB_CZ);
        case '[': return(HP_KDB_CLBRA);
        case '\\': return(HP_KDB_CBSL);
        case ']': return(HP_KDB_CRBRA);
        case '^': return(HP_KDB_CCART);
        case '_': return(HP_KDB_CUSCOR);
  }
  return(c);   // no processing
}

/*
 * metakey flags (see 'state' variable below)
 */
#define KEY_UP    0x01
#define EXT_KEY   0x02
#define SHIFT_L   0x04
#define SHIFT_R   0x08
#define CAPS      0x10
#define CTRL      0x20

static ushort get_9915_code(void)
{
  static uint8_t state=0;
  ushort s;
  ushort c;

  while (1) {
    if ((s = get_scan_code()) == 0)
      return(0);  // queue empty, return
          
    if (s == 0xF0) {
      state |= KEY_UP;  // key up (released) code
                        // this is followed by the key code
      continue;         // get next scan code
    }
    if (s == 0xE0) {
      state |= EXT_KEY;
      continue;
    }
    // metakeys: key up -> clear mode
    if (state & KEY_UP) {
      // 0x61 is the scancode of the key between the left shift and the letter 'Z'
      // we turn this to a left shift as well, putting an end to this abomination.
      if ((s == 0x12) || (s == 0x61)) { 
        state &= ~SHIFT_L;
      } else if (s == 0x59) {
        state &= ~SHIFT_R;
      } else if (s == 0x14) {
        state &= ~CTRL;
      }
      state &= ~(KEY_UP | EXT_KEY);
      continue;
    }
     
    // metakeys: key down -> set state
    if ((s == 0x12) || (s == 0x61)) {
      state |= SHIFT_L;
      continue;
    }
    if (s == 0x59) {
      state |= SHIFT_R;
      continue;
    }
    if (s == 0x14) {
      state |= CTRL;
      continue;
    }
 
    c = 0;
    // proccess CAPS LOCK key!
    if (s == 0x58) {
      if (state & CAPS) {
        // clear CAPS LOCK line
        // for some reason, this does not work, so we 
        // do it in software (see below)
        // digitalWrite(K9915_CAPS, HIGH);  // negative logic
        state &= ~CAPS;
      } else {
        // set CAPS LOCK line
        // digitalWrite(K9915_CAPS, LOW);  // negative logic
        state |= CAPS;
      }
      continue;
    }
    
    if ((state & EXT_KEY)) {
      // extended key (e.g. E0 69 for End) processing
      // we have already received the E0 in the previous run of this loop
      // so the codes that we process here are assumed to be part of a multi
      // byte sequence. This is important as the 0x14 (Right CTRL) we process here is 
      // different from the 0x14 (left CTRL) we proceesed earlier on.
      s |= 0xE000; // prepend the prefix code 
    }
    c = map_keycode(s, (state & (SHIFT_L | SHIFT_R))); // normal key processing
  
    // now that we have the actual key pressed
    // we check if the Control metakey is also
    // pressed and in this case we generate the
    // appropriate control code.
    if (state & CTRL)
      c = map_ctrl(c);

    if (isalpha(c)) {
      // if characgter is A-Z and caps lock is OK
      // we turn uppercase to lower case and vise
      // versa
      if (state & CAPS) {
        if (c & 0x20) // if lowercase
          c &= ~0x20; // turn to uppercase
        else
          c |= 0x20; // turn to lowercase
      }
    }
        
    state &= ~(KEY_UP | EXT_KEY);
    return c;
  } // while(1)
}

bool PS2_9915_Keyboard::available() {
  if (PrevChar)
    return true;
  PrevChar = get_9915_code();
  if (PrevChar)
    return true;
  return false;
}

int PS2_9915_Keyboard::read() {
  ushort result;

  if (PrevChar != 0) {
    result = PrevChar;
    PrevChar = 0;
  } else 
    result = get_9915_code();
  if (result)
    return result;
  return -1;
}

PS2_9915_Keyboard::PS2_9915_Keyboard() {
  // nothing to do here, begin() does it all
}

void PS2_9915_Keyboard::begin(uint8_t data_pin, uint8_t irq_pin, const struct ps2_9915_map *keymap_tbl ) {
  uint8_t irq_num=0;

  mymap = keymap_tbl;

  DataPin = data_pin;

  // initialize the pins
#ifdef INPUT_PULLUP
  pinMode(irq_pin, INPUT_PULLUP);
  pinMode(data_pin, INPUT_PULLUP);
#else
  pinMode(irq_pin, INPUT);
  digitalWrite(irq_pin, HIGH);
  pinMode(data_pin, INPUT);
  digitalWrite(data_pin, HIGH);
#endif
  
#ifdef __STM32F1__
  attachInterrupt(digitalPinToInterrupt(irq_pin),ps2interrupt,FALLING);
#else
  switch(irq_pin) {
    #ifdef CORE_INT0_PIN
    case CORE_INT0_PIN:
      irq_num = 0;
      break;
    #endif
    #ifdef CORE_INT1_PIN
    case CORE_INT1_PIN:
      irq_num = 1;
      break;
    #endif
    #ifdef CORE_INT2_PIN
    case CORE_INT2_PIN:
      irq_num = 2;
      break;
    #endif
    #ifdef CORE_INT3_PIN
    case CORE_INT3_PIN:
      irq_num = 3;
      break;
    #endif
    #ifdef CORE_INT4_PIN
    case CORE_INT4_PIN:
      irq_num = 4;
      break;
    #endif
    #ifdef CORE_INT5_PIN
    case CORE_INT5_PIN:
      irq_num = 5;
      break;
    #endif
    #ifdef CORE_INT6_PIN
    case CORE_INT6_PIN:
      irq_num = 6;
      break;
    #endif
    #ifdef CORE_INT7_PIN
    case CORE_INT7_PIN:
      irq_num = 7;
      break;
    #endif
    default:
      irq_num = 0;
      break;
  }
  attachInterrupt(irq_num, ps2interrupt, FALLING);
#endif /*__STM32F1__*/
  head = 0;
  tail = 0;
}
