//Event Listeners
document.querySelector("button").addEventListener("click", gradeQuiz);

//functions
displayQ4Choices();
function displayQ4Choices() {
  let q4ChoicesArray = ["Maine", "Rhode Island", "Maryland", "Delware"];
  q4ChoicesArray = _.shuffle(q4ChoicesArray);

  for (let i = 0; i < q4ChoicesArray.length; i++) {
    document.querySelector("#q4Choices").innerHTML += ` <input type="radio" name="q4" id= "${q4ChoicesArray[i]}" value="${q4ChoicesArray[i]}"> <label for="${q4ChoicesArray[i]}"> ${q4ChoicesArray[i]}</label>`;
  }
}//displayQ4Choices

displayQ7Choices();
function displayQ7Choices() {
  let q7ChoicesArray = ["True", "False"];
  q7ChoicesArray = _.shuffle(q7ChoicesArray);

  for (let i = 0; i < q7ChoicesArray.length; i++) {
    document.querySelector("#q7Choices").innerHTML += ` <input type="radio" name="q7" id= "${q7ChoicesArray[i]}" value="${q7ChoicesArray[i]}"> <label for="${q7ChoicesArray[i]}"> ${q7ChoicesArray[i]}</label>`;
  }
}//displayQ7Choices
//Global Variables 
var score = 0;
var attempts = localStorage.getItem("total_attempts");

function isFormValid() {
  let isValid = true;
  if (document.querySelector("#q1").value == "") {
    isValid = false;
    document.querySelector("#validationFdbk").innerHTML = "Question 1 was not answered";
  }
  return isValid;
} //isFormValid()

function rightAnswer(index) {
  document.querySelector(`#q${index}Feedback`).innerHTML = "Correct!";
  document.querySelector(`#q${index}Feedback`).className = "bg-success text-white";
  document.querySelector(`#markImg${index}`).innerHTML = "<img src='img/checkmark.png' alt='checkmark'>";
  score += 10;
}

function wrongAnswer(index) {
  document.querySelector(`#q${index}Feedback`).innerHTML = "Incorrect!";
  document.querySelector(`#q${index}Feedback`).className = "bg-warning text-white";
  document.querySelector(`#markImg${index}`).innerHTML = "<img src='img/xmark.png' alt='xmark'>";
}
function gradeQuiz() {
  console.log("Grading quiz...");
  document.querySelector("#validationFdbk").innerHTML = " "; //resets validation feedback 
  if (!isFormValid()) {
    return;
  }

  //variables
  score = 0;
  let q1Response = document.querySelector("#q1").value.toLowerCase();
  let q2Response = document.querySelector("#q2").value;
  let q4Response = document.querySelector("input[name=q4]:checked").value;
  console.log(q2Response);
  console.log(q1Response);
  let q5Response = document.querySelector("#q5").value;
  let q7Response = document.querySelector("input[name=q7]:checked").value;
  let q8Response = document.querySelector("#q8").value;
  let q9Response = document.querySelector("#q9").value.toLowerCase();
  let q10Response = document.querySelector("#q10").value.toLowerCase();
  //Grading Question 1
  if (q1Response == "sacramento") {
    rightAnswer(1);
  }
  else {
    wrongAnswer(1);
  }

  //Grading Question 2: 
  if (q2Response == "mo") {
    rightAnswer(2);
  }
  else {
    wrongAnswer(2);
  }

  //Grading Question 3:
  if (document.querySelector("#Jefferson").checked && document.querySelector("#Roosevelt").checked && !document.querySelector("#Jackson").checked && !document.querySelector("#Franklin").checked) {
    rightAnswer(3);
  }
  else {
    wrongAnswer(3);
  }

  //Grading Question 4:
  if (q4Response == "Rhode Island") {
    rightAnswer(4);
  }
  else {
    wrongAnswer(4);
  }

  //Grading Question 5
  if (q5Response == "1959") {
    rightAnswer(5);
  }
  else {
    wrongAnswer(5);
  }

  //Grading Question 6
  if (document.querySelector("#Atlantic").checked && document.querySelector("#Pacific").checked && document.querySelector("#Arctic").checked && !document.querySelector("#Indian").checked) {
    rightAnswer(6);
  }
  else {
    wrongAnswer(6);
  }

  //Grading Question 7:
  if (q7Response == "True") {
    rightAnswer(7);
  }
  else {
    wrongAnswer(7);
  }

  //Grading Question 8:
  if (q8Response == "nj") {
    rightAnswer(8);
  }
  else {
    wrongAnswer(8);
  }

  //Grading Question 9:
  if (q9Response == "maine") {
    rightAnswer(9);
  }
  else {
    wrongAnswer(9);
  }

  //Grading Question 10:
  if (q10Response == "alaska") {
    rightAnswer(10);
  }
  else {
    wrongAnswer(10);
  }

  if (score < 80) {
    document.querySelector("#totalScore").style.color = 'red';
    document.querySelector("#totalScore").innerHTML = `Total  Score: ${score}`;
    document.querySelector("#congratsMessage").innerHTML = `Less than 80%`;
  }
  else if (score >= 80) {
    document.querySelector("#totalScore").style.color = 'green';
    document.querySelector("#totalScore").innerHTML = `Total  Score: ${score}`;
    document.querySelector("#congratsMessage").innerHTML = `CONGRATULATIONS!`;
  }

  // document.querySelector("#totalScore").innerHTML = `Total  Score: ${score}`;
  document.querySelector("#totalAttempts").innerHTML = `Total Attempts: ${++attempts}`;
  localStorage.setItem("total_attempts", attempts);
}//gradeQuiz