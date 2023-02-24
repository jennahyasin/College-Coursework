const express = require('express');
const fetch = require('node-fetch');
const faker = require('faker');
const app = express();
app.set("view engine", "ejs");
app.use(express.static("public"));
app.get('/', (req, res) => {
  res.render('index')
});

app.get('/trojan-horse', async(req, res) => {
  let url = "https://api.unsplash.com/search/photos?query=hacking&client_id=X247qxuQT9bZvsu67dNnOGYcoohddAYWy3osqgI4qMQ";
  let response = await fetch(url);
  let data = await response.json();
  //random number from 1-10 so image can be different everytime (random image)
  let randomImage = Math.floor(Math.random() * 10);
  let image = data.results[randomImage].urls.small;
  res.render('trojan-horse', {"virusUrl":image})
});

app.get('/browser-hijacker', async (req, res) => {
   let url = "https://api.unsplash.com/search/photos?query=hacking&client_id=X247qxuQT9bZvsu67dNnOGYcoohddAYWy3osqgI4qMQ";
  let response = await fetch(url);
  let data = await response.json();
  //random number from 1-10 so image can be different everytime (random image)
  let randomImage = Math.floor(Math.random() * 10);
  let image = data.results[randomImage].urls.small;
  res.render('browser-hijacker', {"virusUrl":image})
});

app.get('/macro-viruses', async (req, res) => {
   let url = "https://api.unsplash.com/search/photos?query=hacking&client_id=X247qxuQT9bZvsu67dNnOGYcoohddAYWy3osqgI4qMQ";
  let response = await fetch(url);
  let data = await response.json();
  //random number from 1-10 so image can be different everytime (random image)
  let randomImage = Math.floor(Math.random() * 10);
  let image = data.results[randomImage].urls.small;
  res.render('macro-viruses', {"virusUrl":image})
});

app.get('/sources', (req, res) =>{
  res.render('sources')
});

app.get('/help', (req, res) => {
  const info = {
    address: faker.address.streetAddress() + ", " + faker.address.cityName() + ", " + faker.address.state() + ", " + faker.address.zipCode(),
    company: faker.company.companyName(),
    phrase: faker.company.catchPhrase()
  }
  res.render('help', {
    "fakeInfo" : info
  });
});

app.listen(3000, () => {
  console.log('server started');
});


