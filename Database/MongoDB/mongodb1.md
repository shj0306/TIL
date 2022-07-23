# MongoDB 

## Database / Collection / Document 생성, 제거

### 데이터베이스 생성 : use

```shell
$ use [데이터베이스 이름]
```

- 데이터 베이스를 생성할 수 있다.

- 현재 사용중인 데이터베이스를 확인

  ```shell
  $ show db
  ```

- 내가 만든 데이터베이스 리스트들을 확인

  ```shell
  $ show dbs
  ```

  - 데이터베이스가 표시되기 위해선 최소 한개 이상의 document를 추가해야 한다.



### 데이터베이스 제거 : db.dropDatabase()

- 데이터베이스를 제거할 땐 db.dropDatabase() 명령어를 사용하는 데, 이 때 use (삭제할 데이터베이스 이름)을 통해서 삭제하고자 하는 데이터베이스를 선택해야 한다.

- ```shell
  $ use [삭제할 데이터베이스]
  $ db.dropDatabase()
  { "dropped" : "삭제된 데이터베이스 이름", "ok" : 1 }
  ```



### Collection 생성 : db.createCollection()

- 컬렉션을 생성할 때는 db.createCollection(name, [options]) 명령어를 사용한다.

- name은 생성할 컬렉션의 이름이고, option은 document 타입으로 구성된 해당 컬렉션의 설정값이다.

  | Field       | Type    | 설명                                                         |
  | ----------- | ------- | ------------------------------------------------------------ |
  | capped      | Boolean | capped collection을 활성화 시키는 값으로,  고정된 크기를 가진 컬렉션으로서, size가 초과되면 가장 오래된 데이터를 덮어씁니다. 이 값을 true로 설정하면 반드시 size를 설정해야 합니다. |
  | autoIndexId | Boolean | true면 id값을 자동으로 생성합니다. 기본값은 false            |
  | size        | number  | capped collection을 위해 해당 컬렉션의 최대 size를 byte로 지정합니다. |
  | max         | number  | 해당 컬렉션에 추가할 수 있는 최대 갯수를 설정합니다.         |



### Collection 리스트 확인

```shell
$ show collections
```



### Collection 제거 : db.collection_name.drop()

- 컬렉션을 제거할 땐 drop() 메소드를 사용한다.

  ```shell
  $ use test
  $ show collections
  $ db.삭제할컬렉션명.drop()
  ```



### Document 추가 : db.collection_name.insert(document)

- insert 메소드를 사용해 document를 추가할 수 있다.

- 배열 형식의 인자를 전달해주면 여러 document들을 동시에 추가할 수 있다.

  - 한개의 document를 컬렉션에 추가

  ```shell
  $ db.컬렉션명.insert({key1:value1, key2:value2});
  ```

  - 두개 document를 컬렉션에 추가

  ```shell
  $ db.컬렉션명.insert({key1:value1, key2:value2},
  					{key1:value3, key2:value4});
  ```



### Collection의 Document 리스트 확인 : db.collection_name.find()

```shell
$ db.컬렉션명.find()
```



### Document 제거 (deleteOne, deleteMany, findOneAndDelete)

#### deleteOne

- 컬렉션에 있는 filter와 매칭되는 한 개의 document를 삭제한다.

  | parameter    | Type     | Description                                                  |
  | ------------ | -------- | ------------------------------------------------------------ |
  | filter       | document | 삭제할 기준(criteria), filter가 {}라면 컬렉션의 첫번째 document가 삭제됩니다. |
  | writeConcern | document |                                                              |
  | collation    | document |                                                              |

#### deleteMany

- 컬렉션에서 filter와 매칭되는 모든 document를 삭제한다.

#### findOneAndDelete

- 컬렉션에서 filter와 sort를 기준으로 한 개의 document를 삭제한다.

  | parameter | Type     | Description                        |
  | --------- | -------- | ---------------------------------- |
  | filter    | document | 삭제할 기준                        |
  | sort      | document | filter에 매치된 document 정렬 기준 |
  | maxTimeMS | number   | 연산이 수행되어야 할 제한 시간     |



