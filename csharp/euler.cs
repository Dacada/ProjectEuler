using System;
using System.Diagnostics;
using System.Linq;
using System.Collections.Generic;

namespace Euler
{
  /// <summary>
  /// Generates primes in such a way that it can be called multiple times with
  /// different values and only generate new primes when needed.
  /// </summary>
  public class PrimesRepeat
  {
    private List<long> primes;
    private long last;

    public PrimesRepeat()
    {
      this.primes = new List<long> { 2 };
      this.last = 2;
    }

    public bool IsPrime(long n)
    {
      if (n == this.last)
      {
        return true;
      }
      else if (n < this.last)
      {
        return this.primes.BinarySearch(n) >= 0;
      }
      else
      {
        for (long i = this.last+1;; i++)
        {
          if (Euler.IsPrime(i))
          {
            this.primes.Add(i);
            if (i == n)
            {
              this.last = i;
              return true;
            }
            else if (i > n)
            {
              this.last = i;
              return false;
            }
          }
        }
      }
    }
  }

  public static class Euler
  {
    /// <summary>
    /// Execute and time the given action. Display the time taken to run.
    /// </summary>
    public static void TimeWrapper(Action action)
    {
      var timer = new Stopwatch();
      timer.Start();
      action();
      timer.Stop();
      Console.WriteLine(timer.Elapsed.TotalSeconds);
    }

    /// <summary>
    /// Return the prime factors of the given number.
    /// </summary>
    public static long[] Factorize(long n)
    {
      string output;
      using (var p = new Process())
      {
        p.StartInfo.FileName = "factor";
        p.StartInfo.Arguments = n.ToString();
        p.StartInfo.UseShellExecute = false;
        p.StartInfo.RedirectStandardOutput = true;
        p.Start();

        output = p.StandardOutput.ReadToEnd();
        p.WaitForExit();
      }

      var numberAndFactors = output.Split(':');
      if (string.IsNullOrWhiteSpace(numberAndFactors[1]))
        return new long[] { };

      return numberAndFactors[1].Trim().Split()
        .Select(x => long.Parse(x.Trim())).ToArray();
    }

    /// <summary>
    /// Return whether a number is prime.
    /// </summary>
    public static bool IsPrime(long n)
    {
      var limit = Math.Ceiling(Math.Sqrt(n));
      for (long divisor = 2; divisor <= limit; divisor++)
      {
        if (n % divisor == 0)
          return false;
      }
      return true;
    }

    /// <summary>
    /// Return the greatest common divisor of two numbers.
    /// </summary>
    public static long Gcd(long a, long b)
    {
      if (b == 0)
        return a;
      else
        return Gcd(b, a%b);
    }

    /// <summary>
    /// Return an iterator of all the primes up to the given limit.
    /// </summary>
    public static IEnumerable<long> PrimesSieve(long limit)
    {
      if (limit < 2)
      {
        yield break;
      }

      var sieve = new bool[limit];
      sieve[0] = false;
      sieve[1] = false;
      for (int i=2; i<limit; i++)
      {
        sieve[i] = true;
      }

      for (int i=2; i<limit; i++)
      {
        if (sieve[i])
        {
          yield return i;
          for (int j=i*2; j<limit; j+=i)
          {
            sieve[j] = false;
          }
        }
      }
    }

    /// <summary>
    /// Return the text from an url
    /// </summary>
    public static string ReadURL(string address)
    {
      var client = new System.Net.WebClient();
      string reply = client.DownloadString (address);

      Console.WriteLine (reply);
      return null;
    }

    /// <summary>
    /// Return the sum of the propper divisors of n
    /// </summary>
    public static long SumDivisors(long n)
    {
      var factors = Euler.Factorize(n);
      long result = 1;
      foreach (var p in factors.Distinct()) {
        var a = factors.Where(x => x == p).Count();
        result *= Enumerable.Range(0, a+1).Select(ai => (long)Math.Pow(p, ai)).Sum();
      }
      return result - n;
    }
  }
}
