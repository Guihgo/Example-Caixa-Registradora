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
var SocketIo = require('socket.io')(server);


console.log('Server http e socket  rodando...');

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
    res.send({msg:'ok'});
});

var oldCompraFeita = "";
fs.watch('./compraFeita.csv', (eventType, filename) => {
  if (filename) {
    console.log(filename+ " - " + eventType);
    fs.readFile('./'+filename, function (err, data) {
      if (err) {
        return console.error(err);
      }
      if(oldCompraFeita != data.toString()) {
        //console.log("Asynchronous read: \n", data.toString());
        var itensComprados = [];
        data.toString().split("\n").forEach(function(linha, iLinha){
            var item = {
                descricao: "",
                quantidade: 0,
                valor: 0
            };
            itensComprados.push(item);
            linha.split(";").forEach(function(coluna, iColuna){
                switch(iColuna) {
                case 0:
                    itensComprados[iLinha].descricao = coluna;
                    break;
                case 1:
                    itensComprados[iLinha].quantidade = coluna;
                    break;
                case 2:
                    itensComprados[iLinha].valor = coluna;
                    break;
                default:
                    break;
                }
            });
        });
        var isNovaCompra = (itensComprados[0].descricao=="") ? true:false;
        SocketIo.sockets.emit('compraFeita', {"itensComprados": itensComprados, "isNovaCompra":isNovaCompra});
      }
      oldCompraFeita = data.toString();
    });
  }
});

SocketIo.sockets.on('connection', function(socket){ //quando houver uma nova conexão
    console.log('Um client conectou');
    
	//socket.emit('postMsg', {msg: theMsg}); //envia a msg para o socket que acabou de conectar
    //SocketIo.sockets.emit('nUsersOnline', {nUsersOnline: connections.length});
    
	//OnDisconect - quando um socket desconectar
	socket.on('disconnect', function(data) { //quando desconectar
		console.log('Um client desconectou... ', data);
	});

	 //Quando receber uma mensagem
// 	socket.on('msgEnviada', function(data) {
// 		console.log(data);
// 		SocketIo.sockets.emit('postMsg', {msg: data}); //envia para todos sockets abertos a mensagem que acabou de ser recebida
// 	});

});