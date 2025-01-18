FROM alpine:latest AS build
RUN apk add --no-cache build-base automake autoconf
WORKDIR /home/optimaserver
COPY . .
RUN ./configure
RUN make

FROM alpine:latest
WORKDIR /home/optimaserver
COPY --from=build /home/optimaserver/main /usr/local/bin/main
ENTRYPOINT ["/usr/local/bin/main"]