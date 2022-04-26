const host = 'localhost';
const username = 'root';
const password = 'Saigon12345';
const database = 'iot';

const mysql = require('mysql');

var connection = mysql.createConnection({
    host: host,
    user: username,
    password: password,
    database: database
});

(async() => {
    const Status1 = document.getElementById('Status1');
    const Status2 = document.getElementById('Status2');
    
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
    })


})();

