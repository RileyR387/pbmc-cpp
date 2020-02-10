
FROM alpine:latest
RUN apk add g++ make boost boost-dev boost-thread boost-program_options boost-random boost-system git
RUN mkdir pbmc-cpp
COPY ./ /pbmc-cpp/
WORKDIR /pbmc-cpp
RUN make && ./bin/pbmc --help

CMD ./bin/pbmc
