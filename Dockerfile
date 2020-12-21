FROM alpine:3.12 as builder

RUN apk update && apk upgrade && \
    apk add build-base git

COPY . /lakota
RUN cd /lakota && \
    make

FROM scratch
COPY --from=builder /lakota/bin/lakota /lakota

ENTRYPOINT ["/lakota"]
