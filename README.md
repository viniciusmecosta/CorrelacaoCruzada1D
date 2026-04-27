# Correlação Cruzada 1D

Implementação em ANSI C do algoritmo de correlação cruzada, com validação automatizada em Python.

## Como Executar

1. **Compilar o projeto:**
   ```bash
   make
   ```

2. **Gerar sinais e processar em C:**
   ```bash
   ./build/test_suite
   ```

3. **Validar os resultados em Python:**
   ```bash
   python test.py
   ```

## Estrutura de Testes

* **test1_impulso:** Valida o alinhamento e a detecção de atraso temporal.
* **test2_constantes:** Avalia o cálculo de sobreposição e o comportamento nos extremos dos sinais.
* **test3_harmonico:** Executa uma série de 15 testes com senoides variadas para atestar a precisão matemática e o limite numérico das operações em ponto flutuante.