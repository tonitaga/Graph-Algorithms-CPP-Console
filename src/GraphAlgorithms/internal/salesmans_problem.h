#ifndef GRAPHALGORITHMS_SALESMANS_PROBLEM_H
#define GRAPHALGORITHMS_SALESMANS_PROBLEM_H

#include <cmath>
#include <memory>
#include <random>
#include <chrono>
#include <algorithm>

#include "graph.h"

namespace ng {
    template <typename T>
    struct TsmProblem {
        static_assert(std::is_fundamental<T>::value, "Template parameter T must be fundamental");

        std::vector<std::size_t> vertices;
        T distance = 0;
    };

    template <typename T>
    class AntColony {
    public:
        explicit AntColony(const Graph<T> &graph);

        TsmProblem<T> SolveSalesmansProblem();

    private:
        struct Ant {
            explicit Ant(std::size_t start_vertex = 0) : start_location(start_vertex), current_location(start_vertex){};

            TsmProblem<T> path;
            std::vector<std::size_t> visited;
            std::size_t start_location = 0;
            std::size_t current_location = 0;
            bool can_continue = true;

            void MakeChoice(const Graph<T> &graph, const Matrix<double> &pheromone, double alpha, double beta);
            double GetRandomChoice();
        };

        const double kAlpha_ = 2.0;
        const double kBeta_ = 1.0;
        const double kPheromone0_ = 2;
        const double kQ_ = 64.0;
        const double kEvaporation_ = 0.2;

        Graph<T> graph_;
        Matrix<double> pheromone_;

        std::vector<Ant> ants_;

        void CreateAnts();
        void CalculatePheromone(const Matrix<double> &summary_pheromone);
    };

    template<typename T>
    AntColony<T>::AntColony(const Graph<T> &graph)
        : graph_(graph)
    {
        const std::size_t kVertexesCount = graph_.getVertexesCount();
        Matrix<double> matrix(kVertexesCount);
        for (std::size_t row = 0; row != kVertexesCount; ++row)
            for (std::size_t col = 0; col != kVertexesCount; ++col)
                if (row != col)
                    matrix(row, col) = kPheromone0_;
        pheromone_ = std::move(matrix);
    }


    template<typename T>
    void AntColony<T>::CreateAnts() {
        const auto kAntsCount = graph_.getVertexesCount();
        ants_.resize(kAntsCount);

        std::size_t start_vertex = 0;
        for (auto &ant : ants_)
            ant = Ant(start_vertex++);
    }

    template<typename T>
    TsmProblem<T> AntColony<T>::SolveSalesmansProblem() {
        constexpr std::size_t kMaxIterationsWithoutImprovement = 500;
        const std::size_t kVertexesCount = graph_.getVertexesCount();
        std::size_t counter = 0;

        TsmProblem<T> path;
        path.distance = kInf<T>;

        // FOR DEBUG
        int current_generation = 1;

        while (counter++ != kMaxIterationsWithoutImprovement) {
            Matrix<double> summary_pheromone(kVertexesCount, 0.0);
            CreateAnts();
            for (auto &ant : ants_) {
                while (ant.can_continue)
                    ant.MakeChoice(graph_, pheromone_, kAlpha_, kBeta_);

                auto ant_path = ant.path;
                if (ant_path.vertices.size() == kVertexesCount + 1) {
                    if (path.distance > ant.path.distance) {
                        path = std::move(ant.path);

                        // DEBUG
                        std::cout << "Generation: " << current_generation << "; Find shorter path:\n";
                        for (auto v : path.vertices)
                            std::cout << v << ' ';
                        std::cout << '\n';
                        std::cout << "Length: " << path.distance << '\n';

                        counter = 0;
                    }
                }

                for (std::size_t v = 0; v != ant_path.vertices.size() - 1; ++v)
                    summary_pheromone(ant_path.vertices[v], ant_path.vertices[v + 1]) += kQ_ / ant_path.distance;
            }
            current_generation++;
            CalculatePheromone(summary_pheromone);

//            std::cout << "Pheromone matrix after " << current_generation++ << " generation:\n";
//            std::cout << pheromone_ << std::endl;
        }

        return path;
    }

    template <typename T>
    void AntColony<T>::CalculatePheromone(const Matrix<double> &summary_pheromone) {
        for (std::size_t from = 0, size = summary_pheromone.getRows(); from != size; ++from)
            for (std::size_t to = 0; to != size; ++to) {
                pheromone_(from, to) = (1 - kEvaporation_) * pheromone_(from, to) + summary_pheromone(from, to);
                if (pheromone_(from, to) < 0.1 and from != to)
                    pheromone_(from, to) = 0.1;
            }
    }

    template <typename T>
    double AntColony<T>::Ant::GetRandomChoice() {
        std::uniform_real_distribution<> dist(0.0, 1.0);
        std::default_random_engine re(std::chrono::system_clock::now().time_since_epoch().count());
        return dist(re);
    }

    template <typename T>
    void AntColony<T>::Ant::MakeChoice(const Graph<T> &graph, const Matrix<double> &pheromone, double alpha, double beta) {
        if (path.vertices.empty()) {
            path.vertices.push_back(current_location);
            visited.push_back(current_location);
        }

        std::vector<std::size_t> neighbor_vertexes;
        for (std::size_t to = 0; to != graph.getVertexesCount(); ++to)
            if (graph(current_location, to) != 0 and std::find(visited.begin(), visited.end(), to) == visited.end())
                neighbor_vertexes.push_back(to);

        if (neighbor_vertexes.empty()) {
            can_continue = false;
            if (graph(current_location, start_location) != 0) {
                path.vertices.push_back(start_location);
                path.distance += graph(current_location, start_location);
            }
            return;
        }


        std::vector<double> choosing_probability(neighbor_vertexes.size());

        {
            std::vector<double> wish;
            std::vector<double> probability;
            double summary_wish = 0.0f;
            for (auto v : neighbor_vertexes) {
                double t = pheromone(current_location, v);
                double w = graph(current_location, v);
                double n = 1 / w;
                wish.push_back(std::pow(t, alpha) * std::pow(n, beta));
                summary_wish += wish.back();
            }

            for (std::size_t neighbor = 0; neighbor != neighbor_vertexes.size(); ++neighbor) {
                probability.push_back(wish[neighbor] / summary_wish);
                if (neighbor == 0)
                    choosing_probability[neighbor] = probability.back();
                else
                    choosing_probability[neighbor] = choosing_probability[neighbor - 1] + probability.back();
            }
        }

        std::size_t next_vertex = 0;
        double choose = GetRandomChoice();

        for (std::size_t neighbor = 0; neighbor != neighbor_vertexes.size(); ++neighbor) {
            if (choose <= choosing_probability[neighbor]) {
                next_vertex = neighbor_vertexes[neighbor];
                break;
            }
        }

        path.vertices.push_back(next_vertex);
        visited.push_back(next_vertex);
        path.distance += graph(current_location, next_vertex);
        current_location = next_vertex;
    }
}

#endif //GRAPHALGORITHMS_SALESMANS_PROBLEM_H
