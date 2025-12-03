/*
  Projeto: Envio de Dados de Sensores (DHT22 e LDR) para o ThingSpeak - Versão ESP32
  Placa: ESP32 DevKit V1
  
  Descrição:
  Este código se conecta a uma rede Wi-Fi, lê a Temperatura (DHT22) e a Luminosidade (LDR),
  e envia esses dois valores para os Fields 1 (Temperatura) e 2 (Luminosidade) do seu canal ThingSpeak.
  
  IMPORTANTE: O Field 2 no seu canal ThingSpeak (3071812) está atualmente configurado como "Umidade". 
  O código enviará a LUMINOSIDADE para ele. Certifique-se de mudar o nome do Field 2 no ThingSpeak para "Luminosidade"
  para evitar confusão na visualização.
*/

// --- 1. Bibliotecas Necessárias ---
#include <WiFi.h>        // Biblioteca Wi-Fi nativa do ESP32
#include "DHT.h"         // Para a leitura do sensor DHT22
#include <ThingSpeak.h>  // Para simplificar a comunicação com o ThingSpeak

// --- 2. Configurações de Rede e ThingSpeak ---

// Suas credenciais Wi-Fi (já ajustadas)
const char* ssid = "SENAC-Mesh";
const char* password = "09080706";

// Configurações do seu canal ThingSpeak
unsigned long myChannelNumber = 3071812;
const char* myWriteAPIKey = "DU7P3RJKEKMI7OLX"; // Chave de Escrita (Write API Key)

WiFiClient client; // Objeto cliente Wi-Fi

// --- 3. Configurações de Sensores ---

// Pino de dados do DHT (Temperatura) - Pino GPIO 4 é um bom ponto.
#define DHT_DATA_PIN 4 
#define DHTTYPE DHT22 

// Pino Analógico para o LDR (Luminosidade) - Pino GPIO 34 é um pino ADC seguro no ESP32.
#define LDRPIN 34 

// Inicializa o sensor DHT
DHT dht(DHT_DATA_PIN, DHTTYPE);

// Intervalo de tempo entre os envios (em milissegundos). 
const long sendInterval = 20000; // 20 segundos

long lastSendTime = 0;

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

  // Espera a conexão Wi-Fi
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
  
  lastSendTime = millis();
}

// --- 5. Função LOOP: Leitura e Envio de Dados ---
void loop() {
  // Verifica se o tempo de intervalo para envio já passou
  if (millis() - lastSendTime > sendInterval) {
    
    // --- Leitura do Sensor DHT22 (Temperatura) ---
    float t = dht.readTemperature(); // Leitura da Temperatura em Celsius
    
    // --- Leitura do Sensor LDR (Luminosidade) ---
    int l = analogRead(LDRPIN); // Leitura do valor ADC (0 a 4095 no ESP32)
    
    // --- Verificação de Erros de Leitura ---
    
    if (isnan(t)) {
      Serial.println("Erro: Falha na leitura da Temperatura (DHT)! Tentando novamente.");
      return; 
    }
    
    // --- Exibição no Serial Monitor ---
    
    Serial.print("Temperatura: "); Serial.print(t); Serial.println(" °C");
    Serial.print("Luminosidade: "); Serial.print(l); Serial.println(" (ADC)");
    
    // --- Envio de Dados para o ThingSpeak ---
    
    // Field 1: Temperatura
    ThingSpeak.setField(1, t);
    // Field 2: Luminosidade (Enviada para o Field 2, que antes era Umidade)
    ThingSpeak.setField(2, (float)l); 
    
    // Envia os dados e verifica o código de resposta
    int httpCode = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);

    if (httpCode == 200) {
      Serial.println("Envio para ThingSpeak bem-sucedido.");
    } else {
      Serial.print("Erro ao enviar para ThingSpeak. Código de erro: ");
      Serial.println(httpCode);
    }

    lastSendTime = millis(); 
  }
  
  delay(100); 
}
