const mysql = require('mysql');

const pool  = mysql.createPool({
    connectionLimit: 10,
    host: "z3iruaadbwo0iyfp.cbetxkdyhwsb.us-east-1.rds.amazonaws.com",
    user: "b338jnvq8b4k2khc",
    password: "itqrxvhqjj5ha20t",
    database: "c455dc5dm7n7toc5"
});

module.exports = pool;
