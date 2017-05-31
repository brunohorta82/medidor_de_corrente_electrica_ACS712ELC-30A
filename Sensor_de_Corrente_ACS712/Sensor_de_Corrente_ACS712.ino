int pinoSensor =A0;

int sensorValueAux = 0;
float valorSensor = 0;
float valorCorrente = 0;
float voltsporUnidade = 0.004887586;// 5%1023
// Consultar o datasheet do ACS712
float sensibilidade = 0.066;

//Tensao da rede AC 220 Volts  na verdade pode variar entre 220v e 250v
int tensao = 242;

void setup() {
  //Incia a Serial para debug
  Serial.begin(9600); 
  pinMode(pinoSensor, INPUT);
}

void loop() {

  for(int i=10000; i>0; i--){
    /* Leitura do  sensor analogico A0  subtraindo o ajuste 
     *  pela metade da resolução (1023)vcc/2 */
    sensorValueAux = (analogRead(pinoSensor) -511.5); 
    // Soma dos quadrados das leituras
    valorSensor += pow(sensorValueAux,2); 
    //Delay para evitar overflow
    delay(1);
  }

  // Calculo da média dos quadrados e conversão para Volts
  valorSensor = (sqrt(valorSensor/ 10000)) * voltsporUnidade; 
  // Calculo da corrente considerando a sensibilidade do sensor (185 mV por ampere) para o sensor de exemplo
  valorCorrente = (valorSensor/sensibilidade); 

  /*Tratamento para possivel ruido
  O ACS712 de 30 Amperes é projetado para fazer leituras
   de valores altos acima de 0.25 Amperes até 30,
   por isso é normal ocorrer ruidos de até 0.20A */
  if(valorCorrente <= 0.098){
    valorCorrente = 0; 
  }

  valorSensor =0;
  
  //Mostra o valor da corrente
  Serial.print("Corrente : ");
  Serial.print(valorCorrente, 3);
  Serial.print(" A ");

  //Calculo da Potência 
  Serial.print(" Potencia (Consumo) : ");
  Serial.print(valorCorrente * tensao);
  Serial.println(" Watts ");
  //Delay para evitar overflow
  delay(100);

}
