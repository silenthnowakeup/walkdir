# Dirwalk

### Программа dirwalk, сканирующая файловую систему и выводящая информацию в соответствии с опциями программы. Формат вывода аналогичен формату вывода утилиты find.

### Сборка и запуск:

`git clone https://github.com/silenthnowakeup/walkdir.git`  
`cd walkdir`  

`make MODE=release`  
или  
`make MODE=debug`

`./build/debug/walkdir [dir] [options]`

### Options:
Программа поддерживает опции -l, -d, -f, -s.
Допустимые опции:

* `-l` - только символические ссылки (-type l)
* `-d` - только каталоги (-type d)
* `-f` - только файлы (-type f)
* `-s` - сортировать выход в соответствии с LC_COLLATE

Опции могут быть указаны как перед каталогом, так и после.  
Опции могут быть указаны как раздельно, так и вместе (-l -d, -ld ).  
Если опции ldf опущены, выводятся каталоги, файлы и ссылки.
