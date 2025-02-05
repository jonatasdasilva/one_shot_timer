# 📇 Projeto: Temporizador One Shot

Desenvolvimento um temporizador, o qual é acionado a partir de clique em um botão, sendo utilizado um **Raspberry Pi Pico W (RP2040)** para construção da solução em embarcados.

## 🎯 Objetivo

Projetar um sistema de temporização para o acionamento de LEDs, que atua a partir do clique em um botão (pushbutton).

E ao clicar o botão, um temporizador é iniciado para acender todos os LEDs, e após 3 segundos apagar cada um deles na sequência: azul, vermelho e verde, e impedindo que ao pressionar o botão ele permita realizar a mesma ação, ates de que todos os LEDs sejam desligados.

## 🛠️ Dispositivos utilizados

Para o projeto serão utilizados os seguintes dispositivos:

- 1️⃣ Microcontrolador **Raspberry Pi Pico W**;
- 2️⃣ 03 LEDs (vermelho, amarelo e verde);
- 3️⃣ 03 Resistores de 330 Ω;
- 4️⃣ Botão (Pushbutton).
  
## 📌 Requisitos

- 1️⃣ Caso o usuário clique no botão (pushbutton), os três LEDs serão ligados (todos em nível alto). A partir da primeira rotina de atraso, ocorrerá uma mudança de estado para dois LEDs ligados e, em seguida, apenas um;
- 2️⃣ O temporizador do alarme deve ser ajustado para um atraso de 3 segundos (3.000ms), entre os estados de acionamento dos LEDs;
- 3️⃣ A mudança de estado dos LEDs deve ser implementa em funções de call-back do temporizador, a exemplo da rotina trabalhada na aula síncrona - `turn_off_callback()`;
- 4️⃣ O botão só pode alterar o estado dos LEDs quando o último LED for desligado. Deste modo, durante a execução das rotinas de temporização, o botão não pode iniciar uma nova chamada da função call-back;
- 5️⃣ Com o emprego da Ferramenta Educacional BitDogLab, faça um experimento com o código deste exercício utilizando o LED RGB – GPIOs 11, 12 e 13 e o Botão A, GPIO 05;
- 6️⃣ Opcional: Implementar uma rotina em software para atenuação do efeito bouncing no botão (software debounce).

## 👨🏽‍💻 Desenvolvimento

### 🧩 Funcionalidades

 - 1️⃣ Pressionar o botão liga todos os LEDs imediatamente;
 - 2️⃣ Os LEDs permanecem acesos por 3 segundos;
 - 3️⃣ Após os 3 segundos, os LEDs se apagam em sequência (um a cada segundo);
 - 4️⃣ Os LEDs são apagados na sequência: Azul, vermelho e verde, respectivamente;
 - 5️⃣ Se o botão for pressionado durante o desligamento, os LEDs não são acesos imediatamente até que um novo ciclo possa ser iniciado.

### ✍🏻 Entendendo o código

#### 🔄 Variáveis globais

- `interruption`: Impede que o botão reative os LEDs enquanto ainda estão nos 3 segundos iniciais;
- `timer`: armazenar o timer repetitivo, para apagar os leds;
- `leds_para_desligar`: determina qual LED será apagado.

#### ƒ Funções

- `inicialization_pins`: função que inicializa os LEDs como saída e o botão como entrada com pull-up;
- `turn_on_leds`: acende os três LEDs simultaneamente;
- `turn_led_on_callback`: função que é acionada após três segundos, e inicializa o temporizador repetitivo, para desligar os LEDs um por um;
- `turn_led_off_callback`: função para callback para o temporizador repetitivo, onde desliga um LED a cada segundo, obedecendo a sequência: Azul, vermelho e verde. E libera o botão após todos os LEDs serem desligados;
- `turn_off_led`: desliga o LED desejado da sequência de desligamento.

#### ⚡ Conexões

| Componente | GPIO |
| ---------- | ---- |
| LED Vermelho | 13 |
| LED Azul | 12 |
| LED Verde | 11 |
| Botão | 5 |
| | |


## ☑️ Conclusão

Com o projeto é possível aprender sobre temporizadores e temporizadores repetitivos, permitindo a compreensão e entendimento dos conceitos empregados.

## 🌟 Créditos

Desenvolvido por Jônatas da Silva, como parte de um projeto prático, onde é usado o microcontrolador Raspberry Pi Pico W (RP2040). Na iniciativa do projeto **EmbarcaTech**.