FROM alpine:3.14 as builder

RUN apk update && apk upgrade && \
    apk add build-base git

COPY . /lakota
RUN cd /lakota && \
    make

FROM alpine:3.14
COPY --from=builder /lakota/bin/lakota /lakota
RUN ls /
ENTRYPOINT ["/lakota"]
