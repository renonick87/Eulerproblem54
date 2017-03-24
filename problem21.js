var nums = []
function fact(num){
  let newNum = num;
  let factors = []
  for(var i = 1; i <= Math.pow(num, 0.5); i++){
    if(num % i === 0){
      factors.push(i)
      if(Math.pow(i, 2) !== num){
        factors.push(num / i)
      }
    }
  }
  //number sent is prime
  let sum = 0;
  factors.sort(function(a, b){return a-b})
  for(var i = 0; i < factors.length-1; i++){
    sum += factors[i]
  }
  return sum
}

for(var i = 0; i < 10000; i++){
  nums[i] = fact(i)
}
let sum = 0;
for(var i = 0; i < 10000; i++){
  if(i === nums[nums[i]] && !(i == nums[i])){
    sum += i
  }
}
console.log(sum)