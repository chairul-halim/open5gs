#!/bin/sh

export C_POST_PROCESS_FILE="/usr/bin/uncrustify --no-backup"
export UNCRUSTIFY_CONFIG=../.openapi-generator/uncrustify.cfg
openapi_generator_cli="java -jar ${HOME}/Documents/git/my/openapi-generator/modules/openapi-generator-cli/target/openapi-generator-cli.jar"

$openapi_generator_cli generate -i ./modified/TS29510_Nnrf_NFManagement.yaml -c ../.openapi-generator/config.yaml -g go-experimental -o ~/go-experimental