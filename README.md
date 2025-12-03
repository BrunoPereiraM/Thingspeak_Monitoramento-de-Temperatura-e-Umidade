# 🌡️ Monitoramento de Temperatura e Luminosidade (IoT)

Este projeto utiliza um **ESP32 DevKit V1** para coletar dados de **temperatura (DHT22)** e **luminosidade (LDR)**, enviando tudo automaticamente para a plataforma **ThingSpeak**, onde é possível visualizar gráficos e analisar os dados em tempo real.

------------------------------------------------------------

## 🎯 Objetivo

Criar um sistema IoT simples e funcional que:

- Leia **temperatura** através do sensor **DHT22**
- Leia **luminosidade** através de um sensor **LDR**
- Envie os dados periodicamente para um canal **ThingSpeak**
- Permita monitoramento remoto e histórico dos valores coletados

------------------------------------------------------------

## 💻 Hardware Utilizado

| Componente | Função |
|-----------|--------|
| **ESP32 DevKit V1** | Microcontrolador Wi-Fi |
| **DHT22** | Sensor de temperatura |
| **Sensor LDR** | Medição de luminosidade |
| **Resistor** | Divisor de tensão para o LDR |
| **Jumpers** | Conexões gerais |

------------------------------------------------------------

## 🛠️ Configuração e Instalação

### 1. Arduino IDE

- Ferramentas → Placa → **ESP32 Dev Module**
- Instalar bibliotecas:
  - **DHT sensor library**
  - **ThingSpeak**
  - **ESP32 Board Package**

------------------------------------------------------------

### 2. Guia de Conexão (Fiação)

| Componente | Pino do Componente | GPIO no ESP32 | Observações |
|------------|---------------------|---------------|-------------|
| **DHT22** | Data | **GPIO 4** | Leitura digital da temperatura |
| **LDR** | Sinal | **GPIO 34** | Leitura analógica (ADC) |
| **Ambos** | VCC | **3.3V** | Alimentação |
| **Ambos** | GND | **GND** | Aterramento |

*Obs.: O LDR requer um divisor de tensão com resistor.*

------------------------------------------------------------

## 🌐 Configuração do Código  
Arquivo: **thingspeak_t_l_esp32_final.ino**

Configure antes de enviar para o ESP32:

| Variável | Função |
|----------|--------|
| `ssid` | Nome do Wi-Fi |
| `password` | Senha do Wi-Fi |
| `myChannelNumber` | ID do canal: **3071812** |
| `myWriteAPIKey` | Write API Key: **DU7P3RJKEKMI7OLX** |

------------------------------------------------------------

## 📊 Campos no ThingSpeak

| Field | Conteúdo |
|-------|-----------|
| **Field 1** | Temperatura (°C) |
| **Field 2** | Luminosidade (ADC 0–4095) |

------------------------------------------------------------
