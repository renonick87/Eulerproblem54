function fact(num){
  let newNum = num
  for(var i = 2; i < num / 2; i++){
    if(num % i === 0){
      return i
    }
  }
  //number sent is prime
  return false
}
var primes = [2, 3 ,5];
while(primes.length != 10001){
  for(var i = primes[primes.length - 1] + 1; i < 10000000000; i++){
    if(!fact(i)){
      primes.push(i)
      break;
    }
  }
}
console.log(primes[primes.length - 1])