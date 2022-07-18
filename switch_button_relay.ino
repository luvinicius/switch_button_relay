// imutable values:
#define BUTON_PIN 4
#define RELAY_1_PIN 7
#define RELAY_2_PIN 8
#define NUMBER_OF_RELAYS 2

// control variables:
int beforeState = 0; // store the state of button befor change
int buttonState = 0; // store the current state of button
int selected_relay = 0; // stores the current selected relay to tun-on, 0 means none relay is selected

void setup() {
  pinMode(BUTON_PIN, INPUT); // set-up button pin

  pinMode(RELAY_1_PIN, OUTPUT); // set-up first relay pin and start it as turn-off
  digitalWrite(RELAY_1_PIN, HIGH);

  pinMode(RELAY_2_PIN, OUTPUT); // set-up second relay pin and start it as turn-off
  digitalWrite(RELAY_2_PIN, HIGH);

  Serial.begin(9600);
  while (!Serial) ; // wait for serial
  delay(200);
  Serial.println("-------------------");

}

void loop() {
  beforeState = buttonState; // store the current state of button before read the new state
  buttonState = digitalRead(BUTON_PIN); // read new current state of button



  // If the button is released but before it was pressed, its mean one "click"
  if (buttonState == LOW) {
    if (beforeState == HIGH) {
      // each click in the button will selected the next relay
      selected_relay = selected_relay + 1;
      Serial.println("Button click event!");
    }
  }
  if (selected_relay > NUMBER_OF_RELAYS) {
    // If its selected an relay out of bound its mean none relay is selected
    selected_relay = 0; // set selected relay to none
    // turn-off last relay
    digitalWrite(RELAY_2_PIN, HIGH);
    Serial.println("Turn-off second relay!");
  } else if (selected_relay == 1) { // turn-on first relay
    digitalWrite(RELAY_1_PIN, LOW);
    Serial.println("Turn-on first relay!");
  } else if (selected_relay == 2) { // turn-off first relay nd turn-on second relay
    digitalWrite(RELAY_1_PIN, HIGH);
    Serial.println("Turn-off first relay!");
    digitalWrite(RELAY_2_PIN, LOW);
    Serial.println("Turn-on second relay!");
  }
}
