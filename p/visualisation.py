# Execution:
#   python visualisation.py

from matplotlib import pyplot
from numpy import loadtxt

dataFileSolution = ["resuGraph250000.dat","resuGraph200000.dat","resuGraph150000.dat","resuGraph100000.dat"]
dataCitiesSolution = ["resuCities250000.dat","resuCities200000.dat","resuCities150000.dat","resuCities100000.dat"]
for i in range(4):
    
    # draw the cities
    cities = loadtxt(dataCitiesSolution[i], dtype=float, delimiter=" ")
    pyplot.scatter(cities[:,1], cities[:,2], s=cities[:,0]/1000, c=cities[:,0], alpha=0.5);
    
    # draw the graph
    graph = loadtxt(dataFileSolution[i], dtype=int)
    print(graph.shape[0])
    for x in range(graph.shape[0]):
      edge = [graph[x,0], graph[x,1]]
      pyplot.plot(cities[edge,1], cities[edge,2], 'b')
    
    pyplot.xlabel('Longitude', size=32)
    pyplot.ylabel('Latitude', size=32)
    
    
    # save in a PNG file
    name = dataFileSolution[i]
    pyplot.savefig(name+'.png')
    
    # show the result
    pyplot.show()
