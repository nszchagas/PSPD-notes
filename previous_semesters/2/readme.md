1. Configurando a interface notebook para uso do cluster:

a) Abra uma console e crie um proxy vinculado à porta 4741 com o comando abaixo:
``` bash
$ ssh -D 4741 -p 13508 <user>@chococino.naquadah.com.br
```
b) Na estação de trabalho, chame o Mozilla Firefox, instale a extensão foxyproxy e configure a porta 4741 para o proxy do cluster.

c) na chococino:
``` bash
$ python3 -m notebook password
```
d) Escolha uma das máquinas do cluster e ative o notebook com os comandos a seguir:
``` bash
python3 -m notebook —ip cm4
```
2. Testando o broker Kafka:

a) Faça testes de criação e listagem de tópicos no Kafka
``` bash
$ kafka-topics.sh --list --bootstrap-server cm4:9092
$ kafka-topics.sh --create --topic student-a180074741-saida --bootstrap-server
cm4:9092
```
b) Rode o notebook em seu browser configurado com a proxy e rode todas as celulas

c) Crie um diálogo produtor usando o tópico criado
``` bash
$ python3 producer.py
```
