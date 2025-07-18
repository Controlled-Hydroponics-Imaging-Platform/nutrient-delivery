void sendLiters(float wantedLiters){ // technically don't need the paramter because global and only currently asking imput once
  if (totalLiters >= wantedLiters) {
  digitalWrite(12,HIGH); // RELAY OFF   
  }
}