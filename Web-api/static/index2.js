const bodyparser = require('body-parser');
const express = require('express');
const path = require('path');
const fs = require('fs');
const cors = require('cors');
//const { handleRequest } = require('./routes');
const {check, insert, update, front} = require('./database');

const app = express();
const port = process.env.port || 3000

// View Engine Setup
app.set("views", path.join(__dirname))
app.set("view engine", "ejs")

// Body-parser middleware
app.use(bodyparser.urlencoded({extended: false}));
app.use(bodyparser.json());
app.use(cors());
app.use("/static", express.static('./static/'));

app.get('/', function(request, response){
    // code here

    if(request.reversed !== undefined || request.room !== undefined){
        // status contains 1 and 0, represent available or unavailable
        const status = 'Available';
        if(request.reversed === 0){
            status = 'Unavailable';
        }

        // Room number
        const room = request.room;

        const checkdb = check(room);
        if(checkdb === 'insert'){
            insert(room, status);
        }
        else if(checkdb === 'update'){
            update(room, status);
        }
        
    }

    fs.readFile(path.resolve('../index.html'), function(error, htmlPage) {
        if (error) {
          response.writeHead(404);
          response.write('An error occured: ', error);
        } 
        else {
          response.writeHead(200, { 'Content-Type': 'text/html' });
          response.write(htmlPage);
        }
        response.end();
    });
    
});

app.get('/static/styles.css', function(request, response){
    fs.readFile(path.resolve('styles.css'), function(error, htmlPage) {
        if (error) {
          response.writeHead(404);
          response.write('An error occured: ', error);
          response.end();
        } 
        else {
          response.writeHead(200, { 'Content-Type': 'text/css' });
          response.end(htmlPage, 'utf-8');
        }
    });
});

app.get('/static/frontpage.js', function(request, response){
    fs.readFile(path.resolve('frontpage.js'), function(error, htmlPage) {
        if (error) {
          response.writeHead(404);
          response.write('An error occured: ', error);
          response.end();
        } 
        else {
          response.writeHead(200, { 'Content-Type': 'text/javascript' });
          response.end(htmlPage, 'utf-8');
        } 
    });
});

// fetch data from database to frontpage
const frontpage = () => {

    if(typeof document === 'undefined'){
        console.log('no way');
        return;
    }
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
app.listen(port, function(){
    
    console.log(`Hello world app listening on port ${port}!`);
})