var best = 0
for(var i = 0; i < 10; i++){
  for(var j = 0; j < 10; j++){
    for(var k = 0; k < 10; k++){
      for(var l = 0; l < 10; l++){
        for(var m = 0; m < 10; m++){
          for(var n = 0; n < 10; n++){
            let sum = Math.pow(i, 5) + Math.pow(j, 5) + Math.pow(k, 5) + Math.pow(l, 5) + Math.pow(m, 5) + Math.pow(n, 5)
            let digits = parseInt(i.toString() + j.toString() + k.toString() + l.toString() + m.toString() + n.toString())
            if(sum === digits && sum !== 1 && sum !== 0){
              best += sum
            }
          }
        }
      }
    }
  }
}
console.log(best)