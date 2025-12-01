/*
  Projeto: Envio de Dados de Sensores (DHT22 e LDR) para o ThingSpeak
  Placa: ESP8266 (NodeMCU, Wemos D1 Mini, etc.)
  
  Descrição:
  Este código se conecta a uma rede Wi-Fi, lê os dados de Temperatura e Umidade
  do sensor DHT22 e o valor analógico de Luminosidade do sensor LDR,
  e envia esses três valores para os Fields 1, 2 e 3 do seu canal ThingSpeak.
*/

// --- 1. Bibliotecas Necessárias ---
#include <ESP8266WiFi.h> // Para conectar o ESP8266 ao Wi-Fi
#include "DHT.h"         // Para a leitura do sensor DHT22
#include <ThingSpeak.h>  // Para simplificar a comunicação com o ThingSpeak

// --- 2. Configurações de Rede e ThingSpeak ---

// Substitua pelas suas credenciais de Wi-Fi
const char* ssid = "SENAC-Mesh";
const char* password = "09080706";

// Configurações do seu canal ThingSpeak
unsigned long myChannelNumber = 3071812; // Substitua pelo número real do seu canal
const char* myWriteAPIKey = "DU7P3RJKEKMI7OLX"; // Chave de Escrita (Write API Key) fornecida

WiFiClient client; // Objeto cliente Wi-Fi

// --- 3. Configurações de Sensores ---

// Define a porta digital onde o pino de dados do DHT está conectado (Ex: D2/GPIO4)
#define DHTPIN D2 
// Define o tipo de sensor DHT (Ex: DHT11, DHT22)
#define DHTTYPE DHT22 

// Define a porta analógica onde o LDR está conectado (Geralmente A0 no ESP8266)
#define LDRPIN A0

// Inicializa o sensor DHT
DHT dht(DHTPIN, DHTTYPE);

// Intervalo de tempo entre os envios (em milissegundos). 
// ThingSpeak geralmente aceita um envio a cada 15 segundos (15000 ms).
long lastSendTime = 0;
const long sendInterval = 20000; // 20 segundos

// --- 4. Função SETUP: Inicialização e Conexão ---
void setup() {
  Serial.begin(115200);
  delay(100);

  // Inicializa o sensor DHT
  dht.begin();
  
  // Conectando ao Wi-Fi
  Serial.print("Conectando a ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi conectado!");
  Serial.print("Endereço IP: ");
  Serial.println(WiFi.localIP());

  // Inicializa o cliente ThingSpeak
  ThingSpeak.begin(client);
  
  lastSendTime = millis(); // Inicializa o contador de tempo
}

// --- 5. Função LOOP: Leitura e Envio de Dados ---
void loop() {
  // Verifica se o tempo de intervalo para envio já passou
  if (millis() - lastSendTime > sendInterval) {
    
    // --- Leitura do Sensor DHT22 ---
    
    // A função 'readHumidity()' e 'readTemperature()' podem levar 250ms ou mais para retornar.
    float h = dht.readHumidity();
    float t = dht.readTemperature(); // Temperatura em Celsius
    
    // --- Leitura do Sensor LDR ---
    
    // O valor do LDR será entre 0 (Escuro) e 1023 (Claro)
    int l = analogRead(LDRPIN); 
    
    // --- Verificação de Erros de Leitura ---
    
    // Verifica se alguma leitura do DHT falhou. Os dados do LDR (l) raramente falham.
    if (isnan(h) || isnan(t)) {
      Serial.println("Erro: Falha na leitura do sensor DHT!");
      return; // Sai do loop para tentar novamente no próximo intervalo
    }
    
    // --- Exibição no Serial Monitor ---
    
    Serial.print("Umidade: "); Serial.print(h); Serial.println(" %");
    Serial.print("Temperatura: "); Serial.print(t); Serial.println(" °C");
    Serial.print("Luminosidade: "); Serial.print(l); Serial.println(" (ADC)");
    
    // --- Envio de Dados para o ThingSpeak ---
    
    // O ThingSpeak espera valores float para os campos
    
    // Field 1: Temperatura
    ThingSpeak.setField(1, t);
    // Field 2: Umidade
    ThingSpeak.setField(2, h);
    // Field 3: Luminosidade
    ThingSpeak.setField(3, (float)l); // Conversão explícita de int para float
    
    // Envia os dados e verifica o código de resposta
    int httpCode = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);

    if (httpCode == 200) {
      Serial.println("Envio para ThingSpeak bem-sucedido.");
    } else {
      Serial.print("Erro ao enviar para ThingSpeak. Código de erro: ");
      Serial.println(httpCode);
    }

    lastSendTime = millis(); // Atualiza o tempo do último envio
  }
  
  delay(100); // Pequena pausa para evitar sobrecarga
}
