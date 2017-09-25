FROM ubuntu:latest
MAINTAINER paul.becker@tu-dortmund.de

RUN apt-get update && \
	apt-get install -y git && \
	apt-get install -y cmake && \
	apt-get install -y libboost-all-dev && \
	apt-get install -y libsdl1.2-dev && \
	apt-get clean

RUN groupadd --gid 1000 user && \
	 useradd --uid 1000 --gid 1000 --create-home user

RUN cd /home/user
RUN git clone https://github.com/CaptainPaule/GameOfLife.git
RUN cd GameOfLife
RUN mkdir bin
RUN cd bin


USER user
WORKDIR /home/user/GameOfLife/bin
