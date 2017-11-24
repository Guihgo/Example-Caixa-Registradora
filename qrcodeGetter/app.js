/*
 * Autor: Guihgo
*/

var express = require('express');
var path = require('path');
var app = express();
var fs = require('fs');
var bodyParser = require('body-parser');

const httpsOptions = {
  key: fs.readFileSync('./key.pem'),
  cert: fs.readFileSync('./cert.pem')
}
var server = require('https').createServer(httpsOptions, app); //cria servidor http utilizando express como intermediador
server.listen(80); //inicia servidor http na porta 80
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
        var isNovaCompra = false;
        data.toString().split("\n").forEach(function(linha, iLinha){
            var item = {
                codigo: 0,
                descricao: "",
                quantidade: 0,
                valor: 0
            };
      
            linha.split(";").forEach(function(coluna, iColuna){
                switch(iColuna) {
                case 0:
                  item.codigo = coluna;
                  break;
                case 1:
                    item.descricao = coluna;
                    break;
                case 2:
                    item.quantidade = coluna;
                    break;
                case 3:
                    item.valor = coluna;
                    break;
                default:
                    break;
                }
            });
            console.log(item.descricao.length);
            if(item.descricao=="" || item.descricao=="\n" ||item.descricao=="\l" || item.descricao.length<=1){
              isNovaCompra=true;
            }
            if(item.descricao.length!=0) {
              SocketIo.sockets.emit('compraFeita', {"itemComprado": item, "isNovaCompra":isNovaCompra});
            }    
        });
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
