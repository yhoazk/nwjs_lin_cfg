# nwjs_lin_cfg

## Supuestos:
  * El orden en que se declaren no debe de importar
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


regex log
```javascript
'Master: MST, 5 ms, 0.1 ms;'.match(/:(.*)$/ig); => [": MST, 5 ms, 0.1 ms;"]
'Master:MST,5ms,0.1ms;'.match(/:(.*)$/ig)[0].split(',');
[":MST", "5ms", "0.1ms;"]

// nombre del master
'Master:MST,5ms,0.1ms;'.match(/:(.*)$/ig)[0].split(',')[0].match(/\w+/)
["MST"]


'Slaves: SLV'.match(/:(.*)$/ig)[0].split(',')[0].match(/\w+/)
["SLV"]
//tiempo base
'Master:MST,5ms,0.1ms;'.match(/:(.*)$/ig)[0].split(',')[1].match(/\d+/)
["5"]

//jitter
'Master:MST,5ms,2.31ms;'.match(/:(.*)$/ig)[0].split(',')[2].match(/\d+.\d+/)
["2.31"]

/* Para las señales */
'RearFogLampInd:1,0,MST,SLV;'.match(/^\w+/gi);
["RearFogLampInd"]
'RearFogLampInd:1,0,MST,SLV;'.match(/:(.*)$/i)[1].split(',');
["1", "0", "MST", "SLV;"]
```
