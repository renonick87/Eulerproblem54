Class Problem29{
  public static void main(){
SortedSet&lt;BigInteger&gt; setResultsBigInteger = new TreeSet&lt;&gt;();
SortedSet&lt;Double&gt; setResultsDouble = new TreeSet&lt;&gt;();
for (int intA=2; intA&lt;=200; intA++) {
    for (int intB=2; intB&lt;=200; intB++) {
        BigInteger biResult = BigInteger.valueOf(intA).pow(intB);
        Double dblResult = Math.pow(intA,intB);
        setResultsBigInteger.add(biResult);
        setResultsDouble.add(dblResult);
    }
}
System.out.println(setResultsBigInteger.size());
System.out.println(setResultsDouble.size());
}
}