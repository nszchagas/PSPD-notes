# Usar uma imagem base do sistema operacional, por exemplo, Ubuntu
FROM gcc:latest

# Criar o diretório de trabalho dentro do contêiner
WORKDIR /app

# Copiar o código fonte do Socket Server para o contêiner
COPY socket_server.c /app/

# Compilar o código fonte
RUN gcc -o socket_server socket_server.c

# Definir o comando de inicialização do contêiner (executar o Socket Server)
CMD ["./socket_server"]
