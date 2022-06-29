# 스파크 머신러닝 완벽 가이드

## select

- select() 메소드는 SQL의 Select 절과 유사하게 한개 이상의 컬럼들의 값을 DataFrame형태로 반환.
- 한개의 컬럼명, 또는 여러개의 컬럼명을 인자로 입력할 수 있음.
- 개별 컬럼명을 문자열 형태로 또는 DataFrame의 컬럼 속성으로 지정
- DataFrame의 컬럼 속성으로 지정시에는 DataFrame.컬럼명, DataFrame[컬럼명], col(컬럼명) 으로 지정 가능.

## filter

- filter()는 SQL의 where와 유사하게 DataFrame내의 특정 조건을 만족하는 레코드를 DataFrame으로 반환.
- filter()내의 조건 컬럼은 컬럼 속성으로 지정 가능. 조건문 자체는 SQL 과 유사한 문자열로 지정 할 수 있음(조건 컬럼은 문자열 지정이 안됨. )
- where() 메소드는 filter()의 alias이며 SQL where와 직관적인 동일성을 간주하기 위해 생성.
- 복합 조건 and는 & 를, or를 | 를 사용. 개별 조건은 ()로 감싸야 함.

## aggregation

- pandas dataframe과 다르게 spark dataframe은 count()를 제외한 max, min, avg와 같은 aggregate 함수를 바로 쓸 수 없고, select() 메소드 내에서 호출되어야 한다.

## groupBy

- pandas DataFrame의 groupby(by='group_by_col') 수행 시 group_by_컬럼명 레벨로 group by 된 DataFrameGroupBy 객체를 반환하고 여기에 aggregation 메소드 적용.
- spark DataFrame도 groupBy('group_by_col) 수행 시 group_by_col 레벨로 group by 된 GroupedData 객체 반환하고 여기에 aggregation 메소드 적용.
- pandas DataFrameGroupBy 객체에 agg() 메소드를 이용하여 서로 다른 컬럼에 서로 다른 aggregation 함수 적용 가능
- spark GroupedData 객체도 agg() 메소드를 이용하여 서로 다른 컬럼에 서로 다른 aggregation 함수 적용 가능
- spark groupBy()는 pandas groupby()의 특징과 SQL의 특징을 함께 가짐.