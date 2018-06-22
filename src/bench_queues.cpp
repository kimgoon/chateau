#include "benchmark/benchmark.h"

#include "fastqueue.h"
#include <string>

static void BM_StringCreation(benchmark::State& state)
{
    for (auto _ : state)
    {
        std::string empty_string("11");
        benchmark::DoNotOptimize(empty_string.c_str());
        benchmark::ClobberMemory();
    }
}
BENCHMARK(BM_StringCreation);

static void BM_UnsafeQueue(benchmark::State& state)
{
    FastQueueSPSC<int> fq;

    auto val = new int(12);
    for(auto _ : state)
    {
        fq.push(val);
        benchmark::DoNotOptimize(fq.pop());
        benchmark::ClobberMemory();
    }
    delete val;
}
BENCHMARK(BM_UnsafeQueue);

static void BM_AtomicQueue(benchmark::State& state)
{
    FastQueueAtomicSPSC<int> fq;

    auto val = new int(12);
    for(auto _ : state)
    {
        fq.push(val);
        fq.pop();
    }
    delete val;
}
BENCHMARK(BM_AtomicQueue);


BENCHMARK_MAIN();
