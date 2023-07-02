#include <LiquidCrystal.h>

const int Pir = 12;
const int Buzzer = A0;
const int led = A4;
int Leitura = 0;
int x = 0;
String Senha = "2551";
String Salvo;
String Dado;
int Alarme = 0;
int sensor = 0;

LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

void setup() {
  lcd.begin(16, 2);
  pinMode(Buzzer, OUTPUT);
  pinMode(led, OUTPUT);
  pinMode(Pir, INPUT);
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);
  pinMode(A3, OUTPUT);
  pinMode(8, INPUT_PULLUP);
  pinMode(9, INPUT_PULLUP);
  pinMode(10, INPUT_PULLUP);
  pinMode(11, INPUT_PULLUP);

  lcd.clear();
  lcd.print("   Bem-vindo!");
  lcd.setCursor(0, 1);
  lcd.print("  Pressione #");
  lcd.setCursor(0, 2);
}

void loop() {
  if (digitalRead(8) == LOW) {
    delay(300);
    lcd.clear();
    lcd.print("   Bem-vindo!");
    lcd.setCursor(0, 1);
    lcd.print("Senha: ");
    lcd.setCursor(7, 1);
    TecladoMatricial();
    if (Salvo == Senha && Alarme == true) {
      lcd.clear();
      lcd.print("   Bem-vindo");
      lcd.setCursor(0, 1);
      lcd.print("Alarme Desligado");
      Alarme = 0;
      tone(Buzzer, 1000, 100);
      delay(300);
      tone(Buzzer, 1000, 100);
      delay(300);
      tone(Buzzer, 1000, 100);
    }
    else if (Salvo == Senha && Alarme == false) {
      lcd.clear();
      lcd.print("   Bem-vindo");
      lcd.setCursor(0, 1);
      lcd.print("Alarme Ativado!");
      Alarme = 1;
      tone(Buzzer, 1000, 100);
      delay(8000);
      tone(Buzzer, 5000, 1000);
    }
    else if (Salvo != Senha) {
      lcd.clear();
      lcd.print("   Bem-vindo!");
      lcd.setCursor(0, 1);
      lcd.print("  Pressione #");
      lcd.setCursor(0, 2);
      lcd.print(" Senha Errada!");
      tone(Buzzer, 100, 1000);
      delay(300);
      tone(Buzzer, 100, 1000);
      delay(1000);
      lcd.clear();
      lcd.print("   Bem-vindo!");
      lcd.setCursor(0, 1);
      lcd.print("  Pressione #");
      lcd.setCursor(0, 2);
    }
  }

  if (digitalRead(Pir) == HIGH && Alarme == 1) {
    tone(Buzzer, 196);
    sensor = 1;
  }

  while (sensor == 1) {
    lcd.clear();
    lcd.print("    Perigo!!!");
    digitalWrite(led, HIGH);
    lcd.setCursor(0, 1);
    lcd.print("Senha:");
    TecladoMatricial();

    if (Salvo == Senha) {
      lcd.clear();
      lcd.print("Alarme Desligado");
      tone(Buzzer, 1000, 100);
      delay(300);
      tone(Buzzer, 1000, 100);
      delay(1000);
      lcd.clear();
      lcd.print("   Bem-vindo!");
      lcd.setCursor(0, 1);
      lcd.print("  Pressione #");
      lcd.setCursor(0, 2);
      digitalWrite(led, LOW);
      noTone(Buzzer);
      sensor = 0;
      Alarme = 0;
    }

    if (Salvo != Senha) {
      lcd.clear();
      lcd.print(" Senha Errada!");
      delay(1000);
    }
  }
}

void TecladoMatricial() {
  x = 0;
  Salvo = "";
  Dado = "";
  while (x <= 3) {
    if (Leitura == 0) {
      digitalWrite(A3, LOW);
      digitalWrite(A2, HIGH);
      digitalWrite(A1, HIGH);
      if (!digitalRead(11) && Leitura == 0) {
        Dado = '1';
        Salvo += Dado;
        x++;
        lcd.print(Dado);
        delay(300);
      }
      else if (!digitalRead(10) && Leitura == 0) {
        Dado = '4';
        Salvo += Dado;
        x++;
        lcd.print(Dado);
        delay(300);
      }
      else if (!digitalRead(9) && Leitura == 0) {
        Dado = '7';
        Salvo += Dado;
        x++;
        lcd.print(Dado);
        delay(300);
      }
      else if (!digitalRead(8) && Leitura == 0) {
        Dado = '*';
        Salvo += Dado;
        x++;
        lcd.print(Dado);
        delay(300);
      }
      Leitura = 1;
    }

    if (Leitura == 1) {
      digitalWrite(A3, HIGH);
      digitalWrite(A2, LOW);
      digitalWrite(A1, HIGH);
      if (!digitalRead(11) && Leitura == 1) {
        Dado = '2';
        Salvo += Dado;
        x++;
        lcd.print(Dado);
        delay(300);
      }
      else if (!digitalRead(10) && Leitura == 1) {
        Dado = '5';
        Salvo += Dado;
        x++;
        lcd.print(Dado);
        delay(300);
      }
      else if (!digitalRead(9) && Leitura == 1) {
        Dado = '8';
        Salvo += Dado;
        x++;
        lcd.print(Dado);
        delay(300);
      }
      else if (!digitalRead(8) && Leitura == 1) {
        Dado = '0';
        Salvo += Dado;
        x++;
        lcd.print(Dado);
        delay(300);
      }
      Leitura = 2;
    }

    if (Leitura == 2) {
      digitalWrite(A3, HIGH);
      digitalWrite(A2, HIGH);
      digitalWrite(A1, LOW);
      if (!digitalRead(11) && Leitura == 2) {
        Dado = '3';
        Salvo += Dado;
        x++;
        lcd.print(Dado);
        delay(300);
      }
      else if (!digitalRead(10) && Leitura == 2) {
        Dado = '6';
        Salvo += Dado;
        x++;
        lcd.print(Dado);
        delay(300);
      }
      else if (!digitalRead(9) && Leitura == 2) {
        Dado = '9';
        Salvo += Dado;
        x++;
        lcd.print(Dado);
        delay(300);
      }
      else if (!digitalRead(8) && Leitura == 2) {
        Dado = '#';
        Salvo += Dado;
        x++;
        lcd.print(Dado);
        delay(300);
      }
      Leitura = 0;
    }
  }
}
