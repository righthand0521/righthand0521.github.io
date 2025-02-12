# [Protobuf](https://github.com/protocolbuffers/protobuf)

- [Protocol Buffers implementation in C](https://github.com/protobuf-c/protobuf-c)

## Install

```bash
apt install protobuf-compiler -y

protoc --version
```

```bash
apt install protobuf-c-compiler -y
apt install libprotobuf-c-dev -y

protoc-c --version
```

## Example

- vim example.proto

```text
syntax = "proto3";

message Person {
    string name = 1;
    int32 id = 2;
    string email = 3;
}
```

- protoc --c_out=. example.proto

- vim example.c

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "example.pb-c.h"

int main() {
    // Initialize a Person message
    Person person = PERSON__INIT;
    person.name = "Alice";
    person.id = 123;
    person.email = "alice@example.com";

    // Serialize the message
    size_t serialized_size = person__get_packed_size(&person);
    void *buffer = malloc(serialized_size);
    person__pack(&person, buffer);

    printf("Serialized data size: %zu bytes\n", serialized_size);

    // Deserialize the message
    Person *unpacked_person = person__unpack(NULL, serialized_size, buffer);
    if (unpacked_person == NULL) {
        fprintf(stderr, "Error unpacking message\n");
        free(buffer);
        return 1;
    }

    printf("Deserialized Person:\n");
    printf("Name: %s\n", unpacked_person->name);
    printf("ID: %d\n", unpacked_person->id);
    printf("Email: %s\n", unpacked_person->email);

    // Clean up
    person__free_unpacked(unpacked_person, NULL);
    free(buffer);

    return 0;
}
```

- gcc example.pb-c.c example.c -o example -lprotobuf-c
