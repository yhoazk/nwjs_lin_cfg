# nwjs_lin_cfg

## Supuestos:
	* Existen lineas que solo contienen las palabras {nodes, signals, frames, schedule_tables}
	y en esa liena solo estan esas palabras y caracteres en blnco ie {tabs, espacios y lf cr}
	* En seguida de la linea descrita arriba hay un bracket que abre - \{
	* Dependiendo de cada tipo hay las siguientes estructuras, sin contar whitespaces y enclosed in brackets
		- Nodes
			-> [m|M]aster: <id>, \dms,\d.\d\dms; #solo 1 por Nodes
			-> [s|S]laves: *<id>,
		- Signals
			-> <string_id>:<int\d\d>,<int\d\d>,<str_dic[mst.,slv]>,<str_dic[mst,slv]>; # N elementos
		- Frames
			-> Una linea -header- conteniendo
				-> <str_name>:\d\d,<str_dic[mst|slv]>
				-> linea conteniendo {
				-> <str_name>,<offset>\ð\d; #n posible
				-> linea conteniendo }

		- schedule_tables
			-> <str_name>
			-> linea conteniendo {
			-> <name>' 'delay' '\d\d' '*ms; #una por cada Frame
			-> linea conteniendo }

Correr regexp para poner cada {} en una sola linea
- eliminar lineas vacias
- poner un \n despues de cada ;, {

 The file contains four major structures:
 -Nodes
 -signal
 -frames
 -schedule_tables
