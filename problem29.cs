List set = new List();

for (int a = 2; a <= 100; a++) {
    for (int b = 2; b <= 100; b++) {
        double result = Math.Pow(a, b);
        if (!set.Contains(result)) {
            set.Add(result);
        }
    }
}