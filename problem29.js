// I DON'T KNOW WHY IT DOESN"T WORK
var nums = [];
var dupes = 0;
var squaresOfSquaresDupes = 0;
var cubesDupes = 0;
for(var a = 2; a <= 100; a++){
  for(var b = 2; b <= 100; b++){
    let result = Math.pow(a, b)
    if(nums.indexOf(result) === -1){
      nums.push(result)
    } /*else {
      let root = Math.pow(a, 0.5)
      let bool = (Math.pow(root, 1/3) === Math.floor(Math.pow(root, 1/3)))
      if(root === Math.floor(root) && b << 50 && !(Math.pow(root, 0.5) === Math.floor(Math.pow(root, 0.5))) && !bool){
        //console.log(a)
        squaresOfSquaresDupes++
      }
      let cubic = Math.pow(a, 1/3)
      bool = b < 34 || (b % 2 === 0 && b <= 66)
      if(cubic === Math.floor(cubic) && !(Math.pow(cubic, 0.5) === Math.floor(Math.pow(cubic, 0.5))) && bool){
        console.log(a, b)
        cubesDupes++
      }
      dupes++
    }*/
  }
}
nums.sort(function(a,b){return a-b})
//console.log(nums)
console.log(nums.length)
console.log('Total dupes: %s', dupes)
console.log('squaresOfSquaresDupes: %s', squaresOfSquaresDupes)
console.log('cubesDupes: %s', cubesDupes)