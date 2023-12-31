#### СОДЕРЖАНИЕ

```
src-0 - пример композиции;
src-1 - пример агрегации.
```

#### Общая информация

Некоторые аспекты классов:

- класс — это схема, которая используется в качестве «чертежа» для создания
объектов;

- из одного класса можно создать много объектов;

- класс определяет, какие атрибуты должны присутствовать в каждом объекте,
создаваемом на его основе. Но он не имеет никакого отношения к значениям,
которые могут быть присвоены этим атрибутам;

- сам класс не потребляет никакой памяти (по крайней мере не в C или C++) 
и существует лишь в виде исходного кода и только на этапе компиляции.
Но объекты существуют во время выполнения и потребляют память;

- создание объекта начинается с выделения памяти. Освобождение памяти — 
последняя операция, которую выполняет объект;

- объект должен создаваться сразу после выделения памяти и уничтожаться 
непосредственно перед ее освобождением;

- объект может владеть частью ресурсов наподобие потоков, буферов, массивов и пр., 
которые должны быть освобождены перед его уничтожением.

#### Композиция

![Composition](https://github.com/GIYura/c-tutorial/blob/main/extreme-c/chapter-7/composition.png)

**Примечание:**
Класс двигатель не может существовать отдельно (самостоятельно) от автомобиля.

Отношение «композиция» между двумя объектами означает, что один из них 
обладает другим. Иными словами, один объект состоит из другого.

При его использовании должно выполняться одно важное условие:
время жизни внутреннего объекта привязано к времени жизни внешнего объекта
(контейнера).

Примем, что один объект (двигатель) не может существовать без внешнего 
контейнера (авто). В некоторых случаях это возможно.

#### Агрегация

![Aggregation](https://github.com/GIYura/c-tutorial/blob/main/extreme-c/chapter-7/aggregation.png)

В агрегации тоже применяется контейнер, который содержит другой объект.
Основное отличие в том, что время жизни контейнера никак не связано с временем
жизни содержащегося в нем объекта.

Важной особенностью агрегации является то, что контейнер не должен влиять на время 
жизни внутреннего объекта; если следоватьданному правилу, то никаких проблем с памятью 
возникнуть не должно.

**Примечание:**

Агрегация, в отличие от композиции, является временным отношением между двумя объектами.

