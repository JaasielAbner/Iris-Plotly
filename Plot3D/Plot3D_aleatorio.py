from collections import defaultdict
import plotly.graph_objects as go
import random

class Grafo:
    grafo = defaultdict(list)

    def __init__(self, dirigido = False) -> None:
        self.dirigido = dirigido

    def addAresta(self, vertice, vizinho) -> object:
        if vizinho not in self.grafo[vertice]:
            self.grafo[vertice].append(vizinho)
            if not self.dirigido:
                self.grafo[vizinho].append(vertice)

        return self

    def rmAresta(self, vertice, vizinho) -> object:
        if vertice in self.grafo:
            self.grafo[vertice].remove(vizinho)
            if not self.dirigido:
                self.grafo[vizinho].remove(vertice)
        
        return self

    def getNumVertices(self) -> int:
        return len(self.grafo.keys())

    def getGrau(self, s) -> int:
        return len(self.grafo[s])

    def getVertices(self) -> list:
        return self.grafo.keys()

    def bfs(self, s) -> list:
        visitados, fila, resultado = [s], [s], []

        while fila:
            s = fila.pop(0)
            for vertice in self.grafo[s]:
                if vertice not in visitados:
                    visitados.append(vertice)
                    fila.append(vertice)
            resultado.append(s)

        return resultado

    def dfs(self, s) -> list:
        pilha, caminho = [s], []
        while pilha:
            vertice = pilha.pop()
            if vertice not in caminho:
                caminho.append(vertice)
                pilha.extend(self.grafo[vertice])
        
        return caminho

    def __temCiclo(self, s, visitado, parente) -> bool:
        visitado[s] = True

        for i in self.grafo[s]:
            if not visitado[i]:
                if self.__temCiclo(i, visitado, s):
                    return True
            elif parente != i:
                return True

        return False

    def temCiclo(self) -> bool:
        numVertices: int = self.getNumVertices()
        visitado: list = [False] * (numVertices + 1)

        for i in range(numVertices):
            if not visitado[i]:
                if self.__temCiclo(i, visitado, -1):
                    return True

        return False

    def showVertices(self) -> object:
        vertices = self.getVertices()
        
        print("Vertices:")
        for i, s in enumerate(vertices):
            print(f'{s}', end = "")
            if i % 10 == 0:
                print()

        return self

    def showArestas(self) -> object:
        vertices = self.getVertices()
        i = 0
        for s1 in vertices:
            for s2 in self.grafo[s1]:
                print(f'({s1}, {s2})', end = ", ")
                i += 1
                if i % 10 == 0:
                    print()

        return self

    def getArestas(self, tupla = False) -> list:
        resultado, vertices = [], self.getVertices()

        for s1 in vertices:
            for s2 in self.grafo[s1]:
                if tupla:
                    resultado.append((s1, s2))
                else:
                    resultado.append([s1, s2])

        return resultado

    def showMapa3D(self) -> None:
        numVertices = self.getNumVertices()
        arestas_weights = [1] * (numVertices)
        arestas = self.getArestas(tupla=True)

        grafo_3D = defaultdict(list)

        classes = []

        with open("classes.txt", "r") as a:
            for linha in a.readlines():
                classes.append(int(linha))
        

        ## este dict contem as classes separadas, mas com a posição randômica
        random.SystemRandom()
        grafo_3D = {
            v1: [random.random()*50 + (classes[v1]*50), random.random()*50 + (classes[v1]*50), random.random()*50 + (classes[v1]*50)] for v1 in self.getVertices()
        }

        x_vertices = [grafo_3D[key][0] for key in grafo_3D.keys()]
        y_vertices = [grafo_3D[key][1] for key in grafo_3D.keys()]
        z_vertices = [grafo_3D[key][2] for key in grafo_3D.keys()]

        x_arestas, y_arestas, z_arestas = [], [], []
        xtp, ytp, ztp = [], [], []

        for aresta in arestas:
            #formato: [comeco, destino, None]
            x_coords = [grafo_3D[aresta[0]][0], grafo_3D[aresta[1]][0], None]
            x_arestas.extend(x_coords)
            xtp.append(0.5 * (grafo_3D[aresta[0]][0] + grafo_3D[aresta[1]][0]))

            y_coords = [grafo_3D[aresta[0]][1], grafo_3D[aresta[1]][1], None]
            y_arestas.extend(y_coords)
            ytp.append(0.5 * (grafo_3D[aresta[0]][1] + grafo_3D[aresta[1]][1]))

            z_coords = [grafo_3D[aresta[0]][2], grafo_3D[aresta[1]][2], None]
            z_arestas.extend(z_coords)
            ztp.append(0.5 * (grafo_3D[aresta[0]][2] + grafo_3D[aresta[1]][2]))


        # Criar Linhas
        trace_arestas = go.Scatter3d(
                name='Arestas',
                x=x_arestas,
                y=y_arestas,
                z=z_arestas,
                mode='lines',
                line=dict(color='black', width=0.2),
            )

        ## Criar Vertices com a propria classe definida
        trace_vertices1 = go.Scatter3d(
            name='Setosa',
            x=x_vertices[0:50],
            y=y_vertices[0:50],
            z=z_vertices[0:50],
            mode='markers',
            marker=dict(symbol='circle',
                        size=5,
                        color='red')
        )

        trace_vertices2 = go.Scatter3d(
            name='Versicolor',
            x=x_vertices[50:100],
            y=y_vertices[50:100],
            z=z_vertices[50:100],
            mode='markers',
            marker=dict(symbol='diamond',
                        size=5,
                        color='green')
        )

        trace_vertices3 = go.Scatter3d(
            name='Virginica',
            x=x_vertices[100:150],
            y=y_vertices[100:150],
            z=z_vertices[100:150],
            mode='markers',
            marker=dict(symbol='square',
                        size=5,
                        color='pink')
        )

        layout = go.Layout(
                title = "Iris Dataset",
                autosize=True,
                showlegend=True,
                margin=dict(t=80),
            )

        # Juntar todas as infos
        data = [trace_arestas, trace_vertices1, trace_vertices2, trace_vertices3]

        ## com esse set, as posições são setadas randomicamente
        fig = go.Figure(data=data, layout=layout)

        fig.show()




def GrafoFromFile(enderecoArquivo = "", dirigido = False) -> Grafo:
    grafo = Grafo(dirigido)
    split = lambda string: [*map(int, string.split(" "))]

    with open(enderecoArquivo, "r") as arquivo:
        for linha in arquivo.readlines():
            aresta = split(linha)
            if len(aresta) > 1:
                a, b = aresta
                grafo.addAresta(a, b)

    return grafo



#from Grafo import GrafoFromFile


if __name__ == "__main__":
    name= './v1.out'#grafo.csv'#
      
    g = GrafoFromFile(name)    
    g.showMapa3D()
