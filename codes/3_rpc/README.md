# RPC

rpcgen -a <file> 

> Arquivo de definição de interface. 

file = file.x

```x
struct operandos
{
    int x, y;
};

program PROG{
    version VERSAO {
	int ADD(operandos) = 1;
	int SUB(operandos) = 2;
    } = 10;
} = 555;
```
