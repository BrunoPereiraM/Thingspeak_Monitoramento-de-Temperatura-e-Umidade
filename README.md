# Dashboard de Monitoramento de Ambiente

Este projeto consiste em um dashboard simples para visualizar dados de temperatura e umidade de um canal do ThingSpeak, utilizando Python e a biblioteca Dash.

## Pré-requisitos
Certifique-se de ter o Python instalado. As bibliotecas necessárias estão listadas no arquivo `requirements.txt`. Você pode instalá-las com o seguinte comando:

```pip install -r requirements.txt```

## Configuração
1.  Substitua `SUA_ID_DO_CANAL` e `SUA_CHAVE_DE_LEITURA` no arquivo `dashboard_thingspeak.py` pelas suas próprias credenciais do ThingSpeak.
2.  Certifique-se de que seu canal do ThingSpeak esteja enviando dados de umidade (campo 1) e temperatura (campo 2).

## Como Rodar
Execute o script Python a partir da linha de comando:

```python dashboard_thingspeak.py```

O dashboard estará disponível em `http://127.0.0.1:8050/` no seu navegador.