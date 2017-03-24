var one = 1;
var two = 2;
var sum = 2;

while(one.toString().split('').length < 20 && two.toString().split('').length < 20){
  if(one < two){
    one = one + two
  } else {
    two = one + two
  }
}
if(one > two){
  console.log(one)
} else {
  console.log(two)
}