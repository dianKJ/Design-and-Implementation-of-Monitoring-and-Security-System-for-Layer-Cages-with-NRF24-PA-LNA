void tampilData() {
  myRadio.read( &data, sizeof(data) );

  lcd.setCursor(0, 0);
  lcd.print("Suhu:");

  lcd.setCursor(5, 0);
  lcd.print(data.Suhu, 4);

  lcd.setCursor(10, 0);
  sprintf(buff, "Hum:%2i", data.Hum);
  lcd.print(buff);

  lcd.setCursor(0, 1);
  lcd.print("PPM:");

  lcd.setCursor(4, 1);
  lcd.print(data.PPM1_High, 3);

  lcd.setCursor(10, 1);
  lcd.print("KT:");

  lcd.setCursor(13, 1);
  lcd.print(data.kelembaban, 4);



  Serial.print("\nPackage:");
  Serial.print(data.id);
  Serial.print("\n");
  Serial.println(data.kelembaban);
  Serial.println(data.buttonRead);
  Serial.println(data.PPM1_High);
  Serial.println(data.PIR);
  Serial.println(data.Suhu);
  Serial.println(data.Hum);
  Serial.println(data.text);
}




void bacaButton() {

  lcd_printf(0, 0, "   Monitoruing    ");
  lcd_printf(0, 1, "================");
  delay(300);
  lcd.clear();
  lcd_printf(0, 0, "  Kandang Ayam  ");
  lcd_printf(0, 1, "      NRF24       ");
  delay(300);
  lcd.clear();
  menu_choose = 1;
here :
  while (1)
  {
    if (menu_choose == 1)
    {
      lcd_printf(0, 0, "~Tampil Data");
      lcd_printf(0, 1, " Mode Aman ");
    }
    else if (menu_choose == 2)
    {
      lcd_printf(0, 0, "Tampil Data");
      lcd_printf(0, 1, "~Mode Aman ");
    }
    else if (menu_choose == 3)
    {
      lcd_printf(0, 0, " Jalan");
      lcd_printf(0, 1, "~Cek Sensor ");
    }
kesini:

    if (analogRead(A0) < 120 && analogRead(A0) > 20)
    { while (analogRead(A0) < 120 && analogRead(A0) > 20);
      delay(800);
      lcd.clear();
      if (menu_choose == 1) while (1) {
          tampilData();delay(50);
        }

      if (menu_choose == 2)while (1) {
          //          lcd.clear();
          tampilData();
          if (data.PIR == 1) {
            lcd.clear();
            while (1) {

              lcd_printf(0, 0, "Ada Pergerakan !");
              lcd_printf(0, 1, " Cek Kandang ! ");

              digitalWrite(2, HIGH);
              delay(150);
              digitalWrite(2, LOW);
              delay(150);

              if (analogRead(A0) > 600) {
                lcd.clear();
                delay(500);
                goto kesini;
              }

            }

          }
          delay(100);
        }
    }

    if (analogRead(A0) > 120 && analogRead(A0) < 250)
    {
      while (analogRead(A0) > 120 && analogRead(A0) < 250);
      lcd.clear();
      if (menu_choose < 2) menu_choose++; delay(200);
    }

    if (analogRead(A0) > 260 && analogRead(A0) < 500)
    {
      while (analogRead(A0) > 260 && analogRead(A0) < 500);
      lcd.clear();
      if (menu_choose > 1) menu_choose--; delay(200);
    }
    if (analogRead(A0) > 660 )
    {
      while (analogRead(A0) > 660 );

    }
  }

}
