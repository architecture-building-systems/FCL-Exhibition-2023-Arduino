#include <Adafruit_NeoPixel.h>
#include <PGMWrap.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,20,4);

#define PIX_4 18
#define PIX_5 19
#define PIX_6 2
#define PIX_7 3
#define PIX_8 4
#define PIX_9 5
#define PIX_10 6
#define PIX_11 7
#define PIX_12 8
#define PIX_13 9
#define PIX_14 10
#define PIX_15 11
#define PIX_16 12
#define PIX_17 13
#define PIX_18 14
#define PIX_19 15


#define CONT_1 20
#define CONT_2 21
#define CONT_3 22

#define ENC_mode_A 24
#define ENC_mode_B 25
#define ENC_month_A 28
#define ENC_month_B 29
#define ENC_hour_A 46
#define ENC_hour_B 47

#define NUMPIXELS 12
#define DELAYVAL 100

//initialize pixles for the analemmas
Adafruit_NeoPixel pixels_4(NUMPIXELS, PIX_4, NEO_GRBW + NEO_KHZ800);
Adafruit_NeoPixel pixels_5(NUMPIXELS, PIX_5, NEO_GRBW + NEO_KHZ800);
Adafruit_NeoPixel pixels_6(NUMPIXELS, PIX_6, NEO_GRBW + NEO_KHZ800);
Adafruit_NeoPixel pixels_7(NUMPIXELS, PIX_7, NEO_GRBW + NEO_KHZ800);
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
Adafruit_NeoPixel pixels_19(NUMPIXELS, PIX_19, NEO_GRBW + NEO_KHZ800);

//initialize pixles for the control panel
Adafruit_NeoPixel control_1(NUMPIXELS, CONT_1, NEO_GRBW + NEO_KHZ800);
Adafruit_NeoPixel control_2(NUMPIXELS, CONT_2, NEO_GRBW + NEO_KHZ800);
Adafruit_NeoPixel control_3(NUMPIXELS, CONT_3, NEO_GRBW + NEO_KHZ800);



String unit_temp="C";
String unit_grid="kgCO2/kWh";
String unit_ghi="W/m2";
String unit_dema="kWh";
float temp_array[]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
volatile int mode=0;
volatile int month=12;
volatile int hour=16;
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

// ZURICH GHI
float avgghi_4[]={0,0,0,0,0,1,0,0,0,0,0,0};
float avgghi_5[]={0,0,0,2,34,62,42,4,0,0,0,0};
float avgghi_6[]={0,0,2,57,128,161,144,96,21,1,0,0};
float avgghi_7[]={0,2,59,162,251,290,261,213,131,43,1,0};
float avgghi_8[]={7,58,164,289,361,399,386,340,244,135,44,6};
float avgghi_9[]={65,137,271,398,472,526,501,441,332,200,104,64};
float avgghi_10[]={113,208,345,495,522,596,580,517,407,249,147,111};
float avgghi_11[]={163,248,396,491,548,601,585,542,446,267,176,145};
float avgghi_12[]={170,276,429,526,592,567,564,554,444,280,182,134};
float avgghi_13[]={187,323,432,523,545,561,548,535,438,301,208,146};
float avgghi_14[]={145,264,385,469,489,519,532,478,389,253,153,108};
float avgghi_15[]={88,186,293,392,423,455,464,399,321,170,84,56};
float avgghi_16[]={19,100,191,295,331,353,355,312,215,79,9,2};
float avgghi_17[]={0,9,85,163,208,251,252,196,102,6,0,0};
float avgghi_18[]={0,0,3,48,101,134,139,89,7,0,0,0};
float avgghi_19[]={0,0,0,0,15,53,48,5,0,0,0,0};
float avgghi_20[]={0,0,0,0,0,1,0,0,0,0,0,0};
float g_ghi=200;
float max_ghi=728;
float min_ghi=1;
float max_ghi_si=601;
float min_ghi_si=1;

// ZURICH TEMP
float avgtemp_4[]={-1,0,2,5,9,12,14,14,10,7,3,0};
float avgtemp_5[]={-1,-1,2,5,9,12,14,14,10,7,2,0};
float avgtemp_6[]={-1,-1,1,5,10,13,14,14,9,7,2,0};
float avgtemp_7[]={-2,-1,1,5,11,14,15,15,10,7,2,0};
float avgtemp_8[]={-2,-1,2,7,12,16,17,16,11,8,2,0};
float avgtemp_9[]={-1,0,4,8,14,17,18,18,13,9,3,0};
float avgtemp_10[]={0,1,5,10,15,19,20,19,15,11,4,1};
float avgtemp_11[]={1,3,7,12,17,20,21,21,16,12,6,2};
float avgtemp_12[]={2,4,8,13,18,21,22,22,17,13,6,3};
float avgtemp_13[]={3,5,9,14,19,22,23,22,18,13,7,4};
float avgtemp_14[]={3,5,10,14,19,22,23,23,18,14,8,4};
float avgtemp_15[]={4,6,10,15,19,23,24,23,19,14,8,4};
float avgtemp_16[]={3,6,10,15,19,23,24,23,19,14,8,4};
float avgtemp_17[]={2,5,10,14,19,23,23,23,18,13,7,3};
float avgtemp_18[]={2,4,9,14,18,22,23,22,17,12,6,3};
float avgtemp_19[]={2,4,8,12,18,21,22,21,16,12,6,2};
float avgtemp_20[]={1,3,7,11,16,20,21,20,15,11,5,2};
float g_temp=0;
float max_temp=32;
float min_temp=-2;
float max_temp_si=24;
float min_temp_si=-2;

// ZURICH GRID EMISSIONS
float avggrid_4[]={125,149,137,102,41,49,64,105,125,166,144,139};
float avggrid_5[]={122,138,128,89,37,39,51,93,106,144,145,140};
float avggrid_6[]={110,121,113,81,36,37,49,84,95,128,133,135};
float avggrid_7[]={104,114,105,79,37,39,50,81,95,123,129,132};
float avggrid_8[]={102,109,101,81,40,44,55,81,99,121,127,128};
float avggrid_9[]={99,106,101,83,43,48,59,80,102,120,127,126};
float avggrid_10[]={98,107,103,84,44,50,62,84,103,119,127,126};
float avggrid_11[]={98,111,106,87,45,53,64,88,107,125,129,128};
float avggrid_12[]={103,118,110,89,46,56,67,92,111,133,133,131};
float avggrid_13[]={108,126,113,91,46,57,69,93,114,142,136,137};
float avggrid_14[]={112,133,116,94,46,56,69,95,116,147,138,139};
float avggrid_15[]={113,136,118,97,43,49,63,94,117,145,135,134};
float avggrid_16[]={102,125,120,96,38,41,55,86,109,127,122,126};
float avggrid_17[]={91,104,108,90,33,33,49,80,95,108,115,124};
float avggrid_18[]={91,96,94,86,31,30,47,80,91,111,119,126};
float avggrid_19[]={106,110,107,91,32,33,49,85,108,139,129,133};

float b_grid=0;
float max_grid=145;
float min_grid=30;
float max_grid_si=192;
float min_grid_si=88;

// ZURICH DEMAND
float avgdema_4[]={908,1067,746,370,123,118,118,113,141,263,689,1007};
float avgdema_5[]={908,1067,746,370,123,118,118,113,141,263,689,1007};
float avgdema_6[]={2711,2914,2461,1852,578,319,306,291,800,1599,2440,2838};
float avgdema_7[]={2850,3044,2593,1934,598,284,273,266,844,1740,2576,2960};
float avgdema_8[]={2847,3038,2550,1852,594,278,267,268,832,1731,2564,2950};
float avgdema_9[]={2744,2879,2386,1686,533,242,228,232,760,1603,2443,2828};
float avgdema_10[]={2626,2744,2244,1543,481,224,206,207,705,1487,2321,2717};
float avgdema_11[]={2502,2589,2094,1396,468,223,199,192,657,1375,2213,2605};
float avgdema_12[]={2158,2225,1718,1056,370,267,198,179,525,1048,1862,2266};
float avgdema_13[]={2284,2363,1836,1182,390,236,198,182,577,1174,1991,2405};
float avgdema_14[]={2203,2260,1735,1058,298,154,115,101,497,1109,1925,2327};
float avgdema_15[]={2154,2191,1660,977,262,133,96,79,465,1063,1877,2288};
float avgdema_16[]={2152,2192,1664,966,266,141,100,91,474,1088,1882,2275};
float avgdema_17[]={2182,2226,1705,993,344,232,184,172,540,1132,1914,2308};
float avgdema_18[]={2020,2098,1583,903,380,307,231,213,524,1020,1761,2147};
float avgdema_19[]={1924,2024,1521,862,366,298,223,193,490,956,1675,2041};
float avgdema_20[]={2122,2242,1765,1094,360,216,202,192,555,1180,1882,2250};
float g_dema=20;
float max_dema=3044;
float min_dema=-0;
float max_dema_si=3044;
float min_dema_si=79;


int r_sun=120;
int g_sun=120;
int b_sun=120;
int w_sun=255;

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
  pixels_4.begin();
  pixels_5.begin();
  pixels_6.begin();
  pixels_7.begin();
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
  pixels_19.begin();
  pinMode (encoderPINA_mode, INPUT_PULLUP);
  pinMode (encoderPINB_mode, INPUT_PULLUP);
  pinMode (encoderPINA_month, INPUT_PULLUP);
  pinMode (encoderPINB_month, INPUT_PULLUP);
  pinMode (encoderPINA_hour, INPUT_PULLUP);
  pinMode (encoderPINB_hour, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(encoderPINA_month), turn_month, CHANGE);
  attachInterrupt(digitalPinToInterrupt(encoderPINA_hour), turn_hour, CHANGE);
  attachInterrupt(digitalPinToInterrupt(encoderPINA_mode), turn_mode, CHANGE);
  randomSeed(analogRead(A3));
  mode=random(0,5);
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
  dema();
  show();
  //clear_pix();
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
          pixels_4.setPixelColor(i,120+125*(avgghi_4[a]-min_ghi)/(max_ghi-min_ghi), g_ghi,70*(max_ghi-avgghi_4[a])/(max_ghi-min_ghi),0);
          break;
        case 1:  
          pixels_5.setPixelColor(i,120+125*(avgghi_5[a]-min_ghi)/(max_ghi-min_ghi), g_ghi,70*(max_ghi-avgghi_5[a])/(max_ghi-min_ghi),0);
          break;
        case 2:
        if(i>=4){
          pixels_6.setPixelColor(i-4,120+125*(avgghi_6[a]-min_ghi)/(max_ghi-min_ghi), g_ghi,70*(max_ghi-avgghi_6[a])/(max_ghi-min_ghi),0);
          }
          break;
        case 3:
        if(i>=3){
          pixels_7.setPixelColor(i-3,120+125*(avgghi_7[a]-min_ghi)/(max_ghi-min_ghi), g_ghi,70*(max_ghi-avgghi_7[a])/(max_ghi-min_ghi),0);
          }
          break;
        case 4:
        if(i>=2){
          pixels_8.setPixelColor(i-2,120+125*(avgghi_8[a]-min_ghi)/(max_ghi-min_ghi), g_ghi,70*(max_ghi-avgghi_8[a])/(max_ghi-min_ghi),0);
          }
          break;
        case 5:
          pixels_9.setPixelColor(i,120+125*(avgghi_9[a]-min_ghi)/(max_ghi-min_ghi), g_ghi,70*(max_ghi-avgghi_9[a])/(max_ghi-min_ghi),0);
          break;
        case 6:  
          pixels_10.setPixelColor(i,120+125*(avgghi_10[a]-min_ghi)/(max_ghi-min_ghi), g_ghi,70*(max_ghi-avgghi_10[a])/(max_ghi-min_ghi),0);
          break;
        case 7:  
          pixels_11.setPixelColor(i,120+125*(avgghi_11[a]-min_ghi)/(max_ghi-min_ghi), g_ghi,70*(max_ghi-avgghi_11[a])/(max_ghi-min_ghi),0);
          break;
        case 8:  
          pixels_12.setPixelColor(i,120+125*(avgghi_12[a]-min_ghi)/(max_ghi-min_ghi), g_ghi,70*(max_ghi-avgghi_12[a])/(max_ghi-min_ghi),0);
          break;
        case 9:
          pixels_13.setPixelColor(i,120+125*(avgghi_13[a]-min_ghi)/(max_ghi-min_ghi), g_ghi,70*(max_ghi-avgghi_13[a])/(max_ghi-min_ghi),0);
          break;
        case 10:
          pixels_14.setPixelColor(i,120+125*(avgghi_14[a]-min_ghi)/(max_ghi-min_ghi), g_ghi,70*(max_ghi-avgghi_14[a])/(max_ghi-min_ghi),0);
          break;
        case 11:
          pixels_15.setPixelColor(i,120+125*(avgghi_15[a]-min_ghi)/(max_ghi-min_ghi), g_ghi,70*(max_ghi-avgghi_15[a])/(max_ghi-min_ghi),0);
          break;
        case 12:
          pixels_16.setPixelColor(i,120+125*(avgghi_16[a]-min_ghi)/(max_ghi-min_ghi), g_ghi,70*(max_ghi-avgghi_16[a])/(max_ghi-min_ghi),0);
          break;
        case 13:
        if(i>=1){
          pixels_17.setPixelColor(i-1,120+125*(avgghi_17[a]-min_ghi)/(max_ghi-min_ghi), g_ghi,70*(max_ghi-avgghi_17[a])/(max_ghi-min_ghi),0);
        }
          break;
        case 14:
        if(i>=2){
          pixels_18.setPixelColor(i-2,120+125*(avgghi_18[a]-min_ghi)/(max_ghi-min_ghi), g_ghi,70*(max_ghi-avgghi_18[a])/(max_ghi-min_ghi),0);
        }
          break;
        case 15:
        if(i>=4){
          pixels_19.setPixelColor(i-4,120+125*(avgghi_19[a]-min_ghi)/(max_ghi-min_ghi), g_ghi,70*(max_ghi-avgghi_19[a])/(max_ghi-min_ghi),0);
        }
          break;
        case 16:
          pixels_4.setPixelColor(i,120+125*(avgghi_4[a]-min_ghi)/(max_ghi-min_ghi), g_ghi,70*(max_ghi-avgghi_4[a])/(max_ghi-min_ghi),0);
          pixels_5.setPixelColor(i,120+125*(avgghi_5[a]-min_ghi)/(max_ghi-min_ghi), g_ghi,70*(max_ghi-avgghi_5[a])/(max_ghi-min_ghi),0);
          if(i>=4){
          pixels_6.setPixelColor(i-4,120+125*(avgghi_6[a]-min_ghi)/(max_ghi-min_ghi), g_ghi,70*(max_ghi-avgghi_6[a])/(max_ghi-min_ghi),0);
          }
          if(i>=3){
          pixels_7.setPixelColor(i-3,120+125*(avgghi_7[a]-min_ghi)/(max_ghi-min_ghi), g_ghi,70*(max_ghi-avgghi_7[a])/(max_ghi-min_ghi),0);
          }
          if(i>=2){
          pixels_8.setPixelColor(i-2,120+125*(avgghi_8[a]-min_ghi)/(max_ghi-min_ghi), g_ghi,70*(max_ghi-avgghi_8[a])/(max_ghi-min_ghi),0);
          }
          pixels_9.setPixelColor(i,120+125*(avgghi_9[a]-min_ghi)/(max_ghi-min_ghi), g_ghi,70*(max_ghi-avgghi_9[a])/(max_ghi-min_ghi),0);
          pixels_10.setPixelColor(i,120+125*(avgghi_10[a]-min_ghi)/(max_ghi-min_ghi), g_ghi,70*(max_ghi-avgghi_10[a])/(max_ghi-min_ghi),0);
          pixels_11.setPixelColor(i,120+125*(avgghi_11[a]-min_ghi)/(max_ghi-min_ghi), g_ghi,70*(max_ghi-avgghi_11[a])/(max_ghi-min_ghi),0);
          pixels_12.setPixelColor(i,120+125*(avgghi_12[a]-min_ghi)/(max_ghi-min_ghi), g_ghi,70*(max_ghi-avgghi_12[a])/(max_ghi-min_ghi),0);
          pixels_13.setPixelColor(i,120+125*(avgghi_13[a]-min_ghi)/(max_ghi-min_ghi), g_ghi,70*(max_ghi-avgghi_13[a])/(max_ghi-min_ghi),0);
          pixels_14.setPixelColor(i,120+125*(avgghi_14[a]-min_ghi)/(max_ghi-min_ghi), g_ghi,70*(max_ghi-avgghi_14[a])/(max_ghi-min_ghi),0);
          pixels_15.setPixelColor(i,120+125*(avgghi_15[a]-min_ghi)/(max_ghi-min_ghi), g_ghi,70*(max_ghi-avgghi_15[a])/(max_ghi-min_ghi),0);
          pixels_16.setPixelColor(i,120+125*(avgghi_16[a]-min_ghi)/(max_ghi-min_ghi), g_ghi,70*(max_ghi-avgghi_16[a])/(max_ghi-min_ghi),0);
          if(i>=1){
          pixels_17.setPixelColor(i-1,120+125*(avgghi_17[a]-min_ghi)/(max_ghi-min_ghi), g_ghi,70*(max_ghi-avgghi_17[a])/(max_ghi-min_ghi),0);
          }
          if(i>=2){
          pixels_18.setPixelColor(i-2,120+125*(avgghi_18[a]-min_ghi)/(max_ghi-min_ghi), g_ghi,70*(max_ghi-avgghi_18[a])/(max_ghi-min_ghi),0);
          }
          if(i>=4){
          pixels_19.setPixelColor(i-4,120+125*(avgghi_19[a]-min_ghi)/(max_ghi-min_ghi), g_ghi,70*(max_ghi-avgghi_19[a])/(max_ghi-min_ghi),0);
          }
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
          pixels_4.setPixelColor(i,255*(avgtemp_4[a]-min_temp)/(max_temp-min_temp), g_temp,255*(max_temp-avgtemp_4[a])/(max_temp-min_temp),0);
          break;
        case 1:
          pixels_5.setPixelColor(i,255*(avgtemp_5[a]-min_temp)/(max_temp-min_temp), g_temp,255*(max_temp-avgtemp_5[a])/(max_temp-min_temp),0);
          break;
        case 2:
        if(i>=4){
          pixels_6.setPixelColor(i-4,255*(avgtemp_6[a]-min_temp)/(max_temp-min_temp), g_temp,255*(max_temp-avgtemp_6[a])/(max_temp-min_temp),0);
          break;
        }
        case 3: 
        if(i>=3){ 
          pixels_7.setPixelColor(i-3,255*(avgtemp_7[a]-min_temp)/(max_temp-min_temp), g_temp,255*(max_temp-avgtemp_7[a])/(max_temp-min_temp),0);
          break;
        }
        case 4:
        if(i>=2){
          pixels_8.setPixelColor(i-2,255*(avgtemp_8[a]-min_temp)/(max_temp-min_temp), g_temp,255*(max_temp-avgtemp_8[a])/(max_temp-min_temp),0);
          break;
        }
        case 5:
          pixels_9.setPixelColor(i,255*(avgtemp_9[a]-min_temp)/(max_temp-min_temp), g_temp,255*(max_temp-avgtemp_9[a])/(max_temp-min_temp),0);
          break;
        case 6:
          pixels_10.setPixelColor(i,255*(avgtemp_10[a]-min_temp)/(max_temp-min_temp), g_temp,255*(max_temp-avgtemp_10[a])/(max_temp-min_temp),0);
          break;
        case 7:
          pixels_11.setPixelColor(i,255*(avgtemp_11[a]-min_temp)/(max_temp-min_temp), g_temp,255*(max_temp-avgtemp_11[a])/(max_temp-min_temp),0);
          break;
        case 8:
          pixels_12.setPixelColor(i,255*(avgtemp_12[a]-min_temp)/(max_temp-min_temp), g_temp,255*(max_temp-avgtemp_12[a])/(max_temp-min_temp),0);
          break;
        case 9:
          pixels_13.setPixelColor(i,255*(avgtemp_13[a]-min_temp)/(max_temp-min_temp), g_temp,255*(max_temp-avgtemp_13[a])/(max_temp-min_temp),0);
          break;
        case 10:
          pixels_14.setPixelColor(i,255*(avgtemp_14[a]-min_temp)/(max_temp-min_temp), g_temp,255*(max_temp-avgtemp_14[a])/(max_temp-min_temp),0);
          break;
        case 11:
          pixels_15.setPixelColor(i,255*(avgtemp_15[a]-min_temp)/(max_temp-min_temp), g_temp,255*(max_temp-avgtemp_15[a])/(max_temp-min_temp),0);
          break;
        case 12:  
          pixels_16.setPixelColor(i,255*(avgtemp_16[a]-min_temp)/(max_temp-min_temp), g_temp,255*(max_temp-avgtemp_16[a])/(max_temp-min_temp),0);
          break;
        case 13: 
        if(i>=1){ 
          pixels_17.setPixelColor(i-1,255*(avgtemp_17[a]-min_temp)/(max_temp-min_temp), g_temp,255*(max_temp-avgtemp_17[a])/(max_temp-min_temp),0);
        }
        break;
        case 14: 
        if(i>=2){ 
          pixels_18.setPixelColor(i-2,255*(avgtemp_18[a]-min_temp)/(max_temp-min_temp), g_temp,255*(max_temp-avgtemp_18[a])/(max_temp-min_temp),0);
        }
          break;
        case 15:
        if(i>=4){
          pixels_19.setPixelColor(i-4,255*(avgtemp_19[a]-min_temp)/(max_temp-min_temp), g_temp,255*(max_temp-avgtemp_19[a])/(max_temp-min_temp),0);
          }
          break;
        case 16:
          pixels_4.setPixelColor(i,255*(avgtemp_4[a]-min_temp)/(max_temp-min_temp), g_temp,255*(max_temp-avgtemp_4[a])/(max_temp-min_temp),0);
          pixels_5.setPixelColor(i,255*(avgtemp_5[a]-min_temp)/(max_temp-min_temp), g_temp,255*(max_temp-avgtemp_5[a])/(max_temp-min_temp),0);
          if(i>=4){
          pixels_6.setPixelColor(i-4,255*(avgtemp_6[a]-min_temp)/(max_temp-min_temp), g_temp,255*(max_temp-avgtemp_6[a])/(max_temp-min_temp),0);
          }
          if(i>=3){
          pixels_7.setPixelColor(i-3,255*(avgtemp_7[a]-min_temp)/(max_temp-min_temp), g_temp,255*(max_temp-avgtemp_7[a])/(max_temp-min_temp),0);
          }
          if(i>=2){
          pixels_8.setPixelColor(i-2,255*(avgtemp_8[a]-min_temp)/(max_temp-min_temp), g_temp,255*(max_temp-avgtemp_8[a])/(max_temp-min_temp),0);
          }
          pixels_9.setPixelColor(i,255*(avgtemp_9[a]-min_temp)/(max_temp-min_temp), g_temp,255*(max_temp-avgtemp_9[a])/(max_temp-min_temp),0);
          pixels_10.setPixelColor(i,255*(avgtemp_10[a]-min_temp)/(max_temp-min_temp), g_temp,255*(max_temp-avgtemp_10[a])/(max_temp-min_temp),0);
          pixels_11.setPixelColor(i,255*(avgtemp_11[a]-min_temp)/(max_temp-min_temp), g_temp,255*(max_temp-avgtemp_11[a])/(max_temp-min_temp),0);
          pixels_12.setPixelColor(i,255*(avgtemp_12[a]-min_temp)/(max_temp-min_temp), g_temp,255*(max_temp-avgtemp_12[a])/(max_temp-min_temp),0);
          pixels_13.setPixelColor(i,255*(avgtemp_13[a]-min_temp)/(max_temp-min_temp), g_temp,255*(max_temp-avgtemp_13[a])/(max_temp-min_temp),0);
          pixels_14.setPixelColor(i,255*(avgtemp_14[a]-min_temp)/(max_temp-min_temp), g_temp,255*(max_temp-avgtemp_14[a])/(max_temp-min_temp),0);
          pixels_15.setPixelColor(i,255*(avgtemp_15[a]-min_temp)/(max_temp-min_temp), g_temp,255*(max_temp-avgtemp_15[a])/(max_temp-min_temp),0);
          pixels_16.setPixelColor(i,255*(avgtemp_16[a]-min_temp)/(max_temp-min_temp), g_temp,255*(max_temp-avgtemp_16[a])/(max_temp-min_temp),0);
          if(i>=1){
          pixels_17.setPixelColor(i-1,255*(avgtemp_17[a]-min_temp)/(max_temp-min_temp), g_temp,255*(max_temp-avgtemp_17[a])/(max_temp-min_temp),0);
          }
          if(i>=2){
          pixels_18.setPixelColor(i-2,255*(avgtemp_18[a]-min_temp)/(max_temp-min_temp), g_temp,255*(max_temp-avgtemp_18[a])/(max_temp-min_temp),0);
          }
          if(i>=4){
          pixels_19.setPixelColor(i-4,255*(avgtemp_19[a]-min_temp)/(max_temp-min_temp), g_temp,255*(max_temp-avgtemp_19[a])/(max_temp-min_temp),0);
          }
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
          pixels_4.setPixelColor(i,115+140*(avgdema_4[a]-min_dema)/(max_dema-min_dema), g_dema,180*(max_dema-avgdema_4[a])/(max_dema-min_dema),0);
          break;
        case 1:
          pixels_5.setPixelColor(i,115+140*(avgdema_5[a]-min_dema)/(max_dema-min_dema), g_dema,180*(max_dema-avgdema_5[a])/(max_dema-min_dema),0);
          break;
        case 2:
        if(i>=4){
          pixels_6.setPixelColor(i-4,115+140*(avgdema_6[a]-min_dema)/(max_dema-min_dema), g_dema,180*(max_dema-avgdema_6[a])/(max_dema-min_dema),0);
        }
          break;
        case 3: 
        if(i>=3){ 
          pixels_7.setPixelColor(i-3,115+140*(avgdema_7[a]-min_dema)/(max_dema-min_dema), g_dema,180*(max_dema-avgdema_7[a])/(max_dema-min_dema),0);
        }
          break;
        case 4:
        if(i>=2){
          pixels_8.setPixelColor(i-2,115+140*(avgdema_8[a]-min_dema)/(max_dema-min_dema), g_dema,180*(max_dema-avgdema_8[a])/(max_dema-min_dema),0);
        }
          break;
        case 5:
          pixels_9.setPixelColor(i,115+140*(avgdema_9[a]-min_dema)/(max_dema-min_dema), g_dema,180*(max_dema-avgdema_9[a])/(max_dema-min_dema),0);
          break;
        case 6:
          pixels_10.setPixelColor(i,115+140*(avgdema_10[a]-min_dema)/(max_dema-min_dema), g_dema,180*(max_dema-avgdema_10[a])/(max_dema-min_dema),0);
          break;
        case 7:
          pixels_11.setPixelColor(i,115+140*(avgdema_11[a]-min_dema)/(max_dema-min_dema), g_dema,180*(max_dema-avgdema_11[a])/(max_dema-min_dema),0);
          break;
        case 8:
          pixels_12.setPixelColor(i,115+140*(avgdema_12[a]-min_dema)/(max_dema-min_dema), g_dema,180*(max_dema-avgdema_12[a])/(max_dema-min_dema),0);
          break;
        case 9:
          pixels_13.setPixelColor(i,115+140*(avgdema_13[a]-min_dema)/(max_dema-min_dema), g_dema,180*(max_dema-avgdema_13[a])/(max_dema-min_dema),0);
          break;
        case 10:
          pixels_14.setPixelColor(i,115+140*(avgdema_14[a]-min_dema)/(max_dema-min_dema), g_dema,180*(max_dema-avgdema_14[a])/(max_dema-min_dema),0);
          break;
        case 11:
          pixels_15.setPixelColor(i,115+140*(avgdema_15[a]-min_dema)/(max_dema-min_dema), g_dema,180*(max_dema-avgdema_15[a])/(max_dema-min_dema),0);
          break;
        case 12:  
          pixels_16.setPixelColor(i,115+140*(avgdema_16[a]-min_dema)/(max_dema-min_dema), g_dema,180*(max_dema-avgdema_16[a])/(max_dema-min_dema),0);
          break;
        case 13: 
        if(i>=1){ 
          pixels_17.setPixelColor(i-1,115+140*(avgdema_17[a]-min_dema)/(max_dema-min_dema), g_dema,180*(max_dema-avgdema_17[a])/(max_dema-min_dema),0);
        }
        break;
        case 14:  
        if(i>=2){
          pixels_18.setPixelColor(i-2,115+140*(avgdema_18[a]-min_dema)/(max_dema-min_dema), g_dema,180*(max_dema-avgdema_18[a])/(max_dema-min_dema),0);
        }
        break;
        case 15:
        if(i>=4){
          pixels_19.setPixelColor(i-4,115+140*(avgdema_19[a]-min_dema)/(max_dema-min_dema), g_dema,180*(max_dema-avgdema_19[a])/(max_dema-min_dema),0);
        }
        break;
        case 16:
          pixels_4.setPixelColor(i,115+140*(avgdema_4[a]-min_dema)/(max_dema-min_dema), g_dema,180*(max_dema-avgdema_4[a])/(max_dema-min_dema),0);
          pixels_5.setPixelColor(i,115+140*(avgdema_5[a]-min_dema)/(max_dema-min_dema), g_dema,180*(max_dema-avgdema_5[a])/(max_dema-min_dema),0);
          if(i>=4){
          pixels_6.setPixelColor(i-4,115+140*(avgdema_6[a]-min_dema)/(max_dema-min_dema), g_dema,180*(max_dema-avgdema_6[a])/(max_dema-min_dema),0);
          }
          if(i>=3){
          pixels_7.setPixelColor(i-3,115+140*(avgdema_7[a]-min_dema)/(max_dema-min_dema), g_dema,180*(max_dema-avgdema_7[a])/(max_dema-min_dema),0);
          }
          if(i>=2){
          pixels_8.setPixelColor(i-2,115+140*(avgdema_8[a]-min_dema)/(max_dema-min_dema), g_dema,180*(max_dema-avgdema_8[a])/(max_dema-min_dema),0);
          }
          pixels_9.setPixelColor(i,115+140*(avgdema_9[a]-min_dema)/(max_dema-min_dema), g_dema,180*(max_dema-avgdema_9[a])/(max_dema-min_dema),0);
          pixels_10.setPixelColor(i,115+140*(avgdema_10[a]-min_dema)/(max_dema-min_dema), g_dema,180*(max_dema-avgdema_10[a])/(max_dema-min_dema),0);
          pixels_11.setPixelColor(i,115+140*(avgdema_11[a]-min_dema)/(max_dema-min_dema), g_dema,180*(max_dema-avgdema_11[a])/(max_dema-min_dema),0);
          pixels_12.setPixelColor(i,115+140*(avgdema_12[a]-min_dema)/(max_dema-min_dema), g_dema,180*(max_dema-avgdema_12[a])/(max_dema-min_dema),0);
          pixels_13.setPixelColor(i,115+140*(avgdema_13[a]-min_dema)/(max_dema-min_dema), g_dema,180*(max_dema-avgdema_13[a])/(max_dema-min_dema),0);
          pixels_14.setPixelColor(i,115+140*(avgdema_14[a]-min_dema)/(max_dema-min_dema), g_dema,180*(max_dema-avgdema_14[a])/(max_dema-min_dema),0);
          pixels_15.setPixelColor(i,115+140*(avgdema_15[a]-min_dema)/(max_dema-min_dema), g_dema,180*(max_dema-avgdema_15[a])/(max_dema-min_dema),0);
          pixels_16.setPixelColor(i,115+140*(avgdema_16[a]-min_dema)/(max_dema-min_dema), g_dema,180*(max_dema-avgdema_16[a])/(max_dema-min_dema),0);
          if(i>=1){
          pixels_17.setPixelColor(i-1,115+140*(avgdema_17[a]-min_dema)/(max_dema-min_dema), g_dema,180*(max_dema-avgdema_17[a])/(max_dema-min_dema),0);
          }
          if(i>=2){
          pixels_18.setPixelColor(i-2,115+140*(avgdema_18[a]-min_dema)/(max_dema-min_dema), g_dema,180*(max_dema-avgdema_18[a])/(max_dema-min_dema),0);
          }
          if(i>=4){
          pixels_19.setPixelColor(i-4,115+140*(avgdema_19[a]-min_dema)/(max_dema-min_dema), g_dema,180*(max_dema-avgdema_19[a])/(max_dema-min_dema),0);
          }
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
          pixels_4.setPixelColor(i,255*(avggrid_4[a]-min_grid)/(max_grid-min_grid), 255*(max_grid-avggrid_4[a])/(max_grid-min_grid),b_grid,0);
          break;
        case 1:  
          pixels_5.setPixelColor(i,255*(avggrid_5[a]-min_grid)/(max_grid-min_grid), 255*(max_grid-avggrid_5[a])/(max_grid-min_grid),b_grid,0);
          break;
        case 2: 
        if(i>=4){
          pixels_6.setPixelColor(i-4,255*(avggrid_6[a]-min_grid)/(max_grid-min_grid), 255*(max_grid-avggrid_6[a])/(max_grid-min_grid),b_grid,0);
        }
        break;
        case 3: 
        if(i>=3){ 
          pixels_7.setPixelColor(i-3,255*(avggrid_7[a]-min_grid)/(max_grid-min_grid), 255*(max_grid-avggrid_7[a])/(max_grid-min_grid),b_grid,0);
        }
        break;
        case 4:  
        if(i>=2){
          pixels_8.setPixelColor(i-2,255*(avggrid_8[a]-min_grid)/(max_grid-min_grid), 255*(max_grid-avggrid_8[a])/(max_grid-min_grid),b_grid,0);
        }
        break;
        case 5:  
          pixels_9.setPixelColor(i,255*(avggrid_9[a]-min_grid)/(max_grid-min_grid), 255*(max_grid-avggrid_9[a])/(max_grid-min_grid),b_grid,0);
          break;
        case 6:  
          pixels_10.setPixelColor(i,255*(avggrid_10[a]-min_grid)/(max_grid-min_grid), 255*(max_grid-avggrid_10[a])/(max_grid-min_grid),b_grid,0);
          break;
        case 7:  
          pixels_11.setPixelColor(i,255*(avggrid_11[a]-min_grid)/(max_grid-min_grid), 255*(max_grid-avggrid_11[a])/(max_grid-min_grid),b_grid,0);
          break;
        case 8:  
          pixels_12.setPixelColor(i,255*(avggrid_12[a]-min_grid)/(max_grid-min_grid), 255*(max_grid-avggrid_12[a])/(max_grid-min_grid),b_grid,0);
          break;
        case 9:  
          pixels_13.setPixelColor(i,255*(avggrid_13[a]-min_grid)/(max_grid-min_grid), 255*(max_grid-avggrid_13[a])/(max_grid-min_grid),b_grid,0);
          break;
        case 10:  
          pixels_14.setPixelColor(i,255*(avggrid_14[a]-min_grid)/(max_grid-min_grid), 255*(max_grid-avggrid_14[a])/(max_grid-min_grid),b_grid,0);
          break;
        case 11:  
          pixels_15.setPixelColor(i,255*(avggrid_15[a]-min_grid)/(max_grid-min_grid), 255*(max_grid-avggrid_15[a])/(max_grid-min_grid),b_grid,0);
          break;
        case 12:  
          pixels_16.setPixelColor(i,255*(avggrid_16[a]-min_grid)/(max_grid-min_grid), 255*(max_grid-avggrid_16[a])/(max_grid-min_grid),b_grid,0);
          break;
        case 13:  
        if(i>=1){
          pixels_17.setPixelColor(i-1,255*(avggrid_17[a]-min_grid)/(max_grid-min_grid), 255*(max_grid-avggrid_17[a])/(max_grid-min_grid),b_grid,0);
        }
        break;
        case 14:  
        if(i>=2){
          pixels_18.setPixelColor(i-2,255*(avggrid_18[a]-min_grid)/(max_grid-min_grid), 255*(max_grid-avggrid_18[a])/(max_grid-min_grid),b_grid,0);
        }
        break;
        case 15:  
        if(i>=4){
          pixels_19.setPixelColor(i-4,255*(avggrid_19[a]-min_grid)/(max_grid-min_grid), 255*(max_grid-avggrid_19[a])/(max_grid-min_grid),b_grid,0);
        }
        break;
        case 16:
          pixels_4.setPixelColor(i,255*(avggrid_4[a]-min_grid)/(max_grid-min_grid), 255*(max_grid-avggrid_4[a])/(max_grid-min_grid),b_grid,0);
          pixels_5.setPixelColor(i,255*(avggrid_5[a]-min_grid)/(max_grid-min_grid), 255*(max_grid-avggrid_5[a])/(max_grid-min_grid),b_grid,0);
          if(i>=4){
          pixels_6.setPixelColor(i-4,255*(avggrid_6[a]-min_grid)/(max_grid-min_grid), 255*(max_grid-avggrid_6[a])/(max_grid-min_grid),b_grid,0);
          }
          if(i>=3){
          pixels_7.setPixelColor(i-3,255*(avggrid_7[a]-min_grid)/(max_grid-min_grid), 255*(max_grid-avggrid_7[a])/(max_grid-min_grid),b_grid,0);
          }
          if(i>=2){
          pixels_8.setPixelColor(i-2,255*(avggrid_8[a]-min_grid)/(max_grid-min_grid), 255*(max_grid-avggrid_8[a])/(max_grid-min_grid),b_grid,0);
          }
          pixels_9.setPixelColor(i,255*(avggrid_9[a]-min_grid)/(max_grid-min_grid), 255*(max_grid-avggrid_9[a])/(max_grid-min_grid),b_grid,0);
          pixels_10.setPixelColor(i,255*(avggrid_10[a]-min_grid)/(max_grid-min_grid), 255*(max_grid-avggrid_10[a])/(max_grid-min_grid),b_grid,0);
          pixels_11.setPixelColor(i,255*(avggrid_11[a]-min_grid)/(max_grid-min_grid), 255*(max_grid-avggrid_11[a])/(max_grid-min_grid),b_grid,0);
          pixels_12.setPixelColor(i,255*(avggrid_12[a]-min_grid)/(max_grid-min_grid), 255*(max_grid-avggrid_12[a])/(max_grid-min_grid),b_grid,0);
          pixels_13.setPixelColor(i,255*(avggrid_13[a]-min_grid)/(max_grid-min_grid), 255*(max_grid-avggrid_13[a])/(max_grid-min_grid),b_grid,0);
          pixels_14.setPixelColor(i,255*(avggrid_14[a]-min_grid)/(max_grid-min_grid), 255*(max_grid-avggrid_14[a])/(max_grid-min_grid),b_grid,0);
          pixels_15.setPixelColor(i,255*(avggrid_15[a]-min_grid)/(max_grid-min_grid), 255*(max_grid-avggrid_15[a])/(max_grid-min_grid),b_grid,0);
          pixels_16.setPixelColor(i,255*(avggrid_16[a]-min_grid)/(max_grid-min_grid), 255*(max_grid-avggrid_16[a])/(max_grid-min_grid),b_grid,0);
          if(i>=1){
          pixels_17.setPixelColor(i-1,255*(avggrid_17[a]-min_grid)/(max_grid-min_grid), 255*(max_grid-avggrid_17[a])/(max_grid-min_grid),b_grid,0);
          }
          if(i>=2){
          pixels_18.setPixelColor(i-2,255*(avggrid_18[a]-min_grid)/(max_grid-min_grid), 255*(max_grid-avggrid_18[a])/(max_grid-min_grid),b_grid,0);
          }
          if(i>=4){
          pixels_19.setPixelColor(i-4,255*(avggrid_19[a]-min_grid)/(max_grid-min_grid), 255*(max_grid-avggrid_19[a])/(max_grid-min_grid),b_grid,0);
          }
          break;
     
     
        }

    }
  }
  void sunpos(){
    for (int i = lower_b; i < upper_b; i++) {
      switch (hour) {
        case 0:
          pixels_4.setPixelColor(i,r_sun,g_sun,b_sun,w_sun);
          break;
        case 1:  
          pixels_5.setPixelColor(i,r_sun,g_sun,b_sun,w_sun);
          break;
        case 2:  
        if(i>=4){
          pixels_6.setPixelColor(i-4,r_sun,g_sun,b_sun,w_sun);
        }
          break;
        case 3:  
        if(i>=3){
          pixels_7.setPixelColor(i-3,r_sun,g_sun,b_sun,w_sun);
        }
          break;
        case 4:  
        if(i>=2){
          pixels_8.setPixelColor(i-2,r_sun,g_sun,b_sun,w_sun);
        }
          break;
        case 5:  
          pixels_9.setPixelColor(i,r_sun,g_sun,b_sun,w_sun);
          break;
        case 6:  
          pixels_10.setPixelColor(i,r_sun,g_sun,b_sun,w_sun);
          break;
        case 7:
          pixels_11.setPixelColor(i,r_sun,g_sun,b_sun,w_sun);
          break;
        case 8:
          pixels_12.setPixelColor(i,r_sun,g_sun,b_sun,w_sun);
          break;
        case 9:
          pixels_13.setPixelColor(i,r_sun,g_sun,b_sun,w_sun);
          break;
        case 10:
          pixels_14.setPixelColor(i,r_sun,g_sun,b_sun,w_sun);
          break;
        case 11:
          pixels_15.setPixelColor(i,r_sun,g_sun,b_sun,w_sun);
          break;
        case 12:
          pixels_16.setPixelColor(i,r_sun,g_sun,b_sun,w_sun);
          break;
        case 13:
        if(i>=1){
          pixels_17.setPixelColor(i-1,r_sun,g_sun,b_sun,w_sun);
        }
          break;
        case 14:
        if(i>=2){
          pixels_18.setPixelColor(i-2,r_sun,g_sun,b_sun,w_sun);
        }
          break;
        case 15:
        if(i>=4){
          pixels_19.setPixelColor(i-4,r_sun,g_sun,b_sun,w_sun);
        }
          break;
        case 16:

          pixels_4.setPixelColor(i,r_sun,g_sun,b_sun,w_sun);
          pixels_5.setPixelColor(i,r_sun,g_sun,b_sun,w_sun);
          if(i>=4){
          pixels_6.setPixelColor(i-4,r_sun,g_sun,b_sun,w_sun);
          }
          if(i>=3){
          pixels_7.setPixelColor(i-3,r_sun,g_sun,b_sun,w_sun);
          }
          if(i>=2){
          pixels_8.setPixelColor(i-2,r_sun,g_sun,b_sun,w_sun);
          }
          pixels_9.setPixelColor(i,r_sun,g_sun,b_sun,w_sun);
          pixels_10.setPixelColor(i,r_sun,g_sun,b_sun,w_sun);
          pixels_11.setPixelColor(i,r_sun,g_sun,b_sun,w_sun);
          pixels_12.setPixelColor(i,r_sun,g_sun,b_sun,w_sun);
          pixels_13.setPixelColor(i,r_sun,g_sun,b_sun,w_sun);
          pixels_14.setPixelColor(i,r_sun,g_sun,b_sun,w_sun);
          pixels_15.setPixelColor(i,r_sun,g_sun,b_sun,w_sun);
          pixels_16.setPixelColor(i,r_sun,g_sun,b_sun,w_sun);
          if(i>=1){
          pixels_17.setPixelColor(i-1,r_sun,g_sun,b_sun,w_sun);
          }
          if(i>=2){
          pixels_18.setPixelColor(i-2,r_sun,g_sun,b_sun,w_sun);
          }
          if(i>=4){
          pixels_19.setPixelColor(i-4,r_sun,g_sun,b_sun,w_sun);
          }
          break;
      }
     

     
     

    }
  }

  void show(){
    pixels_4.show();
    pixels_5.show();
    pixels_6.show();
    pixels_7.show();
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
    pixels_19.show(); 
  }

void clear_pix(){
    pixels_4.clear();
    pixels_5.clear();
    pixels_6.clear();
    pixels_7.clear();  
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
    pixels_19.clear();
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
      if (encoderPos_hour<16) {
        encoderPos_hour++;
      } else {
      encoderPos_hour=2;
      }
    } else {
      if(encoderPos_hour>0){
        encoderPos_hour--;
      } else if (encoderPos_hour<=2) {
        encoderPos_hour=16;
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
          lcd.print("Hour: 04:00");
          break;
        case 1: 
          lcd.print("Hour: 05:00"); 
          break;
        case 2:
          lcd.print("Hour: 06:00");
          break;
        case 3:
          lcd.print("Hour: 07:00");
          break;
        case 4:
          lcd.print("Hour: 08:00");
          break;
        case 5:
          lcd.print("Hour: 09:00");
          break;
        case 6: 
          lcd.print("Hour: 10:00"); 
          break;
        case 7:  
          lcd.print("Hour: 11:00");
          break;
        case 8:
          lcd.print("Hour: 12:00");  
          break;
        case 9:
          lcd.print("Hour: 13:00");
          break;
        case 10:
          lcd.print("Hour: 14:00");
          break;
        case 11:
          lcd.print("Hour: 15:00");
          break;
        case 12:
          lcd.print("Hour: 16:00");
          break;
        case 13:
          lcd.print("Hour: 17:00");
          break;
        case 14:
          lcd.print("Hour: 18:00");
          break;
        case 15:
          lcd.print("Hour: 19:00");
          break;
        case 16:
          lcd.print("Hour: ALL");
          break;
   }
   print_min_max();
}

void print_min_max(){
  clearLCDLine(3);
  lcd.setCursor(1,3);
  if(month==12 && hour==16){
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
  }else if(month<12 && hour<16){
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
          lcd.print("Temp: "+String(round(avgtemp_4[aa])));
          break;
        case 1:  
          lcd.print("Temp: "+String(round(avgtemp_5[aa])));
          break;
        case 2: 
          lcd.print("Temp: "+String(round(avgtemp_6[aa])));
          break;
        case 3: 
          lcd.print("Temp: "+String(round(avgtemp_7[aa]))); 
          break;
        case 4: 
          lcd.print("Temp: "+String(round(avgtemp_8[aa]))); 
          break;
        case 5:  
          lcd.print("Temp: "+String(round(avgtemp_9[aa]))); 
          break;
        case 6: 
          lcd.print("Temp: "+String(round(avgtemp_10[aa])));  
          break;
        case 7: 
          lcd.print("Temp: "+String(round(avgtemp_11[aa])));  
          break;
        case 8: 
          lcd.print("Temp: "+String(round(avgtemp_12[aa])));  
          break;
        case 9: 
          lcd.print("Temp: "+String(round(avgtemp_13[aa])));  
          break;
        case 10: 
          lcd.print("Temp: "+String(round(avgtemp_14[aa])));  
          break;
        case 11: 
          lcd.print("Temp: "+String(round(avgtemp_15[aa])));  
          break;
        case 12: 
          lcd.print("Temp: "+String(round(avgtemp_16[aa])));  
          break;
        case 13: 
          lcd.print("Temp: "+String(round(avgtemp_17[aa])));  
          break;
        case 14:
          lcd.print("Temp: "+String(round(avgtemp_18[aa])));   
          break;
        case 15:
          lcd.print("Temp: "+String(round(avgtemp_19[aa])));   
          break;
        }
        break;
      case 1:
        switch (hour) {
        case 0:
          lcd.print("Emis: "+String(round(avggrid_4[aa]))+unit_grid);
          break;
        case 1:  
          lcd.print("Emis: "+String(round(avggrid_5[aa]))+unit_grid);
          break;
        case 2: 
          lcd.print("Emis: "+String(round(avggrid_6[aa]))+unit_grid);
          break;
        case 3: 
          lcd.print("Emis: "+String(round(avggrid_7[aa]))+unit_grid); 
          break;
        case 4: 
          lcd.print("Emis: "+String(round(avggrid_8[aa]))+unit_grid); 
          break;
        case 5:  
          lcd.print("Emis: "+String(round(avggrid_9[aa]))+unit_grid); 
          break;
        case 6: 
          lcd.print("Emis: "+String(round(avggrid_10[aa]))+unit_grid);  
          break;
        case 7: 
          lcd.print("Emis: "+String(round(avggrid_11[aa]))+unit_grid);  
          break;
        case 8: 
          lcd.print("Emis: "+String(round(avggrid_12[aa]))+unit_grid);  
          break;
        case 9: 
          lcd.print("Emis: "+String(round(avggrid_13[aa]))+unit_grid);  
          break;
        case 10: 
          lcd.print("Emis: "+String(round(avggrid_14[aa]))+unit_grid);  
          break;
        case 11: 
          lcd.print("Emis: "+String(round(avggrid_15[aa]))+unit_grid);  
          break;
        case 12: 
          lcd.print("Emis: "+String(round(avggrid_16[aa]))+unit_grid);  
          break;
        case 13: 
          lcd.print("Emis: "+String(round(avggrid_17[aa]))+unit_grid);  
          break;
        case 14:
          lcd.print("Emis: "+String(round(avggrid_18[aa]))+unit_grid);   
          break;
        case 15:
          lcd.print("Emis: "+String(round(avggrid_19[aa]))+unit_grid);   
          break;
        }
        break;
      case 2:
        switch (hour) {
        case 0:
          lcd.print("Irrad: "+String(round(avgghi_4[aa]))+unit_ghi);
          break;
        case 1:  
          lcd.print("Irrad: "+String(round(avgghi_5[aa]))+unit_ghi);
          break;
        case 2: 
          lcd.print("Irrad: "+String(round(avgghi_6[aa]))+unit_ghi);
          break;
        case 3: 
          lcd.print("Irrad: "+String(round(avgghi_7[aa]))+unit_ghi); 
          break;
        case 4: 
          lcd.print("Irrad: "+String(round(avgghi_8[aa]))+unit_ghi); 
          break;
        case 5:  
          lcd.print("Irrad: "+String(round(avgghi_9[aa]))+unit_ghi); 
          break;
        case 6: 
          lcd.print("Irrad: "+String(round(avgghi_10[aa]))+unit_ghi);  
          break;
        case 7: 
          lcd.print("Irrad: "+String(round(avgghi_11[aa]))+unit_ghi);  
          break;
        case 8: 
          lcd.print("Irrad: "+String(round(avgghi_12[aa]))+unit_ghi);  
          break;
        case 9: 
          lcd.print("Irrad: "+String(round(avgghi_13[aa]))+unit_ghi);  
          break;
        case 10: 
          lcd.print("Irrad: "+String(round(avgghi_14[aa]))+unit_ghi);  
          break;
        case 11: 
          lcd.print("Irrad: "+String(round(avgghi_15[aa]))+unit_ghi);  
          break;
        case 12: 
          lcd.print("Irrad: "+String(round(avgghi_16[aa]))+unit_ghi);  
          break;
        case 13: 
          lcd.print("Irrad: "+String(round(avgghi_17[aa]))+unit_ghi);  
          break;
        case 14:
          lcd.print("Irrad: "+String(round(avgghi_18[aa]))+unit_ghi);   
          break;
        case 15:
          lcd.print("Irrad: "+String(round(avgghi_19[aa]))+unit_ghi);   
          break;
        }
        break;

      case 3:
      switch (hour) {
        case 0:
          lcd.print("Demand: "+String(round(avgdema_4[aa]))+unit_dema);
          break;
        case 1:  
          lcd.print("Demand: "+String(round(avgdema_5[aa]))+unit_dema);
          break;
        case 2: 
          lcd.print("Demand: "+String(round(avgdema_6[aa]))+unit_dema);
          break;
        case 3: 
          lcd.print("Demand: "+String(round(avgdema_7[aa]))+unit_dema); 
          break;
        case 4: 
          lcd.print("Demand: "+String(round(avgdema_8[aa]))+unit_dema); 
          break;
        case 5:  
          lcd.print("Demand: "+String(round(avgdema_9[aa]))+unit_dema); 
          break;
        case 6: 
          lcd.print("Demand: "+String(round(avgdema_10[aa]))+unit_dema);  
          break;
        case 7: 
          lcd.print("Demand: "+String(round(avgdema_11[aa]))+unit_dema);  
          break;
        case 8: 
          lcd.print("Demand: "+String(round(avgdema_12[aa]))+unit_dema);  
          break;
        case 9: 
          lcd.print("Demand: "+String(round(avgdema_13[aa]))+unit_dema);  
          break;
        case 10: 
          lcd.print("Demand: "+String(round(avgdema_14[aa]))+unit_dema);  
          break;
        case 11: 
          lcd.print("Demand: "+String(round(avgdema_15[aa]))+unit_dema);  
          break;
        case 12: 
          lcd.print("Demand: "+String(round(avgdema_16[aa]))+unit_dema);  
          break;
        case 13: 
          lcd.print("Demand: "+String(round(avgdema_17[aa]))+unit_dema);  
          break;
        case 14:
          lcd.print("Demand: "+String(round(avgdema_18[aa]))+unit_dema);   
          break;
        case 15:
          lcd.print("Demand: "+String(round(avgdema_19[aa]))+unit_dema);   
          break;
        }
        break;
      case 4:
        break;
  }
  }else if(month<12 && hour==16){
    if(month==0){
        aa=11;
      }else{
        aa=month-1;
      }
    switch (mode) {
      case 0:
        temp_array[0]=avgtemp_4[aa];
        temp_array[1]=avgtemp_5[aa];
        temp_array[2]=avgtemp_6[aa];
        temp_array[3]=avgtemp_7[aa];
        temp_array[4]=avgtemp_8[aa];
        temp_array[5]=avgtemp_9[aa];
        temp_array[6]=avgtemp_10[aa];
        temp_array[7]=avgtemp_11[aa];
        temp_array[8]=avgtemp_12[aa];
        temp_array[9]=avgtemp_13[aa];
        temp_array[10]=avgtemp_14[aa];
        temp_array[11]=avgtemp_15[aa];
        temp_array[12]=avgtemp_16[aa];
        temp_array[13]=avgtemp_17[aa];
        temp_array[14]=avgtemp_18[aa];
        temp_array[15]=avgtemp_19[aa];
        break;
      case 1:
        temp_array[0]=avggrid_4[aa];
        temp_array[1]=avggrid_5[aa];
        temp_array[2]=avggrid_6[aa];
        temp_array[3]=avggrid_7[aa];
        temp_array[4]=avggrid_8[aa];
        temp_array[5]=avggrid_9[aa];
        temp_array[6]=avggrid_10[aa];
        temp_array[7]=avggrid_11[aa];
        temp_array[8]=avggrid_12[aa];
        temp_array[9]=avggrid_13[aa];
        temp_array[10]=avggrid_14[aa];
        temp_array[11]=avggrid_15[aa];
        temp_array[12]=avggrid_16[aa];
        temp_array[13]=avggrid_17[aa];
        temp_array[14]=avggrid_18[aa];
        temp_array[15]=avggrid_19[aa];
        break;
      case 2:
        temp_array[0]=avgghi_4[aa];
        temp_array[1]=avgghi_5[aa];
        temp_array[2]=avgghi_6[aa];
        temp_array[3]=avgghi_7[aa];
        temp_array[4]=avgghi_8[aa];
        temp_array[5]=avgghi_9[aa];
        temp_array[6]=avgghi_10[aa];
        temp_array[7]=avgghi_11[aa];
        temp_array[8]=avgghi_12[aa];
        temp_array[9]=avgghi_13[aa];
        temp_array[10]=avgghi_14[aa];
        temp_array[11]=avgghi_15[aa];
        temp_array[12]=avgghi_16[aa];
        temp_array[13]=avgghi_17[aa];
        temp_array[14]=avgghi_18[aa];
        temp_array[15]=avgghi_19[aa];
        break;
      case 3:
        temp_array[0]=avgdema_4[aa];
        temp_array[1]=avgdema_5[aa];
        temp_array[2]=avgdema_6[aa];
        temp_array[3]=avgdema_7[aa];
        temp_array[4]=avgdema_8[aa];
        temp_array[5]=avgdema_9[aa];
        temp_array[6]=avgdema_10[aa];
        temp_array[7]=avgdema_11[aa];
        temp_array[8]=avgdema_12[aa];
        temp_array[9]=avgdema_13[aa];
        temp_array[10]=avgdema_14[aa];
        temp_array[11]=avgdema_15[aa];
        temp_array[12]=avgdema_16[aa];
        temp_array[13]=avgdema_17[aa];
        temp_array[14]=avgdema_18[aa];
        temp_array[15]=avgdema_19[aa];
        break;
      case 4:
        break;
    }
    min_max(temp_array);
    lcd.print("MIN:"+String(round(minValue)));
    lcd.setCursor(12, 3);
    lcd.print("MAX:"+String(round(maxValue)));

  }else if(month==12 && hour<16){
    lcd.setCursor(1,3);
      switch (mode) {
      case 0:
        switch (hour) {
        case 0:
          min_max(avgtemp_4);
          break;
        case 1:  
          min_max(avgtemp_5);
          break;
        case 2: 
          min_max(avgtemp_6);
          break;
        case 3: 
          min_max(avgtemp_7);
          break;
        case 4: 
          min_max(avgtemp_8);
          break;
        case 5:  
          min_max(avgtemp_9);
          break;
        case 6: 
          min_max(avgtemp_10);
          break;
        case 7: 
          min_max(avgtemp_11);
          break;
        case 8: 
          min_max(avgtemp_12);
          break;
        case 9: 
          min_max(avgtemp_13);
          break;
        case 10: 
          min_max(avgtemp_14);
          break;
        case 11: 
          min_max(avgtemp_15);
          break;
        case 12: 
          min_max(avgtemp_16);
          break;
        case 13: 
          min_max(avgtemp_17);
          break;
        case 14:
          min_max(avgtemp_18);
          break;
        case 15:
          min_max(avgtemp_19);
          break;
        }
        lcd.print("MIN:"+String(round(minValue)));
        lcd.setCursor(12, 3);
        lcd.print("MAX:"+String(round(maxValue)));
        break;
      case 1:
        switch (hour) {
        case 0:
          min_max(avggrid_4);
          break;
        case 1:  
          min_max(avggrid_5);
          break;
        case 2: 
          min_max(avggrid_6);
          break;
        case 3: 
          min_max(avggrid_7);
          break;
        case 4: 
          min_max(avggrid_8);
          break;
        case 5:  
          min_max(avggrid_9);
          break;
        case 6: 
          min_max(avggrid_10);
          break;
        case 7: 
          min_max(avggrid_11);
          break;
        case 8: 
          min_max(avggrid_12);
          break;
        case 9: 
          min_max(avggrid_13);
          break;
        case 10: 
          min_max(avggrid_14);
          break;
        case 11: 
          min_max(avggrid_15);
          break;
        case 12: 
          min_max(avggrid_16);
          break;
        case 13: 
          min_max(avggrid_17);
          break;
        case 14:
          min_max(avggrid_18);
          break;
        case 15:
          min_max(avggrid_19);
          break;
        }
        lcd.print("MIN:"+String(round(minValue)));
        lcd.setCursor(12, 3);
        lcd.print("MAX:"+String(round(maxValue)));
        break;
      case 2:
        switch (hour) {
        case 0:
          min_max(avgghi_4);
          break;
        case 1:  
          min_max(avgghi_5);
          break;
        case 2: 
          min_max(avgghi_6);
          break;
        case 3: 
          min_max(avgghi_7);
          break;
        case 4: 
          min_max(avgghi_8);
          break;
        case 5:  
          min_max(avgghi_9);
          break;
        case 6: 
          min_max(avgghi_10);
          break;
        case 7: 
          min_max(avgghi_11);
          break;
        case 8: 
          min_max(avgghi_12);
          break;
        case 9: 
          min_max(avgghi_13);
          break;
        case 10: 
          min_max(avgghi_14);
          break;
        case 11: 
          min_max(avgghi_15);
          break;
        case 12: 
          min_max(avgghi_16);
          break;
        case 13: 
          min_max(avgghi_17);
          break;
        case 14:
          min_max(avgghi_18);
          break;
        case 15:
          min_max(avgghi_19);
          break;
        }
        lcd.print("MIN:"+String(round(minValue)));
        lcd.setCursor(12, 3);
        lcd.print("MAX:"+String(round(maxValue)));
        break;
      case 3:
      switch (hour) {
        case 0:
          min_max(avgdema_4);
          break;
        case 1:  
          min_max(avgdema_5);
          break;
        case 2: 
          min_max(avgdema_6);
          break;
        case 3: 
          min_max(avgdema_7);
          break;
        case 4: 
          min_max(avgdema_8);
          break;
        case 5:  
          min_max(avgdema_9);
          break;
        case 6: 
          min_max(avgdema_10);
          break;
        case 7: 
          min_max(avgdema_11);
          break;
        case 8: 
          min_max(avgdema_12);
          break;
        case 9: 
          min_max(avgdema_13);
          break;
        case 10: 
          min_max(avgdema_14);
          break;
        case 11: 
          min_max(avgdema_15);
          break;
        case 12: 
          min_max(avgdema_16);
          break;
        case 13: 
          min_max(avgdema_17);
          break;
        case 14:
          min_max(avgdema_18);
          break;
        case 15:
          min_max(avgdema_19);
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


 
