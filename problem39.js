var pythagorus = []
for(var a = 1; a <= 120; a++){
  for(var b = 1; b < 120 - a; b++){
    let c = 120 - b - a;
    let arr = [a,b,c]
    arr.sort(function(a, b){return a-b})
     if((Math.pow(arr[0],2) + Math.pow(arr[1], 2) === Math.pow(arr[2], 2)) && pythagorus.indexOf(arr) === -1){
       console.log(pythagorus)
       pythagorus.push(arr)
     }
  }
}
console.log(pythagorus)