Controle de LEDs com Temporização e Botão no Raspberry Pi Pico W
link do video de teste: https://drive.google.com/file/d/1RaUQSDWSgJUtHV7M4YU71WE2EDgZTSkI/view?usp=drivesdk

Este projeto implementa um sistema de controle de LEDs utilizando um Raspberry Pi Pico W e a ferramenta BitDogLab. O objetivo principal é gerenciar o acionamento sequencial de três LEDs a partir do pressionamento de um botão, garantindo um intervalo de tempo fixo entre cada mudança de estado. Para isso, o código utiliza um temporizador de um disparo (One-Shot Timer) que controla os LEDs de forma automática após a ativação pelo botão.

Funcionamento do Código

O sistema inicia aguardando o pressionamento do botão. Assim que o botão é acionado, os LEDs sao ligados ligados sequencialmente com um intervalo de 3 segundos entre cada etapa. Durante esse período, o botão fica desativado para evitar múltiplas ativações simultâneas. Após a conclusão do ciclo, onde todos os LEDs foram desligados, o botão é reativado, permitindo uma nova execução.

A sequência de funcionamento dos LEDs ocorre da seguinte forma:
	
 1.	O botão é pressionado, iniciando a ativação dos LEDs.
	
 2.	Todos os LEDs acendem ao mesmo tempo.

 3.	Após 3 segundos, o LED azul é desligado.

 4.	Após mais 3 segundos, o LED vermelho é desligado.

 5.	Após mais 3 segundos, o LED verde é desligado.

 6.	O botão é reativado, permitindo uma nova execução do ciclo.


Componentes Utilizados

 •	Raspberry Pi Pico W

 •	3 LEDs:

 •	Azul conectado ao GPIO 11

 •	Vermelho conectado ao GPIO 12
	
 •	Verde conectado ao GPIO 13
	
 •	1 Botão (Pushbutton)

 •	Conectado ao GPIO 5

 •	3 Resistores de 330Ω (para limitar a corrente dos LEDs)


Desenvolvimento do Código

O código é organizado em três partes principais:

1. Configuração dos Pinos

Os pinos dos LEDs e do botão são configurados de acordo com suas funções. Os LEDs são definidos como saídas, enquanto o botão é configurado como entrada com um pull-up interno, garantindo uma leitura estável e evitando acionamentos errados.

2. Interrupção do Botão

O botão utiliza uma interrupção configurada para detectar a borda de descida do sinal (quando o botão é pressionado). Assim que pressionado, a interrupção chama a função responsável por iniciar a sequência dos LEDs e, ao mesmo tempo, desativa temporariamente o botão até que todo o ciclo seja concluído.

3. Controle dos LEDs via Temporizador

A sequência de LEDs é gerenciada por um temporizador de um disparo (One-Shot Timer). Após o acionamento pelo botão, o temporizador inicia e chama a função de controle dos LEDs a cada 3 segundos, garantindo que os LEDs sejam desligados de forma escalonada. Quando todos os LEDs são apagados, o sistema reativa a interrupção do botão, permitindo uma nova execução.

Execução do Programa

Após carregar o código no Raspberry Pi Pico W, o sistema fica aguardando o pressionamento do botão. Assim que o botão é acionado, os LEDs começam a acender e apagar conforme a sequência programada. Durante esse período, o botão permanece desativado para evitar acionamentos sucessivos antes da finalização do ciclo.

O funcionamento esperado do sistema é:
	
 •	Botão pressionado → LEDs acendem em sequência

 •	LEDs apagam um por um a cada 3 segundos
	
 •	Botão desativado durante o ciclo
	
 •	Botão reativado após o último LED ser desligado
