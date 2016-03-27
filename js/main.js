

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
    parseSignals();

    /***************************************
    Load template
     ***************************************/
    var templateSrc = document.getElementById( "results-template" ).innerHTML;
    var template = Handlebars.compile(templateSrc);
    /*Iterator for UINT8 vars */
    Handlebars.registerHelper('list_u8', function(context, options) {
      var ret = "UINT8 ";

      for(var i=0, j=context.length; i<j; i++) {
        ret = ret  + options.fn(context[i]) + "</li>";
      }

      return ret + "</ul>";
    });


    var data = {"person":
     {
     "name": "Handlebars",
     "last": "Demo"
   },
     "lin_cfg":{
        "gen_date": "12.1.1524"
     },
     signals: signals_obj,
     nav: [
       { url: "http://www.yehudakatz.com", title: "Katz Got Your Tongue" },
       { url: "http://www.sproutcore.com/block", title: "SproutCore Blog" },
    ]
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
var frames_bracket_sub = 0;
var sched_bracket = 0;
var sched_bracket_sub = 0;

function parseNodes() {

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


//var bnt_gen =
