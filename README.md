# Локальный поисковой движок по файлам
### Сделано AndrGole 

## Функциональный состав проекта

- json файлы
- - answers - вывод результатов поиска
- - config - настройки проекта и некоторая информация о нём
- - requests - список запросов
- exe файл
- - search_engine - запуск программы

## Как использовать
Для настройки проекта есть три json файла и папка с файлами формата txt (**!!!Важно другие форматы не читаются!!!**)
Файл config выглядит подобным образом и нужен для основных настроек
```sh
{
  "config": {
    "max_responses":5,
    "name":"AndrGole_SearchEngine",
    "version":"0.1"
  },
  "files": [
    "file001.txt",
    "file002.txt",
    "file003.txt",
    "file004.txt",
    "file005.txt",
    "file006.txt",
    "file007.txt",
    "file008.txt",
    "file009.txt"
  ]
}
```
В строке max_responses нужно указывать максимальное количество результатов поиска которое вы хотите видеть
Строка name и строка version указывает название проекта и его версию
Ниже представлен список файлов среди которых программа ищет результаты
В проекте эти файлы расположены в папке resources

Файл requests выглядит подобным образом и нужен для задания списка запросов по которым будет осуществлятся поиск
```sh
{
 "requests": [
 	"some word",
	"sugar",
	"drink milk",
	"test"
 ]
}
```
В поле requests расположен список запросов

Файла answers изначально может и не быть нужен для вывода результатов поиска
Рассмотрим то как он устроен
```sh
{
	"answer": {
		"request001": {
			"result": "true",
			"relevance": {
				"docid": 3, "rank" : 1.000,
				"docid": 0, "rank" : 0.666,
				"docid": 1, "rank" : 0.333
			}
		},
		"request002": {
			"result": "true",
			"relevance": {
				"docid": 5, "rank" : 1.000,
				"docid": 4, "rank" : 0.583,
				"docid": 6, "rank" : 0.500,
				"docid": 1, "rank" : 0.166,
				"docid": 8, "rank" : 0.166
			}
		},
		"request003": {
			"result": "true",
			"docid": 0, "rank" : 1.000
		},
		"request004": {
			"result": "false"
		}
	}
}
```
В поле answer расположены запросы
В файле они отображаются как request**ID** где *ID* это порядковый номер запроса в файле requests
Поле запроса состоит из нескольких элементов
- result - результат запроса а именно наличие онного или нет
- relevance - если результат есть и в списке результатов более одного файла

Далее docid **номер документа** rank **ранг этого документа**
docid нумерует документы в порядке представленном в файле config и нумерует их начиная с нуля.
rank показывает соответсвие результата вашему запросу основываясь на частоте встречаемости слов из запроса

## Установка
Для установки надо просто скачать rar файл и распаковать куда удобно
Для запуска программы надо запустить файл search_engine.exe

## Стек используемых технологий
ОС Windows 10
Язык программирования C++
Инструмент разработки CLion

#
#
