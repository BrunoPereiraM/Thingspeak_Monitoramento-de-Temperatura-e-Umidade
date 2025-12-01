📌 Guia de Configuração de Hardware e Sensores

Este guia detalha como conectar os sensores DHT22 (Temperatura e Umidade) e LDR (Luminosidade) ao seu microcontrolador ESP8266 para que o código de envio de dados para o ThingSpeak funcione corretamente.

⚠️ Pré-requisitos de Fiação

Certifique-se de que os sensores estejam conectados em uma protoboard (breadboard) ou placa de circuito impresso e que todos os componentes estejam devidamente aterrados e alimentados.

1. Conexão do Sensor DHT22

O DHT22 é um sensor digital. Seu pino de dados deve ser conectado a uma das portas digitais do ESP8266.

2. Conexão do Sensor LDR

O Sensor de Luminosidade LDR é analógico e requer um resistor pull-down ou divisor de tensão (geralmente um resistor de $10\text{k}\Omega$) para funcionar corretamente. O pino de sinal deve ser conectado à única porta analógica do ESP8266 (A0).

🔌 Diagrama de Conexão Lógica

Para que o código funcione com as definições padrão, siga a tabela abaixo.

Componente

Pino do Sensor

Pino do ESP8266

Função/Observações

Configuração no Código

DHT22

Dados (Data)

D2 (GPIO4)

Leitura Digital de T/U

#define DHTPIN D2

LDR

Sinal Analógico (Resistor Divisor)

A0 (Analógico)

Leitura Analógica de Luminosidade ($0-1023$)

#define LDRPIN A0

Ambos

VCC

3.3V

Alimentação Elétrica



Ambos

GND

GND

Aterramento



📝 Observação Importante

O pino D2 no ESP8266 corresponde ao GPIO4 no chip. As bibliotecas modernas do Arduino IDE para ESP8266 permitem que você use a notação D2 diretamente no código, como está definido em thingspeak_uploader.ino.
