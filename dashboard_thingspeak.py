import dash
from dash import dcc, html
import plotly.graph_objects as go
import requests
from datetime import datetime

# Substituir pelo ID do seu canal e pela chave de leitura, se o canal for privado
channel_id = '3071812'
read_api_key = 'FEQ4URUL89VVA0C3'

# URL da API do ThingSpeak
if read_api_key:
    url = f"https://api.thingspeak.com/channels/{channel_id}/feeds.json?results=100&api_key={read_api_key}"
else:
    url = f"https://api.thingspeak.com/channels/{channel_id}/feeds.json?results=100"

# Função para obter e processar os dados do ThingSpeak
def get_thingspeak_data():
    try:
        response = requests.get(url)
        # Lança um erro para status de erro HTTP
        response.raise_for_status()
        data = response.json()
        feeds = data['feeds']
        
        timestamps = []
        temperatures = []
        humidities = []

        for feed in feeds:
            try:
                # Converte a data e hora para um objeto datetime
                timestamps.append(datetime.fromisoformat(feed['created_at'].replace('Z', '+00:00')))
                # 'field1' e 'field2' são os campos de umidade e temperatura, respectivamente.
                humidities.append(float(feed['field1']))
                temperatures.append(float(feed['field2']))
            except (ValueError, TypeError):
                # Ignora entradas com dados inválidos
                continue
        
        return timestamps, temperatures, humidities
    except requests.exceptions.RequestException as e:
        print(f"Erro ao obter dados: {e}")
        return [], [], []

timestamps, temperatures, humidities = get_thingspeak_data()

# Criação dos gráficos com Plotly
fig_temp = go.Figure(data=go.Scatter(x=timestamps, y=temperatures, mode='lines+markers', name='Temperatura'))
fig_temp.update_layout(title='Gráfico de Temperatura (°C)', xaxis_title='Data/Hora', yaxis_title='Temperatura (°C)')

fig_umid = go.Figure(data=go.Scatter(x=timestamps, y=humidities, mode='lines+markers', name='Umidade'))
fig_umid.update_layout(title='Gráfico de Umidade (%)', xaxis_title='Data/Hora', yaxis_title='Umidade (%)')

# Cria a aplicação Dash
app = dash.Dash(__name__)

# Define o layout do dashboard
app.layout = html.Div(children=[
    html.H1(children='Dashboard de Dados do ThingSpeak'),
    html.Div(children='Visualização de dados de umidade e temperatura.'),
    
    dcc.Graph(
        id='temperature-graph',
        figure=fig_temp
    ),
    
    dcc.Graph(
        id='humidity-graph',
        figure=fig_umid
    )
])

if __name__ == '__main__':
    app.run_server(debug=True)