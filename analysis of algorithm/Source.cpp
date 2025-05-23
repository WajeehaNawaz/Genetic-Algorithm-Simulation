#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;

// Constants
const int POPULATION_SIZE = 10;
const int CHROMOSOME_LENGTH = 10;
const int MAX_GENERATIONS = 10;
const double MUTATION_RATE = 0.1;
const double CROSSOVER_RATE = 0.7;

// Structure to represent a chromosome
struct Chromosome {
    int genes[CHROMOSOME_LENGTH];
    int fitness;
};

// Function to generate a random chromosome
Chromosome generateRandomChromosome() {
    Chromosome chromosome;
    for (int i = 0; i < CHROMOSOME_LENGTH; i++) {
        chromosome.genes[i] = rand() % 2;
    }
    chromosome.fitness = 0;
    return chromosome;
}

// Function to calculate the fitness of a chromosome
int calculateFitness(Chromosome chromosome) {
    int fitness = 0;
    for (int i = 0; i < CHROMOSOME_LENGTH; i++) {
        if (chromosome.genes[i] == 1) {
            fitness++;
        }
    }
    return fitness;
}

// Function to perform crossover between two chromosomes
Chromosome crossover(Chromosome parent1, Chromosome parent2) {
    Chromosome child;
    int crossoverPoint = rand() % CHROMOSOME_LENGTH;
    for (int i = 0; i < crossoverPoint; i++) {
        child.genes[i] = parent1.genes[i];
    }
    for (int i = crossoverPoint; i < CHROMOSOME_LENGTH; i++) {
        child.genes[i] = parent2.genes[i];
    }
    child.fitness = 0;
    return child;
}

// Function to perform mutation on a chromosome
Chromosome mutate(Chromosome chromosome) {
    for (int i = 0; i < CHROMOSOME_LENGTH; i++) {
        if ((double)rand() / RAND_MAX < MUTATION_RATE) {
            chromosome.genes[i] = 1 - chromosome.genes[i];
        }
    }
    chromosome.fitness = 0;
    return chromosome;
}

// Function to perform selection (Fitness Proportional Selection)
Chromosome select(Chromosome population[], int populationSize) {
    int totalFitness = 0;
    for (int i = 0; i < populationSize; i++) {
        totalFitness += population[i].fitness;
    }
    int selection = rand() % totalFitness;
    int cumulativeFitness = 0;
    for (int i = 0; i < populationSize; i++) {
        cumulativeFitness += population[i].fitness;
        if (cumulativeFitness >= selection) {
            return population[i];
        }
    }
    return population[populationSize - 1];
}

int main() {
    srand(time(0));
    Chromosome population[POPULATION_SIZE];

    // Initialize population
    for (int i = 0; i < POPULATION_SIZE; i++) {
        population[i] = generateRandomChromosome();
        population[i].fitness = calculateFitness(population[i]);
    }

    int bestFitness = 0;
    int bestGeneration = -1; // Initialize bestGeneration to -1

    for (int generation = 0; generation < MAX_GENERATIONS; generation++) {
        Chromosome newPopulation[POPULATION_SIZE];

        for (int i = 0; i < POPULATION_SIZE; i++) {
            Chromosome parent1 = select(population, POPULATION_SIZE);
            Chromosome parent2 = select(population, POPULATION_SIZE);
            Chromosome child = crossover(parent1, parent2);
            child = mutate(child);
            child.fitness = calculateFitness(child);
            newPopulation[i] = child;
        }

        // Replace old population with the new population
        for (int i = 0; i < POPULATION_SIZE; i++) {
            population[i] = newPopulation[i];
        }

        // Find the best fitness in the current generation
        int currentBestFitness = 0;
        for (int i = 0; i < POPULATION_SIZE; i++) {
            if (population[i].fitness > currentBestFitness) {
                currentBestFitness = population[i].fitness;
            }
        }

        // Update best fitness and track first occurrence
        if (currentBestFitness > bestFitness) {
            bestFitness = currentBestFitness;
            bestGeneration = generation; // Update bestGeneration only when a new best fitness is found
        }

        // Print intermediate results (optional)
        cout << "Generation: " << generation << ", Best Fitness: " << currentBestFitness << endl;
    }

    // Print the results
    cout << "\nOverall Best Fitness: " << bestFitness << endl;
    cout << "First Achieved in Generation: " << bestGeneration << endl;

    return 0;
}