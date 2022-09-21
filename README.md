# Controlador de Sensores Distribuídos

Trabalho 3 referente à disciplina de Sistemas Embarcados da Universidade de Brasília

## Participantes

- [Emily Dias](https://github.com/emysdias) - 180015966
- [Vitor Lamego](https://github.com/VitorLamego) - 190020903


## Execução

O projeto foi realizado utilizando o framework do Espressif, os passos iniciais de configuração foram realizados utilizando esta [documentação](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/get-started/linux-macos-setup.html). A versão utilizada foi ESP-IDF v5.1-dev-776-g5b39159e66.

Com a esp-idf instalada na máquina, rode os seguintes comandos para executar o programa:

```
. $HOME/esp/esp-idf/export.sh
OBS: Se a pasta "esp" não estiver na HOME, coloque o caminho onde foi clonado o código da esp-idf!
```

```
idf.py build
```

```
idf.py menuconfig

No menu "Configurações do Wifi" coloque a sua rede Wifi Local, preenchendo o ssid e a senha.
```

```
idf.py -p /dev/[tty.usbserial-0001] flash monitor

No meu caso a esp conectada aparecia como tty.usbserial-0001, mas isso pode ser diferente, para verificar rode o comando:

ls /dev/
```

Pronto! O seu programa será executado.

## Light-Sleep Mode

O programa também pode ser executado em modo Light-Sleep, assim fica dormindo até que um dos sensores a acorde. Para executar o programa nesse modo, rode o seguinte comando:

```
idf.py menuconfig

No menu Low Power Mode digite 1 para ligar o modo ou deixe em 0 para deixar desligado
```

Basta rodar os comandos comentados anteriormente e o seu programa será executado em Light-Sleep.


## Sensores utilizados


### DHT11

<img src="/images/dht11.jpeg" alt="drawing" width="350"/>

Sensor para leitura de temperatura e umidade.

### KY-003

<img src="/images/ky003.jpeg" alt="drawing" width="350"/>

Sensor Hall Magnético Digital para leitura de presença de campo magnético.

### KY-036

<img src="/images/ky036.jpeg" alt="drawing" width="350"/>

Sensor de toque