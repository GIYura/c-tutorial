#### Системы сборки

Система сборки — набор программ и сопутствующих текстовых файлов, которые позволяют собрать кодовую базу программного 
обеспечения.

Сборка кодовой базы — получение конечных продуктов компиляции из исходных файлов.

**Make** — утилита, автоматизирующая процесс преобразования файлов из одной формы в другую. Чаще всего 
это компиляция исходного кода в объектные файлы и последующая компоновка в исполняемые файлы или библиотеки.

Утилита использует специальные **make-файлы**, в которых указаны зависимости файлов друг от друга и правила для их удовлетворения. 
На основе информации о времени последнего изменения каждого файла Make определяет и запускает необходимые программы.

**Makefile** — текстовый файл (без какого-либо расширения), который находится в каталоге с исходниками и содержит цели сборки и команды, 
позволяющие **Make** знать, как собирать текущую кодовую базу.

**Примечание:**

Для запуска утилиты make, необходимо выполнить:

```
make -f [make-file-name]
```

#### CMAKE

**CMake** — генератор скриптов сборки для других систем, таких как **Make** и **Ninja**.
