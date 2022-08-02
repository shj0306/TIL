## Document Query - find()

## Document 조회 : db.colection_name.find(query, projection)

| parameter  | Type     | 설명                                                         |
| ---------- | -------- | ------------------------------------------------------------ |
| query      | document | 도큐먼트를 조회할 때 기준을 정한다. 기준이 없이 컬렉션에 있는 모든 도큐먼트를 조회할 때는 빈 매개변수를 전달한다 |
| projection | document | 도규먼트를 조회할 때 보여질 field를 정한다                   |

- 반환 값 : cursor

  - 조건에 해당하는 document들을 선택하여 cursor를 반환합니다. cursor는 쿼리 요청의 결과값을 가리키는 pointer입니다.

### 예제

```
db.articles.insert([
    {
        "title" : "article01",
        "content" : "content01",
        "writer" : "Velopert",
        "likes" : 0,
        "comments" : [ ]
    },
    {
        "title" : "article02",
        "content" : "content02",
        "writer" : "Alpha",
        "likes" : 23,
        "comments" : [
                {
                        "name" : "Bravo",
                        "message" : "Hey Man!"
                }
        ]
    },
    {
        "title" : "article03",
        "content" : "content03",
        "writer" : "Bravo",
        "likes" : 40,
        "comments" : [
                {
                        "name" : "Charlie",
                        "message" : "Hey Man!"
                },
                {
                        "name" : "Delta",
                        "message" : "Hey Man!"
                }
        ]
    }
])
```

- articles 컬렉션에 있는 모든 도큐먼트들을 조회할 때

  > db.articles.find()

- writer 값이 "Velopert"인 Document 조회 

  > db.articles.find({"writer":"Velopert"})

- likes 값이 30 이하인 Document 조회 

  > db.articles.find({"likes":{&lte:30}})

## Query 연산자

### 비교 연산자

| operator | 설명                            |
| -------- | ------------------------------- |
| $eq      | 주어진 값과 일치하는 값         |
| $gt      | 주어진 값보다 큰 값             |
| $gte     | 주어진 값보다 크거나 같은 값    |
| $lt      | 주어진 값보다 작은 값           |
| $lte     | 주어진 값보다 작거나 같은 값    |
| $in      | 주어진 배열 안에 속하는 값      |
| $nin     | 주어진 배열 안에 속하지 않는 값 |

- likes 값이 10보다 크고 30보다 작은 Document 조회

  > db.articles.find({"likes":{$gt:10, $lt:30}})

- writer 값이 배열 ["Alpha", "Bravo"] 안에 속하는 값인 Document 조회

  > db.articles.find({"writer":{$in:["Alpha", "Bravo"]}})

### 논리 연산자

| operator | 설명                                   |
| -------- | -------------------------------------- |
| $or      | 주어진 조건 중 하나라도 true일 때 true |
| $and     | 주어진 조건 모두 true일 때 true        |
| $not     | 주어진 조건이 false일 때 true          |
| $nor     | 주어진 모든 조건이 false일 때 true     |

- title 값이 "article01" 이거나, writer 값이 "Alpha"인 Document 조회

  > db.articles.find({$or:[{"title":"article01"}, {"writer":"Alpha"}]}

- writer 값이 "Velopert"이고, likes 값이 10 미만인 Document 조회

  > db.articles.find({$and:[{"writer":"Velopert}, {"likes":{$lt:10}}]})
  >
  > db.articles.find({"writer":"Velopert","likes":{$lt:10}})



### $regex 연산자

- 정규식을 통해서 Document를 조회할 수 있습니다. 이 연산자는 다음과 같이 사용됩니다.

  ```
  { <field>: { $regex: /pattern/, $options: '<options>' } }
  { <field>: { $regex: 'pattern', $options: '<options>' } }
  { <field>: { $regex: /pattern/<options> } }
  { <field>: /pattern/<options> }
  ```

  | option | 설명                                             |
  | ------ | ------------------------------------------------ |
  | i      | 대소문자 무시                                    |
  | m      | 정규식에서 ^를 사용할 때 값에 \n이 있다면 무력화 |
  | x      | 정규식 안에 있는 공백을 모두 무시                |
  | s      | .을 사용할 때 \n을 포함해서 매치                 |

- 정규식 article0[1-2]에 일치하는 값이 title에 있는 Document 조회

  > db.articles.find({"title":/article-[1-2]/})
  >
  > db.articles.find({"title":{$regex:'article0[1-2]'}})

### $where 연산자

- 자바스크립트 표현식을 사용할 수 있습니다.

- comments field가 비어있는 Document 조회

  > db.articles.find({$where:"this.commnts.length==0"})

### $elemMatch 연산자

- Embedded Documents 배열을 쿼리할 때 사용됩니다. 

- comments 중 "Charlie"가 작성한 댓글이 있는 Document 조회

  > db.articles.find({"comments":{$elemMatch:{"name":"Charlie"}}})

```json
{
    "username": "velopert",
    "name": { "first": "M.J.", "last": "K."},
    "language": ["korean", "english", "chinese"]
}
```

- 한 개의 Embedded Document 경우

  > db.users.find({"name.first" : "M.J."})

- Document 배열이 아니라 그냥 배열일 경우

  > db.users.find({"language":"korean"})



## projection

- 쿼리 결과값에 보여질 field를 정하는 파라미터

- article의 title과 content만 조회

  > db.articles.find({}, {"_id": false, "title": true, "content": true})

### $slice 연산자

- Embedded Document 배열을 읽을 때 limit 설정을 합니다.

- title값이 article03인 Document에서 댓글은 하나만 보이게 출력

  > db.articles.find({"title":"article03"}, {"comments":{$slice:1}})

### $elemMatch 연산자

- query 연산자에 있던 elemMatch와 사용법은 같지만 역할이 다릅니다

- comments중 charlie가 작성한 댓글이 있는 document를 조회 했을 때 게시물 제목과 charlie의 댓글부분만 조회

  ```javascript
  db.articles.find(
  	{
          "comments": {
              $elemMatch: {"name" : "Charlie"}
          }
      },
      {
          "title" :  true,
          "comments": {
              $elemMatch: {"name":"Charlie"}
          }
      }
  )
  ```

