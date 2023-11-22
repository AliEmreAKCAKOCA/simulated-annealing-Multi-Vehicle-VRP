#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <ctime>

using namespace std;

class VehicleRoutingProblem {
public:
    VehicleRoutingProblem(vector<vector<int>> distances, int num_vehicles)
        : distances_(distances), num_vehicles_(num_vehicles) {}

    vector<vector<int>> solve() {
        vector<vector<int>> solution = generateRandomSolution();

        double temperature = 1000.0;
        double cooling_rate = 0.95;

        int iterations = 20;

        for (int i = 0; i < iterations; ++i) {
            std::cout <<"for a geri geldi\n";
            vector<vector<int>> new_solution = perturbSolution(solution);

            int old_cost = calculateCost(solution);
            int new_cost = calculateCost(new_solution);

            if (new_cost < old_cost || acceptanceProbability(old_cost, new_cost, temperature) >((double)rand() / RAND_MAX)) {
                solution = new_solution;
            }

            /*
            for (int i = 0; i < solution.size(); ++i) {
                cout << "Vehicle " << i + 1 << ": ";
                for (int j = 0; j < solution[i].size(); ++j) {
                    cout << solution[i][j] << " ";
                }
                cout << endl;
            }
            std::cout << "-----------" << std::endl;
            //iki dizi arasında eleman geçişi yok onuda ekle
            */

        }
        std::cout << "algoritma bitti\n";

      

        return solution;
    }

private:
    vector<vector<int>> distances_;
    int num_vehicles_;
   
    vector<vector<int>> generateRandomSolution() {
        vector<vector<int>> solution(num_vehicles_);

        for (int i = 1; i < distances_.size(); ++i) {
            solution[i % num_vehicles_].push_back(i);
        }

        for (int i = 0; i < num_vehicles_; i++)
        {
            solution[i].insert(solution[i].begin(), 0);
        }

        return solution;
    }

    vector<vector<int>> perturbSolution(const vector<vector<int>>& solution) {
        vector<vector<int>> perturbed_solution = solution;
        std::cout << " pertubeye geldi\n";
        int vehicle_index;
        vehicle_index = rand() % num_vehicles_;
        std::cout << "ilk vehicle index: " << vehicle_index << "\n\n";

        while (perturbed_solution[vehicle_index].size() <2)
        {
            vehicle_index = rand() % num_vehicles_;
            std::cout << "vehicle index: " << vehicle_index << "\n\n";
        }


     
       
        int index1 = rand() %( perturbed_solution[vehicle_index].size()-1);
     
        int index2 = rand() %( perturbed_solution[vehicle_index].size()-1);
      

        swap(perturbed_solution[vehicle_index][index1+1], perturbed_solution[vehicle_index][index2+1]);


        // araçlar arası durak değişimi
      
        
        int vehicle_index3= rand() % num_vehicles_;
     
        int asa;
        

    

        int vehicle_index4 = rand() % num_vehicles_;
     

        if (perturbed_solution[vehicle_index4].size() > 1 && vehicle_index3!=vehicle_index4 && perturbed_solution[vehicle_index3].size() > 1)
        {
            int index3 = rand() % (perturbed_solution[vehicle_index3].size()-1);
            
            asa = perturbed_solution[vehicle_index3][index3+1];
            perturbed_solution[vehicle_index3].erase(perturbed_solution[vehicle_index3].begin() + index3+1);

            int index4 = rand() % (perturbed_solution[vehicle_index4].size()-1);
           
            perturbed_solution[vehicle_index4].insert(perturbed_solution[vehicle_index4].begin() + index4+1,asa );
        }
       

        for (int i = 0; i < perturbed_solution.size(); ++i) {
            cout << "Vehicle " << i + 1 << ": ";
            for (int j = 0; j < perturbed_solution[i].size(); ++j) {
                cout << perturbed_solution[i][j] << " ";
            }
            cout << endl;
        }
        std::cout << "-----------" << std::endl;
        std::cout << "-----------" << std::endl;
    
        



      

       
        

        ///dizi satırları arasında eleman geçişine izin ver bunu eklemeyi unuta

        // randon vehicle indexten seçilen bir elemanı randon bir vehicle indexin sonuna ekle
        /*
         // 2.indexiden sonraki indexe  9'u eklemek
    myVector.insert(myVector.begin() + 2, 9);


        */

       
        return perturbed_solution;
   

    }

    int calculateCost(const vector<vector<int>>& solution) {
        int total_cost = 0;
        for (int i = 0; i < num_vehicles_; ++i) {
            int cost = 0;
            for (int j = 0; j < solution[i].size() - 1; ++j) {
                cost += distances_[solution[i][j]][solution[i][j + 1]];
            }
            total_cost += cost;

            // Maliyeti yazdır
       //     cout << "Vehicle " << i + 1 << " Cost: " << cost << endl;
        }

        // Toplam maliyeti yazdır
      //  cout << "Total Cost: " << total_cost << endl;

        return total_cost;
    }

    double acceptanceProbability(int old_cost, int new_cost, double temperature) {
        if (new_cost < old_cost) {
            return 1.0;
        }
        return exp((old_cost - new_cost) / temperature);
    }
};

int main() {
    // Örnek mesafe matrisi (10 nokta)
    vector<vector<int>> distances = {
        {0, 10, 15, 20, 25, 30, 35, 40, 45, 50},
        {10, 0, 35, 25, 30, 20, 40, 15, 30, 25},
        {15, 35, 0, 30, 40, 25, 20, 35, 10, 45},
        {20, 25, 30, 0, 50, 15, 30, 25, 20, 35},
        {25, 30, 40, 50, 0, 45, 10, 20, 30, 15},
        {30, 20, 25, 15, 45, 0, 35, 30, 25, 10},
        {35, 40, 20, 30, 10, 35, 0, 40, 15, 20},
        {40, 15, 35, 25, 20, 30, 40, 0, 45, 30},
        {45, 30, 10, 20, 30, 25, 15, 45, 0, 25},
        {50, 25, 45, 35, 15, 10, 20, 30, 25, 0}
    };

    // Araç sayısı (3 araç)
    int num_vehicles = 3;

    // Araç rotalama problemi sınıfını oluştur
    VehicleRoutingProblem vrp(distances, num_vehicles);

    // Problemi çöz
    vector<vector<int>> solution = vrp.solve();

    // Çözümü ekrana yazdır
    cout << " Solution  :\n";
    for (int i = 0; i < solution.size(); ++i) {
        cout << "Vehicle " << i + 1 << ": ";
        for (int j = 0; j < solution[i].size(); ++j) {
            cout << solution[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}
