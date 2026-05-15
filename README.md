# Geração de Animações em uma Matriz de LEDs 5x5 no RP2040

Projeto acadêmico desenvolvido para o Curso de Graduação em Engenharia Elétrica da Universidade Federal do Vale do São Francisco (UNIVASF) — Juazeiro, BA, 2026.

---

## Equipe

| Papel | Nome |
|---|---|
| **Líder** | Ítalo Gustavo Vieira Souza |
| Colaborador | Anderson Luiz Barreto |
| Colaboradora | Maria Clara de Souza Silva |
| Colaborador | Thyago Torres de Castro Gama |

**Orientador:** Prof. Dr. Ricardo Menezes Prates

---

## Descrição

Este projeto tem como objetivo o desenvolvimento de animações visuais em uma matriz de LEDs RGB 5x5 WS2812, utilizando o microcontrolador Raspberry Pi Pico W (RP2040) e a linguagem C com o Pico SDK. O desenvolvimento foi realizado no VS Code integrado ao simulador Wokwi, permitindo a simulação completa do sistema embarcado antes da execução em hardware real.

---

## Objetivos

- Controlar uma matriz de LEDs RGB 5x5 WS2812 via RP2040;
- Implementar duas animações distintas acionadas pelos botões A e B da placa BitDogLab;
- Aplicar técnica de debounce por software para evitar leituras indevidas nos botões;
- Utilizar o ambiente VS Code integrado ao simulador Wokwi para desenvolvimento e testes;
- Praticar versionamento de código com Git e GitHub.

---

## Materiais Utilizados

- Placa BitDogLab (Botões A e B)
- Microcontrolador Raspberry Pi Pico W (RP2040)
- Matriz de LEDs WS2812 5x5 (RGB)
- VS Code com simulador Wokwi

---

## Desenvolvimento do Firmware

O firmware foi escrito em C utilizando o Pico SDK. As etapas de desenvolvimento foram as seguintes:

**1. Configuração de hardware:** definição dos pinos dos botões A e B como entradas digitais com resistores de pull-up internos habilitados, e configuração do pino de dados responsável pela comunicação com a matriz de LEDs.

**2. Funções auxiliares implementadas:**
- Acender LEDs específicos da matriz;
- Atualizar o estado de todos os LEDs;
- Limpar a matriz (apagar todos os LEDs);
- Definir cores no padrão RGB.

**3. Animações:** foram desenvolvidas duas animações distintas, cada uma composta por no mínimo cinco frames, com atrasos de tempo entre eles para produzir o efeito visual de movimento.
- Botão A: colunas de LEDs vermelhos percorrem a matriz sequencialmente.
- Botão B: expansão progressiva de LEDs azuis a partir do centro em direção às bordas, culminando no preenchimento total da matriz.

**4. Debounce por software:** implementado com temporização em milissegundos, com janela de 250 ms, garantindo que apenas acionamentos válidos sejam reconhecidos pelo sistema.

**5. Loop principal:** estrutura `while(true)` responsável por monitorar continuamente o estado dos botões e acionar a animação correspondente ao pressionamento detectado.

---

## Como Testar

### Pré-requisitos

- [VS Code](https://code.visualstudio.com/) instalado;
- Extensão [Wokwi for VS Code](https://marketplace.visualstudio.com/items?itemName=wokwi.wokwi-vscode) instalada;
- [Pico SDK](https://github.com/raspberrypi/pico-sdk) configurado no ambiente;
- CMake e compilador ARM GCC instalados.

### Compilação

1. Clone o repositório e acesse a pasta do projeto;
2. Crie o diretório de build e compile o projeto:

```bash
mkdir build
cd build
cmake ..
make
```

3. O arquivo `.uf2` gerado estará disponível na pasta `build/`.

### Simulação no Wokwi

1. Abra o projeto no VS Code;
2. Certifique-se de que o arquivo `diagram.json` está configurado com a placa Raspberry Pi Pico W, a matriz WS2812 5x5 no pino GP7, e os botões nos pinos GP5 (botão A) e GP6 (botão B);
3. Inicie a simulação pela extensão Wokwi;
4. Com a simulação ativa:
   - Clique no **botão A** (GP5) para acionar a animação vermelha — colunas de LEDs percorrem a matriz sequencialmente;
   - Clique no **botão B** (GP6) para acionar a animação azul — LEDs se expandem progressivamente do centro até o preenchimento total da matriz.

### Execução em Hardware Real

1. Conecte o Raspberry Pi Pico W ao computador via cabo USB enquanto mantém pressionado o botão **BOOTSEL**, para entrar no modo de gravação;
2. Copie o arquivo `.uf2` gerado para o dispositivo de armazenamento que aparecer;
3. O microcontrolador reiniciará automaticamente e o firmware estará em execução;
4. Pressione o **botão A** ou o **botão B** da placa BitDogLab para acionar as respectivas animações.

### Observações

- O debounce está configurado para **250 ms**, de modo que pressionamentos muito rápidos e sucessivos serão ignorados;
- Cada animação é composta por **5 frames** com intervalos de 200 ms (animação vermelha) e 180 ms (animação azul) entre os frames;
- Após a conclusão de cada animação, a matriz é apagada automaticamente.

---

## Conclusão

A implementação das animações na matriz de LEDs 5x5 foi concluída com sucesso. O sistema exibiu os frames visuais conforme planejado, mantendo a temporização e a fluidez desejadas. A comunicação com a matriz de LEDs ocorreu sem falhas, garantindo controle preciso de cada ponto de luz. A lógica de software manteve-se estável durante toda a execução, sem atrasos ou travamentos. O projeto validou a eficiência da arquitetura escolhida e estabelece uma base sólida para expansões futuras.
