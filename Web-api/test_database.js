const host = 'localhost';
const username = 'root';
const password = 'Saigon12345';
const database = 'IOT';

const mysql = require('mysql');

var connection = mysql.createConnection({
    host: host,
    user: username,
    password: password,
    database: database
});

connection.connect(function(err){
    if(err){
        return console.error('error: ' + err.message);
    }


    // TEST create table
    /*let createBook = `create table if not exists Book(
        Room varchar(255) not null,
        Status varchar(255) not null
    )`;

    connection.query(createBook, function(err, results, fields){

        if (err){
            console.log(err.message);
        }
    });*/

    // Querying data
    /*let sql = `SELECT * FROM book`;
    connection.query(sql, (error, results, fields) => {
        if (error) {
            return console.error(error.message);
        }
        if(!results){
            console.log('Empty set');
        }
        console.log(results);
    });*/

    // TEST check, insert and update query
    let checkquery = `SELECT status FROM book `
    /*let insertquery = `INSERT INTO book(Room, Status)
                       VALUES('Room 2', 'Available') `;*/
    /*let updatequery = `UPDATE book
                       SET Status = 'Unavailable'
                       WHERE Room = 'Room 1' `;*/

    connection.query(checkquery, (error, results, fields) => {
        if (error) {
            return console.error(error.message);
        }
        console.log(results);
    });

    connection.end(function(err){
        if(err){
            return console.log(err.message);
        }
    });

    console.log('Connected to Mysql server');
});

