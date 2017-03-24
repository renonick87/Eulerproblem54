var pals = [];
var prod;
for(var i = 100; i < 1000; i++){
  for(var j = 100; j < 1000; j++){
    prod = i * j;
    if(prod.toString() == prod.toString().split("").reverse().join("")){
      pals.push(prod)
    }
  }
}
var best = 0;
for(var i = 0; i < pals.length; i++){
  if(pals[i] > best){
    best = pals[i]
  }
}
console.log(best)