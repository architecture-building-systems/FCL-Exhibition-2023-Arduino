#include <Adafruit_NeoPixel.h>
#include <PGMWrap.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,20,4);


#define PIX_8 12
#define PIX_9 11
#define PIX_10 10
#define PIX_11 9
#define PIX_12 8
#define PIX_13 7
#define PIX_14 6
#define PIX_15 5
#define PIX_16 4
#define PIX_17 3
#define PIX_18 2


#define CONT_1 20
#define CONT_2 21
#define CONT_3 22

#define ENC_mode_A 24
#define ENC_mode_B 25
#define ENC_month_A 28
#define ENC_month_B 29
#define ENC_hour_A 32
#define ENC_hour_B 33

#define NUMPIXELS 12
#define DELAYVAL 100

//initialize pixles for the analemmas

Adafruit_NeoPixel pixels_8(NUMPIXELS, PIX_8, NEO_GRBW + NEO_KHZ800);
Adafruit_NeoPixel pixels_9(NUMPIXELS, PIX_9, NEO_GRBW + NEO_KHZ800);
Adafruit_NeoPixel pixels_10(NUMPIXELS, PIX_10, NEO_GRBW + NEO_KHZ800);
Adafruit_NeoPixel pixels_11(NUMPIXELS, PIX_11, NEO_GRBW + NEO_KHZ800);
Adafruit_NeoPixel pixels_12(NUMPIXELS, PIX_12, NEO_GRBW + NEO_KHZ800);
Adafruit_NeoPixel pixels_13(NUMPIXELS, PIX_13, NEO_GRBW + NEO_KHZ800);
Adafruit_NeoPixel pixels_14(NUMPIXELS, PIX_14, NEO_GRBW + NEO_KHZ800);
Adafruit_NeoPixel pixels_15(NUMPIXELS, PIX_15, NEO_GRBW + NEO_KHZ800);
Adafruit_NeoPixel pixels_16(NUMPIXELS, PIX_16, NEO_GRBW + NEO_KHZ800);
Adafruit_NeoPixel pixels_17(NUMPIXELS, PIX_17, NEO_GRBW + NEO_KHZ800);
Adafruit_NeoPixel pixels_18(NUMPIXELS, PIX_18, NEO_GRBW + NEO_KHZ800);
//initialize pixles for the control panel
Adafruit_NeoPixel control_1(NUMPIXELS, CONT_1, NEO_GRBW + NEO_KHZ800);
Adafruit_NeoPixel control_2(NUMPIXELS, CONT_2, NEO_GRBW + NEO_KHZ800);
Adafruit_NeoPixel control_3(NUMPIXELS, CONT_3, NEO_GRBW + NEO_KHZ800);



String unit_temp="C";
String unit_grid="kgCO2/kWh";
String unit_ghi="W/m2";
String unit_dema="kWh";
float temp_array[]={0,0,0,0,0,0,0,0,0,0,0};
volatile int mode=0;
volatile int month=12;
volatile int hour=11;
float minValue;
float maxValue;
int lower_b;
int upper_b;
int period=200;
int time_now;
int encoderPINA_mode = ENC_mode_A;
int encoderPINB_mode = ENC_mode_B;
int encoderPos_mode = 0;
int encoderPINALast_mode = LOW;
int encoderPINANow_mode = LOW;
int encoderPINA_month = ENC_month_A;
int encoderPINB_month = ENC_month_B;
int encoderPos_month = 0;
int encoderPINALast_month = LOW;
int encoderPINANow_month = LOW;
int encoderPINA_hour = ENC_hour_A;
int encoderPINB_hour = ENC_hour_B;
int encoderPos_hour = 0;
int encoderPINALast_hour = LOW;
int encoderPINANow_hour = LOW;
int a;
int aa;

// SINGAPORE GRID EMISSIONS
float avggrid_8[]={488,488,488,489,487,488,487,487,488,487,488,489};
float avggrid_9[]={492,491,492,492,492,492,492,491,493,492,492,492};
float avggrid_10[]={495,494,495,495,495,494,495,494,497,495,494,495};
float avggrid_11[]={496,495,496,496,495,495,497,495,497,496,494,496};
float avggrid_12[]={496,495,497,496,496,495,497,496,498,496,496,496};
float avggrid_13[]={496,495,497,496,496,495,497,496,498,496,496,496};
float avggrid_14[]={497,495,497,496,496,495,497,496,497,497,495,496};
float avggrid_15[]={497,496,497,497,496,496,498,496,497,497,496,496};
float avggrid_16[]={497,496,498,497,496,496,498,496,497,497,496,497};
float avggrid_17[]={497,496,498,497,496,496,498,496,497,497,496,497};
float avggrid_18[]={498,496,498,497,496,496,498,496,497,497,496,497};
float b_grid=0;
float max_grid=498;
float min_grid=300;
float max_grid_si=498;
float min_grid_si=487;

// SINGAPORE DEMAND


float avgdema_8[]={-279,-324,-716,-854,-1073,-925,-768,-842,-1003,-1052,-670,-498};
float avgdema_9[]={-770,-850,-942,-994,-1112,-999,-928,-966,-1055,-1025,-998,-862};
float avgdema_10[]={-875,-857,-817,-935,-1002,-937,-861,-827,-941,-931,-827,-802};
float avgdema_11[]={-1086,-1085,-1192,-1342,-1445,-1317,-1249,-1243,-1369,-1316,-1227,-1131};
float avgdema_12[]={-1432,-1448,-1535,-1735,-1824,-1670,-1596,-1610,-1746,-1685,-1630,-1459};
float avgdema_13[]={-1436,-1496,-1567,-1710,-1809,-1663,-1578,-1600,-1700,-1680,-1562,-1470};
float avgdema_14[]={-1058,-1164,-1223,-1292,-1386,-1237,-1173,-1180,-1286,-1271,-1160,-1052};
float avgdema_15[]={-829,-936,-1019,-1039,-1127,-995,-921,-942,-1048,-1011,-897,-798};
float avgdema_16[]={-755,-898,-939,-959,-1020,-900,-830,-860,-918,-922,-792,-723};
float avgdema_17[]={-958,-1023,-1053,-1129,-1198,-1074,-989,-1036,-1065,-1064,-926,-867};
float avgdema_18[]={-1839,-1871,-1911,-2055,-2158,-2050,-1935,-1972,-2004,-2006,-1827,-1748};
float g_dema=20;
float max_dema=-279;
float min_dema=-2383;
float max_dema_si=-279;
float min_dema_si=-2383;


// SINGAPORE GHI

float avgghi_8[]={161,162,174,179,189,170,173,177,213,229,182,162};
float avgghi_9[]={313,347,356,327,354,312,318,310,383,406,312,328};
float avgghi_10[]={495,518,529,467,492,476,450,437,508,537,421,456};
float avgghi_11[]={588,594,616,552,514,555,534,513,579,583,494,527};
float avgghi_12[]={646,717,700,639,635,589,582,576,638,609,537,520};
float avgghi_13[]={645,728,698,696,603,598,564,592,629,572,576,569};
float avgghi_14[]={604,693,640,626,538,539,540,587,565,512,494,494};
float avgghi_15[]={509,601,559,494,457,458,498,536,445,421,405,384};
float avgghi_16[]={390,429,413,361,327,350,392,409,322,282,305,294};
float avgghi_17[]={224,267,243,218,184,195,235,233,181,150,144,168};
float avgghi_18[]={80,103,81,69,50,62,82,73,32,12,10,27};
float g_ghi=200;
float max_ghi=728;
float min_ghi=1;
float max_ghi_si=728;
float min_ghi_si=1;


// SINGAPORE TEMP

float avgtemp_8[]={25,25,25,25,26,26,26,26,25,26,25,25};
float avgtemp_9[]={25,25,26,26,27,27,27,27,26,27,26,26};
float avgtemp_10[]={26,27,27,27,28,28,28,28,27,28,26,27};
float avgtemp_11[]={27,28,28,28,29,29,29,29,28,29,27,28};
float avgtemp_12[]={28,28,29,29,30,30,29,29,29,30,28,28};
float avgtemp_13[]={29,29,30,30,31,30,30,30,30,30,29,29};
float avgtemp_14[]={29,30,30,30,31,31,30,30,30,31,29,29};
float avgtemp_15[]={29,30,31,31,32,31,31,31,31,31,30,30};
float avgtemp_16[]={29,30,31,31,32,31,31,31,31,31,30,29};
float avgtemp_17[]={29,30,31,31,32,31,31,31,30,31,30,29};
float avgtemp_18[]={29,30,30,30,31,30,30,30,30,30,29,29};
float g_temp=0;
float max_temp=32;
float min_temp=20;
float max_temp_si=32;
float min_temp_si=25;

int r_sun=100;
int g_sun=100;
int b_sun=100;
int w_sun=200;

int reset_timeout=9000;
int counter=0;
int turn_flag=0;

void setup() {
  watchdogSetup();
  watchdogEnable(10000);
  Serial.begin (115200);
  //initialize LCD
  lcd.init();
  Wire.setClock(400000);
  lcd.clear();         
  lcd.backlight(); 
  //initialize Pixels 
  
  pixels_8.begin();
  pixels_9.begin();
  pixels_10.begin();
  pixels_11.begin();
  pixels_12.begin();
  pixels_13.begin();
  pixels_14.begin();
  pixels_15.begin();
  pixels_16.begin();
  pixels_17.begin();
  pixels_18.begin();
  pinMode (encoderPINA_mode, INPUT_PULLUP);
  pinMode (encoderPINB_mode, INPUT_PULLUP);
  pinMode (encoderPINA_month, INPUT_PULLUP);
  pinMode (encoderPINB_month, INPUT_PULLUP);
  pinMode (encoderPINA_hour, INPUT_PULLUP);
  pinMode (encoderPINB_hour, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(encoderPINA_month), turn_month, CHANGE);
  attachInterrupt(digitalPinToInterrupt(encoderPINA_hour), turn_hour, CHANGE);
  attachInterrupt(digitalPinToInterrupt(encoderPINA_mode), turn_mode, CHANGE);
  randomSeed(analogRead(A2));
  mode=random(0,4);
  print_mode();
  print_month();
  print_hour();
  // put your setup code here, to run once:

}


void loop() {
  watchdogReset();
  if (turn_flag==1){
    counter=0;
    turn_flag=0;
  }
  if( counter  >= reset_timeout && turn_flag==0 ){ 
    rstc_start_software_reset(RSTC);  
  }
  counter++;

  switch (month) {
  case 0:
  case 1:
  case 2:
  case 3:
  case 4:
  case 5:
  case 6:
  case 7:
  case 8:
  case 9:
  case 10:
  case 11:
  upper_b=month+1;
  lower_b=month;
  break;
  case 12:
  upper_b=12;
  lower_b=0;
  break;
  }
  

  //mode switch
  switch (mode) {
  case 0:
  //clear_pix();   
  temp();
  show();
  break;
  case 1:
  //clear_pix();
  grid();
  show();
  break;
  case 2:
  //clear_pix();
  ghi();
  show();
  break;
  case 3:
  //clear_pix();
  dema();
  show();
  break;
  case 4:
  sunpos();
  show();
  break;
  }

  
  
  turn_mode();
  turn_month();
  turn_hour();
  //clear_pix();
    
   
}
  void ghi(){
    
    for (int i = lower_b; i < upper_b; i++) {
      if(i==0){
        a=11;
      }else{
        a=i-1;
      }
      switch(hour){
        case 0:
          pixels_8.setPixelColor(i,120+125*(avgghi_8[a]-min_ghi)/(max_ghi-min_ghi), g_ghi,170*(max_ghi-avgghi_8[a])/(max_ghi-min_ghi),0);
          break;
        case 1:  
          pixels_9.setPixelColor(i,120+125*(avgghi_9[a]-min_ghi)/(max_ghi-min_ghi), g_ghi,170*(max_ghi-avgghi_9[a])/(max_ghi-min_ghi),0);
          break;
        case 2:
          pixels_10.setPixelColor(i,120+125*(avgghi_10[a]-min_ghi)/(max_ghi-min_ghi), g_ghi,170*(max_ghi-avgghi_10[a])/(max_ghi-min_ghi),0);
          break;
        case 3:
          pixels_11.setPixelColor(i,120+125*(avgghi_11[a]-min_ghi)/(max_ghi-min_ghi), g_ghi,170*(max_ghi-avgghi_11[a])/(max_ghi-min_ghi),0);
          break;
        case 4:
          pixels_12.setPixelColor(i,120+125*(avgghi_12[a]-min_ghi)/(max_ghi-min_ghi), g_ghi,170*(max_ghi-avgghi_12[a])/(max_ghi-min_ghi),0);
          break;
        case 5:
          pixels_13.setPixelColor(i,120+125*(avgghi_13[a]-min_ghi)/(max_ghi-min_ghi), g_ghi,170*(max_ghi-avgghi_13[a])/(max_ghi-min_ghi),0);
          break;
        case 6:  
          pixels_14.setPixelColor(i,120+125*(avgghi_14[a]-min_ghi)/(max_ghi-min_ghi), g_ghi,170*(max_ghi-avgghi_14[a])/(max_ghi-min_ghi),0);
          break;
        case 7:  
          pixels_15.setPixelColor(i,120+125*(avgghi_15[a]-min_ghi)/(max_ghi-min_ghi), g_ghi,170*(max_ghi-avgghi_15[a])/(max_ghi-min_ghi),0);
          break;
        case 8:  
          pixels_16.setPixelColor(i,120+125*(avgghi_16[a]-min_ghi)/(max_ghi-min_ghi), g_ghi,170*(max_ghi-avgghi_16[a])/(max_ghi-min_ghi),0);
          break;
        case 9:
          pixels_17.setPixelColor(i,120+125*(avgghi_17[a]-min_ghi)/(max_ghi-min_ghi), g_ghi,170*(max_ghi-avgghi_17[a])/(max_ghi-min_ghi),0);
          break;
        case 10:
          pixels_18.setPixelColor(i,120+125*(avgghi_18[a]-min_ghi)/(max_ghi-min_ghi), g_ghi,170*(max_ghi-avgghi_18[a])/(max_ghi-min_ghi),0);
          break;
        case 11:
         
          pixels_8.setPixelColor(i,120+125*(avgghi_8[a]-min_ghi)/(max_ghi-min_ghi), g_ghi,170*(max_ghi-avgghi_8[a])/(max_ghi-min_ghi),0);
          pixels_9.setPixelColor(i,120+125*(avgghi_9[a]-min_ghi)/(max_ghi-min_ghi), g_ghi,170*(max_ghi-avgghi_9[a])/(max_ghi-min_ghi),0);
          pixels_10.setPixelColor(i,120+125*(avgghi_10[a]-min_ghi)/(max_ghi-min_ghi), g_ghi,170*(max_ghi-avgghi_10[a])/(max_ghi-min_ghi),0);
          pixels_11.setPixelColor(i,120+125*(avgghi_11[a]-min_ghi)/(max_ghi-min_ghi), g_ghi,170*(max_ghi-avgghi_11[a])/(max_ghi-min_ghi),0);
          pixels_12.setPixelColor(i,120+125*(avgghi_12[a]-min_ghi)/(max_ghi-min_ghi), g_ghi,170*(max_ghi-avgghi_12[a])/(max_ghi-min_ghi),0);
          pixels_13.setPixelColor(i,120+125*(avgghi_13[a]-min_ghi)/(max_ghi-min_ghi), g_ghi,170*(max_ghi-avgghi_13[a])/(max_ghi-min_ghi),0);
          pixels_14.setPixelColor(i,120+125*(avgghi_14[a]-min_ghi)/(max_ghi-min_ghi), g_ghi,170*(max_ghi-avgghi_14[a])/(max_ghi-min_ghi),0);
          pixels_15.setPixelColor(i,120+125*(avgghi_15[a]-min_ghi)/(max_ghi-min_ghi), g_ghi,170*(max_ghi-avgghi_15[a])/(max_ghi-min_ghi),0);
          pixels_16.setPixelColor(i,120+125*(avgghi_16[a]-min_ghi)/(max_ghi-min_ghi), g_ghi,170*(max_ghi-avgghi_16[a])/(max_ghi-min_ghi),0);
          pixels_17.setPixelColor(i,120+125*(avgghi_17[a]-min_ghi)/(max_ghi-min_ghi), g_ghi,170*(max_ghi-avgghi_17[a])/(max_ghi-min_ghi),0);
          pixels_18.setPixelColor(i,120+125*(avgghi_18[a]-min_ghi)/(max_ghi-min_ghi), g_ghi,170*(max_ghi-avgghi_18[a])/(max_ghi-min_ghi),0);
        
          break;
    }
    }
  }

  void temp(){
    for (int i = lower_b; i < upper_b; i++) {
      if(i==0){
        a=11;
      }else{
        a=i-1;
      }
      switch(hour){
        case 0:
          pixels_8.setPixelColor(i,255*(avgtemp_8[a]-min_temp)/(max_temp-min_temp), g_temp,255*(max_temp-avgtemp_8[a])/(max_temp-min_temp),0);
          break;
        case 1:
          pixels_9.setPixelColor(i,255*(avgtemp_9[a]-min_temp)/(max_temp-min_temp), g_temp,255*(max_temp-avgtemp_9[a])/(max_temp-min_temp),0);
          break;
        case 2:
          pixels_10.setPixelColor(i,255*(avgtemp_10[a]-min_temp)/(max_temp-min_temp), g_temp,255*(max_temp-avgtemp_10[a])/(max_temp-min_temp),0);
          break;
        case 3:
          pixels_11.setPixelColor(i,255*(avgtemp_11[a]-min_temp)/(max_temp-min_temp), g_temp,255*(max_temp-avgtemp_11[a])/(max_temp-min_temp),0);
          break;
        case 4:
          pixels_12.setPixelColor(i,255*(avgtemp_12[a]-min_temp)/(max_temp-min_temp), g_temp,255*(max_temp-avgtemp_12[a])/(max_temp-min_temp),0);
          break;
        case 5:
          pixels_13.setPixelColor(i,255*(avgtemp_13[a]-min_temp)/(max_temp-min_temp), g_temp,255*(max_temp-avgtemp_13[a])/(max_temp-min_temp),0);
          break;
        case 6:
          pixels_14.setPixelColor(i,255*(avgtemp_14[a]-min_temp)/(max_temp-min_temp), g_temp,255*(max_temp-avgtemp_14[a])/(max_temp-min_temp),0);
          break;
        case 7:
          pixels_15.setPixelColor(i,255*(avgtemp_15[a]-min_temp)/(max_temp-min_temp), g_temp,255*(max_temp-avgtemp_15[a])/(max_temp-min_temp),0);
          break;
        case 8:  
          pixels_16.setPixelColor(i,255*(avgtemp_16[a]-min_temp)/(max_temp-min_temp), g_temp,255*(max_temp-avgtemp_16[a])/(max_temp-min_temp),0);
          break;
        case 9:  
          pixels_17.setPixelColor(i,255*(avgtemp_17[a]-min_temp)/(max_temp-min_temp), g_temp,255*(max_temp-avgtemp_17[a])/(max_temp-min_temp),0);
          break;
        case 10:  
          pixels_18.setPixelColor(i,255*(avgtemp_18[a]-min_temp)/(max_temp-min_temp), g_temp,255*(max_temp-avgtemp_18[a])/(max_temp-min_temp),0);
          break;
        case 11:
          
          pixels_8.setPixelColor(i,255*(avgtemp_8[a]-min_temp)/(max_temp-min_temp), g_temp,255*(max_temp-avgtemp_8[a])/(max_temp-min_temp),0);
          pixels_9.setPixelColor(i,255*(avgtemp_9[a]-min_temp)/(max_temp-min_temp), g_temp,255*(max_temp-avgtemp_9[a])/(max_temp-min_temp),0);
          pixels_10.setPixelColor(i,255*(avgtemp_10[a]-min_temp)/(max_temp-min_temp), g_temp,255*(max_temp-avgtemp_10[a])/(max_temp-min_temp),0);
          pixels_11.setPixelColor(i,255*(avgtemp_11[a]-min_temp)/(max_temp-min_temp), g_temp,255*(max_temp-avgtemp_11[a])/(max_temp-min_temp),0);
          pixels_12.setPixelColor(i,255*(avgtemp_12[a]-min_temp)/(max_temp-min_temp), g_temp,255*(max_temp-avgtemp_12[a])/(max_temp-min_temp),0);
          pixels_13.setPixelColor(i,255*(avgtemp_13[a]-min_temp)/(max_temp-min_temp), g_temp,255*(max_temp-avgtemp_13[a])/(max_temp-min_temp),0);
          pixels_14.setPixelColor(i,255*(avgtemp_14[a]-min_temp)/(max_temp-min_temp), g_temp,255*(max_temp-avgtemp_14[a])/(max_temp-min_temp),0);
          pixels_15.setPixelColor(i,255*(avgtemp_15[a]-min_temp)/(max_temp-min_temp), g_temp,255*(max_temp-avgtemp_15[a])/(max_temp-min_temp),0);
          pixels_16.setPixelColor(i,255*(avgtemp_16[a]-min_temp)/(max_temp-min_temp), g_temp,255*(max_temp-avgtemp_16[a])/(max_temp-min_temp),0);
          pixels_17.setPixelColor(i,255*(avgtemp_17[a]-min_temp)/(max_temp-min_temp), g_temp,255*(max_temp-avgtemp_17[a])/(max_temp-min_temp),0);
          pixels_18.setPixelColor(i,255*(avgtemp_18[a]-min_temp)/(max_temp-min_temp), g_temp,255*(max_temp-avgtemp_18[a])/(max_temp-min_temp),0);
         
          break;
      }
    }
  }

  void dema(){
    for (int i = lower_b; i < upper_b; i++) {
      if(i==0){
        a=11;
      }else{
        a=i-1;
      }
      switch(hour){
      
        case 0:
          pixels_8.setPixelColor(i,50*(avgdema_8[a]-min_dema)/(max_dema-min_dema), g_dema,50+205*(max_dema-avgdema_8[a])/(max_dema-min_dema),0);
          break;
        case 1:
          pixels_9.setPixelColor(i,50*(avgdema_9[a]-min_dema)/(max_dema-min_dema), g_dema,50+205*(max_dema-avgdema_9[a])/(max_dema-min_dema),0);
          break;
        case 2:
          pixels_10.setPixelColor(i,50*(avgdema_10[a]-min_dema)/(max_dema-min_dema), g_dema,50+205*(max_dema-avgdema_10[a])/(max_dema-min_dema),0);
          break;
        case 3:
          pixels_11.setPixelColor(i,50*(avgdema_11[a]-min_dema)/(max_dema-min_dema), g_dema,50+205*(max_dema-avgdema_11[a])/(max_dema-min_dema),0);
          break;
        case 4:
          pixels_12.setPixelColor(i,50*(avgdema_12[a]-min_dema)/(max_dema-min_dema), g_dema,50+205*(max_dema-avgdema_12[a])/(max_dema-min_dema),0);
          break;
        case 5:
          pixels_13.setPixelColor(i,50*(avgdema_13[a]-min_dema)/(max_dema-min_dema), g_dema,50+205*(max_dema-avgdema_13[a])/(max_dema-min_dema),0);
          break;
        case 6:
          pixels_14.setPixelColor(i,50*(avgdema_14[a]-min_dema)/(max_dema-min_dema), g_dema,50+205*(max_dema-avgdema_14[a])/(max_dema-min_dema),0);
          break;
        case 7:
          pixels_15.setPixelColor(i,50*(avgdema_15[a]-min_dema)/(max_dema-min_dema), g_dema,50+205*(max_dema-avgdema_15[a])/(max_dema-min_dema),0);
          break;
        case 8:  
          pixels_16.setPixelColor(i,50*(avgdema_16[a]-min_dema)/(max_dema-min_dema), g_dema,50+205*(max_dema-avgdema_16[a])/(max_dema-min_dema),0);
          break;
        case 9:  
          pixels_17.setPixelColor(i,50*(avgdema_17[a]-min_dema)/(max_dema-min_dema), g_dema,50+205*(max_dema-avgdema_17[a])/(max_dema-min_dema),0);
          break;
        case 10:  
          pixels_18.setPixelColor(i,50*(avgdema_18[a]-min_dema)/(max_dema-min_dema), g_dema,50+205*(max_dema-avgdema_18[a])/(max_dema-min_dema),0);
          break;
        case 11:
          
          pixels_8.setPixelColor(i,50*(avgdema_8[a]-min_dema)/(max_dema-min_dema), g_dema,50+205*(max_dema-avgdema_8[a])/(max_dema-min_dema),0);
          pixels_9.setPixelColor(i,50*(avgdema_9[a]-min_dema)/(max_dema-min_dema), g_dema,50+205*(max_dema-avgdema_9[a])/(max_dema-min_dema),0);
          pixels_10.setPixelColor(i,50*(avgdema_10[a]-min_dema)/(max_dema-min_dema), g_dema,50+205*(max_dema-avgdema_10[a])/(max_dema-min_dema),0);
          pixels_11.setPixelColor(i,50*(avgdema_11[a]-min_dema)/(max_dema-min_dema), g_dema,50+205*(max_dema-avgdema_11[a])/(max_dema-min_dema),0);
          pixels_12.setPixelColor(i,50*(avgdema_12[a]-min_dema)/(max_dema-min_dema), g_dema,50+205*(max_dema-avgdema_12[a])/(max_dema-min_dema),0);
          pixels_13.setPixelColor(i,50*(avgdema_13[a]-min_dema)/(max_dema-min_dema), g_dema,50+205*(max_dema-avgdema_13[a])/(max_dema-min_dema),0);
          pixels_14.setPixelColor(i,50*(avgdema_14[a]-min_dema)/(max_dema-min_dema), g_dema,50+205*(max_dema-avgdema_14[a])/(max_dema-min_dema),0);
          pixels_15.setPixelColor(i,50*(avgdema_15[a]-min_dema)/(max_dema-min_dema), g_dema,50+205*(max_dema-avgdema_15[a])/(max_dema-min_dema),0);
          pixels_16.setPixelColor(i,50*(avgdema_16[a]-min_dema)/(max_dema-min_dema), g_dema,50+205*(max_dema-avgdema_16[a])/(max_dema-min_dema),0);
          pixels_17.setPixelColor(i,50*(avgdema_17[a]-min_dema)/(max_dema-min_dema), g_dema,50+205*(max_dema-avgdema_17[a])/(max_dema-min_dema),0);
          pixels_18.setPixelColor(i,50*(avgdema_18[a]-min_dema)/(max_dema-min_dema), g_dema,50+205*(max_dema-avgdema_18[a])/(max_dema-min_dema),0);
          break;
      }
    }
  }

void grid(){
    for (int i = lower_b; i < upper_b; i++) {
      if(i==0){
        a=11;
      }else{
        a=i-1;
      }
        switch (hour) {
        case 0:  
          pixels_8.setPixelColor(i,255*(avggrid_8[a]-min_grid)/(max_grid-min_grid), 255*(max_grid-avggrid_8[a])/(max_grid-min_grid),b_grid,0);
          break;
        case 1:  
          pixels_9.setPixelColor(i,255*(avggrid_9[a]-min_grid)/(max_grid-min_grid), 255*(max_grid-avggrid_9[a])/(max_grid-min_grid),b_grid,0);
          break;
        case 2:  
          pixels_10.setPixelColor(i,255*(avggrid_10[a]-min_grid)/(max_grid-min_grid), 255*(max_grid-avggrid_10[a])/(max_grid-min_grid),b_grid,0);
          break;
        case 3:  
          pixels_11.setPixelColor(i,255*(avggrid_11[a]-min_grid)/(max_grid-min_grid), 255*(max_grid-avggrid_11[a])/(max_grid-min_grid),b_grid,0);
          break;
        case 4:  
          pixels_12.setPixelColor(i,255*(avggrid_12[a]-min_grid)/(max_grid-min_grid), 255*(max_grid-avggrid_12[a])/(max_grid-min_grid),b_grid,0);
          break;
        case 5:  
          pixels_13.setPixelColor(i,255*(avggrid_13[a]-min_grid)/(max_grid-min_grid), 255*(max_grid-avggrid_13[a])/(max_grid-min_grid),b_grid,0);
          break;
        case 6:  
          pixels_14.setPixelColor(i,255*(avggrid_14[a]-min_grid)/(max_grid-min_grid), 255*(max_grid-avggrid_14[a])/(max_grid-min_grid),b_grid,0);
          break;
        case 7:  
          pixels_15.setPixelColor(i,255*(avggrid_15[a]-min_grid)/(max_grid-min_grid), 255*(max_grid-avggrid_15[a])/(max_grid-min_grid),b_grid,0);
          break;
        case 8:  
          pixels_16.setPixelColor(i,255*(avggrid_16[a]-min_grid)/(max_grid-min_grid), 255*(max_grid-avggrid_16[a])/(max_grid-min_grid),b_grid,0);
          break;
        case 9:  
          pixels_17.setPixelColor(i,255*(avggrid_17[a]-min_grid)/(max_grid-min_grid), 255*(max_grid-avggrid_17[a])/(max_grid-min_grid),b_grid,0);
          break;
        case 10:  
          pixels_18.setPixelColor(i,255*(avggrid_18[a]-min_grid)/(max_grid-min_grid), 255*(max_grid-avggrid_18[a])/(max_grid-min_grid),b_grid,0);
          break;
        case 11:
          
          pixels_8.setPixelColor(i,255*(avggrid_8[a]-min_grid)/(max_grid-min_grid), 255*(max_grid-avggrid_8[a])/(max_grid-min_grid),b_grid,0);
          pixels_9.setPixelColor(i,255*(avggrid_9[a]-min_grid)/(max_grid-min_grid), 255*(max_grid-avggrid_9[a])/(max_grid-min_grid),b_grid,0);
          pixels_10.setPixelColor(i,255*(avggrid_10[a]-min_grid)/(max_grid-min_grid), 255*(max_grid-avggrid_10[a])/(max_grid-min_grid),b_grid,0);
          pixels_11.setPixelColor(i,255*(avggrid_11[a]-min_grid)/(max_grid-min_grid), 255*(max_grid-avggrid_11[a])/(max_grid-min_grid),b_grid,0);
          pixels_12.setPixelColor(i,255*(avggrid_12[a]-min_grid)/(max_grid-min_grid), 255*(max_grid-avggrid_12[a])/(max_grid-min_grid),b_grid,0);
          pixels_13.setPixelColor(i,255*(avggrid_13[a]-min_grid)/(max_grid-min_grid), 255*(max_grid-avggrid_13[a])/(max_grid-min_grid),b_grid,0);
          pixels_14.setPixelColor(i,255*(avggrid_14[a]-min_grid)/(max_grid-min_grid), 255*(max_grid-avggrid_14[a])/(max_grid-min_grid),b_grid,0);
          pixels_15.setPixelColor(i,255*(avggrid_15[a]-min_grid)/(max_grid-min_grid), 255*(max_grid-avggrid_15[a])/(max_grid-min_grid),b_grid,0);
          pixels_16.setPixelColor(i,255*(avggrid_16[a]-min_grid)/(max_grid-min_grid), 255*(max_grid-avggrid_16[a])/(max_grid-min_grid),b_grid,0);
          pixels_17.setPixelColor(i,255*(avggrid_17[a]-min_grid)/(max_grid-min_grid), 255*(max_grid-avggrid_17[a])/(max_grid-min_grid),b_grid,0);
          pixels_18.setPixelColor(i,255*(avggrid_18[a]-min_grid)/(max_grid-min_grid), 255*(max_grid-avggrid_18[a])/(max_grid-min_grid),b_grid,0);
        
          break;
     
     
        }

    }
  }
  void sunpos(){
    for (int i = lower_b; i < upper_b; i++) {
      switch (hour) {
      
        case 0:  
          pixels_8.setPixelColor(i,r_sun,g_sun,b_sun,w_sun);
          break;
        case 1:  
          pixels_9.setPixelColor(i,r_sun,g_sun,b_sun,w_sun);
          break;
        case 2:  
          pixels_10.setPixelColor(i,r_sun,g_sun,b_sun,w_sun);
          break;
        case 3:
          pixels_11.setPixelColor(i,r_sun,g_sun,b_sun,w_sun);
          break;
        case 4:
          pixels_12.setPixelColor(i,r_sun,g_sun,b_sun,w_sun);
          break;
        case 5:
          pixels_13.setPixelColor(i,r_sun,g_sun,b_sun,w_sun);
          break;
        case 6:
          pixels_14.setPixelColor(i,r_sun,g_sun,b_sun,w_sun);
          break;
        case 7:
          pixels_15.setPixelColor(i,r_sun,g_sun,b_sun,w_sun);
          break;
        case 8:
          pixels_16.setPixelColor(i,r_sun,g_sun,b_sun,w_sun);
          break;
        case 9:
          pixels_17.setPixelColor(i,r_sun,g_sun,b_sun,w_sun);
          break;
        case 10:
          pixels_18.setPixelColor(i,r_sun,g_sun,b_sun,w_sun);
          break;
        case 11:
        
          pixels_8.setPixelColor(i,r_sun,g_sun,b_sun,w_sun);
          pixels_9.setPixelColor(i,r_sun,g_sun,b_sun,w_sun);
          pixels_10.setPixelColor(i,r_sun,g_sun,b_sun,w_sun);
          pixels_11.setPixelColor(i,r_sun,g_sun,b_sun,w_sun);
          pixels_12.setPixelColor(i,r_sun,g_sun,b_sun,w_sun);
          pixels_13.setPixelColor(i,r_sun,g_sun,b_sun,w_sun);
          pixels_14.setPixelColor(i,r_sun,g_sun,b_sun,w_sun);
          pixels_15.setPixelColor(i,r_sun,g_sun,b_sun,w_sun);
          pixels_16.setPixelColor(i,r_sun,g_sun,b_sun,w_sun);
          pixels_17.setPixelColor(i,r_sun,g_sun,b_sun,w_sun);
          pixels_18.setPixelColor(i,r_sun,g_sun,b_sun,w_sun);
          break;
      }
     

     
     

    }
  }
  void wait(){
    while(millis() < time_now + period){
        //wait approx. [period] ms
          }
    time_now = millis();
    show();     
  }
 
  void show(){
  
    pixels_8.show();
    pixels_9.show();
    pixels_10.show();  
    pixels_11.show();
    pixels_12.show();
    pixels_13.show();
    pixels_14.show();
    pixels_15.show();
    pixels_16.show();
    pixels_17.show(); 
    pixels_18.show();
  }

void clear_pix(){
    
    pixels_8.clear();
    pixels_9.clear();
    pixels_10.clear();
    pixels_11.clear();
    pixels_12.clear();
    pixels_13.clear();
    pixels_14.clear();
    pixels_15.clear();
    pixels_16.clear();
    pixels_17.clear();
    pixels_18.clear();
    show();
}

void turn_mode(){
  encoderPINANow_mode = digitalRead(encoderPINA_mode);
  if ((encoderPINALast_mode == HIGH) && (encoderPINANow_mode == LOW)) {
    if (digitalRead(encoderPINB_mode) == HIGH) {
      if (encoderPos_mode<4) {
        encoderPos_mode++;
      } else {
      encoderPos_mode=0;
      }
    } else {
      if(encoderPos_mode>0){
        encoderPos_mode--;
      } else if (encoderPos_mode==0) {
        encoderPos_mode=4;
      }
    }
    
    clear_pix();
    clearLCDLine(0);
    turn_flag=1;
    mode=encoderPos_mode;
    print_mode();
  }
  encoderPINALast_mode = encoderPINANow_mode;
}

void turn_month(){
  encoderPINANow_month = digitalRead(encoderPINA_month);
  if ((encoderPINALast_month == HIGH) && (encoderPINANow_month == LOW)) {
    if (digitalRead(encoderPINB_month) == HIGH) {
      if (encoderPos_month<12) {
        encoderPos_month++;
      } else {
      encoderPos_month=0;
      }
    } else {
      if(encoderPos_month>0){
        encoderPos_month--;
      } else if (encoderPos_month==0) {
        encoderPos_month=12;
      }
    }
    
    clear_pix();
    clearLCDLine(1);
    turn_flag=1;
    month=encoderPos_month;
    print_month();
  }
  encoderPINALast_month = encoderPINANow_month; 
}

void turn_hour(){
  encoderPINANow_hour = digitalRead(encoderPINA_hour);
  if ((encoderPINALast_hour == HIGH) && (encoderPINANow_hour == LOW)) {
    if (digitalRead(encoderPINB_hour) == HIGH) {
      if (encoderPos_hour<11) {
        encoderPos_hour++;
      } else {
      encoderPos_hour=0;
      }
    } else {
      if(encoderPos_hour>0){
        encoderPos_hour--;
      } else if (encoderPos_hour==0) {
        encoderPos_hour=11;
      }
    }
    clear_pix();
    clearLCDLine(2);
    turn_flag=1;
    Serial.println(encoderPos_hour);
    hour=encoderPos_hour;
    print_hour();
  }
  encoderPINALast_hour = encoderPINANow_hour; 
}

void print_month(){
  lcd.setCursor(2,1); //Set cursor to character 0 on line 1
  switch(month){
    case 1:
      lcd.print("Month: January");
      break;
    case 2:
      lcd.print("Month: February");
      break;
    case 3:
      lcd.print("Month: March");
      break;
    case 4:
      lcd.print("Month: April");
      break;
    case 5:
      lcd.print("Month: Mai");
      break;
    case 6:
      lcd.print("Month: June");
      break;
    case 7:
      lcd.print("Month: July");
      break;
    case 8:
      lcd.print("Month: August");
      break;
    case 9:
      lcd.print("Month: September");
      break;
    case 10:
      lcd.print("Month: October");
      break;
    case 11:
      lcd.print("Month: November");
      break;
    case 0:
      lcd.print("Month: December");
      break;
    case 12:
      lcd.print("Month: All");
      break;
  }
  print_min_max();
}

void print_mode(){
  lcd.setCursor(0,0);
  switch (mode) {
  case 0:
    lcd.print("1/5 TEMPERATURE");
    break;
  case 1:
    lcd.print("2/5 GRID EMISSIONS");
    break;
  case 2:
    lcd.print("3/5 IRRADIATION");
    break;
  case 3:
    lcd.print("4/5 ENERGY DEMAND");
    break;
  case 4:
    lcd.print("5/5 SUN POSITION");
    break;
  
  }
  print_min_max();
  
}

void print_hour(){
  lcd.setCursor(2,2);
   switch(hour){
        case 0:
          lcd.print("Hour: 08:00");
          break;
        case 1: 
          lcd.print("Hour: 09:00"); 
          break;
        case 2:
          lcd.print("Hour: 10:00");
          break;
        case 3:
          lcd.print("Hour: 11:00");
          break;
        case 4:
          lcd.print("Hour: 12:00");
          break;
        case 5:
          lcd.print("Hour: 13:00");
          break;
        case 6: 
          lcd.print("Hour: 14:00"); 
          break;
        case 7:  
          lcd.print("Hour: 15:00");
          break;
        case 8:
          lcd.print("Hour: 16:00");  
          break;
        case 9:
          lcd.print("Hour: 17:00");
          break;
        case 10:
          lcd.print("Hour: 18:00");
          break;
        case 11:
          lcd.print("Hour: ALL");
          break; 
   }
   print_min_max();
}

void print_min_max(){
  clearLCDLine(3);
  lcd.setCursor(1,3);
  if(month==12 && hour==11){
  lcd.setCursor(1,3);
  switch (mode) {
    case 0:
    lcd.print("MIN:"+String(round(min_temp_si)));
    lcd.setCursor(12, 3);
    lcd.print("MAX:"+String(round(max_temp_si)));
    break;
    case 1:
    lcd.print("MIN:"+String(round(min_grid_si)));
    lcd.setCursor(12, 3);
    lcd.print("MAX:"+String(round(max_grid_si)));
    break;
    case 2:
    lcd.print("MIN:"+String(round(min_ghi_si)));
    lcd.setCursor(12, 3);
    lcd.print("MAX:"+String(round(max_ghi_si)));
    break;
  case 3:
    lcd.print("MIN:"+String(round(min_dema_si)));
    lcd.setCursor(12, 3);
    lcd.print("MAX:"+String(round(max_dema_si)));
    break;
   case 4:
    break;
   
  }
  }else if(month<12 && hour<11){
    lcd.setCursor(1,3);
    if(month==0){
        aa=11;
      }else{
        aa=month-1;
      }
    switch (mode) {
      case 0:
        switch (hour) {
        case 0: 
          lcd.print("Temp: "+String(round(avgtemp_8[aa]))); 
          break;
        case 1:  
          lcd.print("Temp: "+String(round(avgtemp_9[aa]))); 
          break;
        case 2: 
          lcd.print("Temp: "+String(round(avgtemp_10[aa])));  
          break;
        case 3: 
          lcd.print("Temp: "+String(round(avgtemp_11[aa])));  
          break;
        case 4: 
          lcd.print("Temp: "+String(round(avgtemp_12[aa])));  
          break;
        case 5: 
          lcd.print("Temp: "+String(round(avgtemp_13[aa])));  
          break;
        case 6: 
          lcd.print("Temp: "+String(round(avgtemp_14[aa])));  
          break;
        case 7: 
          lcd.print("Temp: "+String(round(avgtemp_15[aa])));  
          break;
        case 8: 
          lcd.print("Temp: "+String(round(avgtemp_16[aa])));  
          break;
        case 9: 
          lcd.print("Temp: "+String(round(avgtemp_17[aa])));  
          break;
        case 10:
          lcd.print("Temp: "+String(round(avgtemp_18[aa])));   
          break;
        }
        break;
      case 1:
        switch (hour) {
        case 0: 
          lcd.print("Emis: "+String(round(avggrid_8[aa]))+unit_grid); 
          break;
        case 1:  
          lcd.print("Emis: "+String(round(avggrid_9[aa]))+unit_grid); 
          break;
        case 2: 
          lcd.print("Emis: "+String(round(avggrid_10[aa]))+unit_grid);  
          break;
        case 3: 
          lcd.print("Emis: "+String(round(avggrid_11[aa]))+unit_grid);  
          break;
        case 4: 
          lcd.print("Emis: "+String(round(avggrid_12[aa]))+unit_grid);  
          break;
        case 5: 
          lcd.print("Emis: "+String(round(avggrid_13[aa]))+unit_grid);  
          break;
        case 6: 
          lcd.print("Emis: "+String(round(avggrid_14[aa]))+unit_grid);  
          break;
        case 7: 
          lcd.print("Emis: "+String(round(avggrid_15[aa]))+unit_grid);  
          break;
        case 8: 
          lcd.print("Emis: "+String(round(avggrid_16[aa]))+unit_grid);  
          break;
        case 9: 
          lcd.print("Emis: "+String(round(avggrid_17[aa]))+unit_grid);  
          break;
        case 10:
          lcd.print("Emis: "+String(round(avggrid_18[aa]))+unit_grid);   
          break;
        }
        break;
      case 2:
        switch (hour) {
        case 0: 
          lcd.print("Irrad: "+String(round(avgghi_8[aa]))+unit_ghi); 
          break;
        case 1:  
          lcd.print("Irrad: "+String(round(avgghi_9[aa]))+unit_ghi); 
          break;
        case 2: 
          lcd.print("Irrad: "+String(round(avgghi_10[aa]))+unit_ghi);  
          break;
        case 3: 
          lcd.print("Irrad: "+String(round(avgghi_11[aa]))+unit_ghi);  
          break;
        case 4: 
          lcd.print("Irrad: "+String(round(avgghi_12[aa]))+unit_ghi);  
          break;
        case 5: 
          lcd.print("Irrad: "+String(round(avgghi_13[aa]))+unit_ghi);  
          break;
        case 6: 
          lcd.print("Irrad: "+String(round(avgghi_14[aa]))+unit_ghi);  
          break;
        case 7: 
          lcd.print("Irrad: "+String(round(avgghi_15[aa]))+unit_ghi);  
          break;
        case 8: 
          lcd.print("Irrad: "+String(round(avgghi_16[aa]))+unit_ghi);  
          break;
        case 9: 
          lcd.print("Irrad: "+String(round(avgghi_17[aa]))+unit_ghi);  
          break;
        case 10:
          lcd.print("Irrad: "+String(round(avgghi_18[aa]))+unit_ghi);   
          break;
        }
        break;
      case 3:
      switch (hour) {
        case 0: 
          lcd.print("Demand: "+String(round(avgdema_8[aa]))+unit_dema); 
          break;
        case 1:  
          lcd.print("Demand: "+String(round(avgdema_9[aa]))+unit_dema); 
          break;
        case 2: 
          lcd.print("Demand: "+String(round(avgdema_10[aa]))+unit_dema);  
          break;
        case 3: 
          lcd.print("Demand: "+String(round(avgdema_11[aa]))+unit_dema);  
          break;
        case 4: 
          lcd.print("Demand: "+String(round(avgdema_12[aa]))+unit_dema);  
          break;
        case 5: 
          lcd.print("Demand: "+String(round(avgdema_13[aa]))+unit_dema);  
          break;
        case 6: 
          lcd.print("Demand: "+String(round(avgdema_14[aa]))+unit_dema);  
          break;
        case 7: 
          lcd.print("Demand: "+String(round(avgdema_15[aa]))+unit_dema);  
          break;
        case 8: 
          lcd.print("Demand: "+String(round(avgdema_16[aa]))+unit_dema);  
          break;
        case 9: 
          lcd.print("Demand: "+String(round(avgdema_17[aa]))+unit_dema);  
          break;
        case 10:
          lcd.print("Demand: "+String(round(avgdema_18[aa]))+unit_dema);   
          break;
        }
        break;
      case 4:
        break;
  }
  }else if(month<12 && hour==11){
    if(month==0){
        aa=11;
      }else{
        aa=month-1;
      }
    switch (mode) {
      case 0:
        temp_array[0]=avgtemp_8[aa];
        temp_array[1]=avgtemp_9[aa];
        temp_array[2]=avgtemp_10[aa];
        temp_array[3]=avgtemp_11[aa];
        temp_array[4]=avgtemp_12[aa];
        temp_array[5]=avgtemp_13[aa];
        temp_array[6]=avgtemp_14[aa];
        temp_array[7]=avgtemp_15[aa];
        temp_array[8]=avgtemp_16[aa];
        temp_array[9]=avgtemp_17[aa];
        temp_array[10]=avgtemp_18[aa];
        break;
      case 1:
        temp_array[0]=avggrid_8[aa];
        temp_array[1]=avggrid_9[aa];
        temp_array[2]=avggrid_10[aa];
        temp_array[3]=avggrid_11[aa];
        temp_array[4]=avggrid_12[aa];
        temp_array[5]=avggrid_13[aa];
        temp_array[6]=avggrid_14[aa];
        temp_array[7]=avggrid_15[aa];
        temp_array[8]=avggrid_16[aa];
        temp_array[9]=avggrid_17[aa];
        temp_array[10]=avggrid_18[aa];
        break;
      case 2:
        temp_array[0]=avgghi_8[aa];
        temp_array[1]=avgghi_9[aa];
        temp_array[2]=avgghi_10[aa];
        temp_array[3]=avgghi_11[aa];
        temp_array[4]=avgghi_12[aa];
        temp_array[5]=avgghi_13[aa];
        temp_array[6]=avgghi_14[aa];
        temp_array[7]=avgghi_15[aa];
        temp_array[8]=avgghi_16[aa];
        temp_array[9]=avgghi_17[aa];
        temp_array[10]=avgghi_18[aa];
        break;
      case 3:
        temp_array[0]=avgdema_8[aa];
        temp_array[1]=avgdema_9[aa];
        temp_array[2]=avgdema_10[aa];
        temp_array[3]=avgdema_11[aa];
        temp_array[4]=avgdema_12[aa];
        temp_array[5]=avgdema_13[aa];
        temp_array[6]=avgdema_14[aa];
        temp_array[7]=avgdema_15[aa];
        temp_array[8]=avgdema_16[aa];
        temp_array[9]=avgdema_17[aa];
        temp_array[10]=avgdema_18[aa];
        break;
      case 4:
        break;
    }
    min_max(temp_array);
    lcd.print("MIN:"+String(round(minValue)));
    lcd.setCursor(12, 3);
    lcd.print("MAX:"+String(round(maxValue)));

  }else if(month==12 && hour<11){
    if(month==0){
        aa=11;
      }else{
        aa=month-1;
      }
    lcd.setCursor(1,3);
      switch (mode) {
      case 0:
        switch (hour) {
        case 0: 
          min_max(avgtemp_8);
          break;
        case 1:  
          min_max(avgtemp_9);
          break;
        case 2: 
          min_max(avgtemp_10);
          break;
        case 3: 
          min_max(avgtemp_11);
          break;
        case 4: 
          min_max(avgtemp_12);
          break;
        case 5: 
          min_max(avgtemp_13);
          break;
        case 6: 
          min_max(avgtemp_14);
          break;
        case 7: 
          min_max(avgtemp_15);
          break;
        case 8: 
          min_max(avgtemp_16);
          break;
        case 9: 
          min_max(avgtemp_17);
          break;
        case 10:
          min_max(avgtemp_18);
          break;
        }
        lcd.print("MIN:"+String(round(minValue)));
        lcd.setCursor(12, 3);
        lcd.print("MAX:"+String(round(maxValue)));
        break;
      case 1:
        switch (hour) {
        case 0: 
          min_max(avggrid_8);
          break;
        case 1:  
          min_max(avggrid_9);
          break;
        case 2: 
          min_max(avggrid_10);
          break;
        case 3: 
          min_max(avggrid_11);
          break;
        case 4: 
          min_max(avggrid_12);
          break;
        case 5: 
          min_max(avggrid_13);
          break;
        case 6: 
          min_max(avggrid_14);
          break;
        case 7: 
          min_max(avggrid_15);
          break;
        case 8: 
          min_max(avggrid_16);
          break;
        case 9: 
          min_max(avggrid_17);
          break;
        case 10:
          min_max(avggrid_18);
          break;
        }
        lcd.print("MIN:"+String(round(minValue)));
        lcd.setCursor(12, 3);
        lcd.print("MAX:"+String(round(maxValue)));
        break;
      case 2:
        switch (hour) {
        case 0: 
          min_max(avgghi_8);
          break;
        case 1:  
          min_max(avgghi_9);
          break;
        case 2: 
          min_max(avgghi_10);
          break;
        case 3: 
          min_max(avgghi_11);
          break;
        case 4: 
          min_max(avgghi_12);
          break;
        case 5: 
          min_max(avgghi_13);
          break;
        case 6: 
          min_max(avgghi_14);
          break;
        case 7: 
          min_max(avgghi_15);
          break;
        case 8: 
          min_max(avgghi_16);
          break;
        case 9: 
          min_max(avgghi_17);
          break;
        case 10:
          min_max(avgghi_18);
          break;
        }
        lcd.print("MIN:"+String(round(minValue)));
        lcd.setCursor(12, 3);
        lcd.print("MAX:"+String(round(maxValue)));
        break;
      
      case 3:
      switch (hour) {
        case 0: 
          min_max(avgdema_8);
          break;
        case 1:  
          min_max(avgdema_9);
          break;
        case 2: 
          min_max(avgdema_10);
          break;
        case 3: 
          min_max(avgdema_11);
          break;
        case 4: 
          min_max(avgdema_12);
          break;
        case 5: 
          min_max(avgdema_13);
          break;
        case 6: 
          min_max(avgdema_14);
          break;
        case 7: 
          min_max(avgdema_15);
          break;
        case 8: 
          min_max(avgdema_16);
          break;
        case 9: 
          min_max(avgdema_17);
          break;
        case 10:
          min_max(avgdema_18);
          break;
        }
        lcd.print("MIN:"+String(round(minValue)));
        lcd.setCursor(12, 3);
        lcd.print("MAX:"+String(round(maxValue)));
        break;
      case 4:
        break;
  }

  }
}
void clearLCDLine(int line){
for(int n = 0; n < 20; n++) { 
lcd.setCursor(n,line);
lcd.print(" ");
}
}

void min_max(float ar[]){
  minValue = Min(ar[0], ar[1]);
  maxValue = Max(ar[0], ar[1]); 
  for (int i = 2; i < 12; i++) {
    if(minValue>ar[a]){
      minValue=ar[a];
    }
    if (maxValue<ar[a]) {
      maxValue=ar[a];
    }
  }
}


 
