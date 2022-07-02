# 스파크 머신러닝 완벽 가이드

## Spark SQL

```python
sdf.createOrReplaceTempView('filename')
```

- sql 사용이 가능하도록 spark dataframe을 db view로 생성해준다.

- sql 코드를 정상 실행하기 위해서 %sql을 적어줘야 한다.

  ```sql
  %sql
  select * from table;
  ```

- Null, Not Null

  ```sql
  select * from table where col is null and col2 is not null;
  ```

- select case when

  ```sql
  select * case when 조건1 then 실행문1 ~ else 실행문N END (as 별칭) from table;
  ```