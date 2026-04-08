using System.Diagnostics;

namespace ExperimentalAnalysis
{
    public class BenchmarkRunner
    {
        private readonly int elementCount = 10000; // adjust if needed
        private readonly int trials = 20;
        private readonly Random rng = new Random(42);

        public void RunAllExperiments()
        {
            var results = new List<BenchmarkResult>();

            // Q1: append to end
            results.Add(Run("Q1_append_end", (isList) => AppendToEnd(isList), trials));

            // Q1b: List capacity tests (10 runs each)
            results.AddRange(RunListCapacityTests());

            // Q2: insert at random positions
            results.Add(Run("Q2_insert_random", InsertRandom, trials));

            // Q3a: remove first repeatedly
            results.Add(Run("Q3_remove_first", RemoveFirstRepeated, trials));

            // Q3b: remove last repeatedly
            results.Add(Run("Q3_remove_last", RemoveLastRepeated, trials));

            // Q4: remove random until empty
            results.Add(Run("Q4_remove_random_until_empty", RemoveRandomUntilEmpty, trials));

            // Q5: 10_000 random accesses
            results.Add(Run("Q5_random_access_10000", RandomAccesses10000, trials));

            PrintSummary(results);
        }

        private IEnumerable<BenchmarkResult> RunListCapacityTests()
        {
            var capacities = new[] { 10, 1_000, 100_000 };
            var listResults = new List<BenchmarkResult>();
            foreach (var cap in capacities)
            {
                listResults.Add(Run($"Q1_list_capacity_{cap}", (isList) => AppendToEnd(isList, initialCapacity: cap), 10));
            }
            return listResults;
        }

        private BenchmarkResult Run(string name, Func<bool, long> action, int runs)
        {
            long sumList = 0, sumLinked = 0;
            for (int i = 0; i < runs; i++)
            {
                sumList += action(true);
                sumLinked += action(false);
            }
            return new BenchmarkResult
            {
                Experiment = name,
                AvgListMs = sumList / (double)runs,
                AvgLinkedMs = sumLinked / (double)runs
            };
        }

        // Experiment implementations return elapsed milliseconds
        private long AppendToEnd(bool isList, int initialCapacity = 0)
        {
            if (isList)
            {
                var list = initialCapacity > 0 ? new List<int>(initialCapacity) : new List<int>();
                var sw = Stopwatch.StartNew();
                for (int i = 0; i < elementCount; i++) list.Add(i);
                sw.Stop();
                return sw.ElapsedMilliseconds;
            }
            else
            {
                var linked = new LinkedList<int>();
                var sw = Stopwatch.StartNew();
                for (int i = 0; i < elementCount; i++) linked.AddLast(i);
                sw.Stop();
                return sw.ElapsedMilliseconds;
            }
        }

        private long InsertRandom(bool isList)
        {
            if (isList)
            {
                var list = new List<int>();
                var sw = Stopwatch.StartNew();
                for (int i = 0; i < elementCount; i++)
                {
                    int pos = rng.Next(0, list.Count + 1);
                    list.Insert(pos, i);
                }
                sw.Stop();
                return sw.ElapsedMilliseconds;
            }
            else
            {
                var linked = new LinkedList<int>();
                var sw = Stopwatch.StartNew();
                for (int i = 0; i < elementCount; i++)
                {
                    int pos = rng.Next(0, linked.Count + 1);
                    if (pos == linked.Count) linked.AddLast(i);
                    else
                    {
                        var node = GetNodeAt(linked, pos);
                        linked.AddBefore(node, i);
                    }
                }
                sw.Stop();
                return sw.ElapsedMilliseconds;
            }
        }

        private long RemoveFirstRepeated(bool isList)
        {
            if (isList)
            {
                var list = Enumerable.Range(0, elementCount).ToList();
                var sw = Stopwatch.StartNew();
                while (list.Count > 0) list.RemoveAt(0);
                sw.Stop();
                return sw.ElapsedMilliseconds;
            }
            else
            {
                var linked = new LinkedList<int>(Enumerable.Range(0, elementCount));
                var sw = Stopwatch.StartNew();
                while (linked.Count > 0) linked.RemoveFirst();
                sw.Stop();
                return sw.ElapsedMilliseconds;
            }
        }

        private long RemoveLastRepeated(bool isList)
        {
            if (isList)
            {
                var list = Enumerable.Range(0, elementCount).ToList();
                var sw = Stopwatch.StartNew();
                while (list.Count > 0) list.RemoveAt(list.Count - 1);
                sw.Stop();
                return sw.ElapsedMilliseconds;
            }
            else
            {
                var linked = new LinkedList<int>(Enumerable.Range(0, elementCount));
                var sw = Stopwatch.StartNew();
                while (linked.Count > 0) linked.RemoveLast();
                sw.Stop();
                return sw.ElapsedMilliseconds;
            }
        }

        private long RemoveRandomUntilEmpty(bool isList)
        {
            if (isList)
            {
                var list = Enumerable.Range(0, elementCount).ToList();
                var sw = Stopwatch.StartNew();
                while (list.Count > 0)
                {
                    int pos = rng.Next(0, list.Count);
                    list.RemoveAt(pos);
                }
                sw.Stop();
                return sw.ElapsedMilliseconds;
            }
            else
            {
                var linked = new LinkedList<int>(Enumerable.Range(0, elementCount));
                var sw = Stopwatch.StartNew();
                while (linked.Count > 0)
                {
                    int pos = rng.Next(0, linked.Count);
                    var node = GetNodeAt(linked, pos);
                    linked.Remove(node);
                }
                sw.Stop();
                return sw.ElapsedMilliseconds;
            }
        }

        private long RandomAccesses10000(bool isList)
        {
            const int accesses = 10_000;
            if (isList)
            {
                var list = Enumerable.Range(0, elementCount).ToList();
                var sw = Stopwatch.StartNew();
                for (int i = 0; i < accesses; i++)
                {
                    int pos = rng.Next(0, list.Count);
                    var v = list[pos];
                }
                sw.Stop();
                return sw.ElapsedMilliseconds;
            }
            else
            {
                var linked = new LinkedList<int>(Enumerable.Range(0, elementCount));
                var sw = Stopwatch.StartNew();
                for (int i = 0; i < accesses; i++)
                {
                    int pos = rng.Next(0, linked.Count);
                    var node = GetNodeAt(linked, pos);
                    var v = node.Value;
                }
                sw.Stop();
                return sw.ElapsedMilliseconds;
            }
        }

        private LinkedListNode<int> GetNodeAt(LinkedList<int> list, int index)
        {
            // simple linear scan from head; could optimize by checking index vs count/2
            var node = list.First;
            for (int i = 0; i < index; i++) node = node.Next;
            return node;
        }

        private void PrintSummary(IEnumerable<BenchmarkResult> results)
        {
            Console.WriteLine("Experiment, AvgListMs, AvgLinkedMs, Ratio(List/Linked)");
            foreach (var r in results)
                Console.WriteLine($"{r.Experiment}: {r.AvgListMs:F2} ms, {r.AvgLinkedMs:F2} ms, ratio={(r.AvgLinkedMs > 0 ? r.AvgListMs / r.AvgLinkedMs : double.NaN):F2}");
        }
    }

    public class BenchmarkResult
    {
        public string Experiment { get; set; }
        public double AvgListMs { get; set; }
        public double AvgLinkedMs { get; set; }
    }
}
