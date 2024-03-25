// q7_server.c

#include <stdio.h>
#include <stdlib.h>
#include <grpc-c/grpc-c.h>

void find_max_and_min(Vector *vector, Result *result, void *userdata) {
  int32_t max_value = vector->values[0];
  int32_t min_value = vector->values[0];

  for (size_t i = 1; i < vector->n_values; i++) {
    if (vector->values[i] > max_value) {
      max_value = vector->values[i];
    }
    if (vector->values[i] < min_value) {
      min_value = vector->values[i];
    }
  }

  result->max_value = max_value;
  result->min_value = min_value;
}

int main() {
  grpc_c_init(GRPC_THREADS_ONE);

  grpc_c_server_t *server = grpc_c_server_create(NULL, NULL);

  Aux *aux = Aux_create(); 
  grpc_c_service_register(aux, server);

  grpc_c_method_register(aux, RPC_AUX_FIND_MAX_AND_MIN,
                         find_max_and_min, NULL);

  grpc_c_server_start(server);

  printf("Servidor iniciado (espero)...\n");
  grpc_c_server_wait(server);
  printf("Desligando o servidor (já estou mais aliviado se chegou aqui)...\n");

  grpc_c_server_shutdown(server, 0, NULL);
  grpc_c_shutdown();

  return 0;
}

// q7_client.c


#include <stdio.h>
#include <stdlib.h>
#include <grpc-c/grpc-c.h>
#include "vector.pb-c.h"

void print_result(Result *result, void *userdata) {
  printf("Maior valor: %d\n", result->max_value);
  printf("Menor valor: %d\n", result->min_value);
}

int main() {
  grpc_c_init(GRPC_THREADS_ONE);

  grpc_c_client_t *client = grpc_c_client_init("localhost:50051", NULL, NULL);

  Aux *aux = Aux_teste(client);

  Vector vector = VECTOR__INIT;
  vector.n_values = 100;
  vector.values = malloc(sizeof(int32_t) * vector.n_values);
  for (size_t i = 0; i < vector.n_values; i++) {
    vector.values[i] = rand();
  }

  grpc_c_client_request(
      aux, AUX_FIND_MAX_AND_MIN, &vector,
      (grpc_c_closure_t)print_result, NULL);

  grpc_c_client_wait_completion(client);

  free(vector.values);
  grpc_c_client_shutdown(client, 0, NULL);
  grpc_c_shutdown();

  return 0;
}


