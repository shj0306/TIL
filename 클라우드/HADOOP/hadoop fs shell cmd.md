## hadoop fs 명령어 정리

- appendToFile : 로컬 시스템의 파일을 기존에 존재하는 hdfs 파일 시스템의 파일에 붙인다.

  ```shell
  hadoop fs -appendToFile [로컬 시스템 파일] [hdfs 파일시스템 디레토리] /[파일명]
  ```


- cat: [파일명]의 내용을 출력한다.

  ```shell
  hadoop fs -cat /data/[파일명]
  ```

- chmod : 파일의 모드를 변경한다. '-R' 옵션을 사용하면 하위 디렉토리에도 같이 반영된다.

  ```shell
  hadoop fs -chmod [MODE CHANGE RULE] [hdfs 파일시스템 디렉토리 혹은 파일명]
  ```

- chown : 파일의 소유권을 변경한다. '-R' 옵션을 사용하면 하위 디렉토리에도 같이 반영된다.

  ```shell
  hadoop fs -chown [이전할 소유자] [hdfs 파일시스템 디렉토리 혹은 파일명]
  ```

- copyFromLocal: 로컬 파일시스템에서 hdfs 파일 시스템으로 파일 복사

  ```shell
  hadoop fs -copyFromLocal [로컬파일시스템 디렉토리]/[파일명] [hdfs 파일시스템 디렉토리]/
  ```

- copyToLocal: hdfs 파일시스템에서 로컬 파일 시스템으로 파일 복사(-copyToLocal)

  ```shell
  hadoop fs -copyToLocal [HDFS 파일시스템 디렉토리]/[파일명] [로컬파일시스템 디렉토리]/
  ```
  
- cp : HDFS 파일시스템 내에서 파일 복사한다. -f 옵션은 목적지 디렉토리에 같은 파일이 있을 경우 덮어 쓴다.

  ```shell
  hadoop fs -cp [hdfs 파일시스템 파일] [hdfs 파일시스템 디렉토리]
  ```

- get: hdfs 파일시스템의 파일을 로컬 파일시스템으로 복사한다.

  ```shell
  hadoop fs -get [hdfs 파일시스템의 파일] [로컬 시스템의 파일]
  ```

- ls -R : hdfs 파일 시스템의 '/data' 디렉토리의 파일 리스트를 조회한다. 2번째처럼 '-R' 옵션을 추가하면 하위 디렉토리를 포함한 전체 파일 리스트를 확인할 수 있다.

  ```shell
  hadoop fs -ls /data
  hadoop fs -ls -R /data
  ```

- mkdir : root 디렉토리 하위에 'data' 디렉토리를 생성한다.

  ```shell
  hadoop fs -mkdir /data
  ```

- moveFromLocal : put 명령어와 유사하며 로컬 시스템의 파일이 hdfs파일 시스템으로 복사가 된후 로컬 시스템의 파일은 삭제 된다.

  ```shell
  - hadoop fs -moveFromLocal [로컬파일시스템의 파일] [hdfs 파일시스템의 디렉토리]
  - 
  ```

- mv: hdfs 파일 시스템 내에서 디렉토리 혹은 파일들을 이동한다.

  ```shell
  hadoop fs -mv [hdfs 파일시스템의 디렉토리 혹은 파일] [hdfs 파일시스템의 디렉토리]
  ```

- put: 로컬 파일시스템의 파일을 hdfs 파일시스템으로 복사한다.

  ```shell
  hadoop fs -put [로컬시스템의 파일] [hdfs 파일시스템의 디렉토리]
  ```

- rm : [파일명]을 삭제한다.

  ```shell
  hadoop fs -rm /data/[파일명]
  ```

- rm -r : 디렉토리 삭제 명령어 -r 옵션은 삭제하려는 디렉토리에 파일이 있더라도 삭제된다.

  ```shell
  hadoop fs -rm -r /data/[파일명]
  ```

- touchz : 파일의 크기가 0인 파일을 생성한다.

  ```shell
  hadoop fs -touchz [생성할 hdfs 파일시스템 파일명]
  ```
