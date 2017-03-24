//142913828922
function fact(num){
  let newNum = num
  for(var i = 2; i <= Math.pow(num, 0.5); i++){
    if(num % i === 0){
      return i
    }
  }
  //number sent is prime
  return  false
}
var sum = 0;
for(var i = 2; i < 2000000; i++){
  if(!fact(i)){
    sum += i
  }
}
console.log(sum)