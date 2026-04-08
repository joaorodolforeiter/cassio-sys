namespace ExperimentalAnalysis
{
    internal class Program
    {
        static void Main(string[] args)
        {
            var runner = new BenchmarkRunner();
            runner.RunAllExperiments();
        }
    }
}
