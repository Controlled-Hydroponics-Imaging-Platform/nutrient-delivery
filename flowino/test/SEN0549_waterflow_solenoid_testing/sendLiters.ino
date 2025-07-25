void sendLiters(float wantedLiters){ // technically don't need the paramter because global and only currently asking imput once
  if (totalLiters >= wantedLiters && !messageSent) {
    digitalWrite(12,LOW); // stop water
    Serial.print(totalLiters, 3);
    Serial.println("L of water was just sent to your tank!");
    delay(300);
    messageSent = true;
    }
}