# Kafka 설치. 실행. CLI

## config/server.properties

- broker.id : 정수로 된 브로커 번호. 클러스터 내 고유 번호로 지정
- listens : kafka 통신에 사용되는 host:port
- advertised.listeners : kafka client가 접속할 host:port
- log.dirs : 메시지를 저장할 디스크 디렉토리. 세그먼트가 저장됨.
- log.segment.bytes : 메시지가 저장되는 파일의 크기 단위
- log.retention.ms : 메시지를 얼마나 보존할지 지정. 닫힌 세그먼트를 처리
- zookeeper.connect : 브로커의 메타데이터를 저장하는 주키퍼의 위치
- auto.create.topics.enable : 자동으로 토픽이 생성 여부
- num.partitions : 자동생성된 토픽의 default_partition 개수
- message.max.bytes : kafka broker에 쓰련느 메시지 최대 크기

## Local 설치 및 CLI 실행

### 1. kafka 파일 다운로드 후 압축 해제

```shell
curl https://archive.apache.org/dist/kafka/2.5.0/kafka_2.13-2.5.0.tgz --output kafka.tgz

tar -xvf kafka.tgz
```

### 2. CLI 실행

```shell
./kafka-topics.sh --create --bootstrap-server {aws ec2 public ip}:9092 --replication-factor 1 --partitions 3 --topic test
./kafka-console-producer.sh --bootstrap-server {aws ec2 public ip}:9092 --topic test
./kafka-console-consumer.sh --bootstrap-server {aws ec2 public ip}:9092 --topic test --from-beginning
./kafka-console-consumer.sh --bootstrap-server {aws ec2 public ip}:9092 --topic test -group testgroup --from-beginning
./kafka-consumer-groups.sh --bootstrap-server {aws ec2 public ip}:9092 --list
./kafka-consumer-groups.sh --bootstrap-server {aws ec2 public ip}:9092 --group testgroup --describe
./kafka-consumer-groups.sh --bootstrap-server {aws ec2 public ip}:9092 --group testgroup --topic test --reset-offsets --to-earliest --execute
./kafka-consumer-groups.sh --bootstrap-server {aws ec2 public ip}:9092 --group testgroup --topic test:1 --reset-offsets --to-offset 10 --execute
```

