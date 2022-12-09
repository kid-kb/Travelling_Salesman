#include<iomanip>
#include<iostream>
#include<vector>
#define endl '\n'
#define INF 1e18
#define endl '\n'

#define INF 1e18
using namespace std;


// Calculates the cost for this particular path.
double distance(vector<vector<double> > &tsp, vector<int> &curr_solution){
    double cost =0.0;
    for(int i=0;i<curr_solution.size()-1;i++){
        cost += tsp[curr_solution[i]][curr_solution[i+1]];
    }
    cost+= tsp[curr_solution[curr_solution.size()-1]][curr_solution[0]];
    return cost;
}

// Calucates the best cost for this 2-D matrix.
pair<vector<int>,double> getBestRoute(vector<vector<double> > &tsp, vector<vector<int> > &neighbors){
    vector<int> min_distance_route = neighbors[0];
    double min_distance = distance(tsp, min_distance_route);
    
    for(auto curr_route:neighbors){
        double curr_route_distance = distance(tsp, curr_route);
        if(curr_route_distance < min_distance){
            min_distance = curr_route_distance;
            min_distance_route=curr_route;
        }
    }
    pair<vector<int>,double> p;
    p.first=min_distance_route;
    p.second=min_distance;
    return p;
}


// Generate a random solution.
vector<int> randomSol(vector<vector<double> > &tsp, int N){
    vector<int>v;
    for(int i=0;i<N;i++){
        v.push_back(i);
    }
    
    vector<int>res;
    while (v.size()>0) {
        int n = v.size();
        
        // Generate a random number
        srand(time(NULL));
        int ind = rand() % n;
        res.push_back(v[ind]);
        int num = v[ind];
        
        
        // Remove the number from the vector
        swap(v[ind], v[n - 1]);
        v.pop_back();
    }
    return res;
}

// Doing one swap from every index.
vector<vector<int> > getneighbors(vector<int> &curr_route){
    vector<vector<int> > neighbors;
    for(int i=0;i<curr_route.size();i++){
        for(int j=i+1;j<curr_route.size();j++){
            vector<int> n = curr_route;
            n[i]=curr_route[j];
            n[j]=curr_route[i];
            neighbors.push_back(n);
        }
    }
    return neighbors;
}

pair<vector<int>,double> hillclimbing(vector<vector<double> > &tsp, int N){
    vector<int>curr_route = randomSol(tsp, N);
    double curr_distance= distance(tsp,curr_route);
    double min_distance = -1e18;
    vector<vector<int> > neighbors;
    pair<vector<int>,double> p;
    vector<int> min_distance_route;

   while(min_distance < curr_distance){
        if(min_distance != -1e18){
            curr_distance=min_distance;
            curr_route=min_distance_route;
        }
        neighbors = getneighbors(curr_route);
        p=getBestRoute(tsp,neighbors);
        min_distance_route=p.first;
        min_distance=p.second;
   }

    p.first=curr_route;
    p.second=curr_distance;
    return p;
}

// Takes graph as input.
vector<vector<double> > take_input(int N){
    vector<vector<double> > graph;
    for(int i=0;i<N;i++){
        vector<double>temp(N);
        for(int j=0;j<N;j++){
            cin>>temp[j];
        }
        graph.push_back(temp);
    }
    return graph;
}

int main(){
    #ifndef ONLINE_JUDGE
        freopen("input.txt", "r", stdin);
        // freopen("output.txt", "w", stdout);
    #endif
    clock_t tStart = clock();
    int N;
    cin>>N;
    vector<vector<double> > tsp = take_input(N);

    pair<vector<int>,double> ans = hillclimbing(tsp, N);
    vector<int> travel_path = ans.first;
    double cost = ans.second;
    cout<<setprecision(8)<<fixed<<cost<<"\n";
    for(auto i:travel_path){
        cout<<i<<" ";
    }
    cout<<'\n';
    printf("Time Taken  %.3fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);
    return 0;
    
}
