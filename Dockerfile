FROM alpine:latest
WORKDIR /home/optimaserver
COPY ./main .
RUN apk add libstdc++ && apk add libc6-compat
ENTRYPOINT [ "./main" ]