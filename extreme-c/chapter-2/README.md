#### Этапы компиляции

- препроцессор;
- компилятор;
- ассемблер;
- компановщик.


##### Препроцессор

Код, прошедший обработку препроцессором, называется единицей трансляции (или единицей
компиляции). 

Единица трансляции — это отдельный логический блок кода на C, сгенерированный препроцессором и готовый к компиляции.

В gcc можно сохранить единицу трансляции:

```
gcc -E file.c
```

Итог этого этапа:
На вход поступает исходный файл, а на выходе получается соответствующая единица трансляции.

##### Компилятор

На вход подается единица компиляции, полученная на предыдущем этапе, а на выходе получается 
соответствующий **ассемблерный код**.

В gcc можно сохранить ассемблерный код:

```
gcc -S file.c
```

Итог этого этапа:
Файл с тем же именем что и исходник, но с расширением **.s**.

##### Ассемблер

Цель — сгенерировать инструкции машинного уровня (или машинный код) на основе ассемблерного кода, 
созданного компилятором на предыдущем этапе. У каждой архитектуры есть свой ассемблер, 
который может преобразовать собственный ассемблерный код в машинные инструкции.

Файл с машинными инструкциями, который мы сгенерируем в этом подразделе,
называется объектным файлом.

В большинстве Unix-подобных операционных систем есть утилита под названием **as**, 
с помощью которой ассемблерный код можно превратить в переносимый объектный файл.

```
as file.s -o file.o

```
Можно объединить предыдущих 3 шага в один с помощью команды:

```
gcc -c file.c
```
Итог этого этапа:

Переносимый объектный файл с тем же именем, что и у исходника с расширением **.o**.

Переносимые объектные файлы не являются исполняемыми. Если конечным продуктом компиляции проекта должен быть
исполняемый файл, то нужно взять все (или по крайней мере некоторые) переносимые объектные файлы, 
уже сгенерированные, и скомпоновать их в единое целое.



