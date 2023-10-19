# Padrões a serem seguidos

## ******************************Padrões de GIT******************************

**Mensagem dos Commits**: *(Conventional commits)*

- “**feat**: …” para novas implementações
- “**fix**: …” para correções
- “**refact**: …” para refatorações
- “**chore**: …” para tarefas gerais

**Criação de Branches**:

- **feature/nome-da-branch** para novas implementações
- **patch/nome-da-branch** para correções, refatorações e adaptações
- **breaking/nome-da-branch** para alterações muito grandes, exemplo mudar uma biblioteca muito usada

# Especificação do Trabalho Parte 1: Funcionalidades básicas em grafos simples

Este documento traz a especificação do Trabalho 1, atividade avaliativa do tipo "Trabalho Prático", e serve de base
para todas as atividades de implementação cobradas ao longo do curso da disciplina **DCC059 - Teoria dos Grafos** no
semestre letivo 2023-2.

## Objeto
Desenvolver um Tipo Abstrato de Dados - TAD ou uma Classe que represente grafos simples, orientados e
não orientados, ponderados e não ponderados (nos vértices e arestas) e implemente o conjunto de funcionalidades
apresentadas a seguir.

## Orientações
- O TAD ou Classe deve ser capaz de representar grafos utilizando lista de adjacência.
- O código deve ser desenvolvido em linguagem C ou C++ e não devem ser usadas funções que não sejam nativas
  da linguagem.
- A clareza e organização do código serão avaliadas, incluindo nomes de funções, variáveis e comentários explicativos.
- O programa principal deve ler os dados do grafo de entrada a partir de um arquivo de texto.
- A informação sobre o tipo de grafo (direcionado ou não direcionado) deve ser passada ao programa por parâmetro via linha de comando.
- Cada grupo enviará um único e-mail com os arquivos fonte e os arquivos de entrada utilizados.
- O padrão de compilação e execução será fornecido.

## Funcionalidades
O programa deve oferecer as seguintes funcionalidades:
- [x] Fecho transitivo direto de um vértice.
- [x] Fecho transitivo indireto de um vértice.
- [x]Caminho mínimo entre dois vértices usando algoritmo de Dijkstra.
- [x]Caminho mínimo entre dois vértices usando algoritmo de Floyd.
- Árvore Geradora Mínima usando o algoritmo de Prim.
- Árvore Geradora Mínima usando o algoritmo de Kruskal.
- Árvore de caminhamento em profundidade a partir de um nó, destacando as arestas de retorno.
- Ordenação topológica ou indicação de que o grafo não é acíclico direcionado.
- Raio, diâmetro, centro e periferia do grafo ponderado nas arestas.
- Conjunto de vértices de articulação.
- Cada saída deve ser apresentada na tela e o usuário poderá optar por salvar a saída em arquivo.
- O programa deve apresentar um menu de opções e repetir até que o usuário escolha sair.

## Perguntas Frequentes
1. Quantos membros um grupo pode ter?
   O trabalho pode ter no máximo 4 pessoas.

2. Se eu fizer alguma parte 1 do trabalho individualmente ou em grupo, terei que fazer a parte 2 correspondente ao assunto da Unidade 6 da mesma forma (mesmo grupo)?
   Sim, a avaliação considera todas as funcionalidades.

3. O projeto poderá ter mais de um arquivo fonte?
   Sim, é permitido e recomendado para organização.

4. O que será levado em conta na correção?
   Interação com o professor, conformidade com a especificação, correção da implementação, eficiência e organização do código.

5. Por que a especificação de como o programa será executado é importante?
   Para garantir que o pré-processamento seja automatizado.

6. O que acontece se a especificação de execução do programa não for corretamente observada?
   Haverá desconto na nota.

7. Meu trabalho tem um bug. O que vai acontecer com minha nota?
   Deve ser informado no relatório e haverá desconto, dependendo da gravidade.

8. Meu código não compila. Posso enviar assim mesmo?
   Não, trabalhos com erros de compilação não serão avaliados.

9. Tenho outra pergunta/dúvida a respeito do trabalho.
   Procure o professor para esclarecer suas dúvidas.
