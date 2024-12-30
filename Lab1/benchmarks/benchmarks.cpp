#include <thread>
#include <benchmark/benchmark.h>

#include "Sorter.h"
#include "LinearRegression.cpp"

static void ExternalSortBenchmark(benchmark::State& state) {
    for (auto _ : state) {
        Sorter sorter("SorterInput", "SorterOut", 10000);
        sorter.sortTapes();
    }
}
// BENCHMARK(ExternalSortBenchmark);
// BENCHMARK(ExternalSortBenchmark)->Iterations(100);

static void LinearRegressionBenchmark(benchmark::State& state) {
    for (auto _ : state) {
        Regression regressor;
        regressor.run_regression("RegressionInput");
    }
}
// BENCHMARK(LinearRegressionBenchmark);
// BENCHMARK(LinearRegressionBenchmark)->Iterations(1000);

void RegressionRunnerFunc() {
    Regression regressor;
    regressor.run_regression("RegressionInput");
}

void ExternalSorterRunnerFunc() {
    Sorter sorter("SorterInput", "SorterOut", 10000);
    sorter.sortTapes();
}

void LinearRegressionBenchmarkLoadThreads(benchmark::State& state) {
    const int numberOfThreads = state.range(0);

    for (auto _ : state) {
        std::vector<std::jthread> threads;

        for (int i = 0; i < numberOfThreads; ++i) {
            threads.emplace_back([&]() {
                RegressionRunnerFunc();
            });
        }
    }
}
BENCHMARK(LinearRegressionBenchmarkLoadThreads)
     ->Iterations(1)
     // ->Arg(100);
     ->Arg(1000);
    // ->Arg(5000);

static void ExternalSortingBenchmarkLoadThreads(benchmark::State& state) {
    const int numberOfThreads = state.range(0);

    for (auto _ : state) {
        std::vector<std::jthread> threads;

        for (int i = 0; i < numberOfThreads; ++i) {
            threads.emplace_back([&](){ExternalSorterRunnerFunc();});
        }
    }
}
// BENCHMARK(ExternalSortingBenchmarkLoadThreads)
// ->Iterations(1)
    // ->Arg(2);
    // ->Arg(4);
    // ->Arg(8);
    // ->Arg(16);
    // ->Arg(32);
    // ->Arg(64);

BENCHMARK_MAIN();