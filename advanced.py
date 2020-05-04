import pyomp

if __name__ == '__main__':
    eq = pyomp.EquityCalculator()
    ranges = [pyomp.CardRange("QQ+,AKs,AcQc"), pyomp.CardRange("A2+"), pyomp.CardRange("random")]
    board = pyomp.CardRange.getCardMask("2c4c5h")
    dead = pyomp.CardRange.getCardMask("Jc")
    stdErrMargin = 2e-5 # stop when standard error below 0.002%
    def callback(results):
        print(results.equity[0], 100 * results.progress, 1e-6 * results.intervalSpeed)
        if results.time > 5: # Stop after 5s
            eq.stop()

    updateInterval = 0.25 # Callback called every 0.25s.
    threads = 0 # max hardware parallelism (default)
    eq.start(ranges, board, dead, False, stdErrMargin, callback, updateInterval, threads)
    eq.wait()
    r = eq.getResults()
    print()
    print(r.equity[0],r.equity[1], r.equity[2])
    print(r.wins[0],r.wins[1], r.wins[2])
    print(r.hands, r.time, 1e-6 * r.speed, r.stdev)
