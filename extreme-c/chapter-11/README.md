#### СОЖЕРДАНИЕ

```
src-0 - пример использования системного вызова напрямую из приложения (без libc);
[reference](https://medium.com/anubhav-shrimal/adding-a-hello-world-system-call-to-linux-kernel-dad32875872)
src-1 - демо системного вызова. /* TODO: should be done on raspberry pi */
```

#### Введение

Когда генерируется прерывание, его обработчик в ядре подхватывает
системный вызов вместе с номером и аргументами. Затем он обращается к таблице
системных вызовов, чтобы найти подходящую функцию, которая должна быть 
выполнена на стороне ядра.

К моменту выполнения обработчика прерывания пользовательский код, который 
инициировал системный вызов, уже покинул центральный процессор,уступив место ядру. 
Это основной механизм, лежащий в основе системных вызовов. 
Когда такой вызов инициируется, процессор переключается в другой режим
и принимает инструкции от ядра, тогда как приложение в пользовательском пространстве 
перестает выполняться. 
Вот почему мы говорим, что ядро выполняет логику системного вызова от имени 
пользовательского приложения.

Ниже перечислены шесть ключевых отличий в процессе разработки для ядра и для
пользовательского пространства.

 - Процесс ядра находится во главе системы и существует в единственном экземпляре. 
Это означает, что если код приведет к сбою в ядре, то, скорее всего, придется перезагрузить 
компьютер и позволить ядру заново выполнить инициализацию. Следовательно, 
цена ошибки в таком коде очень высока, и для проведения экспериментов в нем требуется 
перезагрузка компьютера; в программах пользовательского пространства без этого можно легко
обойтись. В случае ошибки генерируется дамп сбоя ядра, который помогает
выявить причину.
 - В кольце ядра нет никакой стандартной библиотеки C наподобие glibc! Иными
словами, стандарты SUS и POSIX здесь не действуют. Поэтому вы не можете
подключать заголовочные файлы libc, такие как stdio.h или string.h. Вы получаете в свое 
распоряжение отдельный набор функций, которые необходимо использовать для выполнения 
различных операций. Эти функции обычно находятся в заголовках ядра и могут отличаться 
в зависимости от разновидности Unix, поскольку в данной области еще не проводилось никакой 
стандартизации.
Например, занимаясь разработкой ядра в Linux, вы можете выполнять запись
в буфер сообщений ядра с помощью функции printk. Но в FreeBSD для этого
предусмотрено семейство функций printf, которые отличаются от своих аналогов из libc; 
они находятся в заголовочном файле <sys/system.h>. Их эквивалент в ядре XNU, которое используется 
в macOS, — функция os_log.
 - В ядре тоже можно читать и изменять файлы, но без использования функций
из libc. У каждой Unix-системы есть собственный способ доступа к файлам из
кольца ядра. То же самое относится ко всем другим возможностям, доступным
в libc.
 - В кольце ядра вы имеете полный доступ к физической памяти и многим другим
возможностям. Поэтому очень важно писать безопасный и надежный код.
 - В ядре нет механизма системных вызовов. Системные вызовы — основной метод
взаимодействия с кольцом ядра из пользовательского пространства. Поэтому
в самом ядре в нем нет необходимости.
 - Процесс ядра создается путем копирования образа ядра в физическую память.
Этим занимается загрузчик. Вы не можете добавить новые системные вызовы,
не прибегнув к созданию совершенно нового образа и инициализации его в ходе
перезагрузки системы. Кое-какие ядра поддерживают модули, которые можно
динамически добавлять и удалять, но с системными вызовами этого делать
нельзя.

#### Модули ядра

Монолитные ядра обычно предусматривают механизм, который позволяет динамически 
подключать к активному ядру новые компоненты. 
Эти подключаемые компоненты называются модулями ядра.

В целом общение с модулями ядра в Linux и некоторых похожих операционных системах 
происходит тремя способами:

- Файлы устройств в каталоге **/dev**. Модули ядра в основном разрабатываются
для использования в качестве драйверов устройств. Вот почему самый распространенный 
способ взаимодействия с ними — использование файлов внутри
каталога /dev. Читая и записывая эти файлы, можено обмениваться информацией с модулями;
- Содержимое **procfs**. Файлы в каталоге /proc можно использовать для чтения
метаинформации об отдельных модулях ядра. Эти файлы также позволяют отправлять модулям 
метаинформацию или управляющие команды;
 - Содержимое **sysfs**. Это еще одна файловая система в Linux, которая позволяет
управлять пользовательскими процессами и другими компонентами, относящимися к ядру 
(включая модули ядра), с помощью скриптов или вручную. Ее можно считать новой версией procfs.

