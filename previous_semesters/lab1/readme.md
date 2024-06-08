# Lab 1

---

## Caio Martins - 180074741
## Yuri Alves   - 180078640

---

## Contador palavras:

``` bash
hadoop jar /home/prof/hadoop/bin/hadoop-streaming-3.3.4.jar \
-file /home/esw/a180074741/lab1/contador_palavras/mapper.py \
-mapper "python3 mapper.py" \
-file /home/esw/a180074741/lab1/contador_palavras/reducer.py \
-reducer "python3 reducer.py" \
-input /user/a180074741/lab1/contador_palavras/palavras.txt  \
-output /user/a180074741/lab1/contador_palavras/output
```

## Contador amigos:

``` bash
hadoop jar /home/prof/hadoop/bin/hadoop-streaming-3.3.4.jar \
-file /home/esw/a180074741/lab1/contador_amigos/mapper.py \
-mapper "python3 mapper.py" \
-file /home/esw/a180074741/lab1/contador_amigos/reducer.py \
-reducer "python3 reducer.py" \
-input /user/a180074741/lab1/contador_amigos/amigos.txt  \
-output /user/a180074741/lab1/contador_amigos/output
```
