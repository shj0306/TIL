# find() 메소드 활용 - sort(), limit(), skip()

- find() 메소드를 사용하면 조건에 충족하는 모든 document들을 출력하기 때문에 페이지 같은 기능을 사용한다면 부적합합니다. 하지만 find() 메소드 자체에 어디부터 어디까지 불러오도록 설정하는 매개변수는 따로 없습니다.
- find() 메소드는 반환 값이 cursor 객체인데, 이 객체가 가지고 있는 limit, skip 메소드를 통해서 보이는 출력물의 갯수를 제한 할 수 있고, sort메소드를 사용하여 데이터를 정렬할 수 있습니다.

**샘플 데이터 추가**

```
[
    { "_id": 1, "item": { "category": "cake", "type": "chiffon" }, "amount": 10 },
    { "_id": 2, "item": { "category": "cookies", "type": "chocolate chip" }, "amount": 50 },
    { "_id": 3, "item": { "category": "cookies", "type": "chocolate chip" }, "amount": 15 },
    { "_id": 4, "item": { "category": "cake", "type": "lemon" }, "amount": 30 },
    { "_id": 5, "item": { "category": "cake", "type": "carrot" }, "amount": 20 },
    { "_id": 6, "item": { "category": "brownies", "type": "blondie" }, "amount": 10 }
]
```

### cursor.sort(document)

- 데이터를 정렬할 때 사용됩니다 매개변수로는 어떤 키를 사용해 정렬할 지 알려주는 document를 전달합니다.

- document의 구조는 {key : value}이고, key는 데이터 필드 이름이고, value값은 1 혹은 -1입니다. 1로 설정하면 오름차순이고 -1은 내림차순 정렬입니다.

- _id 값을 사용하여 오름차순 정렬

  > db.orders.find().sort({"_id":1})

- amount 값을 사용하여 오름차순으로 정렬하고, 정렬한 값에서 id 값은 내림차순으로 정렬

  > db.orders.find().sort({"amount":1, "_id":-1})

### cursor.limit(value)

- 출력할 때 데이터 갯수를 제한합니다. value는 출력할 갯수입니다.

- 출력할 갯수를 3개로 제한하기

  > db.orders.find().limit(3)

### cursor.skip(value)

- 출력할 데이터의 시작부분을 설정할 때 사용합니다. value 값 갯수의 데이터를 생략하고, 다음부터 출력합니다.

- 2개의 데이터를 생략하고 출력

  > db.orders.find().skip(2)



### 응용

- order를 최신순으로 한 페이지당 2개씩 나타내기

  ```javascript
  var showPage = function(page) {
      return db.orders.find().sort({"_id":-1}).skip((page-1)*2).limit(2);
  }
  
  > showPage(1)
  { "_id" : 6, "item" : { "category" : "brownies", "type" : "blondie" }, "amount" : 10 }
  { "_id" : 5, "item" : { "category" : "cake", "type" : "carrot" }, "amount" : 20 }
  ```