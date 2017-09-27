/*
 * Autor: Guihgo
 * Data: 20/09/2017
*/

var express = require('express');
var path = require('path');
var app = express();
var server = require('http').createServer(app); //cria servidor http utilizando express como intermediador
var bodyParser = require('body-parser');
var fs = require('fs');


server.listen(process.env.PORT || 80); //inicia servidor http na porta 80
console.log('Server http  rodando...');

app.use(bodyParser.urlencoded({ extended: false }));
app.use(bodyParser.json());// parse application/json
app.use(express.static(path.join(__dirname, 'public'))); //deixa public a pasta public - isso é para que o user possa acessar os arquivos estáticos

app.get('/', function(req, res) { //quando houver requisição nesse caminho
	res.sendFile(path.join(__dirname, 'index.html')); //envia essa página como resposta
});

app.post('/setCodigo', function(req, res) {
    console.log(req.body);
    fs.writeFile(__dirname + "/codigo.txt", req.body.codigo, function(err) {
        if(err) {
            return console.log(err);
        }
    
        console.log("O codigo "+req.body.codigo+" foi salvo");
    });
});