//Will not list entire number outside of scientific notation
var two = Math.pow(2, 100).toString().split('')
var sum = 0;
for(var i = 0; i < two.length; i++){
  sum += parseInt(two[i])
}
console.log(two)
console.log(sum)