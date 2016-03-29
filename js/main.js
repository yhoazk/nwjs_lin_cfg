

var gui = require("nw.gui");
var fs = require('fs');
var json_cfg;
var editor;



fs.readFile('./LIN_configuration.txt', 'utf-8', function (error, contents) {

   editor = CodeMirror(
    document.getElementById("output_editor"),
    {
      mode: {name: "javascript", json: true },
      lineNumbers: true,
      theme: "lesser-dark",
    });
    mode = {name: "javascript", json: true};
    editor.setOption("mode", mode);

    parseCfgFile(contents);
    /* Remove empty objs */
    signals_obj.splice(0,1);
    frames_obj.splice(0,1);
    // sched_table_obj.splice(0,1);

    parseSignals();
    parseFrames();
    parseScheduleTable();
    /* parse tables */
    /*
    Formar una tabla con los frames que
    */
    /***************************************
    Load template
     ***************************************/
    var templateSrc = document.getElementById( "results-template" ).innerHTML;
    var template = Handlebars.compile(templateSrc);
    /*Iterator for UINT8 vars */
    var date_val = Date();
    var data = {
     "lin_cfg":{
        "gen_date": date_val
     },
     signals: signals_obj,
     frames: frames_obj,
     sched_table: sched_table_obj
    };


    var outTemplate = template(data);
    console.log("Type of :" + typeof outTemplate);
    console.log("Type of :" +  outTemplate.split('\n').length);
    editor.setValue(template(data));
});

/* Only 1 master multiple slaves*/
var nodes_obj = [    {
        node_name: '',
        time_base: '',
        jitter: ''
    }];

/**/
var signals_obj = [    {
            signal_name: '',
            signal_size: '',
            init_value: '',
            published_by:'',
            suscribed_by:'',
            var_type:''
}];

var frames_obj = [{
        frame_name: '',
        frame_id:'',
        published_by:'',
        frame_size:'', //optional
        signals_frms:{
            signal_name: '',
            signal_offset:'',
            signal_size: '',
            signal_type: ''
        }
    }];

var sched_table_obj ={
        table_name:'',
        frames:[{
            frame_name:'',
            frame_time:''
    }]
};
/* create an instance in the array per publisher */
var fram_table_obj = [{
  node_name: '',
  frames_of_node : [{
    start_time:'',
    num_of_bytes:'',
    calc_pid: ''
  }],
  isMaster: false
}];

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
var frames_bracket_sub = 0;
var sched_bracket = 0;
var sched_bracket_sub = 0;

function parseNodes() {

}


function genericfilter(arr, criteria) {
return arr.filter(function(obj) {
  return Object.keys(criteria).every(function(c) {
    return obj[c] == criteria[c];
  });
});
}


function getParity_Lin(id) { // the id is supposed to be in dec at the input
  p0 = (
    (id & 1) ^
    ((id >> 1) & 1) ^
    ((id >> 2) & 1) ^
    ((id >> 4) & 1)
  );

  p1 = ~(
    ((id >> 1) & 1) ^
    ((id >> 3) & 1) ^
    ((id >> 4) & 1) ^
    ((id >> 5) & 1)
  );

  parity = (p0 & 1) | ((p1 & 1) << 1);
  console.log(parity);
  console.log(parity << 5);

  return ((parity << 6) | id).toString(16);
}

function parseSignals() {
  for (var i = 0; i < signals_obj.length; i++) {
    if(signals_obj[i].signal_size <= 8){
      signals_obj[i].var_type = 'UINT8';
    }else if(signals_obj[i].signal_size > 8 && signals_obj[i].signal_size <= 16){
      signals_obj[i].var_type = 'UINT16';
    }else if(signals_obj[i].signal_size > 16 && signals_obj[i].signal_size <= 32){
      signals_obj[i].var_type = 'UINT32';
    }
  }
}
function parseFrames() {
  for (var i = 0; i < frames_obj.length; i++) {
    var bit_count = 0;
    for (var j = 0; j < frames_obj[i].signals_frms.length; j++) {
      console.log(frames_obj[i].signals_frms[j].signal_name);
      /* get the index of the object with the singnal name  */
      var index_val = signals_obj.map(function(e) { return e.signal_name; }).indexOf(frames_obj[i].signals_frms[j].signal_name);
      if (-1 != index_val) {
        frames_obj[i].signals_frms[j].signal_size = signals_obj[index_val].signal_size;
        frames_obj[i].signals_frms[j].signal_type = signals_obj[index_val].var_type;
        bit_count += Number(signals_obj[index_val].signal_size);
      } else {
        console.log("signal name not found");
      }
    }
    frames_obj[i].size_bits = bit_count;
  }
}
/* Mix the information of hte schedule_tables and Frames
  schedule_tables only gives the order and timing, all the rest of
  the information comes from frames_obj
  Create a new object in which the information is ordered and parsed
 */
/*
1 find publishers
2 find frames with matching publisher
3 attache each frame to publishers obj
3.1 for each frame attach also relevant information
*/
function parseScheduleTable() {
  for (var i = 0; i < frames_obj.length; i++) {
    var index_val_pub = nodes_obj.map(function(e) { return e.node_name[0]; }).indexOf(frames_obj[i].published_by);
    if(-1 != index_val_pub){
      /* Find if this node has already another obj */
      var already_reg = fram_table_obj.map(function(e) { return e.node_name; }).indexOf(frames_obj[i].published_by);
      if (-1 == already_reg) {
        // create node
        var reg_ex = new RegExp("MST", "i");
        var isMaster = reg_ex.test(frames_obj[i].published_by);
        /* Filter the elements in array with property published_by equal to the second arg */
        var pub_by = [];
        pub_by = genericfilter(frames_obj, {published_by: frames_obj[i].published_by});
        /* Obtain the start_time for each fram pub_by i */
        /* find the name of the frame in  the table */
        var frames_in_table;
        var index_of_frame;
        var this_start_time;
        var this_frame_len_bits;
        frames_in_table = sched_table_obj.frames;

        for (var k = 0; k < pub_by.length; k++) {
          index_of_frame = frames_in_table.map(function(e) { return e.frame_name_sched; }).indexOf(frames_obj[i].frame_name);
          this_start_time = frames_in_table[index_of_frame].frame_delayms
          pub_by[k].start_time = this_start_time;

        }

        /* calculate the PID */

        fram_table_obj.push(
          {
            node_name: frames_obj[i].published_by,
            frames_of_node : [{
              start_time:'',
              num_of_bytes:'',
              calc_pid: ''
            }],

            isMaster: isMaster
          }
        );
      }
      else {
        // add frame to node
      }
    }
    else {
      alert("Frame pusblished by a non registered node");
    }
  }
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
                                signals_obj.push(    {
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
                        if (frames_bracket === 1 && frames_bracket_sub == 0) { // get the name of the frame
                            if(line_string === '{'){
                                frames_bracket_sub  = 1;
                                break;
                            }
                            else if (line_string == '}') {
                                frames_bracket =2; // end of frames
                                break;
                            }
                            frame_name_loc = line_string.match(/^\w+/gi)[0];
                            sub_frame_loc = line_string.match(/:(.*)$/i)[1].split(',')
                            frame_id_loc = sub_frame_loc[0];
                            frame_pub_by_loc = sub_frame_loc[1]; //published_by
                            frame_size_loc = sub_frame_loc[2] || 0; // size of frame if 0 the undef

                        } else if (frames_bracket == 1 && frames_bracket_sub == 1) {
                            if(line_string === '}'){
                                frames_bracket_sub  = 2;
                                //insert frame obj
                                frames_obj.push({
                                    frame_name: frame_name_loc,
                                    frame_id: frame_id_loc,
                                    published_by: frame_pub_by_loc,
                                    frame_size: frame_size_loc,
                                    signals_frms: sub_frame_sigs
                                });
                                sub_frame_sigs = [];
                                frames_bracket_sub = 0;
                                break;
                            }
                            signal = line_string.match(/\w+/gi);
                            sub_frame_sigs.push({
                                signal_name: signal[0],
                                signal_offset: Number(signal[1])
                            });

                        }

                        if(frames_bracket === 0 && line_string === '{'){
                            frames_bracket = 1;
                            frames_bracket_sub  = 0;
                            sub_frame_sigs = [];
                        }
                        break;
                    case states['sched_tables']://////////////////////////////////////////
                        console.log('state sched_tables');
                        if (sched_bracket === 1 && frames_bracket_sub == 0) { // get the name of the frame
                            if(line_string === '{'){
                                frames_bracket_sub  = 1;
                                break;
                            }
                            else if (line_string == '}') {
                                sched_bracket =2; // end of frames
                                break;
                            }
                            // get the name of the table
                            sched_table_name = line_string;
                        } else if (sched_bracket == 1 && frames_bracket_sub == 1) {
                            if(line_string === '}'){
                                // insert frame
                                sched_table_obj={
                                    table_name:sched_table_name,
                                    frames:sub_frame_sched
                                };
                                frames_bracket_sub = 0;
                                break;
                            }
                            frame_subStr = line_string.split('delay');
                            sub_frame_sched.push({
                                frame_name_sched: frame_subStr[0],
                                frame_delayms: Number(frame_subStr[1].match(/\d+/gi))
                            });
                        }


                        if(sched_bracket === 0 && line_string === '{'){
                            sched_bracket = 1;
                            sched_bracket_sub  = 0;
                            sub_frame_sched = [];
                        }
                        break;
                    case states['initial']:///////////////////////////////////////////////
                        console.log('state ink');
                        break;
                    default:

                }
            }
        // }

}
