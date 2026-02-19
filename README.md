# Sistema de Indexação de CPFs v2.0 - Árvore AVL & Lista Encadeada 🌳📄

![Language](https://img.shields.io/badge/language-C-blue)
![Course](https://img.shields.io/badge/course-Estrutura%20de%20Dados-green)
![Institution](https://img.shields.io/badge/USP-ICMC%2FEESC-orange)

## 📖 Sobre o Projeto (Remake - TP03)

Este projeto é uma **continuação e evolução direta do trabalho anterior**. A principal atualização desta versão é a substituição da Árvore Binária de Busca (ABO não balanceada) por uma **Árvore AVL (Ordenada e Balanceada)**. 

Desenvolvido para a disciplina **SSC0603 - Estrutura de Dados I** (USP-ICMC), o software implementa uma solução de alta performance integrando o balanceamento automático da AVL com a capacidade de armazenamento de uma Lista Dinâmica Encadeada (LDE).

## 🎯 Definição do Problema e Lógica

O programa processa um arquivo CSV (`basedados.csv`) contendo registros de pessoas (CPF, Código de Verificação, Data de Nascimento e Nome). O objetivo é criar um "índice" de acesso ultra-rápido para os dados completos.

A lógica de integração funciona da seguinte maneira:

1.  **Armazenamento Completo (Lista LDE):** Todos os dados lidos do CSV são inseridos *sempre no início* de uma **Lista Dinâmica Encadeada**, garantindo um custo de inserção de pior caso de O(1).
2.  **Indexação Balanceada (Árvore AVL):** Apenas o CPF (9 dígitos) é inserido na **Árvore AVL**. Graças ao balanceamento automático (rotações), as buscas ocorrem em tempo logarítmico, mesmo no pior caso: custo de consulta O(log N) e inserção O(N log N).
3.  **Ponteiro Cruzado (Link de Acesso):** Ao inserir o registro na LDE, o programa obtém o ponteiro desse nó e o armazena dentro do nó correspondente na árvore AVL. Assim, após encontrar o CPF na árvore, o acesso aos dados complementares na LDE ocorre em apenas 1 passo (custo O(1)).

## 🛠️ Tecnologias e Conceitos

* **Linguagem C** (Padrão ANSI).
* **Árvore AVL:** Balanceamento automático usando Fator de Balanceamento e Rotações (LL, RR, LR, RL) para otimização de busca.
* **Lista Dinâmica Encadeada (LDE):** Armazenamento sequencial robusto (inserção O(1) no início).
* **Integração de Estruturas:** Ponteiros conectando os nós "índices" da AVL aos "blocos de dados" da LDE.
* **Manipulação de Arquivos:** Leitura de `.csv` e geração estruturada de três relatórios `.txt`.

## 📂 Estrutura do Repositório

* `main.c`: Orquestra o fluxo principal, menu de opções e chamadas das funções.
* `ArvoreAVL.c` / `.h`: Implementação da Árvore AVL, rotações, balanceamento e caminhamentos (Em Ordem e Pré-Ordem).
* `LDED.c` / `.h`: Implementação da Lista Dinâmica (neste caso, duplamente encadeada).
* `basedados.csv`: Arquivo de entrada com os dados brutos e flag de parada `-1`.

## ⚙️ Funcionalidades e Saídas

O programa apresenta no console métricas da árvore (total de nós, altura, e os dados do primeiro e último elementos na ordem). 

Através do menu de entrada, o programa opera em dois modos:
1.  **Modo 1:** Executa a leitura, constrói as estruturas em memória e gera silenciosamente os arquivos de saída.
2.  **Modo 2:** Executa todo o processo do Modo 1 e, ao final, utiliza o comando `system("cat...")` para exibir automaticamente no terminal o conteúdo dos três arquivos gerados.

**Arquivos Gerados:**
* `dados1.txt`: Conteúdo completo da LDE (inserções no início).
* `dados2.txt`: CPFs da árvore impressos no percurso **Em Ordem**.
* `dados3.txt`: Estrutura da árvore impressa em **Pré-Ordem**, exibindo detalhadamente a raiz e seus respectivos filhos (Esquerdo e Direito) ou `NULL`.

## 🚀 Como Compilar e Executar

Para compilar o projeto, utilize um compilador GCC.

### 1. Compilação
Abra o terminal na raiz do projeto e execute:

```bash
gcc main.c ArvoreAVL.c LDED.c -o programa
```

### 2. Execução

```bash
./programa
```
