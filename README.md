# FarmTech Solutions – Sistema de Irrigação Inteligente

## Visão Geral

Este projeto simula um sistema de irrigação inteligente utilizando sensores agrícolas e um microcontrolador ESP32. O sistema coleta dados de sensores simulados, controla uma bomba de irrigação e armazena os dados em um banco SQL para análise posterior.

## Componentes do Circuito

- **Sensor de Fósforo (P):** Botão físico (pressionado = presença, solto = ausência)
- **Sensor de Potássio (K):** Botão físico (mesma lógica do fósforo)
- **Sensor de pH:** LDR (Light Dependent Resistor), valor analógico mapeado para faixa de pH (0-14)
- **Sensor de Umidade:** DHT22, retorna umidade do solo em tempo real
- **Bomba de Irrigação:** Relé controlado pelo ESP32, com LED indicador de status

## Lógica de Controle

- A bomba é ligada automaticamente se:
  - Umidade do solo < 40%
  - Fósforo e Potássio presentes (botões pressionados)
- O status da bomba é indicado por um LED.
- Todos os dados dos sensores e o status da bomba são exibidos no monitor serial.


## Armazenamento de Dados (Python + SQLite)

- Os dados exibidos no monitor serial podem ser copiados e inseridos em um banco SQLite via script Python.
- O script implementa operações CRUD (Create, Read, Update, Delete) para as leituras dos sensores.

### Estrutura da Tabela (MER Simplificado)

| Campo     | Tipo     | Descrição                       |
|-----------|----------|---------------------------------|
| id        | Inteiro  | Chave primária                  |
| fosforo   | Booleano | Presença de fósforo             |
| potassio  | Booleano | Presença de potássio            |
| ph        | Real     | Valor do pH                     |
| umidade   | Real     | Umidade do solo (%)             |
| bomba     | Booleano | Status da bomba (ligada/desligada) |
| data_hora | Timestamp| Data e hora da leitura          |

## Como Executar

1. **ESP32:** Compile e envie o código `main.cpp` para o ESP32 usando PlatformIO ou Arduino IDE.
2. **Python:** Execute `sensores_db.py` para simular o armazenamento e manipulação dos dados no banco SQL.



## Justificativa da Estrutura

A estrutura da tabela foi baseada no MER da Fase 2, representando cada sensor como um campo e relacionando as leituras ao controle da bomba. Isso permite análises estatísticas e rastreamento histórico das condições do solo.

---
