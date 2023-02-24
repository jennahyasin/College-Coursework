//event listener
document.querySelector("#city").addEventListener("change", convertCity);
//this function first takes city name and fetches their longitude and latitude values because the weather data API requires those parameters. 
async function convertCity() {
  let city = document.querySelector("#city").value;
  //gets longitude and latitude values for entered city
  let url = `https://api.openweathermap.org/geo/1.0/direct?q=${city}&appid=87424aa60728c1b8212d4d3bf2f692c2`;
  let response = await fetch(url);
  let data = await response.json();
  console.log(data);

  let lat = document.querySelector("#latitude").value = data[0].lat;
  let lon = document.querySelector("#longitude").value = data[0].lon;
  //Validates user input (if city entered is not part of database display nothing but error message)
  if (city != data[0].name) {
    document.querySelector("#cityName").innerHTML = " ";
    document.querySelector("#showCurrentTemp").innerHTML = " ";
    document.querySelector("#weather-description").innerHTML = " ";

    document.querySelector("#weather-image").innerHTML = " ";      document.querySelector("#cityNameError").innerHTML = "City not found";
    document.querySelector("#cityNameError").style.color = "red";
  }
  else {
    document.querySelector("#cityNameError").innerHTML = "";

    //uses generated long and latitude values to fetch weather data.
    let url2 = `https://api.openweathermap.org/data/2.5/weather?lat=${lat}&lon=${lon}&appid=87424aa60728c1b8212d4d3bf2f692c2`;
    let response2 = await fetch(url2);
    let data2 = await response2.json();

    //equaton that converts the current temp from Kelvin to Farenheit
    let f_current_temp = 1.8 * (data2.main.temp - 273) + 32;

    //display output information
    document.querySelector("#cityName").innerHTML = city;
    document.querySelector("#showCurrentTemp").innerHTML = f_current_temp.toFixed(0) + "°F";
    document.querySelector("#weather-description").innerHTML = data2.weather[0].description;

    //Based on temperature, a corresponding weather condition image is displayed
    if (f_current_temp >= 80) {
      document.querySelector("#weather-image").innerHTML = "<img src= 'img/sunny-img.png' alt='sunny'>";
    }
    else if (f_current_temp <= 79 && f_current_temp >= 50) {
      document.querySelector("#weather-image").innerHTML = "<img src= 'img/sunny-cloudy_img.png' alt='sunny cloudy'>";
    }
    else if (f_current_temp <= 51 && f_current_temp >= 10) {
      //put cold image
      document.querySelector("#weather-image").innerHTML = "<img src= 'img/cold.png' alt='cold and cloudy'>";
    }
    else if (f_current_temp <= 9) {
      document.querySelector("#weather-image").innerHTML = "<img src= 'img/freezing.png' alt='snow'>";
    }
  }
}