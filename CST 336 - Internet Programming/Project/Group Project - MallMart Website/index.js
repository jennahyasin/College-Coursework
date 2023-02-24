// Necessary Setup Lines
const express = require("express");
const mysql = require("mysql");
const app = express();
const pool = require("./dbPool");
const session = require('express-session');
const bcrypt = require('bcrypt');

app.set("view engine", "ejs");
app.use(express.static("public"));
app.use(express.urlencoded({ extended: true }));

app.use(session({
    secret: "top secret!",
    resave: true,
    saveUnitialized: true
}));

// Default Root Route aka Main Menu
app.get('/', async function (req, res) {
    let sql = `SELECT itemId, name, price, imgName
             FROM items
             ORDER BY RAND () LIMIT 1`;

    let rows = await executeSQL(sql);

    res.render('index', {'data': rows});
});

app.get('/products', async function (req, res) {
    let category = req.query.category;
    let itemName = req.query.itemName;

    let searchQuery = "SELECT * FROM items";
    let params = [];
    let rows;

    if (typeof itemName != "undefined") { // search item
        searchQuery += ` WHERE name LIKE ?`;
      
        params = [`%${itemName}%`];
      
        rows = await executeSQL(searchQuery, params);

    } else {
        if (typeof category != "undefined" && category != "all") { // category selected
            searchQuery += " WHERE category = ?";
            params = [category];

            rows = await executeSQL(searchQuery, params);
        } else { // default page load
            rows = await executeSQL(searchQuery);
        }
    }

    sql = `SELECT DISTINCT category FROM items`;
    let cat = await executeSQL(sql);
  
    res.render('products', { 'data': rows, "categories": cat });
});

app.post('/products/category', async function (req, res) {
    let sql = "SELECT itemId, name, price, imgName FROM items";
    let rows = await executeSQL(sql);
    sql = `SELECT DISTINCT category FROM items`;
    let cat = await executeSQL(sql);

    res.render('products', { 'data': rows, 'categories': cat });
});

// Cart pages
app.get('/cart', async function (req, res) {
  
    res.render('cart');
});

app.post('/cart', async function (req, res) {
    let item = req.body.item;
    let sql = "INSERT INTO cart (name) VALUES(?);"
    params = [item];
    let rows = await executeSQL(sql, params);
    res.render('cart', { 'item': rows });
});

app.get('purchase', function(req, res) {
    // Move Users to the Cart if they try to access it directly
    res.redirect('cart');
});

// Render Purchase Complete Route
app.post('/purchase', async function(req, res) {
    // Prevent a Guest User from Checking out w/out logging in
    if (req.session.isAuthenticated) {
        let total = req.body.total;
        let userId = req.session.userId;
        let shipping = req.body.shipping;
        let tax = req.body.tax;
        let subtotal = req.body.subtotal;
    
        // DATE_FORMAT(dob, '%Y-%m-%d') dobISO
    
        let sql = `INSERT INTO purchase_history (userId, shipping, subtotal, tax, total, purchase_date) VALUES (?, ?, ?, ?, ?, NOW())`;
        // yyyy-mm-dd 
        params = [userId, shipping, subtotal, tax, total];
        let rows = await executeSQL(sql, params);

        sql = `SELECT * FROM purchase_history WHERE userId = ? ORDER BY purchase_date DESC LIMIT 1`;
        rows = await executeSQL(sql, [userId]);
    
        res.render('purchase', {"data": rows});
    } else {
        res.redirect('account');
    }
});

app.get('/login', function (req, res) {
    if (req.session.isAuthenticated) {
        res.redirect('account');
    } else {
        res.render('login');
    }
});

app.post('/login', async function (req, res) {
    let username = req.body.username;
    let password = req.body.password;
    let hashedPassword = ``;
    let msg = ``;

    let sql = `SELECT userId, password FROM user_info WHERE username = ?`;
    let rows = await executeSQL(sql, [username]);

    if (rows.length > 0) {
        hashedPassword = rows[0].password;
    }

    let passwordMatch = await bcrypt.compare(password, hashedPassword);

    if (passwordMatch) {
        req.session.isAuthenticated = true;
        req.session.username = username;
        req.session.userId = rows[0].userId;
        res.redirect('account');
    } else {
        msg = `Invalid password or username`;
        res.render('login', { "message": msg })
    }
});

app.get('/logout', function (req, res) {
    req.session.destroy();
    res.redirect('login');
});

// For loading the Create Account page
app.get('/create', function (req, res) {
    res.render('create_account');
});

// For Creating the Account Successfully
app.post('/create', async function (req, res) {
    let username = req.body.username;
    let password = req.body.password;
    let fullname = req.body.fullName;
    let bday = req.body.bday;
    let email = req.body.email;
    let phoneNumber = req.body.phoneNumber;
    let address = req.body.address;
    let image = req.body.profilePic;
    let msg = ``;

    let sql = `SELECT * FROM user_info WHERE username = ?`;
    let rows = await executeSQL(sql, [username]);

    if (rows.length > 0) { // username exists
        msg = `Error: User Already Exists`;
        res.render('create_account', { "message": msg});
    } else { // currently successful case
        if (createUser(username, password, fullname, bday, email, phoneNumber, address, image)) {
            msg = `User Created! Please Login.`;
            res.render('login', {"message": msg});
        } else {
            msg = `Error?`;
            res.render('create_account', { "message": msg});
        }
    }
});

app.get('/account', async function (req, res) {
    if (req.session.isAuthenticated) {
        let sql = `SELECT * FROM user_info WHERE username = ? LIMIT 1`;
        let username = req.session.username;
        let rows = await executeSQL(sql, [username]);

        sql = `SELECT * FROM purchase_history WHERE userId = ? ORDER BY purchase_date DESC`;
        let purchases = await executeSQL(sql, [req.session.userId]);
      
        res.render('account', { "data": rows, "purchases": purchases });
    } else {
        res.redirect('login');
    }
});

// For when editing account successfully
app.post('/account', (req, res) => {
    res.send('account');
});

app.get('/editAccount', async function (req, res) {
    let username = req.session.username;

    let sql = `SELECT * FROM user_info WHERE username = ?`;
    let params = [username];
    let rows = await executeSQL(sql, params);

    res.render('editAccount', { "data": rows });
});

app.post('/editAccount', async function (req, res) {
    let fullName = req.body.fullName;
    let email = req.body.email;
    let phoneNumber = req.body.phoneNumber;
    let address = req.body.address;
    let bday = req.body.bday;
    // Use Session to grab Username instead of from form
    let username = req.session.username;

    let sql = `UPDATE user_info
            SET fullName = ?,
            email = ?,
            phoneNumber = ?,
            address = ?,
            bday = ?
            WHERE username = ?`;
    let params = [fullName, email, phoneNumber, address, bday, username];
    let rows = await executeSQL(sql, params);

    res.redirect('account');
});

app.get('/api/item/:id', async (req, res) => {
    let itemId = req.params.id;
    let sql = `SELECT * 
             FROM items
             WHERE itemId = ? `;
    let rows = await executeSQL(sql, [itemId]);
    res.send(rows);
});

// createUser takes plaintext username & pw to make a user
async function createUser(username, plaintextPassword, fullName, bday, email, phoneNumber, address, image) {
    try {
        const hash = await bcrypt.hash(plaintextPassword, 10);

        let sql = `INSERT INTO user_info (username, password, fullName, bday, email, phoneNumber, address, imgUrl) VALUES (?, ?, ?, ?, ?, ?, ?, ?)`;
        params = [username, hash, fullName, bday, email, phoneNumber, address, image];
        await executeSQL(sql, params);

        return true;
    } catch (error) {
        console.error(error);
        return false;
    }
}

// executeSQL function to retrieve/update data
async function executeSQL(sql, params) {
    return new Promise(function (resolve, reject) {
        pool.query(sql, params, function (err, rows, fields) {
            if (err) throw err;
            resolve(rows);
        });
    });
} // executeSQL

//start server
app.listen(3000, () => {
    console.log("Express server running...")
})