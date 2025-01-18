FROM alpine:latest
WORKDIR /home/optimaserver
COPY ./funcClass .
RUN apk add libstdc++ && apk add libc6-compat
ENTRYPOINT [ "./funcClass" ]