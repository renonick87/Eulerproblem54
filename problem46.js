function isPrime(value) {
    for(var i = 2; i <= Math.pow(value, 0.5); i++) {
        if(value % i === 0) {
            return false;
        }
    }
    return value > 1;
}

var prime = [];

for(var i = 0; i < 10000; i++){
  if(isPrime(i)){
    prime.push(i)
  }
}

var i = 1
var confirmed = true
while(confirmed){
  i += 2
  if(!isPrime(i)){
    let j = 0
    while(i > prime[j]){
      let square = Math.pow((i - prime[j])/2, 0.5)
      let isSquare = (square === Math.floor(square))
      if(isSquare){
        confirmed = true
        break;
      } else {
        confirmed = false
        console.log(i, prime[j], square)
      }
      j++
    }
  }
}
console.log(i)
console.log(prime[1228])