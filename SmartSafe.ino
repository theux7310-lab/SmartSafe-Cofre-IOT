#include <Keypad.h>
#include <Servo.h>

// Constantes
const byte VERMELHO = 2, VERDE = 3, SOM = 4, TRANCA = 5, LINHAS = 4, COLUNAS = 4;

// Objeto Servo
Servo tranca;

// Definindo portas do teclado
byte pinosLinhas[LINHAS] = {13,12,11,10};
byte pinosColunas[COLUNAS] = {9,8,7,6};

// Mapeando teclas
char teclas[LINHAS][COLUNAS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

// Objeto keypad
Keypad teclado = Keypad(
  makeKeymap(teclas),
  pinosLinhas,
  pinosColunas,
  LINHAS,
  COLUNAS
);

// Variáveis
String senha = "2315";
String senhaDigitada = "";
bool aberto = false, testar = false;

void setup()
{
  Serial.begin(9600);

  tranca.attach(TRANCA);

  pinMode(VERMELHO, OUTPUT);
  pinMode(VERDE, OUTPUT);
  pinMode(SOM, OUTPUT);

  tranca.write(90);

  digitalWrite(VERMELHO, HIGH);
}

void loop()
{
  char tecla = teclado.getKey();

  if (tecla) {

    senhaDigitada += tecla;

    Serial.println(senhaDigitada);
    Serial.println(senhaDigitada.length());

    tone(SOM, 1400, 150);

    if (senhaDigitada.length() == 4) {
      testar = true;
      delay(1000);
    }
  }

  if (testar) {

    testar = false;

    if (senhaDigitada == senha) {

      aberto = true;

      tone(SOM, 1600, 1000);
      delay(1000);

    } else {

      tone(SOM, 1000, 150);
      delay(300);

      tone(SOM, 1000, 150);
      delay(300);

      tone(SOM, 1000, 150);
      delay(300);
    }

    senhaDigitada = "";

    if (aberto) {

      tranca.write(180);

      digitalWrite(VERDE, HIGH);
      digitalWrite(VERMELHO, LOW);

    } else {

      tranca.write(90);

      digitalWrite(VERDE, LOW);
      digitalWrite(VERMELHO, HIGH);
    }
  }
}
