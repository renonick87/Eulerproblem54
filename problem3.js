var num = 600851475143;
var factor = [];

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
var newNum = num;
while(fact(newNum) !== false){
  let yes = fact(newNum); //factor
  newNum = newNum / yes;
  factor.push(yes)
}
var last = num;
for(var i = 0; i < factor.length; i++){
  last /= factor[i]
}
factor.push(last)
console.log(factor)