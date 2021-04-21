//NASTAVENIA ZARIADENI
#include <LiquidCrystal.h>
#include <Stepper.h>
#include <Wire.h>
#include "RTClib.h"

RTC_DS1307 rtc;
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
const int stepsPerRevolution = 2048;
Stepper stepper = Stepper(stepsPerRevolution, 9, 7, 8, 6);

//Znak celeho vykresleneho pola
byte Thicc[] = {
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111
};
//PREMENNE
//premenne do programu
int pressDelay = 150;
int lcdDelay = 150;
//casove premenne
int seconds = 0;
int minutes = 0;
int hours = 0;
int days = 1;
int months = 1;
int years = 2020;
int DOTW[7] = {0,0,0,0,0,0,0};
int yearNow = 0;
int monthNow = 0;
int weekNow = 0;
int dayNow = 0;
int hoursNow = 0;
int minutesNow = 0;
int timeHappened = 0;
//sypacie premenne
int sypPerDay = 0;
int rotations = 0;
int feeding = 0;
int foodSize = 50;
//premenna cas sypania na int
int hoursTD[5] = {-1,-1,-1,-1,-1};
int minutesTD[5] = {-1,-1,-1,-1,-1};
//premenne do forov
int i = 0;
int i2 = 0;
int i3 = 0;
int i4 = 0;
int i5 = 0;
int done10 = 0;
//menu
int page = 1;
int pages = 6;
//FUNKCIE NA SPUSTANIE V PROGRAME

//zisti ktore tlacidlo sa stlacilo
int evaluateButton(int button, int buttonValue){
buttonValue = analogRead(A0);
  if(buttonValue<20){
    button = 0;
  }
  if(buttonValue>20&&buttonValue<342){
    button = 1;
  }
  if(buttonValue>341&&buttonValue<682){
    button = 2;
  }
  if(buttonValue>681){
    button = 3;
  }
  return button;
}

//nastavenie casu
void timeSet(int done1, int done2, int done3){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Nastav cas:");
  lcd.setCursor(0,1);
  lcd.print(hours);
  lcd.print(":");
  lcd.print(minutes);
  lcd.print("     ");
  delay(lcdDelay);
  do {
    if (evaluateButton(0, 0) == 1) {
      hours = hours + 1;
      if(hours >= 24){
        hours = hours - 24;
      }
      lcd.setCursor(0,1);
      lcd.print(hours);
      lcd.print(":");
      lcd.print(minutes);
      lcd.print("     ");
      delay(pressDelay);
    }
    if (evaluateButton(0, 0) == 2){
      minutes = minutes + 1;
      if(minutes >= 60){
        minutes = minutes - 60;
      }
      lcd.setCursor(0,1);
      lcd.print(hours);
      lcd.print(":");
      lcd.print(minutes);
      delay(pressDelay);
      lcd.print("     ");
    }
    if(evaluateButton(0, 0) == 3){
      done1 = 1;
      delay(pressDelay);
      }
    } while (done1 == 0);
    lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Nastav datum:");
  lcd.setCursor(0,1);
  lcd.print(days);
  lcd.print(".");
  lcd.print(months);
  lcd.print(".");
  lcd.print("     ");
  delay(lcdDelay);
  do {
    if (evaluateButton(0, 0) == 1) {
      days = days + 1;
        if(days > 31){
      days = days - 31;
      }
      lcd.setCursor(0,1);
      lcd.print(days);
      lcd.print(".");
      lcd.print(months);
      lcd.print(".");
      lcd.print("     ");
      delay(pressDelay);
    }
    if (evaluateButton(0, 0) == 2) {
      months = months + 1;
      if(months > 12){
        months = months - 12;
      }
      lcd.setCursor(0,1);
      lcd.print(days);
      lcd.print(".");
      lcd.print(months);
      lcd.print(".");
      lcd.print("     ");
      delay(pressDelay);
    }
    if (evaluateButton(0, 0) == 3) {
      done2 = 1;
      delay(pressDelay);
    }
  } while (done2 == 0);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Nastav rok:");
  lcd.setCursor(0,1);
  lcd.print(years);
  delay(lcdDelay);
  do {
    if (evaluateButton(0, 0) == 1) {
      years = years + 1;
      lcd.setCursor(0,1);
      lcd.print(years);
      lcd.print("     ");
      delay(pressDelay);
    }
    if (evaluateButton(0, 0) == 2) {
      years = years - 1;
      lcd.setCursor(0,1);
      lcd.print(years);
      lcd.print("     ");
      delay(pressDelay);
    }
    if (evaluateButton(0, 0) == 3) {
      done3 = 1;
      delay(pressDelay);
    }
  } while (done3 == 0);
lcd.clear();
lcd.setCursor(0,0);
lcd.print("Nastavene");
delay(1000);
lcd.clear();
}

// pocet sypani za den
void foodPerDay(int done4){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Pocet sypani za");
  lcd.setCursor(0,1);
  lcd.print("den: ");
  lcd.setCursor(5,1);
  lcd.print(sypPerDay);
  lcd.print("   ");
  delay(lcdDelay);
  do {
    if (evaluateButton(0, 0) == 1) {
      sypPerDay = sypPerDay + 1;
      if (sypPerDay > 5){
        sypPerDay = 0;
      }
      lcd.setCursor(5,1);
      lcd.print(sypPerDay);
      lcd.print("   ");
      delay(pressDelay);
    }
    if (evaluateButton(0, 0) == 2) {
      sypPerDay = sypPerDay - 1;
      if (sypPerDay < 0){
        sypPerDay = 5;
      }
      lcd.setCursor(5,1);
      lcd.print(sypPerDay);
      lcd.print("   ");
      delay(pressDelay);
    }
    if (evaluateButton(0, 0) == 3) {
      done4 = 1;
      delay(pressDelay);
    }
  } while (done4 == 0);
  done4 = 0;
  for(i5 = sypPerDay; i5 <= 4; i5++){
    hoursTD[i5] = -1;
  }
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Nastavene");
  delay(1000);
  lcd.clear();
}

//Velkost davky
void foodPortion(int done5){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Nastav velkost");
  lcd.setCursor(0,1);
  lcd.print("davky:");
  lcd.setCursor(7,1);
  lcd.print(foodSize*rotations);
  lcd.print(" g  ");
  delay(lcdDelay);
  do {
    if (evaluateButton(0, 0) == 1) {
      rotations = rotations + 1;
      lcd.setCursor(7,1);
      lcd.print(foodSize*rotations);
      lcd.print(" g  ");
      delay(pressDelay);
    }
    if (evaluateButton(0, 0) == 2) {
      rotations = rotations - 1;
      if (rotations < 0){
        rotations = 0;
      }
      lcd.setCursor(7,1);
      lcd.print(foodSize*rotations);
      lcd.print(" g  ");
      delay(pressDelay);
    }
    if (evaluateButton(0, 0) == 3) {
      done5 = 1;
      delay(pressDelay);
    }
  } while (done5 == 0);
  feeding = rotations * 512;
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Nastavene");
  delay(1000);
  lcd.clear();
}

//Dni v tyzdni ktore to ma fungovat
void weekDays(int done6){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Pondelok   ");
  delay(lcdDelay);
  do {
    if (evaluateButton(0, 0) == 1) {
      lcd.setCursor(0,1);
      lcd.write(1);
      DOTW[1] = 1;
      done6 = 1;
      delay(pressDelay);
    }
    if (evaluateButton(0, 0) == 2) {
      DOTW[1] = 0;
      done6 = 1;
      delay(pressDelay);
    }
  } while (done6 == 0);
  done6 = 0;
  lcd.setCursor(0,0);
  lcd.print("Utorok    ");
  delay(lcdDelay);
  do {
    if (evaluateButton(0, 0) == 1) {
      lcd.setCursor(1,1);
      lcd.write(1);
      DOTW[2] = 1;
      done6 = 1;
      delay(pressDelay);
    }
    if (evaluateButton(0, 0) == 2) {
      DOTW[2] = 0;
      done6 = 1;
    }
  } while (done6 == 0);
  done6 = 0;
  lcd.setCursor(0,0);
  lcd.print("Streda    ");
  delay(lcdDelay);
  do {
    if (evaluateButton(0, 0) == 1) {
      lcd.setCursor(2,1);
      lcd.write(1);
      DOTW[3] = 1;
      done6 = 1;
      delay(pressDelay);
    }
    if (evaluateButton(0, 0) == 2) {
      DOTW[3] = 0;
      done6 = 1;
      delay(pressDelay);
    }
  } while (done6 == 0);
  done6 = 0;
  lcd.setCursor(0,0);
  lcd.print("Stvrtok    ");
  delay(lcdDelay);
  do {
    if (evaluateButton(0, 0) == 1) {
      lcd.setCursor(3,1);
      lcd.write(1);
      DOTW[4] = 1;
      done6 = 1;
      delay(pressDelay);
    }
    if (evaluateButton(0, 0) == 2) {
      DOTW[4] = 0;
      done6 = 1;
      delay(pressDelay);
    }
  } while (done6 == 0);
  done6 = 0;
  lcd.setCursor(0,0);
  lcd.print("Piatok     ");
  delay(lcdDelay);
  do {
    if (evaluateButton(0, 0) == 1) {
      lcd.setCursor(4,1);
      lcd.write(1);
      DOTW[5] = 1;
      done6 = 1;
      delay(pressDelay);
    }
    if (evaluateButton(0, 0) == 2) {
      DOTW[5] = 0;
      done6 = 1;
      delay(pressDelay);
    }
  } while (done6 == 0);
  done6 = 0;
  lcd.setCursor(0,0);
  lcd.print("Sobota     ");
  delay(lcdDelay);
  do {
    if (evaluateButton(0, 0) == 1) {
      lcd.setCursor(5,1);
      lcd.write(1);
      DOTW[6] = 1;
      done6 = 1;
      delay(pressDelay);
    }
    if (evaluateButton(0, 0) == 2) {
      DOTW[6] = 0;
      done6 = 1;
      delay(pressDelay);
    }
  } while (done6 == 0);
  done6 = 0;
  lcd.setCursor(0,0);
  lcd.print("Nedela     ");
  delay(lcdDelay);
  do {
    if (evaluateButton(0, 0) == 1) {
      lcd.setCursor(6,1);
      lcd.write(1);
      DOTW[0] = 1;
      done6 = 1;
      delay(pressDelay);
     }
    if (evaluateButton(0, 0) == 2) {
      DOTW[0] = 0;
      done6 = 1;
      delay(pressDelay);
    }
  } while (done6 == 0);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Nastavene");
  delay(1000);
  lcd.clear();
}

//O kolkej sa to ma robit
void foodTime(int done7){
  lcd.clear();
  for(i5 = 0; i5 <= sypPerDay; i5++){
    hoursTD[i5] = 0;
  }
  for(i = 0; i < sypPerDay; i++){
    lcd.setCursor(0,0);
    lcd.print(i + 1);
    lcd.print(". cas sypania:");
    lcd.setCursor(0,1);
    lcd.print(hoursTD[i]);
    lcd.print(":");
    lcd.print(minutesTD[i]);
    delay(lcdDelay);
    do {
      if (evaluateButton(0, 0) == 1) {
        hoursTD[i] = hoursTD[i] + 1;
        if(hoursTD[i] >= 24){
          hoursTD[i] = hoursTD[i] - 24;
        }
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print(i + 1);
        lcd.print(". cas sypania:");
        lcd.setCursor(0,1);
        lcd.print(hoursTD[i]);
        lcd.print(":");
        lcd.print(minutesTD[i]);
        lcd.print("     ");
        delay(pressDelay);
      }
      if (evaluateButton(0, 0) == 2) {
        minutesTD[i] = minutesTD[i] + 1;
        if(minutesTD[i] >= 60){
          minutesTD[i] = minutesTD[i] - 60;
        }
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print(i + 1);
        lcd.print(". cas sypania:");
        lcd.setCursor(0,1);
        lcd.print(hoursTD[i]);
        lcd.print(":");
        lcd.print(minutesTD[i]);
        lcd.print("     ");
        delay(pressDelay);
      }
      if(evaluateButton(0, 0) == 3) {
        done7 = 1;
        delay(pressDelay);
      }
    } while (done7 == 0);
    done7 = 0;
  }
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Nastavene");
  delay(1000);
  lcd.clear();
}

//Menu
void menu(int done8){
  done8 = 0;
  do{
    if(evaluateButton(0, 0) == 1){
      page = page - 1;
      if(page < 1){
        page = 5;
      }
      menuUI();
      delay(pressDelay);
    }
    if(evaluateButton(0, 0) == 2){
      page = page + 1;
      if(page > 5){
        page = 1;
      }
      menuUI();
      delay(pressDelay);
    }
    if(evaluateButton(0, 0) == 3){
      if(page == 1){
        timeSet(0,0,0);
        rtc.begin();
        rtc.adjust(DateTime(years, months, days, hours, minutes, seconds));
        done8 = 1;
      }
      if(page == 2){
        weekDays(0);
        done8 = 1;
      }
      if(page == 3){
        foodPerDay(0);
        done8 = 1;
      }
      if(page == 4){
        foodTime(0);
        done8 = 1;
      }
      if(page == 5){
        foodPortion(0);
        done8 = 1;
      }
    }
  } while (done8 == 0);
  menuUI();
  done8 = 0;
}

//Menu UI
void menuUI(){
  switch(page){
    case 1:
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Systemovy cas");          //1 menu entry
      lcd.setCursor(0,1);
      lcd.print("Dni krmenia");            //2 menu entry
      break;
    case 2:
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Dni krmenia");
      lcd.setCursor(0,1);
      lcd.print("Krmenia za den");          //3 menu entry
      break;
    case 3:
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Krmenia za den");
      lcd.setCursor(0,1);
      lcd.print("Cas krmeni");               //4 menu entry
      break;
    case 4:
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Cas krmeni");
      lcd.setCursor(0,1);
      lcd.print("Velkost davky");            //5 menu entry
      break;
    case 5:
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Velkost davky");            //6 menu entry
      lcd.setCursor(0,1);
      lcd.print("Systemovy cas");
      break;
    default:
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Systemovy cas");
      lcd.setCursor(0,1);
      lcd.print("Dni krmenia");
  }
}


//HLAVNY PROGRAM
void setup(){
  rtc.begin();
  lcd.begin(16, 2);
  lcd.createChar(1, Thicc);
  if(! rtc.isrunning()){
    timeSet(0, 0, 0);
    rtc.adjust(DateTime(years, months, days, hours, minutes, seconds));
  }
  stepper.setSpeed(15);
  menuUI();
}

void loop(){
  DateTime now = rtc.now();
  yearNow = now.year();
  monthNow = now.month();
  weekNow = now.dayOfTheWeek();
  dayNow = now.day();
  hoursNow = now.hour();
  minutesNow = now.minute();
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(dayNow);
  lcd.print(". ");
  lcd.print(monthNow);
  lcd.print(". ");
  lcd.print(yearNow);
  lcd.setCursor(0,1);
  lcd.print(hoursNow);
  lcd.print(":");
  lcd.print(minutesNow);
  if(done10 == 1&&minutesNow > timeHappened){
    done10 = 0;
  }
  for(i2 = 0; i2 < 7; i2++){
    if(weekNow == i2){
      if(DOTW[i2] == 1){
        for(i3 = 0; i3 < 5; i3++){
          if(done10 == 0&&hoursNow == hoursTD[i3]&&minutesNow == minutesTD[i3]){
            stepper.step(feeding);
            delay(500);
            timeHappened = minutesNow;
            done10 = 1;
          }
        }
      }
    }
  }

/*
  if(now.dayOfTheWeek() == 1){
    if(DOTW[1] == 1){
      if(now.hour() == hoursTD[0]&&now.minute() == minutesTD[0]){
        stepper.step(512*rotations);
      }
      if(now.hour() == hoursTD[1]&&now.minute() == minutesTD[1]){
        stepper.step(512*rotations);
      }
      if(now.hour() == hoursTD[2]&&now.minute() == minutesTD[2]){
        stepper.step(512*rotations);
      }
      if(now.hour() == hoursTD[3]&&now.minute() == minutesTD[3]){
        stepper.step(512*rotations);
      }
      if(now.hour() == hoursTD[4]&&now.minute() == minutesTD[4]){
        stepper.step(512*rotations);
      }
    }
  }
  if(now.dayOfTheWeek() == 2){
    if(DOTW[2] == 1){
      if(now.hour() == hoursTD[0]&&now.minute() == minutesTD[0]){
        stepper.step(512*rotations);
      }
      if(now.hour() == hoursTD[1]&&now.minute() == minutesTD[1]){
        stepper.step(512*rotations);
      }
      if(now.hour() == hoursTD[2]&&now.minute() == minutesTD[2]){
        stepper.step(512*rotations);
      }
      if(now.hour() == hoursTD[3]&&now.minute() == minutesTD[3]){
        stepper.step(512*rotations);
      }
      if(now.hour() == hoursTD[4]&&now.minute() == minutesTD[4]){
        stepper.step(512*rotations);
      }
    }
  }
  if(now.dayOfTheWeek() == 3){
    if(DOTW[3] == 1){
      if(now.hour() == hoursTD[0]&&now.minute() == minutesTD[0]){
        stepper.step(512*rotations);
      }
      if(now.hour() == hoursTD[1]&&now.minute() == minutesTD[1]){
        stepper.step(512*rotations);
      }
      if(now.hour() == hoursTD[2]&&now.minute() == minutesTD[2]){
        stepper.step(512*rotations);
      }
      if(now.hour() == hoursTD[3]&&now.minute() == minutesTD[3]){
        stepper.step(512*rotations);
      }
      if(now.hour() == hoursTD[4]&&now.minute() == minutesTD[4]){
        stepper.step(512*rotations);
      }
    }
  }
  if(now.dayOfTheWeek() == 4){
    if(DOTW[4] == 1){
      if(now.hour() == hoursTD[0]&&now.minute() == minutesTD[0]){
        stepper.step(512*rotations);
      }
      if(now.hour() == hoursTD[1]&&now.minute() == minutesTD[1]){
        stepper.step(512*rotations);
      }
      if(now.hour() == hoursTD[2]&&now.minute() == minutesTD[2]){
        stepper.step(512*rotations);
      }
      if(now.hour() == hoursTD[3]&&now.minute() == minutesTD[3]){
        stepper.step(512*rotations);
      }
      if(now.hour() == hoursTD[4]&&now.minute() == minutesTD[4]){
        stepper.step(512*rotations);
      }
    }
  }
  if(now.dayOfTheWeek() == 5){
    if(DOTW[5] == 1){
      if(now.hour() == hoursTD[0]&&now.minute() == minutesTD[0]){
        stepper.step(512*rotations);
      }
      if(now.hour() == hoursTD[1]&&now.minute() == minutesTD[1]){
        stepper.step(512*rotations);
      }
      if(now.hour() == hoursTD[2]&&now.minute() == minutesTD[2]){
        stepper.step(512*rotations);
      }
      if(now.hour() == hoursTD[3]&&now.minute() == minutesTD[3]){
        stepper.step(512*rotations);
      }
      if(now.hour() == hoursTD[4]&&now.minute() == minutesTD[4]){
        stepper.step(512*rotations);
      }
    }
  }
  if(now.dayOfTheWeek() == 6){
    if(DOTW[6] == 1){
      if(now.hour() == hoursTD[0]&&now.minute() == minutesTD[0]){
        stepper.step(512*rotations);
      }
      if(now.hour() == hoursTD[1]&&now.minute() == minutesTD[1]){
        stepper.step(512*rotations);
      }
      if(now.hour() == hoursTD[2]&&now.minute() == minutesTD[2]){
        stepper.step(512*rotations);
      }
      if(now.hour() == hoursTD[3]&&now.minute() == minutesTD[3]){
        stepper.step(512*rotations);
      }
      if(now.hour() == hoursTD[4]&&now.minute() == minutesTD[4]){
        stepper.step(512*rotations);
      }
    }
  }
  if(now.dayOfTheWeek() == 0){
    if(DOTW[0] == 1){
      if(now.hour() == hoursTD[0]&&now.minute() == minutesTD[0]){
        stepper.step(512*rotations);
      }
      if(now.hour() == hoursTD[1]&&now.minute() == minutesTD[1]){
        stepper.step(512*rotations);
      }
      if(now.hour() == hoursTD[2]&&now.minute() == minutesTD[2]){
        stepper.step(512*rotations);
      }
      if(now.hour() == hoursTD[3]&&now.minute() == minutesTD[3]){
        stepper.step(512*rotations);
      }
      if(now.hour() == hoursTD[4]&&now.minute() == minutesTD[4]){
        stepper.step(512*rotations);
      }
    }
  }
  */
  if(evaluateButton(0, 0) >= 1){
    menuUI();
    delay(150);
    menu(0);
  }
}
