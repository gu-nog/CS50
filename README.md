<h1 align="center">
    <a href="https://cs50.harvard.edu/x/2022">🔗 CS50</a>
</h1>
<p align="center">🚀 curso de ciências da computação gratuito e online de Harvard</p>

# Observação:
## Com essas soluções você poderia rapidamente "finalizar o curso", porém se você não fizer esforço para exercitar esses temas, nunca conseguirá realmente aprendê-los. Enviando essas soluções você conseguiria apenas um certificado, que não vale muito sem todo o conhecimento que várias pessoas se esforçaram em disponibilizá-los gratuitamente para todos, e esse conhecimento que é a coisa mais valiosa desse curso. Então, se esforce para criar sua solução para esse problema e aprender todo o valioso conteúdo passado no CS50, se necessário também apenas leia as anotações que fiz das aulas. para saber mais sobre isso clique [aqui](https://cs50.harvard.edu/x/2022/honesty/).

Tabela de conteúdos
=================
<!--ts-->
   * [Aula 1(Scratch)](#aula-1---scratch)
       * [Meu projeto](#meu-projeto-da-aula-1---scratch)
   * [Ferramentas](#tecnologias)
   * [Licença CC](https://cs50.harvard.edu/x/2022/license/)
<!--te-->
# Aula 1 - Scratch
#### Tempo usado: 3h
### Ensinamento: ciência da computação não é só sobre programar, é sobre resolver problemas também
### Objetivo da ciência da computação: transformar certo input em um output, por meio dum código que a máquina entende. Input > ? > output
### Única coisa que as máquinas entendem: binário - 0 e 1s
- contagem é bem diferente, ex: 00>0, 01>1, 10>2..., quanto maior o número, mais bits para representar
- porque é o mais simples para o computador representar: 1-com eletricidade e 0-sem, ficando essa energia dentro de transistores(tipo micro-interruptores)
- sistema de base 2 em vez de base 10
### Como representar letras: criar um padrão onde números representam certas letras, com um padrão onde cada algarismo ocupa 1byte(8bits), dando 256(número 0-255) possibilidades de símbolos. Esse é o padrão ASCII
### Mas como representar todos símbolos das várias linguagens diferentes do mundo, emojis...: criar uma padrão com mais possibilidades, no caso o unicode com 32 bits e mais de 4 bilhões de possibilidades. OBS: cada sistema, como o IOS e o Android, podem mostrar esses símbolos, como emojis, de formas levemente diferentes graficamente.
### Outras formas de armazenar outras coisas:
- Cores: padrão RGB(red-vermelho, green-verde, blue-azul), representando a quantidade, de 0-255, de cada cor na mistura que formará a cor final
- Imagem: 1 padrão RGB para cada pixel da imagem
- Vídeos: uma sequência de imagens
- Música: um outro padrão de bits, o MIDI
### Mas, apesar desses padrões, existem diferentes formatos para cada mídia(ex: imagem), porque cada formato desse usa uma forma diferente de compressão, para que a informação ocupe menos bits, pois caso contrário em alguns casos poderíamos ter uma imença quantidade de espaço ocupado, como por exemplo em um filme de 2 horas que possui cerca de 30 imagens com milhões de pixels por segundo. E essa compressão podem ser de dois tipos:
- lossy: com um pouco de perda, mas ainda bom para a percepção humana
- lossless: nenhuma perda, mas menos eficiente
### Possuindo também containers que juntam diferentes formatos, como áudio e vídeo.
### OBS: também existem outras formas de ver dados dos computadores, diferentes do binário, como o hexadecimal
### Atualizando: input(em bits) > ? > outputs(em bits)
### Essa "?" representa a parte que transforma o input nos outputs e é chamado de algorítimo(uma sequência de instruções para fazer essa transformação)
- OBS: pode ser em qualquer linguagem de programação, mas no fim virará 0s e 1s
### Exemplos de algorítimos para achar um nome em uma lista alfabética:
- \+ eficiente: olha a página do meio e vê se tá em uma letra antes ou depois da letra do nome e 'discarta' a parte que não estará, repete esse algorítimo até achar o nome. Complexidade: log2 de n.
- \- eficiente: procura o nome página por página. Complexidade: n.
- OBS: 'n' representa nesses exemplos o número de casos, no caso, o número de páginas que olharíamos
### Poderíamos expressar esses algorítimos em pseudocódigo também(passo a passo para a solução do problema, mas em português)
### Sempre em um código precisamos reconhecer possíveis exceções(como o nome não estar no livro), se não, nosso código pode dar erros e travar
### Partes que formam um código:
- funções: pedaços de códigos que executam tarefas específicas, como olhar uma página
- condicionais: coisas que você faz condicionalmente baseado na resposta para certa pergunta
    - e se a resposta pode ser apenas sim ou não, é uma condicão booleana
- loop: um ciclo para repetir um mesmo código
- OBS: também existem outras estruturas, como variáveis e parâmetros, mas que só veremos mais tarde
### Scratch: 
É uma ferramenta gráfica com bloquinhos que fazerm soisas, dispensando o uso de parenteses, etc
- Serve para treinar fundamentos que veremos na maioria das linguagens de programação
### Coordenadas nele:
- x: na horizontal, variando de -240 a 240
- y: na vertical, variando de -180 a 180
### Os blocos são caracterizados pelo o que eles fazem:
Por exemplo, a categoria de eventos, que representa qualquer interação com o dispositivo, como um clique na tela ou digitar uma letra.
### Outra estrutura dos códigos:
- Variáveis: você relaciona um noma a um valor que pretende usar depois
### Exemplo do que acontece quando chamamos um bloco de falar: input(hello) > algorítimo(implementação do bloco de fala) > output(mostra hello na tela)
### Outro modelo relativamente comum na programação é o: input > output ↷ input > output
- ex: input(pergunta qual é o seu nome?) > output(variável com a resposta) ↷ input(a resposta) > output(falar olá + o nome da pessoa)
### Uma coisa que você pode fazer é adicionar extensões ao Scratch e ganhar novos blocos, como a de text to speech
### Evitar repetição de códigos com o mesmo objetivo repetidas vezes: loops/bloco repeat
### Para formar um código mais 'separado', legível e de mais fácil entendimento, você deve criar: funções, que quando chamadas executam certo código
- Separam problemas em sub-problemas mais fáceis de solucionar
- Elas também podem receber parâmetros/inputs, para também serem usadas em diferentes lugares, executando coisas levemente diferentes, mas com uma estrutura básica padrão
### Loop enquanto o código está rodando: bloco forever
### Dica: Antes de escrever um código faça uma "to-do-list" para resolver o problema, em português mesmo
- e vai implementando elas aos poucos, ou até separadamente, juntando tudo depois.
# Meu projeto da aula 1 - Scratch
- Tempo usado: 1h30m
- Objetivo/explicação: Um projeto onde tem inimigos(tópicos dessa aula do CS50) que ficam vindo e você não pode encostar neles para ganhar o jogo. Como se fosse uma aula do CS50 e você tem que fugir dos inimigos, que são os tópicos dessa primeira aula, para assim completar a aula/ganhar o jogo
- Movimentos possíveis:
    - seta para cima: sobe seu personagem
    - seta para baixo: desce seu personagem
- Começar o jogo/rodar o projeto: clique na bandeira verde
- Tecnologia usada: Scratch
# Tecnologias

As seguintes ferramentas foram usadas na construção dos projetos:

- [Scratch](https://scratch.mit.edu/)