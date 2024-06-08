# caio martins 180074741
# yuri alves 180078640

from kafka import KafkaProducer
from time import sleep

#Create an instance of the Kafka producer
arquivo = open('words.txt', 'r').read()
producer = KafkaProducer(bootstrap_servers='localhost:9092', api_version=(0, 10, 1),value_serializer=lambda v: str(v).encode('utf-8'))

# Call the producer.send method with a producer-record
print("Ctrl+c to Stop")
while True:
    producer.send('student-a180074741-saida', arquivo)
    sleep(5)
