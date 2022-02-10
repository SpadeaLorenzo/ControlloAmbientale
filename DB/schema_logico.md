# Logical DB schema

### user (<ins>username</ins> , passowrd);
<br>

### fishino (<ins>id</ins> , name, place, user_username(fk));
<br>

### datas (<ins>data, fishino_id(fk)</ins>, humidity, brightness, sound, temprature, air_quality);