## Como rodar o programa

Precisa ter o golang instalado.

Acesse o diretório 'questao-3'

```go
$ cd questao-3
```

Execute o programa passando na linha de comando dois argumentos, sendo o primeiro o ID do Estado atual e o segundo o ID do Evento:
```go 
$ go run main.go arg1 arg2
```

arg1 pode receber os valores entre 1-4
1: "Link Down",
2: "Enviando Start",
3: "Start recebido envia Configuração",
4: "Link Ok - manda keepalive",

arg2 pod receber os valores entre 1-5
1: "Interface nok",
2: "Interface ok",
3: "Pacote ok recebido",
4: "Pacote nok recebido",
5: "Não recebeu resposta",

```go 
$ go run main.go 1 2
```

Valores fora desses ranges ou de outros tipos de dados resultarão em erros amigáveis na execução do comando. Por exemplo:
```go 
$ go run main.go 1 a
event passed is not an integer value 'a'
```

```go 
$ go run main.go 1 6
failed getting next state: invalid event '6': out of range
```
