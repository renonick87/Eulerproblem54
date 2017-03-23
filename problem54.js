var hands = ['High Card', 'One Pair', 'Two Pairs', 'Three of a Kind', 'Straight', 'Flush', 'Full House', 'Four of a Kind', 'Straight Flush', 'Royal Flush']
var cards = ['1', '2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K', 'A']
var hand = '8C TS KC 9H 4S 7D 2S 5D 3S AC'.split(' ')
var fs = require('fs')
var it;
var test = ['8C', '9C', 'AC', 'JC', 'TC']
var test2 = ['Qd', 'Kd', 'Jd', 'Td', '4d']
var wins = 0;

Array.prototype.multiIndexOf = function (el) {
    var idxs = [];
    for (var i = this.length - 1; i >= 0; i--) {
        if (this[i] === el) {
            idxs.unshift(i);
        }
    }
    return idxs;
};
//console.log(cards.indexOf('A'))

function highCard(x){
  var best = 0
  //console.log(x)
  if(cards.indexOf(x[0][0]) > best){
    best = cards.indexOf(x[0][0])
  }
  if(cards.indexOf(x[1][0]) > best){
    best = cards.indexOf(x[1][0])
  }
  if(cards.indexOf(x[2][0]) > best){
    best = cards.indexOf(x[2][0])
  }
  if(cards.indexOf(x[3][0]) > best){
    best = cards.indexOf(x[3][0])
  }
  if(cards.indexOf(x[4][0]) > best){
    best = cards.indexOf(x[4][0])
  }
  return best
}

function ofAKind(x, sameHand = false, q = 0){
  var nums = []
  var holder = []
  for(var i = 0; i < x.length; i++){ // Build an array to hold the number value of the cards
    holder.push(x[i][0])
  }
  for(var i = 0; i < x.length; i++){
    let y = holder.multiIndexOf(holder[i])
    if(y.length > 1){ //if there are multiple instances of a number
      let nope = true // boolean to say whether the currrent number has been added already
      for(var j = 0; j < nums.length; j++){
        if(nums[j][0] === y[0]){
          nope = false //set to false to indicate that the duplicates have already been accounted for
          break;
        }
      }
      if(nope){
        nums.push(y)
      }
      /*if(nums[0] === undefined){
        nums.push(y) //store as the first instance of multiple instances
        console.log(nums.indexOf(y))
      } else if (nums.contains(y) === -1){
        nums.push(y) //store as the first instance of multiple instances
        console.log(nums.indexOf(y))
      }*/
      //nums.push(y)
      //for(var j = 0; j < nums.length; j++){
      //  x.splice(nums[j], 1) //remove multiple instances of the first character with multiple instances from x
      //}
    }
  }
  /*for(var i = 0; i < nums.length; i++){
    let z = nums.multiIndexOf(nums[i])
    if(z.length > 1){
      console.log('sure')
      for(var j = 0; j < z.length; j++){
        nums.splice(z[j], 1)
      }
    }
  }*/
  if(nums.length === 0){ //There are no numbers that appear multiple times
    return false
  } else if(nums.length === 2){ //There are two cards that have multiple instances(Full House or Two Pair)
    if(nums[0].length === 3){ //One card has three instances, Full House
      if(sameHand){
        return x[nums[0][0]]
      }
      return 'Full House'
    } else if(nums[1].length === 3){
      if(sameHand){
        return x[nums[1][0]]
      }
      return 'Full House'
    } else { // Two Pair
      if(sameHand === true){
        return x[nums[q][0]]
      } else if(sameHand === 'bear'){
        for(var i = 0; i < 5; i++){
          if(nums[0].indexOf(i) === -1 && nums[1].indexOf(i) === -1){
            if(nums[0].indexOf(i) === -1){
              return x[i][0]
            }
            return x[i][0]
          }
        }
      }
      return 'Two Pair'
    }
  } else if(nums.length === 1){ //There is one card with multiple instances(Pair, Three of a Kind, Four of a Kind)
    var first = nums[0].length
    if(first === 2){// Pair
      if(sameHand){
        return x[nums[0][0]]
      }
      return 'Pair'
    } else if(first === 3){//Three of a Kind
      if(sameHand){
        return x[nums[0][0]]
      }
      return 'Three of a Kind'
    } else if(first === 4){//Four of a Kind
      if(sameHand){
        return x[nums[0][0]]
      }
      return 'Four of a Kind'
    }
  }
}

function aceAndTen(x){
  var l = x.filter(function(word, index){
    if(word.match('A')){
      //console.log(index);
      return true;
    }
    return false
  }) +''+ x.filter(function(word, index){
    if(word.match('T')){
      //console.log(index);
      return true;
    }
    return false
  })
  if(l[0] === 'A' && l[2] === 'T'){
    return true
  }
  return false
}
//console.log(test.indexOf(l))

function straight(x, same = false){
  var one = []
  one.push(cards.indexOf(x[0][0]))
  one.push(cards.indexOf(x[1][0]))
  one.push(cards.indexOf(x[2][0]))
  one.push(cards.indexOf(x[3][0]))
  one.push(cards.indexOf(x[4][0]))
  one.sort(function(a, b){return a-b})
  if(same){
    return one[one.length - 1]
  }
  if(one[0] === one[1] - 1 && one[1] === one[2] - 1 && one[2] === one[3] - 1 && one[3] === one[4] - 1){
    return true
  }
  var a = one.indexOf(13)
  //console.log(a)
  if(a === -1){
    return false
  }
  //console.log(one)
  one[a] = 0
  one.sort(function(a, b){return a-b})
  //console.log(one)
  if(one[0] === one[1] - 1 && one[1] === one[2] - 1 && one[2] === one[3] - 1 && one[3] === one[4] - 1){
    return true
  }
  return false
}

function sameSuit(x){
  if(x[0][1] === x[1][1] && x[0][1] === x[2][1] && x[0][1] === x[3][1] && x[0][1] === x[4][1]){
    return true
  }
  return false
}

function sameHand(player1, player2, hand){
  var one;
  var two;
  var best1 = 10;
  var best2 = 10;
  switch(hand){
    case 'Full House':
    case 'Three of a Kind':
    case 'One Pair':
    case 'Four of a Kind':
    one = cards.indexOf(ofAKind(player1, true)[0])
    two = cards.indexOf(ofAKind(player2, true)[0])
    console.log(one, two)
    if(one > two){
      return true
    }
    return false
    break;
    case 'Two Pair':
    one = cards.indexOf(ofAKind(player1, true)[0])
    two = cards.indexOf(ofAKind(player2, true)[0])
    //console.log(one, two)
    if(one > two){
      return true
    } else if(one === two){
      one = cards.indexOf(ofAKind(player1, true, 1)[0])
      two = cards.indexOf(ofAKind(player2, true, 1)[0])
      console.log(ofAKind(player1, true, 1))
      if(one > two){
        return true
      } else if(one === two){
        one = ofAKind(player1, 'bear')
        two = ofAKind(player2, 'bear')
        console.log(typeof one,typeof two)
        if(one > two){
          return true
        }
      }
    }
    return false
    break;
    case 'Straight':
    case 'Straight Flush':
    one = straight(player1, true)
    two = straight(player2, true)
    if(one > two){
      return true
    }
    return false
    break;
    case 'Flush':
    one = highCard(player1)
    two = highCard(player2)
    if(one > two){
      return true
    }
    return false
    break;
    case 'Royal Flush':
    return false;
    break;
  }
}

//console.log(hand[0][1])

function checkHand(x){
  //var success = []
  if(sameSuit(x)){ //Flush
    if(straight(x)){ //Straight Flush
      if(aceAndTen(x)){ //Royal Flush
        return 'Royal Flush'
      } else {
        return'Straight Flush'
      }
    } else {
      return 'Flush'
    }
  }
  if(straight(x)){ //Straight
    return 'Straight'
  }
  let y = x
  if(ofAKind(y)){
    return ofAKind(y)
  }
  return 'High Card'//highCard(x) //High Card
}

fs.readFile('poker.txt', {encoding: 'utf8'}, function(err, data){
  var best = 0
  if (err) throw err
  it = data.toString('ascii', 0, data.length).split('\n')//JSON.parse(data)
  for(var i = 0; i < it.length; i++){
    it[i] = it[i].split(' ')
    let player1 = []
    let player2 = []
    for(var j = 0; j < it[i].length; j++){
      if(j < 5){
        player1.push(it[i][j])
      } else {
        player2.push(it[i][j])
      }
      //console.log(player2)
      //console.log(it[i][j])
    }
    var player1HandType = checkHand(player1)
    var player2HandType = checkHand(player2)
    var player1Hand = hands.indexOf(player1HandType)
    var player2Hand = hands.indexOf(player2HandType)
    if(player1Hand > player2Hand){
      best++
    } else if(player2Hand > player1Hand){
      //console.log('Player 2 Wins1')
    } else {
      if(sameHand(test, test2, player1HandType)){
        best++
        //console.log('Player 1 Wins2')
      } else {
        //console.log(player2HandType)
        //console.log('Player 2 Wins2')
      }
      /*if(highCard(test) > highCard(test2)){
        console.log('Player 1 Wins')
      } else if(highCard(test2) > highCard(test)){
        console.log('Player 2 Wins')
      } else {
        console.log('It\'s a Tie')
      }*/
    }
  }
  module.exports = best
  //console.log(checkHand(test))
  //console.log(sameSuit(test))
  //console.log(straight(test))
  //console.log(it)
})
/*var player1HandType = checkHand(test)
var player2HandType = checkHand(test2)
var player1Hand = hands.indexOf(player1HandType)
var player2Hand = hands.indexOf(player2HandType)
if(player1Hand > player2Hand){
  console.log('Player 1 Wins1')
} else if(player2Hand > player1Hand){
  console.log('Player 2 Wins1')
} else {
  if(sameHand(test, test2, player1HandType)){
    console.log('Player 1 Wins2')
  } else {
    console.log(player2HandType)
    console.log('Player 2 Wins2')
  }
  /*if(highCard(test) > highCard(test2)){
    console.log('Player 1 Wins')
  } else if(highCard(test2) > highCard(test)){
    console.log('Player 2 Wins')
  } else {
    console.log('It\'s a Tie')
  }*/
}
//console.log(checkHand(test), checkHand(test2))
//In the event of the two players having the same hand, the player with the highest card wins