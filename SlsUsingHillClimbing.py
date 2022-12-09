
import random
import time
def getBestRoute(tsp,neighbors):
    min_distance_route=neighbors[0]
    min_distance=distance(tsp,neighbors[0])
    for curr_route in neighbors:
        curr_route_distance=distance(tsp,curr_route)
        if curr_route_distance<min_distance:
            min_distance=curr_route_distance
            min_distance_route=curr_route
    return min_distance_route,min_distance


def distance(tsp,curr_solution):
    cost=0
    for i in range(len(curr_solution)):
        cost+=float(tsp[curr_solution[i-1]][curr_solution[i]])

    return cost

def randomSol(tsp):
    cities=list(range(len(tsp)))
    result=[]
    for i in range(len(tsp)):
        curr_city=cities[random.randint(0,len(cities)-1)]
        result.append(curr_city)
        cities.remove(curr_city)
    return result

def getneighbors(solution):
    neighbors=[]
    for i in range(len(solution)):
        for j in range(i+1, len(solution)):
            neighbor=solution.copy()
            neighbor[i]=solution[j]
            neighbor[j]=solution[i]
            neighbors.append(neighbor)
    return neighbors

def hillclimbing(tsp):
    time1=time.time()
    curr_route= randomSol(tsp)
    curr_distance= distance(tsp,curr_route)
    neighbors=getneighbors(curr_route)
    min_distance_route,min_distance=getBestRoute(tsp,neighbors)
    while min_distance<curr_distance:
        curr_distance=min_distance
        curr_route=min_distance_route
        neighbors=getneighbors(curr_route)
        min_distance_route,min_distance=getBestRoute(tsp,neighbors)
    time2=time.time()
    print("time is" +str(time2-time1))
    return curr_route,curr_distance


def main():
    filename = "input.txt"
    with open(filename) as f:
        content = f.read().splitlines()

    
    tsp=[]
    N = content[0]
    content=content[1:]
    for line in content:
        temp = []
        for i in line.split(' '):
            temp.append(float(i))
        tsp.append(temp)
    
    print(hillclimbing(tsp))
        

if __name__== "__main__":
    main()
