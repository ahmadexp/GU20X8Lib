// Example sketch controlling GU20x8 display directly connected to Arduino Nano
//
// Pin connections:
// GU20x8 Address pins  A0..A5          <--> Arduino A0..A5
// GU20x8 Data pins     D0, D1, D2..D7  <--> Arduino RX0, TX1, D2..D7
// GU20x8 control pin   c/D             <--> Arduino D8
// GU20x8 control pin   WR              <--> Arduino D9
// GU20x8 control pin   BUSY            <--> Arduino D10
// GU20x8 control pin   EN              <--> Arduino D11
//

static byte font[] = {
  0x00, 0x00, 0x00, 0x00, 0x00,// (space)
  0x00, 0x00, 0x5F, 0x00, 0x00,// !
  0x00, 0x07, 0x00, 0x07, 0x00,// "
  0x14, 0x7F, 0x14, 0x7F, 0x14,// #
  0x24, 0x2A, 0x7F, 0x2A, 0x12,// $
  0x23, 0x13, 0x08, 0x64, 0x62,// %
  0x36, 0x49, 0x55, 0x22, 0x50,// &
  0x00, 0x05, 0x03, 0x00, 0x00,// '
  0x00, 0x1C, 0x22, 0x41, 0x00,// (
  0x00, 0x41, 0x22, 0x1C, 0x00,// )
  0x08, 0x2A, 0x1C, 0x2A, 0x08,// *
  0x08, 0x08, 0x3E, 0x08, 0x08,// +
  0x00, 0x50, 0x30, 0x00, 0x00,// ,
  0x08, 0x08, 0x08, 0x08, 0x08,// -
  0x00, 0x60, 0x60, 0x00, 0x00,// .
  0x20, 0x10, 0x08, 0x04, 0x02,// /
  0x3E, 0x51, 0x49, 0x45, 0x3E,// 0
  0x00, 0x42, 0x7F, 0x40, 0x00,// 1
  0x42, 0x61, 0x51, 0x49, 0x46,// 2
  0x21, 0x41, 0x45, 0x4B, 0x31,// 3
  0x18, 0x14, 0x12, 0x7F, 0x10,// 4
  0x27, 0x45, 0x45, 0x45, 0x39,// 5
  0x3C, 0x4A, 0x49, 0x49, 0x30,// 6
  0x01, 0x71, 0x09, 0x05, 0x03,// 7
  0x36, 0x49, 0x49, 0x49, 0x36,// 8
  0x06, 0x49, 0x49, 0x29, 0x1E,// 9
  0x00, 0x36, 0x36, 0x00, 0x00,// :
  0x00, 0x56, 0x36, 0x00, 0x00,// ;
  0x00, 0x08, 0x14, 0x22, 0x41,// <
  0x14, 0x14, 0x14, 0x14, 0x14,// =
  0x41, 0x22, 0x14, 0x08, 0x00,// >
  0x02, 0x01, 0x51, 0x09, 0x06,// ?
  0x32, 0x49, 0x79, 0x41, 0x3E,// @
  0x7E, 0x11, 0x11, 0x11, 0x7E,// A
  0x7F, 0x49, 0x49, 0x49, 0x36,// B
  0x3E, 0x41, 0x41, 0x41, 0x22,// C
  0x7F, 0x41, 0x41, 0x22, 0x1C,// D
  0x7F, 0x49, 0x49, 0x49, 0x41,// E
  0x7F, 0x09, 0x09, 0x01, 0x01,// F
  0x3E, 0x41, 0x41, 0x51, 0x32,// G
  0x7F, 0x08, 0x08, 0x08, 0x7F,// H
  0x00, 0x41, 0x7F, 0x41, 0x00,// I
  0x20, 0x40, 0x41, 0x3F, 0x01,// J
  0x7F, 0x08, 0x14, 0x22, 0x41,// K
  0x7F, 0x40, 0x40, 0x40, 0x40,// L
  0x7F, 0x02, 0x04, 0x02, 0x7F,// M
  0x7F, 0x04, 0x08, 0x10, 0x7F,// N
  0x3E, 0x41, 0x41, 0x41, 0x3E,// O
  0x7F, 0x09, 0x09, 0x09, 0x06,// P
  0x3E, 0x41, 0x51, 0x21, 0x5E,// Q
  0x7F, 0x09, 0x19, 0x29, 0x46,// R
  0x46, 0x49, 0x49, 0x49, 0x31,// S
  0x01, 0x01, 0x7F, 0x01, 0x01,// T
  0x3F, 0x40, 0x40, 0x40, 0x3F,// U
  0x1F, 0x20, 0x40, 0x20, 0x1F,// V
  0x7F, 0x20, 0x18, 0x20, 0x7F,// W
  0x63, 0x14, 0x08, 0x14, 0x63,// X
  0x03, 0x04, 0x78, 0x04, 0x03,// Y
  0x61, 0x51, 0x49, 0x45, 0x43,// Z
  0x00, 0x00, 0x7F, 0x41, 0x41,// [
  0x02, 0x04, 0x08, 0x10, 0x20,// "\"
  0x41, 0x41, 0x7F, 0x00, 0x00,// ]
  0x04, 0x02, 0x01, 0x02, 0x04,// ^
  0x40, 0x40, 0x40, 0x40, 0x40,// _
  0x00, 0x01, 0x02, 0x04, 0x00,// `
  0x20, 0x54, 0x54, 0x54, 0x78,// a
  0x7F, 0x48, 0x44, 0x44, 0x38,// b
  0x38, 0x44, 0x44, 0x44, 0x20,// c
  0x38, 0x44, 0x44, 0x48, 0x7F,// d
  0x38, 0x54, 0x54, 0x54, 0x18,// e
  0x08, 0x7E, 0x09, 0x01, 0x02,// f
  0x08, 0x14, 0x54, 0x54, 0x3C,// g
  0x7F, 0x08, 0x04, 0x04, 0x78,// h
  0x00, 0x44, 0x7D, 0x40, 0x00,// i
  0x20, 0x40, 0x44, 0x3D, 0x00,// j
  0x00, 0x7F, 0x10, 0x28, 0x44,// k
  0x00, 0x41, 0x7F, 0x40, 0x00,// l
  0x7C, 0x04, 0x18, 0x04, 0x78,// m
  0x7C, 0x08, 0x04, 0x04, 0x78,// n
  0x38, 0x44, 0x44, 0x44, 0x38,// o
  0x7C, 0x14, 0x14, 0x14, 0x08,// p
  0x08, 0x14, 0x14, 0x18, 0x7C,// q
  0x7C, 0x08, 0x04, 0x04, 0x08,// r
  0x48, 0x54, 0x54, 0x54, 0x20,// s
  0x04, 0x3F, 0x44, 0x40, 0x20,// t
  0x3C, 0x40, 0x40, 0x20, 0x7C,// u
  0x1C, 0x20, 0x40, 0x20, 0x1C,// v
  0x3C, 0x40, 0x30, 0x40, 0x3C,// w
  0x44, 0x28, 0x10, 0x28, 0x44,// x
  0x0C, 0x50, 0x50, 0x50, 0x3C,// y
  0x44, 0x64, 0x54, 0x4C, 0x44,// z
  0x00, 0x08, 0x36, 0x41, 0x00,// {
  0x00, 0x00, 0x7F, 0x00, 0x00,// |
  0x00, 0x41, 0x36, 0x08, 0x00,// }
  0x08, 0x08, 0x2A, 0x1C, 0x08,// ->
  0x08, 0x1C, 0x2A, 0x08, 0x08 // <-
};

#include "Display.h"
#include "IConnection.h"

// Arduino PORTC = A0..A7
#define AddressPort PORTC
#define AddressPortDirection DDRC
#define AddressMask 0b00111111

// Arduino PORTD = RX0+TX1+D2..D7
#define DataPort PORTD
#define DataPortDirection DDRD
#define DataMask 0b11111111

// Arduino PORTB = D8..D13
#define ControlPort PORTB
#define ControlPortDirection DDRB
#define ControlPort_cD PORTB0
#define ControlPort_WR PORTB1
#define ControlPort_BUSY PORTB2
#define ControlPort_ENABLE PORTB3

//Image Buffer
byte red_buffer[20], blue_buffer[20];

#define SetBits(reg,value,valueMask) { (reg) = ((reg) & ~(valueMask)) | ((value) & (valueMask));}
#define SetBitPos(reg,pos,val) { if (val) (reg) |= (1<<(pos)); else (reg) &= ~(1 << (pos));}

class Connection : public GU20x8::IConnection
{
    virtual void ConfigureBus()
    {
        AddressPortDirection |= AddressMask;
        DataPortDirection |= DataMask;
        ControlPortDirection |= (1 << ControlPort_cD) | (1 << ControlPort_WR) | (1 << ControlPort_ENABLE);
        ControlPortDirection &= ~(1 << ControlPort_BUSY);
    }

    virtual void SetAddressBus(uint8_t address)
    {
        SetBits(AddressPort, address, AddressMask);
    }
    virtual void SetDataBus(uint8_t data)
    {
        SetBits(DataPort, data, DataMask);
    }
    virtual void SetCDBit(bool value)
    {
        SetBitPos(ControlPort, ControlPort_cD, value);
    }
    virtual void SetENBit(bool value)
    {
        SetBitPos(ControlPort, ControlPort_ENABLE, value);
    }
    virtual void SetWRBit(bool value)
    {
        SetBitPos(ControlPort, ControlPort_WR, value);
    }
    virtual bool GetBusyBit()
    {
        return ControlPort & ControlPort_BUSY;
    }
};

Connection connection;
GU20x8::Display vfd(connection);

void clear_all(void)
{
  for(int temp=0; temp<20; temp++)
    {
      red_buffer[temp]=0;
      blue_buffer[temp]=0;
      vfd.WriteColumn( temp, red_buffer[temp], blue_buffer[temp]);
    }
}

void draw_pixel(byte x, byte y, byte c){
if(c&0x01)
  red_buffer[x]=red_buffer[x]|(0x01<<(7-y));
else
  red_buffer[x]=red_buffer[x]&(~(0x01<<(7-y)));  

if(c&0x02)
  blue_buffer[x]=blue_buffer[x]|(0x01<<(7-y));
else
  blue_buffer[x]=blue_buffer[x]&(~(0x01<<(7-y)));  

vfd.WriteColumn( x, red_buffer[x], blue_buffer[x]);
}

void setup()
{
    vfd.Begin();
    vfd.ClearScreen();
    vfd.SetBrightness(3);
    vfd.EnableDisplay();

    clear_all();

}



void write_char(byte x, byte ch, byte c){
  for(byte temp=0;temp<5;temp++){
    if(c&0x01)
      red_buffer[(x*5)+temp]=red_buffer[(x*5)+temp]|(font[(ch*5)+temp]);
    else
      red_buffer[(x*5)+temp]=red_buffer[(x*5)+temp]&(~(font[(ch*5)+temp]));
    if(c&0x02)
      blue_buffer[(x*5)+temp]=blue_buffer[(x*5)+temp]|(font[(ch*5)+temp]);
    else
      blue_buffer[(x*5)+temp]=blue_buffer[(x*5)+temp]&(~(font[(ch*5)+temp]));  
  vfd.WriteColumn( (x*5)+temp, red_buffer[(x*5)+temp], blue_buffer[(x*5)+temp]);     
  } 
}

void print_number(int num, byte c){
  write_char(0,(byte)((num/1000)%10)+16,c);
  write_char(1,(byte)((num/100)%10)+16,c);
  write_char(2,(byte)((num/10)%10)+16,c);
  write_char(3,(byte)(num%10)+16,c);
}

void loop()
{
  for(int temp=0;temp<9999;temp++)
  {
    print_number(temp,3);
    delay(10);
    print_number(temp,0);
  }
}
