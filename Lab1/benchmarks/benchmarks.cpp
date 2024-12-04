#include <benchmark/benchmark.h>

#include "Sorter.h"

static void ExternalSortBenchmark(benchmark::State& state) {
    for (auto _ : state) {
        Sorter sorter("1234", "12345", 2000);
        sorter.sortTapes();
    }
}
BENCHMARK(ExternalSortBenchmark)->Iterations(100);

int main(int argc, char** argv) {
    ::benchmark::Initialize(&argc, argv);
    if (::benchmark::ReportUnrecognizedArguments(argc, argv))
        return 1;
    ::benchmark::RunSpecifiedBenchmarks();
    return 0;
}