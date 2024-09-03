#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <cmath>
#include <climits>
#include <algorithm>


using namespace std;


// Define a structure for representing the graph nodes
struct Node {
   string name;
   vector<pair<Node*, int>> neighbors; // Pair of (neighboring node, cost to that neighbor)
   int heuristic; // Heuristic value (straight-line distance to the goal)


   Node(string n, int h) : name(n), heuristic(h) {}
};


// Comparator for the priority queue to compare total costs
struct CompareCost {
   bool operator()(pair<Node*, int> a, pair<Node*, int> b) {
       return a.second > b.second; // Min-heap based on total cost
   }
};


// Function to perform the A* search
pair<vector<pair<string, int>>, int> aStarSearch(Node* start, Node* goal) {
   // Priority queue to store (current node, total cost) pairs, ordered by total cost
   priority_queue<pair<Node*, int>, vector<pair<Node*, int>>, CompareCost> openSet;
   unordered_map<Node*, int> gScore; // Actual cost from start to current node
   unordered_map<Node*, Node*> cameFrom; // To reconstruct the path


   openSet.push({start, start->heuristic});
   gScore[start] = 0;


   while (!openSet.empty()) {
       Node* current = openSet.top().first;
       openSet.pop();


       if (current == goal) { // Goal reached
           vector<pair<string, int>> path;
           int totalDistance = gScore[goal];
           while (current != nullptr) {
               path.push_back({current->name, gScore[current]});
               current = cameFrom[current];
           }
           reverse(path.begin(), path.end());
           return {path, totalDistance};
       }


       for (auto& neighbor : current->neighbors) {
           Node* neighborNode = neighbor.first;
           int cost = neighbor.second;
           int tentative_gScore = gScore[current] + cost;


           if (gScore.find(neighborNode) == gScore.end() || tentative_gScore < gScore[neighborNode]) {
               cameFrom[neighborNode] = current;
               gScore[neighborNode] = tentative_gScore;
               int fScore = tentative_gScore + neighborNode->heuristic;
               openSet.push({neighborNode, fScore});
           }
       }
   }
   return {{}, 0}; // Return empty path and zero distance if goal not reachable
}


int main() {
   // Create nodes
   Node* Arad = new Node("Arad", 366);
   Node* Zerind = new Node("Zerind", 374);
   Node* Oradea = new Node("Oradea", 380);
   Node* Sibiu = new Node("Sibiu", 253);
   Node* Fagaras = new Node("Fagaras", 178);
   Node* RimnicuVilcea = new Node("Rimnicu Vilcea", 193);
   Node* Pitesti = new Node("Pitesti", 98);
   Node* Timisoara = new Node("Timisoara", 329);
   Node* Lugoj = new Node("Lugoj", 244);
   Node* Mehadia = new Node("Mehadia", 241);
   Node* Drobeta = new Node("Drobeta", 242);
   Node* Craiova = new Node("Craiova", 160);
   Node* Bucharest = new Node("Bucharest", 0);
   Node* Giurgiu = new Node("Giurgiu", 77);
   Node* Urziceni = new Node("Urziceni", 80);
   Node* Hirsova = new Node("Hirsova", 151);
   Node* Eforie = new Node("Eforie", 161);
   Node* Vaslui = new Node("Vaslui", 199);
   Node* Iasi = new Node("Iasi", 226);
   Node* Neamt = new Node("Neamt", 234);


   // Define edges (bidirectional)
   Arad->neighbors = {{Zerind, 75}, {Sibiu, 140}, {Timisoara, 118}};
   Zerind->neighbors = {{Arad, 75}, {Oradea, 71}};
   Oradea->neighbors = {{Zerind, 71}, {Sibiu, 151}};
   Sibiu->neighbors = {{Arad, 140}, {Oradea, 151}, {Fagaras, 99}, {RimnicuVilcea, 80}};
   Fagaras->neighbors = {{Sibiu, 99}, {Bucharest, 211}};
   RimnicuVilcea->neighbors = {{Sibiu, 80}, {Pitesti, 97}, {Craiova, 146}};
   Pitesti->neighbors = {{RimnicuVilcea, 97}, {Craiova, 138}, {Bucharest, 101}};
   Timisoara->neighbors = {{Arad, 118}, {Lugoj, 111}};
   Lugoj->neighbors = {{Timisoara, 111}, {Mehadia, 70}};
   Mehadia->neighbors = {{Lugoj, 70}, {Drobeta, 75}};
   Drobeta->neighbors = {{Mehadia, 75}, {Craiova, 120}};
   Craiova->neighbors = {{Drobeta, 120}, {RimnicuVilcea, 146}, {Pitesti, 138}};
   Bucharest->neighbors = {{Fagaras, 211}, {Pitesti, 101}, {Giurgiu, 90}, {Urziceni, 85}};
   Giurgiu->neighbors = {{Bucharest, 90}};
   Urziceni->neighbors = {{Bucharest, 85}, {Hirsova, 98}, {Vaslui, 142}};
   Hirsova->neighbors = {{Urziceni, 98}, {Eforie, 86}};
   Eforie->neighbors = {{Hirsova, 86}};
   Vaslui->neighbors = {{Urziceni, 142}, {Iasi, 92}};
   Iasi->neighbors = {{Vaslui, 92}, {Neamt, 87}};
   Neamt->neighbors = {{Iasi, 87}};


   // Perform A* Search from Arad to Bucharest
   pair<vector<pair<string, int>>, int> result = aStarSearch(Arad, Bucharest);
   vector<pair<string, int>> path = result.first;
   int totalDistance = result.second;


   if (!path.empty()) {
       cout << "Path from Arad to Bucharest: \n";
       for (size_t i = 0; i < path.size(); ++i) {
           cout << path[i].first;
           if (i < path.size() - 1) {
               cout << " -> " << path[i+1].second << " km -> ";
           }
       }
       cout << "\nTotal distance covered: " << totalDistance << " km" << endl;
   } else {
       cout << "No path found from Arad to Bucharest." << endl;
   }


   // Free memory
   delete Arad; delete Zerind; delete Oradea; delete Sibiu; delete Fagaras;
   delete RimnicuVilcea; delete Pitesti; delete Timisoara; delete Lugoj;
   delete Mehadia; delete Drobeta; delete Craiova; delete Bucharest; delete Giurgiu;
   delete Urziceni; delete Hirsova; delete Eforie; delete Vaslui; delete Iasi; delete Neamt;


   return 0;
}