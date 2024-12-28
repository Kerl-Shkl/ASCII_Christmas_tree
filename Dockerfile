FROM ubuntu

RUN mkdir Tree

COPY ./header ./Tree/header
COPY ./source ./Tree/source
COPY ./Makefile ./Tree/

RUN apt-get -y update && apt-get -y install build-essential libncurses5-dev libncursesw5-dev

WORKDIR /Tree

RUN make build

CMD ["./bin/Tree"]
