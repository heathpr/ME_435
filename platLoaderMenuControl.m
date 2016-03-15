clc
clear variables
close all


%close any open conections
open_ports=instrfind('Type','serial','Status','open');
if ~isempty(open_ports)
    fclose(open_ports);
end

fprintf('Connecting to Robot...')
s=serial('COM4','BaudRate',19200,'Terminator',10,'Timeout',5);
fprintf('\nStatus os %s\n',s.Status)
fprintf('Opening...\n')
fopen(s);
fprintf('Status is %s\n',s.Status)
fprintf(s,'INITIALIZE');
fprintf(getResponse(s));


while(1)
    switch(menu('Choose command','Reset','X-Axis',...
            'Z-Axis','Gripper','Move','Status','Special Moves','Exit'))
        case 1
            fprintf(s,'RESET');
            fprintf(getResponse(s))
        case 2
            fprintf(s,['X-AXIS ',num2str(menu('Choose location to move to','1','2','3','4','5'))]);
            fprintf(getResponse(s))
        case 3
            switch(menu('Z-AXIS:','EXTEND','RETRACT'))
                case 1
                    fprintf(s,'Z-AXIS EXTEND');
                case 2
                    fprintf(s,'Z-AXIS RETRACT');
            end
            fprintf(getResponse(s))
        case 4
            switch(menu('Gripper:','OPEN','CLOSE'))
                case 1
                    fprintf(s,'GRIPPER OPEN');
                case 2
                    fprintf(s,'GRIPPER CLOSE');
            end
            fprintf(getResponse(s))
        case 5
            prompt = {'Location to pick up from:','Location to move to:'};
            dlg_title = 'Move Menu';
            num_lines = 1;
            answer = inputdlg(prompt,dlg_title,num_lines);
            movement=sprintf('MOVE %c %c',answer{1},answer{2})
            fprintf(s,movement);
            fprintf(getResponse(s))
        case 6
            fprintf(s,'LOADER_STATUS');
            fprintf(getResponse(s))
        case 7
            uiwait(helpdlg('Please place plates ar locations 4 and 5'));
            fprintf(s,'X-AXIS 5');
            fprintf(getResponse(s))
            fprintf(s,'GRIPPER OPEN');
            fprintf(getResponse(s))
            fprintf(s,'Z-AXIS EXTEND');
            fprintf(getResponse(s))
            fprintf(s,'GRIPPER CLOSE');
            fprintf(getResponse(s))
            fprintf(s,'Z-AXIS RETRACT');
            fprintf(getResponse(s))
            
            fprintf(s,'X-AXIS 3');
            fprintf(getResponse(s))
            fprintf(s,'Z-AXIS EXTEND');
            fprintf(getResponse(s))
            fprintf(s,'GRIPPER OPEN');
            fprintf(getResponse(s))
            fprintf(s,'Z-AXIS RETRACT');
            fprintf(getResponse(s))
            
            fprintf(s,'X-AXIS 4');
            fprintf(getResponse(s))
            fprintf(s,'Z-AXIS EXTEND');
            fprintf(getResponse(s))
            fprintf(s,'GRIPPER CLOSE');
            fprintf(getResponse(s))
            fprintf(s,'Z-AXIS RETRACT');
            fprintf(getResponse(s))
            
            fprintf(s,'X-AXIS 2');
            fprintf(getResponse(s))
            fprintf(s,'Z-AXIS EXTEND');
            fprintf(getResponse(s))
            fprintf(s,'GRIPPER OPEN');
            fprintf(getResponse(s))
            fprintf(s,'Z-AXIS RETRACT');
            fprintf(getResponse(s))
            
            fprintf(s,'X-AXIS 3');
            fprintf(getResponse(s))
            fprintf(s,'Z-AXIS EXTEND');
            fprintf(getResponse(s))
            fprintf(s,'GRIPPER CLOSE');
            fprintf(getResponse(s))
            fprintf(s,'Z-AXIS RETRACT');
            fprintf(getResponse(s))
            
            fprintf(s,'X-AXIS 1');
            fprintf(getResponse(s))
            fprintf(s,'Z-AXIS EXTEND');
            fprintf(getResponse(s))
            fprintf(s,'GRIPPER OPEN');
            fprintf(getResponse(s))
            fprintf(s,'Z-AXIS RETRACT');
            fprintf(getResponse(s))
            
            fprintf(s,'RESET');
            fprintf(getResponse(s))
        case 8
            fclose('all');
            break;
    end
end
