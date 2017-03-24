var sumOfSquares = 0;
var squareOfSums = 0;
for(var i = 1; i <= 100; i++){
  sumOfSquares += i * i
}
for(var i = 1; i <= 100; i++){
  squareOfSums += i
}
squareOfSums *= squareOfSums
console.log(sumOfSquares - squareOfSums)