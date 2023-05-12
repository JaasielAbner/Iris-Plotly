# Iris-Plotly

**Pasta Imagens** -> Contem os arquivos png dos grafos [2D](imagens/2DGrafo.png), 3D [aleatório](imagens/3DGrafo_aleatorio.png) e [definido](imagens/3DGrafo_definido.png).


**Pasta Plot2d** -> Arquivos para printar o grafo em 2d, usando o neato
  (criar a saída do C como lista de adjacencia, executar o script plot.py para gerar um grafo.dot, depois executar o comando ```bash
  neato -x -Goverlap=scale -Tpng grafo.dot > grafo.png``` para gerar a imagem)


**Pasta Plot3d** -> 

1. Usamos o arquivo **[Plot 3D Aleatório](Plot3D/Plot3D_aleatorio.py)** para plotar o grafo 3D, ultilizando as bibliotecas *pyvis* e *plotly*, com valores aleatórios nas posições *x y z* de um vértice.

2. E para ploar o grafo 3D, tambem ultilizando as bibliotecas *pyvis* e *plotly*, recebemos os valores definidos pelo arquivo IrisDataset.csv, e é criado pelo arquivo **[Plot 3D Definido](Plot3D/Plot3D_definido.py)** o grafo 3D com os valores respectivos.

3. IrisDataset.csv: Arquivo CSV contendo a base de dados IrisDataset.

4. **[Arquivo Main](Plot3D/v1.c)**:
 Nele se encontra todo o processo, desde ler o arquivo CSV, até a criacão do arquivo TXT para a plotagem do grafo. 


**Passo a Passo Arquivo Main** ->

1.  É definido e alocada a matriz *Mat*. E depois foi feito a abertura do arquivo **[IrisDataset](Plot3D/IrisDataset.csv)**.

2.  Ultilizando as funções *strtok* e *atof*, foram lidos os dados do CSV e transformados em float. Logo depois, eles são inseridos na matriz *Mat* de tamanho 150x4.

3.  Com a matriz *Mat* pronta, começa o processo de criação da matriz de distâncias euclidianas. Foi alocada uma matriz chamada *MatDe*, de tamanho 150x150 e feito o calculo euclidiano em cada posição.

4.  O proximo passo, foi chamar a função *normalize_matrix()*, que tem como objetivo, nomalizar a matriz de distâncias euclidianas.

5.  A função *normalize_matrix()*, primeiramente, encontra o maior e o menor valor da *MatDe*, e logo depois, normaliza cada elemento, pegando esse elemento e diminuindo com o menor valor da matriz. Esse resultado é dividido pela subtração do maior valor e menor valor da matriz.

6.  Dentro dessa mesma funcão, após encontrado o resultado da divisão feita, é comparado o numero encontrado com o valor 0.3, e se o valor for menor que 0.3, na matriz 150x150, é posto o valor 1, e se não for menor que 0.3, é posto o valor 0, assim criando a **Matriz de Adjacencias**.

7.  Agora é executada a parte de funções de saida. A primeira funcão de saida é a *print_matrix()*, que simplismente mostra no console a **Matriz de Adjacencias**

8.  E por ultimo, a função *make_txt*, cria um arquivo **[out.txt](Plot3D/output/out.txt)**, que tem como função, ser lida pelo **[Plot 3D Aleatório](Plot3D/Plot3D_aleatorio.py)**, **[Plot 3D Definido](Plot3D/Plot3D_definido.py)** ou o **[Plot 2D](Plot2D/plot.py)**, e criar as respectivas imagens do grafo. O arquivo **[out.txt](Plot3D/output/out.txt)** tem como conteúdo a quantidade de vérticies, uma lista de cada vérticie e quais outros vertíces tem aresta com o respectivo vértice.


**Arquvo ***teste.py***** -> é um script simples para calcular quantas arestas estão corretas e quantas estão erradas.
