//event listeners
displayStates();
document.querySelector("#zip").addEventListener("change", displayCity);
document.querySelector("#zip").addEventListener("change", checkZipcode);
document.querySelector("#password").addEventListener("click", passwordSuggestion);
document.querySelector("#zip").addEventListener("change", displayLatitude);
document.querySelector("#zip").addEventListener("change", displayLongitude);
document.querySelector("#state").addEventListener("change", displayCounties);
document.querySelector("#username").addEventListener("change", checkUsername);
document.querySelector("#signupForm").addEventListener("submit", function(event) {
  validateForm(event);
});
//functions
//Displaying city from Web API after entering a zip code
async function displayCity() {
  //alert(document.querySelector("#zip").value);
  let zipCode = document.querySelector("#zip").value;
  let url = `https://webspace.csumb.edu/~lara4594/ajax/cityInfoByZip.php?zip=${zipCode}`;
  let response = await fetch(url);
  let data = await response.json();
  console.log(data);
  document.querySelector("#city").innerHTML = data.city;
}

//Display latitude from Web API after entering zip code
async function displayLatitude() {
  let zipCode = document.querySelector("#zip").value;
  let url = `https://webspace.csumb.edu/~lara4594/ajax/cityInfoByZip.php?zip=${zipCode}`;

  let response = await fetch(url);
  let data = await response.json();
  console.log(data);

  document.querySelector("#latitude").innerHTML = data.latitude;
}

//Displays longitude from Web API after entering zip code
async function displayLongitude() {
  let zipCode = document.querySelector("#zip").value;
  let url = `https://webspace.csumb.edu/~lara4594/ajax/cityInfoByZip.php?zip=${zipCode}`;
  let response = await fetch(url);
  let data = await response.json();
  console.log(data);
  document.querySelector("#longitude").innerHTML = data.longitude;
}

async function displayCounties() {
  let state = document.querySelector("#state").value;
  let url = `https://webspace.csumb.edu/~lara4594/ajax/countyList.php?state=${state}`;
  let response = await fetch(url);
  let data = await response.json();
  let countyList = document.querySelector("#county");
  countyList.innerHTML = "<option> Select County </option>";
  for (let i = 0; i < data.length; i++) {
    countyList.innerHTML += `<option> ${data[i].county} </option>`;
  }
}
async function checkZipcode() {
  let zipcode = document.querySelector("#zip").value;
  let url = `https://webspace.csumb.edu/~lara4594/ajax/cityInfoByZip.php?zip=${zipcode}`;
  let response = await fetch(url);
  let data = await response.json();
  if (zipcode != data.zip) {
    document.querySelector("#zipcodeError").innerHTML = "Zip code not found";
    document.querySelector("#zipcodeError").style.color = "red";
  }
  else {
    document.querySelector("#zipcodeError").innerHTML = "Zip code found"; document.querySelector("#zipcodeError").style.color = "green";
  }
}
async function checkUsername() {
  let username = document.querySelector("#username").value;
  let url = `https://cst336.herokuapp.com/projects/api/usernamesAPI.php?username=${username}`;
  let response = await fetch(url);
  let data = await response.json();
  let usernameError = document.querySelector("#usernameError");
  if (data.available) {
    usernameError.innerHTML = "Username available";
    usernameError.style.color = "green";
  } else {
    usernameError.innerHTML = "Username not available";
    usernameError.style.color = "red";
  }
}

async function passwordSuggestion() {
  let url = `https://webspace.csumb.edu/~lara4594/ajax/suggestedPwd.php?length=6`;
  let response = await fetch(url);
  let data = await response.json(); document.querySelector("#passwordSuggestion").innerHTML = "Suggested Password: " + data.password;
  document.querySelector("#passwordSuggestion").style.color = "blue";
}

async function displayStates() {
  let url = `https://cst336.herokuapp.com/projects/api/state_abbrAPI.php`;
  let response = await fetch(url);
  let data = await response.json();
  let stateList = document.querySelector("#state");
  stateList.innerHTML = "<option> Select State </option>";
  for (let i = 0; i < data.length; i++) {
    stateList.innerHTML += `<option> ${data[i].usps} </option>`;
  }


}
//Validating form data
function validateForm(e) {
  let isValid = true;
  let username = document.querySelector("#username").value;
  let password = document.querySelector("#password").value;
  let password2 = document.querySelector("#password2").value;
  if (username.length == 0) {
    document.querySelector("#usernameError").innerHTML = "Username Required!";
    document.querySelector("#usernameError").style.color = "red";
    isValid = false;
  }
  else if (password.length < 6) {
    document.querySelector("#passwordError").innerHTML = "Password must be at least 6 characters!";
    document.querySelector("#passwordError").style.color = "red";
    isValid = false;
  }

  else if (password != password2) {
    document.querySelector("#passwordError").innerHTML = "Passwords do not match!";
    document.querySelector("#passwordError").style.color = "red";
    isValid = false;
  }
  if (!isValid) {
    e.preventDefault();
  }
}