# BigBrother
### Авторизация в API
- **URL**: http://bbrother.familyagency.ru/oauth/token
- **METHOD**: POST
- **HEADERS**: Content-Type: application/json

| Параметр | Значение | Описание |
| ------ | ------ | ------ | 
| grant_type | "password" | Тип авторизации, всегда "password" |
| client_id | {client_id} | ID клиентского приложения |
| client_secret | {client_secret} | Пароль клиентского приложения |
| username | test@test.test | e-mail указанный при регистрации |
| password | verysecretpassword | Пароль указанный при регистрации |

В ответе будет передан "access_token". Его необходимо использовать для дальнейших запросов к API.
Пример запроса:
```json
{
  "grant_type":"password",
  "client_id":1,
  "client_secret":"ea135929105c4f29a0f5117d2960926f",
  "username":"test@test.test", 
  "password":"verysecretpassword"
}
```
Пример ответа:
```json
{
    "token_type":"Bearer",
    "expires_in":31536000,
    "access_token":"eyJ0eXAiOiJKV1QiLCJhbGciOiJSUzI1NiIsImp0aSI6IjMyYWYyYjM1NTI2YWU4YWU0NmJlMTM5YjA4NjdiNTllMjlkZjU3MGU5M2Y5MjgyZDBhODIyMjk1MmZhZjVlZjJlYjE4Yjk3M2ZlOWZlNmE4In0.eyJhdWQiOiIyIiwianRpIjoiMzJhZjJiMzU1MjZhZThhZTQ2YmUxMzliMDg2N2I1OWUyOWRmNTcwZTkzZjkyODJkMGE4MjIyOTUyZmFmNWVmMmViMThiOTczZmU5ZmU2YTgiLCJpYXQiOjE1MjIzMTM3ODgsIm5iZiI6MTUyMjMxMzc4OCwiZXhwIjoxNTUzODQ5Nzg4LCJzdWIiOiIxIiwic2NvcGVzIjpbXX0.Kg8k0OOLx69NDjkgH-Ezz6n5tXsRAGWaOzzvdj8lIgCEUW9Ei1j45IKqGNcA8Vkxx4J36G3ldH5Q4RaAxBLvHsN--_6EEpdTWORlqa35YUKJt6YzVZys7OKCv0uaCDs4lTxqA2PObK_2pHmTtFOXWohVgXpCnplbwzQIQIDUYkOZCoocrFjqoOfPaV-eZZ3goq62rTXWGMzZGCzAvdaE8MUK4E4_rS72ehoid2_AgepMX_rkjcUsS7T71DyR6Kz-eGug0By91Sm-GKE_aas3FR5x13PAhts0zIlmCF5x_lflFkOWAJlKR--PhHqk_-nAg6yQrUpM-94FI7xPH341GMurp6GijP-TlpmV2tMmuZ7BYeVLunslj8ODypyBsmW86fInaigXO3FT97w96l_TmxaCEZlX9Gz6v0bPLROpx0Q5yJotTQIEPzbazZ9jxoEQS8jMMv9mwMKz9JxB6RmFod0AIZUj5I7ZxyanNIM1sKwAsIaQ0OX2QETymzAluuw_HGkJNJSZhlsqS3Ijse2o4gwXFLZgrBSnyKD2YDWKjv3paM9XM",
    "refresh_token":"def5020096864be0c3660af786ba7a22c82d5a45752cf52a888f61b8d7c795b94268c9670e915cb318f1e017be4d3bc5d63bf100ce93c10195f43e2a871b4661e9b29f84e4ca90109ca2125a2cce5244a5214d938752457d8772c7801d588282df1c9e6c9fc5f2eac9186dd0fbc74355dc5082a9a372aad19eb82cc1042f86f4fb863e7d054b72f699c19683d1f5a4336a7c7c4630df466b0956e54c137f6c0ae8c74e538fe6ad386d9d3123d82accb32526272cd244688cd7491197dfada283a37f3a45553bf74f61c4726b5839188aac8639314e77d2afaf8a0ca063e872bdacc5d290f139a51b7db94b8199a7af1c5cc838ef1aed99d2717651848858162bb88859b35c1be8b406d6fcff8639fc9ade85874e8a28eb7f16750f12c819fe343b65"
}
```


### Запросы
Зпросы строятся по архитектуре [CRUD](https://ru.wikipedia.org/wiki/CRUD)
Основной URL: http://bbrother.familyagency.ru/
Обязательные заголовки (необходимо указывать при каждом запросе)
	Content-Type: application/json;
	Authorization: Bearer {access_token_here};

В некоторых запросах необходимо передавать ID. Эта переменная подставляется непосредственно в строку запроса, например для получения user с ID=123: http://bbrother.familyagency.ru/api/users/123.

Список объектов и их методов:

#### Users
##### Получение списка пользователей
- **URL**: api/users/
- **METHOD**: GET

Пример ответа:
```json
[
    {
        "id":3,
        "name":"test",
        "master_token":"test_token1",
        "created_at":"2018-03-28 16:00:11",
        "updated_at":"2018-03-28 16:00:11"
    }
]
```

##### Получение конкретного пользователя по id. В ответе так же приходит связанная информация по объекту (phrases, face_tokens)
- **URL**: api/users/{id}
- **METHOD**: GET

Пример ответа:
```json
[
    {
        "id":3,
        "name":"test",
        "master_token":"test_token1",
        "created_at":"2018-03-28 16:00:11",
        "updated_at":"2018-03-28 16:00:11",
        "phrases":[
            {
                "id":1,
                "user_id":3,
                "phrase":"test_phrase",
                "created_at":"2018-03-28 16:08:18",
                "updated_at":"2018-03-28 16:08:18"
            }
        ],
        "face_tokens":[
            {
                "id":1,
                "user_id":3,
                "face_token":"test_face_token",
                "created_at":"2018-03-28 16:08:35",
                "updated_at":"2018-03-28 16:08:35"
            }
        ]
    }
]

```

##### Создание пользователя
- **URL**: api/users/
- **METHOD**: POST
Пример тела запроса:
```json
{
  "name":"lolkek",
  "master_token":"cheburek"
}

```
Пример ответа:
```json
{
    "name":"lolkek",
    "master_token":"cheburek",
    "updated_at":"2018-03-29 09:34:53",
    "created_at":"2018-03-29 09:34:53",
    "id":4
}
```

##### Изменение пользователя
- **URL**: api/users/{id}
- **METHOD**: PUT
Пример тела запроса:
```json
{
  "name":"lolkek",
  "master_token":"cheburek1"
}

```
Пример ответа:
```json
{
    "name":"lolkek",
    "master_token":"cheburek1",
    "updated_at":"2018-03-29 09:34:53",
    "created_at":"2018-03-29 09:34:53",
    "id":4
}
```

##### Удаление пользователя
- **URL**: api/users/{id}
- **METHOD**: DELETE
Пример ответа:
```json
204
```


#### Phrases
##### Получение фразы
- **URL**: api/phrases/{id}
- **METHOD**: GET

##### Создание фразы
- **URL**: api/phrases/
- **METHOD**: POST

Пример тела запроса:
```json
{
  "phrase":"new_phrase",
  "user_id":3
}
```
Пример ответа:
```json
{
    "phrase":"new_phrase",
    "user_id":3,
    "updated_at":"2018-03-29 09:40:29",
    "created_at":"2018-03-29 09:40:29",
    "id":2
}
```

##### Изменение фразы
- **URL**: api/phrases/{id}
- **METHOD**: PUT

Пример тела запроса:
```json
{
  "phrase":"new_phrase_test",
  "user_id":3
}
```
Пример ответа:
```json
{
    "phrase":"new_phrase_test",
    "user_id":3,
    "updated_at":"2018-03-29 09:43:33",
    "created_at":"2018-03-29 09:40:29",
    "id":2
}
```

##### Удаление фразы
- **URL**: api/phrases/{id}
- **METHOD**: DELETE
Пример ответа:
```json
204
```


#### FaceTokens
##### Получение токена
- **URL**: api/faceTokens/{id}
- **METHOD**: GET

##### Создание токена
- **URL**: api/faceTokens/
- **METHOD**: POST

Пример тела запроса:
```json
{
  "face_token":"new_test_face_token",
  "user_id":3
}
```
Пример ответа:
```json
{
    "face_token":"new_test_face_token",
    "user_id":3,
    "updated_at":"2018-03-29 09:46:06",
    "created_at":"2018-03-29 09:46:06",
    "id":2
}
```

##### Изменение токена
- **URL**: api/faceTokens/{id}
- **METHOD**: PUT

Пример тела запроса:
```json
{
  "face_token":"new_test_face_token_111",
  "user_id":3
}
```
Пример ответа:
```json
{
    "id":2,
    "user_id":3,
    "face_token":"new_test_face_token_111",
    "created_at":"2018-03-29 09:46:06",
    "updated_at":"2018-03-29 09:46:55"
}
```

##### Удаление токена
- **URL**: api/faceTokens/{id}
- **METHOD**: DELETE
Пример ответа:
```json
204
```
