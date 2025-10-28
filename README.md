# Primitivas Gráficas - Computação Gráfica

Este projeto apresenta a implementação de quatro algoritmos de primitivas gráficas, desenvolvidos como parte de um trabalho de Computação Gráfica. A aplicação utiliza a biblioteca SDL para renderização e demonstra a funcionalidade dos algoritmos desenhando uma casa com um sol.

## Algoritmos Implementados

Foram implementados os seguintes algoritmos de primitivas gráficas:

1.  **Linha Ponto Médio (Midpoint Line Algorithm):** Algoritmo eficiente para rasterizar linhas em uma grade de pixels;
2.  **Cohen-Sutherland:** Algoritmo de recorte de linha que determina quais partes de uma linha são visíveis dentro de uma janela retangular;
3.  **Polígono:** Algoritmo para desenhar um polígono;
4.  **Scanline (Preenchimento por Varredura):** Algoritmo detalhado para preenchimento de polígonos, que varre o objeto linha por linha.

## Resultado Esperado

Ao executar a aplicação, você verá uma janela SDL que desenha uma casa com um telhado marrom, paredes beges, uma porta marrom, e uma janela com divisões, tudo sob um céu azul com um sol laranja e um chão verde.

![Exemplo de uso das primitivas](./aplicacao-demo.png)

## Como Executar

Para executar a aplicação, siga os passos abaixo:

1.  **Navegue até a pasta `build`:**
    ```bash
    cd build
    ```

2.  **Execute o arquivo `.exe`:**
    ```bash
    ./trabalho_01.exe
    ```
    
## Requisitos

* Sistema operacional compatível com executáveis Windows.