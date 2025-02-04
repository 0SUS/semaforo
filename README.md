# semaforo
# README - Simulação de Semáforo no Raspberry Pi Pico

## Descrição
Este programa simula o funcionamento de um semáforo utilizando três LEDs conectados ao Raspberry Pi Pico. O semáforo segue a sequência tradicional: vermelho, amarelo e verde, com cada estado durando 3 segundos antes da troca.

## Requisitos
- Placa **Raspberry Pi Pico**
- Três LEDs conectados às GPIOs:
  - **LED Vermelho** → GPIO 11
  - **LED Amarelo** → GPIO 12
  - **LED Verde** → GPIO 13
- SDK do Raspberry Pi Pico instalado

## Como Compilar e Executar
1. Clone ou copie este repositório para seu ambiente de desenvolvimento.
2. Compile o código utilizando o **SDK do Pico** e gere o arquivo UF2.
3. Conecte o Raspberry Pi Pico ao computador em **modo bootloader**.
4. Arraste e solte o arquivo UF2 no dispositivo **RPI-RP2**.
5. O código será executado automaticamente após o upload.

## Funcionamento
1. O programa inicia com o **LED vermelho aceso**.
2. Após 3 segundos, o LED vermelho apaga e o **LED amarelo acende**.
3. Após mais 3 segundos, o LED amarelo apaga e o **LED verde acende**.
4. Após mais 3 segundos, o LED verde apaga e o ciclo reinicia com o **LED vermelho aceso**.
5. A saída serial exibe mensagens indicando o estado atual do semáforo.

## Observações
- O programa utiliza um **temporizador periódico** (`add_repeating_timer_ms`) para alternar os LEDs automaticamente.
- A execução do programa pode ser monitorada por um terminal serial via `printf()`.

## Licença
Este código é fornecido sem garantia e pode ser utilizado para fins educacionais e experimentação no Raspberry Pi Pico.

