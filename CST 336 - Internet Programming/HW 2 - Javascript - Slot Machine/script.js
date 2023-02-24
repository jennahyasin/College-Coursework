//Event listeners for buttons:
document.querySelector("#spin-button").addEventListener("click", spinLever);
document.querySelector("#how-to-play").addEventListener("click", howToPlay);

//creates an array for the three symbols
let symbols = ["$", "7", "BAR"];

//shuffles the three symbols
function randomSymbol() {
  return Math.floor(Math.random() * symbols.length);
}
//selects one of the symbols
function chosenSymbol() {
  return symbols[randomSymbol()];
}

function index(id) {
  return document.querySelector(id);
}

//when how to play button is clicked, pop up message appears
function howToPlay() {
  alert("Game Rules/Instructions\n 1. In order to play, you must initially choose a bidding value, otherwise you will not win anything.\n 2. In order to win some money, you have to have three matching slot values.\n 3. The awarding money varies based on the ranking of each symbol.\n 4. \t7 - $100\n\t $ - $60 \n\t BAR - $10 \n 5. Finally, the money you bid is multiplied by each of the symbol values\n Good Luck!");
}
//spinning the slot machine
function spinLever() {
  document.body.style.backgroundImage = "url('img/coins-img.jpg')";

  let bidDrop = document.querySelector("#bid-dropdown").value;
  //sets up the starting slot positions
  let symbol1 = index("#symbol1");
  let symbol2 = index("#symbol2");
  let symbol3 = index("#symbol3");
  //puts a random symbol in every position of slot
  let leftSide = chosenSymbol();
  let middle = chosenSymbol();
  let rightSide = chosenSymbol();

  symbol1.innerHTML = `${leftSide}`;
  symbol2.innerHTML = `${middle}`;
  symbol3.innerHTML = `${rightSide}`;

  //For when user selects $1 as bid
  if (bidDrop == "1") {
    //multiplying the wins by bid amount when there is a win
    if (leftSide === "$" && middle === "$" && rightSide === "$") {
      document.querySelector("#win-or-lose").innerHTML = `YOU WIN $60`;
      document.querySelector("#win-or-lose").style.color = 'green';
    }
    else if (leftSide === "7" && middle === "7" && rightSide === "7") {
      document.querySelector("#win-or-lose").innerHTML = `JACKPOT YOU WIN $100`;
      document.querySelector("#win-or-lose").style.color = 'green';
    }
    else if (leftSide === "BAR" && middle === "BAR" && rightSide === "BAR") {
      document.querySelector("#win-or-lose").innerHTML = `YOU WIN $10`;
      document.querySelector("#win-or-lose").style.color = 'green';
    }
    else {
      //no win
      document.querySelector("#win-or-lose").innerHTML = `NOTHING, TRY AGAIN!`;
      document.querySelector("#win-or-lose").style.color = 'red';
    }
  }
  //For when user selects $20 as bid
  else if (bidDrop == "20") {
    //multiplying the wins by bid amount when there is a win
    if (leftSide === "$" && middle === "$" && rightSide === "$") {
      document.querySelector("#win-or-lose").innerHTML = `YOU WIN $1,200`;
      document.querySelector("#win-or-lose").style.color = 'green';
    }
    else if (leftSide === "7" && middle === "7" && rightSide === "7") {
      document.querySelector("#win-or-lose").innerHTML = `JACKPOT YOU WIN $2,000`;
      document.querySelector("#win-or-lose").style.color = 'green';
    }
    else if (leftSide === "BAR" && middle === "BAR" && rightSide === "BAR") {
      document.querySelector("#win-or-lose").innerHTML = `YOU WIN $200`;
      document.querySelector("#win-or-lose").style.color = 'green';
    }
    //no win
    else {
      document.querySelector("#win-or-lose").innerHTML = `NOTHING, TRY AGAIN!`;
      document.querySelector("#win-or-lose").style.color = 'red';
    }
  }
  //For when user selects $60 as bid
  else if (bidDrop == "60") {
    //multiplying the wins by bid amount when there is a win
    if (leftSide === "$" && middle === "$" && rightSide === "$") {
      document.querySelector("#win-or-lose").innerHTML = `YOU WIN $3,600`;
      document.querySelector("#win-or-lose").style.color = 'green';
    }
    else if (leftSide === "7" && middle === "7" && rightSide === "7") {
      document.querySelector("#win-or-lose").innerHTML = `YOU WIN $6,000`;
      document.querySelector("#win-or-lose").style.color = 'green';
    }
    else if (leftSide === "BAR" && middle === "BAR" && rightSide === "BAR") {
      document.querySelector("#win-or-lose").innerHTML = `YOU WIN $600`;
      document.querySelector("#win-or-lose").style.color = 'green';
    }
    else {
      //no win
      document.querySelector("#win-or-lose").innerHTML = `NOTHING, TRY AGAIN!`;
      document.querySelector("#win-or-lose").style.color = 'red';
    }
  }
  //For when user selects $60 as bid
  else if (bidDrop == "100") {
    //multiplying the wins by bid amount when there is a win
    if (leftSide === "$" && middle === "$" && rightSide === "$") {
      document.querySelector("#win-or-lose").innerHTML = `YOU WIN $6,000`;
      document.querySelector("#win-or-lose").style.color = 'green';
    }
    else if (leftSide === "7" && middle === "7" && rightSide === "7") {
      document.querySelector("#win-or-lose").innerHTML = `HIGHEST JACKPOT YOU WIN $10,000`;
      document.querySelector("#win-or-lose").style.color = 'green';
    }
    else if (leftSide === "BAR" && middle === "BAR" && rightSide === "BAR") {
      document.querySelector("#win-or-lose").innerHTML = `YOU WIN $1,000`;
      document.querySelector("#win-or-lose").style.color = 'green';
    }
    else {
      //no win
      document.querySelector("#win-or-lose").innerHTML = `NOTHING, TRY AGAIN!`;
      document.querySelector("#win-or-lose").style.color = 'red';
    }
  }

}
