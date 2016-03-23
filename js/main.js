
var fs = require('fs');
var json_cfg;


fs.readFile('./LIN_configuration.txt', 'utf-8', function (error, contents) {
//	if(error) throw error;
	// console.log(contents);
	// console.log(typeof contents);
	//json_cfg = JSON.parse(contents);
//	console.log(obj);
	parseCfgFile(contents);
	document.write(contents);

});

/**



*/
/* Only 1 master multiple slaves*/
var nodes_obj = [	{
		node_name: '',
		time_base: '',
		jitter: ''
	}];

/**/
var signals_obj = [	{
			signal_name: '',
			signal_size: '',
			init_value: '',
			published_by:'',
			suscribed_by:''
}];

var frames_obj = [{
		frame_name: '',
		frame_id:'',
		published_by:'',
		frame_size:'', //optional
		signals_frms:{
			signal_name: '',
			signal_offset:''
		}
	}];

var sched_table_obj ={
		table_name:'',
		frames:[{
			frame_name:'',
			frame_time:''
	}]
};

var states = {
	'initial': 0,
	'nodes': 1,
	'signals': 2,
	'frames': 3,
	'sched_tables': 4,
	'unk': 5,
}
/* 0: no abierto 1: abirto 2: cerrado */
var nodes_bracket = 0;
var signals_bracket = 0;
var frames_bracket = 0;
var sched_bracket = 0;

function parseNodes() {

}

function parseSignals() {

}
function parseFrames() {

}
function parseScheduleTable() {

}

function parseCfgFile(file_raw) {
		var reader = new FileReader();
		// reader.onload = function (progress) {
			var lines = file_raw.split('\n')
			var line_string;
			var state = states['initial'];
			for(var line = 0; line < lines.length; line++)
			{
				line_string = lines[line].replace(/\s/g,''); //removing whitespaces
				//console.log("Lnum:" + line + "-> " + line_string);
				if(line_string === '') continue;
				if(line_string.match(/nodes/i)){
					console.log("begining of nodes");
					state = states['nodes'];
				}
				if(line_string.match(/signals/i)){
					console.log("begining of signals");
					state = states['signals'];
				}

				if(line_string.match(/frames/i)){
					console.log("begining of frames");
					state = states['frames'];
				}

				if(line_string.match(/schedule_tables/i)){
					console.log("begining of sched_tables");
					state = states['sched_tables'];
				}


				switch (state) { //'Master: MST, 5 ms, 0.1 ms;'.match(/:(.*)$/ig);
					case states['nodes']:////////////////////////////////////////////////
						console.log('state nodes');
						if(nodes_bracket === 1){
							if(line_string.match(/master/i)){
								sub_mstr = line_string.match(/:(.*)$/ig)[0].split(','); //at this point sub_mstr ==Master:MST,5ms,0.1ms;

								nodes_obj[0] = {
									node_name: sub_mstr[0].match(/\w+/),
									time_base: sub_mstr[1].match(/\d+/),
									jitter: sub_mstr[2].match(/\d+.\d+/)
								};
							}
							else if (line_string.match(/slaves/i)) {
								sub_mstr = line_string.match(/:(.*)$/ig)[0].split(','); //at this point sub_mstr ==Master:MST,5ms,0.1ms;
								nodes_obj.push({
									node_name: sub_mstr[0].match(/\w+/)
									//time_base: sub_mstr[1].match(/\d+/),
									//jitter: sub_mstr[2].match(/\d+.\d+/)
								});
							}
						}
						if(nodes_bracket === 0 && line_string === '{'){
							nodes_bracket = 1;
						}
						else if (nodes_bracket === 1) {

							if(line_string === '}') {
								nodes_bracket = 2;
								state = states['initial'];
							}
						}else if (nodes_bracket === 2) {

						}
						break;

					case states['signals']:///////////////////////////////////////////////
						console.log('state signals');
						if(signals_bracket === 1){
							if(line_string === '}') {
								signals_bracket = 2;
								state = states['initial'];
								continue;
							 }
								sub_str = line_string.match(/:(.*)$/i)[1].split(','); //at this point sub_mstr ==Master:MST,5ms,0.1ms;
								name = line_string.match(/^\w+/gi);
								signals_obj.push(	{
											signal_name: name,
											signal_size: sub_str[0],
											init_value: sub_str[1],
											published_by: sub_str[2],
											suscribed_by:sub_str[3].match(/\w+/gi)[0]
								});
						}
						if(signals_bracket === 0 && line_string === '{'){
							signals_bracket = 1;
						}



						break;
					case states['frames']:////////////////////////////////////////////////
						console.log('state frames');
						break;
					case states['sched_tables']://////////////////////////////////////////
						console.log('state sched_tables');
						break;
					case states['initial']:///////////////////////////////////////////////
						console.log('state ink');
						break;
					default:

				}
			}
		// }

}


//var bnt_gen =
