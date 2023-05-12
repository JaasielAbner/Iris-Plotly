# Iris-Plotly

Pasta Plot2d -> Arquivos para printar o grafo em 2d, usando o neato
  (criar a saída do C como lista de adjacencia, executar o script plot.py para gerar um grafo.dot, depois executar o comando ```bash
  neato -x -Goverlap=scale -Tpng grafo.dot > grafo.png``` para gerar a imagem)

Pasta Plot3d -> 
1. Usamos o arquivo ***a.py*** para plotar o grafo 3D, ultilizando as bibliotecas *pyvis* e *plotly*, com valores aleatórios nas posições *x y z* de um vértice.
2. E para ploar o grafo 3D, tambem ultilizando as bibliotecas *pyvis* e *plotly*, recebemos os valores definidos pelo arquivo IrisDataset.csv, e é criado pelo arquivo ***d.py*** o grafo 3D com os valores respectivos.
  
Pasta Imagens -> Contem os arquivos png dos grafos 2D, 3D aleatório e definido.

IrisDataset.csv -> Arquivo CSV contendo a base de dados IrisDataset.

**teste.py** -> é um script simples para calcular quantas arestas estão corretas e quantas estão erradas.
  
**v1.c** ->

> É o arquivo Main do projeto. Nele se encontra todo o processo, desde ler o arquivo CSV, até a criacão do arquivo TXT para a plotagem do grafo. Abaixo se encontra a lista do passo a passo:

1. 


cria o grafo, usando a DEN para calcular as arestas



a.py usa as bibliotecas pyvis e plotly para criar a visualização do grafo



