using System.Diagnostics;

namespace ExperimentalAnalysis;

public class BenchmarkRunner
{
    private const int ElementCount = 10000; // adjust if needed
    private const int Trials = 20;
    private readonly Random rng = new(42);

    public void RunAllExperiments()
    {
        var results = new List<BenchmarkResult>();

        // Q1: append to end
        results.Add(RunBenchmark("Q1_append_end", AppendToEndList, AppendToEndLinked, Trials));

        // Q1b: List capacity tests (10 runs each)
        results.AddRange(RunListCapacityTests());

        // Q2: insert at random positions
        results.Add(RunBenchmark("Q2_insert_random", InsertRandomList, InsertRandomLinked, Trials));

        // Q3a: remove first repeatedly
        results.Add(RunBenchmark("Q3_remove_first", RemoveFirstRepeatedList, RemoveFirstRepeatedLinked, Trials));

        // Q3b: remove last repeatedly
        results.Add(RunBenchmark("Q3_remove_last", RemoveLastRepeatedList, RemoveLastRepeatedLinked, Trials));

        // Q4: remove random until empty
        results.Add(RunBenchmark("Q4_remove_random_until_empty", RemoveRandomUntilEmptyList,
            RemoveRandomUntilEmptyLinked, Trials));

        // Q5: 10_000 random accesses
        results.Add(RunBenchmark("Q5_random_access_10000", RandomAccesses10000List, RandomAccesses10000Linked, Trials));

        PrintSummary(results);
    }

    private IEnumerable<BenchmarkResult> RunListCapacityTests()
    {
        var capacities = new[] { 10, 1_000, 100_000 };
        var listResults = new List<BenchmarkResult>();
        foreach (var cap in capacities)
        {
            listResults.Add(RunBenchmark($"Q1_list_capacity_{cap}",
                () => AppendToEndList(cap),
                () => 0,
                10));
        }
        return listResults;
    }

    private BenchmarkResult RunBenchmark(string name, Func<long> listAction, Func<long> linkedAction, int runs)
    {
        long sumList = 0, sumLinked = 0;
        for (var i = 0; i < runs; i++)
        {
            sumList += listAction();
            sumLinked += linkedAction();
        }

        return new BenchmarkResult
        {
            Experiment = name,
            AvgListMs = sumList / (double)runs,
            AvgLinkedMs = sumLinked / (double)runs
        };
    }

    private long AppendToEndList()
    {
        return AppendToEndList(0);
    }

    // Experiment implementations return elapsed milliseconds
    private long AppendToEndList(int initialCapacity)
    {
        var list = initialCapacity > 0 ? new List<int>(initialCapacity) : new List<int>();
        var sw = Stopwatch.StartNew();
        for (var i = 0; i < ElementCount; i++) list.Add(i);
        sw.Stop();
        return sw.Elapsed.Nanoseconds;
    }

    private long AppendToEndLinked()
    {
        var linked = new LinkedList<int>();
        var sw = Stopwatch.StartNew();
        for (var i = 0; i < ElementCount; i++) linked.AddLast(i);
        sw.Stop();
        return sw.Elapsed.Nanoseconds;
    }

    private long InsertRandomList()
    {
        var list = new List<int>();
        var sw = Stopwatch.StartNew();
        for (var i = 0; i < ElementCount; i++)
        {
            var pos = rng.Next(0, list.Count + 1);
            list.Insert(pos, i);
        }

        sw.Stop();
        return sw.Elapsed.Nanoseconds;
    }

    private long InsertRandomLinked()
    {
        var linked = new LinkedList<int>();
        var sw = Stopwatch.StartNew();
        for (var i = 0; i < ElementCount; i++)
        {
            var pos = rng.Next(0, linked.Count + 1);
            if (pos == linked.Count)
            {
                linked.AddLast(i);
            }
            else
            {
                var node = GetNodeAt(linked, pos);
                linked.AddBefore(node, i);
            }
        }

        sw.Stop();
        return sw.Elapsed.Nanoseconds;
    }

    private long RemoveFirstRepeatedList()
    {
        var list = Enumerable.Range(0, ElementCount).ToList();
        var sw = Stopwatch.StartNew();
        while (list.Count > 0) list.RemoveAt(0);
        sw.Stop();
        return sw.Elapsed.Nanoseconds;
    }

    private long RemoveFirstRepeatedLinked()
    {
        var linked = new LinkedList<int>(Enumerable.Range(0, ElementCount));
        var sw = Stopwatch.StartNew();
        while (linked.Count > 0) linked.RemoveFirst();
        sw.Stop();
        return sw.Elapsed.Nanoseconds;
    }

    private long RemoveLastRepeatedList()
    {
        var list = Enumerable.Range(0, ElementCount).ToList();
        var sw = Stopwatch.StartNew();
        while (list.Count > 0) list.RemoveAt(list.Count - 1);
        sw.Stop();
        return sw.Elapsed.Nanoseconds;
    }

    private long RemoveLastRepeatedLinked()
    {
        var linked = new LinkedList<int>(Enumerable.Range(0, ElementCount));
        var sw = Stopwatch.StartNew();
        while (linked.Count > 0) linked.RemoveLast();
        sw.Stop();
        return sw.Elapsed.Nanoseconds;
    }

    private long RemoveRandomUntilEmptyList()
    {
        var list = Enumerable.Range(0, ElementCount).ToList();
        var sw = Stopwatch.StartNew();
        while (list.Count > 0)
        {
            var pos = rng.Next(0, list.Count);
            list.RemoveAt(pos);
        }

        sw.Stop();
        return sw.Elapsed.Nanoseconds;
    }

    private long RemoveRandomUntilEmptyLinked()
    {
        var linked = new LinkedList<int>(Enumerable.Range(0, ElementCount));
        var sw = Stopwatch.StartNew();
        while (linked.Count > 0)
        {
            var pos = rng.Next(0, linked.Count);
            var node = GetNodeAt(linked, pos);
            linked.Remove(node);
        }

        sw.Stop();
        return sw.Elapsed.Nanoseconds;
    }

    private long RandomAccesses10000List()
    {
        const int accesses = 10_000;
        var list = Enumerable.Range(0, ElementCount).ToList();
        var sw = Stopwatch.StartNew();
        for (var i = 0; i < accesses; i++)
        {
            var pos = rng.Next(0, list.Count);
            var v = list[pos];
        }

        sw.Stop();
        return sw.Elapsed.Nanoseconds;
    }

    private long RandomAccesses10000Linked()
    {
        const int accesses = 10_000;
        var linked = new LinkedList<int>(Enumerable.Range(0, ElementCount));
        var sw = Stopwatch.StartNew();
        for (var i = 0; i < accesses; i++)
        {
            var pos = rng.Next(0, linked.Count);
            var node = GetNodeAt(linked, pos);
            var v = node.Value;
        }

        sw.Stop();
        return sw.Elapsed.Nanoseconds;
    }

    private LinkedListNode<int> GetNodeAt(LinkedList<int> list, int index)
    {
        // simple linear scan from head; could optimize by checking index vs count/2
        var node = list.First;
        for (var i = 0; i < index; i++) node = node.Next;
        return node;
    }

    private void PrintSummary(IEnumerable<BenchmarkResult> results)
    {
        Console.WriteLine($"{"Experiment",-30}|\tAvgListMs\t|\tAvgLinkedMs\t|\tRatio(List/Linked)");
        foreach (var r in results)
        {
            Console.WriteLine($"{r.Experiment,-30}|\t{r.AvgListMs:F2} ns\t|\t{r.AvgLinkedMs:F2} ns\t|\tratio={(r.AvgLinkedMs > 0 ? r.AvgListMs / r.AvgLinkedMs : double.NaN):F2}");
        }
            
    }
}

public class BenchmarkResult
{
    public required string Experiment { get; set; }
    public double AvgListMs { get; set; }
    public double AvgLinkedMs { get; set; }
}