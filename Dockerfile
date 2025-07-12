FROM ubuntu:22.04

RUN apt-get update && \
        apt-get install -y build-essential cmake libboost-all-dev


WORKDIR /app

COPY . .

RUN mkdir -p build

RUN cd build && cmake .. && make

CMD ["./build/indexer","/app"]