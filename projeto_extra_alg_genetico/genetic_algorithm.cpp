#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <numeric>
#include <iomanip>
#include <cmath>
#include <fstream>

using namespace std;

int randomInt(int min, int max) {
    return rand() % (max - min + 1) + min;
}

double randomDouble() {
    return static_cast<double>(rand()) / RAND_MAX;
}

// Função de fitness
vector<int> fitness(const vector<int>& weights, const vector<int>& values, const vector<vector<int>>& population, int capacity) {
    vector<int> fitness(population.size(), 0);
    for (size_t i = 0; i < population.size(); i++) {
        int total_value = 0, total_weight = 0;
        for (size_t j = 0; j < population[i].size(); j++) {
            total_value += population[i][j] * values[j];
            total_weight += population[i][j] * weights[j];
        }
        if (total_weight <= capacity) { fitness[i] = total_value; }
    }
    return fitness;
}

// Seleção
vector<vector<int>> selection(const vector<int>& fitness, int num_parents, const vector<vector<int>>& population) {
    vector<vector<int>> parents;
    vector<int> fitness_copy = fitness;
    for (int i = 0; i < num_parents; i++) {
        auto max_iter = max_element(fitness_copy.begin(), fitness_copy.end());
        int index = distance(fitness_copy.begin(), max_iter);
        parents.push_back(population[index]);
        *max_iter = -1;
    }
    return parents;
}

// Crossover
vector<vector<int>> crossover(const vector<vector<int>>& parents, int num_offsprings) {
    vector<vector<int>> offsprings(num_offsprings, vector<int>(parents[0].size(), 0));
    int crossover_point = parents[0].size() / 2;
    double crossover_rate = 0.8;
    int i = 0, cnt_offsprings = 0;
    while (cnt_offsprings < num_offsprings) {
        int parent1_index = i % parents.size();
        int parent2_index = (i + 1) % parents.size();
        if (randomDouble() <= crossover_rate) {
            for (int j = 0; j < crossover_point; j++) { offsprings[cnt_offsprings][j] = parents[parent1_index][j]; }
            for (size_t j = crossover_point; j < parents[0].size(); j++) { offsprings[cnt_offsprings][j] = parents[parent2_index][j]; }
            cnt_offsprings++;
        }
        i++;
    }
    return offsprings;
}

// Mutação
vector<vector<int>> mutation(const vector<vector<int>>& offsprings) {
    vector<vector<int>> mutants = offsprings;
    double mutation_rate = 0.15;
    for (size_t i = 0; i < mutants.size(); i++) {
        if (randomDouble() <= mutation_rate) {
            int gene = randomInt(0, mutants[i].size() - 1);
            mutants[i][gene] = 1 - mutants[i][gene];
        }
    }
    return mutants;
}

// Otimização
pair<vector<int>, vector<vector<int>>> optimize(const vector<int>& weights, const vector<int>& values, vector<vector<int>>& population, int num_generations, int capacity) {
    vector<int> best_individual;
    vector<vector<int>> fitness_history;
    int num_parents = population.size() / 2;
    int num_offsprings = population.size() - num_parents;
    for (int generation = 0; generation < num_generations; ++generation) {
        vector<int> current_fitness = fitness(weights, values, population, capacity);
        fitness_history.push_back(current_fitness);
        vector<vector<int>> parents = selection(current_fitness, num_parents, population);
        vector<vector<int>> offsprings = crossover(parents, num_offsprings);
        vector<vector<int>> mutants = mutation(offsprings);
        copy(parents.begin(), parents.end(), population.begin());
        copy(mutants.begin(), mutants.end(), population.begin() + num_parents);
    }
    cout << "Última geração:\n";
    for (const auto& individual : population) {
        for (int gene : individual) { cout << gene << " "; }
        cout << "\n";
    }
    vector<int> fitness_last_gen = fitness(weights, values, population, capacity);
    cout << "Fitness da última geração:\n";
    for (int fit : fitness_last_gen) { cout << fit << " "; }
    cout << "\n";
    auto max_it = max_element(fitness_last_gen.begin(), fitness_last_gen.end());
    int best_index = distance(fitness_last_gen.begin(), max_it);
    best_individual = population[best_index];
    return {best_individual, fitness_history};
}

// Função principal
int main() {
    srand(time(0));

    int num_items = 40;
    int knapsack_capacity = 100;
    vector<int> item_number(num_items), weight(num_items), value(num_items);
    iota(item_number.begin(), item_number.end(), 1);

    // Criando a lista dos itens
    for (int i = 0; i < num_items; i++) {
        weight[i] = randomInt(1, 15);
        value[i] = randomInt(1, 100);
    }

    // Mostrando a lista e a capacidade de peso máxima
    cout << "Possíveis itens:\nItem\tPeso\tValor\n";
    for (int i = 0; i < num_items; i++) { cout << item_number[i] << "\t" << weight[i] << "\t" << value[i] << endl; }
    cout << "Capacidade da mochila: " << knapsack_capacity << endl;

    // Mostrando tamanho da população e a população inicial 
    int solutions_per_pop = 16;
    cout << "Tamanho da população = (" << solutions_per_pop << ", " << num_items << ")" << endl;
    vector<vector<int>> population(solutions_per_pop, vector<int>(num_items, 0));
    for (auto& individual : population) {
        for (int& gene : individual) { gene = randomInt(0, 1); }
    }
    cout << "População inicial:\n";
    for (const auto& individual : population) {
        for (const int gene : individual) { cout << gene << " "; }
        cout << endl;
    }

    // Obtendo melhor combinação e o fitness
    int num_generations = 1000;
    auto [best_individual, fitness_history] = optimize(weight, value, population, num_generations, knapsack_capacity);

    // Mostrando a melhor combinação
    cout << "Indivíduo da última geração com maior fitness: ";
    for (int gene : best_individual) { cout << gene << " "; }
    cout << endl;

    // Mostrando os itens e somando pesos e valores
    cout << "Quais itens irão na mochila: ";
    int total_weight = 0, total_value = 0;
    for (size_t i = 0; i < best_individual.size(); i++) {
        if (best_individual[i] != 0) {
            cout << item_number[i] << " ";
            total_weight += weight[i];
            total_value += value[i];
        }
    }
    cout << "\nPeso total da mochila = " << total_weight << endl;
    cout << "Valor total da mochila = " << total_value << endl;

    // Graph
    vector<double> fitness_history_mean;
    vector<int> fitness_history_max;
    for (const auto& generation_fitness : fitness_history) {
        if (generation_fitness.empty()) { fitness_history_mean.push_back(0); }
        else { 
            double sum = accumulate(generation_fitness.begin(), generation_fitness.end(), 0.0);
            fitness_history_mean.push_back(sum / generation_fitness.size());
        }
        fitness_history_max.push_back(*max_element(generation_fitness.begin(), generation_fitness.end()));
    }

    // Write data to a file for plotting
    ofstream file("fitness_history.csv");
    if (file.is_open()) {
        file << "Generation,MeanFitness,MaxFitness\n";
        for (size_t i = 0; i < fitness_history_mean.size(); ++i) {
            file << i << "," << int(fitness_history_mean[i]) << "," << fitness_history_max[i] << "\n";
        }
        file.close();
        cout << "Data written to fitness_history.csv for plotting.\n";
    } else {
        cerr << "Error: Unable to open file for writing.\n";
    }


    return 0;
}
