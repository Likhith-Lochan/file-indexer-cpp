#!/bin/bash

#----------------------
#script to run indexer |
#----------------------

IMAGE_NAME="file-indexer"
CONTAINER_NAME="file-indexer-container"
HOST_DIR=$(PWD)
TARGET_DIR="/data"

INDEX_PATH="${1:- ${TARGET_DIR}}"
PATTERN="${2:-*}"
REGEX_FLAG="${3:-}"


echo "Building docker image...."
docker build -t ${IMAGE_NAME} .


echo "Running file indexer on : ${INDEX_PATH} (pattern: ${PATTERN})"
docker run --rm -v "${HOST_DIR}":"${TARGET_DIR}" "{$IMAGE_NAME}" "${INDEX_PATH}" "${PATTERN}" "${REGEX_FLAG}"
