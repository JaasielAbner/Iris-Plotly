# Iris-Plotly

Plot2d -> Arquivos para printar o grafo em 2d, usando o neato
  (criar a saída do C como lista de adjacencia, executar o script plot.py para gerar um grafo.dot, depois executar o comando ```neato -x -Goverlap=scale -Tpng grafo.dot > grafo.png``` para gerar a imagem)
  
v1.c cria o grafo, usando a DEN para calcular as arestas

teste.py é um script simples para calcular quantas arestas estão corretas e quantas estão erradas.

a.py usa as bibliotecas pyvis e plotly para criar a visualização do grafo
