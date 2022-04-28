const host = 'localhost';
const username = 'root';
//const password = 'dHybTzxrCxaQSl20';
const password = 'Saigon12345';
const database = 'iot';

const mysql = require('mysql');

var connection = mysql.createConnection({
    host: host,
    user: username,
    password: password,
    database: database
});

const check = room => {
    connection.connect(function(err){
        if(err){
            return console.error('error: ' + err.message);
        }

        let checkquery = `SELECT status FROM book WHERE Room = ${room}`;
        
        connection.query(checkquery, (error, results, fields) =>{
            if(error){
                return console.error(error.message);
            }
            if(results){
                return 'update';
            }
            else{
                return 'insert';
            }
        });
    });
}

const insert = (room, status) => {
    connection.connect(function(err){
        if(err){
            return console.error('error: ' + err.message);
        }

        let insertquery = `INSERT INTO book(Room, Status)
                            VALUES (${room}, ${status}) `;

        
        connection.query(insertquery, (error, results, fields) => {
            if(error){
                return console.error(error.message);
            }
        });
    });
}

const update = (room, status) => {
    connection.connect(function(err){
        if(err){
            return console.error('error: ' + err.message);
        }
        let updatequery = `UPDATE book
                                SET Status = ${status} 
                                WHERE Room = ${room}`;

        connection.query(updatequery, (error, results, fields) =>{
            if(error){
                return console.error(error.message);
            }
        });
    });
}

const front = () => {
    connection.connect(function(err){
        if(err){
            return console.error(err.message);
        }

        let sql = `SELECT Status FROM book`;

        connection.query(sql, (error, results, fields) => {
            if(error){
                return console.error(error.message);
            }
            return results;
        });
    });
}

module.exports = {check, insert, update, front};