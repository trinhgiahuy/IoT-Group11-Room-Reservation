const bodyparser = require('body-parser');
const express = require('express');
const path = require('path');
//const cors = require('cors');
//const { handleRequest } = require('./routes');

// Connect to mysql database
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


const app = express();
const port = process.env.port || 3000

// container
//let books = []

// View Engine Setup
app.set("views", path.join(__dirname))
app.set("view engine", "ejs")

// Body-parser middleware
app.use(bodyparser.urlencoded({extended: false}));
app.use(bodyparser.json());

app.post('/book', function(request, response){
    // code here
    // a json request

    //books.add(data);

    const { method } = request;

    // Method is not get request
    if(method.toUpperCase() !== 'GET'){
        response.statusCode(405)
    }

    else if (method.toUpperCase() === 'GET'){
        // status contains 1 and 0, represent available or unavailable
        const status = request.reversed;
        // Room number
        const room = request.room;

        // connect to database
        connection.connect(function(err){
            if(err){
                return console.error('error: ' + err.message);
            }

            let checkquery = `SELECT * FROM book WHERE Room = ${room}`;
            let insertquery = `INSERT INTO book(Room, Status)
                               VALUES (${room}, ${status}) `;
            let updatequery = `UPDATE book
                               SET Status = ${status} 
                               WHERE Room = ${room}`;
            let query = '';

            // Check if the data already exists
            connection.query(checkquery, (error, results, fields) => {
                if (error) {
                    return console.error(error.message);
                }
                if(results){
                    query = 'update';
                }
                else{
                    query = 'insert';
                }

            });

            // if check data is null, the insert new data
            if(query === 'insert'){
                connection.query(insertquery, (error, results, fields) => {
                    if(error){
                        return console.error(error.message);
                    }
                });
            }

            // else update the data
            else if(query === 'update'){
                connection.query(updatequery, (error, results, fields) => {
                    if(error){
                        return console.error(error.message);
                    }
                });
            }
            
            connection.end(function(err){
                if(err){
                    return console.log(err.message);
                }
            });
        });

        frontpage();
        response.statusCode(200);
    }
    
    
});

// fetch data from database to frontpage
const frontpage = () => {

    // html element
    const Status1 = document.getElementById('Status1');
    const Status2 = document.getElementById('Status2');

    // Fetch status from database to frontpage
    connection.connect(function(err){
        if(err){
            return console.error('error: ' + err.message);
        }

        let sql = `SELECT status FROM book`;
        connection.query(sql, (error, results, fields) => {
            if(error){
                return console.error(error.message);
            }

            const status1 = results[0].status;
            const status2 = results[1].status;

            Status1.textContent = status1;
            Status2.textContent = status2;
        });
    });
};

// The server
var server = app.listen(port, function(){
    console.log(`Hello world app listening on port ${port}!`)
})