const express = require("express");
const mysql = require("mysql");
const app = express();
const pool = require("./dbPool");
app.set("view engine", "ejs");
app.use(express.static("public"));
app.use(express.urlencoded({ extended: true }));

//routes
app.get('/', (req, res) => {
  res.render('index')
});

app.get("/author/new", (req, res) => {
  res.render("newAuthor");
});

app.get("/quote/new", async (req, res) => {
  let sql = `SELECT distinct firstName, lastName, authorId
              FROM q_authors`;
  let rows = await executeSQL(sql);
  let categorySQL = `SELECT DISTINCT category FROM q_quotes`;
  let categoryRows2 = await executeSQL(categorySQL);

  res.render("newQuote", { "authors": rows, "categories": categoryRows2 });
});
app.get("/dbTest", async function(req, res) {
  let sql = "SELECT CURDATE()";
  let rows = await executeSQL(sql);
  res.send(rows);
});//dbTest

app.get("/authors", async function(req, res) {
  let sql = `SELECT *
            FROM q_authors
            ORDER BY lastName`;
  let rows = await executeSQL(sql);
  res.render("authorList", { "authors": rows });
});

app.get("/quotes", async function(req, res) {
  let sql = `SELECT quoteId, quote, authorId, category, firstName, lastName
            FROM q_quotes
            NATURAL JOIN q_authors
            ORDER BY lastName
            `;
  let rows = await executeSQL(sql);
  res.render("quoteList", { "quotes": rows });
});

app.get("/quote/edit", async function(req, res) {
  let quoteId = req.query.quoteId;
  let sql = `SELECT * FROM q_quotes
              NATURAL JOIN q_authors
              WHERE quoteId = ${quoteId}`;
  let rows = await executeSQL(sql);
  let authorSQL2 = `SELECT distinct firstName, lastName, authorId 
  FROM q_authors`;
  let authorRows2 = await executeSQL(authorSQL2);

  let categorySQL3 = `SELECT distinct category FROM q_quotes`;
  let categoryRows3 = await executeSQL(categorySQL3);
  res.render("editQuote", { "quoteInfo": rows, "authors": authorRows2, "categories": categoryRows3 });
});

app.post("/quote/edit", async function(req, res) {
  let authorId = req.body.authorId;
  let sql = `UPDATE q_quotes
    SET authorId = ?, 
    quote = ?,
    category = ?
    WHERE quoteId = ?`;
  let params = [authorId, req.body.quote, req.body.category, req.body.quoteId];
  let rows = await executeSQL(sql, params);
  sql = `SELECT * 
         FROM q_quotes
         WHERE quoteId= ${req.body.quoteId}`;
  rows = await executeSQL(sql);

  let authorSQL2 = `SELECT distinct firstName, lastName, authorId 
  FROM q_authors`;
  let authorRows2 = await executeSQL(authorSQL2);

  let categorySQL3 = `SELECT distinct category FROM q_quotes`;
  let categoryRows3 = await executeSQL(categorySQL3);
  res.render("editQuote", { "quoteInfo": rows, "message": "Quote Updated!", "authors": authorRows2, "categories": categoryRows3 });
});

app.get("/author/edit", async function(req, res) {

  let authorId = req.query.authorId;

  let sql = `SELECT *, DATE_FORMAT(dob, '%Y-%m-%d') dobISO, DATE_FORMAT(dod, '%Y-%m-%d') dodISO
            FROM q_authors
            WHERE authorId =  ${authorId}`;
  let rows = await executeSQL(sql);
  res.render("editAuthor", { "authorInfo": rows });
});



app.post("/author/new", async function(req, res) {
  let fName = req.body.fName;
  let lName = req.body.lName;
  let birthDate = req.body.birthDate;
  let deathDate = req.body.deathDate;
  let birthPlace = req.body.birthPlace;
  let sex = req.body.sex;
  let profession = req.body.profession;
  let portrait = req.body.portrait;
  let bio = req.body.bio;
  let sql = "INSERT INTO q_authors (firstName, lastName, dob, dod, country, sex, profession, portrait, biography ) VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?);"
  let params = [fName, lName, birthDate, deathDate, birthPlace, sex, profession, portrait, bio];
  let rows = await executeSQL(sql, params);
  res.render("newAuthor", { "message": "Author added!" });
});

app.post("/quote/new", async function(req, res) {
  let quote = req.body.quote;
  let authorId = req.body.authorId;
  let category = req.body.category;
  let sql1 = "INSERT INTO q_quotes (quote, authorId, category) VALUES (?, ?, ?);"

  let authorSQL2 = `SELECT distinct firstName, lastName, authorId 
  FROM q_authors`;
  let authorRows2 = await executeSQL(authorSQL2);

  let categorySQL3 = `SELECT distinct category FROM q_quotes`;
  let categoryRows3 = await executeSQL(categorySQL3);
  let params = [quote, authorId, category];
  let rows1 = await executeSQL(sql1, params);
  res.render("newQuote", {
    "message": "Quote added!",
    "authors": authorRows2, "categories": categoryRows3
  });
});

app.post("/author/edit", async function(req, res) {
  let sql = `UPDATE q_authors
            SET firstName = ?,
               lastName = ?,
               dob = ?,
               dod = ?,
               country = ?,
               sex = ?,
               profession = ?,
               portrait = ?,
               biography = ?
            WHERE authorId =  ?`;

  let params = [req.body.fName,
  req.body.lName, req.body.dob,
  req.body.dod, req.body.birthPlace,
  req.body.sex, req.body.profession, req.body.portrait,
  req.body.bio, req.body.authorId];
  let rows = await executeSQL(sql, params);

  sql = `SELECT *, 
        DATE_FORMAT(dob, '%Y-%m-%d') dobISO,
        DATE_FORMAT(dod, '%Y-%m-%d') dodISO
        FROM q_authors
        WHERE authorId= ${req.body.authorId}`;
  rows = await executeSQL(sql);
  res.render("editAuthor", { "authorInfo": rows, "message": "Author Updated!" });
});

app.get("/author/delete", async function(req, res) {
  let sql = `DELETE
             FROM q_authors
             WHERE authorId= ${req.query.authorId}`;
  let rows = await executeSQL(sql);
  res.redirect("/authors");
});

app.get("/quote/delete", async function(req, res) {
  let sql = `DELETE
             FROM q_quotes
             WHERE quoteId= ${req.query.quoteId}`;
  let rows = await executeSQL(sql);
  res.redirect("/quotes");
});

//functions
async function executeSQL(sql, params) {
  return new Promise(function(resolve, reject) {
    pool.query(sql, params, function(err, rows, fields) {
      if (err) throw err;
      resolve(rows);
    });
  });
}//executeSQL

//start server
app.listen(3000, () => {
  console.log("Expresss server running...")
})

