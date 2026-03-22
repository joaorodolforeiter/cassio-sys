# Book Store - Calculo de Entrega

Projeto em C++ para calcular frete de pedidos da livraria conforme regras de PAC, Sedex e Retirada na loja.

## Regras implementadas

- **PAC**
  - ate 1 kg: R$ 10,00
  - acima de 1 kg ate 2 kg: R$ 15,00
  - acima de 2 kg: nao aceita
- **Sedex**
  - ate 500 g: R$ 12,50
  - acima de 500 g ate 1000 g: R$ 20,00
  - acima de 1 kg: R$ 46,50 + R$ 1,50 por cada 100 g adicional
- **Retirada na loja**
  - sem custo

## Build

```bash
cmake -S . -B build
cmake --build build
```

## Executar exemplo

```bash
./build/book_store_app
```

## Executar testes

```bash
ctest --test-dir build --output-on-failure
```

ou

```bash
./build/book_store_tests
```

