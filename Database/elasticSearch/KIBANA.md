# KIBANA

### 키바나 설치 및 실행



공부하다 마주친 에러 : name과 team의 string이 분리되는 문제

- text인 type을 keyword로 수정해준다.

  text 타입은 입력된 문자열을 텀 단위로 쪼개어 역 색인 구조를 만듭니다.

  fielddata : true 설정이 되면 쿼리에 메모리 사용량이 많아지기 때문에 일반적으로는 권장하지 않는다.

- keyword 타입은 입력된 문자열을 하나의 토큰으로 저장합니다. text 타입에 keyword 애널라이저를 적용한 것과 동일합니다. 집계 또는 정렬에 사용할 문자열 필드를 keyword 타입으로 지정합니다.





