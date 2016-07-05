// Bill OS 5.2 par esperys

#include <EEPROM.h>
#include <LiquidCrystal.h>
#include <Servo.h>
#include <Wire.h>
#include <Adafruit_NFCShield_I2C.h>

#define IRQ   (2)
#define RESET (3)

#define c 261
#define d 294
#define e 329
#define f 349
#define g 391
#define gS 415
#define a 440
#define aS 455
#define b 466
#define cH 523
#define cSH 554
#define dH 587
#define dSH 622
#define eH 659
#define fH 698
#define fSH 740
#define gH 784
#define gSH 830
#define aH 880
#define az 3135
#define ae 3729
#define ar 3520
#define at 2349
#define ay 1318
#define au 1174
#define ai 369
#define ao 415
#define ap 1108
#define aq 880
#define as 146
#define ad 164
#define af 980
#define ag 554
#define ah 659

Adafruit_NFCShield_I2C nfc(IRQ, RESET);

int pos = 0;
int master = 0;
int verification = 0;
int speakerPin = 3;                                                                   // Pins du HP  et des LEDs
int led = 13;

Servo servo_pene;
Servo servo_verrou;
Servo servo_porte;

LiquidCrystal lcd(12,11,4,5,6,7);                                                    // Pins de l'écran


//**************************************************Configuration**************************************************


void setup(void) {

  servo_porte.write(180);                                                           // Pos par défaut des servos
  servo_pene.write(180);
  servo_verrou.write(180);

  Serial.begin(115200);                                                              // Communication avec l'ordinateur
  Serial.println("Bill OS 5.2");

  lcd.begin(16,2);
  nfc.begin();

  uint32_t versiondata = nfc.getFirmwareVersion();                                   // Vérification de la présence du Shield RFID

  if (! versiondata) {
    Serial.print("Carte PN53x non trouvee");
    while (1);
  }
                                                                                            // Affichage des infos de base
  Serial.print("Carte PN5 trouvee"); Serial.println((versiondata>>24) & 0xFF, HEX);
  Serial.print("Version du logiciel "); Serial.print((versiondata>>16) & 0xFF, DEC);
  Serial.print('.'); Serial.println((versiondata>>8) & 0xFF, DEC);

  nfc.SAMConfig();                                                                         // Configuration de la carte RFID, des servos et du bouton
  servo_pene.attach(8);
  servo_verrou.attach(10);
  servo_porte.attach(9);
  pinMode(speakerPin, OUTPUT);
  pinMode(led, OUTPUT);

  lcd.setCursor(0,0);
  lcd.print("INITIALISATION");

  Serial.println("En attente d'une carte ISO14443A ...");
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Bonjour, scannez");
  lcd.setCursor(0,1);
  lcd.print("  votre carte  ");

}


//**************************************************Fonctions**************************************************


void ouverture()
{                                       // Fonction gerant l'ouverture
     int valeur=0;
     for(pos = 180; pos>=1; pos-=1)                      // Ouverture du pene et du verrou
  {
    servo_verrou.write(pos);
    servo_pene.write(pos);
    delay(15);
  }

   delay(200);

    for(pos = 180; pos>1; pos-=1)                        // Ouverture porte
  {
    servo_porte.write(pos);
    servo_pene.write(179-pos);                           // Fermeture pene
    delay(30);
  }


  lcd.clear();
  lcd.print("  Porte ouverte");


  delay(7000);                                             // Attente que la personne entre (7 sec)

  lcd.clear();
  lcd.print ("  Fermeture ");


   for(pos = 0; pos < 180; pos += 1)                      // Fermeture porte
  {
    servo_pene.write(180-pos);
    servo_porte.write(pos);                               // Ouverture pene
    delay(15);
  }

   delay(200);

    for(pos = 0; pos < 180; pos += 1)                       // Fermeture verrou + pene
  {
    servo_pene.write(pos);
    servo_verrou.write(pos);
    delay(15);
  }
  lcd.clear();
  lcd.print(" Porte fermee");
  delay(2000);
  digitalWrite(led, LOW);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Bonjour, scannez");
  lcd.setCursor(0,1);
  lcd.print("  votre carte  ");
  }


void beep(unsigned char speakerPin, int frequencyInHertz, long timeInMilliseconds)
{
    int x;

    long delayAmount = (long)(1000000/frequencyInHertz);

    long loopTime = (long)((timeInMilliseconds*1000)/(delayAmount*2));

    for (x=0;x<loopTime;x++)

    {

        digitalWrite(speakerPin,HIGH);

        delayMicroseconds(delayAmount);

        digitalWrite(speakerPin,LOW);

        delayMicroseconds(delayAmount);

    }

    delay(20);

}

void march()
{

    beep(speakerPin, a, 500);

    beep(speakerPin, a, 500);

    beep(speakerPin, a, 500);

    beep(speakerPin, f, 350);

    beep(speakerPin, cH, 150);



    beep(speakerPin, a, 500);

    beep(speakerPin, f, 350);

    beep(speakerPin, cH, 150);

    beep(speakerPin, a, 1000);



    beep(speakerPin, eH, 500);

    beep(speakerPin, eH, 500);

    beep(speakerPin, eH, 500);

    beep(speakerPin, fH, 350);

    beep(speakerPin, cH, 150);



    beep(speakerPin, gS, 500);

    beep(speakerPin, f, 350);

    beep(speakerPin, cH, 150);

    beep(speakerPin, a, 1000);



    beep(speakerPin, aH, 500);

    beep(speakerPin, a, 350);

    beep(speakerPin, a, 150);

    beep(speakerPin, aH, 500);

    beep(speakerPin, gSH, 250);

    beep(speakerPin, gH, 250);



    beep(speakerPin, fSH, 125);

    beep(speakerPin, fH, 125);

    beep(speakerPin, fSH, 250);

    delay(250);

    beep(speakerPin, aS, 250);

    beep(speakerPin, dSH, 500);

    beep(speakerPin, dH, 250);

    beep(speakerPin, cSH, 250);



    beep(speakerPin, cH, 125);

    beep(speakerPin, b, 125);

    beep(speakerPin, cH, 250);

    delay(250);

    beep(speakerPin, f, 125);

    beep(speakerPin, gS, 500);

    beep(speakerPin, f, 375);

    beep(speakerPin, a, 125);



    beep(speakerPin, cH, 500);

    beep(speakerPin, a, 375);

    beep(speakerPin, cH, 125);

    beep(speakerPin, eH, 1000);



    beep(speakerPin, aH, 500);

    beep(speakerPin, a, 350);

    beep(speakerPin, a, 150);

    beep(speakerPin, aH, 500);

    beep(speakerPin, gSH, 250);

    beep(speakerPin, gH, 250);



    beep(speakerPin, fSH, 125);

    beep(speakerPin, fH, 125);

    beep(speakerPin, fSH, 250);

    delay(250);

    beep(speakerPin, aS, 250);

    beep(speakerPin, dSH, 500);

    beep(speakerPin, dH, 250);

    beep(speakerPin, cSH, 250);



    beep(speakerPin, cH, 125);

    beep(speakerPin, b, 125);

    beep(speakerPin, cH, 250);

    delay(250);

    beep(speakerPin, f, 250);

    beep(speakerPin, gS, 500);

    beep(speakerPin, f, 375);

    beep(speakerPin, cH, 125);



    beep(speakerPin, a, 500);

    beep(speakerPin, f, 375);

    beep(speakerPin, c, 125);

    beep(speakerPin, a, 1000);

}


void hungergames()
{
    beep(speakerPin, az, 500);
    beep(speakerPin, ae, 500);
    beep(speakerPin, ar, 500);
    beep(speakerPin, at, 500);

}

void melodie()
{
   beep(speakerPin, ay, 250);
   beep(speakerPin, au, 250);
/*   beep(speakerPin, ai, 250);
   beep(speakerPin, ao, 500);
   beep(speakerPin, ap, 250);
   beep(speakerPin, aq, 250);
   beep(speakerPin, as, 250);
   beep(speakerPin, ad, 250);
   beep(speakerPin, aq, 250);
   beep(speakerPin, af, 250);
   beep(speakerPin, ag, 250);
   beep(speakerPin, ah, 250);
   beep(speakerPin, aq, 500);*/
}

void songrave()
{
  beep(speakerPin, b, 125);
  beep(speakerPin, gH, 125);

}

void attente()
{
  beep(speakerPin, b, 1000);
}

void enregistrement()
{
  beep(speakerPin, as, 250);
  beep(speakerPin, ar, 250);
  beep(speakerPin, aq, 250);
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


//**************************************************Debut de la boucle**************************************************


void loop(void)
{
  int test = 0;
  master = 0;
  verification = 0;
  digitalWrite(led, LOW);                                              // Extinction de la led

  uint8_t success;
  uint8_t uid[] = { 0, 0, 0, 0, 0, 0, 0 };                             // UID retourné (prend la valeur de l'UID de la carte lue)
  uint8_t uidLength;                                                   // Longueur de l'UID (4 ou 7 bytes en fonction de la carte) lue
                                                                       // uint8_t uid_master[] = { 0xCD, 0x2D, 0xB9, 0x7D, 0, 0, 0}; // carte maitre (ne changera jamais)
  uint8_t uid_m[] = { 0xCD, 0x2D, 0xB9, 0x7D, 0, 0, 0};                // carte maitre
  uint8_t uid_e[] = { 0, 0, 0, 0, 0, 0, 0 };
  uint8_t uid_dec[] = { 0, 0, 0, 0, 0, 0, 0 };
  uint8_t uid_r[] = { 0, 0, 0, 0, 0, 0, 0 };
  uint8_t uid_y[] = { 0, 0, 0, 0, 0, 0, 0 };
  uint8_t uid_u[] = { 0, 0, 0, 0, 0, 0, 0 };



   success = nfc.readPassiveTargetID(PN532_MIFARE_ISO14443A, uid, &uidLength);     // Lecture de la carte

   if (success)
   {                                                                            // Si une carte est scannee

    digitalWrite(led, HIGH);
    Serial.println("Carte trouvee");
    Serial.print("  UID Length: ");Serial.print(uidLength, DEC);Serial.println(" bytes");
    Serial.print("  UID: ");
    nfc.PrintHex(uid, uidLength);
    Serial.println("");

    lcd.clear();
    lcd.setCursor(0,0);


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


  EEPROM.write(9,uid[0]);                                                                     // Lecture memoire morte de la carte et rangement dans un tableau
  EEPROM.write(10,uid[1]);
  EEPROM.write(11,uid[2]);
  EEPROM.write(12,uid[3]);

  uid_dec[0] = EEPROM.read(9);
  uid_dec[1] = EEPROM.read(10);
  uid_dec[2] = EEPROM.read(11);
  uid_dec[3] = EEPROM.read(12);


  uid_e[0] = EEPROM.read(1);
  uid_e[1] = EEPROM.read(2);
  uid_e[2] = EEPROM.read(3);
  uid_e[3] = EEPROM.read(4);

  uid_r[0] = EEPROM.read(5);
  uid_r[1] = EEPROM.read(6);
  uid_r[2] = EEPROM.read(7);
  uid_r[3] = EEPROM.read(8);

  uid_y[0] = EEPROM.read(13);
  uid_y[1] = EEPROM.read(14);
  uid_y[2] = EEPROM.read(15);
  uid_y[3] = EEPROM.read(16);

  uid_u[0] = EEPROM.read(17);
  uid_u[1] = EEPROM.read(18);
  uid_u[2] = EEPROM.read(19);
  uid_u[3] = EEPROM.read(20);





    for (int i=0; i < 4; i++)                                                // Comparaison entre l'UID lu et les UID connus
    {
        if (uid[i] == uid_m[i])
        {
          master = master + 1;
        }

       /*else if (uid[i] == uid_t[i])
        {
        verification = verification + 1;

        } */
      /*  else if (uid[i] == uid_n[i])
        {
        verification = verification + 1;

        } */

        else if (uid_e[i] == uid_dec[i])
        {
        verification = verification + 1;

        }
        else if (uid_r[i] == uid_dec[i])
        {
        verification = verification + 1;

        }
        else if (uid_y[i] == uid_dec[i])
        {
        verification = verification + 1;

        }
        else if (uid_u[i] == uid_dec[i])
        {
        verification = verification + 1;

        }

     else                                                                   // Si une morceau du code est faux on quitte la verification
     {
       break;
     }
   }


//**************************************************Gestion des cartes**************************************************


  if (master == 4)                                                                                         // Si la carte mere est scannee
  {
  hungergames();                                                                                           // Jouer hungergames
  master = 0;
  verification = 8;
  uint8_t success;
  uint8_t uid[] = { 0, 0, 0, 0, 0, 0, 0 };
  uint8_t uidLength;
  lcd.print("  Scannez la    ");
  lcd.setCursor(0,1);
  lcd.print(" nouvelle carte ");

  success = nfc.readPassiveTargetID(PN532_MIFARE_ISO14443A, uid, &uidLength); // On lit la carte a enregistrer

  if (success)
  {
   for (int i=0; i < 4; i++)                                                  // Comparaison entre l'UID lu et la carte maitre
    {
        if (uid[i] == uid_m[i])
        {
          master = master + 1;
        }
    }
  if (master == 4)                                                          // Si la care maitre est scannee une deuxieme fois
  {
    march();                                                               // Jouer la marche imperiale
  EEPROM.write(1,0);                                                       // Remise a 0 de la carte enregistree
  EEPROM.write(2,0);
  EEPROM.write(3,0);
  EEPROM.write(4,0);
  EEPROM.write(5,0);                                                       // Remise a 0 de la carte enregistree
  EEPROM.write(6,0);
  EEPROM.write(7,0);
  EEPROM.write(8,0);
  EEPROM.write(13,0);                                                       // Remise a 0 de la carte enregistree
  EEPROM.write(14,0);
  EEPROM.write(15,0);
  EEPROM.write(16,0);
  EEPROM.write(17,0);                                                       // Remise a 0 de la carte enregistree
  EEPROM.write(18,0);
  EEPROM.write(19,0);
  EEPROM.write(20,0);
  lcd.clear();
  lcd.print("Suppression cartes");
  delay(2000);

  }

  else if (master != 4)                                                    // Si la carte qui a ete scannee une deuxieme fois est pas la carte maitre
  {
  melodie();                                                                   // Jouer la melodie
  delay(1000);
  if (uid_e[0] == 0)
  {
   enregistrement();
   EEPROM.write(1,uid[0]);                                                  // Enregistrer le code de la carte sur la memoire morte
   EEPROM.write(2,uid[1]);
   EEPROM.write(3,uid[2]);
   EEPROM.write(4,uid[3]);
   lcd.clear();
   lcd.print("Enregistrement 1");
   delay(4000);
   test=1;
  }

  else if (uid_r[0] == 0 && test == 0)
  {
   enregistrement();
   EEPROM.write(5,uid[0]);                                                  // Enregistrer le code de la carte sur la memoire morte
   EEPROM.write(6,uid[1]);
   EEPROM.write(7,uid[2]);
   EEPROM.write(8,uid[3]);
   lcd.clear();
   lcd.print("Enregistrement 2");
   delay(4000);
   test=1;
  }
  else if (uid_y[0] == 0 && test == 0)
  {
   enregistrement();
   EEPROM.write(13,uid[0]);                                                  // Enregistrer le code de la carte sur la memoire morte
   EEPROM.write(14,uid[1]);
   EEPROM.write(15,uid[2]);
   EEPROM.write(16,uid[3]);
   lcd.clear();
   lcd.print("Enregistrement 3");
   delay(4000);
   test=1;
  }
    else if (uid_u[0] == 0 && test == 0)
  {
   enregistrement();
   EEPROM.write(17,uid[0]);                                                  // Enregistrer le code de la carte sur la memoire morte
   EEPROM.write(18,uid[1]);
   EEPROM.write(19,uid[2]);
   EEPROM.write(20,uid[3]);
   lcd.clear();
   lcd.print("Enregistrement 4");
   delay(4000);
  }

  else
  {
   lcd.clear();
   lcd.print("Plus de place");
   delay(4000);
  }
  }
  }
  }                                                                         // Si l'UID est connu, on apelle la fonction d'ouverture de porte
   else if (verification == 4)
  {
    songrave();
    lcd.clear();
    lcd.print(" Carte acceptee ");
    lcd.setCursor(0,1);
    lcd.print("  Ouverture en cours");
    for(int x=0; x<4; x++)
	{
		lcd.scrollDisplayLeft();
		delay(700);
	}
    ouverture();
  }



 else if (verification != 4)                                  // Carte non reconnue -> temporisation 10 sec
 {
    digitalWrite(led, HIGH);                                  // Allumage led
    lcd.clear();
    lcd.print("  Carte refusee ");
    for (int ab=0; ab<9;ab++)
    {
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("  Carte refusee ");
      lcd.setCursor(0,1);
      lcd.write("   attendez");
      lcd.setCursor(13,1);
      int de= 9-ab;
      lcd.print(de);
      attente();
    }

  digitalWrite(led, LOW);                                   // Extinction de la led
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Bonjour, scannez");
  lcd.setCursor(0,1);
  lcd.print("  votre carte  ");
 }

}

}
