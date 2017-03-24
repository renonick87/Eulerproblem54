var one = 1;
var two = 2;
var sum = 2;

while(one < 4000000 && two < 4000000){
  if(one < two){
    one = one + two
    if(one % 2 === 0){
      sum += one
    }
  } else {
    two = one + two
    if(two % 2 === 0){
      sum += two
    }
  }
}
console.log(sum)