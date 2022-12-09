#include<iomanip>
#include<iostream>
#include<vector>
#define endl '\n'
#define INF 1e18

using namespace std;

double upp_bound = INF;
double ans ;
vector<int> travel_path;
vector<bool> visited;

// Returns a vector containing the two nearest neighbours for that particular node.
vector<double> two_nearest_neighbours(vector<vector<double> > &graph, int i, int N){
    double smallest = INF, second_smallest = INF;
    for(int j=0;j<N;j++){
        if(i == j)
            continue;
        if(graph[i][j] <= smallest){
            second_smallest = smallest;
            smallest = graph[i][j];
        }
        else if (graph[i][j] <= second_smallest && graph[i][j] != smallest){
            second_smallest = graph[i][j];
        }
    }
    vector<double> v(smallest, second_smallest);
    return v;
}

// Returns a vector containing the two nearest neighbours for all the nodes.
vector<vector<double> > calculate_two_nearest_neighbours(vector<vector<double> > &graph, int N){
    vector<vector<double> >heuristic;
    for(int i=0;i<N;i++){
        vector<double> two_min = two_nearest_neighbours(graph, i, N);
        heuristic.push_back(two_min);
    }
    return heuristic;
}

// Recursive function that calucates the cost of a complete path.
void solve_tsp(vector<vector<double> > &graph, double curr_heuristic, double curr_weight, int count, vector<int> &path, int N, vector<vector<double> > &heuristic){
    if(curr_weight>upp_bound)return;
    if (count==N){
        if (graph[path[count-1]][path[0]] == 0){
            return;
        }
        double curr_res = curr_weight + graph[path[count-1]][path[0]];
        
        if (curr_res < upp_bound){
            travel_path = path;
            travel_path.push_back(path[0]);
            ans=curr_res;
           
            upp_bound = curr_res-2;
            
            cout<<setprecision(8)<<fixed<<ans<<"\n";
            
            for(auto i:path){
                cout<<i<<" ";
            }
            cout<<endl;
        }
        return;
    }
    
    for(int i=0;i<N;i++){
      
        if (graph[path[count-1]][i] != 0 and visited[i] == false){
            double val_diff = 0;
            curr_weight += graph[path[count-1]][i];
            
            if (count==1)
                val_diff = (heuristic[path[count-1]][0] + heuristic[i][0])/2;
            else
                val_diff = (heuristic[path[count-1]][1] + heuristic[i][0])/2;
            curr_heuristic -= val_diff;
            double lower_bound = curr_heuristic + curr_weight;

            if (lower_bound <= upp_bound){
                path[count] = i;
                visited[i] = true;
                solve_tsp (graph, curr_heuristic, curr_weight, count+1, path, N, heuristic);
            }
            
            curr_weight -= graph[path[count-1]][i];
            curr_heuristic += val_diff;
            
            visited.clear();
            visited.resize(N,false);

            for(int j=0;j<count;j++) {
                visited[path[j]] = true;
            }
            
        }
        
    }
}

void tsp_branch_bound(vector<vector<double> > &graph, int N){
    double curr_heuristic = 0;
    vector<int>path(N,-1);
    vector<vector<double> >heuristic = calculate_two_nearest_neighbours(graph, N);

    for(int i=0;i<N;i++){
        curr_heuristic += (heuristic[i][0] + heuristic[i][1]);
    }
    curr_heuristic = (curr_heuristic + 1)/2;

    visited.resize(N,false);
    visited[0] = true;
    path[0] = 0;
    upp_bound = INF;
    solve_tsp(graph, curr_heuristic, 0, 1, path, N, heuristic);
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

int main()
{
    #ifndef ONLINE_JUDGE
        freopen("input.txt", "r", stdin);
        // freopen("output.txt", "w", stdout);
    #endif
    int N;
    cin>>N;
    vector<vector<double> > graph = take_input(N);
    
    clock_t tStart = clock();
    tsp_branch_bound(graph, N);

    cout<<setprecision(8)<<fixed<<ans<<"\n";
    for(auto i:travel_path){
        cout<<i<<" ";
    }
    cout<<'\n';
    printf("Time Taken  %.3fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);
}